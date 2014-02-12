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
};