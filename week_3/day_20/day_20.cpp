#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // get algorithm string
    const std::string& algorithm = input[0];
    size_t height = input.size()-2;
    size_t width  = input[2].size();
    const size_t size   = 500;
    size_t offset = 200;

    // fill (extra large) grid with '.' and place original image (roughly) at centre
    std::vector<std::string> grid(size,std::string(size,'.'));
    
    for (size_t x=0; x<width; x++){
        for (size_t y=0; y<height; y++){
            if (input[y+2][x]=='#'){ grid[y+offset][x+offset] = '#'; }
        }
    }

    // extra grid to hold next iter and part_1
    std::vector<std::string> copy(size,std::string(size,'.')), save;

    // the 'infinite' grid backgroud is either all '.' or '#' 
    // depending on 0th and last element of algorithm
    const char even_fill = algorithm.front();
    const char odd_fill  = algorithm.back();

    // perform enhancements
    const int num_enhance = 50;
    for (int i=0; i<num_enhance; i++){

        // fill background
        if (i % 2 == 0){ for (auto& line : copy){ std::ranges::fill(line,even_fill); }}
        else           { for (auto& line : copy){ std::ranges::fill(line,odd_fill ); }}

        // every iter, center image grows by 2
        offset--;
        width  += 2;
        height += 2;

        std::string pixels, binary;
        size_t index;
        for (size_t x=offset; x<width+offset; x++){
            for (size_t y=offset; y<width+offset; y++){

                pixels = grid[y-1].substr(x-1,3) + grid[y].substr(x-1,3) + grid[y+1].substr(x-1,3);
                for (char& c : pixels){ c == '#' ? c = '1' : c = '0'; }

                index  = std::stoi(pixels,nullptr,2);

                // use algorithm to assign new pixel to copy
                copy[y][x] = algorithm[index];
            }
        }

        // get part_1 grid
        if (i==1){
            for (size_t y=offset; y<height+offset; y++){
                save.push_back(copy[y].substr(offset,width));
            }
        }

        // update grid
        std::swap(grid,copy);
    }

    // use utility function (utils.h) to count number of '#' in grid
    auto part_1 = grid_count(save,'#');
    auto part_2 = grid_count(grid,'#');

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}
