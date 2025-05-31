// // #include<sstream>
// // #include<string>
// // #include<fstream>
// #include <iomanip>
// #include <iostream>
// #include "employee.h"
// using namespace std;

// // ==================== File.IO ====================

// // //Write Employee to the file
// // void writeEmployeeToFile(EmployeeList *l) {
// //     ofstream f("employee.csv");
// //     if (!f) {
// //         cout << "Error opening file for writing." << endl;
// //         return;
// //     }

// //     f << "ID,First Name,Last Name,Gender,Phone Number,Department,Position,Salary,Bonus" << endl;
// //     EmployeeData *e = l->head;
// //     while (e != nullptr) {
// //         f << e->emp.id << ","
// //           << e->emp.firstName << ","
// //           << e->emp.lastName << ","
// //           << e->emp.gender << ","
// //           << e->emp.phoneNumber << ","
// //           << e->emp.department << ","
// //           << e->emp.position << ","
// //           << e->emp.salary << ","
// //           << e->emp.bonus << "," 
// //           << e->emp.password<<endl;
// //         e = e->next;
// //     }
// //     f.close();
// // }

// // //read employee from the file
// // void readEmployeeFromFile(EmployeeList *l) {
// //     ifstream f("employee.csv");
// //     if (!f) {
// //         cout << "Error opening file for reading." << endl;
// //         return;
// //     }

// //     string line;
// //     getline(f, line); // Skip header
// //     while (getline(f, line)) {
// //         stringstream ss(line);
// //         string token;
// //         EmployeeInfo emp;

// //         getline(ss, emp.id, ',');
// //         getline(ss, emp.firstName, ',');
// //         getline(ss, emp.lastName, ',');
// //         getline(ss, token, ','); emp.gender = token[0];
// //         getline(ss, emp.phoneNumber, ',');
// //         getline(ss, emp.department, ',');
// //         getline(ss, emp.position, ',');
// //         getline(ss, token, ','); emp.salary = stod(token);
// //         getline(ss, token, ','); emp.bonus = stod(token);
// //         getline(ss, emp.password, ',');

// //         EmployeeData *e = new EmployeeData;
// //         e->emp = emp;
// //         e->next = nullptr;

// //         if (l->head == nullptr) {
// //             l->head = l->tail = e;
// //         } else {
// //             l->tail->next = e;
// //             l->tail = e;
// //         }
// //         l->n++;
// //     }
// //     f.close();
// // }

// //sort employee by name after before write it to file
// // void sortEmpByName(EmployeeList *l) {
// //     if (l->head == nullptr || l->head->next == nullptr) return;

// //     bool swapped;
// //     do {
// //         swapped = false;
// //         EmployeeData *current = l->head;
// //         while (current->next != nullptr) {
// //             if (current->emp.firstName > current->next->emp.firstName) {
// //                 swap(current->emp, current->next->emp);
// //                 swapped = true;
// //             }
// //             current = current->next;
// //         }
// //     } while (swapped);
// // }

// // ==================== Manager Functions ====================

// //To make sure string ID with biggercase and smaller are the same
// string toLower(string s) {
//     for (char &c : s) c = tolower(c);
//     return s;
// }

// //add employee to list that we create
// void addEmployee(EmployeeList *l) {
//     EmployeeInfo emp;

//     cout << "Enter ID: ";
//     cin >> emp.id;

//     // Check for duplicate ID so it can't be add to the list
//     EmployeeData *current = l->head;
//     while (current != nullptr) {
//         if (toLower(current->emp.id) == toLower(emp.id)) {
//             cout << "Error: Employee with ID " << emp.id << " already exists. Cannot add duplicate." << endl;
//             return;
//         }
//         current = current->next;
//     }

//     cout << "First Name: ";
//     cin >> emp.firstName;
//     cout << "Last Name: ";
//     cin >> emp.lastName;
//     cout << "Gender (M/F): ";
//     cin >> emp.gender;
//     cout << "Phone: ";
//     cin >> emp.phoneNumber;
//     cin.ignore();
//     cout << "Department: ";
//     getline(cin, emp.department);
//     cout << "Position: ";
//     getline(cin, emp.position);
//     cout << "Salary: ";
//     cin >> emp.salary;
//     cout << "Bonus: ";
//     cin >> emp.bonus;
//     cout << "Password: ";
//     cin >> emp.password;

