
#include "2048.h"

#include <stdlib.h> //rand, srand

void convert_move_to_drow_dcol(Move_2048 move, int &drow, int &dcol) {
    switch (move) {
        case Move_2048::UP:
            drow = -1;
            dcol = 0;
            return;
        case Move_2048::DOWN:
            drow = 1;
            dcol = 0;
            return;
        case Move_2048::LEFT:
            drow = 0;
            dcol = -1;
            return;
        case Move_2048::RIGHT:
            drow = 0;
            dcol = 1;
            return;
        default:
            //should never get here...
            assert (false);
            return;
    }
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

void State_2048::copy_state(State_2048* other_state) {
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            this->board[row][col] = other_state->board[row][col];
        }
    }
    this->score = other_state->score;
}

bool State_2048::combine_cells_row(int row, int dir, bool dont_modify) {
    assert (dir == 1 || dir == -1);
    assert (row >= 0 && row < NUM_ROWS);
    int start = (dir == 1 ? 0 : NUM_COLS - 1);
    int end = (dir == 1 ? NUM_COLS : -1);
    int prev_col = -1;
    bool something_happened = false;
    for (int col = start; col != end; col += dir) {
        if (this->board[row][col] != 0) {
            //something is in this cell
            if (prev_col == -1 || this->board[row][col] != this->board[row][prev_col]) {
                //dont combine
                prev_col = col;
            } else {
                //combine
                if (dont_modify) {return true;}
                this->board[row][prev_col] *= 2;
                this->board[row][col] = 0;
                this->score += this->board[row][prev_col];
                prev_col = -1;
                something_happened = true;
            }
        }
    }
    return something_happened;
}

bool State_2048::combine_cells_col(int col, int dir, bool dont_modify) {
    assert (dir == 1 || dir == -1);
    assert (col >= 0 && col < NUM_COLS);
    int start = (dir == 1 ? 0 : NUM_ROWS - 1);
    int end = (dir == 1 ? NUM_ROWS : -1);
    int prev_row = -1;
    bool something_happened = false;
    for (int row = start; row != end; row += dir) {
        if (this->board[row][col] != 0) {
            //something is in this cell
            if (prev_row == -1 || this->board[row][col] != this->board[prev_row][col]) {
                //dont combine
                prev_row = col;
            } else {
                //combine
                if (dont_modify) {return true;}
                this->board[prev_row][col] *= 2;
                this->board[row][col] = 0;
                this->score += this->board[prev_row][col];
                prev_row = -1;
                something_happened = true;
            }
        }
    }
    return something_happened;
}

bool State_2048::combine_cells(int drow, int dcol, bool dont_modify) {
    assert (drow * dcol == 0 && drow + dcol != 0);
    bool something_happened = false;
    if (drow == 0) {
        for (int row = 0; row < NUM_ROWS; row++) {
            something_happened = this->combine_cells_row(row, dcol, dont_modify) || something_happened;
        }
    } else {
        for (int col = 0; col < NUM_COLS; col++) {
            something_happened = this->combine_cells_col(col, drow, dont_modify) || something_happened;
        }
    }
    return something_happened;
}

bool State_2048::cascade_row(int row, int dir, bool dont_modify) {
    assert (dir == 1 || dir == -1);
    int start = (dir == 1 ? 0 : NUM_COLS - 1);
    int end = (dir == 1 ? NUM_COLS : -1);
    int cur_col = start;
    bool something_happened = false;
    for (int col = start; col != end; col += dir) {
        if (this->board[row][col] != 0) {
            if (col != cur_col) {
                if (dont_modify) {return true;}
                this->board[row][cur_col] = this->board[row][col];
                this->board[row][col] = 0;
                something_happened = true;
            }
            cur_col += dir;
        }
    }
    return something_happened;
}

bool State_2048::cascade_col(int col, int dir, bool dont_modify) {
    assert (dir == 1 || dir == -1);
    int start = (dir == 1 ? 0 : NUM_ROWS - 1);
    int end = (dir == 1 ? NUM_ROWS : -1);
    int cur_row = start;
    bool something_happened = false;
    for (int row = start; row != end; row += dir) {
        if (this->board[row][col] != 0) {
            if (row != cur_row) {
                if (dont_modify) {return true;}
                this->board[cur_row][col] = this->board[row][col];
                this->board[row][col] = 0;
                something_happened = true;
            }
            cur_row += dir;
        }
    }
    return something_happened;
}

bool State_2048::cascade(int drow, int dcol, bool dont_modify) {
    assert (drow * dcol == 0 && drow + dcol != 0);
    bool something_happened = false;
    if (drow == 0) {
        for (int row = 0; row < NUM_ROWS; row++) {
            something_happened = this->cascade_row(row, dcol, dont_modify) || something_happened;
        }
    } else {
        for (int col = 0; col < NUM_COLS; col++) {
            something_happened = this->cascade_col(col, drow, dont_modify) || something_happened;
        }
    }
    return something_happened;
}

bool State_2048::try_make_move(Move_2048 move, bool dont_modify) {
    int drow, dcol;
    convert_move_to_drow_dcol(move, drow, dcol);
    bool combine_happened = this->combine_cells(drow, dcol, dont_modify);
    bool cascade_happened = this->cascade(drow, dcol, dont_modify);
    return combine_happened || cascade_happened;
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

int State_2048::get_cell_value(int row, int col) {
    assert (row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS);
    return this->board[row][col];
}

int State_2048::get_legal_moves(Move_2048* legal_moves) {
    int num_legal_moves = 0;
    for (int i = 0; i < NUM_MOVES; i++) {
        Move_2048 cur_move = ALL_MOVES[i];
        if (this->try_make_move(cur_move, false)) {
            legal_moves[num_legal_moves] = cur_move;
            num_legal_moves++;
        }
    }
    return num_legal_moves;
}

State_2048 State_2048::make_move(Move_2048 move) {
    State_2048 new_state(this->random_policy);
    new_state.copy_state(this);
    bool something_happened = new_state.try_make_move(move, true);
    assert (something_happened);
    return new_state;
}

Game_2048::Game_2048(Player_2048* player, Random_Policy* random_policy)
        : player{player}, cur_state(random_policy) {
    //nothing right now
}

Game_2048::~Game_2048() {
    //nothing right now...
}

void Game_2048::play_game() {
    while (true) {
        //get legal moves, if none are left then end game, ask player what move to do, make the move and add a new random piece (assert it can), loop
        Move_2048 legal_moves[NUM_MOVES];
        int num_legal_moves = this->cur_state.get_legal_moves(legal_moves);
        if (num_legal_moves == 0) {
            break;
        }
        int which_move = this->player->get_move(this->cur_state, num_legal_moves, legal_moves);
        if (which_move < 0 || which_move >= num_legal_moves) {
            //player returned an illegal move; make an arbitrary choice for them
            which_move = 0;
        }
        Move_2048 move = legal_moves[which_move];
        this->cur_state = this->cur_state.make_move(move);
        bool added_random_cell = this->cur_state.add_random_cell();
        assert (added_random_cell);
    }
    //TODO do whatever end game stuff there is
}
