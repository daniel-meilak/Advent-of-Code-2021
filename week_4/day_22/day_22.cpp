#include<iostream>
#include<vector>
#include<string>
#include<set>
#include<utility>
#include"../../Utils/utils.h"
#include"../../Utils/point.h"

// to avoid confusion for x,y members in point_t, derive new struct with new names
struct range: public point{
    const int& min() const{ return x; }
    const int& max() const{ return y; }

    void setmin(int a){ x = a; }
    void setmax(int a){ y = a; }

    range(int x, int y): point(x,y){}
};

// I used cube to mean cuboid throughout this code
struct cube{
    range x={0,0}, y = {0,0}, z={0,0};
    bool on = true;

    // spaceship operator defines "==","!=",">","<",">=","<="
    auto operator<=>(const cube&) const = default;

    cube() = default;
    cube(const range& x, const range& y, const range& z, bool on = true): x(x), y(y), z(z), on(on){};
    
    bool intersect(const cube& b) const;
    ulong volume() const{ 
        ulong sum = 0;
        sum += abs(x.max()-x.min())+1;
        sum *= abs(y.max()-y.min())+1;
        sum *= abs(z.max()-z.min())+1;

        return sum;
    }
};

void form_new_cubes(const cube& a, const cube& b, std::set<cube>& pieces, std::set<cube>& left_over);

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {" x=","..",",y=",",z="};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // set of cubes
    std::set<cube> on_cubes;

    // add cubes to map
    for (const auto& line : input){

        cube a = {{std::stoi(line[1]), std::stoi(line[2])}, {std::stoi(line[3]), std::stoi(line[4])}, {std::stoi(line[5]), std::stoi(line[6])}};
        if (line[0] == "off"){ a.on = false; }
        std::set<cube> left_over{a}, pieces;

        // break up intersections into pieces and left over
intersected:;
        while (!left_over.empty()){

            const cube current = *left_over.begin();
            left_over.erase(left_over.begin());

            // check for intersections with cubes already in map
            // auto it = on_cubes.begin();
            // while (it != on_cubes.end());
            for (auto it=on_cubes.begin(); it!=on_cubes.end();){

                // if the cubes intersect, create divisions of cubes
                if (current.intersect(*it)){

                    form_new_cubes(*it,current,pieces,left_over);

                    // remove intersected cube
                    it = on_cubes.erase(it);

                    // for (auto it1=left_over.begin(); it1!=left_over.end(); it1++){
                    //     for (auto it2=left_over.begin(); it2!=left_over.end(); it2++){
                    //         if (it1==it2){continue;}

                    //         if ((*it1).intersect(*it2)){
                    //             std::cout << "problem" << std::endl;
                    //         }
                    //     }
                    // }

                    // add pieces back to intersect with other segments

                    on_cubes.insert(pieces.begin(),pieces.end());
                    pieces.clear();
                    goto intersected;
                }
                else{ ++it; }
            }

            // if (current.on){
            //     bool new_piece = true;
            //     for (const auto& p : pieces){
            //         if (current.intersect(p)){
            //             new_piece = false;
            //             break;
            //         }
            //     }
            
            //     if (new_piece){ pieces.insert(current); }
            // }
            if (current.on){ on_cubes.insert(current); }
            //on_cubes.insert(pieces.begin(),pieces.end());
            //pieces.clear();
        }

        //on_cubes.insert(pieces.begin(),pieces.end());
    }

    // calculate volume of on cubes
    ulong part_1 = 0, part_2 = 0, volume;
    for (const cube& c : on_cubes){

        volume = c.volume();
        if (c.x.min()>=-50 && c.x.max()<=50&&c.y.min()>=-50 && c.y.max()<=50&&c.z.min()>=-50 && c.z.max()<=50){
            part_1 += volume;
        }

        part_2 += volume;
    }

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}

bool cube::intersect(const cube& b) const{
    return x.min()<=b.x.max() && x.max()>= b.x.min() && y.min()<=b.y.max() && y.max()>=b.y.min() && z.min()<=b.z.max() && z.max()>=b.z.min();
}

