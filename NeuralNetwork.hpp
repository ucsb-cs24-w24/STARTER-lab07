#ifndef NEURAL_NET_HPP
#define NEURAL_NET_HPP

// includes
#include "Graph.hpp"
#include "DataLoader.hpp"

// class declarations

// The NeuralNetwork class inherits from the Graph class, because a NeuralNetwork is a more specific type of Graph!
// You have not learned about inherited classes yet, but for now, treat the NeuralNetwork class as if it were also of type Graph.
class NeuralNetwork : public Graph {

    public:

        // use these constructors for building your neural network manually through code
        NeuralNetwork();
        NeuralNetwork(int size);

        // use these constructors for loading a premade architecture from a file
        NeuralNetwork(std::string filename);
        NeuralNetwork(std::istream& in);


        // TODO: getters / setters
        // Put the neural network in "eval" mode. In "eval" mode, the neural network will not accumulate gradients.
        void eval();
        // Put the neural network in "train" mode. In "train" mode, the neural network will accumulated gradients.
        void train();
        // sets the learning rate of the neural network: how impactful each gradient contribution is at each step.
        void setLearningRate(double lr);
        // contains set of node ids which correspond to input nodes
        void setInputNodeIds(std::vector<int> inputNodeIds);
        // contains a set of node ids which correspond to output nodes
        void setOutputNodeIds(std::vector<int> outputNodeIds);
        // gets the id's of every input node. 
        std::vector<int> getInputNodeIds() const;
        // gets the id's of every output node.
        std::vector<int> getOutputNodeIds() const;


        // TODO: Neural Network Implementations
        // Flow data instance into the neural network and compute the predicted value. 
        std::vector<double> predict(DataInstance instance);
        // Apply accumumated gradients to every weight and every bias
        bool update();



        // Other useful methods...
        // Calculates the neural networks accuracy given a dataset in the form of a DataLoader object.
        double assess(DataLoader dl);
        // Calculates the nerual networks accuracy given a dataset stored in the given filename. 
        double assess(std::string filename);
        // Saves the model structure, weights, and biases into the given filename. 
        void saveModel(std::string filename);
        friend std::ostream& operator<<(std::ostream& out, const NeuralNetwork& nn);

    private:

        // TODO: given the neural nets prediction and the ground truth label, it accumulates gradients for weights and biases. 
        // each contribution is accumulated in a variable called delta, which resides in every node (for the bias) and every connection (for the weight)
        bool contribute(double y, double p);
        // a helper function to contribute. 
        double contribute(int nodeId, const double& y, const double& p);

         // VERY helpful visit methods for predict and contribute
        // visits the node during evaluation
        void visitPredictNode(int vId);
        // visits v's neighbor during evaluation
        void visitPredictNeighbor(Connection c);
        // visits the node during contribution
        void visitContributeNode(int vId, double& outgoingContribution);
        // visits the connection during contribution
        void visitContributeNeighbor(Connection& c, double& incomingContribution, double& outgoingContribution);


        // other helpful and members...
        // indicates the number of training instances seen before the neural network updates
        double batchSize;
        // eval or train mode. evaluating = true indicates eval mode. 
        bool evaluating;
        // controls the impact of each gradient contribution. 
        double learningRate;
        // each index of layers holds a vector which contains the id's of every node in that layer. 
        std::vector<std::vector<int> > layers;
        // keeps track of which contributions have already been made.
        std::unordered_map<int, double> contributions;
        // contains ids of input nodes
        std::vector<int> inputNodeIds;
        // contains ids of output nodes
        std::vector<int> outputNodeIds;


        // other helpful methods...
        // loads neural network structure from the input file stream
        void loadNetwork(std::istream& in);
        // refreshes node values for the next computation.
        void flush();

        // since NeuralNetwork inherits from Graph, you can imagine all of the graph members here as well...

};

#endif