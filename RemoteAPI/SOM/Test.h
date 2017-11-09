/* 
 * File:   Test.h
 * Author: oriva
 *
 * Created on 20 de Agosto de 2016, 11:37
 */

#ifndef TEST_H
#define TEST_H

#include "SOM.h"
#include <DataSet.h>
#include <fstream>
#include <string>

class Test {
public:
    Test();
    Test(const Test& orig);
    virtual ~Test();


    void armInTraining(int size, int n, std::string filename);
    void colorDataSet();
    void dataRecovery();
    void loadNeurons();
    void partialDistance();
    void meanSquaredErroTest_old(int size, std::string samplesFile, std::string output);
    void meanSquaredErroTest3D(int size, std::string samplesFile, std::string output);
    void ULTRA_MSE(int size, std::string samplesFile, std::string output);
    void toNormalize_old(std::string fileName); // normalize data
    void toNormalizeCsv(std::string fileName);
    void PseudoNormalizador(std::string fileName, std::string outputName);

private:



};

#endif /* TEST_H */

