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
    int time;
};

// Graph structure created with adjecency_list
class Graph {
    unordered_map<int, vector<Edge>> list;

public:
    void add_edge(int u, int v, int weight, int time) {
        list[u].push_back({v, weight, time});
    }

    unordered_map<int, vector<Edge>> get_list(){
        return list;
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

    void add_busLine(vector<int> stops, vector<int> times, int count, int totalStops){
        for(int i = 0; i < stops.size()-1; i++){
            add_edge(stops[i], stops[i+1], times[i+1]-times[i], times[i]);
        }
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
        graph.add_busLine(stops, times, i, numberOfBusstops);
        unordered_map<int, vector<Edge>> list = graph.get_list();
        //  for(int i = 0; i < list.size(); i++){
        //      std::cout << list.at(i) << std::endl;
        //  }
    }
    return 0;
}
