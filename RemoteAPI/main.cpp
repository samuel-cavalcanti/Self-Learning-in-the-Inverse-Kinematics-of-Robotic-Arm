#include "AuraArmVrep/AuraArmVrep.h"
#include <iostream>

using namespace std;

bool threshold1D(double rx,double ry);
bool threshold2D(double rx,double ry);
    
int main (){  
    
    bool openCV = false; 
    AuraArmVrep exemple ("127.0.0.1",19999);
   
    //exemple.collectingData(3,"test.csv", threshold1D,openCV);
    //exemple.trainingSOM(36,"Coleta/ArmInLine.csv");
    //exemple.VisualTest("outputs/amostrasFinaisSize36/amostrasFinais.csv_1_Size36_10000.csv", openCV);
 
   
}

bool threshold1D( double rx,double ry){
     /* coleta de dados para o movimento 1D
      * o mesmo apresentado no artigo 
      */
    if (ry > 0.28 and ry < 0.30)
        return(true);
    
    return(false);
}

bool threshold2D ( double rx, double ry){
    /* coleta de dados para o movimento 2D 
     * o mesmo apresentado no artigo 
     */
    if (rx <= 0.45 and ry >= 0.29 )
        return(true);
    
    return(false);
}