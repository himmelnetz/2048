
#ifndef ___2048__TRACE__H___
#define ___2048__TRACE__H___

#include "2048.h"
#include "state.h"
#include "statistics.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Trace_2048 {

private:

public:

    virtual ~Trace_2048() = 0;
    virtual void start_trace() = 0;
    virtual void on_player_move(Move_2048 move, double thinking_time_msec) = 0;
    virtual void on_new_state(State_2048 &state) = 0;
    virtual void end_trace() = 0;

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class Player_Statistics_Trace_2048 : public Trace_2048 {

private:

    Summary_Statistics score_statistics;
    Summary_Statistics thinking_time_statistics;
    Summary_Statistics num_moves_per_game_statistics;
    Summary_Statistics move_statistics[NUM_MOVES];

    int cur_score;
    int cur_game_move_counts[NUM_MOVES];

public:

    Player_Statistics_Trace_2048();
    virtual ~Player_Statistics_Trace_2048();
    virtual void start_trace();
    virtual void on_player_move(Move_2048 move, double thinking_time_msec);
    virtual void on_new_state(State_2048 &state);
    virtual void end_trace();

    void merge(Player_Statistics_Trace_2048* other_trace);

    Summary_Statistics get_score_statistics();
    Summary_Statistics get_thinking_time_statistics();
    Summary_Statistics get_num_moves_per_game_statistics();
    void get_move_statistics(Summary_Statistics* move_statistics);

};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif /* ___2048__TRACE__H___ */
