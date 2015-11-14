
#ifndef ___2048__STATE__H___
#define ___2048__STATE__H___

#include "2048.h"
#include "random_policy.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

class State_2048 {

private:

    int board[NUM_ROWS][NUM_COLS];
    int score;
    int num_empty_cells;

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

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

#endif /* ___2048__STATE__H___ */
