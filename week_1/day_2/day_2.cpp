#include<iostream>
#include<vector>
#include<string>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" "};
    std::vector<std::vector<std::string>> input = read_input_2D("input_2", delimiters);

    // part 1
    int depth = 0;
    int pos   = 0;
    int aim   = 0;
    int X;

    for ( auto step : input ){

        // convert string value to int
        X = std::stoi(step[1]);

        // use first letter of forward/down/up
        switch (step[0][0]){
        case 'f': 
            pos += X;
            depth += aim * X;
            break;
        
        case 'd':
            aim += X;
            break;

        case 'u':
            aim -= X;
            break;
        }
    }

    // aim in part 2 is the same as depth in part 1, and pos remains unchanged
    std::cout << "Answer (part 1): " << aim*pos   << std::endl;
    std::cout << "Answer (part 2): " << depth*pos << std::endl;

    return 0;
}
