#include <stdio.h>
#include <iostream>
#include <math.h>
//#include "Header.h"
#include <fstream>
#include <vector>
#include <string>
#include <windows.h>
#include <time.h>

using namespace std;

//constants

const int input = 3;
const int hidden = 7;
const int output = 7;
const int inputDataLength = 5000;
const int trainingDataLength = 4950;


//variables
double learningRate = 0.9;

//inputs
unsigned char netInputs[inputDataLength];
double netInputsBits[inputDataLength][input];
double desiredOutputBits[inputDataLength][output];
double setError[inputDataLength];
char clampedOutput[output];

//neurons
//double* inputNeurons;
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

class inputLayer
{
private:
	int numInputs;
	double* inputNeurons;

public:
	inputLayer(int n)
	{
		numInputs = n;
		inputNeurons = new(double[(numInputs + 1)]);
		for (int i = 0; i < numInputs; i++){ inputNeurons[i] = 0;}
		inputNeurons[numInputs] = -1;
	}

	double getNeuron(int n)
	{
		return inputNeurons[n];
	}

	void setNeuron(int n, double value)
	{
		inputNeurons[n] = value;
	}

	int getInputs(void)
	{
		return numInputs;
	}	
};

//prototypes
void createLayers(int input, int hidden, int output);
void createWeights(int input, int hidden, int output);
void checkNet(inputLayer iL);
void genRand(void);
void initialiseWeights(void);
void generateNetInputs(void);
void checkInputData(void);
void generateNetInputsBits(void);
void passInputData(inputLayer iL, double data[][input], int index);
double activationFunction(double x);
void calculateHiddenLayer(inputLayer iL);
void calculateOutputLayer(void);
void calculateDesiredOutput(void);
void checkOutputs(void);
void calculateErrors(void);
void createDeltaLists(void);
void createErrorGradients(void);
void errorsAndGradients(int index);
void errorsAndGradients(inputLayer iL, int index);
void checkDelta(void);
void updateWeights(void);
void initialiseNetwork(void);
void getErrors(int index);
void displayOutput(void);
void writeCSV(void);
void modulus(void);
void trainNetwork(void);
void displayOutputNeurons(void);
void clampOutputs(void);




int main(void)
{
	char train = 'y';
	char train2 = 'y';
	char charIn[4];
	//initialiseNetwork();

	inputLayer testLayer(input);
	generateNetInputs();
	generateNetInputsBits();
	calculateDesiredOutput();
	createLayers(input, hidden, output);
	createWeights(input, hidden, output);
	createDeltaLists();
	createErrorGradients();
	initialiseWeights();

	while (train == 'y')
	{
		cout << "Would you like to test the untrained network? [y/n]: ";
		cin >> train;
		cin.ignore();
		if (train == 'y')
		{
			cout << "Please enter a 3-bit number (i.e. 101) : ";
			cin.getline(charIn,4);
			//cout << (int(charIn[0]) - 48) << (int(charIn[1]) - 48) << (int(charIn[2]) - 48) << endl;


			//Needs Changed!!!!!!
			//testLayer.setNeuron[2] = int(charIn[0]) - 48;
			//testLayer.setNeuron[1] = int(charIn[1]) - 48;
			//testLayer.setNeuron[0] = int(charIn[2]) - 48;
			testLayer.setNeuron(2, int(charIn[0]) - 48);
			testLayer.setNeuron(1, int(charIn[1]) - 48);
			testLayer.setNeuron(0, int(charIn[2]) - 48);
			

			calculateHiddenLayer(testLayer);
			calculateOutputLayer();
			clampOutputs();

			displayOutputNeurons();
		}
	}

	//trainNetwork();
	for (int i = 0; i < trainingDataLength; i++)
	{
		//Needs changed!!!! Or maybe it doesnt, passInputData can probably do it.
		passInputData(testLayer, netInputsBits, i);	
		calculateHiddenLayer(testLayer);
		calculateOutputLayer();
		//errorsAndGradients(i);
		errorsAndGradients(testLayer, i);
		getErrors(i);
		updateWeights();
	}

	while (train2 == 'y')
	{
		cout << "Would you like to test the trained network? [y/n]: ";
		cin >> train2;
		cin.ignore();
		if (train2 == 'y')
		{
			cout << "Please enter a 3-bit number (i.e. 101) : ";
			cin.getline(charIn,4);
			//cout << (int(charIn[0]) - 48) << (int(charIn[1]) - 48) << (int(charIn[2]) - 48) << endl;

			//Needs changed!!!!
			testLayer.setNeuron(2, int(charIn[0]) - 48);
			testLayer.setNeuron(1, int(charIn[1]) - 48);
			testLayer.setNeuron(0, int(charIn[2]) - 48);

			calculateHiddenLayer(testLayer);
			calculateOutputLayer();
			clampOutputs();

			displayOutputNeurons();
		}
	}

	//checkNet();
	//displayOutput();
	modulus();
	writeCSV();

	cout << "Press any key to exit";
	cin.get();
	return(0);
}

