#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<numeric>
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

        // check depths in groups of 3 (ignore common steps from sum)
        if (input[i] > input[i-3]){ part_2++; }
    }

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}

// Thanks to another reddit user, /u/paul2718, std::inner_product is a convenient inbuilt function that 
// can shorted the code considerably. Of course you are now required to loop through the input twice.
void using_inner_product(){

    // read input into vector of strings.
    std::vector<int> input = input_to_int<int>(read_input("input", ""));

    // parameter breakdown:                                first1         last1          first2           init  op1            op2
    std::cout << "Answer (part 1): " << std::inner_product(input.begin(), input.end()-1, input.begin()+1, 0   , std::plus<>(), std::less<>()) << "\n";
    std::cout << "Answer (part 2): " << std::inner_product(input.begin(), input.end()-3, input.begin()+3, 0   , std::plus<>(), std::less<>()) << "\n";

    // first1, last1 - first range of elemets
    // first2        - beginning of second range
    // init          - initial value of the sum
    // op1           - takes return of op2 and accumulator(init) and produces a new value
    // op2           - compares one value from each range and produces a new value
}
