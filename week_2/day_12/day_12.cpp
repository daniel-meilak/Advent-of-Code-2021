#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<cctype>
#include<unordered_map>
#include<set>
#include"../../Utils/utils.h"

// struct to keep graph information together
struct graph_t{

    // start and end of graph
    const std::string start = "start", end = "end";

    // flag to allow visiting small cave twice
    bool part_2 = false;

    // map of nodes
    std::unordered_map<std::string,std::vector<std::string>> tree;

    // vector of paths
    std::vector<std::vector<std::string>> paths;

    // method to find number of paths
    void calculate_paths();

    private:
        // breadth first search for looking through tree
        void BFS( const std::string& current, std::vector<std::string>& path, std::multiset<std::string>& visited, bool visited_twice = false );
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
    graph.paths.clear();

    // number of paths with extra small cave (part 2)
    graph.part_2 = true;
    graph.calculate_paths();
    size_t part_2 = graph.paths.size();

    std::cout << "Answer (part 1): " << part_1 << std::endl;
    std::cout << "Answer (part 2): " << part_2 << std::endl;

    return 0;
}

void graph_t::calculate_paths(){

    // visited nodes (uppercase nodes)
    std::multiset<std::string> visited;

    // vector to store path
    std::vector<std::string> path;

    // call BFS to find paths
    BFS(start, path, visited);
}

void graph_t::BFS( const std::string& current, std::vector<std::string>& path, std::multiset<std::string>& visited, bool visited_twice ){

    // if small cave add to visited
    if ( std::islower(current[0]) ){
        // for part 2, one small cave can be visited twice
        if (part_2 && visited.contains(current)){ visited_twice = true; }
        visited.insert(current);
    }

    // add current step to path
    path.push_back(current);

    // if at end, add full path to paths
    if ( current == end ){ paths.push_back(path); }
    // else, continue BFS with connected nodes
    else {
        for (const std::string& next : tree[current]){

            if (next == start){ continue; }

            // only continue to unvisited or uppercase nodes, and in part 2, one extra small cave
            if (!visited.contains(next) || (part_2 && !visited_twice)){ BFS(next, path, visited, visited_twice); }
        }
    }

    // remove last step and visited check for other paths
    path.pop_back();
    auto it = visited.find(current);
    if (it != visited.end()){ visited.erase(it); }
}