#pragma once
#include "Network.h"
//Propagation class

//Back propagation class
//Private variables will be deltas and gradients

class backPropagate
{
private:
	//error gradients
	double* hiddenErrorGradients;
	double* outputErrorGradients;

	//change to weights
	double** deltaInputHidden;
	double** deltaHiddenOutput;

	int numInput;
	int numHidden;
	int numOutput;

public:
	backPropagate(inputLayer iL, hiddenLayer hL, outputLayer oL);

	//Need variables more desciriptive than i and j but i'll change that later
	//HiddenErrorGradients
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

//class forwardPass
//{
//private:
//	inputLayer iLayer;
//	hiddenLayer hLayer;
//	outputLayer oLayer;
//	weights iWeights;
//	weights hWeights;
//public:
//	forwardPass(inputLayer iL, weights wil, hiddenLayer hL, weights who, outputLayer oL);
//
//};
