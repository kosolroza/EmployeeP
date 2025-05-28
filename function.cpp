#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

// ==================== Data Structures ====================

struct EmployeeInfo {
    char gender;
    string id, firstName, lastName, phoneNumber, department, position,password;
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

// ==================== File I/O ====================

void writeEmployeeToFile(EmployeeList *l) {
    ofstream f("employee.csv");
    if (!f) {
        cerr << "Error opening file for writing." << endl;
        return;
    }

    f << "ID,First Name,Last Name,Gender,Phone Number,Department,Position,Salary,Bonus" << endl;
    EmployeeData *e = l->head;
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

void readEmployeeFromFile(EmployeeList *l) {
    ifstream f("employee.csv");
    if (!f) {
        cerr << "Error opening file for reading." << endl;
        return;
    }

    string line;
    getline(f, line); // Skip header
    while (getline(f, line)) {
        stringstream ss(line);
        string token;
        EmployeeInfo emp;

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

        EmployeeData *e = new EmployeeData;
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

void sortEmpByName(EmployeeList *l) {
    if (l->head == nullptr || l->head->next == nullptr) return;

    bool swapped;
    do {
        swapped = false;
        EmployeeData *current = l->head;
        while (current->next != nullptr) {
            if (current->emp.firstName > current->next->emp.firstName) {
                swap(current->emp, current->next->emp);
                swapped = true;
            }
            current = current->next;
        }
    } while (swapped);
}

// ==================== Employee Functions ====================
void addEmployee(EmployeeList *l) {
    EmployeeInfo emp;
    cout << "Enter ID: "; cin >> emp.id;
    cout << "First Name: "; cin >> emp.firstName;
    cout << "Last Name: "; cin >> emp.lastName;
    cout << "Gender (M/F): "; cin >> emp.gender;
    cout << "Phone: "; cin >> emp.phoneNumber;
    cin.ignore();
    cout << "Department: "; getline(cin, emp.department);
    cout << "Position: "; getline(cin, emp.position);
    cout << "Salary: "; cin >> emp.salary;
    cout << "Bonus: "; cin >> emp.bonus;
    cout << "Password: "; cin >> emp.password;

    EmployeeData *e = new EmployeeData{emp, nullptr};

    if (l->head == nullptr) l->head = l->tail = e;
    else { l->tail->next = e; l->tail = e; }

    l->n++;
    sortEmpByName(l);
    writeEmployeeToFile(l);
}

void displayEmployees(EmployeeList *l) {
    if (l->head == nullptr) {
        cout << "No employees found." << endl;
        return;
    }

    EmployeeData *current = l->head;
    while (current != nullptr) {
        cout << current->emp.id << " | "
             << current->emp.firstName << " "
             << current->emp.lastName << " | "
             << current->emp.department << " | "
             << current->emp.position << " | "
             << current->emp.salary << " | "
             << current->emp.bonus << endl;
        current = current->next;
    }
}

void updateEmp(EmployeeList *l) {
    if (!l->head) {
        cout << "No employees to update." << endl;
        return;
    }
    string id;
    cout << "Enter ID to update: "; cin >> id;

    EmployeeData *e = l->head;
    while (e) {
        if (e->emp.id == id) {
            cout << "What to update? 1-First Name, 2-Last Name, 3-Phone, 4-Dept, 5-Pos, 6-Salary, 7-Bonus: ";
            int ch; cin >> ch;
            switch (ch) {
                case 1: cout << "New First Name: "; cin >> e->emp.firstName; break;
                case 2: cout << "New Last Name: "; cin >> e->emp.lastName; break;
                case 3: cout << "New Phone: "; cin >> e->emp.phoneNumber; break;
                case 4: cout << "New Dept: "; cin >> e->emp.department; break;
                case 5: cout << "New Pos: "; cin >> e->emp.position; break;
                case 6: cout << "New Salary: "; cin >> e->emp.salary; break;
                case 7: cout << "New Bonus: "; cin >> e->emp.bonus; break;
                default: cout << "Invalid choice." << endl;
            }
            writeEmployeeToFile(l);
            return;
        }
        e = e->next;
    }
    cout << "Employee not found." << endl;
}

void removeEmp(EmployeeList *l) {
    if (!l->head) {
        cout << "No employees to remove." << endl;
        return;
    }

    string id;
    cout << "Enter ID to remove: "; cin >> id;

    EmployeeData *curr = l->head, *prev = nullptr;
    while (curr) {
        if (curr->emp.id == id) {
            if (!prev) l->head = curr->next;
            else prev->next = curr->next;
            if (curr == l->tail) l->tail = prev;
            delete curr;
            l->n--;
            writeEmployeeToFile(l);
            cout << "Employee removed." << endl;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
    cout << "Employee not found." << endl;
}

void searchByID(EmployeeList *l) {
    string id;
    cout << "Enter ID to search: "; cin >> id;
    EmployeeData *e = l->head;
    while (e) {
        if (e->emp.id == id) {
            cout << e->emp.firstName << " " << e->emp.lastName << " | "
                 << e->emp.department << " | " << e->emp.position << endl;
            return;
        }
        e = e->next;
    }
    cout << "Not found." << endl;
}

void changePassword(EmployeeList *l) {
    if (!l->head) {
        cout << "No users." << endl;
        return;
    }

    string id, newPass;
    cout << "Enter ID: "; cin >> id;

    EmployeeData *L = l->head;
    while (L) {
        if (L->emp.id == id) {
            cout << "New Password: "; cin >> newPass;
            L->emp.password = newPass;
            writeEmployeeToFile(l);
            cout << "Password updated." << endl;
            return;
        }
        L = L->next;
    }
    cout << "User not found." << endl;
}

EmployeeList *elist = createEmployeeList();

void ManagerBoard() {
    int ch;
    while (true) {
        cout << "\n1-View\n2-Add\n3-Update\n4-Delete\n5-Search\n6-Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: displayEmployees(elist); break;
            case 2: addEmployee(elist); break;
            case 3: updateEmp(elist); break;
            case 4: removeEmp(elist); break;
            case 5: searchByID(elist); break;
            case 6: return;
            default: cout << "Invalid." << endl;
        }
    }
}

void employeeBoard() {
    int ch;
    while (true) {
        cout << "\n1-View Personal Info\n2-Update Personal Info\n3-Change Password\n4.exit\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: displayEmployees(elist); break;
            case 2: updateEmp(elist); break;
            case 3: changePassword(elist);
            case 4: return;
            default: cout << "Invalid." << endl;
        }
    }
}

void loginManager() {
    string email, pass;
    cout << "Email: "; cin >> email;
    cout << "Pass: "; cin >> pass;
    if (email == "manager" && pass == "manager") {
        cout << "Login success." << endl;
        ManagerBoard();
    } else {
        cout << "Try again." << endl;
        loginManager();
    }
}

void loginEmployee() {
    string id, pass;
    cout << "ID: "; cin >> id;
    cout << "Pass: "; cin >> pass;
    EmployeeData *L = elist->head;
    while (L) {
        if (L->emp.id == id && L->emp.password == pass) {
            cout << "Welcome!" << endl;
            employeeBoard();
            return;
        }
        L = L->next;
    }
    cout << "Invalid. Try again." << endl;
    loginEmployee();
}

void firstboard() {
    int ch;
    while (true) {
        cout << "\n1-Login as Manager\n2-Login as Employee\n3-Exit\nChoice: ";
        cin >> ch;
        switch (ch) {
            case 1: loginManager(); break;
            case 2: loginEmployee(); break;
            case 3: return;
            default: cout << "Invalid." << endl;
        }
    }
}

int main() {
    readEmployeeFromFile(elist);
    firstboard();
    writeEmployeeToFile(elist);
    return 0;
}


