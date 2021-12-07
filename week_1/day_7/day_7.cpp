#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<numeric>
#include"../../Utils/utils.h"

int triangle_distance(int n){ return n*(n+1)/2; }

int main(){

    // read input into vector of int.
    std::vector<int> input = input_to_int(read_input("input", ","));

    // task is to find the median value
    auto middle = input.begin() + (input.end() - input.begin())/2;

    // std::nth_element finds the sorted value at middle position
    // (without sorting the rest of the vector)
    std::nth_element(input.begin(), middle, input.end());

    int median;
    // if odd middle value is median
    if ((input.end()-input.begin())%2 != 0){ median = *middle; }
    // else even so find lower middle and average with upper
    else {
        auto lower_middle = std::max_element(input.begin(), middle);
        median = (*lower_middle + *middle)/2;
    }

    // in testing part 1, the mean seemed to give a close answer for part 2
    float average = (std::accumulate(input.begin(),input.end(),0.0)/input.size());
    
    // try the values above and below average
    int upper = (int)std::ceil(average);
    int lower = (int)std::floor(average);

    // to calcualte fuel, find sum of distances to middle
    int part_1 = 0, part_2;
    int upper_fuel = 0, lower_fuel = 0;
    for (const auto& pos : input){

        // part 1 uses euclidian distance
        part_1 += std::abs(median - pos);

        // part 2 uses the triangle distance n*(n+1)/2
        upper_fuel += triangle_distance(std::abs(upper - pos));
        lower_fuel += triangle_distance(std::abs(lower - pos));
    }

    // choose whichever is lower
    part_2 = upper_fuel < lower_fuel ? upper_fuel : lower_fuel;

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}