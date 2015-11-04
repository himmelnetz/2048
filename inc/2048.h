
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

static const int NUM_MOVES = 4;
static const Move_2048 ALL_MOVES[NUM_MOVES] = {Move_2048::UP, Move_2048::DOWN, Move_2048::LEFT, Move_2048::RIGHT};


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

//should be immutable...but have that reset state thingy. TODO
class State_2048 {

private:

    int board[NUM_ROWS][NUM_COLS];
    int score;
    Random_Policy* random_policy;

    void reset_to_blank_state();
    void copy_state(State_2048* other_state);

    bool combine_cells_row(int row, int dir, bool dont_modify);
    bool combine_cells_col(int col, int dir, bool dont_modify);
    bool combine_cells(int drow, int dcol, bool dont_modify);
    bool cascade_row(int row, int dir, bool dont_modify);
    bool cascade_col(int col, int dir, bool dont_modify);
    bool cascade(int drow, int dcol, bool dont_modify);
    bool try_make_move(Move_2048 move, bool dont_modify);

    bool is_legal_move(Move_2048 move);

public:

    State_2048(Random_Policy* random_policy);
    ~State_2048();

    void reset_to_initial_state();
    bool add_random_cell();

    int get_cell_value(int row, int col);
    int get_legal_moves(Move_2048* legal_moves); //legal moves must be big enough to hold everything

    State_2048 make_move(Move_2048 move);

};

class Player_2048 {

private:

public:

    virtual void init(/*possibly put things like config here?*/) = 0;
    virtual int get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves) = 0;

};

class Game_2048 {

private:

    Player_2048* player;
    State_2048 cur_state;

public:

    Game_2048(Player_2048* player, Random_Policy* random_policy);
    ~Game_2048();

    void play_game();

};

#endif /* ___2048__2048__H___ */
