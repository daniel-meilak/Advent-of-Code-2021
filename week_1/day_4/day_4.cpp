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

// box in bingo card to hold int(value) and bool(crossed out or not)
struct box_t{
    int num;
    bool crossed_out = false;
};

// logical && for crossed_out in box_t type
constexpr bool box_and(const bool& lhs, const box_t& rhs){
    return lhs && rhs.crossed_out;
}

// bingo card struct
struct card_t{

    // 2D vector of boxes (initialise as 5x5)
    std::vector<std::vector<box_t>> sheet{5,std::vector<box_t>(5)};

    // unordered map containing all numbers in sheet and location
    std::unordered_map<int,point> values;

    // check if row/col at pos has been completed
    bool completed_card( const int& x, const int& y ){

        // check row 
        if (std::accumulate(sheet[x].begin(), sheet[x].end(), true, box_and)){ return true; }

        // check col
        bool completed = true;

        for (size_t i=0; i<5; i++){
            completed &= sheet[i][y].crossed_out;
        }

        return completed;
    }

    int sum_unmarked(){

        int sum = 0;
        for ( const auto& row : sheet){
            for (const auto& box : row){
                if (!box.crossed_out){ sum += box.num; }
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
    std::vector<int> call_outs = input_to_int<int>(input[0]);

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
            temp.sheet[fill_row][j].num = num;

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
            card->sheet[x][y].crossed_out = true;

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
