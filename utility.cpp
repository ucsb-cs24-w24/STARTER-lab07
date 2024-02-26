#include "utility.hpp"

// DO NOT MODIFY FUNCTIONS IN THIS FILE
// YOU MAY ADD YOUR OWN NEW FUNCTIONS HERE

double identity(double x) {
    return x;
}

double ReLU(double x) {
    if (x >= 0) {
        return x;
    }
    return 0;
}

double sigmoid(double x) {
    return (1 / (1 + exp(-1 * x)));
}

double step(double x) {
    return (x > 0) ? 1.0 : 0.0;
}

double sigmoid_prime(double x) {
    return sigmoid(x) * (1 - sigmoid(x));
}

double identity_prime(double x) {
    return 1;
}

FuncSig getActivationFunction(std::string identifier) {
    if (identifier == "ReLU") {
        return ReLU;
    } else if (identifier == "sigmoid") {
        return sigmoid;
    }
    return identity;
}

FuncSig getActivationDerivative(std::string identifier) {
    if (identifier == "ReLU") {
        return step;
    } else if (identifier == "sigmoid") {
        return sigmoid_prime;
    }
    return identity_prime;
}

std::string getActivationIdentifier(FuncSig f) {
    if (f == ReLU) {
        return "ReLU";
    } else if (f == sigmoid) {
        return "sigmoid";
    } else if (f == identity) {
        return "identity";
    } else if (f == step) {
        return "step";
    } else if (f == sigmoid_prime) {
        return "sigmoid_prime";
    }
    return "null";
}

double sample() {
    // Static variables for efficiency, so they are not re-created on each call
    static std::mt19937 gen(1);
    static std::normal_distribution<> dist(0, 1);

    // Generate and return a sample
    return dist(gen);
}

std::ostream& operator<<(std::ostream& out, std::vector<double> v) {
    for (int i = 0; i < v.size(); i++) {
        out << v.at(i) << " ";
    }
    return out;
}
