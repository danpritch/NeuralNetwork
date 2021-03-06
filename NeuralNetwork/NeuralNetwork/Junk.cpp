void checkInputData(void);
void checkOutputs(void);
void checkErrorGradients(backPropagate bP);
void checkDelta(backPropagate bP);
void genRand(void);
void generateNetInputs(void);
void generateNetInputsBits(void);
void calculateDesiredOutput(void);
void passInputData(inputLayer iL, double** data, int index);
void displayOutput(void);
void displayOutputNeurons(outputLayer oL);
void clampOutputs(outputLayer oL);
void checkNet(inputLayer iL, hiddenLayer hL, outputLayer oL);
void writeCSV(void);
void modulus(void);

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

void clampOutputs(outputLayer oL)
{
	for (int i = 0; i < output; i++)
	{
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


void displayOutput(void)
{
	for(int i = 0; i < trainingDataLength; i++)
	{
		//cout << i << ". Average difference = " << setError[i] << endl;
	}		
}

void passInputData(inputLayer iL, double** data, int index)
{
	//set input neurons to input values
	for(int i = 0; i < input; i++)
	{
		//Had to swap the array dimensions around because of the screw up i made in the dataIO class
		iL.setNeuron(i, data[i][index]);
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

void checkInputData(void)
{
	for (int i = 0; i < inputDataLength; i++)
	{
		cout << "The value in netInputs is: " << int(netInputs[i]) << ". In bits this is: " 
			<< netInputsBits[i][2] << " " << netInputsBits[i][1] << " "<< netInputsBits[i][0] << endl; 
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

	ofstream fout;
	string fileName = "input_0.csv";

	for (int j = 0; j < input; j++)
	{
		fileName[6] = '0' + j;
		fout.open(fileName);
		if(fout.is_open())
		{
			cout << "File Opened successfully!!!. Writing data from array to file" << endl;

			for (int i = 0; i < inputDataLength; i++)
			{
				_itoa_s(netInputsBits[i][j], buffer, 10);
				fout << buffer << ',';
			}
			fout.close();
			cout << "Array data successfully saved into the file " << fileName << endl;
		}
		else //file could not be opened
		{
			cout << "File could not be opened." << endl;
		}
		cout << "Moving to next array..." << endl;
	}

	fileName = "output_0.csv";

	for (int j = 0; j < output; j++)
	{
		fileName[7] = '0' + j;
		fout.open(fileName);
		if(fout.is_open())
		{
			cout << "File Opened successfully!!!. Writing data from array to file" << endl;

			for (int i = 0; i < inputDataLength; i++)
			{
				_itoa_s(desiredOutputBits[i][j], buffer, 10);
				fout << buffer << ',';
			}
			fout.close();
			cout << "Array data successfully saved into the file " << fileName << endl;
		}
		else //file could not be opened
		{
			cout << "File could not be opened." << endl;
		}
		cout << "Moving to next array..." << endl;
	}

	cout << testclass.getInput(2,0) << testclass.getInput(1,0) << testclass.getInput(0,0) << " = " << testclass.getOutput(6,0) << testclass.getOutput(5,0) << testclass.getOutput(4,0) << testclass.getOutput(3,0) << testclass.getOutput(2,0) << testclass.getOutput(1,0) << testclass.getOutput(0,0) << endl;

