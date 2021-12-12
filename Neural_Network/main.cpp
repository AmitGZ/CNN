#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <vector>
#include "Network.h"
#include "Matrix.h"
#include "DataSet.h"
#include <vector>

/*
Neural network designed to train on the MNIST data set for recognizing handwritten digits.
It is run with an input layer of 784 inputs (28x28 images) and 2 hidden layers, each with 15 neurons.
The output layer has 10 neurons, each of which represents the probability that the image is the digit 0-9, in order.
The sigmoid activation function is used.
*/

using namespace std;

int main(int argc, char* argv[])
{
	int example_num = 10000, max_value = 1;
	vector<int> network_arr = { 28 * 28,16,16,10 };
	Network network(network_arr);
	char export_file[20] = "__layers.txt";
	export_file[0] = (char)(48+ network_arr.size());
	network.importData(export_file);

	char inputs[20] = "test_images.txt";
	char labels[20] = "test_labels.txt";
	DataSet *data_set = new DataSet(network_arr, example_num, inputs, labels, max_value);

	int batch_num = 500,epoch = example_num / batch_num;
	for (int i = 0; i < 90;i++)
	{
		network.trainNetwork(data_set, epoch, batch_num);
		network.exportData(export_file);
	}
	return 0;
}