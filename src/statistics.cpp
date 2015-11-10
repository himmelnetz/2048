
#include "statistics.h"

#include <math.h> //sqrt

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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
