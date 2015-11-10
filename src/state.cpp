
#include "state.h"

#include "util.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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
                prev_row = row;
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
            bool something_combined = this->combine_cells_row(row, -dcol, dont_modify);
            something_happened = something_happened || something_combined;
        }
    } else {
        for (int col = 0; col < NUM_COLS; col++) {
            bool something_combined = this->combine_cells_col(col, -drow, dont_modify);
            something_happened = something_happened || something_combined;
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
            bool something_cascaded = this->cascade_row(row, -dcol, dont_modify);
            something_happened = something_happened || something_cascaded;
        }
    } else {
        for (int col = 0; col < NUM_COLS; col++) {
            bool something_cascaded = this->cascade_col(col, -drow, dont_modify);
            something_happened = something_happened || something_cascaded;
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

int State_2048::get_score() {
    return this->score;
}

int State_2048::get_legal_moves(Move_2048* legal_moves) {
    int num_legal_moves = 0;
    for (int i = 0; i < NUM_MOVES; i++) {
        Move_2048 cur_move = ALL_MOVES[i];
        if (this->try_make_move(cur_move, true)) {
            legal_moves[num_legal_moves] = cur_move;
            num_legal_moves++;
        }
    }
    return num_legal_moves;
}

State_2048 State_2048::make_move(Move_2048 move) {
    State_2048 new_state(this->random_policy);
    new_state.copy_state(this);
    bool something_happened = new_state.try_make_move(move, false);
    assert (something_happened);
    return new_state;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
