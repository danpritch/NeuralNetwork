#include <stdio.h>
#include <iostream>
#include <math.h>
#include "Header.h"

using namespace std;

//constants


//variables
double learningRate = 0.9;

//inputs
unsigned char netInputs[inputDataLength];
double netInputsBits[inputDataLength][input];
double desiredOutputBits[inputDataLength][output];
double setError[inputDataLength];

//neurons
double* inputNeurons;
double* hiddenNeurons;
double* outputNeurons;

//weights
double** wInputHidden;
double** wHiddenOutput;

//change to weights
double** deltaInputHidden;
double** deltaHiddenOutput;

//error gradients
double* hiddenErrorGradients;
double* outputErrorGradients;

//prototypes
void createLayers(int input, int hidden, int output);
void createWeights(int input, int hidden, int output);
void checkNet(void);
void genRand(void);
void initialiseWeights(void);
void generateNetInputs(void);
void checkInputData(void);
void generateNetInputsBits(void);
void passInputData(double data[][input], int index);
double activationFunction(double x);
void calculateHiddenLayer(void);
void calculateOutputLayer(void);
void calculateDesiredOutput(void);
void checkOutputs(void);
void calculateErrors(void);
void createDeltaLists(void);
void createErrorGradients(void);
void errorsAndGradients(int index);
void checkErrorGradients(void);
void checkDelta(void);
void updateWeights(void);
void initialiseNetwork(void);
void getErrors(int index);
void displayOutput(void);

int main(void)
{
	initialiseNetwork();
	for (int i = 0; i < trainingDataLength; i++)
	{
		passInputData(netInputsBits, i);	
		calculateHiddenLayer();
		calculateOutputLayer();
		errorsAndGradients(i);
		//getErrors(i);
		updateWeights();
	}
	checkNet();
	//displayOutput();
	cin.get();
	return(0);
}

void displayOutput(void)
{
	for(int i = 0; i < trainingDataLength; i++)
	{
		cout << i << ". Average difference = " << setError[i] << endl;
	}		
}


void getErrors(int index)
{
	setError[index] = 0;
	for(int k = 0; k < output; k++)
	{
		setError[index]  += desiredOutputBits[index][k] - outputNeurons[k];
	}
	setError[index] = setError[index]/output;
}


void initialiseNetwork(void)
{
	generateNetInputs();
	generateNetInputsBits();
	calculateDesiredOutput();
	createLayers(input, hidden, output);
	createWeights(input, hidden, output);
	createDeltaLists();
	createErrorGradients();
	initialiseWeights();
}

void createLayers(int input, int hidden, int output)
{
	inputNeurons = new( double[input + 1] );
	for ( int i=0; i < input; i++ ) inputNeurons[i] = 0;

	//create input bias neuron
	inputNeurons[input] = -1;

	hiddenNeurons = new( double[hidden + 1] );
	for ( int i=0; i < hidden; i++ ) hiddenNeurons[i] = 0;

	//create hidden bias neuron
	hiddenNeurons[hidden] = -1;

	outputNeurons = new( double[output] );
	for ( int i=0; i < output; i++ ) outputNeurons[i] = 0;
}

void createWeights(int input, int hidden, int output)
{
	//create weights between input and hidden layer

	//Create an array of arrays, 4 arrays containing 8 arrays each
	wInputHidden = new( double*[input + 1] );						
	for ( int i=0; i <= input; i++ ) 
	{
		wInputHidden[i] = new (double[hidden]);

		//Each element has initial value of 0
		for ( int j=0; j < hidden; j++ ) wInputHidden[i][j] = 0;		
	}

	//create weights between hidden and output layer
	wHiddenOutput = new( double*[hidden + 1] );
	for ( int i=0; i <= hidden; i++ ) 
	{
		wHiddenOutput[i] = new (double[output]);			
		for ( int j=0; j < output; j++ ) wHiddenOutput[i][j] = 0;		
	}
}

void checkNet(void)
{
	//Check input layer
	for(int i = 0; i < (input + 1); i++)
	{
		cout << "inputNeurons element: " << i << " has been created. Value = " << inputNeurons[i] << endl;
	}

	//Check hidden layer
	for(int i = 0; i < (hidden + 1); i++)
	{
		cout << "hiddenNeurons element: " << i << " has been created. Value = " << hiddenNeurons[i] << endl;
	}

	//Check output layer
	for(int i = 0; i < (output); i++)
	{
		cout << "outputNeurons element: " << i << " has been created. Value = " << outputNeurons[i] << endl;
	}

	//Check hidden input weights
	for(int i = 0; i < (input + 1); i++)
	{
		//There is no connection between the inputs and the hidden bias neuron, the last element in hidden is the bias neuron.
		for(int j = 0; j < (hidden); j++)
		{
			cout << "hidden input weights: (" << i << ", " << j << ") have a value of: " << wInputHidden[i][j] << endl;
		}
	}

	//Check output hidden weights
	for(int i = 0; i < (hidden + 1); i++)
	{
		for(int j = 0; j < (output); j++)
		{
			cout << "output hidden weights: (" << i << ", " << j << ") have a value of: " << wHiddenOutput[i][j] << endl;
		}
	}
}

