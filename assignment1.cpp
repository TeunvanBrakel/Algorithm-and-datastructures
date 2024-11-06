#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <string>
#include <sstream>
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

    vector<int> change_string_to_list_of_int(string input){
        vector<int> result = std:: vector<int>();
        std::stringstream str_strm(input);
        std::string word;
        while (str_strm >> word){
            result.emplace_back(std::stoi(word));
        }
        return result;
    }

    void add_busLine(string b, string c){
        
       
    }
};

int main()
{
    Graph graph;
    int numberOfBusLines;std::cin>>numberOfBusLines;
    int numberOfBusstops;std::cin>>numberOfBusstops;
    std::cout<<numberOfBusLines<<std::endl;
    //cin appart anders hoeft dit niet. Zoals bij getline.
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    for (int i = 0; i < numberOfBusLines; i++)
    {
        string busStops;
        string arrivalTimes;
        std::getline(std::cin, busStops);
        std::getline(std::cin, arrivalTimes);
        std::cout << busStops << std::endl;
        std:: vector<int> stops = graph.change_string_to_list_of_int(busStops);
        std:: vector<int> times = graph.change_string_to_list_of_int(arrivalTimes);

        //  for(int i = 0; i < test.size(); i++){
        //      std::cout<<test.at(i)<<std::endl;
        //  }
        std:: cout << "test" << std:: endl;
    }
    return 0;
}
