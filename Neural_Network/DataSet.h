#pragma once
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include <vector>

class DataSet
{
	Matrix** data;
	Matrix** labels;
	int example_size, example_num;
public:
	DataSet(std::vector<int> network_arr, int example_num, char* data_file, char* label_file, int max_value);
	Matrix* getData(int index) const { return data[index]; }
	Matrix* getLabels(int index)const { return labels[index]; }
	void setData(char* data_file, char* label_file, int max_value);
};

