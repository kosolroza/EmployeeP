#include "employee.h"

using namespace std;

// ==================== Manager Functions ====================

//To make sure string ID with biggercase and smaller are the same
string toLower(string s) {
    for (char &c : s) c = tolower(c);
    return s;
}

//================== Add Employee to list that we create =============

void displayEmployees(EList *l);

// Use add To End as addEmployee
void addEmployee(EList *l) {      
    displayEmployees(l);
    EInfo emp;   //call EInfo cause It store E'Info
    cout << "Enter ID: ";   // Check for duplicate ID so it can't be add to the list
    cin >> emp.id;

    EData *E = l->head;    //make sure that data start from head 
    while (E != nullptr) {
        if (toLower(E->emp.id) == toLower(emp.id)) {    //checking if id input with small letter or big letter
            cout << "Error: Employee with ID " << emp.id << " already exists. Cannot add duplicate." << endl;
            return;
        }
        E = E->next;
    }
    cout << "First Name: ";
    cin >> emp.firstName;
    cout << "Last Name: ";
    cin >> emp.lastName;
    cout << "Gender (M/F): ";
    cin >> emp.gender;
    cout << "Phone: ";
    cin >> emp.phoneNumber;
    cin.ignore();
    cout << "Department: ";
    getline(cin, emp.department);
    cout << "Position: ";
    getline(cin, emp.position);
    cout << "Salary: ";
    cin >> emp.salary;
    cout << "Bonus: ";
    cin >> emp.bonus;
    cout << "Password: ";
    cin >> emp.password;

    EData *e = new EData;  //Let all emp info = null all
    e->emp = emp;
    e->next = nullptr;
    e->pre = nullptr;
    if (l->head == nullptr){
        l->head = e;
        l->tail = e;
    }
    else {
        l->tail->next = e;
        e->pre = l->tail;
        l->tail = e;
    }
    l->n++;
    sortEmpByName(l);
    writeEToFile(l);
    cout<<"Employee has been add to system successfully!"<<endl;
}

//for manager update some wrong info about employee
void updateEmp(EList *l) {
    if (!l->head) {
        cout << "No employees to update." << endl;
        return;
    }
    displayEmployees(l);
    string id;
    cout << "Enter ID to update: "; 
    cin >> id;

    EData *e = l->head;   // also make sure that it start from head
    while (e) {
        if (e->emp.id == id) {
            int ch;
            cout << "Which one do you want to update? \n1-First Name \n2-Last Name \n3-Phone Number \n4-Department \n5-Position \n6-Salary \n7-Bonus\nEnter a choice: "; 
            cin >> ch;
            switch (ch) {
                case 1: cout << "New First Name: "; 
                    cin >> e->emp.firstName; 
                    break;
                case 2: cout << "New Last Name: "; 
                    cin >> e->emp.lastName; 
                    break;
                case 3: cout << "New Phone: "; 
                    cin >> e->emp.phoneNumber; 
                    break;
                case 4: cout << "New Department: "; 
                    cin >> e->emp.department; 
                    break;
                case 5: cout << "New Position: ";
                    cin >> e->emp.position; 
                    break;
                case 6: cout << "New Salary: "; 
                    cin >> e->emp.salary; 
                    break;
                case 7: cout << "New Bonus: "; 
                    cin >> e->emp.bonus; 
                    break;
                default: 
                    cout << "Invalid choice." << endl;
            }
            writeEToFile(l);    //afer update, writeToFile csv
            cout<<"Employee has been updated to system successfully!"<<endl;
            return;
        }
        e = e->next;
    }
    cout << "Employee not found." << endl;
}


//for manager to delete any employee
//this funtion is remove at position 
void removeEmp(EList *l) {
    if (!l->head) {
        cout << "No employees to remove." << endl;
        return;
    }

    string id;
    cout << "Enter ID to remove: "; 
    cin >> id;

    EData *e = l->head;
    EData *pre = nullptr;

    while(e != nullptr){
        if(e->emp.id == id){
            //for delete from head
            if(e->pre = nullptr){
                l->head = e->next;
            }
            else{
                pre->next = e->next;
            }
            //for delete from tail
            if(e==l->tail){
                l->tail = pre;
            }
            delete e;
            l->n--;
            writeEToFile(l);
            cout<<"Employee removed!"<<endl;
            return;
        }
        pre = e;
        e = e->next;
    }
    cout<<"Employee not found!"<<endl;
}

