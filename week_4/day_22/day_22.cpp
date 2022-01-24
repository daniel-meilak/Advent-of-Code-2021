#include<algorithm>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include"utils.h"

using ullong = unsigned long long;

struct cube_t{

   int xmin, xmax;
   int ymin, ymax;
   int zmin, zmax;

   // spaceship operator defines "==","!=",">","<",">=","<="
   auto operator<=>(const cube_t&) const = default;
};

int main(){

   // read input into vector of vector of strings.
   std::vector<std::string> delimiters = {" x=","..",",y=",",z="};
   std::vector<std::vector<std::string>> input = read_input_2D("input_22", delimiters);

   std::vector<cube_t> cubes;

   // map of cubes to count
   std::map<cube_t,ullong> counter;

   
   for (const auto& line : input){

      // read cube list
      cube_t new_cube;
      
      new_cube.xmin = std::stoi(line[1]);
      new_cube.xmax = std::stoi(line[2]);
      new_cube.ymin = std::stoi(line[3]);
      new_cube.ymax = std::stoi(line[4]);
      new_cube.zmin = std::stoi(line[5]);
      new_cube.zmax = std::stoi(line[6]);
      bool on = line[0]=="on" ? true : false;

      // counter for new cubes
      std::map<cube_t,ullong> update;

      for (const auto& [cube,count] : counter){

         cube_t inter;

         // find intersections
         inter.xmin = std::max(new_cube.xmin, cube.xmin);
         inter.ymin = std::max(new_cube.ymin, cube.ymin);
         inter.zmin = std::max(new_cube.zmin, cube.zmin);
         inter.xmax = std::min(new_cube.xmax, cube.xmax);
         inter.ymax = std::min(new_cube.ymax, cube.ymax);
         inter.zmax = std::min(new_cube.zmax, cube.zmax);

         if (inter.xmin<=inter.xmax && inter.ymin<=inter.ymax && inter.zmin<=inter.zmax){ update[inter] -= count; }
      }

      update[new_cube] += on;

      for (const auto& [cube,count] : update){ counter[cube] += count; }
   }

   // calculate volumes
   ullong part_1 = 0;
   ullong part_2 = 0;

   for (const auto& [cube,count] : counter){

      ullong volume = (cube.xmax-cube.xmin+1ull)*(cube.ymax-cube.ymin+1ull)*(cube.zmax-cube.zmin+1ull)*count;

      if (cube.xmin>=-50 && cube.xmax<=50 && cube.ymin>=-50 && cube.ymax<=50 && cube.zmin>=-50 && cube.zmax<=50){
         part_1 += volume;
      }

      part_2 += volume;
   }

   std::cout << "Answer (part 1): " << part_1 << std::endl;
   std::cout << "Answer (part 2): " << part_2 << std::endl;

   return 0;
}