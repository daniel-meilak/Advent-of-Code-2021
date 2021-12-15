#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<utility>
#include<queue>
#include"../../Utils/utils.h"
#include"../../Utils/point.h"

using PD = std::pair<double,point>;

const std::vector<point> cardinals = {{1,0},{0,1},{-1,0},{0,-1}};
int A_star_cost(const std::vector<std::vector<int>>& grid, const point& start, const point& end);

int main(){

    // read input into vector of vector of int.
    std::vector<std::vector<int>> grid = read_int_grid("input");

    const int width  = static_cast<int>(grid[0].size()); 
    const int height = static_cast<int>(grid.size());
    const int mult = 5;

    // start and end points
    point start = {0,0};
    point end   = {width-1,height-1};
    point end2  = {width*mult-1,height*mult-1};

    // create grid for part 2
    std::vector<std::vector<int>> grid2(height*mult,std::vector<int>(width*mult));
    for (int i=0; i<width*mult; i++){
        for (int j=0; j<height*mult; j++){

            int next = grid[j%height][i%width] + i/width + j/height;
            grid2[j][i] = next > 9 ? (next % 10)+1 : next;
        }
    }

    std::cout << "Answer (part 1): " << A_star_cost(grid ,start,end ) << std::endl;
    std::cout << "Answer (part 2): " << A_star_cost(grid2,start,end2) << std::endl;

    return 0;
}

int A_star_cost(const std::vector<std::vector<int>>& grid, const point& start, const point& end){

    const int width  = static_cast<int>(grid[0].size()); 
    const int height = static_cast<int>(grid.size());

    // unordered map to store path and cost 
    std::unordered_map<point,point> came_from;
    std::unordered_map<point,int> cost;

    // priority queue to chose best path to follow
    std::priority_queue<PD,std::vector<PD>,std::greater<PD>> frontier;
    frontier.emplace(0,start);

    // start path and cost calculation
    came_from[start] = start;
    cost[start] = 0;

    // A*
    while(!frontier.empty()){
        point current = frontier.top().second;
        frontier.pop();

        if (current == end){ break; }

        // try neighbours
        for (const auto& p : cardinals){
            point next = current + p;

            // check if out of bounds
            if (next.x < 0 || next.y < 0 || next.x >= width || next.y >= height){ continue; }

            // calculate path cost and check if it is new/better path
            int new_cost = cost[current] + grid[next.y][next.x];
            if (!cost.contains(next) || new_cost < cost[next]){

                // A* uses priority made up of path cost + heuristic (manhattan distance)
                cost[next] = new_cost;
                int priority = new_cost + manhattan(next,end);

                frontier.emplace(priority,next);
                came_from[next] = current;
            }
        }
    }
    
    return cost[end];
}