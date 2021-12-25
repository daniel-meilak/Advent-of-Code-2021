#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<climits>
#include"../../Utils/utils.h"

int main(){

    // read input into vector of strings.
    std::vector<std::string> input = read_input("input", "");

    const int height = static_cast<int>(input.size());
    const int width  = static_cast<int>(input[0].size());

    // copy of input
    std::vector<std::string> copy(input);

    auto cucumbers = {std::make_tuple<char,int,int>('>',1,0),std::make_tuple<char,int,int>('v',0,1)};

    int moves  = INT_MAX;
    int part_1 = 0;
    // simulate movements
    while (moves != 0){

        moves = 0;

        // move right then down
        for (const auto& [dir,dx,dy] : cucumbers){
            
            for (int y=0; y<height; y++){
                for (int x=0; x<width; x++){

                    int i = (x+dx)%width;
                    int j = (y+dy)%height;

                    if ( input[y][x]==dir ){
                        if (input[j][i]=='.'){
                            
                            // count move
                            moves++;

                            // move
                            copy[j][i]=dir;
                            copy[y][x]='.';
                        }
                    }
                }
            }
            
            // update grid
            input = copy;
        }
        part_1++;    
    }

    std::cout << "Answer: " << part_1 << std::endl;
    std::cout << "Merry Christmas!" << std::endl;

    return 0;
}
