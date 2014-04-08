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

//----------------------------------------------------Main function-----------------------------------------------

int main(void)
{
	//Initialise
	inputLayer testLayer(input);
	hiddenLayer hLayer(hidden);
	outputLayer oLayer(output);
	weights wInputHidden(testLayer, hLayer);
	weights wHiddenOutput(hLayer, oLayer);
	backPropagate backProp(testLayer.getInputs(), hLayer.getNumHidden(), oLayer.getNumOutput());
	dataIO testclass(3,7);		
	backProp.initialise(inputDataLength,output,testclass);
	
	//Test untrained network
	testclass.UI(testLayer, wInputHidden, hLayer, wHiddenOutput, oLayer);
	
	//Train network	
	cout << "Training... " << endl;
	backProp.errorsAndGradients(testLayer, hLayer, oLayer, wHiddenOutput, wInputHidden, testclass);		
	
	//Test trained network
	testclass.UI(testLayer, wInputHidden, hLayer, wHiddenOutput, oLayer);

	//Exit program
	cout << "Press any key to exit";
	cin.get();
	return(0);
}