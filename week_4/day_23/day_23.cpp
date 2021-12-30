#include<iostream>
#include<climits>
#include<map>
#include<string>
#include<vector>
#include<unordered_map>
#include"../../Utils/utils.h"

const std::unordered_map<char,int> cost = {{'A',1},{'B',10},{'C',100},{'D',1000}};
const std::unordered_map<char,int> correct_room = {{'A',2},{'B',4},{'C',6},{'D',8}};
const std::vector<size_t> allowed_positions = {0,1,3,5,7,9,10};

struct state_t{
   std::map<char,std::string> rooms;
   std::string hall;

   // spaceship operator defines "==","!=",">","<",">=","<="
   auto operator<=>(const state_t&) const = default;

   state_t(std::string A, std::string B, std::string C, std::string D){
      rooms['A'] = A;
      rooms['B'] = B;
      rooms['C'] = C;
      rooms['D'] = D;
      hall = std::string(11,'.');
   }
};


bool finished(const std::unordered_map<char,std::string>& state);
bool can_move_from(char amphipod, const std::string& column);
bool can_move_to(char amphipod, const std::string& column);
int  top_index(const std::string& room);
int  destination_index(const std::string& room);
bool between(int index1, char amphipod, int index2);
bool clear_path(char amphipod, int index, const std::string& hall);
int  solve(state_t& state, std::map<state_t,int>& seen_states);

int main(){

   //  read input into vector of strings.
   std::vector<std::string> in = read_input("input_23", "");

   // create states for part 1 and part 2
   state_t part_1({in[2][3],in[3][3]},{in[2][5],in[3][5]},{in[2][7],in[3][7]},{in[2][9],in[3][9]});
   state_t part_2({in[2][3],'D','D',in[3][3]},{in[2][5],'C','B',in[3][5]},{in[2][7],'B','A',in[3][7]},{in[2][9],'A','C',in[3][9]});

   std::map<state_t,int> seen_states1, seen_states2;

   std::cout << "Answer (part 1): " << solve(part_1, seen_states1) << std::endl;
   std::cout << "Answer (part 2): " << solve(part_2, seen_states2) << std::endl;

   return 0;
}

// state is finished when amphipods are in the right columns
bool finished(const state_t& state){

   for (const auto& [amphipod,column] : state.rooms){
      for (const char& c : column){
         if (c != amphipod){ return false; }
      }
   }
   return true;
}

// check if amphipod is in wrong column
bool can_move_from(char amphipod, const std::string& column){

   for (const char& c : column){
      if (c!=amphipod && c!='.'){ return true; }
   }
   return false;
}

// check if amphipod can move into column
bool can_move_to(char amphipod, const std::string& column){

   for (const char& c : column){
      if (c!=amphipod && c!='.'){ return false; }
   }
   return true;
}

// get index of first amphipod in room
int top_index(const std::string& room){
   for (size_t i=0; i<room.size(); i++){
      if (room[i]!='.'){ return static_cast<int>(i); }
   }
   return INT_MAX;
}

// get index of last empty spot in room
int destination_index(const std::string& room){
   for (int i=static_cast<int>(room.size())-1; i>=0; i--){
      if (room[i]=='.'){ return i; }
   }
   return INT_MAX;
}

// check that amphipod should lie between two indexes
bool between(int index1, char amphipod, int index2){
   return (correct_room.at(amphipod)<index1 && index1<index2) || (index2<index1 && index1<correct_room.at(amphipod));
}

// check if path to correct room is clear
bool clear_path(char amphipod, int index, const std::string& hall){
   for (int i=0; i<static_cast<int>(hall.size()); i++){
      if (between(i,amphipod,index) && hall[i]!='.'){ return false; }
   }
   return true;
}

int solve(state_t& state, std::map<state_t,int>& seen_states){

   auto& rooms = state.rooms;
   auto& hall  = state.hall;

   // if finished, cost does not increase
   if (finished(state)){ return 0; }

   // if state has been seen, get last calculated cost
   if (seen_states.contains(state)){ return seen_states.at(state); }

   // create copy
   state_t copy = state;

   // move to destination if possible
   for (size_t i=0; i<hall.size(); i++){
      char amphipod = hall[i];
      
      if (amphipod!='.' && can_move_to(amphipod,rooms.at(amphipod)) && clear_path(amphipod,i,hall)){
         
         // calculate distance and cost for move
         int dest     = destination_index(rooms.at(amphipod));
         int distance = dest + 1 + abs(correct_room.at(amphipod)-i);
         int new_cost = cost.at(amphipod) * distance;

         // update state
         hall[i] = '.';

         // create new state
         state_t new_state = state;
         new_state.rooms[amphipod][dest] = amphipod;

         return new_cost + solve(new_state, seen_states);
      }
   }

   // move out of room if possible
   int answer = 1000000;
   for (auto& [amphipod,room] : rooms){
      
      // check if amphipod isn't in correct room
      if (!can_move_from(amphipod, room)){ continue; }

      // check if room is full
      int index = top_index(room);
      if (index == INT_MAX){ continue; }

      char moving_amphi = room[index];
      // find first empty spot
      for (const size_t pos : allowed_positions){
         if (hall[pos]!='.'){ continue; }

         if (clear_path(amphipod, pos, hall)){
            int distance   = index + 1 + abs(pos - correct_room.at(amphipod));
            
            // create new state
            state_t new_state = state;
            new_state.hall[pos] = moving_amphi;
            new_state.rooms[amphipod][index] = '.';

            answer = std::min(answer, cost.at(moving_amphi)*distance + solve(new_state, seen_states)); 
         }
      }
   }
   seen_states[copy] = answer;

   return answer;
}