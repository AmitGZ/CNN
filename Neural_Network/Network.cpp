#define _CRT_SECURE_NO_WARNINGS
#include "Network.h"


Network::Network(std::vector<int> layers)
{
	this->layers = layers;

	biases = new Matrix * [layers.size()];
	bias_gradient = new Matrix * [layers.size()];
	nodes = new Matrix * [layers.size()];
	weights = new Matrix * [layers.size()];
	weight_gradient = new Matrix * [layers.size()];

	for (int i = 1; i < layers.size();i++)
	{
		biases[i] = new Matrix(layers[i], 1);
		biases[i]->setRandom();
		bias_gradient[i] = new Matrix(layers[i], 1);
		nodes[i] = new Matrix(layers[i], 1);
		weights[i] = new Matrix(layers[i], layers[i - 1]);
		weights[i]->setRandom();
		weight_gradient[i] = new Matrix(layers[i], layers[i - 1]);
	}
}

void Network::forwardProp(Matrix* const inputs)
{
	nodes[0] = inputs;			   //setting first layer to inputs
	for (int i = 1; i < layers.size();i++)
		*nodes[i] = ((*weights[i]) * (*nodes[i - 1]) + *biases[i]).getSigmoid();
}

void Network::backProp(Matrix* const desired, int layer_index)
{
	layer_index--;
	if (layer_index < 1)
		return;
	Matrix z = ((*nodes[layer_index]).getInverseSigmoid()).getSigmoidDerivative();
	Matrix new_desired(layers[layer_index - 1], 1);

	for (int j = 0; j < layers[layer_index]; j++)
	{
		bias_gradient[layer_index]->addData(j, 0, (*desired).getData(j, 0) * z.getData(j, 0));
		for (int k = 0; k < layers[layer_index - 1]; k++)
		{
			weight_gradient[layer_index]->addData(j, k, (*nodes[layer_index - 1]).getData(k, 0) * (*desired).getData(j, 0) * z.getData(j, 0));
			new_desired.addData(k, 0, weights[layer_index]->getData(j, k) * (*desired).getData(j, 0) * z.getData(j, 0));
		}
	}
	backProp(&(new_desired), layer_index);
}

void Network::subtractGradient(int sample_num)
{
	for (int i = 1; i < layers.size();i++)
	{
		*weights[i] = (*weights[i]) + ((*weight_gradient[i]) / (-sample_num));
		*biases[i] = (*biases[i]) + ((*bias_gradient[i]) / (-sample_num));

		weight_gradient[i]->zero();
		bias_gradient[i]->zero();
	}
}

void Network::trainNetwork(DataSet *data_set, int epoch, int batch)
{
	int yes = 0, no = 0, index = 0;
	for (int i = 0; i < epoch;i++)
	{
		for (int j = 0; j < batch;j++, index++)
		{	
			forwardProp(data_set->getData(index));
			(data_set->getLabels(index)->getData(getOutput()->getMax(), 0)) ? yes++ : no++; // add to success ratio
			backProp(&(((*nodes[layers.size()-1]) - *(data_set->getLabels(index))) * 2), layers.size());
		}
		subtractGradient(batch);

		if (!(i%(epoch/100+1))) // for debugging output
			std::cout << "progress: " << i * 100 / epoch <<"%"<< std::endl
			<< "accuracy: "<< 100*((float)(yes)/ (float)(no+yes))<<"%"<< std::endl;
	}
}

void Network::exportData(char* filename)
{
	std::ofstream output;
	output.open(filename); // opens the file
	if (!output) { // file couldn't be opened
		std::cout << "File Error" << std::endl;
		exit(1);
	}

	for (int i = 1; i < layers.size();i++)
	{
		for (int j = 0;j < layers[i];j++)
			output << biases[i]->getData(j, 0) << std::endl;

		for (int j = 0;j < layers[i];j++)
			for (int k = 0;k < layers[i - 1];k++)
				output << weights[i]->getData(j, k) << std::endl;
	}
	output.close();
}

void Network::importData(char* filename)
{
	std::ifstream input;
	input.open(filename);
	if (!input) {
		std::cout << "File Error" << std::endl;
		return;
	}

	float tmp = 0;
	for (int i = 1; i < layers.size();i++)
	{
		for (int j = 0;j < layers[i];j++)
		{
			input >> tmp;
			biases[i]->setData(j, 0, tmp);
		}

		for (int j = 0;j < layers[i];j++)
			for (int k = 0;k < layers[i - 1];k++)
			{
				input >> tmp;
				weights[i]->setData(j, k, tmp);
			}
	}
	input.close();
}

Network::~Network()
{
	for (int i = 1;i < layers.size();i++)
	{
		delete biases[i];
		delete bias_gradient[i];
		delete nodes[i];
		delete weights[i];
		delete weight_gradient[i];
	}
	delete& biases[0];
	delete& bias_gradient[0];
	delete& nodes[0];
	delete& weights[0];
	delete& weight_gradient[0];
}