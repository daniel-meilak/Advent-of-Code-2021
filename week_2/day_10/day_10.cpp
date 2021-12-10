#include<iostream>
#include<list>
#include<string>
#include<vector>
#include<algorithm>
#include<numeric>
#include<unordered_map>
#include"../../Utils/utils.h"

const std::unordered_map<char,int> illegal_scoring = {
    {')',3},
    {']',57},
    {'}',1197},
    {'>',25137}
};

const std::unordered_map<char,int> complete_scoring = {
    {')',1},
    {']',2},
    {'}',3},
    {'>',4}
};

int main(){

    // read input into vector of strings.
    std::list<std::string> input = read_input<std::list>("input", "");

    // scoring for illegal and autocomplete characters
    int part_1 = 0;
    std::vector<long> auto_scores;
    auto_scores.reserve(input.size());

    // work through  line
    for (auto it=input.begin(); it!=input.end(); it++){
next_line:
        std::string open_chunks;
        open_chunks.reserve((*it).size());

        // work through chunks
        for (const char& c : *it){

            switch (c){
                // conveniently the close brackets are +1/+2 in ascii value
                case '[': case '{': case '<':
                    open_chunks.push_back(c+2);
                break;

                case '(':
                    open_chunks.push_back(c+1);
                break;

                default:

                    if (open_chunks.back() == c){ open_chunks.pop_back(); }
                    else {
                        // add score, remove line and go to next (break out of nested for)
                        part_1 += illegal_scoring.at(c);
                        it = input.erase(it);
                        goto next_line;
                    }
                break;
            }
        }

        // calculate and find autocomplete score
        auto_scores.push_back( std::accumulate(open_chunks.rbegin(), open_chunks.rend(), 0l, [&](long l, char r){return l*5l + complete_scoring.at(r);}) );
    }
    
    // autocomplete score is middle
    auto part_2 = auto_scores.begin() + auto_scores.size()/2;
    std::nth_element(auto_scores.begin(), part_2, auto_scores.end());

    std::cout << "Answer (part 1): " <<  part_1 << std::endl;
    std::cout << "Answer (part 2): " << *part_2 << std::endl;

    return 0;
}
