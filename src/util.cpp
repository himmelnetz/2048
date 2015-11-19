
#include "2048.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void convert_move_to_drow_dcol(Move_2048 move, int &drow, int &dcol) {
    switch (move) {
        case Move_2048::UP:
            drow = -1;
            dcol = 0;
            return;
        case Move_2048::DOWN:
            drow = 1;
            dcol = 0;
            return;
        case Move_2048::LEFT:
            drow = 0;
            dcol = -1;
            return;
        case Move_2048::RIGHT:
            drow = 0;
            dcol = 1;
            return;
        default:
            //should never get here...
            assert (false);
            return;
    }
}

int move_to_i(Move_2048 move) {
    switch (move) {
        case Move_2048::UP: return 0;
        case Move_2048::DOWN: return 1;
        case Move_2048::LEFT: return 2;
        case Move_2048::RIGHT: return 3;
        default:
            assert (false);
            return 0;
    }
}

Move_2048 i_to_move(int i) {
    switch (i) {
        case 0: return Move_2048::UP;
        case 1: return Move_2048::DOWN;
        case 2: return Move_2048::LEFT;
        case 3: return Move_2048::RIGHT;
        default:
            assert (false);
            return Move_2048::UP;
    }
}

//assumes base 2
int cell_value_to_i_general(int cell_value) {
    assert (cell_value > 0);
    int i = 0;
    while (cell_value != 2) {
        assert (cell_value % 2 == 0);
        cell_value /= 2;
        i++;
    }
    return i;
}

int cell_value_to_i(int cell_value) {
    assert (cell_value > 0);
    switch (cell_value) {
        case 2: return 0;
        case 4: return 1;
        case 8: return 2;
        case 16: return 3;
        case 32: return 4;
        case 64: return 5;
        case 128: return 6;
        case 256: return 7;
        case 512: return 8;
        case 1024: return 9;
        case 2048: return 10;
        case 4098: return 11;
        default: return cell_value_to_i_general(cell_value);
    }
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
