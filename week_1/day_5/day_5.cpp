#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<numeric>
#include"utils.h"
#include"point.h"

int main(){

    // read input into vector of vector of int
    std::vector<std::string> delimiters = {",", " ", "->"};
    std::vector<std::vector<int>> input = input_to_int_2D(read_input_2D("input_5", delimiters));

    // map of points and no of crosses for only horizontal/vertical and all
    std::unordered_map<point,int> non_diag_crosses, all_crosses;

    // go through lines and find all crosses
    for (const auto& line : input){

        // find line gradient vector {x2-x1,y2-y1}
        point gradient = {line[2]-line[0], line[3]-line[1]};
        // check if horizontal or vertival
        bool h_or_v = gradient.x == 0 || gradient.y == 0;

        // reduce to smallest step (e.g. {5,-5} -> {1,-1})
        gradient /= std::gcd(gradient.x,gradient.y);

        point start = {line[0],line[1]};
        point end   = {line[2],line[3]};

        // add starting point to map 
        all_crosses[start]++;
        if (h_or_v){ non_diag_crosses[start]++; }

        // add rest of points on line to map
        while (start != end){
            start += gradient;

            // if horizontal or vertical
            if (h_or_v){ non_diag_crosses[start]++; }

            all_crosses[start]++;
        }
    }

    // find num of crossings with at least 1 overlap
    int part_1 = 0;
    int part_2 = 0;

    // only non diagonal (part 1)
    for ( auto const& [_, crosses] : non_diag_crosses ){
        if (crosses >= 2){ part_1++; }
    }

    // all crosses (part 2)
    for ( auto const& [_, crosses] : all_crosses ){
        if (crosses >= 2){ part_2++; }
    }

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}
