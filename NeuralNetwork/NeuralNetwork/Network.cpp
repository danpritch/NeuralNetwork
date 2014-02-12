#include "Network.h"

#include <iostream>
#include <math.h>

//Functions for input layer

inputLayer::inputLayer(int n)
{
	numInputs = n;
	inputNeurons = new(double[(numInputs + 1)]);
	for (int i = 0; i < numInputs; i++){ inputNeurons[i] = 0;}
	inputNeurons[numInputs] = -1;
}

double inputLayer::getNeuron(int n)
{
	return inputNeurons[n];
}

void inputLayer::setNeuron(int n, double value)
{
	inputNeurons[n] = value;
}

int inputLayer::getInputs(void)
{
	return numInputs;
}

//Functions for hidden layer class

hiddenLayer::hiddenLayer(int n)
{
	numHidden = n;
	hiddenNeurons = new(double[(numHidden + 1)]);
	for (int i = 0; i < numHidden; i++) hiddenNeurons[i] = 0;
	hiddenNeurons[numHidden] = -1;
}

double hiddenLayer::getNeuron(int n)
{
	return hiddenNeurons[n];
}

void hiddenLayer::setNeuron(int n, double value)
{
	hiddenNeurons[n] = value;
}

int hiddenLayer::getNumHidden(void)
{
	return numHidden;
}

//Functions for output layer class

outputLayer::outputLayer(int n)
{
	numOutput = n;

	//No bias neuron
	outputNeurons = new(double[numOutput]);
	for (int i = 0; i <= numOutput; i++) outputNeurons[i] = 0;
}

double outputLayer::getNeuron(int n)
{
	return outputNeurons[n];
}

void outputLayer::setNeuron(int n, double value)
{
	outputNeurons[n] = value;
}

int outputLayer::getNumOutput(void)
{
	return numOutput;
}