#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <string>
using namespace std;

// Edge structure
struct Edge {
    int destination;
    int weight;
};

// Graph structure created with adjecency_list
class Graph {
    unordered_map<int, vector<Edge>> list;

public:
    void add_edge(int u, int v, int weight) {
        list[u].push_back({v, weight});
    }

    
    void print()
    {
        
    }
};

int main()
{
    
    return 0;
}

