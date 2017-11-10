
#include "extras.h"
#include <iostream>
#include <string>
#include <fstream>
#include <cmath>


using namespace std;

double Extras::pi() {
    return 3.141592653589;

}

double Extras::ToDegree(double Degree) {
    return (Degree * 3.14159265359) / 180;
}
double Extras::ToRadians(double radians){
    return (radians*180)/3.14159265359;
}

// Algoritmos para gerenciamento de arquivos

void Extras::log(double beta, double gama, double relativeX, double relativeY, string filename) {
    ofstream myfile;
    string data;


    myfile.open(filename.c_str(), ios::app); // abrindo o log

    if (myfile.is_open() && myfile.good()) {
        data = to_string(beta) + "  " + to_string(gama) + "  " + to_string(relativeX) + "  " + to_string(relativeY);

        myfile << data << endl;
    }

    myfile.close();
}

void Extras::log3(std::string Data, std::string fileName) {
    ofstream myfile;

    myfile.open(fileName.c_str(), ios::app); // abrindo o log

    if (myfile.is_open() && myfile.good()) {
        myfile << Data << endl;
    }

    myfile.close();

}
void Extras::checkAndAddTypeCSV(std::string fileName){
    string typeFile = ".csv";
    for(int i=0; i< typeFile.size(); i++){
        if(typeFile[i] != fileName[fileName.size() -4 +i]){
           
            fileName+=typeFile;
            break;
        }
    }
 
}

void Extras::logCsv(std::string data, std::string filename, std::string header) {
    ofstream myfile;
    Extras::checkAndAddTypeCSV(filename.c_str());

    while (true) {
        myfile.open(filename.c_str(), ios::in);
        if (myfile.is_open() && myfile.good()) {
            myfile.close();
            myfile.open(filename.c_str(), ios::app);
            myfile << data << endl;
          //  cout << data << endl;
            return;
        } else {
            myfile.open(filename.c_str(), ios::app);
            if (myfile.is_open() && myfile.good()) {
                myfile << header << endl;
                myfile.close();
            }

        }

    }


}

void Extras::logCsv_old(double beta, double gama, double relativeX, double relativeY) {
    ofstream myfile;
    string data;


    myfile.open("teste.csv", ios::in);
    if (myfile.is_open() && myfile.good()) {
        myfile.close();
        myfile.open("teste.csv", ios::app);
        data = to_string(beta) + ", " + to_string(gama) + ", " + to_string(relativeX) + ", " + to_string(relativeY);
        myfile << data << endl;
    } else {
        myfile.open("teste.csv", ios::app);
        if (myfile.is_open() && myfile.good()) {
            data = "beta, gamma, rx, ry";
            myfile << data << endl;
        }



    }



}

void Extras::log2(double alfa, double beta, double gama, double relativeXCam1, double relativeYCam1, double relativeXCam2, double relativeYCam2) {
    ofstream myfile;
    string data;

    myfile.open("amostrasArm3D", ios::app); // abrindo o log

    if (myfile.is_open() && myfile.good()) {
        data = to_string(alfa) + "  " + to_string(beta) + "  " + to_string(gama) + "  " + to_string(relativeXCam1) + "  " + to_string(relativeYCam1) + "  " + to_string(relativeXCam2) + " " + to_string(relativeYCam2);
        ;

        myfile << data << endl;
    }

    myfile.close();
}

void Extras::comecarDaOndeParou(string &filename, int &nColeta, int &nSamples, bool debug) {

    string aux;

    ifstream myfile;


    myfile.open(filename.c_str(), ios::in);

    while (myfile.is_open() && myfile.good()) {

        myfile.close();
        nColeta++;
        filename = "coletaEmLinha_" + to_string(nColeta);
        myfile.open(filename.c_str(), ios::in);

    }
    nColeta--;
    filename = "coletaEmLinha_" + to_string(nColeta);
    if (debug)
        cout << "filename: " << filename << endl;



    myfile.open(filename.c_str(), ios::in);

    while (getline(myfile, aux)) {
        nSamples--;
    }

    if (debug)
        cout << "nSamples: " << nSamples << endl;



    /*
    #include <dirent.h>
    
    if( opendir("teste1") )
  cout << "ok" <<endl;

  else
    system("mkdir \"teste1\"");


     */

}

