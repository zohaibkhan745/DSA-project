#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <climits>

using namespace std;

// Helper function to find the index of a node in the graph
int findNodeIndex(const vector<string>& nodes, const string& node) {
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (nodes[i] == node) {
            return i;
        }
    }
    return -1;
}

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

    void clear() {
        stack.clear();
    }

    void display() {
        if (stack.empty()) {
            cout << "Stack is empty." << endl;
        } else {
            cout << "Stack contents: ";
            for (auto it = stack.rbegin(); it != stack.rend(); ++it) {
                cout << *it << " ";
            }
            cout << endl;
        }
    }
};

class Graph {
    vector<string> nodes;
    vector<vector<pair<int, int>>> adjList;

    void dfsUtil(int nodeIndex, vector<bool>& visited) {
        visited[nodeIndex] = true;
        cout << nodes[nodeIndex] << " ";

        for (auto& neighbor : adjList[nodeIndex]) {
            if (!visited[neighbor.first]) {
                dfsUtil(neighbor.first, visited);
            }
        }
    }

public:
    void addEdge(string u, string v, int weight) {
        int uIndex = findNodeIndex(nodes, u);
        if (uIndex == -1) {
            nodes.push_back(u);
            adjList.push_back({});
            uIndex = nodes.size() - 1;
        }

        int vIndex = findNodeIndex(nodes, v);
        if (vIndex == -1) {
            nodes.push_back(v);
            adjList.push_back({});
            vIndex = nodes.size() - 1;
        }

        adjList[uIndex].push_back({vIndex, weight});
        adjList[vIndex].push_back({uIndex, weight});
    }

    void displayGraph() {
        cout << "Graph Representation:" << endl;
        for (size_t i = 0; i < nodes.size(); ++i) {
            cout << nodes[i] << " -> ";
            for (auto& neighbor : adjList[i]) {
                cout << "(" << nodes[neighbor.first] << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }

    void bfs(string start) {
        int startIndex = findNodeIndex(nodes, start);
        if (startIndex == -1) {
            cout << "Start node not found in graph." << endl;
            return;
        }

        vector<bool> visited(nodes.size(), false);
        queue<int> q;

        q.push(startIndex);
        visited[startIndex] = true;

        cout << "BFS Traversal starting from " << start << ": ";
        while (!q.empty()) {
            int currentNode = q.front();
            q.pop();

            cout << nodes[currentNode] << " ";

            for (auto& neighbor : adjList[currentNode]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    void dfs(string start) {
        int startIndex = findNodeIndex(nodes, start);
        if (startIndex == -1) {
            cout << "Start node not found in graph." << endl;
            return;
        }

        vector<bool> visited(nodes.size(), false);
        cout << "DFS Traversal starting from " << start << ": ";
        dfsUtil(startIndex, visited);

        // Handle disconnected components
        for (size_t i = 0; i < nodes.size(); ++i) {
            if (!visited[i]) {
                dfsUtil(i, visited);
            }
        }
        cout << endl;
    }

    void ambulanceRouteOptimization(string start, string end) {
        int startIndex = findNodeIndex(nodes, start);
        int endIndex = findNodeIndex(nodes, end);

        if (startIndex == -1 || endIndex == -1) {
            cout << "Start or end node not found in graph." << endl;
            return;
        }

        vector<int> distance(nodes.size(), INT_MAX);
        vector<int> parent(nodes.size(), -1);
        distance[startIndex] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
        pq.push({0, startIndex});

        while (!pq.empty()) {
            int current = pq.top().second;
            int currentDist = pq.top().first;
            pq.pop();

            if (current == endIndex) break;

            for (auto& neighbor : adjList[current]) {
                int newDist = currentDist + neighbor.second;
                if (newDist < distance[neighbor.first]) {
                    distance[neighbor.first] = newDist;
                    pq.push({newDist, neighbor.first});
                    parent[neighbor.first] = current;
                }
            }
        }

        if (distance[endIndex] == INT_MAX) {
            cout << "No route found from " << start << " to " << end << endl;
        } else {
            cout << "Optimized Route (Ambulance): ";
            Stack path;
            int node = endIndex;
            while (node != -1) {
                path.push(nodes[node]);
                node = parent[node];
            }
            while (!path.empty()) {
                cout << path.top();
                path.pop();
                if (!path.empty()) cout << " -> ";
            }
            cout << " | Distance: " << distance[endIndex] << endl;
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

    void emptyCrowdStack() {
        if (!crowdStack.empty()) {
            cout << "People removed from Stack in order: ";
            while (!crowdStack.empty()) {
                cout << crowdStack.top() << " ";
                crowdStack.pop();
            }
            cout << endl;
        } else {
            cout << "Crowd Stack is already empty." << endl;
        }
        cout << "Crowd Stack has been emptied." << endl;
    }

    void displayCrowdStack() {
        crowdStack.display();
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

    void emptyCrowdQueue() {
        if (!crowdQueue.empty()) {
            cout << "People removed from Queue in order: ";
            while (!crowdQueue.empty()) {
                cout << crowdQueue.front() << " ";
                crowdQueue.pop();
            }
            cout << endl;
        } else {
            cout << "Crowd Queue is already empty." << endl;
        }
        cout << "Crowd Queue has been emptied." << endl;
    }

    void displayCrowdQueue() {
        if (crowdQueue.empty()) {
            cout << "Queue is empty." << endl;
        } else {
            cout << "Queue contents: ";
            queue<string> tempQueue = crowdQueue;
            while (!tempQueue.empty()) {
                cout << tempQueue.front() << " ";
                tempQueue.pop();
            }
            cout << endl;
        }
    }
};

int EmergencyServices() {
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
        cout << "2. BFS Traversal" << endl;
        cout << "3. DFS Traversal" << endl;
        cout << "4. Ambulance Route Optimization" << endl;
        cout << "5. Add Person to Crowd Stack" << endl;
        cout << "6. Remove Person from Crowd Stack" << endl;
        cout << "7. Display Crowd Stack" << endl;
        cout << "8. Add Person to Crowd Queue" << endl;
        cout << "9. Remove Person from Crowd Queue" << endl;
        cout << "10. Display Crowd Queue" << endl;
        cout << "11. Empty Crowd Stack" << endl;
        cout << "12. Empty Crowd Queue" << endl;
        cout << "13. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            emergencyGraph.displayGraph();
            break;

        case 2: {
            string start;
            cin.ignore();
            cout << "Enter starting location: ";
            getline(cin, start);
            emergencyGraph.bfs(start);
            break;
        }

        case 3: {
            string start;
            cin.ignore();
            cout << "Enter starting location: ";
            getline(cin, start);
            emergencyGraph.dfs(start);
            break;
        }

        case 4: {
            string start, end;
            cin.ignore();
            cout << "Enter starting location: ";
            getline(cin, start);
            cout << "Enter destination location: ";
            getline(cin, end);
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

        case 7:
            crowdControl.displayCrowdStack();
            break;

        case 8: {
            string name;
            cout << "Enter person name to add to Queue: ";
            cin >> name;
            crowdControl.addPersonToQueue(name);
            break;
        }

        case 9:
            crowdControl.removePersonFromQueue();
            break;

        case 10:
            crowdControl.displayCrowdQueue();
            break;

        case 11:
            crowdControl.emptyCrowdStack();
            break;

        case 12:
            crowdControl.emptyCrowdQueue();
            break;

        case 13:
            cout << "Exiting Emergency Services System." << endl;
            break;

        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 13);

    return 0;
}
