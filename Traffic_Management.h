#include <iostream>
#include <vector>
#include <string>
#include <fstream> // For file handling
using namespace std;

class Vehicles{
    public:
    string id;
    string type;

    Vehicles(){
        id = "";
        type = "";
    }

    Vehicles(string id, string type){
        this->id = id;
        this->type = type;
    }

    void displayInfo(){
        cout<<" <-- ID: "<<id;
    }
    
};

class Node{
    public:
    Vehicles data;
    Node* next;

    Node(){
        data = Vehicles();
        next = nullptr;
    }

    Node(Vehicles data){
        this->data = data;
        next = nullptr;
    }
};

class ListQue{
    Node* front;
    Node* rear;

    public:
    ListQue(){
        front = nullptr;
        rear = nullptr;
    }

    void Enqueue(Vehicles data){
        Node* newNode = new Node(data);

        if (front == nullptr){
            front = rear = newNode;
        }
        else{
            rear->next = newNode;
            rear = newNode;
        }

    } 

    void Dequeue() {
        if (front == nullptr) {
            cout << "The queue is empty" << endl;
            return;
        }
        Node* temp = front;
        ofstream file("passed_vehicles.txt", ios::app);
        if (file.is_open()) {
            file << temp->data.id << endl; // Log the ID of the removed vehicle
            file.close();
        } else {
            cout << "Error: Unable to open the file for logging vehicle IDs." << endl;
        }

        cout << "Removing Vehicle ID: " << temp->data.id << " from the lane." << endl; // Added message
        front = front->next;
        delete temp;
        if (front == nullptr) { // Reset rear if queue is empty after dequeue
            rear = nullptr;
        }
    }

    void Display(){
        Node* temp = front;
        while (temp != nullptr){
            temp->data.displayInfo();
            temp = temp->next;
        }
        cout<<endl;
    }

    void Front(){
        if (front == nullptr){
            cout<<"The queue is empty"<<endl;
            return;
        }
        front->data.displayInfo();
    }

    void Rear(){
        if (rear == nullptr){
            cout<<"The queue is empty"<<endl;
            return;
        }
        rear->data.displayInfo();
    }

    void IsEmpty(){
        if (front == nullptr){
            cout<<"The queue is empty"<<endl;
        }
        else{
            cout<<"The queue is not empty"<<endl;
        }
    }

    void Clear() {
    while (front != nullptr) {
        Node* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;  // Reset rear to null after clearing
}

    ~ListQue(){
        Clear();
    }
    
};

class ArrayQue{
    public:
    int rear, front;
    static const int size = 100;
    Vehicles arr[size]; 

    ArrayQue(){
        rear = front = -1;
    }

    bool isFull(){
        return (rear == size - 1); 
    }

    bool isEmpty(){
        return front == -1;
    }

    void Enqueue(Vehicles value){
        if (isFull()){
            cout<<"The Lane is full, you can't add more vehicles!"<<endl;
            return;
        }
        if (isEmpty()){
            front = rear = 0;
            arr[rear] = value;
            return;
        }
        arr[++rear] = value; 
    }

    void Dequeue() {
    if (isEmpty()) {
        cout << "The Lane is already Empty!" << endl;
        return;
    }
    ofstream file("passed_vehicles.txt", ios::app);
        if (file.is_open()) {
            file << arr[front].id << endl;
            file.close();
        } else {
            cout << "Error: Unable to open the file for logging vehicle IDs." << endl;
        }

    cout << "Removing Vehicle ID: " << arr[front].id << " from the lane." << endl; // Added message
    if (front == rear) {
        front = rear = -1;
    } else {
        front++;
    }
}

    void Display(){
        for (int i = front; i <= rear; i++){
            arr[i].displayInfo();
        }
    }
};

class TrafficSignal{
    public:
    string state;
    int duration;

    TrafficSignal(){
        state = "Red";
        duration = 10;
    }

    void changeSignal(int elapsedTime) {
        while (elapsedTime > 0) {
            if (elapsedTime < duration) {
                duration -= elapsedTime;
                break;
            }
            elapsedTime -= duration;
            if (state == "Red") {
                state = "Green";
                duration = 15;
            } else if (state == "Green") {
                state = "Yellow";
                duration = 5;
            } else if (state == "Yellow") {
                state = "Red";
                duration = 10;
            }
        }
}


    void displaySignal() {
        cout << "Signal: " << state << " | Remaining Duration: " << duration << " seconds" << endl;
    }

