#include "main.hpp"

void EmployeeDetails::CreateDB3()
{
    int rc = sqlite3_open("book_management.db", &db);
    const char* CreateEmployeeTable = "CREATE TABLE IF NOT EXISTS Employee_Details ("
                 "id INTEGER PRIMARY KEY,"
                 "name TEXT NOT NULL,"
                 "addr_line1 TEXT,"
                 "addr_line2 TEXT,"
                 "addr_city TEXT,"
                 "addr_state TEXT,"
                 "phn INTEGER NOT NULL,"
                 "salary INTEGER NOT NULL"
                 ");";

    rc = sqlite3_exec(db, CreateEmployeeTable, 0, 0, 0);
    if (rc != SQLITE_OK) {
        std::cerr<< "SQL error: "<< sqlite3_errmsg(db)<<"\n";
        sqlite3_close(db);
        return;
    }
    sqlite3_close(db);
}

void EmployeeDetails::add_emp()
{
    int rc = sqlite3_open("book_management.db", &db);
    std::cout<<"Enter the Employee ID: ";
    std::cin>>id;
    std::cout<<"Enter the Employee name: ";
    std::getline(std::cin,name);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout<<"Enter the Employee Address-1: ";
    std::getline(std::cin,addr_line1);
    std::cout<<"Enter the Employee Address-2: ";
    std::getline(std::cin,addr_line2);
    std::cout<<"Enter the Employee Address-City: ";
    std::getline(std::cin,addr_city);
    std::cout<<"Enter the Employee Address-State: ";
    std::getline(std::cin,addr_state);
    std::cout<<"Enter the Employee Phn number: ";
    std::cin>>phn;
    std::cout<<"Enter the Employee Salary: ";
    std::cin>>salary;
    const std::string sql = "INSERT INTO Employee_Details(id, name, addr_line1, addr_line2, addr_city, addr_state , phn,salary ) VALUES (?, ?, ?, ?, ?, ?, ?, ?);";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
        sqlite3_close(db);
        return;
    }
    sqlite3_bind_int(stmt,1,id);
    sqlite3_bind_text(stmt,2,name.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,3,addr_line1.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,4,addr_line2.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,5,addr_city.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,6,addr_state.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_int(stmt,7,phn);
    sqlite3_bind_int(stmt,8,salary);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        std::cout << "Value added to the table successfully." << std::endl;
    } else {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return;


}
void EmployeeDetails::search_emp()
{
    int rc = sqlite3_open("book_management.db", &db);
    const char* command  = "SELECT * FROM Employee_Details WHERE name = ?;";
    rc = sqlite3_prepare_v2(db, command, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << "test33"<< std::endl;
        sqlite3_close(db);
        return;
    }
    std::cout<<"Please enter the Name : "<<std::endl;
    std::getline(std::cin,name);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    sqlite3_bind_text(stmt,1,name.c_str(),-1,SQLITE_STATIC);
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        // Access and print the data from each column
        int columnCount = sqlite3_column_count(stmt);
        for (int i = 0; i < columnCount; i++) {
            const char* columnName = sqlite3_column_name(stmt, i);
            const char* columnValue = (const char*)sqlite3_column_text(stmt, i);
            std::cout << columnName << ": " << columnValue << " ";
        }
        std::cout << std::endl;
    }
    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void EmployeeDetails::displayEmpDetails()
{
    int rc = sqlite3_open("book_management.db", &db);
    const char* command  = "SELECT * FROM Employee_Details;";
    rc = sqlite3_prepare_v2(db, command, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        // Access and print the data from each column
        int columnCount = sqlite3_column_count(stmt);
        for (int i = 0; i < columnCount; i++) {
            const char* columnName = sqlite3_column_name(stmt, i);
            const char* columnValue = (const char*)sqlite3_column_text(stmt, i);
            std::cout << columnName << ": " << columnValue << " ";
        }
        std::cout << std::endl;
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);    
}
void EmployeeDetails::del_emp()
{
    int rc = sqlite3_open("book_management.db", &db);
    std::cout << "Please Enter the Option:\n"
              << "1) To Remove by the ID\n"
              << "2) To Remove by the Name\n";
    int option{};
    const char* command = nullptr;
    std::cin>>option;
    switch (option){
    case 1:
        std::cout<<"Remove by ID"<<"\n";
        command = "DELETE FROM Employee_Details WHERE id = ?;";
        rc = sqlite3_prepare_v2(db, command, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
            sqlite3_close(db);
            return;
        }
        int id;
        std::cout << "Enter the ID to delete: ";
        std::cin >> id;
        std::cout<<id<<std::endl;
        sqlite3_bind_int(stmt,1,id);
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) {
        std::cout << "Value Deleted from the table successfully." << std::endl;
        }else {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        }
        break;
    case 2:
        std::cout<<"Delete by Name"<<"\n";
        command = "DELETE FROM Employee_Details WHERE name = ?;";
        rc = sqlite3_prepare_v2(db, command, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
            sqlite3_close(db);
            return;
        }
        std::cout << "Enter the name to delete: ";
        std::getline(std::cin,name);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout<<name<<std::endl;
        sqlite3_bind_text(stmt,1,name.c_str(),-1,SQLITE_STATIC);
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) {
        std::cout << "Value Deleted from the table successfully." << std::endl;
        }else {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        }
        break;
    default:
        std::cout<<"By Default Delete the first row";
        command = "DELETE FROM Employee_Details WHERE rowid = (SELECT min(rowid) FROM Book_Details LIMIT 1);";
        rc = sqlite3_exec(db, command, 0,0,0);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
            sqlite3_close(db);
            return;
        }
        break;
    }
    sqlite3_close(db);


}
