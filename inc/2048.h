
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

// i really dont want to assign them values, but i will so they can be used as array indexes
enum class Move_2048 {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

static const int NUM_MOVES = 4;
static const Move_2048 ALL_MOVES[NUM_MOVES] = {Move_2048::UP, Move_2048::DOWN, Move_2048::LEFT, Move_2048::RIGHT};

#endif /* ___2048__2048__H___ */
