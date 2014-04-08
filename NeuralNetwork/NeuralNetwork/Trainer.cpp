#include "Trainer.h"
//Changing these to ints. But that was kind of pointless.

backPropagate::backPropagate(int iL, int hL, int oL)
{
	numInput = iL;
	numHidden = hL;
	numOutput = oL;
}

//need to pass the training data sting into the argument here.
void backPropagate::initialise(int length, int width, dataIO data)
{
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

	//initialising training data here
	//Using new, set the length of the data.
	//okay i dont need this now, as im going to make the trainingOutput = dataIO.getOutput();
	//i Just dont havr the out put bits yet.
	//trainingOutput = new(double*[length]);
	//for (int i = 0; i < length;i++)
	//{
	//	trainingOutput[i] = new(double[width]);
	//	for (int j = 0; j < width; j++) trainingOutput[i][j] = 0;
	//}
	trainingOutput = data.getOutputs();



	//setError setup
	setError = new(double[length]);
	for (int i = 0; i < length; i++) setError[i] = 0;
}

//Gradients
//removing learning rate to use the constant instead.
void backPropagate::errorsAndGradients(inputLayer iL, hiddenLayer hL,  outputLayer oL, weights who, int index)
{
	for(int k = 0; k < oL.getNumOutput(); k++)
	{
		//think the error here is because i swapped things array with the order of the inputs
		setOutputErrorGradient(k, (oL.getNeuron(k)*(1-oL.getNeuron(k))*(trainingOutput[k][index] - oL.getNeuron(k))));
		
		//for all nodes in hidden layer and bias neuron
		//The less than or equal includes the bias neuron
		for (int j = 0; j <= hL.getNumHidden(); j++) 
		{				
			//calculate change in weight
			incrementDeltaHiddenOutput(j, k, (learningRate * hL.getNeuron(j) * getOutputErrorGradient(k)));
		}
	}

	//create deltas for all connections between input and hidden layer
	for (int j = 0; j < hL.getNumHidden(); j++)
	{
		//get error gradient for every hidden node
		//first i need to get the sum of the hidden neuron weights multiplied by each of the error gradients. 
		//so i can find the error in each hidden neuron.
		double weightedSum = 0;
		for( int k = 0; k < oL.getNumOutput(); k++ ) 
		{
			weightedSum += who.getWeight(j,k) * getOutputErrorGradient(k);
		}
		
		setHiddenErrorGradient(j, (hL.getNeuron(j) * ( 1 -  hL.getNeuron(j)) * weightedSum));

		//for all nodes in input layer and bias neuron
		//The less than or equal is what includes the bias neuron.
		for (int i = 0; i <= iL.getInputs(); i++)
		{
			//calculate change in weight 
			incrementDeltaInputHidden(i, j, (learningRate * iL.getNeuron(i) * getHiddenErrorGradient(j)));
		}
	}

	//going to include the setError code here just to see what happens, but i think itll work.
	for(int k = 0; k < oL.getNumOutput(); k++)
	{
		//setError[index]  += outputNeurons[k] - desiredOutputBits[index][k];
		//same issue here
		setError[index]  += oL.getNeuron(k) - trainingOutput[k][index];
	}
	setError[index] = setError[index]/oL.getNumOutput();
}

double backPropagate::getTrainingOutput(int i, int j)
{
	return trainingOutput[i][j];
}

//How to I change the 7 to not a variable!
void backPropagate::fillTrainingOutput(double data[][output])
{
	for (int i = 0; i < trainingDataLength; i++)
	{
		for (int j = 0; j < output; j++)
		{
			trainingOutput[i][j] = data[i][j];
		}
	}
}

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


