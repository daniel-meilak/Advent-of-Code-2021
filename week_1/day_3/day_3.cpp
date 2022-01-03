#include<iostream>
#include<functional>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

std::string most_common_value(const std::vector<std::string>& input);
char common_digit(const std::vector<std::string>& input, const size_t& i, const  std::function<bool(int,float)>& sign);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_3");

    // part 1

    // string made up of most common digit
    std::string most_common, least_common;

    // find most common digits
    most_common = most_common_value(input);
    // flip values for least common digits
    for (const char& digit : most_common){
        if (digit == '1'){ least_common.push_back('0'); }
        else             { least_common.push_back('1'); }
    }

    // convert to integer type
    unsigned long gamma   = std::stoul(most_common,  nullptr, 2);
    unsigned long epsilon = std::stoul(least_common, nullptr, 2);

    std::cout << "Answer (part 1): " << gamma*epsilon << std::endl;

    // part 2

    // start with full input as candidates
    std::vector<std::string> oxygen_candidates = input;
    std::vector<std::string> CO2_candidates    = input;
    
    // search until only one candidate is left
    size_t i = 0;
    while (oxygen_candidates.size() != 1){
        
        // vector to hold intermediaries
        std::vector<std::string> temp;
        temp.reserve(oxygen_candidates.size());

        // find most common digit at current index
        char common = common_digit(oxygen_candidates,i,std::greater_equal());

        // check all candidates
        for (const auto& value : oxygen_candidates){

            // oxygen rating uses most common 
            if (value[i] == common){ temp.push_back(value); }
        }

        // start fresh for next digit
        oxygen_candidates = temp;
        i++;        
    }

    // same for CO2 candidates
    i = 0;
    while (CO2_candidates.size() != 1){

        // use temp to hold intermediary values
        std::vector<std::string> temp;
        temp.reserve(CO2_candidates.size());

        // find least common digit at current index
        char common = common_digit(CO2_candidates,i,std::less());

        // check all candidates
        for (const auto& value : CO2_candidates){

            // oxygen rating uses most common 
            if (value[i] == common){ temp.push_back(value); }
        }
    
        // start fresh for next digit
        CO2_candidates = temp;
        i++;
    }

    // convert final candidates to int 
    unsigned long oxygen_rating = std::stoul(oxygen_candidates[0],  nullptr, 2);
    unsigned long CO2_rating    = std::stoul(CO2_candidates[0],  nullptr, 2);

    std::cout << "Answer (part 2): " << oxygen_rating*CO2_rating << std::endl;

    return 0;
}

// find most common string 
std::string most_common_value(const std::vector<std::string>& input){

    // binary number length
    const size_t& length = input[0].size();

    // string made up of most common digit
    std::string most_common;

    for (size_t i=0; i<length; i++){
     
        // number of '1' in each position
        size_t count = 0;

        for (const auto& value : input){
            if (value[i] == '1'){ count++; }
        }

        // a>b returns an integer (int)1 or (int)0, adding the (char)'0' converts to char.
        most_common.push_back( (count >= input.size()/2.0)+'0' );
    }

    return most_common;
}

// find most/least common digit an a particular index
char common_digit(const std::vector<std::string>& input, const size_t& i, const std::function<bool(int,float)>& sign){

    char common;

    // number of '1' in each position
    size_t count = 0;

    for (const auto& value : input){
        if (value[i] == '1'){ count++; }
    }

    // sign is >= for oxygen or < for CO2. '0' converts to char
    common = sign(count,input.size()/2.0) + '0';

    return common;
}