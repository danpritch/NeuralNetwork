#include "Trainer.h"
#include "Network.h"
#include <iostream>

backPropagate::backPropagate(inputLayer iL, hiddenLayer hL, outputLayer oL)
{
	numInput = iL.getInputs();
	numHidden = hL.getNumHidden();
	numOutput = oL.getNumOutput ();

	//Gradients
	hiddenErrorGradients = new( double[numHidden + 1] );
	for ( int i=0; i <= numHidden; i++ ) hiddenErrorGradients[i] = 0;
	
	outputErrorGradients = new( double[numOutput + 1] );
	for ( int i=0; i <= numOutput; i++ ) outputErrorGradients[i] = 0;

	//Deltas
	deltaInputHidden = new( double*[numInput + 1] );
	for ( int i=0; i <= numInput; i++ ) 
	{
		deltaInputHidden[i] = new (double[numHidden]);
		for ( int j=0; j < numHidden; j++ ) deltaInputHidden[i][j] = 0;		
	}

	deltaHiddenOutput = new( double*[numHidden + 1] );
	for ( int i=0; i <= numHidden; i++ ) 
	{
		deltaHiddenOutput[i] = new (double[numOutput]);			
		for ( int j=0; j < numOutput; j++ ) deltaHiddenOutput[i][j] = 0;		
	}

}

//Gradients
double backPropagate::getHiddenErrorGradient(int i)
{
	return hiddenErrorGradients[i];
}

void backPropagate::setHiddenErrorGradient(int i, double value)
{
	hiddenErrorGradients[i] = value;
}

void backPropagate::incrementHiddenErrorGradient(int i, double value)
{
	hiddenErrorGradients[i] += value;
}

double backPropagate::getOutputErrorGradient(int i)
{
	return outputErrorGradients[i];
}

void backPropagate::setOutputErrorGradient(int i, double value)
{
	outputErrorGradients[i] = value;
}

void backPropagate::incrementOutputErrorGradient(int i, double value)
{
	outputErrorGradients[i] += value;
}

//Deltas
double backPropagate::getDeltaInputHidden(int i, int j)
{
	return deltaInputHidden[i][j];
}

void backPropagate::setDeltaInputHidden(int i, int j, double value)
{
	deltaInputHidden[i][j] = value;
}

void backPropagate::incrementDeltaInputHidden(int i, int j, double value)
{
	deltaInputHidden[i][j] += value;
}

double backPropagate::getDeltaHiddenOutput(int i, int j)
{
	return deltaHiddenOutput[i][j];
}

void backPropagate::setDeltaHiddenOutput(int i, int j, double value)
{
	deltaHiddenOutput[i][j] = value;
}
	
void backPropagate::incrementDeltaHiddenOutput(int i, int j, double value)
{
	deltaHiddenOutput[i][j] += value;
}


//forwardPass::forwardPass(inputLayer iL, weights wil, hiddenLayer hL, weights who, outputLayer oL)
//{
//
//}
