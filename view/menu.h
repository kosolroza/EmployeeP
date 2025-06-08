#include "../service/manager.h"
#include "ui.h"


//create a empty list
EList *elist = createEmployeeList(); 
void ManagerBoard() {
    int ch;
    system("cls");
    while (true) {
        intoManager();
        cin >> ch;
        switch (ch) {
            case 1: 
                displayEmployees(elist); 
                break;
            case 2: 
                addEmployee(elist);
                 break;
            case 3: 
                updateEmp(elist); 
                break;
            case 4: 
                removeEmp(elist); 
                break;
            case 5: 
                askSearch(elist);
                break;
            case 6: 
                viewEmpByDepar(elist);  
                break;
            case 7:
                generateReportEmp(elist);
                break;
            case 8: 
                return;
            default: 
                cout << "Invalid." << endl;
        }
    }
}

//to know who employee is in control right now
string currentLoginID;

//employee interface
void employeeBoard() {
    int ch;
    system("cls");
    while (true) {
        intoEmployee();
        cin >> ch;
        switch (ch) {
            case 1: 
                displayAllEmployees(elist); 
                break;
            case 2: 
                updateMyInfo(elist); 
                break;
            case 3: 
                changePassword(elist);
                break;
            case 4:
                displayOwnInfo(elist, currentLoginID);
                break;
            case 5: 
                viewSalary(elist);
                break;
            case 6:
                requestLeave();
                break;
            case 7:
                updateEmgInfo();
                break;
            case 8:
                return;
            default: 
            cout << "Invalid." << endl;
        }
    }
}

//manager login 
void loginManager() {
    string email, pass;
    cout << "\033[1;33mEnter manager's email: \033[0m"; 
    cin >> email;
    cout << "\033[1;33mEnter manager's password: \033[0m"; 
    pass = coverPass();
    if (email == "manager" && pass == "manager") {
        loading();
        cout<<"\n\n";
        cout << "\033[1;32mLogin successful!.\033[0m";
        sleep(1);      //sleep for 1 second
        ManagerBoard();
    } else {
        cout << "\033[1;31mInvalid Email or Password. Please Try again. \033[0m" << endl;
        loginManager();
    }
}

//employee login
void loginEmployee() {
    string loginId, loginPass;
    cout << "\033[1;32mEnter your ID: \033[0m"; 
    cin >> loginId;
    cout << "\033[1;32mEnter your password: \033[0m"; 
    loginPass = coverPass();
    EData *L = elist->head;
    while (L) {
        if (L->emp.id == loginId && L->emp.password == loginPass) {
            loading();
            cout<<"\n\n";
            cout << "\033[1;33m========== Welcome! ==========\033[0m";
            sleep(1);
            currentLoginID = loginId;
            employeeBoard();
            return;
        }
        L = L->next;
    }
    cout << "\033[1;31mInvalid ID or Password. Please Try again. \033[0m" << endl;
    loginEmployee();
}

//The 1st interface before anythings
void firstboard() {
    int ch;
    while (true) {
        system("cls");
        askUser();
        cin >> ch;
        switch (ch) {
            case 1: 
                loginManager(); 
                break;
            case 2: 
                loginEmployee(); 
                break;
            case 3: 
                return;
            default: 
                cout << "Invalid." << endl;
        }
    }
}