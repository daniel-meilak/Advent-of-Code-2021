#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include"utils.h"

int main(){

    // read input
    std::vector<std::string> delimiters = {",","fold along ", "="};
    std::vector<std::vector<std::string>> input  = read_input_2D("input_13", delimiters);

    // separate into folds and dots
    std::vector<std::vector<std::string>> folds;
    std::vector<std::vector<int>> dots;

    bool read_dots = false;
    for (const auto& line : input){

        if (!read_dots){
            if (line.empty()){ read_dots=true; continue; }
            dots.push_back({std::stoi(line[0]), std::stoi(line[1])});
        }
        else { folds.push_back(line); }
    }

    // get grid size
    int xmax = folds[0][0] == "x" ? std::stoi(folds[0][1])*2 + 1 : std::stoi(folds[1][1])*2 + 1;
    int ymax = folds[0][0] == "x" ? std::stoi(folds[1][1])*2 + 1 : std::stoi(folds[0][1])*2 + 1;

    // create and fill grid
    std::vector<std::vector<bool>> grid(ymax, std::vector<bool>(xmax,false));

    for (const auto& line : dots){
        grid[line[1]][line[0]] = true;
    }

    // number of dots after first fold
    int part_1 = 0;
    bool first_fold = true;

    // perform folds
    int xmin, ymin, mirror_x, mirror_y;
    for (const auto& line : folds){

        // folding along x or y
        bool x_fold = line[0] == "x";
       
        xmin = x_fold  ? std::stoi(line[1])+1 : 0;
        ymin = !x_fold ? std::stoi(line[1])+1 : 0;

        // work through grid being folded up/left
        for (int x=xmin; x<xmax; x++){
            for (int y=ymin ; y<ymax; y++){

                mirror_x = x_fold  ? 2*(xmin-1) - x : x;
                mirror_y = !x_fold ? 2*(ymin-1) - y : y;

                // mirror over dots
                if (grid[y][x]){ grid[mirror_y][mirror_x] = true; }
            }
        }

        // reduce grid x/ymax
        if (x_fold){ xmax = xmin-1; }
        else       { ymax = ymin-1; }

        // count folds for part 1
        if (first_fold){
            for (int x=0; x<xmax; x++){
                for (int y=0; y<ymax; y++){
                    if (grid[y][x]){ part_1++; }
                }
            }
            first_fold = false;
        }
    }

    // reduce grid to final state for printing
    grid.erase(std::next(grid.begin(),ymax), grid.end());
    for (auto& row : grid){ row.erase(std::next(row.begin(),xmax),row.end()); }

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << std::endl;
    display(grid);

    return 0;
}