void clampOutputs(void)
{
	for (int i = 0; i < output; i++)
	{
		if(outputNeurons[i] > 0.9)
		{
			clampedOutput[i] = '1';
		}
		else if(outputNeurons[i] < 0.1)
		{
			clampedOutput[i] = '0';
		}
		else
		{
			clampedOutput[i] = 'n';
		}
	}
}

void displayOutputNeurons(void)
{
	cout << fixed << "Output '1' = " << outputNeurons[0] << "			Clamped output is: " << clampedOutput[0] << endl;
	cout << fixed << "Output '2' = " << outputNeurons[1] << "			Clamped output is: " << clampedOutput[1] << endl;
	cout << fixed << "Output '3' = " << outputNeurons[2] << "			Clamped output is: " << clampedOutput[2] << endl;
	cout << fixed << "Output '4' = " << outputNeurons[3] << "			Clamped output is: " << clampedOutput[3] << endl;
	cout << fixed << "Output '5' = " << outputNeurons[4] << "			Clamped output is: " << clampedOutput[4] << endl;
	cout << fixed << "Output '6' = " << outputNeurons[5] << "			Clamped output is: " << clampedOutput[5] << endl;
	cout << fixed << "Output '7' = " << outputNeurons[6] << "			Clamped output is: " << clampedOutput[6] << endl;
}

void trainNetwork(void)
{
	//for (int i = 0; i < trainingDataLength; i++)
	//{
	//	//Needs changed!!!! Or maybe it doesnt, passInputData can probably do it.
	//	passInputData(netInputsBits, i);	
	//	calculateHiddenLayer();
	//	calculateOutputLayer();
	//	errorsAndGradients(i);
	//	getErrors(i);
	//	updateWeights();
	//}
}

void modulus(void)
{
	for(int i = 0; i < trainingDataLength; i++)
	{
		if(setError[i] < 0)
		{
			setError[i] = setError[i]*-1;
		}
	}
}

void writeCSV(void)
{
	ofstream MyFile;
	MyFile.open("Ouput.csv"); //, ios::out | ios::ate | ios::app);

	for(int i = 0; i < trainingDataLength; i++)
	{
		MyFile << setError[i];
		MyFile << ',';
	}
	MyFile.close();
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
		setError[index]  += outputNeurons[k] - desiredOutputBits[index][k];
	}
	setError[index] = setError[index]/output;
}

void initialiseNetwork(void)
{
	//Needs changed!!!! Changed to create instance of inputLayer class
	inputLayer testLayer(input);
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

	//Needs changed!!!! Changed so that the repeated procedural sections have been commented out.

	//inputNeurons = new( double[input + 1] );
	//for ( int i=0; i < input; i++ ) inputNeurons[i] = 0;

	//create input bias neuron
	//inputNeurons[input] = -1;

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

	//Needs changed!!!! Was going to change the 'input' part to getNumInputs, but not necessary just now
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

void checkNet(inputLayer iL)
{
	//Check input layer

	//Needs changed!!!! Changed to add inputLayer Class as an argument.
	for(int i = 0; i < (input + 1); i++)
	{
		//cout << "inputNeurons element: " << i << " has been created. Value = " << inputNeurons[i] << endl;
		cout << "inputNeurons element: " << i << " has been created. Value = " << iL.getNeuron(i) << endl;
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
void passInputData(inputLayer iL, double data[][input], int index)
{
	//set input neurons to input values
	//for(int i = 0; i < nInput; i++) inputNeurons[i] = pattern[i];

	for(int i = 0; i < input; i++)
	{

		//Needs changed!!!! Changed 
		//iL.setNeuron[i] = data[index][i];
		iL.setNeuron(i, data[index][i]);
	}
}

double activationFunction(double x)
{
	//sigmoid function
	return 1/(1+exp(-x));
}	

void calculateHiddenLayer(inputLayer iL)
{
	for(int j=0; j < hidden; j++)
	{
		//clear value
		hiddenNeurons[j] = 0;				
		
		//get weighted sum of pattern and bias neuron

		//Needs changed!!!! Changed
		for( int i=0; i <= input; i++ ) hiddenNeurons[j] += iL.getNeuron(i) * wInputHidden[i][j];
		
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
void errorsAndGradients(inputLayer iL, int index)
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

			//Needs changed!!!! Changed
			deltaInputHidden[i][j] += learningRate * iL.getNeuron(i) * hiddenErrorGradients[j]; 
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






