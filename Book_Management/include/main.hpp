#include<iostream>
#include<string_view>
#include<string>
#include<limits>
#include <iomanip>
#include<sqlite3.h>

#define maxInputSize  1000 // Adjust as needed

class BookDetails{
        int id;			// Primary Key
        std::string name;
        std::string auth;
        std::string publisher;
        int qty;
        public:
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
            void add_sup();
            void remove_supplier();
            void searchBySupplierid();
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
            void add_emp();
            void search_emp();
            void display();
            void del_emp();
};
