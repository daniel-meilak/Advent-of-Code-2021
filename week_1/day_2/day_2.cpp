#include<iostream>
#include<vector>
#include<string>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" "};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // part 1
    int depth = 0;
    int pos   = 0;
    int aim   = 0;
    int X;

    for ( auto step : input ){

        // use first letter of forward/down/up
        switch (step[0][0]){
        case 'f': 
            X = std::stoi(step[1]);
            pos += X;
            depth += aim * X;
            break;
        
        case 'd':
            aim += std::stoi(step[1]);
            break;

        case 'u':
            aim -= std::stoi(step[1]);
            break;
        }
    }

    std::cout << "Answer (part 1): " << aim*pos   << std::endl;
    std::cout << "Answer (part 2): " << depth*pos << std::endl;

    return 0;
}
