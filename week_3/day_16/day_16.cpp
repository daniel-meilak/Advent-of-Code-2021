#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<numeric>
#include<bitset>
#include<functional>
#include<unordered_map>
#include"../../Utils/utils.h"

// map of type_ID to operator
const std::unordered_map<int, std::function<long(std::vector<long>&)>> operators = {
   {0, [](auto& vec){ return  std::accumulate (vec.begin(), vec.end(), 0l); }                   }, // plus
   {1, [](auto& vec){ return  std::accumulate (vec.begin(), vec.end(), 1l,std::multiplies()); } }, // multiply
   {2, [](auto& vec){ return *std::min_element(vec.begin(), vec.end()); }                       }, // minimum
   {3, [](auto& vec){ return *std::max_element(vec.begin(), vec.end()); }                       }, // maximum
   {5, [](auto& vec){ return  vec.front() >  vec.back(); }                                      }, // greater than
   {6, [](auto& vec){ return  vec.front() <  vec.back(); }                                      }, // less than
   {7, [](auto& vec){ return  vec.front() == vec.back(); }                                      }  // equal
};

long read_packet(const std::string binary, int& version_sum, size_t& read_pos);

int main(){

   // read input into vector of strings.
   std::string input = read_line("input_16");

   // convert input hex to binary representation
   std::string binary;
   for (const char& c : input){
      binary += std::bitset<4>((c >= 'A') ? (c - 'A' + 10) : (c - '0')).to_string();
   }

   size_t start_pos = 0ul;

   // calculate version sum and expression
   int part_1 = 0;
   long part_2 = read_packet(binary,part_1, start_pos);

   std::cout << "Answer (part 1): " << part_1 << std::endl;
   std::cout << "Answer (part 2): " << part_2 << std::endl;

   return 0;
}

long read_packet(const std::string binary, int& version_sum, size_t& read_pos){

   long output;

   // first three bits are packet version
   version_sum += std::stol(binary.substr(read_pos,3), nullptr, 2);
   read_pos += 6;

   // next three bits are type ID
   int type_ID = std::stoi(binary.substr(read_pos-3,3), nullptr, 2);

   switch (type_ID){
      // literal
      case 4:{
            
         std::string s;
         bool end_of_literal = false;
         while (!end_of_literal){
         
            if (binary[read_pos] == '0'){ end_of_literal = true; }
            s += binary.substr(read_pos+1,4);
            read_pos += 5;
         }

         // calculate op(result)
         output = stoul(s,nullptr,2);
         break;
      }
      // operator
      default:{

         auto op = operators.at(type_ID);

         // keep memory of calculated literals
         std::vector<long> memory;

         // read by length of packets
         if (binary[read_pos] == '0'){
            
            // total length of contained subpackets
            size_t read_length = read_pos + std::stoul(binary.substr(read_pos+1,15), nullptr, 2) + 16;
            read_pos += 16;

            // read packets until length is exceeded
            while (read_pos < read_length){
               memory.push_back(read_packet(binary,version_sum,read_pos));
            }
         }
         // read by number of packets
         else {
            
            // number of sub-packets to process
            int to_process = std::stoi(binary.substr(read_pos+1,11), nullptr, 2);
            read_pos += 12;

            for (int i=0; i<to_process; i++){
               memory.push_back(read_packet(binary,version_sum,read_pos));
            }
         }

         // calculate operation
         output = op(memory);
         break;
      }
   }
   return output;
}

