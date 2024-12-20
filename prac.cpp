#include <iostream>
#include <vector>
#include <string>
using namespace std;

// User Struct
struct User {
    string email;
    string password;
    string name;
    double electricityBill;
    double waterBill;
    User* next; // For chaining in case of collision
};

// Hash Table for User Management
class UserHashTable {
private:
    vector<User*> table; // Array of linked lists
    int size;

    int hashFunction(const string& key) {
        int hash = 0;
        for (char c : key) {
            hash = (hash * 31 + c) % size; // Simple hash function
        }
        return hash;
    }

public:
    UserHashTable(int s) : size(s) {
        table.resize(size, nullptr);
    }

    void registerUser() {
        string email, password, name;
        cout << "Enter Email: ";
        cin >> email;
        cout << "Enter Password: ";
        cin >> password;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);

        int index = hashFunction(email);
        User* newUser = new User{email, password, name, 0.0, 0.0, nullptr};
        newUser->next = table[index];
        table[index] = newUser;
        cout << "User registered successfully.\n";
    }

    User* findUser() {
        string email;
        cout << "Enter Email to Search: ";
        cin >> email;
        int index = hashFunction(email);
        User* temp = table[index];
        while (temp) {
            if (temp->email == email)
                return temp;
            temp = temp->next;
        }
        cout << "User not found!\n";
        return nullptr;
    }

    void displayUsers() {
        for (int i = 0; i < size; i++) {
            cout << "Index " << i << ": ";
            User* temp = table[i];
            while (temp) {
                cout << temp->name << " (" << temp->email << ") -> ";
                temp = temp->next;
            }
            cout << "null\n";
        }
    }
};

// Bill Management
class BillManager {
private:
    double electricityIncrement;
    double waterIncrement;

public:
    BillManager(double elecInc, double waterInc)
        : electricityIncrement(elecInc), waterIncrement(waterInc) {}

    void increaseBills(User* user) {
        if (user) {
            user->electricityBill += electricityIncrement;
            user->waterBill += waterIncrement;
        }
    }

    void checkBills(User* user) {
        if (user) {
            cout << "Electricity Bill: $" << user->electricityBill << "\n";
            cout << "Water Bill: $" << user->waterBill << "\n";
        } else {
            cout << "User not found.\n";
        }
    }

    void payBills(User* user) {
        if (user) {
            cout << "Paying bills for " << user->name << "...\n";
            cout << "Electricity Bill Paid: $" << user->electricityBill << "\n";
            cout << "Water Bill Paid: $" << user->waterBill << "\n";
            user->electricityBill = 0.0;
            user->waterBill = 0.0;
        } else {
            cout << "User not found.\n";
        }
    }
};

// Main Function with Menu
int main() {
    UserHashTable userTable(10);
    BillManager billManager(5.0, 2.0); // Bills increase by $5 (electricity) and $2 (water) per interaction
    int choice;

    do {
        cout << "\n--- Utility Management System ---\n";
        cout << "1. Register New User\n";
        cout << "2. Find User\n";
        cout << "3. Display All Users\n";
        cout << "4. Increase Bills (System Event)\n";
        cout << "5. Check Bills\n";
        cout << "6. Pay Bills\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            userTable.registerUser();
            break;
        case 2: {
            User* user = userTable.findUser();
            if (user) {
                cout << "User Found: " << user->name << "\n";
                cout << "Email: " << user->email << "\n";
            }
            break;
        }
        case 3:
            userTable.displayUsers();
            break;
        case 4: {
            User* user = userTable.findUser();
            if (user) {
                billManager.increaseBills(user);
                cout << "Bills increased for " << user->name << ".\n";
            }
            break;
        }
        case 5: {
            User* user = userTable.findUser();
            billManager.checkBills(user);
            break;
        }
        case 6: {
            User* user = userTable.findUser();
            billManager.payBills(user);
            break;
        }
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 7);

    return 0;
}
