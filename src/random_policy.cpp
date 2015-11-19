
#include "random_policy.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int Random_Policy::rand_int(int lo, int hi) {
    return rand() % (hi - lo) + lo;
}

Random_Policy::Random_Policy(int n, int* values_in, int* weights_in, int random_seed) {
    this->values.assign(values_in, values_in + n);
    this->weights.assign(weights_in, weights_in + n);

    this->total_weight = 0;
    for (int weight : this->weights) {
        this->total_weight += weight;
    }

    srand(random_seed);
}

Random_Policy::~Random_Policy() {
    //nothing right now...
}

vector<int> Random_Policy::get_values() {
    return this->values;
}

vector<int> Random_Policy::get_weights() {
    return this->weights;
}

vector<double> Random_Policy::get_normalized_weights() {
    vector<double> normalized_weights;
    for (int weight : this->weights) {
        normalized_weights.push_back(weight * 1.0 / this->total_weight);
    }
    return normalized_weights;
}

void Random_Policy::get_random_position_and_value(int num_position, int &position_to_use, int &value) {
    position_to_use = this->rand_int(0, num_position);

    int weight_to_use = this->rand_int(0, this->total_weight);
    bool found_weight_flag = false;
    for (vector<int>::size_type i = 0; i < this->weights.size(); i++) {
        int weight = this->weights[i];
        if (weight_to_use < weight) {
            value = this->values[i];
            found_weight_flag = true;
            break;
        }
        weight_to_use -= weight;
    }
    assert (found_weight_flag);

    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
