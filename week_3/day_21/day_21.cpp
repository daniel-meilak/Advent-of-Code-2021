#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include"utils.h"

using ullong = unsigned long long;

struct game_t{
    int score1 = 0;
    int score2 = 0;

    int pos1;
    int pos2;

    // who is playing. 0 = player 1, 1 = player 2
    bool who = 0;

    game_t(const game_t& game) = default;
    game_t(int pos1, int pos2): pos1(pos1), pos2(pos2){};

    // spaceship operator defines "==","!=",">","<",">=","<="
    auto operator<=>(const game_t&) const = default;
};

// hash for storage in map, turn into std::string and use std::hash<std::string>
struct hash{
    std::size_t operator()(const game_t& game) const{
        return std::hash<std::string>()(std::to_string(game.score1)+std::to_string(game.score2)+std::to_string(game.pos1)
                                       +std::to_string(game.pos2)  +std::to_string(game.who));
    }
};

// map of number of outcomes for rolling 3 3-sided dice
const std::unordered_map<int,int> outcomes = {{3,1},{4,3},{5,6},{6,7},{7,6},{8,3},{9,1}};

bool play(game_t& game, int& die);
void play2(std::unordered_map<game_t,ullong,hash>& all_games, ullong& wins1, ullong& wins2);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"Player "," starting position: "};
    std::vector<std::vector<int>> input = input_to_int_2D(read_input_2D("input_21", delimiters));

    game_t game(input[0][1],input[1][1]);
    int die = 0;

    // part 1
    while(play(game, die)){}
    int part_1 = std::min(game.score1,game.score2)*die; 

    // part 2
    // map of game and number of occurences (in all universes)
    std::unordered_map<game_t,ullong,hash> all_games;
    all_games[game_t(input[0][1],input[1][1])] = 1;

    // number of wins
    ullong wins1 = 0, wins2 = 0;

    while(!all_games.empty()){

        // create all games, play and add back if not won
        play2(all_games,wins1,wins2);
    }

    ullong part_2 = std::max(wins1,wins2);

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}

bool play(game_t& game, int& die){

    if (game.who){
        game.pos2    = ((game.pos2 + (die*3) + 5 ) % 10) + 1;
        game.score2 += game.pos2;
    }
    else {
        game.pos1    = ((game.pos1 + (die*3) + 5 ) % 10) + 1;
        game.score1 += game.pos1;
    }

    game.who = !game.who;
    die   += 3;

    return game.score1 < 1000 && game.score2 < 1000;
}

void play2(std::unordered_map<game_t,ullong,hash>& all_games, ullong& wins1, ullong& wins2){

    // next set of games
    std::unordered_map<game_t,ullong,hash> next_games;

    for (const auto& [game,identicals] : all_games){
        for (int i=3; i<=9; i++){
            
            game_t copy = game;
            if (game.who){
                copy.pos2    = ((copy.pos2 + i -1) % 10) + 1;
                copy.score2 += copy.pos2;
            }
            else {
                copy.pos1    = ((copy.pos1 + i -1) % 10) + 1;
                copy.score1 += copy.pos1;
            }
            copy.who = !copy.who;
            ullong new_identicals = identicals*outcomes.at(i);

            if      (copy.score1 >= 21){ wins1 += new_identicals; }
            else if (copy.score2 >= 21){ wins2 += new_identicals; }
            else    { next_games[copy] += new_identicals; }
        }
    }

    // update all games
    all_games.swap(next_games);
}