#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<int> input = input_to_int<int>(read_input("input", ""));

    size_t size = input.size();
    
    // number of increments
    int part_1 = 0;
    int part_2 = 0;

    // check first two steps
    if (input[1] > input[0]){ part_1++; }
    if (input[2] > input[1]){ part_1++; }
    
    // loop through input from 4th depth
    for (size_t i = 3; i < size; i++){
        
        // check consecutive depths
        if (input[i] > input[i-1]){ part_1++; }

        // check depths in groups of 3
        if ( (input[i]+input[i-1]+input[i-2]) > (input[i-1]+input[i-2]+input[i-3]) ){ part_2++; }
    }

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}
