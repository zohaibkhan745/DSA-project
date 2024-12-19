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

    void deleteUser(User *&head, const string &email)
    {
        if (head == nullptr)
        {
            cout << "No users to delete.\n";
            return;
        }

        User *temp = head, *prev = nullptr;

        // If the user to delete is the head
        if (temp != nullptr && temp->email == email)
        {
            head = temp->next;
            delete temp;
            cout << "User deleted successfully.\n";
            return;
        }

        // Search for the user to delete
        while (temp != nullptr && temp->email != email)
        {
            prev = temp;
            temp = temp->next;
        }

        // If user not found
        if (temp == nullptr)
        {
            cout << "User not found.\n";
            return;
        }

        // Unlink the user and delete
        prev->next = temp->next;
        delete temp;
        cout << "User deleted successfully.\n";
    }
};

class UtilityManagement
{
public:
    void manageUtilities()
    {
        int choice;
        double electricityBill = 0, waterBill = 0;

        while (true)
        {
            cout << "\n--- Utility Management System ---\n";
            cout << "1. Pay Electricity Bill\n";
            cout << "2. Pay Water Bill\n";
            cout << "3. View Bills\n";
            cout << "4. Exit\n";
            cout << "Enter your choice: ";

            cin >> choice;

            switch (choice)
            {
            case 1:
                cout << "Enter amount for Electricity Bill: ";
                cin >> electricityBill;
                cout << "Electricity Bill Paid: " << electricityBill << "\n";
                break;
            case 2:
                cout << "Enter amount for Water Bill: ";
                cin >> waterBill;
                cout << "Water Bill Paid: " << waterBill << "\n";
                break;
            case 3:
                cout << "Electricity Bill: " << electricityBill << "\n";
                cout << "Water Bill: " << waterBill << "\n";
                break;
            case 4:
                cout << "Exiting Utility Management System...\n";
                return;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        }
    }
};

int main()
{
    string adminPassword;
    string adminUsername;
    Registration r;
    UtilityManagement um;
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
                    while (true)
                    {
                        cout << "\n--- Admin Panel ---\n";
                        cout << "1. Display Users\n";
                        cout << "2. Delete User\n";
                        cout << "3. Exit Admin Panel\n";
                        cout << "Enter your choice: ";
                        cin >> choice;

                        switch (choice)
                        {
                        case 1:
                            r.displayUsers(head);
                            break;
                        case 2:
                        {
                            string email;
                            cout << "Enter email of user to delete: ";
                            cin >> email;
                            r.deleteUser(head, email);
                            break;
                        }
                        case 3:
                            cout << "Exiting Admin Panel...\n";
                            opt = true;
                            goto exit_admin;
                        default:
                            cout << "Invalid choice. Try again.\n";
                        }
                    }
                }
exit_admin:;
            } while (opt);

            break;
        case 2:
            while (true)
            {

                cout << "\n--- User Registration and Login System ---\n";
                cout << "1. Register\n";
                cout << "2. Login\n";
                cout << "3. Utility Management\n";
                cout << "4. Exit\n";
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
                    um.manageUtilities();
                    break;
                case 4:
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
