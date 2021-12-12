# Neural-Network
This is a neural network designed to train on the MNIST data set for recognizing handwritten digits. It is run with an input layer of 784 inputs (28x28 images) and 2 hidden layers, each with 15 neurons. The output layer has 10 neurons, each of which represents the probability that the image is the digit 0-9, in order. The sigmoid activation function is used.

The data set used to train this is the MNIST data set, found here: http://yann.lecun.com/exdb/mnist/. The training data set (60,000 images) is used for everything; it is split 75/25% for training and testing, respectively.

# File Structure
The MNIST set is too large to include here on Github; as a result, the file structure to use the images and to train the data is shown here.
the 4_layers.txt file is the information of the trained network that can be imported to set the weights and biases
