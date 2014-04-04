#include <stdio.h>
#include <iostream>
#include <math.h>
//#include "Header.h"
#include "Network.h"
#include "Trainer.h"
#include <fstream>
#include <string>

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

//prototypes
void checkNet(inputLayer iL, hiddenLayer hL, outputLayer oL);
void genRand(void);
void generateNetInputs(void);
void checkInputData(void);
void generateNetInputsBits(void);
void passInputData(inputLayer iL, double data[][input], int index);
void calculateDesiredOutput(void);
void checkOutputs(void);
void calculateErrors(void);
void checkErrorGradients(backPropagate bP);
void errorsAndGradients(inputLayer iL, hiddenLayer hL,  outputLayer oL, weights who, backPropagate bP, int index);
void checkDelta(backPropagate bP);
void updateWeights(weights wil, weights who, backPropagate bP);
void getErrors(outputLayer oL, int index);
void displayOutput(void);
void writeCSV(void);
void modulus(void);
void displayOutputNeurons(outputLayer oL);
void clampOutputs(outputLayer oL);

//----------------------------------------------------Main function-----------------------------------------------

int main(void)
{
	char train = 'y';
	char train2 = 'y';
	char charIn[4];
	//initialiseNetwork();

	inputLayer testLayer(input);
	hiddenLayer hLayer(hidden);
	outputLayer oLayer(output);

	backPropagate backProp(testLayer, hLayer, oLayer);
	
	weights wInputHidden(testLayer, hLayer);
	weights wHiddenOutput(hLayer, oLayer);
	
	

	generateNetInputs();
	generateNetInputsBits();
	calculateDesiredOutput();

	while (train == 'y')
	{
		cout << "Would you like to test the untrained network? [y/n]: ";
		cin >> train;
		cin.ignore();
		if (train == 'y')
		{
			cout << "Please enter a 3-bit number (i.e. 101) : ";
			cin.getline(charIn,4);

			testLayer.setNeuron(2, int(charIn[0]) - 48);
			testLayer.setNeuron(1, int(charIn[1]) - 48);
			testLayer.setNeuron(0, int(charIn[2]) - 48);
			
			//calculateHiddenLayer(testLayer, hLayer, wInputHidden);
			hLayer.calculate(testLayer, wInputHidden);
			oLayer.calculate(hLayer, wHiddenOutput);
			//calculateOutputLayer(hLayer, oLayer, wHiddenOutput);
			clampOutputs(oLayer);
			displayOutputNeurons(oLayer);
		}
	}

	//trainNetwork();
	for (int i = 0; i < trainingDataLength; i++)
	{
		passInputData(testLayer, netInputsBits, i);	
		//calculateHiddenLayer(testLayer, hLayer, wInputHidden);
		//calculateOutputLayer(hLayer, oLayer, wHiddenOutput);
		hLayer.calculate(testLayer, wInputHidden);
		oLayer.calculate(hLayer, wHiddenOutput);

		errorsAndGradients(testLayer, hLayer, oLayer, wHiddenOutput, backProp, i);
		getErrors(oLayer, i);
		//updateWeights(wInputHidden, wHiddenOutput, backProp);
		wInputHidden.update(backProp);
		wHiddenOutput.update(backProp);
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

			testLayer.setNeuron(2, int(charIn[0]) - 48);
			testLayer.setNeuron(1, int(charIn[1]) - 48);
			testLayer.setNeuron(0, int(charIn[2]) - 48);

			//calculateHiddenLayer(testLayer, hLayer, wInputHidden);
			//calculateOutputLayer(hLayer, oLayer, wHiddenOutput);
			hLayer.calculate(testLayer, wInputHidden);
			oLayer.calculate(hLayer, wHiddenOutput);

			clampOutputs(oLayer);

			displayOutputNeurons(oLayer);
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

void clampOutputs(outputLayer oL)
{
	for (int i = 0; i < output; i++)
	{

		//if(outputNeurons[i] > 0.9)
		if(oL.getNeuron(i) > 0.9)
		{
			clampedOutput[i] = '1';
		}
		else if(oL.getNeuron(i) < 0.1)
		{
			clampedOutput[i] = '0';
		}
		else
		{
			clampedOutput[i] = '?';
		}
	}
}

//This function can also be made alot smaller with a loop. Do this later though.
void displayOutputNeurons(outputLayer oL)
{
	cout << fixed << "Output '1' = " << oL.getNeuron(0) << "			Clamped output is: " << clampedOutput[0] << endl;
	cout << fixed << "Output '2' = " << oL.getNeuron(1) << "			Clamped output is: " << clampedOutput[1] << endl;
	cout << fixed << "Output '3' = " << oL.getNeuron(2) << "			Clamped output is: " << clampedOutput[2] << endl;
	cout << fixed << "Output '4' = " << oL.getNeuron(3) << "			Clamped output is: " << clampedOutput[3] << endl;
	cout << fixed << "Output '5' = " << oL.getNeuron(4) << "			Clamped output is: " << clampedOutput[4] << endl;
	cout << fixed << "Output '6' = " << oL.getNeuron(5) << "			Clamped output is: " << clampedOutput[5] << endl;
	cout << fixed << "Output '7' = " << oL.getNeuron(6) << "			Clamped output is: " << clampedOutput[6] << endl;
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

void getErrors(outputLayer oL, int index)
{
	setError[index] = 0;
	for(int k = 0; k < output; k++)
	{
		//setError[index]  += outputNeurons[k] - desiredOutputBits[index][k];
		setError[index]  += oL.getNeuron(k) - desiredOutputBits[index][k];
	}
	setError[index] = setError[index]/output;
}

void checkNet(inputLayer iL, hiddenLayer hL, outputLayer oL, weights wil, weights who)
{
	//Check input layer

	//Needs changed!!!! Changed to add inputLayer Class as an argument.
	for(int i = 0; i < (input + 1); i++)
	{
		cout << "inputNeurons element: " << i << " has been created. Value = " << iL.getNeuron(i) << endl;
	}

	//Check hidden layer
	for(int i = 0; i < (hidden + 1); i++)
	{
		cout << "hiddenNeurons element: " << i << " has been created. Value = " << hL.getNeuron(i) << endl;
	}

	//Check output layer
	for(int i = 0; i < (output); i++)
	{
		cout << "outputNeurons element: " << i << " has been created. Value = " << oL.getNeuron(i) << endl;
	}

	//Check hidden input weights
	for(int i = 0; i < (input + 1); i++)
	{
		//There is no connection between the inputs and the hidden bias neuron, the last element in hidden is the bias neuron.
		for(int j = 0; j < (hidden); j++)
		{
			cout << "hidden input weights: (" << i << ", " << j << ") have a value of: " << wil.getWeight(i,j) << endl;
		}
	}

	//Check output hidden weights
	for(int i = 0; i < (hidden + 1); i++)
	{
		for(int j = 0; j < (output); j++)
		{
			cout << "output hidden weights: (" << i << ", " << j << ") have a value of: " << who.getWeight(i,j) << endl;
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

void passInputData(inputLayer iL, double data[][input], int index)
{
	//set input neurons to input values
	for(int i = 0; i < input; i++)
	{
		iL.setNeuron(i, data[index][i]);
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

void errorsAndGradients(inputLayer iL, hiddenLayer hL,  outputLayer oL, weights who, backPropagate bP, int index)
{
	for(int k = 0; k < output; k++)
	{
		bP.setOutputErrorGradient(k, (oL.getNeuron(k)*(1-oL.getNeuron(k))*(desiredOutputBits[index][k] - oL.getNeuron(k))));
		
		//for all nodes in hidden layer and bias neuron
		//The less than or equal includes the bias neuron
		for (int j = 0; j <= hidden; j++) 
		{				
			//calculate change in weight
			bP.incrementDeltaHiddenOutput(j, k, (learningRate * hL.getNeuron(j) * bP.getOutputErrorGradient(k)));
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
			weightedSum += who.getWeight(j,k) * bP.getOutputErrorGradient(k);
		}
		
		bP.setHiddenErrorGradient(j, (hL.getNeuron(j) * ( 1 -  hL.getNeuron(j)) * weightedSum));

		//for all nodes in input layer and bias neuron
		//The less than or equal is what includes the bias neuron.
		for (int i = 0; i <= input; i++)
		{
			//calculate change in weight 
			bP.incrementDeltaInputHidden(i, j, (learningRate * iL.getNeuron(i) * bP.getHiddenErrorGradient(j)));
		}
	}
}

//arguments and prototype
void checkErrorGradients(backPropagate bP)
{
	for(int i = 0; i < output; i++)
	{
		//cout << "Error gradient for output neuron " << i << " is: " << outputErrorGradients[i] << endl;
		cout << "Error gradient for output neuron " << i << " is: " << bP.getOutputErrorGradient(i) << endl;
	}
}

void checkDelta(backPropagate bP)
{
	for(int i = 0; i < output; i++)
	{
		for(int j = 0; j < (hidden + 1); j++)
		{
			//cout << "Deltas for HiddenOutput (" << i << ", " << j << ") is: " << deltaHiddenOutput[i][j] << endl;
			cout << "Deltas for HiddenOutput (" << i << ", " << j << ") is: " << bP.getDeltaHiddenOutput(i,j) << endl;
		}
	}

	for(int i = 0; i < (input + 1); i++)
	{
		for(int j = 0; j < (hidden + 1); j++)
		{
			//cout << "Deltas for InputHidden (" << i << ", " << j << ") is: " << deltaInputHidden[i][j] << endl;
			cout << "Deltas for InputHidden (" << i << ", " << j << ") is: " << bP.getDeltaInputHidden(i,j) << endl;
		}
	}


}

//All commented out now
void updateWeights(weights wil, weights who, backPropagate bP)
{
	////input -> hidden weights
	////--------------------------------------------------------------------------------------------------------
	//for (int i = 0; i <= input; i++)
	//{
	//	for (int j = 0; j < hidden; j++) 
	//	{
	//		//update weight
	//		//wil.setWeight(i,j,(wil.getWeight(i,j) + deltaInputHidden[i][j]));
	//		wil.setWeight(i,j,(wil.getWeight(i,j) + bP.getDeltaInputHidden(i,j)));

	//		//clear delta only if using batch (previous delta is needed for momentum
	//		//deltaInputHidden[i][j] = 0;
	//		bP.setDeltaInputHidden(i,j,0);
	//	}
	//}
	//
	////hidden -> output weights
	////--------------------------------------------------------------------------------------------------------
	//for (int j = 0; j <= hidden; j++)
	//{
	//	for (int k = 0; k < output; k++) 
	//	{					
	//		//update weight
	//		//who.incrementWeight(j,k, deltaHiddenOutput[j][k]);
	//		who.incrementWeight(j,k, bP.getDeltaHiddenOutput(j,k));
	//		
	//		//clear delta only if using batch (previous delta is needed for momentum)
	//		//deltaHiddenOutput[j][k] = 0;
	//		bP.setDeltaHiddenOutput(j,k,0);
	//	}
	//}
}






