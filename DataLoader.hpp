#ifndef DATALOADER_HPP
#define DATALOADER_HPP

// DO NOT TOUCH THIS FILE!!!!!
// If you are curious about this file's implementation, read on! :)
/*

This class was constructed because we wanted a convienant data management structure to interface with the nerual network.
A DataLoader object essentially holds a dataset and does some useful processing on the data before it is sent to the neural network.

For example:
- It contains pairs of data instances and their labels, in an object called DataInstance
- When initialized, it normalizes the data as to not skew the weights in a neural network. 
    - Imagine you have a data point, it holds binary data, like if a patient has prediabetes, this would hold 1 or 0
    - In the same dataset you might have another data point, like systolic blood pressure, this could be a double digit or triple digit number
    - These values need to be normalized so that one data point doesn't hold more weight than the other. 
    - Normalizing squeezes the data into a consistent range of values. 


To ensure a user of the neural network doesn't need to worry about these details, DataLoader is used. 
Notice that loadData calls normalizeData, this is what I mean. 

This approach is similar to what the pytorch python library does, which requires users to define a dataloader. 
*/

#include <string>
#include <fstream>
#include <vector>
#include <utility>
#include <iostream>
#include <sstream>
#include <cmath>



struct DataInstance {
    DataInstance(std::vector<double> features, int label = 0);
    std::vector<double> x;
    int y;

    friend std::ostream& operator<<(std::ostream& o, const DataInstance& d);
};

std::vector<double> calculateMean(const std::vector<DataInstance>& data);
std::vector<double> calculateStdDev(const std::vector<DataInstance>& data, const std::vector<double>& mean);

class DataLoader {
    public:
        DataLoader(std::string filename);
        DataLoader(std::istream& fin);

        std::vector<DataInstance> getData() const;

    private:

        std::vector<std::string> split(std::string s, std::string delimiter);
        void loadData(std::istream& in);
        std::vector<DataInstance> data;

        void normalizeDataSet();

};

#endif