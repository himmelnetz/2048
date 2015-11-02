
#ifndef ___2048__2048__H___
#define ___2048__2048__H___

//#define NDEBUG    //uncomment this to turn off asserts
#include <assert.h>

#include <vector>

using std::vector;

static const int NUM_ROWS = 4;
static const int NUM_COLS = 4;

enum class Move_2048 {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Random_Policy {

private:

    vector<int> values;
    vector<int> weights;
    int total_weight;

    int rand_int(int lo, int hi); //[lo, hi)

public:

    Random_Policy(int n, int* values_in, int* weights_in, int random_seed);
    ~Random_Policy();

    void get_random_position_and_value(int num_position, int &position_to_use, int &value);

};

class State_2048 {

private:

    int board[NUM_ROWS][NUM_COLS];
    int score;
    Random_Policy* random_policy;

    void reset_to_blank_state();
    bool add_random_cell();

public:

    State_2048(Random_Policy* random_policy);
    ~State_2048();

    void reset_to_initial_state();

    int get_cell_value(int row, int col);

};

class Game_2048 {

private:

    State_2048 cur_state;

public:

    Game_2048(Random_Policy* random_policy);
    ~Game_2048();

    void play_game();

};

#endif /* ___2048__2048__H___ */
