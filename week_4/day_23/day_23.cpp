#include<iostream>
#include<vector>
#include<string>
#include<cmath>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<map>
#include<utility>
#include<cctype>
#include<deque>
#include"../../Utils/utils.h"
#include"../../Utils/point.h"

const std::vector<point> cardinals  = {{1,0}, {-1,0}, {0,1}, {0,-1}};
const std::unordered_set<point> disallowed = {{3,1},{5,1},{7,1},{9,1}};
const std::unordered_map<char,int> correct_room = {{'A',3},{'B',5},{'C',7},{'D',9}};

std::vector<point> get_paths(const std::vector<std::string>& input, const std::unordered_map<point,std::vector<point>>& neighbours, const std::map<point,char>& positions, const point& pos, char letter);

int main(){

    // read inputs into vector of strings.
    std::vector<std::string> input[2] = {read_input("input1", ""), read_input("input2", "")};

    std::unordered_map<point,std::vector<point>> neighbours[2];
    std::map<point,char> amphi_pos[2];
    int final_energy[2];

    // end states
    const std::map<point,char> end_state[2] ={
        // part 1
        { {{3,2},'A'}, {{3,3},'A'}, {{5,2},'B'}, {{5,3},'B'}, {{7,2},'C'}, {{7,3},'C'}, {{9,2},'D'}, {{9,3},'D'} },

        // part 2
        { {{3,2},'A'}, {{3,3},'A'}, {{3,4},'A'}, {{3,5},'A'}, {{5,2},'B'}, {{5,3},'B'}, {{5,4},'B'}, {{5,5},'B'},
          {{7,2},'C'}, {{7,3},'C'}, {{7,4},'C'}, {{7,5},'C'}, {{9,2},'D'}, {{9,3},'D'}, {{9,4},'D'}, {{9,5},'D'} }
    };

    // do both part 1 and 2
    for (int part=0; part<2; part++){

        // build neighbouring rooms and amphipod positions
        for (size_t y=0; y<input[part].size(); y++){
            for (size_t x=0; x<input[part][y].size(); x++){

                char  c = input[part][y][x];
                point p = {(int)x,(int)y};
                
                // ignore walls or points
                if (c == '#' || c == ' '){ continue; }
                // add amphipods
                else if (std::isupper(c)){ amphi_pos[part][p] = c; }

                // add room and neighbours
                for (const auto& dir : cardinals){
                    
                    point next = dir + p;

                    if ( input[part][next.y][next.x] != '#' ){ neighbours[part][p].push_back(next); } 
                }
            }
        }

        // simulate all possible configurations
        std::map<std::map<point,char>,int> seen_states = {{amphi_pos[part],0}};
        std::deque<std::map<point,char>> states = {amphi_pos[part]};
        
        while (!states.empty()){

            std::map<point,char> current = states.front();
            states.pop_front();

            if (current == end_state[part]){ break; }

            // work through all movable amphipods
            for (const auto& [pos,letter] : current){

                // amphipod in correct pos, dont move
                if (pos.x == correct_room.at(letter)){

                    bool done = true;
                    for (int j=pos.y+1; j<=(part==0?3:5); j++){
                        if (input[part][j][pos.x]!=letter){
                            done = false;
                            break;
                        }
                    }

                    if (done){ continue; }
                }

                // find all possible positions to move to
                for (const auto stop : get_paths(input[part],neighbours[part],current,pos,letter)){

                    // copy state and move letter from pos to stop
                    std::map<point,char> copy = current;
                    copy[stop] = letter;
                    copy.erase(pos);

                    // calculate energy cost of moving
                    int energy = seen_states.at(current) + manhattan(pos,stop)*std::pow(10,letter-'A');

                    // if state is new or better than identical older state, add/replace with new energy
                    if (!seen_states.contains(copy) || seen_states.at(copy) > energy){
                        seen_states[copy] = energy;
                    } 

                    // explore new state
                    states.push_back(copy);
                }
            }            
        }

        final_energy[part] = seen_states.at(end_state[part]);
    }

    std::cout << "Answer (part 1): " << final_energy[0] << std::endl;
    std::cout << "Answer (part 2): " << final_energy[1] << std::endl;

    return 0;
}

std::vector<point> get_paths(const std::vector<std::string>& input, const std::unordered_map<point,std::vector<point>>& neighbours, const std::map<point,char>& positions, const point& pos, char letter){

    std::deque<point> path = {pos};
    std::unordered_set<point> visited;
    std::vector<point> stops;

    while (!path.empty()){

        point current = path.front();
        path.pop_front();

        for (const auto& next : neighbours.at(current)){

            // skip occupied and visited steps
            if (!positions.contains(next) && !visited.contains(next)){ visited.insert(next); }
            else { continue; }

            // add next to path to find next steps
            path.push_back(next);

            // check if next can be stopped at
            // cannot move from hall to hall
            if ( (pos.y==1 && next.y==1) ){ continue; }
            // if moving to room 
            else if ( next.y != 1 ){

                // must be correct room
                if ( next.x != correct_room.at(letter) ){ continue; }

                // must move to bottom of room
                if ( input[next.y+1][next.x]!='#' && !positions.contains({next.x,next.y+1}) ){ continue; }

                // room must contain only correct letters
                if (positions.contains({next.x,5}) && positions.at({next.x,5})!=letter){ continue; }
                if (positions.contains({next.x,4}) && positions.at({next.x,4})!=letter){ continue; }
                if (positions.contains({next.x,3}) && positions.at({next.x,3})!=letter){ continue; }
                if (positions.contains({next.x,2}) && positions.at({next.x,2})!=letter){ continue; }

                // all checks pass add to list of possible positions
                stops.push_back(next);
            }
            // moving to hall, dont allow stopping in front of rooms
            else if ( disallowed.contains(next) ){ continue; }
            // all checks pass, add to list of possible positions
            else { stops.push_back(next); }
        }
    }

    return stops;
}