#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<unordered_set>
#include<cstdlib>
#include"utils.h"

void find_segment(const std::string& digit_a, const std::string& digit_b, char c, std::unordered_map<char,char>& cipher, std::string& known_segments);
void find_digit(std::unordered_set<std::string>& set, int n1, int n2, std::vector<std::string>& numbers, std::unordered_map<std::string,char>& look_up);
int decipher( std::vector<std::string>& display );

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

        part_2 += decipher(line);
    }

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}

int decipher( std::vector<std::string>& display ){

    // sort the segments in alphabetical order
    for ( std::string& number : display ){ std::sort(number.begin(), number.end()); }

    // vector to hold related segments
    std::unordered_map<char,char> cipher(7);

    // vector to hold numbers. each map indicates which segments are on
    std::vector<std::string> numbers(10);

    // loop-up for digit from ordered segments
    std::unordered_map<std::string,char> look_up;

    // unknowns (implemented as sets for easy removal)
    std::unordered_set<std::string> n0_6_9, n2_3_5;

    // known ciphered segments
    std::string known_segments;

    // work through unique signal pattern
    for (int i=0; i<10; i++){

        const std::string& signal_pattern = display[i];
        switch (signal_pattern.size()){
            // 1 has 2 segments
            case 2ul:
                numbers[1] = signal_pattern;
                look_up[signal_pattern] = '1';
                break;        
            // 7 has 3 segments
            case 3ul:
                numbers[7] = signal_pattern;
                look_up[signal_pattern] = '7';
                break;
            // 4 has 4 segments
            case 4ul:
                numbers[4] = signal_pattern;
                look_up[signal_pattern] = '4';
                break;
            // 2,3,5 have 5 segments
            case 5ul:
                n2_3_5.insert(signal_pattern);
                break;
            // 0,6,9 have 6 segments
            case 6ul:
                n0_6_9.insert(signal_pattern);
                break;
            case 7ul:
                numbers[8] = signal_pattern;
                look_up[signal_pattern] = '8';
                break;
        }
    }
    // known numbers: 1,4,7,8       known letters:

    // difference between 1&7 is a
    find_segment(numbers[7], numbers[1], 'a', cipher, known_segments);
    // known numbers: 1,4,7,8       known letters: a

    // check 0,6,9 - only 9 has all segments in 4
    find_digit(n0_6_9, 9, 4, numbers, look_up);
    // known numbers: 1,4,7,8,9       known letters: a

    // diference between 8&9 is e
    find_segment(numbers[8], numbers[9], 'e', cipher, known_segments);
    // known numbers: 1,4,7,8,9       known letters: a,e

    // difference between 9&4 is a&g, we already know a
    for (const char& segment : numbers[9]){

        const auto pos = numbers[4].find(segment);

        // if segment is not in 4 and it is not cipher[a] -> it is g
        if (pos == std::string::npos && segment != cipher['a']){
            cipher['g'] = segment;
            known_segments.push_back(segment);
            break;
        }
    }
    // known numbers: 1,4,7,8,9       known letters: a,e,g

    // out of 2,3,5 only 2 contains e
    for (const std::string& signal_pattern : n2_3_5){
        
        if (signal_pattern.find(cipher['e']) != std::string::npos){
            numbers[2] = signal_pattern;
            look_up[signal_pattern] = '2';
            n2_3_5.erase(signal_pattern);
            break;
        }
    }
    // known numbers: 1,2,4,7,8,9       known letters: a,e,g

    // compare 1&2, 2 contains c but not f
    if (numbers[2].find(numbers[1][0]) == std::string::npos){
        cipher['f'] = numbers[1][0];
        cipher['c'] = numbers[1][1];
    }
    else {
        cipher['f'] = numbers[1][1];
        cipher['c'] = numbers[1][0];
    }
    known_segments += numbers[1];
    // known numbers: 1,2,4,7,8,9       known letters: a,c,e,f,g

    // check 3,5 - only 3 has all segments in 7
    find_digit(n2_3_5, 3, 7, numbers, look_up);
    numbers[5] = *n2_3_5.begin();
    look_up[*n2_3_5.begin()] = '5';
    // known numbers: 1,2,3,4,5,7,8,9       known letters: a,c,e,f,g

    // check 0,6 - only 0 has all segments in 7
    find_digit(n0_6_9, 0, 7, numbers, look_up);
    numbers[6] = *n0_6_9.begin();
    look_up[*n0_6_9.begin()] = '6';
    // known numbers: 0,1,2,3,4,5,6,7,8,9       known letters: a,c,e,f,g

    // difference between 0&8 is d
    find_segment(numbers[8], numbers[0], 'd', cipher, known_segments);
    // known numbers: 0,1,2,3,4,5,6,7,8,9       known letters: a,c,d,e,f,g

    // difference between 3&9 is b
    find_segment(numbers[9], numbers[3], 'b', cipher, known_segments);
    // known numbers: 0,1,2,3,4,5,6,7,8,9       known letters: a,b,c,d,e,f,g

    // now we can decipher the output
    std::string value;
    for (int i=10; i<14; i++){
        value.push_back(look_up[display[i]]);
    }

    return std::stoi(value);
}

// compare two signal patters with one difference. find the difference.
void find_segment(const std::string& digit_a, const std::string& digit_b, char c, std::unordered_map<char,char>& cipher, std::string& known_segments){

    for (const char& segment : digit_a){

        // if segment is not in digit_b, it is c
        if (digit_b.find(segment) == std::string::npos){
            cipher[c] = segment;
            known_segments.push_back(segment);
            break;
        }
    }
}

// in a set of digits, only one contains all segments of a separate digit. find that digit.
void find_digit(std::unordered_set<std::string>& set, int n1, int n2, std::vector<std::string>& numbers, std::unordered_map<std::string,char>& look_up){

    for (const std::string& signal_pattern : set){

        // flag for finding n
        bool is_n1 = true;

        for (const char& segment : numbers[n2]){
            if (signal_pattern.find(segment) == std::string::npos){
                is_n1 = false;
                break;
            }
        }

        // if is_n remains true, we've found n
        if (is_n1){
            numbers[n1] = signal_pattern;
            look_up[signal_pattern] = n1+'0';
            set.erase(signal_pattern);
            break;
        }
    }
}