#include <fstream>   //using fstream as a library to write fileio
#include <sstream>   //sstream use to write read from file

#include "../model/function.h"   //include funtion from model folder. ***** <../> mean to go up then look for function file

using namespace std;

// ==================== File.IO ====================

//Write Employee to the file csv
void writeEToFile(EList *l) {   
    ofstream f("employee.csv");
    if (!f) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    f << "ID,First Name,Last Name,Gender,Phone Number,Department,Position,Salary,Bonus,Password" << endl;  //before start write in to file 
    EData *e = l->head;
    while (e != nullptr) {
        f << e->emp.id << ","
          << e->emp.firstName << ","
          << e->emp.lastName << ","
          << e->emp.gender << ","
          << e->emp.phoneNumber << ","
          << e->emp.department << ","
          << e->emp.position << ","
          << e->emp.salary << ","
          << e->emp.bonus << "," 
          << e->emp.password<<endl;
        e = e->next;
    }
    f.close();
}

//read employee from the file
void readEFromFile(EList *l) { 
    ifstream f("employee.csv");
    if (!f) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    string line;
    getline(f, line); //  use for skip header
    while (getline(f, line)) {
        stringstream ss(line);
        string token;
        EInfo emp;

        getline(ss, emp.id, ',');
        getline(ss, emp.firstName, ',');
        getline(ss, emp.lastName, ',');
        getline(ss, token, ','); emp.gender = token[0];   //since gender are ch, then it will store in [0] in array
        getline(ss, emp.phoneNumber, ',');
        getline(ss, emp.department, ',');
        getline(ss, emp.position, ',');
        getline(ss, token, ','); emp.salary = stod(token); //stod for string to double 
        getline(ss, token, ','); emp.bonus = stod(token);
        getline(ss, emp.password, ',');

        EData *e = new EData;
        e->emp = emp;
        e->next = nullptr;

        if (l->head == nullptr) {
            l->head = l->tail = e;
        } else {
            l->tail->next = e;
            l->tail = e;
        }
        l->n++;
    }
    f.close();
}

// =================================== Leave =========================================

void writeReToFile(string id, string date, string reason) {   //use for request leave 
    ofstream f1("records.txt", ios::app);
    if (!f1) {
        cout << "Error opening file to write leave.\n";
        return;
    }

    f1 << "Request For Leave:\n"; 
    f1 << id << "\n"; 
    f1 << date << "\n"; 
    f1<< reason << "\n";
    f1 <<"---\n";
    f1.close();
}

void readReFromFile(string inputID) {
    ifstream f1("records.txt");
    if (!f1) {
        cout << "Error opening file to read.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(f1, line)) {
        if (line == "Request For Leave:") {
            string fileID, date, reason;
            getline(f1, fileID); 
            getline(f1, date);
            getline(f1, reason);

            if (fileID == inputID) {
                cout << "\nLeave Date: " << date << ", Reason: " << reason << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No leave records found for ID: " << inputID << endl;
    }

    f1.close();
}

//  ======================= Emergency Contact =============================

void writeEmgToFile(string id, string name, string phone) {   //For write Emergency Contact
    ofstream f2("records.txt", ios::app);
    if (!f2) {
        cout << "Error opening file to write emergency contact.\n";
        return;
    }

    f2 << "=> Emergency Contact:\n" ;
    f2 << id << "\n";
    f2 << name << "\n";
    f2 << phone << "\n";
    f2 << "---\n";
    f2.close();
}


void readEmgFromFile(string inputID) {
    ifstream f2("records.txt");
    if (!f2) {
        cout << "Error opening file to read emergency contacts.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(f2, line)) {
        if (line == "Emergency Contact:") {
            string fileID, name, phone;
            getline(f2, fileID);
            getline(f2, name);
            getline(f2, phone);

            if (fileID == inputID) {
                cout << "\nEmergency Contact for ID " << inputID << ": " << endl;
                cout << "Name: " << name << ", Phone: " << phone << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No emergency contact records found for ID: " << inputID << endl;
    }

    f2.close();
}


//sort employee by name after before write it to file
void sortEmpByName(EList *l) {
    if (l->head == nullptr || l->head->next == nullptr) {
        return;
    }

    bool swapped;
    do {
        swapped = false;
        EData *current = l->head;
        while (current->next != nullptr) {
            if (current->emp.firstName > current->next->emp.firstName) {
                swap(current->emp, current->next->emp);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}