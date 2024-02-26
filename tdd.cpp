#include "tdd.hpp"

// DO NOT MODIFY FUNCTIONS IN THIS FILE
// YOU MAY ADD YOUR OWN NEW FUNCTIONS HERE

void ASSERT_EQUAL(string actual, string expected, string testName) {
    if (actual != expected) {
        cout << "\tFAILED: " << testName << endl;
        cout << "\t\tactual: " << actual << endl;
        cout << "\t\texpected: " << expected << endl;
        return;
    } 
    cout << "\tPASSED: " << testName << endl; 
}

void ASSERT_EQUAL(int actual, int expected, string testName) {
    if (actual != expected) {
        cout << "\tFAILED: " << testName << endl;
        cout << "\t\tactual: " << actual << endl;
        cout << "\t\texpected: " << expected << endl;
        return;
    } 
    cout << "\tPASSED: " << testName << endl; 
}

void ASSERT_EQUAL(double actual, double expected, string testName) {
    if (abs(actual - expected) > 0.00001) {
        cout << "\tFAILED: " << testName << endl;
        cout << "\t\tactual: " << actual << endl;
        cout << "\t\texpected: " << expected << endl;
        return;
    } 
    cout << "\tPASSED: " << testName << endl; 
}

void ASSERT_EQUAL(NodeInfo actual, NodeInfo expected, string testName) {
    if (!(actual == expected)) {
        cout << "\tFAILED: " << testName << endl;
        cout << "\t\tactual: " << actual << endl;
        cout << "\t\texpected: " << expected << endl;
        return;
    } 
    cout << "\tPASSED: " << testName << endl; 
}

void ASSERT_EQUAL(NeuralNetwork actual, NeuralNetwork expected, string testName) {
    stringstream ssActual, ssExpected;
    ssActual << actual; ssExpected << expected;
    ASSERT_EQUAL(ssActual.str(), ssExpected.str(), testName);
}

void ASSERT_EQUAL(vector<double> actual, vector<double> expected, string testName) {
    if (actual != expected) {
        cout << "\tFAILED: " << testName << endl;
        cout << "\t\tactual: " << actual << endl;
        cout << "\t\texpected: " << expected << endl;
        return;
    } 
    cout << "\tPASSED: " << testName << endl; 
}

void ASSERT_EQUAL(Connection actual, Connection expected, string testName) {
    if (!(actual == expected)) {
        cout << "\tFAILED: " << testName << endl;
        cout << "\t\tactual: " << actual << endl;
        cout << "\t\texpected: " << expected << endl;
        return;
    } 
    cout << "\tPASSED: " << testName << endl; 
}
