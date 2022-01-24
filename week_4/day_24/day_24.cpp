#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_map>
#include<sstream>
#include"utils.h"

// instructions and storage
enum struct ALU{inp, add, mul, div, mod, eql};
std::vector<long long> reg = {0,0,0,0};

// maps from string to instruction and storage
const std::unordered_map<std::string, ALU> fn = {{"inp",ALU::inp},{"add",ALU::add},{"mul",ALU::mul},{"div",ALU::div},{"mod",ALU::mod},{"eql",ALU::eql}};

// ALU functions
void inp(const std::string& a, std::stringstream& ss);
void add(const std::string& a, const std::string& b);
void mul(const std::string& a, const std::string& b);
void div(const std::string& a, const std::string& b);
void mod(const std::string& a, const std::string& b);
void eql(const std::string& a, const std::string& b);

// print
std::string print(const std::string& number);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" "};
    std::vector<std::vector<std::string>> input = read_input_2D("input_24", delimiters);

    // input stream
    std::stringstream ss;

    std::string max_number = "9 1 6 9 9 3 9 4 8 9 4 9 9 5";
    std::string min_number = "5 1 1 4 7 1 9 1 1 6 1 2 6 1";

    // insert model number into string stream
    ss.str(min_number);

    // run ALU
    for (const auto& line : input){

        switch (fn.at(line[0])){
            case ALU::inp : inp(line[1],ss)     ; break;
            case ALU::add : add(line[1],line[2]); break;
            case ALU::mul : mul(line[1],line[2]); break;
            case ALU::div : div(line[1],line[2]); break;
            case ALU::mod : mod(line[1],line[2]); break;
            case ALU::eql : eql(line[1],line[2]); break;
        }
    }

    if (reg[3]!=0){ std::cout << "Houston, we have a problem\n"; }

    // highest and lowest model number found by decompiling input. Explained in README.md 
    std::cout << "Answer (part 1): " << print(max_number) << std::endl;
    std::cout << "Answer (part 2): " << print(min_number) << std::endl;

    return 0;
}

// print number without " "
std::string print(const std::string& number){
    std::string output;

    for (const auto& c : number){
        if (c==' '){ continue; }
        output.push_back(c);
    }

    return output;
}

void inp(const std::string& a, std::stringstream& ss){
    ss >> reg[a[0]-'w'];
}

void add(const std::string& a, const std::string& b){
    
    // if not convertible integer, is register
    try { reg[a[0]-'w'] += std::stol(b); }
    catch (const std::invalid_argument&){ reg[a[0]-'w'] += reg[b[0]-'w']; }
}

void mul(const std::string& a, const std::string& b){
    
    // if not convertible integer, is register
    try { reg[a[0]-'w'] *= std::stol(b); }
    catch (const std::invalid_argument&){ reg[a[0]-'w'] *= reg[b[0]-'w']; }
}

void div(const std::string& a, const std::string& b){
    
    // if not convertible integer, is register
    try { reg[a[0]-'w'] /= std::stol(b); }
    catch (const std::invalid_argument&){ reg[a[0]-'w'] /= reg[b[0]-'w']; }
}

void mod(const std::string& a, const std::string& b){
    
    // if not convertible integer, is register
    try { reg[a[0]-'w'] %= std::stol(b); }
    catch (const std::invalid_argument&){ reg[a[0]-'w'] %= reg[b[0]-'w']; }
}

void eql(const std::string& a, const std::string& b){
    
    // if not convertible integer, is register
    try { reg[a[0]-'w'] = (reg[a[0]-'w']==std::stol(b)); }
    catch (const std::invalid_argument&){ reg[a[0]-'w'] = (reg[a[0]-'w']==reg[b[0]-'w']); }
}


