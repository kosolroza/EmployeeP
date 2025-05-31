#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

//color codes
const string RESET = "\033[0m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string BLUE = "\033[34m";
const string MAGENTA = "\033[35m";
const string CYAN = "\033[36m";
const string WHITE = "\033[37m";

void askUser(){
    cout << "\033[1;34m";
    cout << "\t ----------------------- USER OPTIONS --------------------------\n";
    cout << "\t|                                                               |\n";
    cout << "\t|                    [1] Login as Manager                       |\n";
    cout << "\t|                                                               |\n";
    cout << "\t|                                                               |\n";
    cout << "\t|                    [2] Login as Employee                      |\n";
    cout << "\t|                                                               |\n";
    cout << "\t|                                                               |\n";
    cout << "\t|                    [3] Exit Program                           |\n";
    cout << "\t|                                                               |\n";
    cout << "\t --------------------------------------------------------------- \n\n\n";

    cout << "\033[1;35mEnter your choice : \033[0m";
}


void intoManager(){
    cout <<"\n\n";
        cout << "\033[1;36m";
        cout << "\t ------------------------ MANAGER MENU ------------------------- \n";
        cout << "\t|                                                              |\n";
        cout << "\t|                 [1]  View All Employees                      |\n";
        cout << "\t|                                                              |\n";
        cout << "\t|                 [2]  Add Employee into System                |\n";
        cout << "\t|                                                              |\n";
        cout << "\t|                 [3]  Update Employee into System             |\n";
        cout << "\t|                                                              |\n";
        cout << "\t|                 [4]  Remove Employee from System             |\n";
        cout << "\t|                                                              |\n";
        cout << "\t|                 [5]  Find Employee                           |\n";
        cout << "\t|                                                              |\n";
        cout << "\t|                 [6]  Exit                                    |\n";
        cout << "\t|                                                              |\n";
        cout << "\t --------------------------------------------------------------- \033[0m\n\n\n";

        cout << "\033[1;35mEnter your choice : \033[0m";
}


void intoEmployee(){
    cout <<"\n\n";
        cout << "\033[1;36m";
        cout << "\t ----------------------- EMPLOYEE MENU ------------------------- \n";
        cout << "\t|                                                              |\n";
        cout << "\t|          [1]  View All Employees in Company                  |\n";
        cout << "\t|                                                              |\n";
        cout << "\t|          [2]  Update My Personal Infomation                  |\n";
        cout << "\t|                                                              |\n";
        cout << "\t|          [3]  Change Password                                |\n";
        cout << "\t|                                                              |\n";
        cout << "\t|          [4]  View My personal Information                   |\n";
        cout << "\t|                                                              |\n";
        cout << "\t|          [5]  Exit                                           |\n";
        cout << "\t|                                                              |\n";
        cout << "\t --------------------------------------------------------------- \033[0m\n\n\n";

        cout << "\033[1;35mEnter your choice : \033[0m";
}


void loading(){
    cout<<"\n\033[1;36mPlease wait for a moment";
    for(int i=0; i<5; i++){
        Sleep(500);
        cout<<".";
    }
}

string coverPass(){
    char c;
    string pass;
    while((c = _getch()) != '\r') {  // Enter key stops input
         if(c == '\b'){
            if(!pass.empty()){
                pass.pop_back();
                cout << "\b \b";        
            }
        }else{
            pass += c;
            cout << "*";            
        }
    }
    cout <<endl;
    return pass;
}

