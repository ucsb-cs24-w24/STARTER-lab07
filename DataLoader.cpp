#include "DataLoader.hpp"
using namespace std;

// DO NOT TOUCH THIS FILE!!!!!
// If you are curious about this file's implementation, read on! :)
/*

This class was constructed because we wanted a conveinant data management structure to interface with the nerual network.
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
*/

// Function to calculate the mean of each feature
std::vector<double> calculateMean(const std::vector<DataInstance>& data) {
    if (data.empty()) return {};

    std::vector<double> mean(data[0].x.size(), 0.0);
    for (const auto& instance : data) {
        for (size_t i = 0; i < instance.x.size(); ++i) {
            mean[i] += instance.x[i];
        }
    }
    for (double& m : mean) {
        m /= data.size();
    }
    return mean;
}

// Function to calculate the standard deviation of each feature
std::vector<double> calculateStdDev(const std::vector<DataInstance>& data, const std::vector<double>& mean) {
    if (data.empty()) return {};

    std::vector<double> std_dev(mean.size(), 0.0);
    for (const auto& instance : data) {
        for (size_t i = 0; i < instance.x.size(); ++i) {
            std_dev[i] += std::pow(instance.x[i] - mean[i], 2);
        }
    }
    for (double& sd : std_dev) {
        sd = std::sqrt(sd / data.size());
    }
    return std_dev;
}

DataInstance::DataInstance(vector<double> features, int label) {
    x = features;
    y = label;
}

ostream& operator<<(ostream& o, const DataInstance& d) {
    o << d.y << ": ";
    for (int i = 0; i < d.x.size(); i++) {
        o << d.x.at(i) << ", ";
    }
    o << endl;
    return o;
}

DataLoader::DataLoader(string filename) {
    ifstream fin(filename);

    if (fin.fail()) {
        cerr << "DataLoader failed to open file: " << filename << endl;
        exit(1);
    }

    loadData(fin);
    fin.close();
}

DataLoader::DataLoader(istream& in) {
    loadData(in);
}

std::vector<std::string> DataLoader::split(string s, string delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}

void DataLoader::loadData(istream& in) {

    std::string line;
    while (getline(in, line)) {

        std::vector<double> features;
        std::vector<string> tokens;
        int label;

        tokens = split(line, ",");
        for (int i = 0; i < tokens.size()-1; i++) {
            features.push_back(stod(tokens.at(i)));
        }
        label = stoi(tokens.at(tokens.size()-1));

        data.push_back(DataInstance(features, label));
    }

    normalizeDataSet();
}

vector<DataInstance> DataLoader::getData() const {
    return data;
}

void DataLoader::normalizeDataSet() {
    if (data.empty()) return;

    std::vector<double> mean = calculateMean(data);
    std::vector<double> std_dev = calculateStdDev(data, mean);

    for (auto& instance : data) {
        for (size_t i = 0; i < instance.x.size(); ++i) {
            instance.x[i] = (instance.x[i] - mean[i]) / std_dev[i];
        }
    }
}