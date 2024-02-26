#include "Graph.hpp"
using namespace std;

// NodeInfo -----------------------------------------------------------------------------------------------------------------------------------

NodeInfo::NodeInfo() {
    preActivationValue = 0;
    bias = 0;
    activationFunction = identity;
    activationDerivative = identity;
    activate();
    delta = 0;
}

NodeInfo::NodeInfo(string activationFunction, double value, double bias) {
    this->activationFunction = getActivationFunction(activationFunction);
    this->activationDerivative = getActivationDerivative(activationFunction);
    this->preActivationValue = value;
    this->activate();
    this->bias = bias;
    this->delta = 0;
}

double NodeInfo::activate() {
    postActivationValue = activationFunction(preActivationValue);
    return postActivationValue;
}

double NodeInfo::derive() {
    return activationDerivative(preActivationValue);
}

bool NodeInfo::operator==(const NodeInfo& other) {
    return (this->preActivationValue == other.preActivationValue) && 
           (this->postActivationValue == other.postActivationValue) && 
           (this->activationFunction == other.activationFunction) &&
           (this->bias == other.bias) &&
           (this->activationDerivative == other.activationDerivative);
}

std::ostream& operator<<(std::ostream& out, const NodeInfo& n) {
    out << "bias: " << n.bias << 
           " preActivationValue: " << n.preActivationValue << 
           " postActivationValue: " << n.postActivationValue << 
           " activationFunction: " << getActivationIdentifier(n.activationFunction) <<
           " activationDerivative: " << getActivationIdentifier(n.activationDerivative) << endl;
    return out;
}

// Connection -----------------------------------------------------------------------------------------------------------------------------------

Connection::Connection() {
    this->source = -1;
    this->dest = -1;
    this->weight = 0;
    this->delta = 0;
}

Connection::Connection(int source, int dest, double weight) {
    this->source = source;
    this->dest = dest;
    this->weight = weight;
    this->delta = 0;
}

bool Connection::operator<(const Connection& other) {
    return this->dest < other.dest;
}

bool Connection::operator==(const Connection& other) {
    return (this->dest == other.dest) && 
           (this->source == other.source) && 
           (this->weight == other.weight);
}

std::ostream& operator<<(std::ostream& out, const Connection& c) {
    out << "source: " << c.source << 
           " dest: " << c.dest << 
           " weight: " << c.weight << endl;
    return out;
}



// ------------------------ YOU DO NOT NEED TO MODIFY THE CODE ABOVE (but feel free to explore it) --------------------------------------




// Graph -----------------------------------------------------------------------------------------------------------------------------------

// STUDENT TODO: IMPLEMENT
void Graph::updateNode(int id, NodeInfo n) {
    if (true /* stub condition: change this to the correct condition*/) {
        cout << "Attempting to update node with id: " << id << " but node does not exist" << endl;
        return;
    }

    return; //stub
}

// STUDENT TODO: IMPLEMENT
NodeInfo* Graph::getNode(int id) const {
    return nullptr; //stub
}

// STUDENT TODO: IMPLEMENT
void Graph::updateConnection(int v, int u, double w) {
    if (true /* stub condition: change this to the correct condition*/) {
        cerr << "Attempting to update connection between " << v << " and " << u << " with weight " << w << " but " << v << " does not exist" << endl;
        exit(1);
    }
    if (true /* stub condition: change this to the correct condition*/) {
        cerr << "Attempting to update connection between " << v << " and " << u << " with weight " << w << " but " << u << " does not exist" << endl;
        exit(1);
    }
    
    return; //stub
}

// STUDENT TODO: IMPLEMENT
void Graph::clear() {
    return; //stub
}




// ------------------------ YOU DO NOT NEED TO MODIFY THE REMAINING CODE (but please feel free to explore it!) --------------------------------------





Graph::Graph() {
    this->size = 0;
}

Graph::Graph(int size) {
    resize(size);
}

Graph::Graph(const Graph& other) {
    this->size = other.size;
    this->adjacencyList = other.adjacencyList;
    for (int i = 0; i < other.nodes.size(); i++) {
        nodes.push_back(new NodeInfo(*other.nodes.at(i)));
    }
}

Graph& Graph::operator=(const Graph& other) {
    if (this == &other) {
        return *this;
    }
    clear();
    this->size = other.size;
    this->adjacencyList = other.adjacencyList;
    for (int i = 0; i < other.nodes.size(); i++) {
        nodes.push_back(new NodeInfo(*other.nodes.at(i)));
    }
    return *this;
}

Graph::~Graph() {
    clear();
}

AdjList& Graph::getAdjacencyList() {
    return adjacencyList;
}

ostream& operator<<(ostream& out, const Graph& g) {
    // output as dot format for graph visualization
    out << "digraph G {" << endl;
    for (int i = 0; i < g.adjacencyList.size(); i++) {
        for (auto j = g.adjacencyList.at(i).begin(); j != g.adjacencyList.at(i).end(); j++) {
            out << "\t" << i << " -> " << j->second.dest << "[label=\"" << j->second.weight << "\"]" << endl;
        }
    }
    out << "}" << endl;
    for (int i = 0; i < g.nodes.size(); i++) {
        string end = "\n";
        if (i == g.nodes.size()-1) {
            end = "";
        }
        out << "node " << i 
            << ": (z=" << g.nodes.at(i)->preActivationValue << "\t"\
            << ", a=" << g.nodes.at(i)->postActivationValue << "\t"
            << ", bias=" << g.nodes.at(i)->bias << "\t"
            << ", activation=" << getActivationIdentifier(g.nodes.at(i)->activationFunction) << ")" << end;
    }

    // take the console output starting from digraph G {...} (to the last bracket) and paste it here: 
    // https://dreampuf.github.io/GraphvizOnline/#digraph%20G%20%7B%0A%0A%20%20subgraph%20cluster_0%20%7B%0A%20%20%20%20style%3Dfilled%3B%0A%20%20%20%20color%3Dlightgrey%3B%0A%20%20%20%20node%20%5Bstyle%3Dfilled%2Ccolor%3Dwhite%5D%3B%0A%20%20%20%20a0%20-%3E%20a1%20-%3E%20a2%20-%3E%20a3%3B%0A%20%20%20%20label%20%3D%20%22process%20%231%22%3B%0A%20%20%7D%0A%0A%20%20subgraph%20cluster_1%20%7B%0A%20%20%20%20node%20%5Bstyle%3Dfilled%5D%3B%0A%20%20%20%20b0%20-%3E%20b1%20-%3E%20b2%20-%3E%20b3%3B%0A%20%20%20%20label%20%3D%20%22process%20%232%22%3B%0A%20%20%20%20color%3Dblue%0A%20%20%7D%0A%20%20start%20-%3E%20a0%3B%0A%20%20start%20-%3E%20b0%3B%0A%20%20a1%20-%3E%20b3%3B%0A%20%20b2%20-%3E%20a3%3B%0A%20%20a3%20-%3E%20a0%3B%0A%20%20a3%20-%3E%20end%3B%0A%20%20b3%20-%3E%20end%3B%0A%0A%20%20start%20%5Bshape%3DMdiamond%5D%3B%0A%20%20end%20%5Bshape%3DMsquare%5D%3B%0A%7D
    return out;
}

void Graph::resize(int size) {
    this->size = size;
    adjacencyList.resize(size);
    for (int i = 0; i < size; i++) {
        nodes.push_back(nullptr);
    }
}

vector<NodeInfo*> Graph::getNodes() const {
    return nodes;
}
