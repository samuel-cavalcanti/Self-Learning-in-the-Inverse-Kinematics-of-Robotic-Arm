/* 
 * File:   Test.cpp
 * Author: oriva
 * 
 * Created on 20 de Agosto de 2016, 11:37
 */

#include <Test.h>
#include <sys/stat.h>
#include <cmath>
#include <fstream>
//#include "../Extras/extras.h"

Test::Test() {
}

Test::~Test() {
}

Test::Test(const Test& orig) {
}

void Test::colorDataSet() {
    std::string fileData = "data/cores_3d.txt";

    SOM som(10);
    DataSet *data = new DataSet(fileData);
    data->show();

    som.setDataSet(data);


    float maxColorInitialValue = 0.02;
    som.initializeNodes(3, true, maxColorInitialValue);

    int iterations = 150;


    // Execute many iterations 
    int i = 0;
    som.printNodes();
    while (i < iterations) {
        som.executeOneIt();
        i++;
        som.printNodes();
    }
    std::cout << "Iteractions executed: " << iterations << std::endl;

    delete data;
}

void Test::armInTraining(int size, int n, std::string filename) {



    //setando posiçoes de leitura e escrita
    std::string directory = "output/" + filename + "Size" + std::to_string(size) + "/";
    std::string subDirectory = directory + filename + "Size" + std::to_string(size) + "N" + std::to_string(n) + "/";
    std::string dataFile = "Coleta/" + filename;
    std::string csvHeader;

    // criando diretório
    mkdir("output", 0777);
    mkdir(directory.c_str(), 0777); // 
    mkdir(subDirectory.c_str(), 0777);

    SOM som(size);

    DataSet *data = new DataSet(dataFile);
    data->show();
    std::string outputFile = subDirectory + filename + "_" + std::to_string(n) + "_Size" + std::to_string(size) + "_";
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
       // if (i % 1000 == 0)
            som.saveNodes(outputFile, csvHeader.c_str(), false);
    }
    std::cout << "Iteractions executed: " << iterations << std::endl;

    delete data;



}

void Test::dataRecovery() {
    SOM som(150);
    // amostra original: 0.730579, 1.68034, 0.276046, 0.250247}
    std::vector<double> sample = {0, 0, 0.276046, 0.250247}; // amostra parcial 
    // sample[2] = 0.276046
    // sample[3] = 0.250247

    som.loadNodes("data/Arm_in_Plane_6_Size50_1000.csv");
    som.printNodes(true);

    som.findBest(sample, 2, 3);

    //  amostra recuperada 
    for (int i = 0; i < 4; i++) {
        std::cout << sample[i] << " ";
    }
    std::cout << std::endl;
}

void Test::loadNeurons() {

    SOM som(12);

    float maxFeatureInitialValue = 0.01;
    som.initializeNodes(9, true, maxFeatureInitialValue);
    som.printNodes(true);

    som.loadNodes("output/example.txt");

    som.printNodes(true);
}

/**
 * Test for the function that calculates the partial distance from a sample.
 * At the end the method calculates and shows the distance comparing with desired value 
 */
void Test::partialDistance() {
    // Sample 1
    // 1.25507 0.631361 0.153656 0.24678 
    std::vector<double> v1 = {1.25507, 0.631361, 0.153656, 0.24678};

    // Sample 2 
    // 1.20418 0.733149 0.160494 0.246656
    std::vector<double> v2 = {1.20418, 0.733149, 0.160494, 0.246656};

    Sample s(v1);
    std::cout << " Distância Parcial [2-3] " << s.distance(v2, 2, 3) << " == 0.0068392" << std::endl;

    // valor desejado 0.0068392 para estas amostras 
}

