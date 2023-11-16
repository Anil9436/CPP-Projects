#include "main.hpp"

sqlite3* db;
sqlite3_stmt* stmt;
int main()
{

    BookDetails Bfirst{};
    EmployeeDetails Efirst{};
    Suppliers Sfirst{};
    Bfirst.CreateDB1();
    Sfirst.CreateDB2();
    Efirst.CreateDB3();
    Bfirst.add();
    Bfirst.display();
    
    
}