//     EmployeeData *e = new EmployeeData{emp, nullptr};

//     if (l->head == nullptr)
//         l->head = l->tail = e;
//     else {
//         l->tail->next = e;
//         l->tail = e;
//     }

//     l->n++;
//     sortEmpByName(l);
//     writeEmployeeToFile(l);
// }

// //display all employee info for manager except his/her password
// void displayEmployees(EmployeeList *l) {
//     if (l->head == nullptr) {
//         cout << "No employees found." << endl;
//         return;
//     }

//     EmployeeData *current = l->head;
//     cout <<  left << setw(10) << "ID"
//          <<  setw(20)<< "First Name"
//          <<  setw(20)<< "Last Name"
//          <<  setw(10)<< "Gender"
//          <<  setw(20)<< "Phone Number"
//          <<  setw(20)<< "Department"
//          <<  setw(20)<< "Position"
//          <<  setw(20)<< "Salary"
//          <<  setw(20)<< "Bonus"
//          <<  endl;
//     while (current != nullptr) {
//         cout <<  left << setw(10) << current ->emp.id
//              <<  setw(20)<< current ->emp.firstName
//              <<  setw(20)<< current ->emp.lastName
//              <<  setw(10)<< current ->emp.gender
//              <<  setw(20)<< current ->emp.phoneNumber
//              <<  setw(20)<< current ->emp.department
//              <<  setw(20)<< current ->emp.position
//              <<  setw(20)<< current ->emp.salary
//              <<  setw(20)<< current ->emp.bonus
//              <<  endl;
//         current= current ->next;
//     }
// }

// //display employees to other but hide their privacy info
// // void displayForEmployees(EmployeeList *l) {
// //     if (l->head == nullptr) {
// //         cout << "No employees found." << endl;
// //         return;
// //     }

// //     EmployeeData *current = l->head;
// //     cout << left << setw(10) << "ID"
// //          <<  setw(20)<< "First Name"
// //          <<  setw(20)<< "Last Name"
// //          <<  setw(10)<< "Gender"
// //          <<  setw(20)<< "Phone Number"
// //          <<  setw(20)<< "Department"
// //          <<  setw(20)<< "Position"
// //          <<  endl;
// //     while (current != nullptr) {
// //         cout <<  left << setw(10) << current ->emp.id
// //              <<  setw(20)<< current ->emp.firstName
// //              <<  setw(20)<< current ->emp.lastName
// //              <<  setw(10)<< current ->emp.gender
// //              <<  setw(20)<< current ->emp.phoneNumber
// //              <<  setw(20)<< current ->emp.department
// //              <<  setw(20)<< current ->emp.position
// //              <<  endl;
// //         current= current ->next;
// //     }
// // }

// //for manager update some wrong info about employee
// void updateEmp(EmployeeList *l) {
//     if (!l->head) {
//         cout << "No employees to update." << endl;
//         return;
//     }
//     string id;
//     cout << "Enter ID to update: "; 
//     cin >> id;

//     EmployeeData *e = l->head;
//     while (e) {
//         if (e->emp.id == id) {
//             int ch;
//             cout << "What to update? \n1-First Name \n2-Last Name \n3-Phone Number \n4-Department \n5-Position \n6-Salary \n7-Bonus\nEnter a choice: "; 
//             cin >> ch;
//             switch (ch) {
//                 case 1: cout << "New First Name: "; 
//                     cin >> e->emp.firstName; 
//                     break;
//                 case 2: cout << "New Last Name: "; 
//                     cin >> e->emp.lastName; 
//                     break;
//                 case 3: cout << "New Phone: "; 
//                     cin >> e->emp.phoneNumber; 
//                     break;
//                 case 4: cout << "New Dept: "; 
//                     cin >> e->emp.department; 
//                     break;
//                 case 5: cout << "New Pos: ";
//                     cin >> e->emp.position; 
//                     break;
//                 case 6: cout << "New Salary: "; 
//                     cin >> e->emp.salary; 
//                     break;
//                 case 7: cout << "New Bonus: "; 
//                     cin >> e->emp.bonus; 
//                     break;
//                 default: 
//                     cout << "Invalid choice." << endl;
//             }
//             writeEmployeeToFile(l);
//             return;
//         }
//         e = e->next;
//     }
//     cout << "Employee not found." << endl;
// }

