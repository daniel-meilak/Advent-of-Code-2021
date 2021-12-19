#include<iostream>
#include<vector>
#include<string>
#include<functional>
#include<list>
#include<unordered_map>
#include<unordered_set>
#include"../../Utils/utils.h"

// simple hash for vector<int>(3) (turn into string and use built-in string hash)
struct hash{
    size_t operator()(const std::vector<int>& key) const{
        return std::hash<std::string>()(std::to_string(key[0]) + std::to_string(key[1])+std::to_string(key[2]));
    }
};

struct scanner_t{

    std::vector<std::vector<int>> beacons;
    int axis = 0;
    std::vector<int> correction = {0,0,0};

    void rotate_axis();
    void change_axis();
    bool match(const std::unordered_set<std::vector<int>,hash>& other);
    void align();
};

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {","};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // build scanners
    std::list<scanner_t> scanners;

    scanner_t temp;
    for (const auto& line: input){

        if      (line.size() == 1){ temp.beacons.clear();                       }
        else if (line.size() == 3){ temp.beacons.push_back(input_to_int(line)); }
        else                      { scanners.push_back(temp);                   }
    }
    scanners.push_back(temp);

    // set of all beacons (start with scanner 0)
    std::unordered_set<std::vector<int>,hash> all_beacons;
    for (auto& beacon : scanners.front().beacons){ all_beacons.insert(beacon); }

    // try matching to all_beacons
    for (auto it=++scanners.begin(); it!=scanners.end(); it++){

        bool matched = false;
       
       // 6 axes
        for (int i=0; i<6; i++){

            it->change_axis();
            // 4 rotations about each axis
            for (int j=0; j<4; j++){
                it->rotate_axis();

                // check for 12 matching beacons
                if (it->match(all_beacons)){

                    // align all other beacons and add uniques to all_beacons
                    it->align();
                    for (auto& beacon : it->beacons){ all_beacons.insert(beacon); }
                    matched = true;
                    goto after_match;
                }
            }
        }
after_match:;
        // if no match made, try again at end
        if (!matched){
            it->axis = 0;
            scanners.push_back(*it);
            it = --scanners.erase(it);   
        }       
    }

    // find largest manhattan distance
    int part_2 = 0;
    for (auto it1=scanners.begin(); it1!=scanners.end(); it1++){
        for (auto it2=scanners.begin(); it2!=scanners.end(); it2++){

            if (it1 == it2){ continue; }
            part_2 = std::max(part_2,manhattan(it1->correction,it2->correction));
        }
    }

    std::cout << "Answer (part 1): " << all_beacons.size() << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}

// rotate 90 degrees about z-axis
void scanner_t::rotate_axis(){
    for (auto& beacon : beacons){ beacon = {-beacon[1],beacon[0],beacon[2]}; }
}

// explore all 6 axes by doing 4 90 degree rotations in y and 2 in x(+90, -90)
void scanner_t::change_axis(){

    switch(axis){
        
        case 0: case 1: case 2: case 3:
            for (auto& beacon : beacons){ beacon = {beacon[2],beacon[1],-beacon[0]}; }
            break;
        case 4: 
            for (auto& beacon : beacons){ beacon = {beacon[0],-beacon[2],beacon[1]}; }
            break;
        case 5:
            for (auto& beacon : beacons){ beacon = {beacon[0],-beacon[1],-beacon[2]}; }
            break;
    }

    axis++;
}

// finds all vectors between beacons and checks for 12+ mactching values
bool scanner_t::match(const std::unordered_set<std::vector<int>,hash>& other){

    std::unordered_map<std::vector<int>,int,hash> distances;
    std::vector<int> direction;

    for (const auto& b1 : other){
        for (const auto& b2 : beacons){

            direction = {b2[0]-b1[0],b2[1]-b1[1],b2[2]-b1[2]};

            // if any distance occurs 12 or more times, it is a match
            if (++distances[direction] == 4){
                correction = direction;
                return true;
            }
        }
    }

    return false;
}

// align beacons w.r.t. scanner 0 
void scanner_t::align(){

    for (auto& beacon: beacons){
        for (size_t i=0; i<3; i++){ beacon[i] -= correction[i]; }
    }
}
