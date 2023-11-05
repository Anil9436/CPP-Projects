#include "main.hpp"

void BookDetails::CreateDB1()
{
    int rc = sqlite3_open("book_management.db", &db);
    const std::string createBookTable = "CREATE TABLE IF NOT EXISTS Book_Details ("
                 "id INTEGER PRIMARY KEY,"
                 "name TEXT NOT NULL,"
                 "auth TEXT,"
                 "publisher TEXT"
                 ");";

    rc = sqlite3_exec(db, createBookTable.c_str(), 0, 0, 0);
    if (rc != SQLITE_OK) {
        std::cerr<< "SQL error: "<< sqlite3_errmsg(db)<<"\n";
        return;
    }
    sqlite3_close(db);

}
void BookDetails::add()
{
    int rc = sqlite3_open("book_management.db", &db);
    std::cout<<"Enter the book ID: ";
    std::cin>>id;
    std::cout<<"Enter the book name: ";
    std::getline(std::cin,name);
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout<<"Enter the book author: ";
    std::getline(std::cin,auth);
    std::cout<<"Enter the book publisher: ";
    std::getline(std::cin,publisher);
    const std::string sql = "INSERT INTO Book_Details (id, name, auth, publisher) VALUES (?, ?, ?, ?);";
    rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
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
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return;

}
void BookDetails::del()
{
    int rc = sqlite3_open("book_management.db", &db);
    std::cout << "Please Enter the Option:\n"
              << "1) To Delete by the ID\n"
              << "2) To Delete by the Name\n"
              << "3) To Delete by the Publisher\n"
              << "4) To Delete by the Author\n";
    int option{};
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
        std::cout<<"Delete by Name"<<"\n";
        command = "DELETE FROM Book_Details WHERE name = ?;";
        rc = sqlite3_prepare_v2(db, command, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
            sqlite3_close(db);
            return;
        }
        std::cout << "Enter the name to delete: ";
        std::getline(std::cin,name);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
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
    case 3:
        std::cout<<"Delete by Publisher"<<" \n";
        command = "DELETE FROM Book_Details WHERE publisher = ?;";
        rc = sqlite3_prepare_v2(db, command, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
            sqlite3_close(db);
            return;
        }
        std::cout << "Enter the publisher details to delete: "<<" \n";
        std::getline(std::cin,publisher);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        sqlite3_bind_text(stmt,1,publisher.c_str(),-1,SQLITE_STATIC);
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
        std::cout<<"Delete by Author"<<" \n";
        command = "DELETE FROM Book_Details WHERE auth = ?;";
        rc = sqlite3_prepare_v2(db, command, -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
            sqlite3_close(db);
            return;
        }
        std::cout << "Enter the author to delete: "<<" \n";
        std::getline(std::cin,auth);
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        sqlite3_bind_text(stmt,1,auth.c_str(),-1,SQLITE_STATIC);
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
        command = "DELETE FROM Book_Details WHERE rowid = (SELECT min(rowid) FROM Book_Details LIMIT 1);";
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
void BookDetails::display()
{
    int rc = sqlite3_open("book_management.db", &db);
    const char* command  = "SELECT * FROM Book_Details;";
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
void BookDetails::getbyId()
{
    int rc = sqlite3_open("book_management.db", &db);
    const char* command  = "SELECT * FROM Book_Details WHERE id = ?;";
    rc = sqlite3_prepare_v2(db, command, -1, &stmt, 0);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << "test33"<< std::endl;
        sqlite3_close(db);
        return;
    }
    std::cout<<"Please enter the ID : "<<std::endl;
    std::cin>>id;
    sqlite3_bind_int(stmt,1,id);
    
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
void BookDetails::getbyName()
{
    int rc = sqlite3_open("book_management.db", &db);
    const char* command  = "SELECT * FROM Book_Details WHERE name = ?;";
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
