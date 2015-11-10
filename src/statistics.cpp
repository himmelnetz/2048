
#include "statistics.h"

#include <math.h> //sqrt
#include <algorithm> //sort

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Summary_Statistics::Summary_Statistics() {
    //nothing right now...
}

Summary_Statistics::~Summary_Statistics() {
    //nothing right now...
}

void Summary_Statistics::add_datum(double datum) {
    this->data.push_back(datum);
}

void Summary_Statistics::add_data(double* data, int n) {
    for (int i = 0; i < n; i++) {
        double datum = data[i];
        this->add_datum(datum);
    }
}

void Summary_Statistics::add_data(vector<double> data) {
    for (double datum : data) {
        this->add_datum(datum);
    }
}

int Summary_Statistics::get_n() {
    return this->data.size();
}

double Summary_Statistics::get_mean() {
    long double sum = 0.0;
    for (double datum : this->data) {
        sum += datum;
    }
    int n = this->get_n();
    return sum / n;
}

double Summary_Statistics::get_stdev() {
    long double sum = 0.0;
    long double sum_squared = 0.0;
    for (double datum : this->data) {
        sum += datum;
        sum_squared += datum * datum;
    }
    int n = this->get_n();
    long double variance = (sum_squared - (sum * sum) / n) / (n - 1);
    return sqrt(variance);
}

double Summary_Statistics::get_skew() {
    double mean = this->get_mean();
    long double sum_cube_diff = 0.0;
    for (double datum : this->data) {
        sum_cube_diff += pow(datum - mean, 3);
    }
    int n = this->get_n();
    double stdev = this->get_stdev();
    return (sum_cube_diff / n) / pow(stdev, 3);
}

double Summary_Statistics::get_kurtosis() {
    double mean = this->get_mean();
    long double sum_fourth_diff = 0.0;
    for (double datum : this->data) {
        sum_fourth_diff += pow(datum - mean, 4);
    }
    int n = this->get_n();
    double stdev = this->get_stdev();
    return (sum_fourth_diff / n) / pow(stdev, 4) - 3;
}

double Summary_Statistics::get_median() {
    std::sort(this->data.begin(), this->data.end());
    int n = this->data.size();
    return n % 2 == 1
        ? this->data[n / 2]
        : (this->data[n / 2] + this->data[n / 2 - 1]) / 2.0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
