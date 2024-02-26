#include "NeuralNetwork.hpp"
#include "tdd.hpp"
#include <vector>
#include <iostream>
#include <unordered_set>
using namespace std;

void usage();

void runTest(int testNum);
void runAll();
void test_evaluate();
void test_contribute();
void test_accuracy();
void test_structure();
void test_algorithm();

int main(int argc, char* argv[]) {
    int testNum = 0;
    if (argc < 2) {
        usage();
    } else {
        testNum = stoi(argv[1]);
    }

    runTest(testNum);
    
    return 0;
}

void usage() {
    cout << "to run a specific test: ./test_neuralnet [testNum]" << endl;
    cout << "or" << endl;
    cout << "to run all tests: ./test_neuralnet" << endl;
}

void runTest(int testNum) {
    switch (testNum) {
        case 0:
            runAll();
            break;
        case 1:
            test_evaluate();
            break;
        case 2:
            test_contribute();
            break;
        case 3:
            test_accuracy();
            break;
        case 4:
            test_structure();
            break;
        case 5:
            test_algorithm();
            break;
    }
    return;
}

void runAll() {
    test_evaluate();
    test_contribute();
    test_accuracy();
    test_structure();
    test_algorithm();
}

void test_evaluate() {
    cout << "test_evaluate: " << endl;
    NeuralNetwork nn("./models/neuralnet_example1.init");
    nn.eval();
    vector<double> input; input.push_back(0.3); input.push_back(-0.2);
    DataInstance di(input, 0);
    vector<double> prediction = nn.predict(di);

    ASSERT_EQUAL(prediction.at(0), 0.428639, "test_evaluate");
}

void test_contribute() {
    cout << "test_contribute" << endl;
    NeuralNetwork nn("./models/neuralnet_example2.init");
    double biasBefore = nn.getNode(0)->bias;
    double weightBefore = nn.getAdjacencyList().at(0).begin()->second.weight;

    vector<double> input; input.push_back(0.3); input.push_back(-0.2);
    nn.train();
    nn.predict(input);
    nn.update();
    double biasAfter = nn.getNode(0)->bias;
    double weightAfter = nn.getAdjacencyList().at(0).begin()->second.weight;

    double biasDiffExpected = 0;
    double weightDiffExpected = -0.05999962;

    ASSERT_EQUAL(biasAfter - biasBefore, biasDiffExpected, "test_contribute: bias");
    ASSERT_EQUAL(weightAfter - weightBefore, weightDiffExpected, "test_contribute: weight");
}

void test_accuracy() {
    cout << "test_accuracy" << endl;
    NeuralNetwork nn("./models/diabetes.init");
    nn.setLearningRate(0.001);

    // initialize a dataloader, similar to pytorch
    DataLoader dl("./data/diabetes_train.csv");

    vector<double> output;
    int numEpochs = 3;

    // put the neural network in train mode, similar to pytorch
    nn.train();

    for (int i = 0; i < numEpochs; i++) {
        for (int j = 0; j < dl.getData().size(); j++) {
            DataInstance di = dl.getData().at(j);
            output = nn.predict(di);
        }
        nn.update();
    }

    double expectedAccuracy = 0.91675;
    ASSERT_EQUAL(nn.assess("./data/diabetes_test.csv"), expectedAccuracy, "test_accuracy: diabetes");
}

void test_structure() {
    cout << "test_structure" << endl;
    NeuralNetwork nn("./models/diabetes1.init");
    ifstream fin("./test_output/test_neuralnet.txt");
    stringstream ssExpected;
    stringstream ssActual;
    ssExpected << fin.rdbuf();
    ssActual << nn;
    ASSERT_EQUAL(ssActual.str(), ssExpected.str(), "test_structure");
}

void test_algorithm() {
    cout << "test_algorithm" << endl;
    NeuralNetwork nn(6);
    NeuralNetwork nn_2("./models/neuralnet_example4.init");

    NodeInfo n0("ReLU", 0, -0.2);
    NodeInfo n1("ReLU", 0, 0.2);
    NodeInfo n2("identity", 0, 0);
    NodeInfo n3("sigmoid", 0, 0.98);
    NodeInfo n4("ReLU", 0, 0.11);
    NodeInfo n5("identity", 0, 0);

    nn.updateNode(0, n0);
    nn.updateNode(1, n1);
    nn.updateNode(2, n2);
    nn.updateNode(3, n3);
    nn.updateNode(4, n4);
    nn.updateNode(5, n5);

    nn.updateConnection(2, 1, 0.1);
    nn.updateConnection(2, 4, 0.2);
    nn.updateConnection(2, 0, 0.3);
    nn.updateConnection(5, 1, 0.4);
    nn.updateConnection(5, 4, 0.5);
    nn.updateConnection(5, 0, 0.6);
    nn.updateConnection(1, 3, 0.7);
    nn.updateConnection(4, 3, 0.8);
    nn.updateConnection(0, 3, 0.9);

    nn.setInputNodeIds({2, 5});
    nn.setOutputNodeIds({3});

    nn.eval();
    nn_2.eval();

    vector<double> input; input.push_back(0.3); input.push_back(-0.2);
    DataInstance di(input, 0);
    double p1 = nn.predict(di).at(0);
    double p2 = nn_2.predict(di).at(0);

    ASSERT_EQUAL(p1, 0.757863, "test_algorithm:1");
    ASSERT_EQUAL(p2, 0.757863, "test_algorithm:2");
}