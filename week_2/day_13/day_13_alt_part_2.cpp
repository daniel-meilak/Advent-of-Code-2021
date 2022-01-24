#include<iostream>
#include<vector>
#include<string>
#include"utils.h"

int main(){

    // read dots
    std::vector<std::string> delimiters = {","};
    std::vector<std::vector<int>> dots  = input_to_int_2D(read_input_2D("dots", delimiters));

    // read folds
    delimiters = {"fold along ", "="};
    std::vector<std::vector<std::string>> folds = read_input_2D("folds", delimiters);

    // get number of repeated grids in each direction and initial & final grid size
    int x_repeats = 1, y_repeats = 1;
    int xmin = 0, ymin = 0, xmax = 0, ymax = 0;
    for (const auto& line : folds){
        if (line[0] == "x"){
            x_repeats *= 2;
            if (!xmax){ xmax = std::stoi(line[1])*2+1; }
            xmin = std::stoi(line[1]);
        }
        else               {
            y_repeats *= 2;
            if (!ymax){ ymax = std::stoi(line[1])*2+1; }
            ymin = std::stoi(line[1]);
        }
    }

    // create and fill grid
    std::vector<std::vector<bool>> grid(ymax, std::vector<bool>(xmax,false));
    for (const auto& line : dots){ grid[line[1]][line[0]] = true; }

    // loop through final grid
    for (int x=0; x<xmin; x++){
        for (int y=0; y<ymin; y++){

            // loop through all unfolded grids
            for (int nx=1; nx<=x_repeats; nx++){
                int i = 0.5*( 2*(xmin+1)*nx + (xmin -2*x -1)*std::pow(-1,nx) - (xmin+2) );

                for (int ny=1; ny<=y_repeats; ny++){
                    int j = 0.5*( 2*(ymin+1)*ny + (ymin -2*y -1)*std::pow(-1,ny) - (ymin+2) );

                    if (grid[j][i]){
                        grid[y][x] = true;
                        goto next_point;
                    }
                }
            }
next_point:;
        }
    }

    // reduce grid to final state for printing
    grid.erase(std::next(grid.begin(),ymin), grid.end());
    for (auto& row : grid){ row.erase(std::next(row.begin(),xmin),row.end()); }

    std::cout << "Answer (part 2): " << std::endl;
    display(grid);

    return 0;
}