void Test::meanSquaredErroTest_old(int size, std::string samplesFile, std::string output) {
    int lines;
    int teste;
    double beta, gama, rx, ry;
    double somaDaDiferencaBeta = 0;
    double somaDaDiferencaGama = 0;
    double mseBeta, mseGama;
    std::vector<double> sample = {0, 0, 0, 0};
    SOM som(size);
    som.loadNodes(output.c_str());
    std::ifstream coleta;
    std::ofstream resultado;
    std::string resultadotxt;





    coleta.open(samplesFile.c_str());
    if (coleta.is_open() && coleta.good()) {

        coleta >> lines >> teste;
        std::cout << "lines: " << lines << std::endl;
        for (int i = 0; i < lines; i++) {
            coleta >> beta >> gama >> rx >> ry;
            sample = {0, 0, rx, ry};
            som.findBest(sample, 2, 3);

            /* 
             std::cout << "beta: " << beta << " sample[0]: " << sample[0] << std::endl;
             std::cout << "gama: " << gama << " sample[1]: " << sample[1] << std::endl;
             std::cout << "rx: " << rx << " ry: " << ry << std::endl;
             */

            somaDaDiferencaBeta += (beta - sample[0]) * (beta - sample[0]);
            somaDaDiferencaGama += (gama - sample[1]) * (gama - sample[1]);

        }

        coleta.close();

    } else
        std::cout << " arquivo não encontrando" << std::endl;

    mseBeta = somaDaDiferencaBeta / lines;
    mseGama = somaDaDiferencaGama / lines;

    resultadotxt = "resultadosMSE/resultadoMSE_" + std::to_string(lines) + "samples_size" + std::to_string(size) + "x" + std::to_string(size) + ".txt";

    resultado.open(resultadotxt.c_str());
    if (resultado.is_open() && resultado.good()) {


        resultado << "tamanho da rede: " << size << "x" << size << std::endl;
        resultado << "quantidade de amostras no treinamento: " << lines << std::endl;
        resultado << "quantidade de amostras na validação: " << lines << std::endl;
        resultado << "Mean Squared Error beta: " << mseBeta << std::endl;
        resultado << "Mean Squared Error gama: " << mseGama << std::endl;




    } else
        std::cout << " arquivo não encontrando" << std::endl;










}

void Test::meanSquaredErroTest3D(int size, std::string samplesFile, std::string output) {


    std::vector<double> sample;
    SOM som(size);
    som.loadNodes(output.c_str());


    std::ifstream coleta;
    std::ofstream resultado;
    std::string aux;
    std::string cell;
    std::size_t pos1 = output.find("Coleta"); // position of Coleta" in file
    std::size_t pos = output.find(".csvSize"); // position of ".csv" in file
    std::string resultadotxt = "MSE/MSE_" + output.substr(pos1, pos - pos1) + "Size" + std::to_string(size) + ".txt";


    samplesFile = "Coleta/" + samplesFile;
    // std::cout << samplesFile << std::endl;

    int columns = 0;
    int rows = 0;
    double alfa, beta, gama;
    double somaDaDiferencaAlfa = 0;
    double somaDaDiferencaBeta = 0;
    double somaDaDiferencaGama = 0;
    double mseAlfa;
    double mseBeta;
    double mseGama;





    coleta.open(samplesFile.c_str());

    if (coleta.is_open() && coleta.good()) {

        std::getline(coleta, aux); // pula primeira linha  
        std::stringstream lineStreamFeatures(aux); //capiturando linha
        // std::cout << aux <<std::endl;
        while (std::getline(lineStreamFeatures, cell, ','))
            columns++;

        // std::cout << "columns: "<< columns <<std::endl;

        ///sample.resize(columns);  


        while (std::getline(coleta, aux)) {
            std::stringstream lineStream(aux);
            //std::cout << aux <<std::endl;
            while (std::getline(lineStream, cell, ',')) {
                alfa = std::stod(cell);
                //  std::cout << alfa << ",";
                sample.push_back(alfa);
            }
            //std::cout<<std::endl;
            // std::cout << sample[0]<<","<<sample[1]<<","<<sample[2]<<","<<sample[3]<<","<< sample[4]<<","<<sample[5] << std::endl;
            //  printf("%f,%f,%f,%f,%f,%f \n",sample[0],sample[1],sample[2],sample[3],sample[4],sample[5]);

            alfa = sample[0];
            beta = sample[1];
            gama = sample[2];
            sample[0] = 0;
            sample[1] = 0;
            sample[2] = 0;

            som.findBest(sample, 3, 5);

            somaDaDiferencaAlfa += (alfa - sample[0]) * (alfa - sample[0]);
            somaDaDiferencaBeta += (beta - sample[1]) * (beta - sample[1]);
            somaDaDiferencaGama += (gama - sample[2]) * (gama - sample[2]);
            // printf("%f %f\n",alfa , sample[0]);
            rows++;
            sample.clear();
        }

        // std::cout << "rows: "<< rows<<std::endl;

    } else {
        std::cout << " arquivo Coleta não encontrando" << std::endl;
        return;
    }
    mseAlfa = somaDaDiferencaAlfa / rows;
    mseBeta = somaDaDiferencaBeta / rows;
    mseGama = somaDaDiferencaGama / rows;


    resultado.open(resultadotxt.c_str());
    if (resultado.is_open() && resultado.good()) {

        resultado << "tamanho da rede: " << size << "x" << size << std::endl;
        resultado << "quantidade de amostras no treinamento: " << rows << std::endl;
        resultado << "quantidade de amostras na validação: " << rows << std::endl;
        resultado << "Mean Squered Error alfa: " << mseAlfa << std::endl;
        resultado << "Mean Squared Error beta: " << mseBeta << std::endl;
        resultado << "Mean Squared Error gama: " << mseGama << std::endl;




    } else
        std::cout << resultadotxt << " não encontrando" << std::endl;





    std::cout << "MSE_SOM_Size" << size << " finish" << std::endl;





}

