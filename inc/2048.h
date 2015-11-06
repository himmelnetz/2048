
#ifndef ___2048__2048__H___
#define ___2048__2048__H___

//#define NDEBUG    //uncomment this to turn off asserts
#include <assert.h>

#include <vector>
#include <string>

using std::vector;
using std::string;

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
    int get_score();
    int get_legal_moves(Move_2048* legal_moves); //legal moves must be big enough to hold everything

    State_2048 make_move(Move_2048 move);

};

class Player_2048 {

private:

public:

    virtual ~Player_2048();
    virtual void init(/*possibly put things like config here?*/) = 0;
    virtual int get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves) = 0;

};

class Console_Player_2048 : public Player_2048 {

private:

    void print_state_to_console(State_2048 &state);
    void print_legal_moves(int num_legal_moves, Move_2048* legal_moves);
    int try_get_move(char c, int num_legal_moves, Move_2048* legal_moves);

public:

    Console_Player_2048();
    virtual ~Console_Player_2048();

    virtual void init();
    virtual int get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves);

};

class Zed_Player_2048 : public Player_2048 {

private:

public:

    Zed_Player_2048();
    virtual ~Zed_Player_2048();

    virtual void init();
    virtual int get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves);

};

class Bertha_Player_2048 : public Player_2048 {

private:

public:

    Bertha_Player_2048();
    virtual ~Bertha_Player_2048();

    virtual void init();
    virtual int get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves);

};

class Trace_2048 {

private:

public:

    virtual ~Trace_2048() = 0;
    virtual void start_trace() = 0;
    virtual void on_player_move(Move_2048 move, double thinking_time_msec) = 0;
    virtual void on_new_state(State_2048 &state) = 0;
    virtual void end_trace() = 0;

};

class Dev_Null_Trace_2048 : public Trace_2048 {

private:

public:

    Dev_Null_Trace_2048();
    virtual ~Dev_Null_Trace_2048();
    virtual void start_trace();
    virtual void on_player_move(Move_2048 move, double thinking_time_msec);
    virtual void on_new_state(State_2048 &state);
    virtual void end_trace();
};

class State_Only_File_Trace_2048 : public Trace_2048 {

private:

    string filename;
    vector<string> state_strings;
    bool trace_written;

    string convert_state_to_string(State_2048 &state);

public:

    State_Only_File_Trace_2048(string filename);
    virtual ~State_Only_File_Trace_2048();
    virtual void start_trace();
    virtual void on_player_move(Move_2048 move, double thinking_time_msec);
    virtual void on_new_state(State_2048 &state);
    virtual void end_trace();

};

class Game_2048 {

private:

    Player_2048* player;
    Trace_2048* trace;
    State_2048 cur_state;

public:

    Game_2048(Player_2048* player, Trace_2048* trace, Random_Policy* random_policy);
    ~Game_2048();

    void play_game();

};

#endif /* ___2048__2048__H___ */
