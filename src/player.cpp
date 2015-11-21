
#include "player.h"

#include "util.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Player_2048::~Player_2048() {
    //should be empty
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Console_Player_2048::Console_Player_2048() {
    //nothing right now...
}

Console_Player_2048::~Console_Player_2048() {
    //nothing right now...
}

void Console_Player_2048::print_state_to_console(State_2048 &state) {
    for (int row = 0; row < NUM_ROWS; row++) {
        if (row != 0) {
            for (int i = 0; i < (5 * NUM_COLS - 1); i++) {printf("-");}
            printf("\n");
        }
        for (int col = 0; col < NUM_COLS; col++) {
            if (col != 0) {printf("|");}
            printf("%4d", state.get_cell_value(row, col));
        }
        printf("\n");
    }
    printf("\nScore: %d\n\n", state.get_score());
    return;
}

void Console_Player_2048::print_legal_moves(int num_legal_moves, Move_2048* legal_moves) {
    printf("Legal Moves: ");
    for (int i = 0; i < num_legal_moves; i++) {
        if (i != 0) {printf(", ");}
        switch (legal_moves[i]) {
            case Move_2048::UP: printf("UP"); break;
            case Move_2048::DOWN: printf("DOWN"); break;
            case Move_2048::LEFT: printf("LEFT"); break;
            case Move_2048::RIGHT: printf("RIGHT"); break;
            default: assert(false);
        }
    }
    printf("\n");
}

int Console_Player_2048::try_get_move(char c, int num_legal_moves, Move_2048* legal_moves) {
    Move_2048 requested_move;
    if (c == 'w' || c == 'W') {
        requested_move = Move_2048::UP;
    } else if (c == 's' || c == 'S') {
        requested_move = Move_2048::DOWN;
    } else if (c == 'a' || c == 'A') {
        requested_move = Move_2048::LEFT;
    } else if (c == 'd' || c == 'D') {
        requested_move = Move_2048::RIGHT;
    } else {
        return -1;
    }
    for (int i = 0; i < num_legal_moves; i++) {
        if (legal_moves[i] == requested_move) {
            return i;
        }
    }
    return -1;
}

void Console_Player_2048::init() {
    //nothing right now...
}

