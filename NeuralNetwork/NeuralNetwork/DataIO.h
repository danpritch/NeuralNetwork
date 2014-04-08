#pragma once

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
//#include <stdio.h>
#include "Constants.h"

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
	void readInputs(void);
	void readOutputs(void);
	double** getInputs(void);
	double** getOutputs(void);
	double getInput(int x, int y);
	double getOutput(int x, int y);
	int getInputDataLengths(int x);
	void checkDataLenghts(void);
};


