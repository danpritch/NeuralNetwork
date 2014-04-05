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