int Console_Player_2048::get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves) {
    //haha very funny im using printf which isnt good blah blah. i used it here because i just need a quick console interface for making sure the functionality is correct
    this->print_state_to_console(state);
    this->print_legal_moves(num_legal_moves, legal_moves);
    while (true) {
        printf("Enter move using WASD: ");
        char c;
        int num_returned = scanf("%c", &c);
        assert (num_returned == 1);
        if (c == '\n') {continue;}
        int move_i = this->try_get_move(c, num_legal_moves, legal_moves);
        if (move_i != -1) {
            return move_i;
        }
        printf("Illegal Move\n");
    }
    assert (false);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Zed_Player_2048::Zed_Player_2048() {
    //nothing right now...
}

Zed_Player_2048::~Zed_Player_2048() {
    //nothing right now...
}

void Zed_Player_2048::init() {
    //nothing right now...
}

int Zed_Player_2048::get_move(State_2048 &, int num_legal_moves, Move_2048*) {
    return rand() % num_legal_moves;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Bertha_Player_2048::Bertha_Player_2048() {
    //nothing right now...
}

Bertha_Player_2048::~Bertha_Player_2048() {
    //nothing right now...
}

void Bertha_Player_2048::init() {
    //nothing right now...
}

int Bertha_Player_2048::get_move(State_2048 &, int num_legal_moves, Move_2048* legal_moves) {
    Move_2048 move_preference[NUM_MOVES] = {Move_2048::LEFT, Move_2048::DOWN, Move_2048::UP, Move_2048::RIGHT};
    for (int i = 0; i < NUM_MOVES; i++) {
        Move_2048 pref_move = move_preference[i];
        for (int j = 0; j < num_legal_moves; j++) {
            Move_2048 cur_move = legal_moves[j];
            if (pref_move == cur_move) {
                return j;
            }
        }
    }
    assert (false);
    return 0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int Single_Level_Heuristic_Player_2048::compare_heuristic_values(int* a, int a_count, int* b, int b_count) {
    if (a_count == 0 && b_count == 0) {return 0;}
    if (a_count == 0) {return -1;}
    if (b_count == 0) {return 1;}
    int a_val = *a;
    int b_val = *b;
    if (a_val < b_val) {return -1;}
    if (a_val > b_val) {return 1;}
    return this->compare_heuristic_values(a + 1, a_count - 1, b + 1, b_count - 1);
}

Single_Level_Heuristic_Player_2048::Single_Level_Heuristic_Player_2048() {
    //nothing right now...
}

Single_Level_Heuristic_Player_2048::~Single_Level_Heuristic_Player_2048() {
    //nothing right now...
}

void Single_Level_Heuristic_Player_2048::init() {
    //nothing right now...
}

int Single_Level_Heuristic_Player_2048::get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves) {
    int max_move_i = -1;
    int max_heuristic[MAX_NUM_HEURISTIC_VALUES];
    int max_heuristic_count = 0;
    for (int i = 0; i < num_legal_moves; i++) {
        Move_2048 cur_move = legal_moves[i];
        State_2048 state_after_move = state.make_move(cur_move);
        int cur_heuristic[MAX_NUM_HEURISTIC_VALUES];
        int cur_heuristic_count = this->get_heuristic_values(state_after_move, cur_move, cur_heuristic);
        int compare = this->compare_heuristic_values(cur_heuristic, cur_heuristic_count, max_heuristic, max_heuristic_count);
        if (compare > 0) {
            max_move_i = i;
            for (int j = 0; j < cur_heuristic_count; j++) {
                max_heuristic[j] = cur_heuristic[j];
            }
            max_heuristic_count = cur_heuristic_count;
        }
    }
    return max_move_i;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int Rod_Player_2048::move_to_preference(Move_2048 move) {
    switch (move) {
        case Move_2048::UP: return 1;
        case Move_2048::DOWN: return 3;
        case Move_2048::LEFT: return 4;
        case Move_2048::RIGHT: return 2;
        default:
            assert (false);
            return 0;
    }
}

Rod_Player_2048::Rod_Player_2048() {
    //nothing right now...
}

Rod_Player_2048::~Rod_Player_2048() {
    //nothing right now...
}

int Rod_Player_2048::get_heuristic_values(State_2048 &state, Move_2048 move, int* heuristic_values) {
    heuristic_values[0] = state.get_score();
    heuristic_values[1] = this->move_to_preference(move);
    return 2;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int Friedrich_Player_2048::move_to_preference(Move_2048 move) {
    switch (move) {
        case Move_2048::UP: return 1;
        case Move_2048::DOWN: return 3;
        case Move_2048::LEFT: return 4;
        case Move_2048::RIGHT: return 2;
        default:
            assert (false);
            return 0;
    }
}

Friedrich_Player_2048::Friedrich_Player_2048() {
    //nothing right now...
}

Friedrich_Player_2048::~Friedrich_Player_2048() {
    //nothing right now...
}

int Friedrich_Player_2048::get_heuristic_values(State_2048 &state, Move_2048 move, int* heuristic_values) {
    int max_i = MAX_NUM_HEURISTIC_VALUES - 1;
    for (int i = 0; i < max_i; i++) {
        heuristic_values[i] = 0;
    }
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            int cell_value = state.get_cell_value(row, col);
            if (cell_value != 0) {
                int i = cell_value_to_i(cell_value);
                if (i < max_i) {
                    heuristic_values[max_i - i - 1]++;
                }
            }
        }
    }
    heuristic_values[MAX_NUM_HEURISTIC_VALUES - 1] = this->move_to_preference(move);
    return MAX_NUM_HEURISTIC_VALUES;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

double Full_Single_Level_Heuristic_Player_2048::get_expected_heuristic_value_after_random(State_2048 &state, Move_2048 move) {
    int num_empty_cells = state.get_num_empty_cells();
    Random_Policy* random_policy = state.get_random_policy();
    vector<int> values = random_policy->get_values();
    vector<double> normalized_weights = random_policy->get_normalized_weights();
    double total_heuristic_value = 0.0;

    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            if (state.get_cell_value(row, col) == 0) {
                for (vector<int>::size_type i = 0; i < values.size(); i++) {
                    int value = values[i];
                    double weight = normalized_weights[i] / num_empty_cells;
                    State_2048 new_state = state.make_state_after_adding_random_cell(row, col, value);
                    double new_state_heuristic_value = this->get_heuristic_value(new_state, move);
                    total_heuristic_value += new_state_heuristic_value * weight;
                }
            }
        }
    }

    return total_heuristic_value;
}

Full_Single_Level_Heuristic_Player_2048::Full_Single_Level_Heuristic_Player_2048() {
    //nothing right now...
}

Full_Single_Level_Heuristic_Player_2048::~Full_Single_Level_Heuristic_Player_2048() {
    //nothing right now...
}

void Full_Single_Level_Heuristic_Player_2048::init() {
    //nothing right now...
}

int Full_Single_Level_Heuristic_Player_2048::get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves) {
    int max_move_i = -1;
    double max_heuristic_value = 0.0;
    for (int i = 0; i < num_legal_moves; i++) {
        Move_2048 cur_move = legal_moves[i];
        State_2048 state_after_move = state.make_move(cur_move);
        double cur_heuristic_value = this->get_expected_heuristic_value_after_random(state_after_move, cur_move);
        if (max_move_i == -1 || cur_heuristic_value > max_heuristic_value) {
            max_move_i = i;
            max_heuristic_value = cur_heuristic_value;
        }
    }
    return max_move_i;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

int Rodney_Player_2048::move_to_preference(Move_2048 move) {
    switch (move) {
        case Move_2048::UP: return 1;
        case Move_2048::DOWN: return 3;
        case Move_2048::LEFT: return 4;
        case Move_2048::RIGHT: return 2;
        default:
            assert (false);
            return 0;
    }
}

Rodney_Player_2048::Rodney_Player_2048() {
    //nothing right now...
}

Rodney_Player_2048::~Rodney_Player_2048() {
    //nothing right now...
}

double Rodney_Player_2048::get_heuristic_value(State_2048 &state, Move_2048 move) {
    return state.get_score() + this->move_to_preference(move) / 4.0;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

double Many_Level_Heuristic_Player_2048::get_expected_heuristic_value_after_random(State_2048 &state, int depth) {
    int num_empty_cells = state.get_num_empty_cells();
    Random_Policy* random_policy = state.get_random_policy();
    vector<int> values = random_policy->get_values();
    vector<double> normalized_weights = random_policy->get_normalized_weights();
    double total_heuristic_value = 0.0;

    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            if (state.get_cell_value(row, col) == 0) {
                for (vector<int>::size_type i = 0; i < values.size(); i++) {
                    int value = values[i];
                    double weight = normalized_weights[i] / num_empty_cells;
                    State_2048 new_state = state.make_state_after_adding_random_cell(row, col, value);
                    double new_state_heuristic_value = this->get_heuristic_value_after_move(new_state, depth - 1);
                    total_heuristic_value += new_state_heuristic_value * weight;
                }
            }
        }
    }

    return total_heuristic_value;
}

