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
        cout<<"ID: "<<id<<endl;
        cout<<"Type: "<<type<<endl;
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



int main(){
    
    Vehicles v1("1234", "Car");
    Vehicles v2("5678", "Bus");
    Vehicles v3("9101", "Truck");

    que q;
    q.Enqueue(v1);
    q.Enqueue(v2);
    q.Enqueue(v3);

    q.Display();
    q.Front();
    q.Rear();
    q.IsEmpty();
    q.Dequeue();
    q.Display();
    q.Clear();
    q.IsEmpty();

    return 0;
}