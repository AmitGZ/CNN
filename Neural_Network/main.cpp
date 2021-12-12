#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cmath>
#include <vector>
#include "Network.h"
#include "Matrix.h"
#include "DataSet.h"
#include <vector>

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