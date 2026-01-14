// PROGRAM: HOSTEL MANAGEMENT SYSTEM (UTeM DORM)
// GROUP MEMBERS: Chew Yi Xiong, Izaz, Zariff, Qusyairi
// SUBJECT: PROGRAMMING TECHNIQUES (C++)
// DATE: January 4, 2026 

#include <iostream>
#include <string>
#include <limits> 

using namespace std;


struct Student {
    string name = ""; 
    string ic;
    string matricCard;
    string phoneNum;
};


const int TOTAL_HOUSES = 108; 
const int BEDS_PER_HOUSE = 10;

Student hostel[TOTAL_HOUSES][BEDS_PER_HOUSE];


void showMainMenu();
void registerStudent();
void checkAvailability();
void findStudent();


int main() {
    int choice = 0;
    while (choice != 5) {

        showMainMenu();
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            checkAvailability();
        }
        else if (choice == 2) {
            registerStudent();
        }
        else if (choice == 3) {
            cout << "Feature not active in this version.\n";
        }
        else if (choice == 4) {
            findStudent();
        }
        else if (choice == 5) {
            cout << "Exiting system. \n";
        }
        else {
            cout << "Invalid input. Please enter 1-5.\n";
        }
    }
    return 0;
}



void showMainMenu() {
    cout << "\n======================================\n";
    cout << "      HOSTEL MANAGEMENT SYSTEM        \n";
    cout << "======================================\n";
    cout << "1. Check Room Availability\n";
    cout << "2. Register New Student\n";
    cout << "3. View All (Optional)\n";
    cout << "4. Find Student Details (By Name)\n";
    cout << "5. Exit\n";
    cout << "======================================\n";
}

void registerStudent() {
    int method;
    int rowIndex = -1;   
    int targetCol = -1; 

    cout << "\n--- REGISTER NEW STUDENT ---\n";
    cout << "1. Manual Selection (Choose Room)\n";
    cout << "2. Automatic Assignment (Random/First Available)\n";
    cout << "Select Method (1 or 2): ";
    cin >> method;


    if (method == 1) {
        int f, h, r;
        cout << "Enter Floor (1-9): "; cin >> f;
        cout << "Enter House (1-12): "; cin >> h;
        cout << "Enter Room (1-5): "; cin >> r;

        /
        if (f < 1 || f > 9 || h < 1 || h > 12 || r < 1 || r > 5) {
            cout << ">> Error: Invalid inputs.\n";
            return;
        }

      
        int calcRow = ((f - 1) * 12) + (h - 1);
        int startCol = (r - 1) * 2;

      
        if (hostel[calcRow][startCol].name == "") {
            rowIndex = calcRow;
            targetCol = startCol;
        }
        else if (hostel[calcRow][startCol + 1].name == "") {
            rowIndex = calcRow;
            targetCol = startCol + 1;
        }
        else {
            cout << ">> Error: That specific room is full.\n";
            return;
        }
    }
  
    else if (method == 2) {
        bool found = false;
        cout << ">> Searching for the nearest empty bed...\n";

    
        for (int i = 0; i < TOTAL_HOUSES; i++) {
            for (int j = 0; j < BEDS_PER_HOUSE; j++) {
                if (hostel[i][j].name == "") {
                    rowIndex = i;
                    targetCol = j;
                    found = true;
                    break; 
                }
            }
            if (found) break; 
        }

        if (!found) {
            cout << ">> SYSTEM FULL: No empty beds available anywhere!\n";
            return;
        }
    }
    else {
        cout << "Invalid selection.\n";
        return;
    }

   
    int floor = (rowIndex / 12) + 1;
    int house = (rowIndex % 12) + 1;
    int room = (targetCol / 2) + 1;
    int bed = (targetCol % 2) + 1;

    cout << ">> Bed Found at: Floor " << floor << ", House " << house
        << ", Room " << room << ", Bed " << bed << endl;

    auto& student = hostel[rowIndex][targetCol];

    cout << ">> Proceeding to register...\n";
    cout << "1. Name: ";
    getline(cin >> ws, student.name);

    cout << "2. IC Number: ";
    getline(cin, student.ic);

    cout << "3. Matric Card: ";
    getline(cin, student.matricCard);

    cout << "4. Phone Number: ";
    getline(cin, student.phoneNum);

    cout << ">> Registration Successful!\n";
}

void checkAvailability() {
    int f, h;
    cout << "\n--- CHECK AVAILABILITY ---\n";
    cout << "Enter Floor (1-9): "; cin >> f;
    cout << "Enter House (1-12): "; cin >> h;

    if (f < 1 || f > 9 || h < 1 || h > 12) {
        cout << ">> Error: Invalid inputs.\n";
        return;
    }

    int rowIndex = ((f - 1) * 12) + (h - 1);
    int count = 0;

    cout << "\nStatus for Floor " << f << " House " << h << ":\n";

    for (int j = 0; j < BEDS_PER_HOUSE; j++) {
        int roomNum = (j / 2) + 1;
        int bedNum = (j % 2) + 1;

        if (hostel[rowIndex][j].name == "") {
            cout << "[Room " << roomNum << " Bed " << bedNum << "] Empty\n";
            count++;
        }
        else {
            cout << "[Room " << roomNum << " Bed " << bedNum << "] Occupied by "
                << hostel[rowIndex][j].name << "\n";
        }
    }
    cout << ">> Total Empty Beds: " << count << endl;
}

void findStudent() {
    string keyword;
    bool found = false;

    cout << "\n--- SEARCH STUDENT ---\n";
    cout << "Enter Name: ";

    cin.ignore();
    getline(cin, keyword);

    cout << "\n>> RESULTS:\n";

    for (int i = 0; i < TOTAL_HOUSES; i++) {
        for (int j = 0; j < BEDS_PER_HOUSE; j++) {

            auto& s = hostel[i][j];

            if (s.name == "" || s.name.find(keyword) == string::npos) {
                continue;
            }

            int floor = (i / 12) + 1;
            int house = (i % 12) + 1;
            int room = (j / 2) + 1;
            int bed = (j % 2) + 1;

            cout << "--------------------------------\n";
            cout << "Name   : " << s.name << "\n";
            cout << "Matric : " << s.matricCard << "\n";
            cout << "Phone  : " << s.phoneNum << "\n";
            cout << "Loc    : Floor " << floor << ", House " << house
                << ", Room " << room << ", Bed " << bed << "\n";

            found = true;
        }
    }

    if (!found) cout << ">> No student found.\n";

}
