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

void backPropagate::errorsAndGradients(inputLayer iL, hiddenLayer hL,  outputLayer oL, weights who, weights wil, dataIO data)
{
	for(int index = 0; index < data.getInputDataLengths(0); index++)
	{
		/*In this section I update the input neurons with the next iteration of input data given by the index.*/
		for(int i = 0; i < iL.getInputs(); i++)
		{
			iL.setNeuron(i, data.getInput(i, index));
		}

		/*This section is the forward pass, where the value in the neurons in each layer is calculated from the previous layers value and weight connection. */
		hL.calculate(iL, wil);
		oL.calculate(hL, who);
	
		/*This section is the beginning of the back propogation phase, first the gradients are calculated, then the associated deltas.
		  I start by iterating through each output neuron.*/
		for(int k = 0; k < oL.getNumOutput(); k++)
		{
			/*I need to remember that training[k][index] was changed from training[index][k] due to the way the input data array is structured.
			  The gradient is given by: (derivative of the signmoid function) multiplied by the (difference between the actual and expected value of the output).
			  At this point, the neuron output has already been multiplied by the sigmoid function so I don't need to do it here.*/
			outputErrorGradients[k] = oL.getNeuron(k)*(1-oL.getNeuron(k))*(trainingOutput[k][index] - oL.getNeuron(k));
		
			/*Then for each output neuron, I iterate through each connection to a hidden neuron, including the bias neuron.*/
			for (int j = 0; j <= hL.getNumHidden(); j++) 
			{
				/*This equation is consistant with Jonathons notes, for each gradient, multiply be each hidden neuron to find the delta.
				  I don't believe the increment is needed here unless I was using momentum, but might as well keep it in.*/
				deltaHiddenOutput[j][k] += learningRate * hL.getNeuron(j) * outputErrorGradients[k];
			}
		}

		/*This section finds the deltas between the input and the hidden layers.*/
		for (int j = 0; j < hL.getNumHidden(); j++)
		{
			//get error gradient for every hidden node
			//first i need to get the sum of the hidden neuron weights multiplied by each of the error gradients. 
			//so i can find the error in each hidden neuron.

			/*It's not as simple to find the errors in the hidden layer to calculate the gradients, as we don't know what the error actually is.
			  We calculate the error by multiply the error gradients of the output neurons, by their weight connection to the hidden neuron in question,
			  and then summing it for each connection. This give us the total error in the hidden neuron. */
			double weightedSum = 0;
			for( int k = 0; k < oL.getNumOutput(); k++ ) 
			{
				weightedSum += who.getWeight(j,k) * outputErrorGradients[k];
			}
		
			/*After the error in the hidden layer is found the procedure for calculating the deltas is the same*/
			hiddenErrorGradients[j] = hL.getNeuron(j) * ( 1 -  hL.getNeuron(j)) * weightedSum;

			for (int i = 0; i <= iL.getInputs(); i++)
			{
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

		wil.update(deltaInputHidden, deltaHiddenOutput);
		who.update(deltaInputHidden, deltaHiddenOutput);
	}
}

double** backPropagate::getDeltaHiddenOutputs(void)
{
	return deltaHiddenOutput;
}

double** backPropagate::getDeltaInputHiddens(void)
{
	return deltaInputHidden;
}


//Annoying functions that take up room in the viewer

double backPropagate::getTrainingOutput(int i, int j)
{
	return trainingOutput[i][j];
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