//looking for a employee much more easier for manager
void searchByID(EList *l) {
    string id;
    cout << "Enter ID to search: "; 
    cin >> id;
    EData *e = l->head;
    bool found = 0;
    while (e) {
        if (e->emp.id == id) {
            cout<<"--------------------------------------------------------------------------------------------------------------------\n";
            cout << "| "<< setw(10)<<left << "ID"
            <<  setw(15) <<left<< "First Name"
            <<  setw(15) <<left<< "Last Name"
            <<  setw(8)  <<left<< "Gender"
            <<  setw(15) <<left<< "Phone Number"
            <<  setw(15) <<left<< "Department"
            <<  setw(15) <<left<<  "Position"
            <<  setw(10) <<left<<  "Salary"
            <<  setw(8) <<left<<  "Bonus"
            <<  "  |"<<endl;
            cout<<"--------------------------------------------------------------------------------------------------------------------\n";
            cout << "| "<< setw(10) <<left<< e ->emp.id
            <<  setw(15) <<left<< e ->emp.firstName
            <<  setw(15)<<left<< e ->emp.lastName
            <<  setw(8)<<left<< e ->emp.gender
            <<  setw(15)<<left<< e ->emp.phoneNumber
            <<  setw(15)<<left<< e ->emp.department
            <<  setw(15)<<left<< e->emp.position<<"$"
            <<  setw(10)<<left<< e->emp.salary<<"$"
            <<  setw(8)<<left<< e->emp.bonus
            <<  "|"<<endl;
            cout<<"--------------------------------------------------------------------------------------------------------------------\n";
            found = 1;
            break;
        }
        e = e->next;
    }
    if(!found){
        cout<<"Not found!";
    }
}


// This function is to search Employee By name
void searchByname(EList *a){
    string name;
    cout << "Enter first name or last name to search: "; 
    cin>>name;
    EData *e = a->head;
    bool found = 0;
    while (e) {
        if (e->emp.firstName == name || e->emp.lastName == name) {
            cout<<"--------------------------------------------------------------------------------------------------------------------\n";
            cout << "| "<< setw(10)<<left << "ID"
            <<  setw(15) <<left<< "First Name"
            <<  setw(15) <<left<< "Last Name"
            <<  setw(8)  <<left<< "Gender"
            <<  setw(15) <<left<< "Phone Number"
            <<  setw(15) <<left<< "Department"
            <<  setw(15) <<left<<  "Position"
            <<  setw(10) <<left<<  "Salary"
            <<  setw(8) <<left<<  "Bonus"
            <<  "  |"<<endl;
            cout<<"--------------------------------------------------------------------------------------------------------------------\n";
            cout << "| "<< setw(10) <<left<< e ->emp.id
            <<  setw(15) <<left<< e ->emp.firstName
            <<  setw(15)<<left<< e ->emp.lastName
            <<  setw(8)<<left<< e ->emp.gender
            <<  setw(15)<<left<< e ->emp.phoneNumber
            <<  setw(15)<<left<< e ->emp.department
            <<  setw(15)<<left<< e->emp.position<<"$"
            <<  setw(10)<<left<< e->emp.salary<<"$"
            <<  setw(8)<<left<< e->emp.bonus
            <<  "|"<<endl;
            cout<<"--------------------------------------------------------------------------------------------------------------------\n";
            found = 1;
            break;
        }
        e = e->next;
    }
    if(!found){
        cout<<"Sorry The Employee is not found!. Please Try Again";
    }
}