void Test::ULTRA_MSE(int size, std::string samplesFile, std::string output) {
    int lines;
    int error;
    int totalSamples = 0;
    double beta, gama, rx, ry;
    double somaDaDiferencaBeta = 0;
    double somaDaDiferencaGama = 0;
    double somaDaDiferencaBeta1 = 0;
    double somaDaDiferencaGama1 = 0;
    double mseBeta1[30];
    double mseGamma1[30];
    double mediaMseBeta = 0;
    double mediaMseGamma = 0;
    double mseBeta;

    double mseGamma;
    double sBeta = 0;
    double sGamma = 0;
    std::vector<double> sample = {0, 0, 0, 0};
    std::string aux = "/";
    std::string directorySamples = "Coleta";
    std::string size_str = std::to_string(size);
    SOM som(size);
    //output/ArmInLineSize , ArmInLine
    std::string preOutput = output + size_str + aux + samplesFile + "Size" + size_str + "N";
    directorySamples += aux + samplesFile;
    std::ifstream coleta;
    std::ofstream resultado;
    std::string resultadotxt;




    for (int i = 1; i <= 30; i++) {
        std::string i_str = std::to_string(i);

        output = preOutput + i_str + aux + samplesFile + "_" + i_str + "_Size" + size_str + "_10000.csv";
        som.loadNodes(output.c_str());

        std::cout << output << std::endl;

        coleta.open(directorySamples.c_str());
        if (coleta.is_open() && coleta.good()) {

            coleta >> lines >> error;
            std::cout << "lines: " << error << std::endl;
            for (int i = 0; i < lines; i++) {
                coleta >> beta >> gama >> rx >> ry;
                sample = {0, 0, rx, ry};
                som.findBest(sample, 2, 3);



                somaDaDiferencaBeta += (beta - sample[0]) * (beta - sample[0]);
                somaDaDiferencaGama += (gama - sample[1]) * (gama - sample[1]);
                somaDaDiferencaBeta1 += (beta - sample[0]) * (beta - sample[0]);
                somaDaDiferencaGama1 += (gama - sample[1]) * (gama - sample[1]);

            }

            coleta.close();

        } else
            std::cout << " arquivo não encontrando" << std::endl;
        mseBeta1[i - 1] = somaDaDiferencaBeta1 / lines;
        mseGamma1[i - 1] = somaDaDiferencaGama1 / lines;
        totalSamples += lines;

        somaDaDiferencaBeta1 = 0;
        somaDaDiferencaGama1 = 0;


    }
    for (int i = 0; i < 30; i++) {
        mediaMseBeta += mseBeta1[i];
        mediaMseGamma += mseGamma1[i];
    }
    mediaMseBeta = mediaMseBeta / 30;
    mediaMseGamma = mediaMseGamma / 30;

    for (int i = 0; i < 30; i++) {
        sBeta += (mseBeta1[i] - mediaMseBeta) * (mseBeta1[i] - mediaMseBeta);
        sGamma += (mseGamma1[i] - mediaMseGamma) * (mseGamma1[i] - mediaMseGamma);
    }
    sBeta = std::sqrt((sBeta / 29));
    sGamma = std::sqrt((sGamma / 29));




    mseBeta = somaDaDiferencaBeta / totalSamples;
    mseGamma = somaDaDiferencaGama / totalSamples;

    resultadotxt = "resultadosMSE/resultadoMSE_" + samplesFile + size_str;

    resultado.open(resultadotxt.c_str());
    if (resultado.is_open() && resultado.good()) {


        resultado << "tamanho da rede: " << size << "x" << size << std::endl;
        resultado << "quantidade de amostras no treinamento: " << lines << std::endl;
        resultado << "quantidade de amostras na validação: " << lines << std::endl;
        resultado << "MEGA Mean Squared Error beta: " << mseBeta << std::endl;
        resultado << "MEGA Mean Squared Error gama: " << mseGamma << std::endl;
        resultado << "Desvio padrão do Beta: " << sBeta << std::endl;
        resultado << "Desvio padrão do Gamma: " << sGamma << std::endl;
        resultado << "Media de MseBeta" << mediaMseBeta << std::endl;
        resultado << "Media de MseGamma" << mediaMseGamma << std::endl;





    } else
        std::cout << " arquivo não encontrando" << std::endl;


}

