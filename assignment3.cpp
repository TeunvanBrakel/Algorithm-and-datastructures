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
        return waitTime > other.waitTime;
    }
};

struct startingPoints{
    int time;
    int number;
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

    //Method in which the BFS functionality is performed. 
    //It uses the start location, end location and current maximum time as an input. And outputs the maximum it found.
    int bfs(int start, int end, int maxTime) {
        priority_queue<pair<vertex, int>, vector<pair<vertex, int>>, greater<pair<vertex, int>>> pq;
        unordered_map<int, int> max_time;
        vertex t;
        t.arrivalTime = 0;
        t.waitTime = 0;
        pq.push({t, start});
        max_time[start] = 0;
        max_time[end] = maxTime;
        int waitTime = 0;
        while (!pq.empty()) {
            auto [curr_vertex, curr_node] = pq.top();
            pq.pop();
            
            // Explore the neighbors for each edge
            for (const Edge& edge : list[curr_node]) {
                if (curr_vertex.arrivalTime <= edge.time && curr_node != end) {
                    waitTime = curr_vertex.waitTime + edge.time - curr_vertex.arrivalTime;
                    t.arrivalTime = edge.time + edge.weight;
                    t.waitTime = waitTime;
                    // Only update the maximum time if the current maximum waittime is larger.
                    if (!max_time[edge.destination] || waitTime > max_time[edge.destination]) {
                        max_time[edge.destination] = waitTime;
                    }if(edge.destination != end){
                        pq.push({t, edge.destination});
                    }
                }
            }
        }
        return max_time[end];
    }

    //Method to change the input string to a list of integers.
    vector<int> change_string_to_list_of_int(const string& input){
        vector<int> result;
        stringstream str_strm(input);
        string word;
        while (str_strm >> word){
            result.push_back(stoi(word));
        }
        return result;
    }

    //Method which adds an edge between each location of a busline to create a graph.
    startingPoints add_busLine(const vector<int>& stops, const vector<int>& times, int count, int totalStops, int max){
        startingPoints result;
        bool containsStart = false;
        if(stops[0] == 0){
                result.number = count;
                containsStart = true;
        }
        for(size_t i = 0; i < stops.size()-1; i++){
            int from = get_id(stops[i], times[i]);
            int to = get_id(stops[i + 1], times[i + 1]);
            int weight = times[i + 1] - times[i];
            add_edge(stops[i], stops[i + 1], weight, times[i]);
            if(containsStart == true && stops[i+1] == totalStops){
                result.number = 5656;
                result.time = times[0];
            }
        }
        return result;
    }

    unordered_map<int, unordered_map<int, int>> location_time_to_id;
    int next_id = -1;

    //Create a location timestamp to easily have for each location multiple moments in time from which an edge will departure.
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
    //Initializing the graph.
    Graph graph;
    int numberOfBusLines; cin >> numberOfBusLines;
    int numberOfBusstops; cin >> numberOfBusstops;
    bool skip = false;
    int count = 0;
    unordered_map<int, startingPoints> startBus;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    
    //Creating the graph with the input.
    for (int i = 0; i < numberOfBusLines; i++)
    {
        string busStops;
        string arrivalTimes;
        getline(cin, busStops);
        getline(cin, arrivalTimes);
        
        vector<int> stops = graph.change_string_to_list_of_int(busStops);
        vector<int> times = graph.change_string_to_list_of_int(arrivalTimes);
        startingPoints result;
        if(skip == false){
            result = graph.add_busLine(stops, times,count,numberOfBusstops-1, numberOfBusLines);
        }
        if(result.number == 5656){
            startBus[count] = result;
            count++;
        }
    }
    bool exit = false;
    int maxTime = 0;
    auto g = graph.get_list();
    //Get the maxTime if you would wait at start.
    for (int i = 0; i < startBus.size(); i++) {
        if(startBus[i].time > maxTime){
            maxTime = startBus[i].time;
        }
    }
    //Performing BFS on the graph. And printing the result.
    if(exit == false){
        int result = graph.bfs(0, numberOfBusstops-1, maxTime);

        if (result != -1) {
            cout << result << endl;
        } else {
            cout << -1 << endl;
        }
    }
    return 0;
}