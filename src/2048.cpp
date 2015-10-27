
#include "2048.h"

State_2048::State_2048() {
    for (int row = 0; row < NUM_ROWS; row++) {
        for (int col = 0; col < NUM_COLS; col++) {
            this->board[row][col] = 0;
        }
    }
    this->score = 0;
}

State_2048::~State_2048() {
    //nothing right now...
}

int State_2048::get_cell_value(int row, int col) {
    assert(row >= 0 && row < NUM_ROWS && col >= 0 && col < NUM_COLS);
    return this->board[row][col];
}

Game_2048::Game_2048() {
    //nothing right now...
}

Game_2048::~Game_2048() {
    //nothing right now...
}

void Game_2048::play_game() {
    //um, this is where the game would go, but nothing right now...
}