double Many_Level_Heuristic_Player_2048::get_heuristic_value_after_move(State_2048 &state, int depth) {
    assert (depth > 0);

    double max_heuristic_value = 0.0;
    Move_2048 legal_moves[NUM_MOVES];
    int num_legal_moves = state.get_legal_moves(legal_moves);
    if (num_legal_moves == 0) {
        return -10000000.0;
    }
    for (int i = 0; i < num_legal_moves; i++) {
        Move_2048 cur_move = legal_moves[i];
        State_2048 state_after_move = state.make_move(cur_move);
        double cur_heuristic_value = depth == 1
            ? this->get_heuristic_value(state)
            : this->get_expected_heuristic_value_after_random(state_after_move, depth);
        if (i == 0 || cur_heuristic_value > max_heuristic_value) {
            max_heuristic_value = cur_heuristic_value;
        }
    }
    return max_heuristic_value;
}

Many_Level_Heuristic_Player_2048::Many_Level_Heuristic_Player_2048() {
    //nothing right now...
}

Many_Level_Heuristic_Player_2048::~Many_Level_Heuristic_Player_2048() {
    //nothing right now...
}

void Many_Level_Heuristic_Player_2048::init() {
    //nothing right now...
}

int Many_Level_Heuristic_Player_2048::get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves) {
    int max_move_i = -1;
    double max_heuristic_value = 0.0;
    for (int i = 0; i < num_legal_moves; i++) {
        Move_2048 cur_move = legal_moves[i];
        State_2048 state_after_move = state.make_move(cur_move);
        double cur_heuristic_value = this->get_expected_heuristic_value_after_random(state_after_move, MANY_LEVEL_HEURISTIC_PLAYER_SEARCH_DEPTH);
        if (max_move_i == -1 || cur_heuristic_value > max_heuristic_value) {
            max_move_i = i;
            max_heuristic_value = cur_heuristic_value;
        }
    }
    return max_move_i;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

double Silvia_Player_2048::get_neighbor_discomfort(int index_a, int index_b) {
    if (index_b == -1) {
        return index_a;
    } else if (index_a == index_b) {
        return index_a * 0.75;
    } else {
        return std::abs(index_a - index_b);
    }
}

double Silvia_Player_2048::get_neighbor_discomfort_for_cell(int index_board[NUM_ROWS][NUM_COLS], int row, int col, int cur_value_index) {
    double total_discomfort = 0.0;

    //up
    if (row > 0) {
        int neighbor_value_index = index_board[row - 1][col];
        total_discomfort += this->get_neighbor_discomfort(cur_value_index, neighbor_value_index);
    }
    //down
    if (row < NUM_ROWS - 1) {
        int neighbor_value_index = index_board[row + 1][col];
        total_discomfort += this->get_neighbor_discomfort(cur_value_index, neighbor_value_index);
    }
    //left
    if (col > 0) {
        int neighbor_value_index = index_board[row][col - 1];
        total_discomfort += this->get_neighbor_discomfort(cur_value_index, neighbor_value_index);
    }
    //right
    if (col < NUM_COLS - 1) {
        int neighbor_value_index = index_board[row][col + 1];
        total_discomfort += this->get_neighbor_discomfort(cur_value_index, neighbor_value_index);
    }

    return total_discomfort;
}

double Silvia_Player_2048::get_location_discomfort(int row, int col, int value_index) {
    return ((col * NUM_ROWS) + (NUM_ROWS - row - 1)) * value_index;
}

Silvia_Player_2048::Silvia_Player_2048() {
    //nothing right now...
}

Silvia_Player_2048::~Silvia_Player_2048() {
    //nothing right now...
}

double Silvia_Player_2048::get_heuristic_value(State_2048 &state) {
    int index_board[NUM_ROWS][NUM_COLS];
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            int value = state.get_cell_value(row, col);
            index_board[row][col] = value != 0
                ? cell_value_to_i(value)
                : -1;
        }
    }

    double total_location_discomfort = 0.0;
    double total_neighbor_discomfort = 0.0;

    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            int cur_value_index = index_board[row][col];
            if (cur_value_index != -1) {
                total_location_discomfort += this->get_location_discomfort(row, col, cur_value_index);
                total_neighbor_discomfort += this->get_neighbor_discomfort_for_cell(index_board, row, col, cur_value_index);
            }
        }
    }
    
    double total_discomfort = total_location_discomfort * 4.0 + total_neighbor_discomfort * 2.0;
    double weighted_num_empty_cells = state.get_num_empty_cells() * 128.0;
    return -total_discomfort + weighted_num_empty_cells;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
