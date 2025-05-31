#include <iostream>
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

    f << "ID,First Name,Last Name,Gender,Phone Number,Department,Position,Salary,Bonus" << endl;
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

//sort employee by name after before write it to file
void sortEmpByName(EList *l) {
    if (l->head == nullptr || l->head->next == nullptr) return;

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