#include <iostream>
using namespace std;

class Node{
    public:
    string data;
    Node* next;

    Node(){
        data = "";
        next = nullptr;
    }

    Node(string data){
        this-> data = data;
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

    void Enqueue(string data){
        Node* newNode = new Node(data);

        if (front == nullptr){
            front = rear = newNode;
        }
        rear->next = newNode;
        rear = newNode;

    } 

    void Dequeue(){
        if (front == nullptr){
            cout<<"The queue is empty"<<endl;
            return;
        }
        Node* temp = front;
        front = front->next;
        delete temp;
    }

    void Display(){
        Node* temp = front;
        while (temp != nullptr){
            cout<<temp->data<<" ";
            temp = temp->next;
        }
        cout<<endl;
    }

    void Front(){
        if (front == nullptr){
            cout<<"The queue is empty"<<endl;
            return;
        }
        cout<<front->data<<endl;
    }

    void Rear(){
        if (rear == nullptr){
            cout<<"The queue is empty"<<endl;
            return;
        }
        cout<<rear->data<<endl;
    }

    void IsEmpty(){
        if (front == nullptr){
            cout<<"The queue is empty"<<endl;
        }
        else{
            cout<<"The queue is not empty"<<endl;
        }
    }

    void Clear(){
        while (front != nullptr){
            Node* temp = front;
            front = front->next;
            delete temp;
        }
    }

    ~que(){
        Clear();
    }
    
};

class Vehicles{
    public:
    
};

int main(){
    
}