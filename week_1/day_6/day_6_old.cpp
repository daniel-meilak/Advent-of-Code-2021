#include<iostream>
#include<vector>
#include<string>
#include<numeric>
#include<algorithm>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of int.
    std::vector<int> input = input_to_int(read_input("input_6", ","));

    // vector of no of fish at each stage (index)
    std::vector<long> stages(9);

    // fill school from input
    for (const auto& fish_stage : input){
        stages[fish_stage]++;
    }

    // simulate school evolution for 80 days
    const int days = 256;
    long part_1, part_2;
    for (int i=0; i<days; i++){

        // move stages down by rotating the vector
        std::rotate(stages.begin(), stages.begin()+1, stages.end());

        // add back the reset fish to stage 6
        stages[6] += stages[8];        

        // at 80 days record number of fish for part_1
        if (i == 79){ part_1 = std::accumulate(stages.begin(),stages.end(),0l); }
    }

    // count all fish 
    part_2 = std::accumulate(stages.begin(),stages.end(),0l);

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}
