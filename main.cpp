
#include "2048.h"
#include "random_policy.h"
#include "player.h"
#include "trace.h"
#include "game.h"

int main(/*int argc, char *argv[]*/) {
    int num_values = 2;
    int values[2] = {2, 4};
    int weights[2] = {5, 1};
    int random_seed = (int) time(0);
    Random_Policy random_policy(num_values, values, weights, random_seed);
    Player_2048* player = new Bertha_Player_2048();
    Trace_2048* trace = new State_Only_File_Trace_2048("foo");
    Game_2048 game(player, trace, &random_policy);
    game.play_game();
    delete player;
    delete trace;
    return 0;
}
