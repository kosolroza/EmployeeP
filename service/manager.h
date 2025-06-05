#include "employee.h"

using namespace std;

// ==================== Manager Functions ====================

//To make sure string ID with biggercase and smaller are the same
string toLower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

//================== Add Employee to list that we create =============

// Use add To End as addEmployee
void addEmployee(EList *l) {      
    EInfo emp;   //call EInfo cause It store E'Info
    cout << "Enter ID: ";   // Check for duplicate ID so it can't be add to the list
    cin >> emp.id;

    EData *E = l->head;    //make sure that data start from head 
    while (E != nullptr) {
        if (toLower(E->emp.id) == toLower(emp.id)) {    //checking if id input with small letter or big letter
            cout << "Error: Employee with ID " << emp.id << " already exists. Cannot add duplicate." << endl;
            return;
        }
        E = E->next;
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

    EData *e = new EData;  //Let all emp info = null all
    e->emp = emp;
    e->next = nullptr;
    e->pre = nullptr;
    if (l->head == nullptr){
        l->head = e;
        l->tail = e;
    }
    else {
        l->tail->next = e;
        e->pre = l->tail;
        l->tail = e;
    }
    l->n++;
    sortEmpByName(l);
    writeEToFile(l);
    cout<<"Employee has been add to system successfully!"<<endl;
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

    EData *e = l->head;   // also make sure that it start from head
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
                case 4: cout << "New Department: "; 
                    cin >> e->emp.department; 
                    break;
                case 5: cout << "New Position: ";
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
            writeEToFile(l);    //afer update, writeToFile csv
            cout<<"Employee has been updated to system successfully!"<<endl;
            return;
        }
        e = e->next;
    }
    cout << "Employee not found." << endl;
}


//for manager to delete any employee
//this funtion is remove at position 
void removeEmp(EList *l) {
    if (!l->head) {
        cout << "No employees to remove." << endl;
        return;
    }

    string id;
    cout << "Enter ID to remove: "; 
    cin >> id;

    EData *e = l->head;
    EData *pre = nullptr;

    while(e != nullptr){
        if(e->emp.id == id){
            //for delete from head
            if(e->pre = nullptr){
                l->head = e->next;
            }
            else{
                pre->next = e->next;
            }
            //for delete from tail
            if(e==l->tail){
                l->tail = pre;
            }
            delete e;
            l->n--;
            writeEToFile(l);
            cout<<"Employee removed!"<<endl;
            return;
        }
        pre = e;
        e = e->next;
    }
    cout<<"Employee not found!"<<endl;
}

//looking for a employee much more easier for manager
void searchByID(EList *l) {
    string id;
    cout << "Enter ID to search: "; 
    cin >> id;
    EData *e = l->head;
    bool found = 0;
    while (e) {
        if (e->emp.id == id) {
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
            <<  "  |"<<endl;
            cout<<"--------------------------------------------------------------------------------------------------------------------\n";
            cout << "| "<< setw(10) <<left<< e ->emp.id
            <<  setw(15) <<left<< e ->emp.firstName
            <<  setw(15)<<left<< e ->emp.lastName
            <<  setw(8)<<left<< e ->emp.gender
            <<  setw(15)<<left<< e ->emp.phoneNumber
            <<  setw(15)<<left<< e ->emp.department
            <<  setw(15)<<left<< e->emp.position<<"$"
            <<  setw(10)<<left<< e->emp.salary<<"$"
            <<  setw(8)<<left<< e->emp.bonus
            <<  "|"<<endl;
            cout<<"--------------------------------------------------------------------------------------------------------------------\n";
            found = 1;
            break;
        }
        e = e->next;
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

    EData *e = l->head;
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
    cout<<"--------------------------------------------------------------------------------------------------------------------\n";
    while (e != nullptr) {
        cout << "| "<< setw(10) <<left<< e ->emp.id
             <<  setw(15) <<left<< e ->emp.firstName
             <<  setw(15)<<left<< e ->emp.lastName
             <<  setw(8)<<left<< e ->emp.gender
             <<  setw(15)<<left<< e ->emp.phoneNumber
             <<  setw(15)<<left<< e ->emp.department
             <<  setw(15)<<left<< e->emp.position<<"$"
             <<  setw(10)<<left<<e->emp.salary<<"$"
             <<  setw(8)<<left<<e->emp.bonus
             <<  "|"<<endl;
        e = e ->next;
    }
    cout<<"--------------------------------------------------------------------------------------------------------------------\n";
}
