
#include "trace.h"

#include "util.h"

//these three for the string stream things and writing to files (not sure which is necessary for what)
#include <iostream> 
#include <sstream> 
#include <fstream> //this one for writing to files

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Trace_2048::~Trace_2048() {
    //should be empty
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Dev_Null_Trace_2048::Dev_Null_Trace_2048() {
    //should be empty
}

Dev_Null_Trace_2048::~Dev_Null_Trace_2048() {
    //should be empty
}

void Dev_Null_Trace_2048::start_trace() {
    //should be empty
}

void Dev_Null_Trace_2048::on_player_move(Move_2048, double) {
    //should be empty
}

void Dev_Null_Trace_2048::on_new_state(State_2048 &) {
    //should be empty
}

void Dev_Null_Trace_2048::end_trace() {
    //should be empty
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

string State_Only_File_Trace_2048::convert_state_to_string(State_2048 &state) {
    std::ostringstream os;
    os << "{";
    os << "\"board\": [";
    for (int row = 0; row < NUM_ROWS; row++) {
        if (row != 0) {os << ",";}
        os << "[";
        for (int col = 0; col < NUM_COLS; col++) {
            if (col != 0) {os << ",";}
            os << state.get_cell_value(row, col);
        }
        os << "]";
    }
    os << "],";
    os << "\"score\": " << state.get_score();
    os << "}";
    return os.str();
}

State_Only_File_Trace_2048::State_Only_File_Trace_2048(string filename) {
    this->filename = filename;
    this->trace_written = false;
}

State_Only_File_Trace_2048::~State_Only_File_Trace_2048() {
    //nothing right now
}

void State_Only_File_Trace_2048::start_trace() {
    //nothing right now
}

void State_Only_File_Trace_2048::on_player_move(Move_2048, double) {
    //this trace ignores the players move
}

void State_Only_File_Trace_2048::on_new_state(State_2048 &state) {
    string state_string = this->convert_state_to_string(state);
    this->state_strings.push_back(state_string);
}

void State_Only_File_Trace_2048::end_trace() {
    string actual_filename = "traces/" + this->filename + ".trace2048";
    std::ofstream f(actual_filename);
    bool is_open = f.is_open();
    assert (is_open);
    f << "{";
    f << "\"num_rows\": " << NUM_ROWS << ",";
    f << "\"num_cols\": " << NUM_COLS << ",";
    f << "\"states\": [";
    for (unsigned int i = 0; i < this->state_strings.size(); i++) {
        if (i != 0) {f << ",";}
        f << this->state_strings[i];
    }
    f << "]";
    f << "}";
    f.close();
    return;
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Player_Statistics_Trace_2048::Player_Statistics_Trace_2048() {
    //should be empty
}

Player_Statistics_Trace_2048::~Player_Statistics_Trace_2048() {
    //should be empty
}

void Player_Statistics_Trace_2048::start_trace() {
    this->cur_score = 0;
    for (int i = 0; i < NUM_MOVES; i++) {
        this->cur_game_move_counts[i] = 0;
    }
}

void Player_Statistics_Trace_2048::on_player_move(Move_2048 move, double thinking_time_msec) {
    int move_i = move_to_i(move);
    this->cur_game_move_counts[move_i]++;
    this->thinking_time_statistics.add_datum(thinking_time_msec);
}

void Player_Statistics_Trace_2048::on_new_state(State_2048 &state) {
    this->cur_score = state.get_score();
}

void Player_Statistics_Trace_2048::end_trace() {
    this->score_statistics.add_datum(this->cur_score);
    int total_num_moves = 0;
    for (int i = 0; i < NUM_MOVES; i++) {
        int cur_count = this->cur_game_move_counts[i];
        total_num_moves += cur_count;
        this->move_statistics[i].add_datum(cur_count);
    }
    this->num_moves_per_game_statistics.add_datum(total_num_moves);
}

Summary_Statistics Player_Statistics_Trace_2048::get_score_statistics() {
    return this->score_statistics;
}

Summary_Statistics Player_Statistics_Trace_2048::get_thinking_time_statistics() {
    return this->thinking_time_statistics;
}

Summary_Statistics Player_Statistics_Trace_2048::get_num_moves_per_game_statistics() {
    return this->num_moves_per_game_statistics;
}

void Player_Statistics_Trace_2048::get_move_statistics(Summary_Statistics* move_statistics) {
    for (int i = 0; i < NUM_MOVES; i++) {
        move_statistics[i] = this->move_statistics[i];
    }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
