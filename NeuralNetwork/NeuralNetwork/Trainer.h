#pragma once
#include "Network.h"
#include "Constants.h"
#include "DataIO.h"
//Propagation class

//Back propagation class
//Private variables will be deltas and gradients

class inputLayer;
class hiddenLayer;
class outputLayer;
class weights;

class backPropagate
{
private:
	//error gradients
	double* hiddenErrorGradients;
	double* outputErrorGradients;

	//change to weights
	double** deltaInputHidden;
	double** deltaHiddenOutput;

	//Training output
	double** trainingOutput;

	//Set error
	double* setError;

	int numInput;
	int numHidden;
	int numOutput;

public:

	backPropagate(int iL, int hL, int oL);

	//Need variables more desciriptive than i and j but i'll change that later
	//HiddenErrorGradients
	//removing learning rate to use the constant instead.
	void errorsAndGradients(inputLayer iL, hiddenLayer hL,  outputLayer oL, weights who, int index);

	double getTrainingOutput(int i, int j);

	void fillTrainingOutput(int i, int j, double value);

	//This is the one
	void fillTrainingOutput(double data[][output]);

	//Changed to add dataIO to argument
	void initialise(int length, int width, dataIO data);

	double getHiddenErrorGradient(int i);

	void setHiddenErrorGradient(int i, double value);

	void incrementHiddenErrorGradient(int i, double value);

	//OutputErrorGradients
	double getOutputErrorGradient(int i);

	void setOutputErrorGradient(int i, double value);

	void incrementOutputErrorGradient(int i, double value);

	//Deltas

	double getDeltaInputHidden(int i, int j);

	void setDeltaInputHidden(int i, int j, double value);

	void incrementDeltaInputHidden(int i, int j, double value);

	double getDeltaHiddenOutput(int i, int j);

	void setDeltaHiddenOutput(int i, int j, double value);

	void incrementDeltaHiddenOutput(int i, int j, double value);


};


