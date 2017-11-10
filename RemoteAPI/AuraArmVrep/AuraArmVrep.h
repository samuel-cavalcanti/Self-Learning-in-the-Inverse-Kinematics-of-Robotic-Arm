
#ifndef AURAARMVREP_H


#define AURAARMVREP_H

#include <string>
#include <iostream>
#include "../Vdc/Vdc.h"
#include "../VrepToOpencv/VrepToOpencv.h"

class AuraArmVrep {
public:


    AuraArmVrep(std::string serverIP, int serverPort);
  
    void collectingData(int nSamples, std::string fileName, bool threshold(double rx, double ry), bool openCV);
    void trainingSOM(int size ,std::string SamplesFile);
    void VisualTest(std::string somOutputFile, bool openCV);
  
    

private:
    void start();
    void saveSample(std::string file, double beta, double gamma, double rx, double ry);
    float randomValue();
    void randomAngle(double &beta, double &gamma);
    bool getVisionData(double& rx, double& ry, bool openCV);
    bool getVisionVrep(int cam, double& rx, double& ry);
    bool getVisionOpenCV(double &rx, double& ry);
    void setJoints(double alpha, double beta, double gama);
    
      
    

    int Joint[3];
    int Webcam;
    Vdc * Vrep;
    VrepToOpencv* OpencvImage;
    
    

};


#endif // AURAARMVREP_H