void genRand(void)
{
	int value;
	for (int i = 0; i < 100; i++)
	{
		value = ((rand()%10) + 1);
		cout << "Random number is: " << value << endl;
	}
}

void initialiseWeights(void)
{
	double inputHiddenRand = 1/sqrt(double(input));
	double hiddenOutputRand = 1/sqrt(double(hidden));

	for(int i = 0; i <= input; i++)
	{		
		for(int j = 0; j < hidden; j++) 
		{
			//set weights to random values
			//wInputHidden[i][j] = double( ( ( (rand()%101) /100)*2*inputHiddenRand) - inputHiddenRand);
			wInputHidden[i][j] = ( ( (double)(rand()%100)+1)/100  * 2 * inputHiddenRand ) - inputHiddenRand;	
		}
	}

	for(int i = 0; i <= hidden; i++)
	{		
		for(int j = 0; j < output; j++) 
		{
			//set weights to random values
			wHiddenOutput[i][j] = ( ( (double)(rand()%100)+1)/100 * 2 * hiddenOutputRand ) - hiddenOutputRand;
		}
	}
}

void generateNetInputs(void)
{
	for (int i = 0; i < inputDataLength; i++)
	{
		netInputs[i] = rand() % 7 + 1;
	}
}

void generateNetInputsBits(void)
{
	for (int i = 0; i < inputDataLength; i++)
	{
		if(netInputs[i] & (1 << 0)) 
		{
			netInputsBits[i][0] = 1;
		}
		else
		{
			netInputsBits[i][0] = 0;
		}

		if(netInputs[i] & (1 << 1)) 
		{
			netInputsBits[i][1] = 1;
		}
		else
		{
			netInputsBits[i][1] = 0;
		}

		if(netInputs[i] & (1 << 2)) 
		{
			netInputsBits[i][2] = 1;
		}
		else
		{
			netInputsBits[i][2] = 0;
		}
	}
}

void checkInputData(void)
{
	for (int i = 0; i < inputDataLength; i++)
	{
		cout << "The value in netInputs is: " << int(netInputs[i]) << ". In bits this is: " 
			<< netInputsBits[i][2] << " " << netInputsBits[i][1] << " "<< netInputsBits[i][0] << endl; 
	}
}

//Well i clearly prepared well for this later on.
void passInputData(double data[][input], int index)
{
	//set input neurons to input values
	//for(int i = 0; i < nInput; i++) inputNeurons[i] = pattern[i];

	for(int i = 0; i < input; i++)
	{
		inputNeurons[i] = data[index][i];
	}
}

double activationFunction(double x)
{
	//sigmoid function
	return 1/(1+exp(-x));
}	

void calculateHiddenLayer(void)
{
	for(int j=0; j < hidden; j++)
	{
		//clear value
		hiddenNeurons[j] = 0;				
		
		//get weighted sum of pattern and bias neuron
		for( int i=0; i <= input; i++ ) hiddenNeurons[j] += inputNeurons[i] * wInputHidden[i][j];
		
		//set to result of sigmoid
		hiddenNeurons[j] = activationFunction( hiddenNeurons[j] );			
	}
}

void calculateOutputLayer(void)
{
		for(int k=0; k < output; k++)
	{
		//clear value
		outputNeurons[k] = 0;				
		
		//get weighted sum of pattern and bias neuron
		for( int j=0; j <= hidden; j++ ) outputNeurons[k] += hiddenNeurons[j] * wHiddenOutput[j][k];
		
		//set to result of sigmoid
		outputNeurons[k] = activationFunction( outputNeurons[k] );
	}
}

void calculateDesiredOutput(void)
{
	for(int i = 0; i < inputDataLength; i++)
	{
		if (netInputs[i] == 1)
		{
			desiredOutputBits[i][0] = 1;
		}
		else
		{
			desiredOutputBits[i][0] = 0;
		}

		if (netInputs[i] == 2)
		{
			desiredOutputBits[i][1] = 1;
		}
		else
		{
			desiredOutputBits[i][1] = 0;
		}
		if (netInputs[i] == 3)
		{
			desiredOutputBits[i][2] = 1;
		}
		else
		{
			desiredOutputBits[i][2] = 0;
		}
		if (netInputs[i] == 4)
		{
			desiredOutputBits[i][3] = 1;
		}
		else
		{
			desiredOutputBits[i][3] = 0;
		}
		if (netInputs[i] == 5)
		{
			desiredOutputBits[i][4] = 1;
		}
		else
		{
			desiredOutputBits[i][4] = 0;
		}
		if (netInputs[i] == 6)
		{
			desiredOutputBits[i][5] = 1;
		}
		else
		{
			desiredOutputBits[i][5] = 0;
		}
		if (netInputs[i] == 7)
		{
			desiredOutputBits[i][6] = 1;
		}
		else
		{
			desiredOutputBits[i][6] = 0;
		}
	}
}

