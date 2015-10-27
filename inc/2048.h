
#ifndef ___2048__2048__H___
#define ___2048__2048__H___

//#define NDEBUG    //uncomment this to turn off asserts
#include <assert.h>

static const int NUM_ROWS = 4;
static const int NUM_COLS = 4;

class State_2048 {

private:

    int board[NUM_ROWS][NUM_COLS];
    int score;

public:

    State_2048();
    ~State_2048();

    int get_cell_value(int row, int col);

};

class Game_2048 {

private:

    State_2048 cur_state;

public:

    Game_2048();
    ~Game_2048();

    void play_game();

};

#endif /* ___2048__2048__H___ */
