#ifndef UTILITY_HPP
#define UTILITY_HPP

// DO NOT MODIFY FUNCTIONS IN THIS FILE
// YOU MAY ADD YOUR OWN NEW FUNCTIONS HERE

#include <cmath>
#include <string>
#include <random>
#include <iostream>
typedef double(* FuncSig)(double param);

// Utility Functions

// identity applies no activation to x. 
double identity(double x);

// ReLU returns x if x is greater than 0, and 0 otherwise
// it is commonly used as an activation function in modern neural net architectures.
double ReLU(double x);

// sigmoid is defined as 1 / (1+e^(-x))
// it is another commonly used activation function in modern neural net architectures.
double sigmoid(double x);

// step is the derivative of ReLU. It returns 1 for positive values, and 0 otherwise.
// it is needed to compute the derivative for gradient descent.
double step(double x);

// derivative of sigmoid
double sigmoid_prime(double x);

double identity_prime(double x);

FuncSig getActivationFunction(std::string identifier);

FuncSig getActivationDerivative(std::string identifier);

std::string getActivationIdentifier(FuncSig f);

double sample();

std::ostream& operator<<(std::ostream& out, std::vector<double> v);

#endif