void Test::toNormalize_old(std::string fileName) {
//    Extras extras;

    // normalizeData(filename.c_str());

    std::fstream data;
    std::ofstream myfile;
    //std::vector<std::vector<double>> matrix;

    std::string nameOfNewData = fileName + "Normalized";


    int rows;
    int columns;


    data.open(fileName.c_str());

    if (data.is_open() && data.good()) {
        data >> rows >> columns;

        std::vector < std::vector < double > > matrix(rows + 2, std::vector< double >(columns, 0));




        for (int j = 0; j < columns; j++) {
            matrix[rows][j] = 9999999; //Vmin
            matrix[rows + 1][j] = -matrix[rows][j]; // Vmax
        }
        //std::cout << "matrix: "<< matrix[rows][0] <<std::endl;




        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++) {
                data >> matrix[i][j];

                if (matrix[i][j] < matrix[rows][j]) //catching Vmin
                    matrix[rows][j] = matrix[i][j];

                if (matrix[i][j] > matrix[rows + 1][j]) // catching Vmax
                    matrix[rows + 1][j] = matrix[i][j];

            }


        //std::cout << "matrix: "<< matrix[0][0] <<std::endl;

        data.close();

        for (int i = 0; i < rows; i++)
            for (int j = 0; j < columns; j++) {
                matrix[i][j] = (matrix[i][j] - matrix[rows][j]) / (matrix[rows + 1][j] - matrix[rows][j]);
            }

   //     for (int i = 0; i < rows; i++)
  //          extras.log(matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3], nameOfNewData.c_str());









    }
}

