#include <iostream>

using namespace std;

// ==================== Data Structures ====================

struct EInfo {      //Employee information
    char gender;
    string id, firstName, lastName, phoneNumber, department, position, password;
    double salary, bonus;
// Attendance
    bool att[30];  // for 30days
    int totalPresent;
    int totalAbs;

    string feedback;
    string dateLeave, reason; 
    string contactPhone, contanctName;
};

struct EData {     //Employee Data to store Employees Information
    EInfo emp;
    EData *next;
    EData *pre;
};

struct EList {    //Using single Linked List to put Employee into list 
    int n;
    EData *head;
    EData *tail;
};

EList* createEmployeeList() {   // Make List to store Employees
    EList* list = new EList;
    list->n = 0;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}

