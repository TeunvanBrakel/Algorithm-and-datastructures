#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
#include <limits>
#include <string>
#include <sstream>
using namespace std;

struct Edge {
    int destination;
    int weight;
    int time;
};

class Graph {
    unordered_map<int, vector<Edge>> list;

public:
    void add_edge(int u, int v, int weight, int time) {
        list[u].push_back({v, weight, time});
    }

    unordered_map<int, vector<Edge>> get_list(){
        return list;
    }

    int dijkstra(int start, int end) {
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        unordered_map<int, int> min_time;
        
        pq.push({0, start});
        min_time[start] = 0;
        
        while (!pq.empty()) {
            auto [curr_time, curr_node] = pq.top();
            pq.pop();
            
            // Explore the neighbors
            for (const Edge& edge : list[curr_node]) {
                if (curr_time <= edge.time) {
                    int arrival_time = edge.time + edge.weight;
                
                    // Only proceed if we find a shorter path to the neighbor
                    if (!min_time.count(edge.destination) || arrival_time < min_time[edge.destination]) {
                        min_time[edge.destination] = arrival_time;
                        pq.push({arrival_time, edge.destination});
                    }
                }
            }

        }
        return min_time[end];
    }

    vector<int> change_string_to_list_of_int(const string& input){
        vector<int> result;
        stringstream str_strm(input);
        string word;
        while (str_strm >> word){
            result.push_back(stoi(word));
        }
        return result;
    }

    void add_busLine(const vector<int>& stops, const vector<int>& times){
        for(size_t i = 0; i < stops.size()-1; i++){
            int from = get_id(stops[i], times[i]);
            int to = get_id(stops[i + 1], times[i + 1]);
            int weight = times[i + 1] - times[i];
            add_edge(stops[i], stops[i + 1], weight, times[i]);
        }
    }

    unordered_map<int, unordered_map<int, int>> location_time_to_id;
    int next_id = 0;

    int get_id(int location, int time) {
        if (!location_time_to_id[location].count(time)) {
            location_time_to_id[location][time] = next_id;
            next_id++;
        }
        return location_time_to_id[location][time];
    }
};

int main()
{
    Graph graph;
    int numberOfBusLines; cin >> numberOfBusLines;
    int numberOfBusstops; cin >> numberOfBusstops;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    for (int i = 0; i < numberOfBusLines; i++)
    {
        string busStops;
        string arrivalTimes;
        getline(cin, busStops);
        getline(cin, arrivalTimes);
        
        vector<int> stops = graph.change_string_to_list_of_int(busStops);
        vector<int> times = graph.change_string_to_list_of_int(arrivalTimes);
        
        graph.add_busLine(stops, times);
    }

    int result = graph.dijkstra(0, numberOfBusstops-1);

     if (result != -1) {
        cout << result << endl;
    } else {
        cout << -1 << endl;
    }

    return 0;
}