void checkOutputs(void)
{
	for (int i = 0; i < inputDataLength; i++)
	{
		cout << "Input: " << int(netInputs[i]) << "     Outputs: " << desiredOutputBits[i][6] << desiredOutputBits[i][5] << desiredOutputBits[i][4] <<
			desiredOutputBits[i][3] << desiredOutputBits[i][2] << desiredOutputBits[i][1] << desiredOutputBits[i][0] << endl;
		
	}
}

void createDeltaLists(void)
{
	deltaInputHidden = new( double*[input + 1] );
	for ( int i=0; i <= input; i++ ) 
	{
		deltaInputHidden[i] = new (double[hidden]);
		for ( int j=0; j < hidden; j++ ) deltaInputHidden[i][j] = 0;		
	}

	deltaHiddenOutput = new( double*[hidden + 1] );
	for ( int i=0; i <= hidden; i++ ) 
	{
		deltaHiddenOutput[i] = new (double[output]);			
		for ( int j=0; j < output; j++ ) deltaHiddenOutput[i][j] = 0;		
	}
}

void createErrorGradients(void)
{
	hiddenErrorGradients = new( double[hidden + 1] );
	for ( int i=0; i <= hidden; i++ ) hiddenErrorGradients[i] = 0;
	
	outputErrorGradients = new( double[output + 1] );
	for ( int i=0; i <= output; i++ ) outputErrorGradients[i] = 0;
}

//This needs to be changed so that it can incremenent through the list of desired outputs.
//Which it has been.
void errorsAndGradients(int index)
{
	//Creates deltas for all connections between hidden and output layer
	for(int k = 0; k < output; k++)
	{
		outputErrorGradients[k] = outputNeurons[k]*(1-outputNeurons[k])*(desiredOutputBits[index][k] - outputNeurons[k]);

		//for all nodes in hidden layer and bias neuron
		//The less than or equal includes the bias neuron
		for (int j = 0; j <= hidden; j++) 
		{				
			//calculate change in weight
			deltaHiddenOutput[j][k] += learningRate * hiddenNeurons[j] * outputErrorGradients[k];
		}
	}

	//create deltas for all connections between input and hidden layer
	for (int j = 0; j < hidden; j++)
	{
		//get error gradient for every hidden node
		//first i need to get the sum of the hidden neuron weights multiplied by each of the error gradients. 
		//so i can find the error in each hidden neuron.
		double weightedSum = 0;
		for( int k = 0; k < output; k++ ) 
		{
			weightedSum += wHiddenOutput[j][k] * outputErrorGradients[k];
		}
		hiddenErrorGradients[j] = hiddenNeurons[j] * ( 1 - hiddenNeurons[j] ) * weightedSum;

		//for all nodes in input layer and bias neuron
		//The less than or equal is what includes the bias neuron.
		for (int i = 0; i <= input; i++)
		{
			//calculate change in weight 
			deltaInputHidden[i][j] += learningRate * inputNeurons[i] * hiddenErrorGradients[j]; 
		}
	}
}

void checkErrorGradients()
{
	for(int i = 0; i < output; i++)
	{
		cout << "Error gradient for output neuron " << i << " is: " << outputErrorGradients[i] << endl;
	}
}

void checkDelta(void)
{
	for(int i = 0; i < output; i++)
	{
		for(int j = 0; j < (hidden + 1); j++)
		{
			cout << "Deltas for HiddenOutput (" << i << ", " << j << ") is: " << deltaHiddenOutput[i][j] << endl;
		}
	}

	for(int i = 0; i < (input + 1); i++)
	{
		for(int j = 0; j < (hidden + 1); j++)
		{
			cout << "Deltas for InputHidden (" << i << ", " << j << ") is: " << deltaInputHidden[i][j] << endl;
		}
	}


}

void updateWeights(void)
{
	//input -> hidden weights
	//--------------------------------------------------------------------------------------------------------
	for (int i = 0; i <= input; i++)
	{
		for (int j = 0; j < hidden; j++) 
		{
			//update weight
			wInputHidden[i][j] += deltaInputHidden[i][j];	
			
			//clear delta only if using batch (previous delta is needed for momentum
			deltaInputHidden[i][j] = 0;				
		}
	}
	
	//hidden -> output weights
	//--------------------------------------------------------------------------------------------------------
	for (int j = 0; j <= hidden; j++)
	{
		for (int k = 0; k < output; k++) 
		{					
			//update weight
			wHiddenOutput[j][k] += deltaHiddenOutput[j][k];
			
			//clear delta only if using batch (previous delta is needed for momentum)
			deltaHiddenOutput[j][k] = 0;
		}
	}
}






