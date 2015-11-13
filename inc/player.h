
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

#endif /* ___2048__PLAYER__H___ */
