
#include "player.h"

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
