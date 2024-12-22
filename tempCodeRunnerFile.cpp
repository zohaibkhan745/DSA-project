    void manageUtilities(const string &username)
    {
        creatFileforBill(username);
        while (true)
        {
            int select;
            cout << "1. Manage Utilities\n";
            cout << "2. Emergency Services\n";
            cout << "3. Exit\n";
            cout << "Enter your choice: ";
            cin >> select;
            switch (select)
            {
            case 1:
            
                int choice;
                while (true)
                {
                    cout << "\n--- Utility Management System ---\n";
                    cout << "1. Pay Electricity Bill\n";
                    cout << "2. Pay Water Bill\n";
                    cout << "3. View Bills\n";
                    cout << "4. To Do List\n";
                    cout << "5. Exit\n";
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
                        TODO(username);
                        break;
                    case 5:
                        cout << "Exiting Utility Management System...\n";
                        return;
                    default:
                        cout << "Invalid choice. Try again.\n";
                    }
                }
                break;
            
            case 2:
            EmergencyServices();
            break;
        
        }
         }

        
    }
};
