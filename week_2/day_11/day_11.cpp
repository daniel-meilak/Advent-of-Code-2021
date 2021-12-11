#include<iostream>
#include<vector>
#include<unordered_set>
#include<climits>
#include"../../Utils/utils.h"
#include"../../Utils/point.h"

// neighbouring cells in a grid
std::vector<point> neighbours = {{1,0},{-1,0},{0,1},{0,-1},{1,1},{-1,-1},{1,-1},{-1,1}};

int check_flash( const int x, const int y, std::vector<std::vector<int>>& grid, std::unordered_set<point>& flashed );

int main(){

    // read input into vector of vector of int
    std::vector<std::vector<int>> input = read_int_grid("input", true, INT_MIN);

    // simulate 100 steps
    const int steps  = 100;
    const int height = input.size();
    const int width  = (int)input[0].size();
    int i = 0;

    // number of flashes
    int part_1 = 0;
    int part_2 = 0;

    while( !part_2 ){

        std::unordered_set<point> flashed;

        for (int x=1; x<width-1; x++){
            for (int y=1; y<height-1; y++){

                if (i < steps){ part_1 += check_flash(x,y,input,flashed); }
                else { check_flash(x,y,input,flashed); }
            }
        }

        i++;
        if ( (int)flashed.size() == (width-2)*(height-2) ){ part_2 = i; }
    }

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}

// checks octopus at {x,y} if it hasnt flashed. Increments, checks for flash -> if yes checks surrounding octop[i/uses/edes]
int check_flash( const int x, const int y, std::vector<std::vector<int>>& grid, std::unordered_set<point>& flashed ){

    int num_flashes = 0; 

    // if an octupus hasn't already flashed, increment energy level and check for flash
    if ( !flashed.contains({x,y}) && ++grid[y][x] == 10 ){

        // add new flash to list of flashed
        flashed.insert({x,y});

        // set octopus to 0
        grid[y][x] = 0;

        // add 1 to counter
        num_flashes++;

        // recursively check surrounding points
        for ( const point& p : neighbours ){ num_flashes += check_flash(x+p.x, y+p.y, grid, flashed); }
    }

    return num_flashes;
}