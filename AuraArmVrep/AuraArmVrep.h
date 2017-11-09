
#ifndef AURAARMVREP_H


#define AURAARMVREP_H

#include <string>
#include <iostream>
#include "../Vdc/Vdc.h"

class AuraArmVrep {
public:


    AuraArmVrep(std::string serverIP, int serverPort);


    void setJoints(double alpha, double beta, double gama);
    bool getVisionInfo(int cam, double& rx, double& ry);
    void collectingData(int nSamples, std::string fileName, bool threshold(double rx, double ry));
    void trainingSOM(int size ,std::string SamplesFile);
    void VisualTest(std::string somOutputFile);

    //  void validadeTraining2D(std::string outputFile, std::string data);


private:
    void start();
    void saveSample(std::string file, double beta, double gamma, double rx, double ry);
    float randomValue();
    void randomAngle(double &beta, double &gamma);

    int Joint[3];
    int Webcam;
    Vdc * Vrep;


};

#endif // AURAARMVREP_H