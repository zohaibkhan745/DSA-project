#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;

struct User
{
    string email;
    string password;
    string name;
    User *next;
};

class Registration
{
public:
    string hashPassword(const string &password)
    {
        string hashed = "";
        for (char c : password)
        {
            hashed += to_string((int)c + 3); // Shift ASCII values for basic encryption
        }
        return hashed;
    }

    User *createUser(const string &email, const string &password, const string &name)
    {
        User *newUser = new User();
        newUser->email = email;
        newUser->password = hashPassword(password); // Store hashed password
        newUser->name = name;
        newUser->next = nullptr;
        return newUser;
    }

    void registerUser(User *&head)
    {
        string name, email, password;

        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your email: ";
        getline(cin, email);
        cout << "Enter your password: ";
        getline(cin, password);

        // Check if the email is already registered
        User *temp = head;
        while (temp != nullptr)
        {
            if (temp->email == email)
            {
                cout << "Email is already registered. Try logging in.\n";
                loginUser(head);
                return;
            }
            temp = temp->next;
        }

        // Create a new user and add to the list
        User *newUser = createUser(email, password, name);
        newUser->next = head;
        head = newUser;

        // Save data to file immediately
        saveToFile(head);

        cout << "Registration successful!\n";
    }

    void loginUser(User *head)
    {
        string email, password;

        cout << "Enter your email: ";
        cin.ignore();
        getline(cin, email);
        cout << "Enter your password: ";
        getline(cin, password);

        // Hash the entered password for comparison
        string hashedPassword = hashPassword(password);

        // Search for the user in the linked list
        User *temp = head;
        while (temp != nullptr)
        {
            if (temp->email == email && temp->password == hashedPassword)
            {
                cout << "Login successful! Welcome, " << temp->name << "!\n";
                return;
            }
            temp = temp->next;
        }

        cout << "Invalid email or password.\n";
    }

    void saveToFile(User *head)
    {
        ofstream file("users.txt");
        if (!file)
        {
            cout << "Error saving data to file.\n";
            return;
        }

        User *temp = head;
        while (temp != nullptr)
        {
            file << temp->name << "," << temp->email << "," << temp->password << "\n";
            temp = temp->next;
        }
        file.close();
        cout << "Data saved successfully!\n";
    }

    void loadFromFile(User *&head)
    {
        ifstream file("users.txt");
        if (!file)
        {
            if (file.fail())
            {
                cout << "Error opening file. Please check file permissions.\n";
            }
            else
            {
                cout << "No previous data found.\n";
            }
            return;
        }

        string line, name, email, password;
        while (getline(file, line))
        {
            size_t pos1 = line.find(',');
            size_t pos2 = line.find(',', pos1 + 1);
            name = line.substr(0, pos1);
            email = line.substr(pos1 + 1, pos2 - pos1 - 1);
            password = line.substr(pos2 + 1);

            User *newUser = new User();
            newUser->name = name;
            newUser->email = email;
            newUser->password = password;
            newUser->next = head;
            head = newUser;
        }
        file.close();
        cout << "Data loaded successfully!\n";
    }

    void displayUsers(User *head)
    {
        cout << "\n--- Registered Users ---\n";
        while (head != nullptr)
        {
            cout << "Name: " << head->name << ", Email: " << head->email << "\n";
            head = head->next;
        }
        cout << "-------------------------\n";
    }
};

int main()
{
    string adminPassword;
    string adminUsername;
    Registration r;
    User *head = nullptr;
    r.loadFromFile(head);

    int choice;
    bool opt = true;
    while (true)
    {

        cout << "\n--- User Registration and Login System ---\n";
        cout << "1. Admin \n";
        cout << "2. Users \n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        while (!(cin >> choice))
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a valid number: ";
        }
        switch (choice)
        {
        case 1:

            do
            {
                cout << "Enter the password :";
                cin >> adminPassword;
                cout << "Enter the username :";
                cin >> adminUsername;
                if (adminPassword == "z123" && adminUsername == "z123")
                {
                    opt = false;
                }
                
            } while (opt);

            
            break;
        case 2:
            while (true)
            {

                cout << "\n--- User Registration and Login System ---\n";
                cout << "1. Register\n";
                cout << "2. Login\n";
                cout << "3. Exit\n";
                cout << "Enter your choice: ";
                while (!(cin >> choice))
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input. Please enter a valid number: ";
                }
                switch (choice)
                {
                case 1:
                    r.registerUser(head);
                    break;
                case 2:
                    r.loginUser(head);
                    break;
                case 3:
                    r.saveToFile(head); // Save data before exiting
                    cout << "Exiting...\n";
                    return 0;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
                break;
            }
        }
    }
}
