#include <iomanip>
#include "fileio.h"

using namespace std;

void displayAllEmployees(EList *l) {   //display all employee in company
    if (l->head == nullptr) {
        cout << "No employees found." << endl;
        return;
    }
    EData *d = l->head;   //data always start from head
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

//employee can update their information such as fName, lName, pNumber
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

void changePassword(EList *l) {  //employee need to chnage password for secure their acc
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

void viewSalary(EList *l){         //employee can view their salary by this function
    if(!l->head){
        cout<<"There are no employee found!"<<endl;
        return;
    }
    string pass;
    cout<<"Please confrim your password first! "<<endl;
    cout<<"Enter your password: ";
    cin>>pass;

    EData *e = l->head;
    while(e){
        if(e->emp.password == pass){
            cout<<"Your Salary: "<<e->emp.salary<<"$"<<endl;
            return;
        }
        e = e->next;
    }
    cout<<"Incorrect Password! Please Try again!"<<endl;
}

void requestLeave(EList *l) {       // ask for requestLeave
    string id, reason, date, pass;
    bool found = 0;
    EData *d = l->head;
    cout<<"Please confirm your password first"<<endl;
    cout<<"Enter your password: ";
    cin>>pass;
    if(d->emp.password == pass){
        cout << "\t[+] If you want to request for leave, Please fill in this form: \n";
        cout << "\t[+] NOTED: You need to request 2 days before your leave.\n";
        cout << "Enter your ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter date for leave (YYYY-MM-DD): ";
        getline(cin, date);
        cout << "Enter reason for leave: ";
        getline(cin, reason);
    
        writeReToFile(id, date, reason);
        cout << "Leave request has been submitted to management.\n";
        found =1;
    }
    d = d->next;
    if(!found){
        cout<<"Incorrect Password! Please Try Again!"<<endl;
    }
}

void viewHisLeave(string id){  //For view their history
    cout<<"Please Enter your ID to see Leave History: ";
    cin>>id;
    readReFromFile(id);
}

void updateEmgInfo(EList *l) {              //employee can update their Emergency Contact suct ad Name, pNumber
    string id, contactName, contactPhone, pass;
    EData *d = l->head;
    bool found = 0;
    cout<<"Please confirm your password first"<<endl;
    cout<<"Enter your password: ";
    cin>>pass;
    if(d->emp.password == pass){
        cout << "Enter your ID: ";
        cin >> id;
        cin.ignore();
        cout << "Enter Emergency Contact Name: ";
        getline(cin, contactName);
        cout << "Enter Emergency Contact Phone: ";
        getline(cin, contactPhone);
    
        writeEmgToFile(id, contactName, contactPhone);
        cout << "Emergency contact updated successfully.\n";
        found = 1;
    }
    d = d->next;
    if(!found){
        cout<<"Incorrect Password! Please Try again!"<<endl;
    }
}