void Test::toNormalizeCsv(std::string fileName) {
    //Extras extras;

    fileName = "Coleta/" + fileName;


    // normalizeData(filename.c_str());

    std::fstream data;
    std::ofstream myfile;
    std::size_t pos = fileName.find(".csv"); // position of ".csv" in fileName
    std::string str2 = fileName.substr(0, pos);
    std::string nameOfNewData = fileName.substr(0, pos) + "Normalized.csv";
    std::string aux;
    std::string csvHeader;


    int rows = 0;
    int columns = 0;



    data.open(fileName.c_str());

    if (data.is_open() && data.good()) {

        std::getline(data, aux); // pula primeira linha
        csvHeader = aux;

        std::stringstream lineStreamHeader(aux);

        while (std::getline(lineStreamHeader, aux, ','))
            columns++;

        while (getline(data, aux))
            rows++;



        data.close();
    } else {
        std::cout << "File is not found" << std::endl;
        return;
    }

    std::vector < std::vector < double > > matrix(rows + 2, std::vector< double >(columns, 0));

    for (int j = 0; j < columns; j++) {
        matrix[rows][j] = 9999999; //Vmin
        matrix[rows + 1][j] = -matrix[rows][j]; // Vmax
    }


    data.open(fileName.c_str());
    std::getline(data, aux); // pula primeira linha

    for (int i = 0; i < rows; i++) {
        std::getline(data, aux);
        std::stringstream lineStream(aux);
        std::string cell;
        for (int j = 0; j < columns; j++) {
            std::getline(lineStream, cell, ',');
            matrix[i][j] = std::stod(cell);

            if (matrix[i][j] < matrix[rows][j]) //catching Vmin
                matrix[rows][j] = matrix[i][j];

            if (matrix[i][j] > matrix[rows + 1][j]) // catching Vmax
                matrix[rows + 1][j] = matrix[i][j];


        }

    }

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++) {
            matrix[i][j] = (matrix[i][j] - matrix[rows][j]) / (matrix[rows + 1][j] - matrix[rows][j]);
        }


    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns - 1; j++) {
            std::string data = std::to_string(matrix[i][j]) + ",";
      //      extras.logCsv(data.c_str(), nameOfNewData.c_str(), csvHeader.c_str());
        }
       // extras.logCsv("\n", nameOfNewData.c_str(), csvHeader.c_str());
    }


    /*
        for (int i = 0; i < rows; i++)
            extras.log(matrix[i][0], matrix[i][1], matrix[i][2], matrix[i][3], nameOfNewData.c_str());
     */

    //std::cout << "matrix: "<< matrix[0][0] <<std::endl;

    data.close();





}

void Test::PseudoNormalizador(std::string fileName, std::string outputName) {
    //Extras extras;

    fileName = "Coleta/" + fileName;


    // normalizeData(filename.c_str());

    std::fstream data;
    std::ofstream myfile;
    std::size_t pos = fileName.find(".csv"); // position of ".csv" in fileName
    std::string str2 = fileName.substr(0, pos);
    std::string nameOfNewData = fileName.substr(0, pos) + "Normalized.csv";
    std::string aux;
    std::string csvHeader;


    int rows = 0;
    int columns = 0;



    data.open(fileName.c_str());

    if (data.is_open() && data.good()) {

        std::getline(data, aux); // pula primeira linha
        csvHeader = aux;

        std::stringstream lineStreamHeader(aux);

        while (std::getline(lineStreamHeader, aux, ','))
            columns++;

        while (getline(data, aux))
            rows++;



        data.close();
    } else {
        std::cout << "File is not found" << std::endl;
        return;
    }

    std::vector < std::vector < double > > matrix(rows, std::vector< double >(columns, 0));




    data.open(fileName.c_str());
    std::getline(data, aux); // pula primeira linha

    //    double auxValue;

    for (int i = 0; i < rows; i++) {
        std::getline(data, aux);
        std::stringstream lineStream(aux);
        std::string cell;
        for (int j = 0; j < columns; j++) {
            std::getline(lineStream, cell, ',');
            if (j > 1)
                matrix[i][j] = std::stod(cell) / 512;
            else
                matrix[i][j] = std::stod(cell);


        }

    }

    std::string value = "";

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (j != columns - 1)
                value += std::to_string(matrix[i][j]) + ",";
            else
                value += std::to_string(matrix[i][j]);
        }
        //  std::cout << value <<std::endl;
      //  extras.logCsv(value.c_str(), "teste.csv", csvHeader.c_str());
        value = "";
    }



    data.close();





}