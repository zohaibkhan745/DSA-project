#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <sstream>
using namespace std;

// Task structure
struct Task {
    int id;                // Unique task ID
    string description;    // Task description
    string deadline;       // Task deadline
    bool isCompleted;      // Task status

    Task(int id, string desc, string dl, bool completed = false)
        : id(id), description(desc), deadline(dl), isCompleted(completed) {}
};

// Hash Node (used for chaining in the hash map)
struct HashNode {
    Task task;
    HashNode* next;

    HashNode(Task t) : task(t), next(nullptr) {}
};

// Custom Hash Map class
class CustomHashMap {
private:
    vector<HashNode*> table; // Hash table (array of linked lists)
    int capacity;            // Number of buckets
    int size;                // Number of elements in the map
    string filename;         // File to store tasks

    // Hash function
    int hashFunction(int key) {
        return key % capacity; // Simple modulo operation
    }

    // Write all tasks to the file
    void saveToFile() {
        ofstream outFile(filename);
        if (!outFile) {
            cerr << "Error opening file for writing.\n";
            return;
        }

        for (int i = 0; i < capacity; i++) {
            HashNode* temp = table[i];
            while (temp != nullptr) {
                outFile << temp->task.id << "|"
                        << temp->task.description << "|"
                        << temp->task.deadline << "|"
                        << temp->task.isCompleted << "\n";
                temp = temp->next;
            }
        }

        outFile.close();
    }

    // Read tasks from the file
    void loadFromFile() {
        ifstream inFile(filename);
        if (!inFile) {
            cerr << "Error opening file for reading. Starting fresh.\n";
            return;
        }

        string line;
        while (getline(inFile, line)) {
            stringstream ss(line);
            string idStr, desc, dl, completedStr;
            getline(ss, idStr, '|');
            getline(ss, desc, '|');
            getline(ss, dl, '|');
            getline(ss, completedStr);

            int id = stoi(idStr);
            bool completed = (completedStr == "1");

            addTask(id, desc, dl, completed);
        }

        inFile.close();
    }

public:
    CustomHashMap(const string& user, int cap = 10) : capacity(cap), size(0), filename(user + "_tasks.txt") {
        table.resize(capacity, nullptr); // Initialize the hash table
        loadFromFile(); // Load tasks from file on startup
    }

    // Add a task
    void addTask(int id, string description, string deadline, bool isCompleted = false) {
        int index = hashFunction(id);
        HashNode* newNode = new HashNode(Task(id, description, deadline, isCompleted));

        if (table[index] == nullptr) {
            table[index] = newNode;
        } else {
            // Handle collision using chaining
            HashNode* temp = table[index];
            while (temp->next != nullptr) {
                if (temp->task.id == id) {
                    cout << "Task ID already exists. Use updateTask instead.\n";
                    delete newNode; // Avoid memory leak
                    return;
                }
                temp = temp->next;
            }
            temp->next = newNode;
        }

        size++;
        saveToFile(); // Save to file after adding
        cout << "Task added successfully.\n";
    }

    // Search for a task by ID
    Task* searchTask(int id) {
        int index = hashFunction(id);
        HashNode* temp = table[index];

        while (temp != nullptr) {
            if (temp->task.id == id) {
                return &(temp->task); // Return pointer to the task
            }
            temp = temp->next;
        }

        return nullptr; // Task not found
    }

    // Update a task
    void updateTask(int id, string newDescription, string newDeadline, bool isCompleted) {
        Task* task = searchTask(id);

        if (task != nullptr) {
            task->description = newDescription;
            task->deadline = newDeadline;
            task->isCompleted = isCompleted;
            saveToFile(); // Save to file after updating
            cout << "Task updated successfully.\n";
        } else {
            cout << "Task ID not found.\n";
        }
    }

    // Delete a task by ID
    void deleteTask(int id) {
        int index = hashFunction(id);
        HashNode* temp = table[index];
        HashNode* prev = nullptr;

        while (temp != nullptr && temp->task.id != id) {
            prev = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            cout << "Task ID not found.\n";
            return;
        }

        if (prev == nullptr) {
            table[index] = temp->next; // Remove head node
        } else {
            prev->next = temp->next; // Bypass the node to delete
        }

        delete temp;
        size--;
        saveToFile(); // Save to file after deleting
        cout << "Task deleted successfully.\n";
    }

    // Display all tasks
    void displayTasks() {
        for (int i = 0; i < capacity; i++) {
            HashNode* temp = table[i];
            if (temp != nullptr) {
                cout << "Bucket " << i << ":\n";
                while (temp != nullptr) {
                    cout << "  Task ID: " << temp->task.id << "\n"
                         << "  Description: " << temp->task.description << "\n"
                         << "  Deadline: " << temp->task.deadline << "\n"
                         << "  Status: " << (temp->task.isCompleted ? "Completed" : "Pending") << "\n";
                    temp = temp->next;
                }
            }
        }
    }
};

int TODO(const string& username) {
    CustomHashMap toDoList(username, 10); // Pass the username to the hash map

    int choice, id;
    string description, deadline;
    bool isCompleted;

    while (true) {
        cout << "\n1. Add Task\n2. Search Task\n3. Update Task\n4. Delete Task\n5. Display Tasks\n6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter Task ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Description: ";
                getline(cin, description);
                cout << "Enter Deadline: ";
                getline(cin, deadline);
                toDoList.addTask(id, description, deadline);
                break;
            case 2:
                cout << "Enter Task ID: ";
                cin >> id;
                if (Task* task = toDoList.searchTask(id)) {
                    cout << "Task found:\n";
                    cout << "  Task ID: " << task->id << "\n"
                         << "  Description: " << task->description << "\n"
                         << "  Deadline: " << task->deadline << "\n"
                         << "  Status: " << (task->isCompleted ? "Completed" : "Pending") << "\n";
                } else {
                    cout << "Task not found.\n";
                }
                break;
            case 3:
                cout << "Enter Task ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter New Description: ";
                getline(cin, description);
                cout << "Enter New Deadline: ";
                getline(cin, deadline);
                cout << "Is the task completed? (1 for yes, 0 for no): ";
                cin >> isCompleted;
                toDoList.updateTask(id, description, deadline, isCompleted);
                break;
            case 4:
                cout << "Enter Task ID: ";
                cin >> id;
                toDoList.deleteTask(id);
                break;
            case 5:
                toDoList.displayTasks();
                break;
            case 6:
                exit(0);
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}