#include<iostream>
#include<sqlite3.h>
#include<string_view>
#include<string>
#include<limits>
#include<bits/stdc++.h> 
#include<iomanip>



#define MAX_NAME_LENGTH 60
#define MAX_ADDRESS_LENGTH 120
extern sqlite3* db;
extern sqlite3_stmt* stmt;

class BookDetails{
        int id;			// Primary Key
        std::string name;
        std::string auth;
        std::string publisher;
        int qty;
        public:
            void CreateDB1();
            void getbyId();
            void getbyName();
            void add();
            void del();
            void display();
};

class Suppliers{
        int id;			//Primary Key
        std::string name;
        long int phn;
        std::string addr_line1;
        std::string addr_line2;
        std::string addr_city;
        std::string addr_state;
        public:
            void CreateDB2();
            void add_sup();
            void remove_supplier();
            void searchSupplierByid();
};

class EmployeeDetails{
        int id;				//Primary Key
        std::string name;
        std::string addr_line1;
        std::string addr_line2;
        std::string addr_city;
        std::string addr_state;
        long int phn;
        long int salary;
        public:
            void CreateDB3();
            void add_emp();
            void search_emp();
            void displayEmpDetails();
            void del_emp();
};
