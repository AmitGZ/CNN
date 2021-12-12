#ifndef NETWORK_H
#define NETWORK_H
#include "Matrix.h"
#include <iostream>
#include <fstream>
#include "DataSet.h"
#include <vector>

class Network
{
private:
	std::vector<int> layers;
	Matrix** nodes, ** weights, ** biases;
	Matrix** weight_gradient, ** bias_gradient;
public:
	Network(std::vector<int> layers);
	~Network();
	void trainNetwork(DataSet* data_set, int epoch, int batch);
	float calculateCost(char* filename, int size);
	void forwardProp(Matrix* const inputs);
	void backProp(Matrix* const desired, int layer_index);
	void subtractGradient(int sample_num);
	Matrix* getOutput()const { return nodes[layers.size() - 1]; }
	void exportData(char* filename);
	void importData(char* filename);
};

#endif

