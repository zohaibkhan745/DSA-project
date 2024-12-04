#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;
class Node{
    string name;
    int id;
    Node(string name, int id){
        name = this->name;
        id = this->id;
    }
};
// struct UtilityData {
//     string area;
//     int electricityUsage;
//     int waterUsage;
// };

// struct Report {
//     string area;
//     string issue;
// };

// vector<string> tips = {
//     "Turn off lights when not in use.",
//     "Fix water leaks to save water.",
//     "Use energy-efficient appliances.",
//     "Limit unnecessary water usage."
// };

// vector<UtilityData> generateUtilityData() {
//     vector<UtilityData> data;
//     vector<string> areas = {"Area A", "Area B", "Area C"};
//     srand(time(0));

//     for (const string& area : areas) {
//         data.push_back({area, rand() % 500 + 50, rand() % 1000 + 200});
//     }

//     return data;
// }

// void monitorUtilities(const vector<UtilityData>& data) {
//     for (const auto& utility : data) {
//         cout << "Area: " << utility.area 
//              << " | Electricity: " << utility.electricityUsage 
//              << " kWh | Water: " << utility.waterUsage << " liters\n";

//         if (utility.electricityUsage < 100) {
//             cout << "  ALERT: Electricity outage in " << utility.area << "!\n";
//         }
//         if (utility.waterUsage > 800) {
//             cout << "  NOTICE: High water usage in " << utility.area << ".\n";
//         }
//     }
// }

// void reportIssue(vector<Report>& reports) {
//     string area, issue;
//     cout << "Enter the area: ";
//     cin >> ws;
//     getline(cin, area);
//     cout << "Enter the issue: ";
//     getline(cin, issue);

//     reports.push_back({area, issue});
//     cout << "Report submitted successfully for " << area << ".\n";
// }

// void displayTips() {
//     srand(time(0));
//     int randomIndex = rand() % tips.size();
//     cout << "Resource-Saving Tip: " << tips[randomIndex] << "\n";
// }

int main() {
    // vector<UtilityData> utilityData;
    // vector<Report> reports;
    // int choice;

    // while (true) {
    //     cout << "\n=== Smart City Simulation ===\n";
    //     cout << "1. Generate Utility Data\n";
    //     cout << "2. Monitor Utilities\n";
    //     cout << "3. Report an Issue\n";
    //     cout << "4. Display Resource-Saving Tip\n";
    //     cout << "5. Exit\n";
    //     cout << "Enter your choice: ";
    //     cin >> choice;

    //     switch (choice) {
    //         case 1:
    //             utilityData = generateUtilityData();
    //             cout << "Utility data generated.\n";
    //             break;
    //         case 2:
    //             if (utilityData.empty()) {
    //                 cout << "No utility data available. Generate data first.\n";
    //             } else {
    //                 monitorUtilities(utilityData);
    //             }
    //             break;
    //         case 3:
    //             reportIssue(reports);
    //             break;
    //         case 4:
    //             displayTips();
    //             break;
    //         case 5:
    //             cout << "Exiting...\n";
    //             return 0;
    //         default:
    //             cout << "Invalid choice. Please try again.\n";
    //     }
    // }
}
