
#include "2048.h"
#include "random_policy.h"
#include "player.h"
#include "trace.h"
#include "game.h"

#include <iostream>
#include <boost/algorithm/string.hpp>
#include <pthread.h>

static const int NUM_THREADS = 1;

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
    } else if (player_name == "oliver") {
        return new Oliver_Player_2048("");
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

Random_Policy* make_new_standard_random_policy() {
    int num_values = 2;
    int values[2] = {2, 4};
    int weights[2] = {5, 1};
    int random_seed = (int) time(0);
    return new Random_Policy(num_values, values, weights, random_seed);
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

typedef struct {
    int thread_num;
    Player_2048* player;
    Player_Statistics_Trace_2048* trace;
    Random_Policy* random_policy;
    int num_games;
} statistics_worker_args;

void* generate_statistics_worker(void* void_arg) {
    statistics_worker_args* args = (statistics_worker_args*) void_arg;

    Player_2048* player = args->player;
    Trace_2048* trace = args->trace;
    Random_Policy* random_policy = args->random_policy;
    int num_games = args->num_games;

    for (int i = 0; i < num_games; i++) {
        Game_2048 game(player, trace, random_policy);
        State_2048 end_state = game.play_game();
        if ((i + 1) % 10 == 0) {
            std::cout << "for game " << i + 1 << " on thread " << args->thread_num << " score was " << end_state.get_score() << std::endl;
        }
    }

    pthread_exit(NULL);
}

void generate_statistics_for_player_threads(Player_2048* player, int num_games) {
    assert (num_games > 0);
    /*
    Random_Policy random_policy = make_standard_random_policy();
    Player_Statistics_Trace_2048 statistics_trace;
    for (int i = 0; i < num_games; i++) {
        std::cout << "on game " << i + 1 << std::endl;
        Game_2048 game(player, (Trace_2048*) &statistics_trace, &random_policy);
        game.play_game();
    }
    statistics_trace.get_score_statistics().print_statistics();
    statistics_trace.get_thinking_time_statistics().print_statistics();
    */
    /**/
    int num_games_per_thread = (num_games + NUM_THREADS - 1) / NUM_THREADS;

    pthread_t pthreads[NUM_THREADS];
    statistics_worker_args args[NUM_THREADS];
    for (int i = 0; i < NUM_THREADS; i++) {
        statistics_worker_args* cur_args = &(args[i]);
        cur_args->thread_num = i;
        cur_args->player = player;
        cur_args->trace = new Player_Statistics_Trace_2048();
        cur_args->random_policy = make_new_standard_random_policy();
        cur_args->num_games = num_games_per_thread;
        int ret = pthread_create(&(pthreads[i]), NULL, &generate_statistics_worker, (void*) cur_args);
        assert (ret == 0);
    }

    Player_Statistics_Trace_2048 all_statistics;

    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(pthreads[i], NULL);
        all_statistics.merge(args[i].trace);
        delete args[i].trace;
        delete args[i].random_policy;
    }

    all_statistics.get_score_statistics().print_statistics();
    all_statistics.get_thinking_time_statistics().print_statistics();
    /**/
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
        std::cout << "valid player names are: zed, bertha, rod, friedrich, rodney, silvia, oliver" << std::endl;
        return -1;
    }
    int return_status;
    boost::to_lower(mode);
    if (mode == "traces") {
        string filename = make_generated_filename(player_name);
        generate_trace_files_for_player(player, filename, n);
        return_status = 0;
    } else if (mode == "stats") {
        generate_statistics_for_player_threads(player, n);
        return_status = 0;
    } else {
        std::cout << "invalid mode: " << mode << std::endl;
        std::cout << "valid modes are: traces, stats" << std::endl;
        return_status = -1;
    }
    delete player;
    return return_status;
}
