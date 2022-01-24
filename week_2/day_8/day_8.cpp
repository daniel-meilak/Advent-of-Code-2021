#include<iostream>
#include<vector>
#include<cmath>
#include<string>
#include<unordered_map>
#include"utils.h"

// table of ID to digit (explained in README.md)
const std::unordered_map<int,int> table = {
    {42,0},
    {17,1},
    {34,2},
    {39,3},
    {30,4},
    {37,5},
    {41,6},
    {25,7},
    {49,8},
    {45,9}
};

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" ", "|"};
    std::vector<std::vector<std::string>> input = read_input_2D("input_8", delimiters);

    // count number of 1,4,7,8 in output (lengths 2,3,4 and 7) - part 1
    // add up deciphered output - part 2
    int part_1 = 0;
    int part_2 = 0;
    for ( auto& line : input ){

        // only check output
        for (int i=10; i<14; i++){
            const size_t& length = line[i].size();
            if ( length <= 4ul || length == 7ul ){ part_1++; }
        }

        // count up number of each segment in signal pattern
        std::unordered_map<char,int> key{{'a',0},{'b',0},{'c',0},{'d',0},{'e',0},{'f',0},{'g',0}};
        for (int i=0; i<10; i++){
            for (const char& segment : line[i]){ key[segment]++; }
        }

        // work out integer output
        for (int i=10; i<14; i++){
            int id = 0;

            // find the pattern id (sum of segment occurences)
            for (const char& c : line[i]){ id += key[c]; }

            // using table, we can find the correspoding digit from the id
            part_2 += table.at(id) * std::pow(10,3-(i-10));
        }
    }

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}

