#include "main.hpp"

sqlite3* db;
int rc = sqlite3_open("book_management.db", &db);

void BookDetails::add()
{
    
    std::cout<<"Enter the book ID: ";
    std::cin>>id;
    std::cout<<"Enter the book name: ";
    std::cin>>name;
    //std::getline(std::cin,name,'x');
    std::cout<<"Enter the book author: ";
    std::cin>>auth;
    //std::getline(std::cin,auth,'x');
    std::cout<<"Enter the book publisher: ";
    std::cin>>publisher;
    //std::getline(std::cin,publisher,'x');

    const std::string createTableSQL = "CREATE TABLE IF NOT EXISTS Book_Details ("
                 "id INTEGER PRIMARY KEY,"
                 "name TEXT NOT NULL,"
                 "auth TEXT,"
                 "publiser TEXT"
                 ");";

    ::rc = sqlite3_exec(db, createTableSQL.c_str(), 0, 0, 0);
    if (rc != SQLITE_OK) {
        std::cerr<< "SQL error: "<< sqlite3_errmsg(db)<<"\n";
        return;
    }

    const std::string sql = "INSERT INTO Book_Details (id, name, auth, publiser) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    ::rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
        sqlite3_close(db);
        return;
    }
    sqlite3_bind_int(stmt,1,id);
    sqlite3_bind_text(stmt,2,name.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,3,auth.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,4,publisher.c_str(),-1,SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        std::cout << "Value added to the table successfully." << std::endl;
    } else {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
    // sqlite3_finalize(stmt);
    // sqlite3_close(db);

    return;

}
void BookDetails::del()
{

    std::cout << "Please Enter the Option:\n"
              << "1) To Delete by the ID\n"
              << "2) To Delete by the Name\n"
              << "3) To Delete by the Publisher\n"
              << "4) To Delete by the Author\n";
    int option{};
    sqlite3_stmt* stmt; // need to move to global 
    const char* command = nullptr;
    std::cin>>option;
    switch (option){
    case 1:
        std::cout<<"Delete by ID"<<"\n";
        command = "DELETE FROM Book_Details WHERE id = ?;";
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
        std::cout<<"Delete by Name";
        command = "DELETE FROM Book_Details WHERE name = ?;";
        rc = sqlite3_prepare_v2(db, command, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
            sqlite3_close(db);
            return;
        }
        std::cout << "Enter the name to delete: ";
        std::cin >> name;
        std::cout<<name<<std::endl;
        sqlite3_bind_text(stmt,2,name.c_str(),-1,SQLITE_STATIC);
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) {
        std::cout << "Value Deleted from the table successfully." << std::endl;
        }else {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        }
        break;
    case 3:
        std::cout<<"Delete by Publisher";
        command = "DELETE FROM Book_Details WHERE publiser = ?;";
        rc = sqlite3_prepare_v2(db, command, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
            sqlite3_close(db);
            return;
        }
        std::cout << "Enter the ID to delete: ";
        std::cin >> publisher;
        std::cout<<publisher<<std::endl;
        sqlite3_bind_text(stmt,2,publisher.c_str(),-1,SQLITE_STATIC);
        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) {
        std::cout << "Value Deleted from the table successfully." << std::endl;
        }else {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        }
        break;
    case 4:
        std::cout<<"Delete by Author";
        command = "DELETE FROM Book_Details WHERE auth = ?;";
        rc = sqlite3_prepare_v2(db, command, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
            sqlite3_close(db);
            return;
        }
        std::cout << "Enter the author to delete: ";
        std::cin >> auth;
        std::cout<<auth<<std::endl;
        sqlite3_bind_text(stmt,2,auth.c_str(),-1,SQLITE_STATIC);
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
        std::cout<<"By Default using Delete by ID";
        break;
    }
    // sqlite3_finalize(stmt);

}
void BookDetails::display()
{

}
void BookDetails::getbyId()
{

}
void BookDetails::getbyName()
{

}

void Suppliers::add_sup()
{


}

void Suppliers::remove_supplier()
{


}

void Suppliers::searchBySupplierid()
{

}

void EmployeeDetails::add_emp()
{

}
void EmployeeDetails::search_emp()
{

}
void EmployeeDetails::del_emp()
{

}
// g++ -o my_program my_program.cpp -lsqlite3

int main()
{
    BookDetails first{};
    first.add();
    first.del();
}