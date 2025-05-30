#include <iostream>
#include <sstream>

using namespace std;

// ==================== Data Structures ====================

struct EmployeeInfo {
    char gender;
    string id, firstName, lastName, phoneNumber, department, position, password;
    double salary, bonus;
};

struct EmployeeData {
    EmployeeInfo emp;
    EmployeeData* next;
};

struct EmployeeList {
    int n;
    EmployeeData *head;
    EmployeeData *tail;
};

EmployeeList* createEmployeeList() {
    EmployeeList* list = new EmployeeList;
    list->n = 0;
    list->head = nullptr;
    list->tail = nullptr;
    return list;
}