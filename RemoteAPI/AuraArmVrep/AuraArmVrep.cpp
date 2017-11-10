#include <AuraArmVrep.h>
#include "../Extras/extras.h"
#include "../SOM/SOM.h"
#include <iostream>
#include <sys/stat.h>
#include <boost/algorithm/string.hpp>
#include <string>
#include <fstream>
#include <unistd.h>

AuraArmVrep::AuraArmVrep(std::string serverIP, int serverPort) {
    Vrep = new Vdc(serverIP.c_str(), serverPort);
    start();
    OpencvImage = new VrepToOpencv(Vrep->getClientID(), Webcam);
    // OpencvImage->showImage("teste");
}

void AuraArmVrep::start() {
    Vrep->conectpiece("Webcam", Webcam);
    Vrep->conectpiece("Joint#1", Joint[0]);
    Vrep->conectpiece("Joint#2", Joint[1]);
    Vrep->conectpiece("Joint#3", Joint[2]);

}

void AuraArmVrep::setJoints(double alpha, double beta, double gama) {
    Vrep->setJointPosition(Joint[0], alpha);
    Vrep->setJointPosition(Joint[1], beta);
    Vrep->setJointPosition(Joint[2], gama);

}

void AuraArmVrep::collectingData(int nSamples, std::string filename, bool threshold(double, double), bool openCV) {
    double beta = 0;
    double gamma = 0;
    double relativeXCam = -1; // se ocorrer erro de leitor o seu valor continuará em -1
    double relativeYCam = -1;

    while (Vrep->simulationIsActive() and nSamples > 0) {

        /***************************************************************
            Calculando a posição aleatória para o braço
         ***************************************************************/
        randomAngle(beta, gamma);

        // atualização das posições das articulações
        Vrep->setJointPosition(Joint[1], beta);
        Vrep->setJointPosition(Joint[2], gamma);

        // espera um pouco antes de ler a câmera
        Vrep->delay(1000);
        /***************************************************************
            Obtendo a posição da ponta do braço na câmera
         ***************************************************************/
        getVisionData(relativeXCam, relativeYCam, openCV);


        // se a posição for uma possição valida 
        if (threshold(relativeXCam, relativeYCam)) {
            saveSample(filename.c_str(), beta, gamma, relativeXCam, relativeYCam);
            nSamples--;
        }


        // espera um pouco antes de reiniciar a leitura dos sensores
        Vrep->delay(1000);

    }
}

float AuraArmVrep::randomValue() {
    // gerando um valor aleatório entre 0 e 1.0
    double xDiv = 10000000;
    double x = rand() % int(xDiv);
    x = x / xDiv;
    return x;

}

void AuraArmVrep::randomAngle(double& beta, double& gamma) {


    double x = randomValue();

    beta = x * 3.14159265359;

    x = randomValue();

    gamma = x * 3.14159265359;



}

bool AuraArmVrep::getVisionData(double& rx, double& ry, bool openCV) {
    if (openCV)
        if (getVisionOpenCV(rx, ry))
            return true;
        else
            return false;
    else
        if (getVisionVrep(Webcam, rx, ry))
        return true;
    else
        return false;

}

bool AuraArmVrep::getVisionVrep(int cam, double& rx, double& ry) {
    std::vector<float> auxValues;
    int auxValuesCount;

    if (Vrep->simulationIsActive()) {
        //http://www.coppeliarobotics.com/helpFiles/en/regularApi/simReadVisionSensor.htm
        if (Vrep->readVisionSensor(cam, auxValues, auxValuesCount)) {



            if (auxValues[16] < 0.001 || auxValues[17] < 0.001)
                return false;

            rx = auxValues[16];
            ry = auxValues[17];


            // std::cout << "x: " << rx << " y: " << ry <<std::endl;
            return true;

        }

        return false;

    } // std::cout << "Simuation is off" << std::endl;
    return false;

}

bool AuraArmVrep::getVisionOpenCV(double& rx, double& ry) {
    if (OpencvImage->findRedColorMass(rx, ry))
        return true;

    return false;
}

void AuraArmVrep::saveSample(std::string file, double beta, double gamma, double rx, double ry) {
    Extras save;
    std::string data;
    std::string header = "beta,gamma,rx,ry";

    data = std::to_string(beta) + "," + std::to_string(gamma) + ",";
    data += std::to_string(rx) + "," + std::to_string(ry);

    save.logCsv(data.c_str(), file.c_str(), header.c_str());
}

void AuraArmVrep::VisualTest(std::string somOutputFile, bool openCV) {
    // carregando a SOM
   
    SOM som (36);
    som.loadNodes(somOutputFile.c_str());
    std::vector<double> sample = {0, 0, 0, 0}; // amostra parcial: beta , gamma , rx ,ry;

    // enquando a simuação estiver acontecendo
    while (Vrep->simulationIsActive()) {

        // obetendo o valor rx,ry da bola
        getVisionData(sample[2], sample[3], openCV);
        //encontrando o neuronio vencedor e recuperando o dados de controle 
        som.findBest(sample, 2, 3);

        // atribuindo ao braço os dados de controle da rede som 
        setJoints(0, sample[0], sample[1]);

        Vrep->delay(500);

    }

}

void AuraArmVrep::trainingSOM(int size, std::string samplesFile) {

    std::vector<std::string> results;
    std::string filename;

    boost::split(results, samplesFile, [](char c) {
        return c == '/';
    });

    filename = results[ results.size() - 1 ];
    results.clear();
    boost::split(results, filename, [](char c) {
        return c == '.';
    });
    filename = results[0];


    //setando posiçoes de leitura e escrita
    std::string directory = "output/" + filename + "Size" + std::to_string(size) + "/";
    std::string dataFile = samplesFile;
    std::string csvHeader;

    // criando diretório
    mkdir("output", 0777);
    mkdir(directory.c_str(), 0777);

    SOM som(size);

    DataSet *data = new DataSet(dataFile);
    data->show();
    std::string outputFile = directory + filename + "_" + "_Size" + std::to_string(size) + "_";
    som.setDataSet(data);

    // std::cout <<  outputFile << std::endl;



    float maxFeatureInitialValue = 0.01;
    // std::cout<< "data:: " << data->getSampleSize() << std::endl;
    som.initializeNodes(data->getSampleSize(), true, maxFeatureInitialValue);

    int iterations = 10000;


    // Execute many iterations 
    int i = 0;

    csvHeader = "x,y," + data->features;

    som.saveNodes(outputFile, csvHeader.c_str(), false);
    while (i < iterations) {
        som.executeOneIt();
        i++;
        if (i % 1000 == 0)
            som.saveNodes(outputFile, csvHeader.c_str(), false);
    }
    std::cout << "Iteractions executed: " << iterations << std::endl;

    delete data;


}



