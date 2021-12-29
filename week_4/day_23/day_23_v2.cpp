#include<iostream>
#include<vector>
#include<string>
#include<climits>
#include<cmath>
#include<unordered_map>
#include<array>
#include"../../Utils/utils.h"

constexpr std::array<int,4> correct_columns = {3,5,7,9};
constexpr std::array<int,7> hallway_positions = {1,2,4,6,8,10,11};

// struct to hold state infomration
struct state{
   std::vector<std::string> burrow;
   int energy = 0;
   int in_place = 0;
   bool extended = false;
};

// forward function declarations
bool can_enter(const state& current, char letter, int col);
bool can_exit(const state& current, char letter, int col);
int enter(state& current, int start, int end, char letter);
int exit(state& current, int start, int end);
void rearrange(state current, int& energy);

int main(){

   //  read input into vector of strings.
   std::vector<std::string> input[2] = {read_input("input_23", ""),read_input("input_23", "")};
   input[1].insert(std::next(input[1].end(),-2), "  #D#C#B#A#");
   input[1].insert(std::next(input[1].end(),-2), "  #D#B#A#C#");

   state part_1, part_2;
   part_1.burrow = input[0];
   part_2.burrow = input[1];
   part_2.extended = true;
  
   int min_cost[2] = {INT_MIN, INT_MIN};
   rearrange(part_1,min_cost[0]);
   rearrange(part_2,min_cost[1]); 

   std::cout << "Answer (part 1): " << min_cost[0] << std::endl;
   std::cout << "Answer (part 2): " << min_cost[1] << std::endl;

   return 0;
}

bool can_enter(const state& current, char letter, int col){

   // all steps in room must be empty or contining the correct letter
   if (current.extended && current.burrow[5][col]!='.' && current.burrow[5][col]!=letter){ return false; }
   if (current.extended && current.burrow[4][col]!='.' && current.burrow[4][col]!=letter){ return false; }
   if (current.burrow[3][col]!='.' && current.burrow[3][col]!=letter){ return false; }
   if (current.burrow[2][col]!='.' && current.burrow[2][col]!=letter){ return false; }

   return true; 
}

// if a room is (partially)complete, do not remove 
bool can_exit(const state& current, char letter, int col){ return !can_enter(current,letter,col); }

int enter(state& current, int start, int end, char letter){

   // step direction
   int step    = start < end ? 1 : -1;
   int n_steps = 0;

   // move across hall to correct room
   for (int pos=start+1; pos<=end; pos+=step){

      // can only move into open spaces
      if (current.burrow[1][pos]!='.'){ return INT_MAX; }
      n_steps++;
   }

   int i=2;
   // go down into room, stop when the next step is a dead end
   while (current.burrow[i][end]!='.'){
      n_steps++;
      i++;
   }

   // update state
   current.burrow[i-1][end] = letter;
   current.burrow[1][start] = '.';
   int energy = n_steps*std::pow(10,letter-'A');
   current.energy += energy;

   return energy;
}

int exit(state& current, int start, int end){

   int height=2;
   
   // get height and letter of moving amphipod
   while (current.burrow[height][start]=='.'){ ++height; }
   char letter = current.burrow[height][start];

   // step direction
   int step    = start < end ? 1 : -1;
   int n_steps = 0;
   for (int pos=start+1; pos<=end; pos+=step){

      // can only move into open spaces
      if (current.burrow[1][pos]!='.'){ return INT_MAX; }
      n_steps++;
   }

   // update state
   current.burrow[1][end] = letter;
   current.burrow[height][start] = '.';
   int energy = n_steps*std::pow(10,letter-'A');
   current.energy += energy;

   return energy;
}

void rearrange(state current, int& energy){

   // if all amphipods in place
   if (current.in_place == 16){
      
      // check if current energy is lower, if not move on
      if (current.energy >= energy){ return; }
      else { energy = current.energy; }
   }

   // try moving amphipod into correct room
   for (int pos : hallway_positions){

      char letter = current.burrow[1][pos];
      int end   = correct_columns[letter-'A'];

      // ignore empty spaces
      if (letter=='.'){ continue; }
      // calculate cost to move into correct room
      else if (can_enter(current, letter, end)){

         // create copy of state and recursively continue
         state copy = current;
         if (enter(copy, pos, end, letter) != INT_MAX){ rearrange(copy, energy); }
      }
   }

   // try moving amphipot out of wrong room
   for (int start : correct_columns){
      
      char letter = 'A'+(start-2)/2;

      if (can_exit(current,letter,start)){
         
         for (int end : hallway_positions){

            state copy = current;
            if (exit(copy,start,end) != INT_MAX){ rearrange(copy, energy); }
         }
      }
   }
}