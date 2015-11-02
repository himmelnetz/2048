
#include "2048.h"

#include <stdlib.h> //rand, srand

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

int Random_Policy::rand_int(int lo, int hi) {
    return rand() % (hi - lo) + lo;
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

State_2048::State_2048(Random_Policy* random_policy) {
    this->random_policy = random_policy;
}

void State_2048::reset_to_blank_state() {
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            this->board[row][col] = 0;
        }
    }
    this->score = 0;
}

bool State_2048::add_random_cell() {
    int num_empty_cells = 0;
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            if (this->board[row][col] == 0) {
                num_empty_cells++;
            }
        }
    }
    if (num_empty_cells == 0) {
        return false;
    }
    
    int position_to_use, value;
    this->random_policy->get_random_position_and_value(num_empty_cells, position_to_use, value);

    bool added_new_cell_flag = false;
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            if (this->board[row][col] == 0) {
                if (position_to_use == 0) {
                    this->board[row][col] = value;
                    added_new_cell_flag = true;
                    break;
                } else {
                    position_to_use--;
                }
            }
        }
        if (added_new_cell_flag) {break;}
    }
    assert (added_new_cell_flag);

    return true;
}

State_2048::~State_2048() {
    //nothing right now...
}

void State_2048::reset_to_initial_state() {
    this->reset_to_blank_state();
    // TODO this is currently hard coded to initially spawn two random cells; make this a config
    this->add_random_cell();
    this->add_random_cell();
}

int State_2048::get_cell_value(int row, int col) {
    assert(row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS);
    return this->board[row][col];
}

Game_2048::Game_2048(Player_2048* player, Random_Policy* random_policy)
        : player{player}, cur_state(random_policy) {
    //nothing right now
}

Game_2048::~Game_2048() {
    //nothing right now...
}

void Game_2048::play_game() {
    //um, this is where the game would go, but nothing right now...
}
