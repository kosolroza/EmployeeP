#include <iomanip>
#include "fileio.h"

using namespace std;

void displayAllEmployees(EList *l) {   //display all employee in company
    if (l->head == nullptr) {
        cout << "No employees found." << endl;
        return;
    }
    EData *d = l->head;
    cout<<"-----------------------------------------------------------------------------------------------\n";
    cout << "| "<< setw(10)<<left << "ID"
         <<  setw(15) <<left<< "First Name"
         <<  setw(15) <<left<< "Last Name"
         <<  setw(8)  <<left<< "Gender"
         <<  setw(15) <<left<< "Phone Number"
         <<  setw(15) <<left<< "Department"
         <<  setw(15) <<left<<  "Position"
         <<  "|"<<endl;
    cout<<"-----------------------------------------------------------------------------------------------\n";
    while (d != nullptr) {
        cout << "| "<< setw(10) <<left<< d ->emp.id
             <<  setw(15) <<left<< d ->emp.firstName
             <<  setw(15)<<left<< d ->emp.lastName
             <<  setw(8)<<left<< d ->emp.gender
             <<  setw(15)<<left<< d ->emp.phoneNumber
             <<  setw(15)<<left<< d ->emp.department
             <<  setw(15)<<left<< d->emp.position
             <<  "|"<<endl;
        d = d ->next;
    }
    cout<<"-----------------------------------------------------------------------------------------------\n";
}

//employee has right to edit their info as well but not fully as manager
void updateMyInfo(EList *l) {
    if (!l->head) {
        cout << "No employees to update." << endl;
        return;
    }
    string id, pass;
    cout<<"Please Confirm your ID and Password To Update!"<<endl;
    cout << "Enter your ID: "; 
    cin >> id;
    cout << "Enter your Password: "; 
    cin >> pass;

    EData *d = l->head;
    while (d) {
        if (d->emp.id == id && d->emp.password==pass) {
            int ch;
            cout << "Whice one do you want to update? \n1-First Name \n2-Last Name \n3-Phone \nEnter your choice: "; 
            cin >> ch;
            switch (ch) {
                case 1: cout << "New First Name: "; 
                    cin >> d->emp.firstName; 
                    cout<<"First Name has been updated successful!";
                    break;
                case 2: cout << "New Last Name: "; 
                    cin >> d->emp.lastName; 
                    cout<<"Last Name has been updated successful!";
                    break;
                case 3: cout << "New Phone Number: "; 
                    cin >> d->emp.phoneNumber; 
                    cout<<"Phone Number has been updated successful!";
                    break;
                default: 
                    cout << "Invalid choice." << endl;
            }
            writeEToFile(l);
            return;
        }
        d = d->next;
    }
    cout << "Incorrect ID/Password! Please try again." << endl;
}

void changePassword(EList *l) {
    if (!l->head) {
        cout << "No users." << endl;
        return;
    }

    string id, oldPass, newPass;
    cout << "Enter your ID: "; 
    cin >> id;
    cout << "Enter your old password: ";
    cin >> oldPass;

    EData *d = l->head;
    while (d) {
        if (d->emp.id == id && d->emp.password==oldPass) {
            cout << "New Password: "; 
            cin >> newPass;
            d->emp.password = newPass;
            writeEToFile(l);
            cout << "Password updated." << endl;
            return;
        }
       d = d->next;
    }
    cout << "Incorrect ID or Password!" << endl;
}


//display employee thier own info after login

void displayOwnInfo(EList *l, string pass) {
    EData *d = l->head;
    bool found = 0;
    cout<<"Please confirm your password first"<<endl;
    cout<<"Enter your password: ";
    cin>>pass;
    while (d) {
        if (d->emp.password == pass) {
            cout<<"---------------------------------------------------------------------------------------------------------\n";
            cout << "| "<< setw(10)<<left << "ID"
            <<  setw(15) <<left<< "First Name"
            <<  setw(15) <<left<< "Last Name"
            <<  setw(8)  <<left<< "Gender"
            <<  setw(15) <<left<< "Phone Number"
            <<  setw(15) <<left<< "Department"
            <<  setw(15) <<left<<  "Position"
            <<  setw(8) <<left<<  "Salary"
            <<  " |"<<endl;
            cout<<"---------------------------------------------------------------------------------------------------------\n";
            cout << "| "<< setw(10) <<left<< d ->emp.id
            <<  setw(15) <<left<< d ->emp.firstName
            <<  setw(15)<<left<< d ->emp.lastName
            <<  setw(8)<<left<< d ->emp.gender
            <<  setw(15)<<left<< d ->emp.phoneNumber
            <<  setw(15)<<left<< d ->emp.department
            <<  setw(15)<<left<< d->emp.position<<"$"
            <<  setw(8)<<left<< d->emp.salary
            <<  "|"<<endl;
            cout<<"---------------------------------------------------------------------------------------------------------\n";
            found = 1;
            break;
        }
        d = d->next;
    }
    if(!found){
        cout << "Incorrect Password!" << endl;
    }
}