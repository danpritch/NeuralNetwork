#pragma once
#include <stdio.h>
#include <iostream>
#include <math.h>
#include "Network.h"
#include "Trainer.h"
#include "DataIO.h"
#include <fstream>
#include <string>
#include "Constants.h"
using namespace std;

//variables
char clampedOutput[output];

//prototypes
void checkNet(inputLayer iL, hiddenLayer hL, outputLayer oL);
void passInputData(inputLayer iL, double** data, int index);
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

	inputLayer testLayer(input);
	hiddenLayer hLayer(hidden);
	outputLayer oLayer(output);
	weights wInputHidden(testLayer, hLayer);
	weights wHiddenOutput(hLayer, oLayer);
	backPropagate backProp(testLayer.getInputs(), hLayer.getNumHidden(), oLayer.getNumOutput());
	dataIO testclass(3,7);	
	
	backProp.initialise(inputDataLength,output,testclass);

	//backkProp fillTrainingOutput is no longer needed and can be removed from the class.
	//backProp.fillTrainingOutput(desiredOutputBits);

	//First simulation using user input.
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
			hLayer.calculate(testLayer, wInputHidden);
			oLayer.calculate(hLayer, wHiddenOutput);
			clampOutputs(oLayer);
			displayOutputNeurons(oLayer);
		}
	}

	////trainNetwork();
	//This entire section need rewritten, and the back propogation class probably needs completely changed.
	for (int i = 0; i < trainingDataLength; i++)
	{
		passInputData(testLayer, testclass.getInputs(), i);	

		//This will be condensed down to one line after the layer classes are sorted out
		hLayer.calculate(testLayer, wInputHidden);
		oLayer.calculate(hLayer, wHiddenOutput);

		backProp.errorsAndGradients(testLayer, hLayer, oLayer, wHiddenOutput, i);
		
		wInputHidden.update(backProp);
		wHiddenOutput.update(backProp);
	}

	//Second simulation using user input
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
			hLayer.calculate(testLayer, wInputHidden);
			oLayer.calculate(hLayer, wHiddenOutput);
			clampOutputs(oLayer);
			displayOutputNeurons(oLayer);
		}
	}

	////checkNet();
	////displayOutput();
	////modulus();
	////writeCSV();

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
	//for(int i = 0; i < trainingDataLength; i++)
	//{
	//	if(setError[i] < 0)
	//	{
	//		setError[i] = setError[i]*-1;
	//	}
	//}
}

//Write CSV will no longer work as setError is contained in the trainer class
void writeCSV(void)
{
	//ofstream MyFile;
	//MyFile.open("Ouput.csv"); //, ios::out | ios::ate | ios::app);

	//for(int i = 0; i < trainingDataLength; i++)
	//{
	//	MyFile << setError[i];
	//	MyFile << ',';
	//}
	//MyFile.close();
}

void displayOutput(void)
{
	for(int i = 0; i < trainingDataLength; i++)
	{
		//cout << i << ". Average difference = " << setError[i] << endl;
	}		
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

//I think if I change this function so that the parameter takes a pointer I can pass the dataIO.getInputs to it.
//Need to changed the prototype as well
//void passInputData(inputLayer iL, int data[][input], int index)
void passInputData(inputLayer iL, double** data, int index)
{
	//set input neurons to input values
	for(int i = 0; i < input; i++)
	{
		//Had to swap the array dimensions around because of the screw up i made in the dataIO class
		iL.setNeuron(i, data[i][index]);
	}
}




