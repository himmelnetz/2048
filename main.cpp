
#include "2048.h"

#include <stdio.h>
#include <iostream>

int main(/*int argc, char *argv[]*/) {
    int num_values = 2;
    int values[2] = {2, 4};
    int weights[2] = {5, 1};
    int random_seed = (int) time(0);
    Random_Policy random_policy(num_values, values, weights, random_seed);
    Player_2048* player = new Console_Player_2048();
    Game_2048 game(player, &random_policy);
    game.play_game();
    delete player;
    return 0;
}