// // //employee has right to edit their info as well but not fully as manager
// // void updateMyInfo(EmployeeList *l) {
// //     if (!l->head) {
// //         cout << "No employees to update." << endl;
// //         return;
// //     }
// //     string id, pass;
// //     cout << "Enter your ID to update: "; 
// //     cin >> id;
// //     cout << "Enter your Password to update: "; 
// //     cin >> pass;

// //     EmployeeData *e = l->head;
// //     while (e) {
// //         if (e->emp.id == id && e->emp.password==pass) {
// //             int ch;
// //             cout << "What to update?: \n1-First Name \n2-Last Name \n3-Phone \nEnter your choice: "; 
// //             cin >> ch;
// //             switch (ch) {
// //                 case 1: cout << "New First Name: "; 
// //                     cin >> e->emp.firstName; 
// //                     break;
// //                 case 2: cout << "New Last Name: "; 
// //                     cin >> e->emp.lastName; 
// //                     break;
// //                 case 3: cout << "New Phone: "; 
// //                     cin >> e->emp.phoneNumber; 
// //                     break;
// //                 default: 
// //                     cout << "Invalid choice." << endl;
// //             }
// //             writeEmployeeToFile(l);
// //             return;
// //         }
// //         e = e->next;
// //     }
// //     cout << "Incorrect ID/Password! Please try again." << endl;
// // }

// //for manager to delete any employee
// void removeEmp(EmployeeList *l) {
//     if (!l->head) {
//         cout << "No employees to remove." << endl;
//         return;
//     }

//     string id;
//     cout << "Enter ID to remove: "; 
//     cin >> id;

//     EmployeeData *curr = l->head, *prev = nullptr;
//     while (curr) {
//         if (curr->emp.id == id) {
//             if (!prev) l->head = curr->next;
//             else prev->next = curr->next;
//             if (curr == l->tail) l->tail = prev;
//             delete curr;
//             l->n--;
//             writeEmployeeToFile(l);
//             cout << "Employee removed." << endl;
//             return;
//         }
//         prev = curr;
//         curr = curr->next;
//     }
//     cout << "Employee not found." << endl;
// }

// //looking for a employee much more easier for manager
// void searchByID(EmployeeList *l) {
//     string id;
//     cout << "Enter ID to search: "; 
//     cin >> id;
//     EmployeeData *current = l->head;
//     while (current) {
//         if (current->emp.id == id) {
//             cout << left << setw(10) << "ID"
//                 <<  setw(20)<< "First Name"
//                 <<  setw(20)<< "Last Name"
//                 <<  setw(10)<< "Gender"
//                 <<  setw(20)<< "Phone Number"
//                 <<  setw(20)<< "Department"
//                 <<  setw(20)<< "Position"
//                 <<  setw(20)<< "Salary"
//                 <<  setw(20)<< "Bonus"
//                 << endl;
//             cout << left << setw(10) << current ->emp.id
//                 <<  setw(20)<< current ->emp.firstName
//                 <<  setw(20)<< current ->emp.lastName
//                 <<  setw(10)<< current ->emp.gender
//                 <<  setw(20)<< current ->emp.phoneNumber
//                 <<  setw(20)<< current ->emp.department
//                 <<  setw(20)<< current ->emp.position
//                 <<  setw(20)<< current ->emp.salary
//                 <<  setw(20)<< current->emp.bonus
//                 << endl;
//         }
//         current = current->next;
//         return;
//     }
//     cout << "Not found." << endl;
// }

// // //display employee thier own info after login
// // void displayEmployee(EmployeeList *l, string id) {
// //     EmployeeData *current = l->head;
// //     while (current) {
// //         if (current->emp.id == id) {
// //             cout <<  left << setw(10) << "ID"
// //                 <<  setw(20)<< "First Name"
// //                 <<  setw(20)<< "Last Name"
// //                 <<  setw(10)<< "Gender"
// //                 <<  setw(20)<< "Phone Number"
// //                 <<  setw(20)<< "Department"
// //                 <<  setw(20)<< "Position"
// //                 <<  setw(20)<< "Salary"
// //                 <<  setw(20)<< "Bonus"
// //                 <<  endl;
// //             cout <<  left << setw(10) << current ->emp.id
// //              <<  setw(20)<< current ->emp.firstName
// //              <<  setw(20)<< current ->emp.lastName
// //              <<  setw(10)<< current ->emp.gender
// //              <<  setw(20)<< current ->emp.phoneNumber
// //              <<  setw(20)<< current ->emp.department
// //              <<  setw(20)<< current ->emp.position
// //              <<  setw(20)<< current ->emp.salary
// //              <<  setw(20)<< current ->emp.bonus
// //              <<  endl;
// //             return;
// //         }
// //         current = current->next;
// //     }
// //     cout << "Incorrect ID/Password or not found." << endl;
// //     return;
// // }

