
#include "game.h"

#include <boost/date_time/posix_time/posix_time.hpp> //for timing how long the player takes to make a move

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Game_2048::Game_2048(Player_2048* player, Trace_2048* trace, Random_Policy* random_policy)
        : player{player}, trace{trace}, cur_state(random_policy) {
    //nothing right now
}

Game_2048::~Game_2048() {
    //nothing right now...
}

void Game_2048::play_game() {
    this->cur_state.reset_to_initial_state();
    this->trace->start_trace();
    this->trace->on_new_state(this->cur_state);
    while (true) {
        //get legal moves, if none are left then end game, ask player what move to do, make the move and add a new random piece (assert it can), loop
        Move_2048 legal_moves[NUM_MOVES];
        int num_legal_moves = this->cur_state.get_legal_moves(legal_moves);
        if (num_legal_moves == 0) {
            break;
        }
        boost::posix_time::ptime startTime = boost::posix_time::microsec_clock::local_time();
        int which_move = this->player->get_move(this->cur_state, num_legal_moves, legal_moves);
        boost::posix_time::ptime endTime = boost::posix_time::microsec_clock::local_time();
        double thinking_time_msec = (endTime - startTime).total_microseconds() / 1000.0;
        if (which_move < 0 || which_move >= num_legal_moves) {
            //player returned an illegal move; make an arbitrary choice for them
            which_move = 0;
        }
        Move_2048 move = legal_moves[which_move];
        this->trace->on_player_move(move, thinking_time_msec);
        this->cur_state = this->cur_state.make_move(move);
        bool added_random_cell = this->cur_state.add_random_cell();
        assert (added_random_cell);
        this->trace->on_new_state(this->cur_state);
    }
    this->trace->end_trace();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
