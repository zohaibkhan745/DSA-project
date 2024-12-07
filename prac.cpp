#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

// Function to hash the password for basic security
string hashPassword(const string &password) {
    string hashed = "";
    for (char c : password) {
        hashed += to_string((int)c + 3); // Shift ASCII values for basic encryption
    }
    return hashed;
}

// Function to register a new user
void registerUser() {
    string name, email, password;

    cout << "Enter your name: ";
    cin >> name;
    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your password: ";
    cin >> password;

    // Hash the password before storing
    string hashedPassword = hashPassword(password);

    // Open file in append mode to save user details
    ofstream userFile("users.txt", ios::app);
    if (userFile.is_open()) {
        userFile << email << "," << hashedPassword << "," << name << endl;
        cout << "Registration successful!\n";
    } else {
        cerr << "Unable to open file.\n";
    }
    userFile.close();
}

// Function to login an existing user
void loginUser() {
    string email, password;

    cout << "Enter your email: ";
    cin >> email;
    cout << "Enter your password: ";
    cin >> password;

    // Hash the entered password for comparison
    string hashedPassword = hashPassword(password);

    // Open file in read mode to check user details
    ifstream userFile("users.txt");
    string line;
    bool isAuthenticated = false;
    if (userFile.is_open()) {
        while (getline(userFile, line)) {
            // Parse the line to get stored email and password
            size_t comma1 = line.find(',');
            size_t comma2 = line.rfind(',');
            string storedEmail = line.substr(0, comma1);
            string storedPassword = line.substr(comma1 + 1, comma2 - comma1 - 1);

            if (storedEmail == email && storedPassword == hashedPassword) {
                isAuthenticated = true;
                cout << "Login successful! Welcome, " << line.substr(comma2 + 1) << "!\n";
                break;
            }
        }
        userFile.close();

        if (!isAuthenticated) {
            cout << "Invalid email or password.\n";
        }
    } else {
        cerr << "Unable to open file.\n";
    }
}

int main() {
    int choice;

    while (true) {
        cout << "\n--- User Registration and Login System ---\n";
        cout << "1. Register\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                registerUser();
                break;
            case 2:
                loginUser();
                break;
            case 3:
                cout << "Exiting...\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }
}
