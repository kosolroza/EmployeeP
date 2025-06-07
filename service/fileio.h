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

    f << "ID,First Name,Last Name,Gender,Phone Number,Department,Position,Salary,Bonus,Password" << endl;
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
    getline(f, line); // Skip header
    while (getline(f, line)) {
        stringstream ss(line);
        string token;
        EInfo emp;

        getline(ss, emp.id, ',');
        getline(ss, emp.firstName, ',');
        getline(ss, emp.lastName, ',');
        getline(ss, token, ','); emp.gender = token[0];
        getline(ss, emp.phoneNumber, ',');
        getline(ss, emp.department, ',');
        getline(ss, emp.position, ',');
        getline(ss, token, ','); emp.salary = stod(token);
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

void writeReToFile(string id, string date, string reason) {
    ofstream fout("records.txt", ios::app);
    if (!fout) {
        cout << "Error opening file to write leave.\n";
        return;
    }

    fout << "===== LEAVE ====\n";
    fout << id << "\t" << date << "\t" << reason << "\n";
    fout.close();
}

void readReFromFile(string inputID) {
    ifstream fin("records.txt");
    if (!fin) {
        cout << "Error opening file to read.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(fin, line)) {
        if (line == "LEAVE") {
            string fileID, date, reason;
            getline(fin, fileID);
            getline(fin, date);
            getline(fin, reason);

            if (fileID == inputID) {
                cout << "\nLeave Date: " << date << ", Reason: " << reason << endl;
                found = true;
            }
        }
    }

    if (!found) {
        cout << "No leave records found for ID: " << inputID << endl;
    }

    fin.close();
}

//  ======================= Emergency Contact =============================

void writeEmgToFile(string id, string name, string phone) {
    ofstream fout("records.txt", ios::app);
    if (!fout) {
        cout << "Error opening file to write emergency contact.\n";
        return;
    }

    fout << "==== EMG ====\n";
    fout << id << "\t" << name << "\t" << phone << "\n";
    fout.close();
}


void readEmgFromFile(string inputID) {
    ifstream fin("records.txt");
    if (!fin) {
        cout << "Error opening file to read emergency contacts.\n";
        return;
    }

    string line;
    bool found = false;
    while (getline(fin, line)) {
        if (line == "EMG") {
            string fileID, name, phone;
            getline(fin, fileID);
            getline(fin, name);
            getline(fin, phone);

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

    fin.close();
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