// //employee can change thier password in case somethings wrong
// // void changePassword(EmployeeList *l) {
// //     if (!l->head) {
// //         cout << "No users." << endl;
// //         return;
// //     }

// //     string id, oldPass, newPass;
// //     cout << "Enter your ID: "; 
// //     cin >> id;
// //     cout << "Enter your old password: ";
// //     cin >> oldPass;

// //     EmployeeData *L = l->head;
// //     while (L) {
// //         if (L->emp.id == id && L->emp.password==oldPass) {
// //             cout << "New Password: "; 
// //             cin >> newPass;
// //             L->emp.password = newPass;
// //             writeEmployeeToFile(l);
// //             cout << "Password updated." << endl;
// //             return;
// //         }
// //         L = L->next;
// //     }
// //     cout << "Incorrect ID or Password!" << endl;
// // }

// //create a empty list
// EmployeeList *elist = createEmployeeList();

// //manager interface
// void ManagerBoard() {
//     int ch;
//     while (true) {
//         cout << "\n1-View\n2-Add\n3-Update\n4-Delete\n5-Search\n6-Exit\nChoice: ";
//         cin >> ch;
//         switch (ch) {
//             case 1: 
//                 displayEmployees(elist); 
//                 break;
//             case 2: 
//                 addEmployee(elist);
//                  break;
//             case 3: 
//                 updateEmp(elist); 
//                 break;
//             case 4: 
//                 removeEmp(elist); 
//                 break;
//             case 5: 
//                 searchByID(elist); 
//                 break;
//             case 6: 
//                 return;
//             default: 
//                 cout << "Invalid." << endl;
//         }
//     }
// }

// //to know who employee is in control right now
// string currentLoginID;

// //employee interface
// void employeeBoard() {
//     int ch;
//     while (true) {
//         cout << "\n1-View Employees Info\n2-Update My Personal Info\n3-Change My Password\n4.View My personal Info\n5.Exit\nChoice: ";
//         cin >> ch;
//         switch (ch) {
//             case 1: 
//                 displayForEmployees(elist); 
//                 break;
//             case 2: 
//                 updateMyInfo(elist); 
//                 break;
//             case 3: 
//                 changePassword(elist);
//                 break;
//             case 4: 
//                 displayEmployee(elist, currentLoginID);
//                 break;
//             case 5: 
//                 return;
//             default: 
//             cout << "Invalid." << endl;
//         }
//     }
// }

// //manager login 
// void loginManager() {
//     string email, pass;
//     cout << "Enter manager's email: "; 
//     cin >> email;
//     cout << "Enter manager's password: "; 
//     cin >> pass;
//     if (email == "manager" && pass == "manager") {
//         cout << "Login success." << endl;
//         ManagerBoard();
//     } else {
//         cout << "Try again." << endl;
//         loginManager();
//     }
// }

// //employee login
// void loginEmployee() {
//     string loginId, loginPass;
//     cout << "Enter your ID: "; 
//     cin >> loginId;
//     cout << "Enter your password: "; 
//     cin >> loginPass;
//     EmployeeData *L = elist->head;
//     while (L) {
//         if (L->emp.id == loginId && L->emp.password == loginPass) {
//             cout << "Welcome!" << endl;
//             currentLoginID = loginId;
//             employeeBoard();
//             return;
//         }
//         L = L->next;
//     }
//     cout << "Invalid! Please try again." << endl;
//     loginEmployee();
// }

// //The 1st interface before anythings
// void firstboard() {
//     int ch;
//     while (true) {
//         cout << "\n1-Login as Manager\n2-Login as Employee\n3-Exit\nChoice: ";
//         cin >> ch;
//         switch (ch) {
//             case 1: 
//                 loginManager(); 
//                 break;
//             case 2: 
//                 loginEmployee(); 
//                 break;
//             case 3: 
//                 return;
//             default: 
//                 cout << "Invalid." << endl;
//         }
//     }
// }



