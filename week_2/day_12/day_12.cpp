#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<cctype>
#include<unordered_map>
#include<unordered_set>
#include"../../Utils/utils.h"

// struct to keep graph information together
struct graph_t{

    // start and end of graph
    std::string start = "start", end = "end";

    // special small cave and num visits to it
    std::string special;
    int special_visits = 0;

    // map of nodes
    std::unordered_map<std::string,std::vector<std::string>> tree;

    // vector of paths
    std::vector<std::vector<std::string>> paths;

    // method to find number of paths
    void calculate_paths();

    // method to find number of paths with small cave special case (part 2)
    void calculate_paths_extra_cave();

    private:
        // breadth first search for looking through tree
        void BFS( const std::string& current, std::vector<std::string>& path, std::unordered_set<std::string>& visited );
};

int main(){

    // read input into vector of vector of strings.
    std::vector<std::string> delimiters = {"-"};
    std::vector<std::vector<std::string>> input = read_input_2D("input", delimiters);

    // create graph
    graph_t graph;

    // add nodes to tree
    for ( const auto& line : input ){
        graph.tree[line[0]].push_back(line[1]);
        graph.tree[line[1]].push_back(line[0]);
    }

    // number of normal paths (part 1)
    graph.calculate_paths();
    size_t part_1 = graph.paths.size();

    // number of paths with extra small cave (part 2)
    graph.calculate_paths_extra_cave();
    size_t part_2 = graph.paths.size();

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}

void graph_t::calculate_paths(){

    // visited nodes (uppercase nodes)
    std::unordered_set<std::string> visited;

    // vector to store path
    std::vector<std::string> path;

    // call BFS to find paths
    BFS(start, path, visited);
}

void graph_t::calculate_paths_extra_cave(){

    // loop through nodes to try different small caves
    for ( const auto& [key, value] : tree ){

        // skip start and end
        if (key == "start" || key == "end" || std::isupper(key[0])){ continue; }

        // set to special
        special = key;

        calculate_paths();
    }
}

void graph_t::BFS( const std::string& current, std::vector<std::string>& path, std::unordered_set<std::string>& visited ){

    // if small cave check if it can be visited twice, if not add to visited
    if ( std::islower(current[0]) ){
        if (current != special){ visited.insert(current); }
        else if ( ++special_visits == 2 ){ visited.insert(current); }          
    }

    // add current step to path
    path.push_back(current);

    // if at end, add full path to paths
    if ( current == end ){
        if (std::find(paths.begin(),paths.end(),path) == paths.end()){ paths.push_back(path); }
    }
    // else, continue BFS with connected nodes
    else {
        for (const std::string& next : tree[current]){

            // only continue to unvisited or uppercase nodes
            if (!visited.contains(next)){ BFS(next, path, visited); }
        }
    }

    // remove last step and visited check for other paths
    path.pop_back();
    if (current == special){ special_visits--; }
    visited.erase(current);
}