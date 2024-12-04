#include<iostream>
#include<string>
using namespace std;
class Node{
     public:
    string name;
    string password;
    string email;
    Node* Next;
    Node* prev;
   
    Node(string name, string password, string email){
        this->name = name;
        this->password = password;
        this->email = email;
        Next = NULL;
        prev = NULL;
    }
};
class userData{
    public:
    Node* head;
    Node* tail;
    userData(){
        head = NULL;
        tail = NULL;
    }
    Node* insert(){
        string name, password, email;
        cout<<"Name: ";
        getline(cin, name);
        cout<<"Password: ";
        getline(cin, password);
        cout<<"Email: ";
       getline(cin, email);
        Node* temp = new Node(name, password, email);
        if(head == NULL){
            head = temp;
            tail = temp;
        }
        else{
            tail->Next = temp;
            temp->prev = tail;
            tail = temp;
        }
        cout<<"Registeration Successful\n";
        
    }
    void display(){
            Node* temp = head;
            while(temp != NULL){
                cout<<"Name: "<<temp->name<<endl;
                cout<<"Password: "<<temp->password<<endl;
                cout<<"Email: "<<temp->email<<endl;
                temp = temp->Next;
            }
        }
        
};
int main()
{
    Node* head = NULL;
    userData userdata;
    userdata.insert();
    userdata.display();
    
   
    return 0;
}