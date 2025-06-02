#include "employee.h"

using namespace std;

// ==================== Manager Functions ====================

//To make sure string ID with biggercase and smaller are the same
string toLower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

//================== Add Employee to list that we create =============

void addEmployee(EList *l) {
    EInfo emp;

    cout << "Enter ID: ";
    cin >> emp.id;

    // Check for duplicate ID so it can't be add to the list
    EData *current = l->head;
    while (current != nullptr) {
        if (toLower(current->emp.id) == toLower(emp.id)) {
            cout << "Error: Employee with ID " << emp.id << " already exists. Cannot add duplicate." << endl;
            return;
        }
        current = current->next;
    }

    cout << "First Name: ";
    cin >> emp.firstName;
    cout << "Last Name: ";
    cin >> emp.lastName;
    cout << "Gender (M/F): ";
    cin >> emp.gender;
    cout << "Phone: ";
    cin >> emp.phoneNumber;
    cin.ignore();
    cout << "Department: ";
    getline(cin, emp.department);
    cout << "Position: ";
    getline(cin, emp.position);
    cout << "Salary: ";
    cin >> emp.salary;
    cout << "Bonus: ";
    cin >> emp.bonus;
    cout << "Password: ";
    cin >> emp.password;

    EData *e = new EData{emp, nullptr};

    if (l->head == nullptr)
        l->head = l->tail = e;
    else {
        l->tail->next = e;
        l->tail = e;
    }

    l->n++;
    sortEmpByName(l);
    writeEToFile(l);
}

//for manager update some wrong info about employee
void updateEmp(EList *l) {
    if (!l->head) {
        cout << "No employees to update." << endl;
        return;
    }
    string id;
    cout << "Enter ID to update: "; 
    cin >> id;

    EData *e = l->head;
    while (e) {
        if (e->emp.id == id) {
            int ch;
            cout << "Which one do you want to update? \n1-First Name \n2-Last Name \n3-Phone Number \n4-Department \n5-Position \n6-Salary \n7-Bonus\nEnter a choice: "; 
            cin >> ch;
            switch (ch) {
                case 1: cout << "New First Name: "; 
                    cin >> e->emp.firstName; 
                    break;
                case 2: cout << "New Last Name: "; 
                    cin >> e->emp.lastName; 
                    break;
                case 3: cout << "New Phone: "; 
                    cin >> e->emp.phoneNumber; 
                    break;
                case 4: cout << "New Dept: "; 
                    cin >> e->emp.department; 
                    break;
                case 5: cout << "New Pos: ";
                    cin >> e->emp.position; 
                    break;
                case 6: cout << "New Salary: "; 
                    cin >> e->emp.salary; 
                    break;
                case 7: cout << "New Bonus: "; 
                    cin >> e->emp.bonus; 
                    break;
                default: 
                    cout << "Invalid choice." << endl;
            }
            writeEToFile(l);
            return;
        }
        e = e->next;
    }
    cout << "Employee not found." << endl;
}


//for manager to delete any employee
void removeEmp(EList *l) {
    if (!l->head) {
        cout << "No employees to remove." << endl;
        return;
    }

    string id;
    cout << "Enter ID to remove: "; 
    cin >> id;

    EData *curr = l->head, *prev = nullptr;
    while (curr) {
        if (curr->emp.id == id) {
            if (!prev) l->head = curr->next;
            else prev->next = curr->next;
            if (curr == l->tail) l->tail = prev;
            delete curr;
            l->n--;
            writeEToFile(l);
            cout << "Employee removed." << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Employee not found." << endl;
}

//looking for a employee much more easier for manager
void searchByID(EList *l) {
    string id;
    cout << "Enter ID to search: "; 
    cin >> id;
    EData *d = l->head;
    bool found = 0;
    while (d) {
        if (d->emp.id == id) {
            cout<<"--------------------------------------------------------------------------------------------------------------------\n";
            cout << "| "<< setw(10)<<left << "ID"
            <<  setw(15) <<left<< "First Name"
            <<  setw(15) <<left<< "Last Name"
            <<  setw(8)  <<left<< "Gender"
            <<  setw(15) <<left<< "Phone Number"
            <<  setw(15) <<left<< "Department"
            <<  setw(15) <<left<<  "Position"
            <<  setw(10) <<left<<  "Salary"
            <<  setw(8) <<left<<  "Bonus"
            <<  "|"<<endl;
            cout << "| "<< setw(10) <<left<< d ->emp.id
            <<  setw(15) <<left<< d ->emp.firstName
            <<  setw(15)<<left<< d ->emp.lastName
            <<  setw(8)<<left<< d ->emp.gender
            <<  setw(15)<<left<< d ->emp.phoneNumber
            <<  setw(15)<<left<< d ->emp.department
            <<  setw(15)<<left<< d->emp.position<<"$"
            <<  setw(10)<<left<< d->emp.salary<<"$"
            <<  setw(8)<<left<< d->emp.bonus
            <<  "  |"<<endl;
            cout<<"--------------------------------------------------------------------------------------------------------------------\n";
            found = 1;
            break;
        }
        d = d->next;
    }
    if(!found){
        cout<<"Not found!";
    }
}

void displayEmployees(EList *l) {
    if (l->head == nullptr) {
        cout << "No employees found." << endl;
        return;
    }

    EData *d = l->head;
    cout<<"--------------------------------------------------------------------------------------------------------------------\n";
    cout << "| "<< setw(10)<<left << "ID"
         <<  setw(15) <<left<< "First Name"
         <<  setw(15) <<left<< "Last Name"
         <<  setw(8)  <<left<< "Gender"
         <<  setw(15) <<left<< "Phone Number"
         <<  setw(15) <<left<< "Department"
         <<  setw(15) <<left<<  "Position"
         <<  setw(10) <<left<<  "Salary"
         <<  setw(8)  <<left<<  " Bonus"
         <<  "  |"<<endl;
    while (d != nullptr) {
        cout << "| "<< setw(10) <<left<< d ->emp.id
             <<  setw(15) <<left<< d ->emp.firstName
             <<  setw(15)<<left<< d ->emp.lastName
             <<  setw(8)<<left<< d ->emp.gender
             <<  setw(15)<<left<< d ->emp.phoneNumber
             <<  setw(15)<<left<< d ->emp.department
             <<  setw(15)<<left<< d->emp.position<<"$"
             <<  setw(10)<<left<<d->emp.salary<<"$"
             <<  setw(8)<<left<<d->emp.bonus
             <<  "|"<<endl;
        d = d ->next;
    }
    cout<<"--------------------------------------------------------------------------------------------------------------------\n";
}