    bool canPass(){
        return state == "Green";
    }
};

class Road {
public:
    ListQue TruckLane_list;
    ListQue CarLane_list;
    ListQue BikeLane_list;

    ArrayQue TruckLane_array;
    ArrayQue CarLane_array;
    ArrayQue BikeLane_array;

    TrafficSignal TruckSignal;
    TrafficSignal CarSignal;
    TrafficSignal BikeSignal;

    int inputMode; // 1 for Linked List, 2 for Array

    Road() {
        inputMode = 0;
    }

    void setInputMode() {
    cout << "1. Use Linked List." << endl;
    cout << "2. Use Array." << endl;
    cout << "Enter choice: ";
    cin >> inputMode;
    if (inputMode != 1 && inputMode != 2) {
        cout << "Invalid choice. Defaulting to Linked List." << endl;
        inputMode = 1;
    } else {
        cout << (inputMode == 1 ? "Using Linked List" : "Using Array") << " for lane management." << endl;
    }
}


    void AddVehiclesToLane(Vehicles vehicle) {

        if (vehicle.type != "Truck" && vehicle.type != "Car" && vehicle.type != "Bike") {
        cout << "Invalid vehicle type. Please enter Truck, Car, or Bike." << endl;
        return;
    }
        if (inputMode == 1) {
            if (vehicle.type == "Truck") {
                TruckLane_list.Enqueue(vehicle);
            } else if (vehicle.type == "Car") {
                CarLane_list.Enqueue(vehicle);
            } else if (vehicle.type == "Bike") {
                BikeLane_list.Enqueue(vehicle);
            } else {
                cout << "Unknown Vehicle type" << endl;
            }
        } else if (inputMode == 2) {
            if (vehicle.type == "Truck") {
                TruckLane_array.Enqueue(vehicle);
            } else if (vehicle.type == "Car") {
                CarLane_array.Enqueue(vehicle);
            } else if (vehicle.type == "Bike") {
                BikeLane_array.Enqueue(vehicle);
            } else {
                cout << "Unknown Vehicle type" << endl;
            }
        }
    }

    void DequeueVehiclesFromLanes(string LaneType) {
        if (inputMode == 1) {
            if (LaneType == "Truck") {
                if (TruckSignal.canPass()) {
                    TruckLane_list.Dequeue();
                } else {
                    cout << "Truck Lane Signal is not Green! Please wait" << endl;
                }
            } else if (LaneType == "Car") {
                if (CarSignal.canPass()) {
                    CarLane_list.Dequeue();
                } else {
                    cout << "Car Lane Signal is not Green! Please wait" << endl;
                }
            } else if (LaneType == "Bike") {
                if (BikeSignal.canPass()) {
                    BikeLane_list.Dequeue();
                } else {
                    cout << "Bike Lane Signal is not Green! Please wait" << endl;
                }
            }
        } else if (inputMode == 2) {
            if (LaneType == "Truck") {
                if (TruckSignal.canPass()) {
                    TruckLane_array.Dequeue();
                } else {
                    cout << "Truck Lane Signal is not Green! Please wait" << endl;
                }
            } else if (LaneType == "Car") {
                if (CarSignal.canPass()) {
                    CarLane_array.Dequeue();
                } else {
                    cout << "Car Lane Signal is not Green! Please wait" << endl;
                }
            } else if (LaneType == "Bike") {
                if (BikeSignal.canPass()) {
                    BikeLane_array.Dequeue();
                } else {
                    cout << "Bike Lane Signal is not Green! Please wait" << endl;
                }
            }
        }
    }

    void DisplayAllLanes() {
        if (inputMode == 1) {
            cout << "\nTrucks Lane (Linked List): ";
            TruckLane_list.Display();

            cout << "\nCars Lane (Linked List): ";
            CarLane_list.Display();

            cout << "\nBikes Lane (Linked List): ";
            BikeLane_list.Display();
        } else if (inputMode == 2) {
            cout << "\nTrucks Lane (Array): ";
            TruckLane_array.Display();

            cout << "\nCars Lane (Array): ";
            CarLane_array.Display();

            cout << "\nBikes Lane (Array): ";
            BikeLane_array.Display();
        }
    }

    void updateAllSignals(int elapsedTime) {
        TruckSignal.changeSignal(elapsedTime);
        CarSignal.changeSignal(elapsedTime);
        BikeSignal.changeSignal(elapsedTime);
    }

