#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

class Stack {
    vector<string> stack;

public:
    void push(string name) {
        stack.push_back(name);
    }

    void pop() {
        if (!stack.empty()) {
            stack.pop_back();
        }
    }

    string top() {
        if (!stack.empty()) {
            return stack.back();
        }
        return "";
    }

    bool empty() {
        return stack.empty();
    }
};

class Graph {
    unordered_map<string, vector<pair<string, int>>> adjList;

public:
    void addEdge(string u, string v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});
    }

    void displayGraph() {
        cout << "Graph Representation:" << endl;
        for (auto& node : adjList) {
            cout << node.first << " -> ";
            for (auto& neighbor : node.second) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    void bfs(string start) {
        queue<string> q;
        unordered_map<string, bool> visited;

        q.push(start);
        visited[start] = true;

        cout << "BFS Traversal starting from " << start << ": ";
        while (!q.empty()) {
            string node = q.front();
            q.pop();
            cout << node << " ";

            for (auto& neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    void dfsUtil(string node, unordered_map<string, bool>& visited) {
        cout << node << " ";
        visited[node] = true;

        for (auto& neighbor : adjList[node]) {
            if (!visited[neighbor.first]) {
                dfsUtil(neighbor.first, visited);
            }
        }
    }

    void dfs(string start) {
        unordered_map<string, bool> visited;
        cout << "DFS Traversal starting from " << start << ": ";
        dfsUtil(start, visited);
        cout << endl;
    }

    void ambulanceRouteOptimization(string start, string end) {
        unordered_map<string, int> distance;
        unordered_map<string, string> parent;
        for (auto& node : adjList) {
            distance[node.first] = INT_MAX;
        }
        distance[start] = 0;

        priority_queue<pair<int, string>, vector<pair<int, string>>, greater<pair<int, string>>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            string current = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();

            if (current == end) break;

            for (auto& neighbor : adjList[current]) {
                int newDist = currentDist + neighbor.second;
                if (newDist < distance[neighbor.first]) {
                    distance[neighbor.first] = newDist;
                    pq.push({newDist, neighbor.first});
                    parent[neighbor.first] = current;
                }
            }
        }

        if (distance[end] == INT_MAX) {
            cout << "No route found from " << start << " to " << end << endl;
        } else {
            cout << "Optimized Route (Ambulance): ";
            string node = end;
            Stack path;
            while (node != start) {
                path.push(node);
                node = parent[node];
            }
            path.push(start);
            while (!path.empty()) {
                cout << path.top();
                path.pop();
                if (!path.empty()) cout << " -> ";
            }
            cout << " | Distance: " << distance[end] << endl;
        }
    }
};

class CrowdControl {
    Stack crowdStack;
    queue<string> crowdQueue;

public:
    void addPersonToStack(string name) {
        crowdStack.push(name);
        cout << name << " added to Stack." << endl;
    }

    void removePersonFromStack() {
        if (!crowdStack.empty()) {
            cout << crowdStack.top() << " removed from Stack." << endl;
            crowdStack.pop();
        } else {
            cout << "No one in the Stack." << endl;
        }
    }

    void addPersonToQueue(string name) {
        crowdQueue.push(name);
        cout << name << " added to Queue." << endl;
    }

    void removePersonFromQueue() {
        if (!crowdQueue.empty()) {
            cout << crowdQueue.front() << " removed from Queue." << endl;
            crowdQueue.pop();
        } else {
            cout << "No one in the Queue." << endl;
        }
    }
};

int main() {
    Graph emergencyGraph;
    CrowdControl crowdControl;

    emergencyGraph.addEdge("Hospital", "Fire Station", 5);
    emergencyGraph.addEdge("Hospital", "Police Station", 3);
    emergencyGraph.addEdge("Fire Station", "Accident Site", 8);
    emergencyGraph.addEdge("Police Station", "Accident Site", 6);
    emergencyGraph.addEdge("Hospital", "Accident Site", 10);

    int choice;
    do {
        cout << "\nEmergency Services Menu:" << endl;
        cout << "1. Display Graph" << endl;
        cout << "2. BFS Traversal (Enter starting location, e.g., Hospital)" << endl;
        cout << "3. DFS Traversal (Enter starting location, e.g., Hospital)" << endl;
        cout << "4. Ambulance Route Optimization (Enter starting and destination locations, e.g., Hospital and Accident Site)" << endl;
        cout << "5. Add Person to Crowd Stack (Enter name of person)" << endl;
        cout << "6. Remove Person from Crowd Stack" << endl;
        cout << "7. Add Person to Crowd Queue (Enter name of person)" << endl;
        cout << "8. Remove Person from Crowd Queue" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            emergencyGraph.displayGraph();
            break;

        case 2: {
            string start;
            cout << "Enter starting location (e.g., Hospital): ";
            cin >> start;
            emergencyGraph.bfs(start);
            break;
        }

        case 3: {
            string start;
            cout << "Enter starting location (e.g., Hospital): ";
            cin >> start;
            emergencyGraph.dfs(start);
            break;
        }

        case 4: {
            string start, end;
            cout << "Enter starting location (e.g., Hospital): ";
            cin >> start;
            cout << "Enter destination location (e.g., Accident Site): ";
            cin >> end;
            emergencyGraph.ambulanceRouteOptimization(start, end);
            break;
        }

        case 5: {
            string name;
            cout << "Enter person name to add to Stack: ";
            cin >> name;
            crowdControl.addPersonToStack(name);
            break;
        }

        case 6:
            crowdControl.removePersonFromStack();
            break;

        case 7: {
            string name;
            cout << "Enter person name to add to Queue: ";
            cin >> name;
            crowdControl.addPersonToQueue(name);
            break;
        }

        case 8:
            crowdControl.removePersonFromQueue();
            break;

        case 9:
            cout << "Exiting Emergency Services System." << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 9);

    return 0;
}
