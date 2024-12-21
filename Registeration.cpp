#include <iostream>
#include <fstream>
#include <string>
#include <limits>
using namespace std;
class UtilityManagement
{
public:
    double electricityBill = 0.0;
    double waterBill = 0.0;

    void payBill(const string &username, double &billAmount, const string &billType)
    {
        double amount;
        cout << "Enter amount for " << billType << ": ";
        cin >> amount;

        if (amount < 0)
        {
            cout << "Invalid amount. Payment cannot be negative.\n";
            return;
        }

        billAmount += amount;
        cout << billType << " Paid: " << amount << "\n";
        saveBillsToFile(username);
    }

    void viewBills()
    {
        cout << "\n--- Current Bill Status ---\n";
        cout << "Electricity Bill: $" << electricityBill << "\n";
        cout << "Water Bill: $" << waterBill << "\n";
    }

    void saveBillsToFile(const string &username)
    {
        ofstream file(username + "bills.txt");
        if (!file)
        {
            cout << "Error saving bills to file.\n";
            return;
        }
        file << electricityBill << "," << waterBill << "\n";
        file.close();
        cout << "Bills saved successfully!\n";
    }

    void loadBillsFromFile(const string &username)
    {
        ifstream file(username + "bills.txt");
        if (!file)
        {
            cout << "No previous bill data found.\n";
            return;
        }

        string line;
        if (getline(file, line))
        {
            size_t pos = line.find(',');
            electricityBill = stod(line.substr(0, pos));
            waterBill = stod(line.substr(pos + 1));
        }
        file.close();
    }
    void creatFileforBill(const string &username)
    {
        ofstream file(username + "bill.txt");
    }

public:

    void manageUtilities(const string &username)
    {
        creatFileforBill(username);
        int choice;

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
                payBill(username, electricityBill, "Electricity Bill");
                break;
            case 2:
                payBill(username, waterBill, "Water Bill");
                break;
            case 3:
                viewBills();
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

struct User
{
    string name;
    string email;
    string password;
    User *left;
    User *right;
    int height;
};
class Registration
{

public:
    User *root;

    int height(User *node)
    {
        return node ? node->height : 0;
    }

    int balanceFactor(User *node)
    {
        return node ? height(node->left) - height(node->right) : 0;
    }

    User *rotateRight(User *y)
    {
        User *x = y->left;
        User *T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height = max(height(y->left), height(y->right)) + 1;
        x->height = max(height(x->left), height(x->right)) + 1;

        return x;
    }

    User *rotateLeft(User *x)
    {
        User *y = x->right;
        User *T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height = max(height(x->left), height(x->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        return y;
    }

    User *balance(User *node)
    {
        int balance = balanceFactor(node);

        if (balance > 1 && balanceFactor(node->left) >= 0)
            return rotateRight(node);

        if (balance > 1 && balanceFactor(node->left) < 0)
        {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balance < -1 && balanceFactor(node->right) <= 0)
            return rotateLeft(node);

        if (balance < -1 && balanceFactor(node->right) > 0)
        {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    User *insert(User *node, const string &name, const string &email, const string &password)
    {
        if (!node)
        {
            User *newUser = new User{name, email, password, nullptr, nullptr, 1};
            return newUser;
        }

        if (email < node->email)
            node->left = insert(node->left, name, email, password);
        else if (email > node->email)
            node->right = insert(node->right, name, email, password);
        else
        {
            cout << "Email already registered. Try logging in.\n";
            loginUser(root);
            return node;
        }

        node->height = max(height(node->left), height(node->right)) + 1;
        return balance(node);
    }

    User *findMin(User *node)
    {
        while (node->left)
            node = node->left;
        return node;
    }

    User *remove(User *node, const string &email)
    {
        if (!node)
            return node;

        if (email < node->email)
            node->left = remove(node->left, email);
        else if (email > node->email)
            node->right = remove(node->right, email);
        else
        {
            if (!node->left || !node->right)
            {
                User *temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            }
            else
            {
                User *temp = findMin(node->right);
                node->email = temp->email;
                node->name = temp->name;
                node->password = temp->password;
                node->right = remove(node->right, temp->email);
            }
        }

        node->height = max(height(node->left), height(node->right)) + 1;
        return balance(node);
    }

    void inOrder(User *node)
    {
        if (node)
        {
            inOrder(node->left);
            cout << "Name: " << node->name << ", Email: " << node->email << "\n";
            inOrder(node->right);
        }
    }

    void saveToFile(User *node, ofstream &file)
    {
        if (node)
        {
            saveToFile(node->left, file);
            file << node->name << "," << node->email << "," << node->password << "\n";
            saveToFile(node->right, file);
        }
    }

    User *loadFromFile(User *node, const string &name, const string &email, const string &password)
    {
        return insert(node, name, email, password);
    }

    string hashPassword(const string &password)
    {
        string hashed;
        for (char c : password)
            hashed += to_string((int)c + 3);
        return hashed;
    }

public:
    Registration() : root(nullptr) {}

    void registerUser()
    {
        string name, email, password;

        cout << "Enter your name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter your email: ";
        getline(cin, email);
        cout << "Enter your password: ";
        getline(cin, password);

        root = insert(root, name, email, hashPassword(password));
        saveToFile();
        cout << "Registration successful!\n";
    }

    void loginUser(User *node)
    {
        string email, password;
        cout << "Enter your email: ";
        cin.ignore();
        getline(cin, email);
        cout << "Enter your password: ";
        getline(cin, password);

        string hashedPassword = hashPassword(password);
        User *temp = root;

        while (temp)
        {
            if (email == temp->email && hashedPassword == temp->password)
            {
                cout << "Login successful! Welcome, " << temp->name << "!\n";
                UtilityManagement u;
                u.loadBillsFromFile(temp->name);
                u.manageUtilities(temp->name);
                return;
            }
            else if (email < temp->email)
            {
                temp = temp->left;
            }
            else
            {
                temp = temp->right;
            }
        }

        cout << "Invalid email or password.\n";
    }

    void saveToFile()
    {
        ofstream file("users_avl.txt");
        if (!file)
        {
            cout << "Error saving data to file.\n";
            return;
        }

        saveToFile(root, file);
        file.close();
        cout << "Data saved successfully!\n";
    }

    void loadFromFile()
    {
        ifstream file("users_avl.txt");
        if (!file)
        {
            cout << "No previous data found.\n";
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

            root = loadFromFile(root, name, email, password);
        }
        file.close();
    }

    void displayUsers()
    {
        cout << "\n--- Registered Users ---\n";
        inOrder(root);
        cout << "-------------------------\n";
    }

    void deleteUser(const string &email)
    {
        root = remove(root, email);
    }
};

int main()
{
    string adminPassword;
    string adminUsername;
    Registration r;
    UtilityManagement um;
    User *head = nullptr;
    r.loadFromFile();

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
                cout << "Enter the username :";
                cin >> adminUsername;
                cout << "Enter the password :";
                cin >> adminPassword;
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
                            r.displayUsers();
                            break;
                        case 2:
                        {
                            string email;
                            cout << "Enter email of user to delete: ";
                            cin >> email;
                            r.deleteUser(email);
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
                    r.registerUser();
                    break;
                case 2:
                    r.loginUser(head);
                    break;
                case 3:
                    r.saveToFile(); // Save data before exiting
                    cout << "Exiting...\n";
                    return 0;
                default:
                    cout << "Invalid choice. Try again.\n";
                }
            }
        }
    exit_admin:;
    }
}
