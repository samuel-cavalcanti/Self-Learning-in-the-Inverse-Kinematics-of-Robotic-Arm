#ifndef EXTRAS_H
#define	EXTRAS_H


#include <iostream>
#include <string>
#include <fstream>
#include <cmath>

class Extras {
    
public:
    double pi();
    double ToDegree(double Degree);
    double ToRadians(double radians);
    void log(double beta, double gama, double relativeX, double relativeY, std::string filename);
    void logCsv_old(double beta, double gama, double relativeX, double relativeY);
    void logCsv(std::string data, std::string filename , std::string header);
    void log2(double alfa, double beta, double gama, double relativeXCam1, double relativeYCam1, double relativeXCam2, double relativeYCam2);
    void comecarDaOndeParou(std::string &filename, int &nColeta, int &nSamples, bool debug);
    void log3(std::string Data, std::string fileName);
    void checkAndAddTypeCSV(std::string fileName);
    
    
    
    
    
    
};



#endif	/* EXTRAS_H */






