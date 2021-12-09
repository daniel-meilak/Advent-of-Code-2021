#include<iostream>
#include<vector>
#include<list>
#include<string>
#include<algorithm>
#include<functional>
#include<numeric>
#include<unordered_map>
#include"../../Utils/utils.h"
#include"../../Utils/point.h"

// bingo card struct
struct card_t{

    // 2D vector of numbers and bool (initialise as 5x5)
    std::vector<std::vector<int>> sheet{5,std::vector<int>(5)};
    std::vector<std::vector<bool>> crossed{5,std::vector<bool>(5,false)};

    // unordered map containing all numbers in sheet and location
    std::unordered_map<int,point> values;

    // check if row/col at pos has been completed
    bool completed_card( const int& x, const int& y ){

        // check row 
        if (std::accumulate(crossed[x].begin(), crossed[x].end(), true, std::logical_and())){ return true; }

        // check col
        bool completed = true;

        for (size_t i=0; i<5; i++){
            completed &= crossed[i][y];
        }

        return completed;
    }

    int sum_unmarked(){

        int sum = 0;
        for ( int i=0; i<5; i++ ){
            for ( int j=0; j<5; j++ ){
                if (!crossed[i][j]){ sum += sheet[i][j]; }
            }
        }

        return sum;
    }
};

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {","," "};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // list of called out values
    std::vector<int> call_outs = input_to_int(input[0]);

    // all bingo cards (list for fast insertion and removal, random access not required)
    std::list<card_t> bingo_cards;

    // fill out bingo cards
    card_t temp;
    int fill_row = 0;
    const size_t& size = input.size();
    for (size_t i=2; i<size; i++){

        // at an empty line, add bingo card to pack and start next
        if (input[i].empty()){
            bingo_cards.push_back(temp);
            temp.values.clear();
            fill_row = 0;
            continue;
        }

        // fill a row of values in bingo card
        for (int j=0; j<5; j++){

            int num = std::stoi(input[i][j]);
            temp.sheet[fill_row][j] = num;

            // keep track of value position
            temp.values.insert( {num,{fill_row,j}} );
        }

        // move on to new row in bingo card
        fill_row++;
    }
    // push back last bingo card
    bingo_cards.push_back(temp);

    // go through callouts and find winning card
    int first_score = 0;
    int final_score = 0;
    bool first_score_set = false;
    for (const auto& call : call_outs){

        // check each card for call
        for (auto card = bingo_cards.begin(); card != bingo_cards.end();){

            // get position of call in card
            const auto& call_pos = card->values.find(call);

            // if call_pos == card.values.end(), call is not on card
            if (call_pos == card->values.end()){
                card++;
                continue;
            }

            const int& x = call_pos->second.x;
            const int& y = call_pos->second.y;

            // cross out value on card
            card->crossed[x][y] = true;

            // check if card has won
            if (card->completed_card(x,y)){

                // score is the sum of unmarked numbers * last call
                // only set the first score once
                if (!first_score_set){
                    first_score     = card->sum_unmarked() * call;
                    first_score_set = true;
                }
                else {
                    final_score = card->sum_unmarked() * call;
                }     

                // remove card from bingo_cards (returns next card)
                card = bingo_cards.erase(card);
            }
            // else move to next card
            else { card++; }
        }
    }

    std::cout << "Answer (part 1): " << first_score << std::endl;
    std::cout << "Answer (part 2): " << final_score << std::endl;

    return 0;
}
