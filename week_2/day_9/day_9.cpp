#include<iostream>
#include<vector>
#include<deque>
#include<set>
#include<string>
#include"../../Utils/utils.h"
#include"../../Utils/point.h"

std::vector<point> cardinals = {{1,0},{-1,0},{0,1},{0,-1}};

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    // grid width and height
    int height = (int)input.size()+2;
    int width  = (int)input[0].size()+2;

    // grid with top border
    std::vector<std::vector<int>> grid{std::vector<int>(width,9)};

    // convert to std::vector<std::vector<int>> with borders
    for (const std::string& line : input){
        
        // next line in grid with left border
        std::vector<int> temp = {9};
        temp.reserve(width);

        for (const char& c : line){ temp.push_back(c-'0'); }
        // add right border
        temp.push_back(9);

        // add to grid
        grid.push_back(temp);
    }

    // bottom border
    grid.push_back(std::vector<int>(width,9));

    // calculate sum of risk levels and basin sizes
    int part_1 = 0;
    std::multiset<size_t> basin_sizes;
    for (int x=1; x<height-1; x++){
        for (int y=1; y<width-1; y++){

            const int& p = grid[x][y];

            // check left, right, up, down
            if (grid[x-1][y] > p && grid[x+1][y] > p && grid[x][y-1] > p && grid[x][y+1] > p){
                part_1 += p+1;

                // part 2 - find size of basin
                point start = {x,y};

                // list of all points in basin
                std::set<point> visited;

                // list of points that lead to others in basin
                std::deque<point> check{start};

                while (!check.empty()){

                    // start at a point
                    point current = check.front();

                    // remove from check list
                    check.pop_front();

                    // keep track of visited points
                    visited.insert(current);

                    // check up down left right
                    for (const auto& dir : cardinals){
                        
                        point next = current + dir;

                        // if new point is in basin and not already visited, add to check list
                        if (grid[next.x][next.y] != 9 && visited.find(next) == visited.end()){ check.push_back(next); }
                    }
                }

                // basin size is the number of visited points in basin
                basin_sizes.insert(visited.size());
            }
        }
    }

    // multiply together biggest three basin sizes (last three valus in multiset due to std::less ordering)
    const auto& it = basin_sizes.rbegin();
    size_t part_2 = *it * *std::next(it,1) * *std::next(it,2);

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}