void form_new_cubes(const cube& a, const cube& b, std::set<cube>& pieces, std::set<cube>& left_over){

    // central cube in intersection
    cube c;

    std::vector<cube> check;

    // add all cubes not in intersection (when on)
    // working along x
    // left cube
    if (a.x.min() < b.x.min()){
        pieces.insert( {{a.x.min(),b.x.min()-1}, a.y, a.z} );

        c.x.setmin(b.x.min());
    }
    else if (a.x.min() > b.x.min()){
        left_over.insert( {{b.x.min(),a.x.min()-1}, b.y, b.z, b.on} );

        c.x.setmin(a.x.min());
    }
    else { c.x.setmin(a.x.min()); }

    // right cube
    if (a.x.max() > b.x.max()){
        pieces.insert( {{b.x.max()+1,a.x.max()}, a.y, a.z} );

        c.x.setmax(b.x.max());
    }
    else if (a.x.max() < b.x.max()){
        left_over.insert( {{a.x.max()+1,b.x.max()}, b.y, b.z, b.on} );

        c.x.setmax(a.x.max());
    }
    else { c.x.setmax(a.x.max()); }

    // for (auto& l : left_over){
    //     if (a.intersect(l)){
    //         std::cout << "inner intersecter" << std::endl;
    //     }
    // }

    // for (auto it1=left_over.begin(); it1!=left_over.end(); it1++){
    //     for (auto it2=pieces.begin(); it2!=pieces.end(); it2++){
    //         if (it1==it2){continue;}

    //         if ((*it1).intersect(*it2)){
    //             std::cout << "pieces-left_over problem" << std::endl;
    //         }
    //     }
    // }

    // working along y
    // left cube
    if (a.y.min() < b.y.min()){
        pieces.insert( {c.x, {a.y.min(),b.y.min()-1}, a.z} );

        c.y.setmin(b.y.min());
    }
    else if (a.y.min() > b.y.min()){
        left_over.insert( {c.x, {b.y.min(),a.y.min()-1}, b.z, b.on} );

        c.y.setmin(a.y.min());
    }
    else { c.y.setmin(a.y.min()); }

    // right cube
    if (a.y.max() > b.y.max()){
        pieces.insert( {c.x, {b.y.max()+1,a.y.max()}, a.z} );

        c.y.setmax(b.y.max());
    }
    else if (a.y.max() < b.y.max()){
        left_over.insert( {c.x, {a.y.max()+1,b.y.max()}, b.z, b.on} );

        c.y.setmax(a.y.max());
    }
    else { c.y.setmax(a.y.max()); }

    // for (auto it1=left_over.begin(); it1!=left_over.end(); it1++){
    //     for (auto it2=pieces.begin(); it2!=pieces.end(); it2++){
    //         if (it1==it2){continue;}

    //         if ((*it1).intersect(*it2)){
    //             std::cout << "pieces-left_over problem" << std::endl;
    //         }
    //     }
    // }

    // working along z
    // left cube
    if (a.z.min() < b.z.min()){
        pieces.insert( {c.x, c.y, {a.z.min(),b.z.min()-1}} );

        c.z.setmin(b.z.min());
    }
    else if (a.z.min() > b.z.min()){
        left_over.insert( {c.x, c.y, {b.z.min(),a.z.min()-1}, b.on} );

        c.z.setmin(a.z.min());
    }
    else { c.z.setmin(a.z.min()); }

    // right cube
    if (a.z.max() > b.z.max()){
        pieces.insert( {c.x, c.y, {b.z.max()+1,a.z.max()}} );

        c.z.setmax(b.z.max());
    }
    else if (a.z.max() < b.z.max()){
        left_over.insert( {c.x, c.y, {a.z.max()+1,b.z.max()}, b.on} );

        c.z.setmax(a.z.max());
    }
    else { c.z.setmax(a.z.max()); }

    // finally add intersection cube if b is on
    if (b.on){ pieces.insert(c); }
}