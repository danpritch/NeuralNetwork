#pragma once

//To let the compiler know weights actually exists
class weights;

class inputLayer
{
private:
	int numInputs;
	double* inputNeurons;

public:
	inputLayer(int n);

	double getNeuron(int n);

	void setNeuron(int n, double value);

	int getInputs(void);
};

class hiddenLayer
{
private:
	int numHidden;
	double* hiddenNeurons;

public:
	hiddenLayer(int n);

	double getNeuron(int n);

	void setNeuron(int n, double value);

	int getNumHidden(void);

	void calculate(inputLayer iL, weights wil);

	double activationFunction(double x);
};

class outputLayer
{
private:
	int numOutput;
	double* outputNeurons;

public:
	outputLayer(int n);

	double getNeuron(int n);

	void setNeuron(int n, double value);

	int getNumOutput(void);

	void calculate(hiddenLayer hL, weights who);

	double activationFunction(double x);
};

class weights
{
private:
	int numLayerOne;
	int numLayerTwo;
	double** weightArray;

public:
	weights(inputLayer iL, hiddenLayer hL);

	weights(hiddenLayer hL, outputLayer oL);

	double getWeight(int layerOne , int layerTwo);

	void setWeight(int layerOne , int layerTwo, double value);

	void weights::incrementWeight(int layerOne , int layerTwo, double value);

	void initialiseWeights(int n);
};
