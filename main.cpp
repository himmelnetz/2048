
#include "2048.h"
#include "random_policy.h"
#include "player.h"
#include "trace.h"
#include "game.h"

#include <iostream>
#include <boost/algorithm/string.hpp>

Player_2048* get_player_from_player_name(string player_name) {
    boost::to_lower(player_name);
    if (player_name == "zed") {
        return new Zed_Player_2048();
    } else if (player_name == "bertha") {
        return new Bertha_Player_2048();
    } else if (player_name == "rod") {
        return new Rod_Player_2048();
    } else if (player_name == "friedrich") {
        return new Friedrich_Player_2048();
    } else if (player_name == "rodney") {
        return new Rodney_Player_2048();
    } else if (player_name == "silvia") {
        return new Silvia_Player_2048();
    } else {
        return NULL;
    }
}

Random_Policy make_standard_random_policy() {
    int num_values = 2;
    int values[2] = {2, 4};
    int weights[2] = {5, 1};
    int random_seed = (int) time(0);
    Random_Policy random_policy(num_values, values, weights, random_seed);
    return random_policy;
}

void generate_trace_files_for_player(Player_2048* player, string filename, int count = 1) {
    assert (count > 0 && count < 50); //a reasonable cutoff to prevent generating too many files
    Random_Policy random_policy = make_standard_random_policy();
    for (int i = 0; i < count; i++) {
        string cur_filename = count == 1
            ? filename
            : filename + "_" + std::to_string(i);
        State_Only_File_Trace_2048 file_trace(cur_filename);
        Game_2048 game(player, (Trace_2048*) &file_trace, &random_policy);
        game.play_game();
    }
}

void generate_statistics_for_player(Player_2048* player, int num_games) {
    assert (num_games > 0);
    Random_Policy random_policy = make_standard_random_policy();
    Player_Statistics_Trace_2048 statistics_trace;
    for (int i = 0; i < num_games; i++) {
        Game_2048 game(player, (Trace_2048*) &statistics_trace, &random_policy);
        game.play_game();
    }
    statistics_trace.get_score_statistics().print_statistics();
}

string make_generated_filename(string player_name) {
    //http://stackoverflow.com/questions/22318389/pass-system-date-and-time-as-a-filename-in-c
    time_t t = time(0);
    struct tm* now = localtime(&t);
    int max_len = 64;
    char buf[max_len];
    strftime(buf, max_len, "%Y_%m_%d_%H_%M_%S", now);
    return player_name + "_" + std::string(buf);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cout << "usage: ./2048 <mode> <player_name> <n>" << std::endl;
        return -1;
    }
    string mode = argv[1];
    string player_name = argv[2];
    int n = atoi(argv[3]);
    Player_2048* player = get_player_from_player_name(player_name);
    if (player == NULL) {
        std::cout << "invalid player name: " << player_name << std::endl;
        std::cout << "valid player names are: zed, bertha, rod, friedrich, rodney, sylvia" << std::endl;
        return -1;
    }
    int return_status;
    boost::to_lower(mode);
    if (mode == "traces") {
        string filename = make_generated_filename(player_name);
        generate_trace_files_for_player(player, filename, n);
        return_status = 0;
    } else if (mode == "stats") {
        generate_statistics_for_player(player, n);
        return_status = 0;
    } else {
        std::cout << "invalid mode: " << mode << std::endl;
        std::cout << "valid modes are: traces, stats" << std::endl;
        return_status = -1;
    }
    delete player;
    return return_status;
}
