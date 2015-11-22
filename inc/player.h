
#ifndef ___2048__PLAYER__H___
#define ___2048__PLAYER__H___

#include "2048.h"
#include "state.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Player_2048 {

private:

public:

    virtual ~Player_2048();
    virtual void init(/*possibly put things like config here?*/) = 0;
    virtual int get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves) = 0;
    virtual void after_move(State_2048 &state, bool is_game_over) = 0;

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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
    virtual void after_move(State_2048 &, bool) {};

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Zed_Player_2048 : public Player_2048 {

private:

public:

    Zed_Player_2048();
    virtual ~Zed_Player_2048();

    virtual void init();
    virtual int get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves);
    virtual void after_move(State_2048 &, bool) {};

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Bertha_Player_2048 : public Player_2048 {

private:

public:

    Bertha_Player_2048();
    virtual ~Bertha_Player_2048();

    virtual void init();
    virtual int get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves);
    virtual void after_move(State_2048 &, bool) {};

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

static const int MAX_NUM_HEURISTIC_VALUES = 16;

class Single_Level_Heuristic_Player_2048 : public Player_2048 {

private:

    int compare_heuristic_values(int* a, int a_count, int* b, int b_count);

public:

    Single_Level_Heuristic_Player_2048();
    virtual ~Single_Level_Heuristic_Player_2048();

    virtual void init();
    virtual int get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves);
    virtual void after_move(State_2048 &, bool) {};

    virtual int get_heuristic_values(State_2048 &state, Move_2048 move, int* heuristic_values) = 0;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Rod_Player_2048 : public Single_Level_Heuristic_Player_2048 {

private:

    int move_to_preference(Move_2048 move);

public:

    Rod_Player_2048();
    virtual ~Rod_Player_2048();

    virtual int get_heuristic_values(State_2048 &state, Move_2048 move, int* heuristic_values);

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Friedrich_Player_2048 : public Single_Level_Heuristic_Player_2048 {

private:

    int move_to_preference(Move_2048 move);

public:

    Friedrich_Player_2048();
    virtual ~Friedrich_Player_2048();

    virtual int get_heuristic_values(State_2048 &state, Move_2048 move, int* heuristic_values);

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Full_Single_Level_Heuristic_Player_2048 : public Player_2048 {

private:

    double get_expected_heuristic_value_after_random(State_2048 &state, Move_2048 move);

public:

    Full_Single_Level_Heuristic_Player_2048();
    virtual ~Full_Single_Level_Heuristic_Player_2048();

    virtual void init();
    virtual int get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves);
    virtual void after_move(State_2048 &, bool) {};

    virtual double get_heuristic_value(State_2048 &state, Move_2048 move) = 0;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Rodney_Player_2048 : public Full_Single_Level_Heuristic_Player_2048 {

private:

    int move_to_preference(Move_2048 move);

public:

    Rodney_Player_2048();
    virtual ~Rodney_Player_2048();

    virtual double get_heuristic_value(State_2048 &state, Move_2048 move);
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

static const int MANY_LEVEL_HEURISTIC_PLAYER_SEARCH_DEPTH = 4;

class Many_Level_Heuristic_Player_2048 : public Player_2048 {

private:

    double get_expected_heuristic_value_after_random(State_2048 &state, int depth, double branch_weight);
    double get_heuristic_value_after_move(State_2048 &state, int depth, double branch_weight);

public:

    Many_Level_Heuristic_Player_2048();
    virtual ~Many_Level_Heuristic_Player_2048();

    virtual void init();
    virtual int get_move(State_2048 &state, int num_legal_moves, Move_2048* legal_moves);
    virtual void after_move(State_2048 &, bool) {};

    virtual double get_heuristic_value(State_2048 &state) = 0;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Silvia_Player_2048 : public Many_Level_Heuristic_Player_2048 {

private:

    double get_neighbor_discomfort(int value_a, int value_b);
    double get_neighbor_discomfort_for_cell(int index_board[NUM_ROWS][NUM_COLS], int row, int col, int cur_value_index);
    double get_location_discomfort(int row, int col, int value);

public:

    Silvia_Player_2048();
    virtual ~Silvia_Player_2048();

    virtual double get_heuristic_value(State_2048 &state);
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif /* ___2048__PLAYER__H___ */
