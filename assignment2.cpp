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
    int waitTime;
};

struct vertex{
    int arrivalTime;
    int waitTime;

     // Define an operator< for vertex
    bool operator<(const vertex& other) const {
        return waitTime < other.waitTime;
    }
};

class Graph {
    unordered_map<int, vector<Edge>> list;

public:
    void add_edge(int u, int v, int weight, int time) {
        list[u].push_back({v, weight, time,0});
    }

    unordered_map<int, vector<Edge>> get_list(){
        return list;
    }

    int dijkstra(int start, int end) {
        priority_queue<pair<vertex, int>, vector<pair<vertex, int>>, greater<pair<vertex, int>>> pq;
        unordered_map<int, int> min_time;
        vertex t;
        t.arrivalTime = 0;
        t.waitTime = 0;
        pq.push({t, start});
        min_time[start] = 0;
        int waitTime = 0;
        while (!pq.empty()) {
            auto [curr_vertex, curr_node] = pq.top();
            pq.pop();
            
            // Explore the neighbors
            for (const Edge& edge : list[curr_node]) {
                if (curr_vertex.arrivalTime <= edge.time) {
                        vertex g;
                        g.arrivalTime = edge.time + edge.weight;
                        waitTime = curr_vertex.waitTime + edge.time - curr_vertex.arrivalTime;
                        g.waitTime = waitTime;
                        // Only proceed if we find a shorter path to the neighbor
                        if (!min_time.count(edge.destination) || waitTime < min_time[edge.destination]) {
                            min_time[edge.destination] = waitTime;
                            if(edge.destination == end && waitTime == 0){
                                return 0;
                            }
                        // curr_waitTime[edge.destination].push_back({arrival_time, edge.destination, waitTime});
                        }
                        pq.push({g, edge.destination});
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

    int add_busLine(const vector<int>& stops, const vector<int>& times, int count, int totalStops, int max){
        int result;
        int stopCount = 0;
        bool test = false;
        if(stops[0] == 0 && times[0] == 0){
                result = count;
                test = true;
        }
        for(size_t i = 0; i < stops.size()-1; i++){
            int from = get_id(stops[i], times[i]);
            int to = get_id(stops[i + 1], times[i + 1]);
            int weight = times[i + 1] - times[i];
            if(test == true && stops[i+1] == totalStops){
                return 5656;
            }
            add_edge(stops[i], stops[i + 1], weight, times[i]);
            stopCount++;
        }
        return result;
    }

    unordered_map<int, unordered_map<int, int>> location_time_to_id;
    int next_id = -1;

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
    int count = 0;
    int startBus = 0;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    for (int i = 0; i < numberOfBusLines; i++)
    {
        string busStops;
        string arrivalTimes;
        getline(cin, busStops);
        getline(cin, arrivalTimes);
        
        vector<int> stops = graph.change_string_to_list_of_int(busStops);
        vector<int> times = graph.change_string_to_list_of_int(arrivalTimes);
        
        int result = graph.add_busLine(stops, times,count,numberOfBusstops-1, numberOfBusLines);
        count++;
        if(result == 5656){
            startBus = 5656;
        }else if(result != -1 && startBus != 5656){
            startBus = result;
        }
    }
    if(startBus == 5656){
        cout << 0 << endl;
        return 0;
    }else{
        int result = graph.dijkstra(0, numberOfBusstops-1);

        if (result != -1) {
            cout << result << endl;
        } else {
            cout << -1 << endl;
        }
        return 0;
    }
}
