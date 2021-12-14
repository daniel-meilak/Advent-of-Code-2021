#include<iostream>
#include<vector>
#include<string>
#include<climits>
#include<algorithm>
#include<map>
#include<unordered_map>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" -> "};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // read polymer template and insertion rules
    std::string polymer = input[0][0];
    std::unordered_map<std::string,std::string> rules;

    for (auto it=input.begin()+2; it!=input.end(); it++){
        rules[(*it)[0]] = (*it)[1];
    }

    // maps of polymer pairs and their n occurences
    std::unordered_map<std::string,long long> count, next, save;

    // fill count1 with initial polymer pairs
    for (size_t i=0; i<polymer.size()-1; i++){
        count[polymer.substr(i,2)]++;
    }

    const int steps = 40;
    // 10 steps of pair insertion
    for (int i=0; i<steps; i++){

        // look up insertion rule for each pair
        for (const auto& [pair,n] : count){

            // polymer insertion
            std::string insert = rules[pair];

            // fill count2 with next set of polymer pairs
            next[pair[0]+insert] += n;
            next[insert+pair[1]] += n;
        }

        // swap count1 and 2 and empty count2
        count = next;
        next.clear();

        // remember state after 10 steps for part 1
        if (i == 9){ save = count; }
    }

    // ordered map of polymer occurences (start with one of last polymer in init)
    std::map<char,long long> polymer_count1{{polymer.back(),1}}, polymer_count2{{polymer.back(),1}};

    // count by using first polymer in each pair
    for (const auto& [pair,n] : save  ){ polymer_count1[pair[0]] += n; }
    for (const auto& [pair,n] : count ){ polymer_count2[pair[0]] += n; }

    // find min max of map using lambda to sort values, not keys
    auto [min1,max1] = std::minmax_element(polymer_count1.begin(), polymer_count1.end(), [&](auto l, auto r){return l.second < r.second;});
    auto [min2,max2] = std::minmax_element(polymer_count2.begin(), polymer_count2.end(), [&](auto l, auto r){return l.second < r.second;});

    std::cout << "Answer (part 1): " << max1->second - min1->second << std::endl;
    std::cout << "Answer (part 2): " << max2->second - min2->second << std::endl;

    return 0;
}
