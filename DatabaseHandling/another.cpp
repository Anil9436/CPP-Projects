// #include<iostream>
// #include<sqlite3.h>

// static int callback(void *data, int argc, char **argv, char **azColName) {
//     for (int i = 0; i < argc; i++) {
//         std::cout << azColName[i] << ": " << (argv[i] ? argv[i] : "NULL") <<std::endl;
//     }
//     return 0;
// }

// void login()
// {

//     sqlite3* db;
//     sqlite3_stmt* stmt;

//     int rc = sqlite3_open("../Book_Management/build/book_management.db", &db);  // Replace with your SQLite database file

//     if (rc) {
//         std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
//         sqlite3_close(db);
//         return;
//     }
//     std::string enteredSalt = entered_password + "SALT";
//         unsigned char hashValue[SHA256_DIGEST_LENGTH];
//         SHA256_CTX sha256;
//         SHA256_Init(&sha256);
//         SHA256_Update(&sha256, enteredSalt.c_str(), enteredSalt.size());
//         SHA256_Final(hashValue, &sha256);
        
//         std::string hashed_password(reinterpret_cast<char*>(hashValue), SHA256_DIGEST_LENGTH);
    
//     std::string Entered_Name;
//     std::cout<<"Please enter the user name ";
//     std::cin>>Entered_Name;
//     std::string sql = "SELECT password_hash FROM Customers WHERE username = '" + Entered_Name + "';";


//     std::string storedPassword; // Assume stored password is stored in this variable

//     if ( == storedPassword) {
//         cout << "Authentication successful" << endl;
//         return true;
//     } else {
//         cout << "Authentication failed" << endl;
//         return false;
//     }

// }



// int main()
// {
//     login();
// }


//     // rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

//     // sqlite3_bind_text(stmt,2,Entered_Name.c_str(),-1,SQLITE_STATIC);
//     // std::cout<<"Hellowrold"<<std::endl;
    
//     // /rc = sqlite3_exec(db, query.c_str(), callback, NULL, NULL); 
//     // while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
//     //     // Access and print the data from each column
//     //     int columnCount = sqlite3_column_count(stmt);
//     //     for (int i = 0; i < columnCount; i++) {
//     //         const char* columnName = sqlite3_column_name(stmt, i);
//     //         const char* columnValue = (const char*)sqlite3_column_text(stmt, i);
//     //         std::cout << columnName << ": " << columnValue << " ";
//     //     }
//     //     std::cout << std::endl;
//     // }
//     // if (rc != SQLITE_DONE) {
//     //     std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
//     // }
    
//     // std::cout<<"Hellowrold"<<std::endl;

//     // if (rc != SQLITE_DONE) {
//     //     std::cerr << "Hey SQL error: " << sqlite3_errmsg(db) << std::endl;
//     // }