    void displayAllSignals() {
        cout << "\nTruck lane Signal: ";
        TruckSignal.displaySignal();

        cout << "Car Lane Signal: ";
        CarSignal.displaySignal();

        cout << "Bike lane Signal: ";
        BikeSignal.displaySignal();
    }
};

void bubbleSort(vector<string>& ids) {
    int n = ids.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (ids[j] > ids[j + 1]) {
                string temp = ids[j];
                ids[j] = ids[j + 1];
                ids[j + 1] = temp;
            }
        }
    }
}

void insertionSort(vector<string>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        string key = arr[i];
        int j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<string>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }
}

void merge(vector<string>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<string> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;

    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<string>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);

        merge(arr, left, mid, right);
    }
}

int partition(vector<string>& arr, int low, int high) {
    string pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<string>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


void sortPassedVehicles(int algorithmChoice) {
    ifstream inputFile("passed_vehicles.txt");
    vector<string> ids;

    if (!inputFile.is_open()) {
        cout << "Error: Unable to open the file for reading vehicle IDs." << endl;
        return;
    }

    string id;
    while (getline(inputFile, id)) {
        ids.push_back(id); // Read IDs into the vector
    }
    inputFile.close();

    if (ids.empty()) {
        cout << "No vehicle IDs to sort!" << endl;
        return;
    }

    for (string s : ids){
        cout<<s<<" ";
    }

    switch (algorithmChoice) {
        case 1:
            bubbleSort(ids);
            break;
        case 2:
            insertionSort(ids);
            break;
        case 3:
            selectionSort(ids);
            break;
        case 4:
            mergeSort(ids, 0, ids.size() - 1);
            break;
        case 5:
            quickSort(ids, 0, ids.size() - 1);
            break;
        default:
            cout << "Invalid sorting algorithm choice!" << endl;
            return;
    }
    cout<<endl; 
    for (string s : ids){
        cout<<s<<" ";
    }


    ofstream outputFile("passed_vehicles.txt"); // Open file in truncate mode
    if (!outputFile.is_open()) {
        cout << "Error: Unable to open the file for writing sorted vehicle IDs." << endl;
        return;
    }

    for (const string& sortedId : ids) {
        outputFile << sortedId << endl; // Write sorted IDs back to the file
    }
    outputFile.close();

    cout << "Vehicle IDs have been sorted and updated in the file!" << endl;
}


int TrafficManagement() {
    system("CLS");
    Road road;
    road.setInputMode();

    int choice;
    do {
        cout << "\nTraffic Management System Menu:" << endl;
        cout << "1. Add Vehicle to Lane" << endl;
        cout << "2. Remove Vehicle from Lane" << endl;
        cout << "3. Display All Lanes" << endl;
        cout << "4. Update Traffic Signals" << endl;
        cout << "5. Display Traffic Signals" << endl;
        cout << "6. Sort Vehicle IDs" << endl; 
        cout << "7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            string id, type;
            cout << "Enter Vehicle ID: ";
            cin >> id;
            cout << "Enter Vehicle Type (Truck/Car/Bike): ";
            cin >> type;
            road.AddVehiclesToLane(Vehicles(id, type));
            break;
        }

        case 2: {
            string laneType;
            cout << "Enter Lane Type to Remove Vehicle (Truck/Car/Bike): ";
            cin >> laneType;
            road.DequeueVehiclesFromLanes(laneType);
            break;
        }

        case 3:
            road.DisplayAllLanes();
            break;

        case 4: { 
        int elapsedTime; 
        cout << "Enter elapsed time in seconds to update signals: "; 
        cin >> elapsedTime; 
        road.updateAllSignals(elapsedTime); 
        cout << "Signals updated!" << endl; 
        break; 
    }
        case 5:
            road.displayAllSignals();
            break;

        case 6: {
            int sortChoice;
            cout << "Select Sorting Algorithm:" << endl;
            cout << "1. Bubble Sort" << endl;
            cout << "2. Insertion Sort" << endl;
            cout << "3. Selection Sort" << endl;
            cout << "4. Merge Sort" << endl;
            cout << "5. Quick Sort" << endl;
            cout << "Enter your choice: ";
            cin >> sortChoice;

            sortPassedVehicles(sortChoice); 
            break;
        }

        case 7:
            cout << "Exiting the system. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 7);

    return 0;
}