#include<iostream>
#include<vector>
#include<string>
#include<list>
#include<iterator>
#include<cctype>
#include"../../Utils/utils.h"

bool is_digit(char c){ return std::isdigit(c); };
bool is_pair(std::list<char>::iterator it);
bool explode(std::list<char>& number);
bool split(std::list<char>& number);
int magnitude(std::list<char>& number);
std::list<char> add(std::list<char> a, const std::list<char>& b);
std::list<char> reduce(std::list<char>& number);

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input_18");

    // store snailfish numbers in list for fast insertion/deletion
    std::vector<std::list<char>> numbers;
    for (const std::string& line: input){ numbers.push_back({line.begin(),line.end()}); }

    // sum snailfish numbers (part 1)
    std::list<char> sum = numbers[0];
    for (auto it=std::next(numbers.begin()); it!=numbers.end(); it++){

        // add next snail number
        sum = add(sum,*it);

        // reduce sum if required
        reduce(sum);
    }

    // find largest magnitude of any two summed numbers (part 2)
    int part_2 = 0;
    std::list<char> sum1,sum2;
    for (auto it1=numbers.begin(); it1!=numbers.end(); it1++){
        for (auto it2=numbers.begin(); it2!=numbers.end(); it2++){

            if (it1==it2){ continue; }

            sum1 = add(*it1,*it2);
            sum2 = add(*it2,*it1);
            reduce(sum1);
            reduce(sum2);

            part_2 = std::max(part_2, std::max(magnitude(sum1),magnitude(sum2)));
        }
    }

    std::cout << "Answer (part 1): " << magnitude(sum) << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}

std::list<char> add(std::list<char> a, const std::list<char>& b){

    a.insert(a.begin(),'[');                // front bracket
    a.insert(a.end(),',');                  // middle comma
    a.insert(a.end(),b.begin(),b.end());    // second term
    a.insert(a.end(),']');                  // back bracket

    return a;
}

std::list<char> reduce(std::list<char>& number){
    bool reduced = false;
    while (!reduced){
        
        if (explode(number)){ continue; }
        if (split(number)  ){ continue; }

        reduced = true;
    }

    return number;
}

bool explode(std::list<char>& number){

    int nests = 0;
    
    for (auto it=number.begin(); it!=number.end(); it++){
        if      (*it=='['){ nests++; }
        else if (*it==']'){ nests--; }

        // found explosion
        if (nests==5){

            // check for previous digit
            auto last = std::find_if(std::make_reverse_iterator(it), number.rend(), is_digit).base();
            if (last != number.begin()){ std::advance(last,-1); }

            auto start = it;

            // get a,b in [a,b] explosion
            std::string a,b;
            while (std::isdigit(*(++it))){ a.push_back(*it); }
            while (std::isdigit(*(++it))){ b.push_back(*it); }

            // check for next digit
            auto next = std::find_if(it, number.end() , is_digit);

            // if digits exist, add a and b
            std::string s;
            if (last != number.begin()){
                if (std::isdigit(*std::next(last,-1))){
                    s = std::to_string(std::stoi(std::basic_string(std::next(last,-1),std::next(last))) + std::stoi(a));
                    last = number.erase(std::next(last,-1),std::next(last));
                }
                else {
                    s = std::to_string((*last - '0') + std::stoi(a));
                    last = number.erase(last);
                }

                
                number.insert(last,s.begin(),s.end());
            }
            if (next != number.end() ){
                if (std::isdigit(*std::next(next))){
                    s = std::to_string(std::stoi(std::basic_string(next,std::next(next,2))) + std::stoi(b));
                    next = number.erase(next,std::next(next,2));
                }
                else {
                    s = std::to_string((*next - '0') + std::stoi(b));
                    next = number.erase(next);
                }
                number.insert(next,s.begin(),s.end());
            }

            // insert 0 and remove [a,b]
            number.insert(start,'0');
            number.erase(start,std::next(it));

            return true;
        }
    }
    return false;
}


bool split(std::list<char>& number){

    for (auto it=number.begin(); it!=number.end(); it++){

        if (std::isdigit(*it) && std::isdigit(*std::next(it))){

            // get digit
            int digit = std::stoi(std::basic_string(it,std::next(it,2)));

            // remove digit
            it = number.erase(it,std::next(it,2));

            // add new pair
            std::string s = "[" + std::to_string(digit/2) + "," + std::to_string((digit+1)/2) + "]";
            number.insert(it, s.begin(), s.end());
            
            return true;
        }
    }

    return false;
}

int magnitude(std::list<char>& number){

    bool found_magnitude = false;

    while (!found_magnitude){

        found_magnitude = true;

        for (auto it=number.begin(); it!=number.end(); it++){
            
            if (std::isdigit(*std::next(it)) && is_pair(it)){

                auto start = it;
                std::string a,b,magnitude;
                while (std::isdigit(*(++it))){ a.push_back(*it); }
                while (std::isdigit(*(++it))){ b.push_back(*it); }

                magnitude = std::to_string(3*std::stoi(a) + 2*std::stoi(b));

                number.insert(start,magnitude.begin(),magnitude.end());
                it = number.erase(start,std::next(it));

                found_magnitude = false;
            }
        }
    }

    return std::stoi(std::basic_string(number.begin(),number.end()));
}

bool is_pair(std::list<char>::iterator it){

    std::string s;
    
    while(s.size() != 2){
        if (!std::isdigit(*(++it))){ s.push_back(*it); }
    }

    return s == ",]";
}