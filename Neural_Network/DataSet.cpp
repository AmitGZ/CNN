#define _CRT_SECURE_NO_WARNINGS
#include "DataSet.h"

DataSet::DataSet(std::vector<int> network_arr, int example_num, char* data_file, char* label_file, int max_value)
{
	this->example_size = network_arr.at(0);
	this->example_num = example_num;
	data = new Matrix * [example_num];
	labels = new Matrix * [example_num];
	for (int i = 0; i < example_num;i++)
	{
		data[i] = new Matrix(network_arr.at(0), 1);
		labels[i] = new Matrix(network_arr.at(network_arr.size()-1), 1);
	}
	setData(data_file, label_file,max_value);
}

void DataSet::setData(char* data_file, char* label_file, int max_value)
{
	float in_tmp;
	std::ifstream input(data_file);
	int out_tmp;
	std::ifstream output(label_file);
	for (int i = 0; i < example_num;i++)
	{
		output >> out_tmp;
		labels[i]->setData(out_tmp, 0, 1);
		for (int j = 0; j < example_size;j++)
		{
			input >> in_tmp;
			data[i]->setData(j, 0,in_tmp/ max_value);
		}
	}
}