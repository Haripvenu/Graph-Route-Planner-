#include "Graph.h"
#include <queue>
#include <unordered_set>

using namespace std;

int main(){
    Graph city;
    int choice;

    do
    {
        cout << "\n===== GRAPH ROUTE PLANNER =====\n";
        cout << "1. Add Location\n";
        cout << "2. Add Road\n";
        cout << "3. Display Graph\n";
        cout << "4. BFS Traversal\n";
        cout<<"5. DFS Traversal\n";
        cout<<"6. Shortest Path\n";
        cout<<"7.Remove Location\n";
        cout<<"8. Remove  Road\n";
        cout << "9. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string location;
            cout << "Enter location name: ";
            cin >> location;
            city.addLocation(location);
            break;
        }

        case 2:
        {
            string source, destination;
            int distance;

            cout << "Enter source location: ";
            cin >> source;

            cout << "Enter destination location: ";
            cin >> destination;

            cout << "Enter distance (km): ";
            cin >> distance;

            city.addRoad(source, destination, distance);
            break;
        }

        case 3:
            city.displayGraph();
            break;

        case 4:{
            string start;
            cout << "Enter starting location:\n";
            cin >> start;
            city.BFS(start);
            break;
        }
        case 5:{
            string start;
            cout<<"Enter starting location: ";
            cin >>start;
            city.DFS(start);
            break;
        }

        case 6:{
            string source, destination;

            cout << "Enter source: ";
            cin >> source;

            cout << "Enter destination: ";
           cin >> destination;

          city.shortestPath(source, destination);
            break;
        }
        case 7:{
            string location;

            cout<<"Enter location to remove";
            cin>> location;

            city.removeLocation(location);
            break;

        }
        case 8:{
            string source,destination;

            cout<<"Enter source location:";
            cin>> source;

            cout<<"Enter destination location:";
            cin>>destination;

            city.removeRoad(source, destination);
            break;

        }

        case 9:{
            cout<<"Exiting program...\n";
            break;
        }

        default:
            cout << "Invalid choice! Please try again.\n";

    }
 } while (choice != 9);

    return 0;
}
