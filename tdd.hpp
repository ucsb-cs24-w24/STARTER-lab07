#ifndef TDD_HPP
#define TDD_HPP

// DO NOT MODIFY FUNCTIONS IN THIS FILE
// YOU MAY ADD YOUR OWN NEW FUNCTIONS HERE

#include "NeuralNetwork.hpp"
#include <iostream>
#include <string>
using namespace std;

void ASSERT_EQUAL(string actual, string expected, string testName);
void ASSERT_EQUAL(int actual, int expected, string testName);
void ASSERT_EQUAL(double actual, double expected, string testName);
void ASSERT_EQUAL(NodeInfo actual, NodeInfo expected, string testName);
void ASSERT_EQUAL(NeuralNetwork actual, NeuralNetwork expected, string testName);
void ASSERT_EQUAL(vector<double> actual, vector<double> expected, string testName);
void ASSERT_EQUAL(Connection actual, Connection expected, string testName);

#endif