#pragma once

#include <stdio.h>
#pragma once
#include <iostream>
#include <fstream>
#include <string>
//#include <stdio.h>
#include "Constants.h"
#include "Network.h"

class backPropagate;
class inputLayer;
class hiddenLayer;
class outputLayer;
class weights;

class dataIO
{
private:
	//std::string fileName;
	
	double** inputSet;
	double** outputSet;
	
	int* inputDataLengths;	
	int* outputDataLengths;

	int numberOfInputs;
	int numberOfOutputs;

public:
	dataIO(int x, int y);
	void initialise(void);
	void UI(inputLayer iL, weights wil, hiddenLayer hL, weights who, outputLayer oL);
	char clampOutputs(double x);
	void readInputs(void);
	void readOutputs(void);
	double** getInputs(void);
	double** getOutputs(void);
	double getInput(int x, int y);
	double getOutput(int x, int y);
	int getInputDataLengths(int x);
	void checkDataLenghts(void);
};


