#include <iostream>
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
        // cout<<" Type: "<<type;
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

class que{
    Node* front;
    Node* rear;

    public:
    que(){
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
    front = front->next;
    delete temp;
    if (front == nullptr) {  // Reset rear if queue is empty after dequeue
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

    ~que(){
        Clear();
    }
    
};

class TrafficSignal{
    public:
    string state;
    int duration;

    TrafficSignal(){
        state = "Red";
        duration = 0;
    }

    void changeSignal(){
        if (state == "Red"){
            state = "Green";
        }
        else if (state == "Green"){
            state = "Yellow";
        }
        else if (state == "Yellow"){
            state = "Red";
        }    
    }

    void DisplaySignal(){
        cout<<"Signla : "<<state<<endl;
    }

    bool canPass(){
        return state == "Green";
    }
};
class Road{
    public:
    que TruckLane;
    que CarLane;
    que BikeLane;
    TrafficSignal TruckSignal;
    TrafficSignal CarSignal;
    TrafficSignal BikeSignal;

    void AddVehiclesToLane(Vehicles vehicle){
        if (vehicle.type == "Truck"){
            TruckLane.Enqueue(vehicle);
        }
        else if(vehicle.type == "Car"){
            CarLane.Enqueue(vehicle);
        }
        else if(vehicle.type == "Bike"){
            BikeLane.Enqueue(vehicle);
        }
        else{
            cout<<"Unknown Vehicle type"<<endl;
        }
    }

    void DisplayAllLanes(){
        cout<<"\nTrucks Lane : ";
        TruckLane.Display();

        cout<<"\nCars Lane : ";
        CarLane.Display();
        
        cout<<"\nBikes Lane : ";
        BikeLane.Display();
    }

    void DequeueVehiclesFromLanes(string LaneType){
        if (LaneType == "Truck"){
            if (TruckSignal.canPass()){
                TruckLane.Dequeue();
            }
            else{
                cout<<"Truck Lane Signal is not Green! Please wait"<<endl;
            }
        }
        if (LaneType == "Car"){
            if (CarSignal.canPass()){
                CarLane.Dequeue();
            }
            else{
                cout<<"Car Lane Signal is not Green! Please wait"<<endl;
            }
        }
        if (LaneType == "Bike"){
            if (BikeSignal.canPass()){
                BikeLane.Dequeue();
            }
            else{
                cout<<"Bike Lane Signal is not Green! Please wait"<<endl;
            }
        }
    }
};


int main(){
    // Create some vehicles
    Vehicles v1("1234", "Car");
    Vehicles v2("5678", "Truck");
    Vehicles v3("9101", "Bike");
    Vehicles v4("1122", "Car");
    Vehicles v5("3344", "Truck");

    // Create a road instance
    Road road;

    // Add vehicles to the respective lanes
    road.AddVehiclesToLane(v1);
    road.AddVehiclesToLane(v2);
    road.AddVehiclesToLane(v3);
    road.AddVehiclesToLane(v4);
    road.AddVehiclesToLane(v5);

    // Display all lanes
    road.DisplayAllLanes();

    // Remove a vehicle from TruckLane
    cout << "\nRemoving a truck from the Truck Lane:\n";
    road.TruckLane.Dequeue();
    road.DisplayAllLanes();

    return 0;
}