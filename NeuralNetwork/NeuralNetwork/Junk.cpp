void checkInputData(void);
void checkOutputs(void);
void checkErrorGradients(backPropagate bP);
void checkDelta(backPropagate bP);

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

