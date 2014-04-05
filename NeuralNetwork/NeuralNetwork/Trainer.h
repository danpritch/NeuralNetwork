#pragma once
#include "Network.h"
#include "Constants.h"
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
	void errorsAndGradients(inputLayer iL, hiddenLayer hL,  outputLayer oL, weights who, double learningRate, int index);

	double getTrainingOutput(int i, int j);

	void fillTrainingOutput(int i, int j, double value);

	//This is the one
	void fillTrainingOutput(double data[][output]);

	void initialise(int length, int width);

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


