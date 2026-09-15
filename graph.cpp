#include "Graph.h"
#include <unordered_set>
#include <queue>
#include <algorithm>
#include <climits>


void Graph::addLocation(string location)
{
    if (adjList.find(location) != adjList.end())
    {
        cout << "Location already exists.\n";
        return;
    }

    adjList[location] = {};
    cout << "Location added successfully.\n";
}

void Graph::addRoad(string source, string destination, int distance)
{
    if (adjList.find(source) == adjList.end())
    {
        cout << "Source location does not exist.\n";
        return;
    }

    if (adjList.find(destination) == adjList.end())
    {
        cout << "Destination location does not exist.\n";
        return;
    }

    if (source == destination)
    {
        cout << "Cannot connect a location to itself.\n";
        return;
    }

    if (distance <= 0)
    {
        cout << "Distance must be greater than 0.\n";
        return;
    }

    // Check for duplicate road
    for (auto road : adjList[source])
    {
        if (road.first == destination)
        {
            cout << "Road already exists.\n";
            return;
        }
    }

    adjList[source].push_back({destination, distance});
    adjList[destination].push_back({source, distance});

    cout << "Road added successfully.\n";
}

void Graph::displayGraph()
{
    if (adjList.empty())
    {
        cout << "\nNo locations available.\n";
        return;
    }

    cout << "\n========== CITY MAP ==========\n";

    for (auto node : adjList)
    {
        cout << node.first << " -> ";

        if (node.second.empty())
        {
            cout << "No connected roads";
        }
        else
        {
            for (auto road : node.second)
            {
                cout << road.first << "("
                     << road.second << " km) ";
            }
        }

        cout << endl;
    }

    cout << "==============================\n";
}

    

void Graph::BFS(string start){
    if (adjList.find(start) == adjList.end())
    {
        cout << "Location does not exist.\n";
        return;
    }

    unordered_set<string> visited;
    queue<string> q;

    visited.insert(start);
    q.push(start);

    cout << "\nBFS Traversal: ";

    while (!q.empty())
    {
        string current = q.front();
        q.pop();

        cout << current << " ";

        for (auto neighbour : adjList[current])
        {
            if (visited.find(neighbour.first) == visited.end())
            {
                visited.insert(neighbour.first);
                q.push(neighbour.first);
            }
        }
    }

    cout << endl;
}
void Graph::DFSHelper(string current, unordered_set<string>& visited)
{
    visited.insert(current);
    cout << current << " ";

    for (auto neighbour : adjList[current])
    {
        if (visited.find(neighbour.first) == visited.end())
        {
            DFSHelper(neighbour.first, visited);
        }
    }
}

void Graph::DFS(string start)
{
    if (adjList.find(start) == adjList.end())
    {
        cout << "Location does not exist.\n";
        return;
    }

    unordered_set<string> visited;

    cout << "\nDFS Traversal: ";
    DFSHelper(start, visited);
    cout << endl;
}
void Graph::shortestPath(string source, string destination)
{
    if (adjList.find(source) == adjList.end() ||
        adjList.find(destination) == adjList.end())
    {
        cout << "One or both locations do not exist.\n";
        return;
    }

    unordered_map<string, int> distance;
    unordered_map<string, string> previous;

    // Min Heap
    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<pair<int, string>>
    > pq;

    // Initialize distances
    for (auto node : adjList)
    {
        distance[node.first] = INT_MAX;
    }

    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty())
    {
        string current = pq.top().second;
        int currentDistance = pq.top().first;
        pq.pop();

        if (currentDistance > distance[current])
            continue;

        for (auto neighbour : adjList[current])
        {
            string next = neighbour.first;
            int weight = neighbour.second;

            if (distance[current] + weight < distance[next])
            {
                distance[next] = distance[current] + weight;
                previous[next] = current;
                pq.push({distance[next], next});
            }
        }
    }

    if (distance[destination] == INT_MAX)
    {
        cout << "No path exists.\n";
        return;
    }

    vector<string> path;

    for (string at = destination; at != ""; at = previous[at])
    {
        path.push_back(at);

        if (at == source)
            break;
    }

    reverse(path.begin(), path.end());

    cout << "\nShortest Path:\n";

    for (int i = 0; i < path.size(); i++)
    {
        cout << path[i];

        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << "\nTotal Distance = "
         << distance[destination]
         << " km\n";
}
void Graph::removeLocation(string location)
{
    if (adjList.find(location) == adjList.end())
    {
        cout << "Location does not exist.\n";
        return;
    }

    // Remove this location from all connected locations
    for (auto &node : adjList)
    {
        auto &roads = node.second;

        roads.erase(
            remove_if(roads.begin(), roads.end(),
                      [&](pair<string, int> road)
                      {
                          return road.first == location;
                      }),
            roads.end());
    }

    // Remove the location itself
    adjList.erase(location);

    cout << "Location removed successfully.\n";
}
void Graph::removeRoad(string source, string destination)
{
    if (adjList.find(source) == adjList.end() ||
        adjList.find(destination) == adjList.end())
    {
        cout << "One or both locations do not exist.\n";
        return;
    }

    auto &sourceRoads = adjList[source];
    sourceRoads.erase(
        remove_if(sourceRoads.begin(), sourceRoads.end(),
                  [&](pair<string, int> road)
                  {
                      return road.first == destination;
                  }),
        sourceRoads.end());

    auto &destinationRoads = adjList[destination];
    destinationRoads.erase(
        remove_if(destinationRoads.begin(), destinationRoads.end(),
                  [&](pair<string, int> road)
                  {
                      return road.first == source;
                  }),
        destinationRoads.end());

    cout << "Road removed successfully.\n";
}