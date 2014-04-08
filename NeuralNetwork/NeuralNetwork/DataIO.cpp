#include "DataIO.h"

dataIO::dataIO(int x, int y)
{
	numberOfInputs = x;
	numberOfOutputs = y;
	initialise();
	readInputs();
	readOutputs();
	checkDataLenghts();
}

void dataIO::initialise(void)
{
	inputSet = new(double*[MAX_INPUTS]);
	for (int i = 0; i < MAX_INPUTS; i++)
	{
		inputSet[i] = new(double[MAX_INPUT_LENGTH]);
		for (int j = 0; j < MAX_INPUT_LENGTH; j++) inputSet[i][j] = 0;
	}

	outputSet = new(double*[MAX_OUTPUTS]);
	for (int i = 0; i < MAX_OUTPUTS; i++)
	{
		outputSet[i] = new(double[MAX_OUTPUT_LENGTH]);
		for (int j = 0; j < MAX_OUTPUT_LENGTH; j++) outputSet[i][j] = 0;
	}
	
	inputDataLengths = new(int[MAX_INPUTS]);
	for (int i = 0; i < MAX_INPUTS; i++)
	{
		inputDataLengths[i] = 0;
	}

	outputDataLengths = new(int[MAX_OUTPUTS]);
	for (int i = 0; i < MAX_OUTPUTS; i++)
	{
		outputDataLengths[i] = 0;
	}
}

void dataIO::readInputs(void)
{
	//Variables
	//int x = 0;	
	char data[10];
	std::string fileName = "input_0.csv";
	std::ifstream infile;
	char fileNumber;

	for (int i = 0; i < numberOfInputs; i++)
	{
		fileNumber = '0' + i;
		fileName[6] = fileNumber;
		infile.open(fileName);		
		if(infile.is_open())
		{
			std::cout << fileName << " opened successfully!!!. Writing data from array to file" << std::endl;

			//Data read in
			for (int j = 0; !infile.eof(); j++)
			{
				infile.getline(data,10,',');
				inputSet[i][j] = atoi(data);
				inputDataLengths[i] = j;
			}
			infile.close();
			std::cout << fileName << " closed successfully!" << std::endl;
		}
		else //file could not be opened
		{
			std::cout << "File could not be opened." << std::endl;
		}
	}
	//return x;
}

void dataIO::readOutputs(void)
{
	char data[10];
	std::string fileName = "output_0.csv";
	std::ifstream infile;
	char fileNumber;

	for (int i = 0; i < numberOfOutputs; i++)
	{
		fileNumber = '0' + i;
		fileName[7] = fileNumber;
		infile.open(fileName);		
		if(infile.is_open())
		{
			std::cout << fileName << " opened successfully!!!. Writing data from array to file" << std::endl;

			//Data read in
			for (int j = 0; !infile.eof(); j++)
			{
				infile.getline(data,10,',');
				outputSet[i][j] = atoi(data);
				outputDataLengths[i] = j;
			}
			infile.close();
			std::cout << fileName << " closed successfully!" << std::endl;
		}
		else //file could not be opened
		{
			std::cout << "File could not be opened." << std::endl;
		}
	}
	//return x;
}

double** dataIO::getInputs(void)
{
	//Make a smaller array from the bigger array, by doing
	//double array[inputs][inputlength]
	//then fill it with the data from the big array
	//return inputs;
	return inputSet;
}

double** dataIO::getOutputs(void)
{
	//this is what im going to output to the trainer
	//may need to make the outputSet array smaller so it does not exceed the expect dimensions in trainer.
	return outputSet;
}

double dataIO::getInput(int x, int y)
{
	return inputSet[x][y];
}

double dataIO::getOutput(int x, int y)
{
	return outputSet[x][y];
}

int dataIO::getInputDataLengths(int x)
{
	return inputDataLengths[x];
}

void dataIO::checkDataLenghts(void)
{
	//Check input lengths
	bool checkInput = true;
	for (int i = 0; i < (numberOfInputs - 1); i++)
	{
		if (inputDataLengths[i] != inputDataLengths[(i + 1)])
		{
			checkInput = false;
		}
	}
	if(checkInput)
	{
		std::cout << "All input lengths are the same!" << std::endl;
	}
	else
	{
		std::cout << "All input lengths are NOT the same!" << std::endl;
	}

	//Check output lengths
	bool checkOutput = true;
	for (int i = 0; i < (numberOfOutputs - 1); i++)
	{
		if (outputDataLengths[i] != outputDataLengths[(i + 1)])
		{
			checkOutput = false;
		}
	}
	if(checkOutput)
	{
		std::cout << "All output lengths are the same!" << std::endl;
	}
	else
	{
		std::cout << "All output lengths are NOT the same!" << std::endl;
	}
}