//  This function is to search Employee by Department
void searchByDepart(EList *l){
    string depart, pos;
    cout << "Enter department to search: "; 
    cin >> depart;
    cout<<"Enter position to search: ";
    cin>>pos;
    EData *e = l->head;
    bool found = 0;
    bool dis = 0;   //for display more employee in that department
    while (e) {
        if (e->emp.department == depart && e->emp.position == pos) {
            if(!dis){
                cout<<"--------------------------------------------------------------------------------------------------------------------\n";
                cout << "| "<< setw(10)<<left << "ID"
                <<  setw(15) <<left<< "First Name"
                <<  setw(15) <<left<< "Last Name"
                <<  setw(8)  <<left<< "Gender"
                <<  setw(15) <<left<< "Phone Number"
                <<  setw(15) <<left<< "Department"
                <<  setw(15) <<left<<  "Position"
                <<  setw(10) <<left<<  "Salary"
                <<  setw(8) <<left<<  "Bonus"
                <<  "  |"<<endl;
                cout<<"--------------------------------------------------------------------------------------------------------------------\n";
                dis = 1;
            }

            cout << "| "<< setw(10) <<left<< e ->emp.id
            <<  setw(15) <<left<< e ->emp.firstName
            <<  setw(15)<<left<< e ->emp.lastName
            <<  setw(8)<<left<< e ->emp.gender
            <<  setw(15)<<left<< e ->emp.phoneNumber
            <<  setw(15)<<left<< e ->emp.department
            <<  setw(15)<<left<< e->emp.position<<"$"
            <<  setw(10)<<left<< e->emp.salary<<"$"
            <<  setw(8)<<left<< e->emp.bonus
            <<  "|"<<endl;
            found = 1;
        }
        e = e->next;
    }
    if(dis){
        cout<<"--------------------------------------------------------------------------------------------------------------------\n";
    }
    if(!found){
        cout<<"Sorry The Employee with "<<depart<<"and "<<pos<<"is not found!. Please Try Again";
    }
}

void askSearch(EList *s){
    int choice;
    cout<<"Choose the methods for Search Employee\n1. Search By ID\n2. Search By Name\n3. Search By Department"<<endl;
    cout<<"Enter your choice: ";
    cin>>choice;
    if(choice==1){
        searchByID(s);
    }
    else if(choice == 2){
        searchByname(s);
    }
    else if(choice==3){
        searchByDepart(s);
    }
    else{
        cout<<"Invalid Choice!"<<endl;
    }
}

void displayEmployees(EList *l) {
    if (l->head == nullptr) {
        cout << "No employees found." << endl;
        return;
    }

    EData *e = l->head;
    cout<<"--------------------------------------------------------------------------------------------------------------------\n";
    cout << "| "<< setw(10)<<left << "ID"
         <<  setw(15) <<left<< "First Name"
         <<  setw(15) <<left<< "Last Name"
         <<  setw(8)  <<left<< "Gender"
         <<  setw(15) <<left<< "Phone Number"
         <<  setw(15) <<left<< "Department"
         <<  setw(15) <<left<<  "Position"
         <<  setw(10) <<left<<  "Salary"
         <<  setw(8)  <<left<<  " Bonus"
         <<  "  |"<<endl;
    cout<<"--------------------------------------------------------------------------------------------------------------------\n";
    while (e != nullptr) {
        cout << "| "<< setw(10) <<left<< e ->emp.id
             <<  setw(15) <<left<< e ->emp.firstName
             <<  setw(15)<<left<< e ->emp.lastName
             <<  setw(8)<<left<< e ->emp.gender
             <<  setw(15)<<left<< e ->emp.phoneNumber
             <<  setw(15)<<left<< e ->emp.department
             <<  setw(15)<<left<< e->emp.position<<"$"
             <<  setw(10)<<left<<e->emp.salary<<"$"
             <<  setw(8)<<left<<e->emp.bonus
             <<  "|"<<endl;
        e = e ->next;
    }
    cout<<"--------------------------------------------------------------------------------------------------------------------\n";
}


