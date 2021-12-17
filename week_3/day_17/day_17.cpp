#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdlib>
#include"../../Utils/utils.h"

// calculate max distance from x velocity
int max_distance(int x){
    return x*(x+1)/2;
}

int main(){

    // read input into vector of vector of int
    std::vector<std::string> delimiters = {"target area: x=", "..", ", y="};
    std::vector<std::vector<int>> input = input_to_int_2D(read_input_2D("input", delimiters));

    // target
    const int xmin=input[0][0];
    const int xmax=input[0][1];
    const int ymin=input[0][2];
    const int ymax=input[0][3];

    // initial state
    int vel = 0;

    // minimum xvelocity that reaches target before getting to 0
    int min_x_vel;

    int distance = 0;
    while (distance < xmax){
        vel++;

        // calculate max distance and check its over xmin
        if ( (distance = max_distance(vel)) > xmin){
            min_x_vel = vel;
            break;
        }
    }

    // on the way down, y=0 again, and next step is -initial_yvel. If -initial_yvel is 
    // lower than ymin, target area is missed, hence max height from initial_yvel = -ymin-1
    int part_1 = max_distance(-ymin-1);

    // brute force between min and max xvalues
    int part_2 = 0;

    // min x has been calculated and max x is xmax, cannot overshoot target after one step!
    for (int i=min_x_vel; i<=xmax; i++){
        // we can shoot down now so go between ymin and -ymin-1
        for (int j=ymin; j<=-ymin-1; j++){

            int xpos = 0;
            int ypos = 0;
            int xvel = i;
            int yvel = j;

            // simulate untill beyond bounds
            while (xpos <= xmax && ypos >= ymin){
                xpos += xvel;
                ypos += yvel;
                if (xvel > 0){ xvel -= 1; }
                yvel -= 1;

                if (xpos >= xmin && xpos <= xmax && ypos >=ymin && ypos <= ymax){
                    part_2++;
                    break;
                }
            }
        }
    }

    // trajectory is mirrored up to down, so max height reached by distance to lower bound
    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}
