#include <iostream>
#include "NeuralNetwork.hpp"
#include "utility.hpp"
#include "DataLoader.hpp"
using namespace std;

void testTrain(string networkFile, string trainFile, string testFile);

int main(int argc, char* argv[]) {

    // once you get the basic setters and getters and graph methods complete, you should be able
    // to play around with this file and explore the neural net. 
    // diabetes1.init contains a pretrained model. 
    
    testTrain("./data/diabetes1.init", "./data/diabetes_train.csv", "./data/diabetes_test.csv");

    return 0;
}


// sample train code
void testTrain(string networkFile, string trainFile, string testFile) {
    NeuralNetwork nn(networkFile);
    nn.setLearningRate(0.001);

    // initialize a dataloader, similar to pytorch
    DataLoader dl(trainFile);

    vector<double> output;
    int numEpochs = 3;

    // put the neural network in train mode, similar to pytorch
    nn.train();

    for (int i = 0; i < numEpochs; i++) {
        // cout << nn << endl;
        for (size_t j = 0; j < dl.getData().size(); j++) {
            DataInstance di = dl.getData().at(j);
            output = nn.predict(di);
        }
        cout << "epoch: " << i << " accuracy: " << nn.assess(testFile) << endl;
        nn.update();
    }

    // cout << nn << endl;
    cout << "accuracy: " << nn.assess(testFile) << endl;
}