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

//Added this
void hiddenLayer::calculate(inputLayer iL, weights wil)
{
	for(int j=0; j < numHidden; j++)
	{
		//clear value
		setNeuron(j, 0);
		
		//get weighted sum of pattern and bias neuron
		for( int i=0; i <= iL.getInputs(); i++ )
		{
			setNeuron(j, (getNeuron(j) + (iL.getNeuron(i) * wil.getWeight(i,j))));
		}
		
		//set to result of sigmoid
		setNeuron(j, activationFunction(getNeuron(j)));
	}
}

//Added this
double hiddenLayer::activationFunction(double x)
{
	//sigmoid function
	return 1/(1+exp(-x));
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

//Added this
void outputLayer::calculate(hiddenLayer hL, weights who)
{
	for(int k=0; k < numOutput; k++)
	{
		//clear value
		setNeuron(k, 0);
		
		//get weighted sum of pattern and bias neuron
		for( int j=0; j <= hL.getNumHidden(); j++ ) 
		{
			setNeuron(k, (getNeuron(k) + (hL.getNeuron(j) * who.getWeight(j,k))));
		}
		
		//set to result of sigmoid
		setNeuron(k, activationFunction(getNeuron(k)));
	}
}

//Added this
double outputLayer::activationFunction(double x)
{
	//sigmoid function
	return 1/(1+exp(-x));
}

weights::weights(inputLayer iL, hiddenLayer hL)
{
	numLayerOne = iL.getInputs();
	numLayerTwo = hL.getNumHidden();
	weightArray = new(double*[numLayerOne + 1]);
	for (int i = 0; i <= numLayerOne; i++)
	{
		weightArray[i] = new(double[numLayerTwo + 1]);
		for (int j = 0; j <= numLayerTwo; j++) weightArray[i][j] = 0;
	}

	//Weights need to be initialise here.
	initialiseWeights(numLayerOne);
}

weights::weights(hiddenLayer hL, outputLayer oL)
{
	numLayerOne = hL.getNumHidden();
	numLayerTwo = oL.getNumOutput();
	weightArray = new(double*[numLayerOne + 1]);
	for (int i = 0; i <= numLayerOne; i++)
	{
		weightArray[i] = new(double[numLayerTwo + 1]);
		for (int j = 0; j <= numLayerTwo; j++) weightArray[i][j] = 0;
	}
	initialiseWeights(numLayerTwo);
}

double weights::getWeight(int layerOne , int layerTwo)
{
	return weightArray[layerOne][layerTwo];
}

void weights::setWeight(int layerOne , int layerTwo, double value)
{
	weightArray[layerOne][layerTwo] = value;
}

void weights::incrementWeight(int layerOne , int layerTwo, double value)
{
	weightArray[layerOne][layerTwo] += value;
}

void weights::initialiseWeights(int n)
{
	double weightRand = 1/sqrt(double(n));
	
	for(int i = 0; i <= numLayerOne; i++)
	{		
		for(int j = 0; j < numLayerTwo; j++) 
		{
			weightArray[i][j] = ( ( (double)(rand()%100)+1)/100  * 2 * weightRand ) - weightRand;	
		}
	}
}