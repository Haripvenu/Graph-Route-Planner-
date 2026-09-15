#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <limits>
#include <unordered_set>
#include <queue>

using namespace std;

class Graph
{
private:
    unordered_map<string, vector<pair<string, int>>> adjList;
    void DFSHelper(string current,unordered_set<string>& visited);

public:
    void addLocation(string location);
    void addRoad(string source, string destination, int distance);
    void displayGraph();
    void BFS(string start);
    void DFS(string start);
    void shortestPath(string source,string destination);
    void removeLocation(string location);
    void removeRoad(string source, string destination);
};

#endif