void viewEmpByDepar(EList *l){
    string dep;
    cout<<"Display All Employee in department"<<endl;
    cout<<"Enter the name of department: ";
    cin>>dep;
    EData *e = l->head;
    bool found = 0;
    bool dis = 0;   //for display more employee in that department
    while (e) {
        if (e->emp.department == dep) {
            if(!dis){
                cout<<"--------------------------------------------------------------------------------------------------------------------\n";
                cout << "| "<< setw(10)<<left << "ID"
                <<  setw(15) <<left<< "First Name"
                <<  setw(15) <<left<< "Last Name"
                <<  setw(8)  <<left<< "Gender"
                <<  setw(15) <<left<< "Phone Number"
                <<  setw(15) <<left<< "Department"
                <<  setw(15) <<left<<  "Position"
                <<  setw(10) <<left<<  "Salary"
                <<  setw(8) <<left<<  "Bonus"
                <<  "  |"<<endl;
                cout<<"--------------------------------------------------------------------------------------------------------------------\n";
                dis = 1;
            }

            cout << "| "<< setw(10) <<left<< e ->emp.id
            <<  setw(15) <<left<< e ->emp.firstName
            <<  setw(15)<<left<< e ->emp.lastName
            <<  setw(8)<<left<< e ->emp.gender
            <<  setw(15)<<left<< e ->emp.phoneNumber
            <<  setw(15)<<left<< e ->emp.department
            <<  setw(15)<<left<< e->emp.position<<"$"
            <<  setw(10)<<left<< e->emp.salary<<"$"
            <<  setw(8)<<left<< e->emp.bonus
            <<  "|"<<endl;
            found = 1;
        }
        e = e->next;
    }
    if(dis){
        cout<<"--------------------------------------------------------------------------------------------------------------------\n";
    }
    if(!found){
        cout<<"The Company has no department"<<dep<<"!";
    }
}
 //Summary Report for employee
void summaryRep(EList *a){
    cout<<"\t\t ============= Employee summary report ==========="<<endl;
    cout<<" ==> Total Employee: "<<a->n<<endl;

    string departs[100];
    int depCount[100] = {0};
    int uniqueDep = 0;

    EData *e = a->head;
    while(e != nullptr){
        bool found = 0;
        for(int i= 0; i<uniqueDep; i++){
            if(departs[i] == e->emp.department){
                depCount[i]++;
                found = 1;
                break;
            }
        }
        if(!found){
            departs[uniqueDep] = e->emp.department;
            depCount[uniqueDep] = 1;
            uniqueDep++;
        }
        e = e->next;
    }
    cout << "\n--> Department-wise Count: "<<endl;
    for(int i=0; i<uniqueDep; i++){
        cout<<departs[i]<<": "<<depCount[i]<<"employees"<<endl;
    }
}

void salaryRep(EList *r){
    double totalSal = 0;
    double totalBonus = 0;
    double maxSal = 0;
    double minSal = 9999999;
    string highp, lowp;
    EData *e = r->head;
    while(e!=nullptr){
        totalSal += e->emp.salary;
        totalBonus += e->emp.bonus;

        if(e->emp.salary > maxSal){
            maxSal = e->emp.salary;
            highp = e->emp.firstName + " " + e->emp.lastName;
        }
        if(e->emp.salary < minSal){
            minSal = e->emp.salary;
            lowp = e->emp.firstName + " " +e->emp.lastName;
        }
        e = e->next;
    }
    cout<<"========= Salary Report =========="<<endl;
    cout<<"Total Payroll: "<<fixed<<setprecision(2)<<totalSal<<"$"<<endl;
    cout<<"Total Bonus: "<<totalBonus<<endl;
    cout<<"Average Salary: "<<totalSal / r->n <<endl;
    cout<<"Highest Paid: "<<highp<<"($"<<maxSal<<")"<<endl;
    cout<<"Lowest Paid: "<<lowp<<"($"<<minSal<<")"<<endl;
}

void generateReportEmp(EList *s){
    if(s->head == nullptr){
        cout<<"No Employee data available for report!"<<endl;
        return;
    }
    int choice;
    cout<<"========== Generate Report ==========="<<endl;
    cout<<"1. Employee Summary Report"<<endl;
    cout<<"2. Department-wise Report"<<endl;
    cout<<"3. Salary Report"<<endl;
    cout<<"Please Enter your choice: ";
    cin>>choice;

    switch(choice){
        case 1:{
            summaryRep(s);
            break;
        }
        case 2:{
            displayAllEmployees(s);
            break;
        }
        case 3:{
            salaryRep(s);
            break;
        }
    }
}
