#include <iostream>
#include <sqlite3.h>
#include <string>
#include <cstring>
#include <openssl/sha.h>

class BankAccount{
    private: 
    sqlite3* db;
    sqlite3_stmt* stmt;

    public:
    void createAccount()
    {
        int rc = sqlite3_open("your_database.db", &db);  // Replace with your SQLite database file

        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }

        const char* CreateEmployeeTable = "CREATE TABLE IF NOT EXISTS Customers ("
                    "userid INTEGER,"
                    "username TEXT NOT NULL,"
                    "password_hash TEXT NOT NULL"
                    ");";

        rc = sqlite3_exec(db, CreateEmployeeTable, 0, 0, 0);
        if (rc != SQLITE_OK) {
            std::cerr<< "SQL error: "<< sqlite3_errmsg(db)<<"\n";
            sqlite3_close(db);
            return;
        }
        int id{0};
        std::string Entered_Name, entered_password;
        std::cout<<"Please enter the user ID ";
        std::cin>>id;
        std::cout<<"Please enter the user name ";
        std::cin>>Entered_Name;
        std::cout<<"Please enter the user password ";
        std::cin>>entered_password;
        
        std::string enteredSalt = entered_password + "SALT";
        unsigned char hashValue[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, enteredSalt.c_str(), enteredSalt.size());
        SHA256_Final(hashValue, &sha256);
        
        std::string hashed_password(reinterpret_cast<char*>(hashValue), SHA256_DIGEST_LENGTH);


        const std::string sql = "INSERT INTO Customers(userid, username , password_hash) VALUES (?, ?, ?);";
        rc = sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, 0);
        if (rc != SQLITE_OK) {
            std::cerr << "SQL error test2: " << sqlite3_errmsg(db) <<"\n";
            sqlite3_close(db);
            return;
        }

        sqlite3_bind_int(stmt,1,id);
        sqlite3_bind_text(stmt,2,Entered_Name.c_str(),-1,SQLITE_STATIC);
        sqlite3_bind_text(stmt,3,hashed_password.c_str(),-1,SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_DONE) {
            std::cout << "Value added to the table successfully." << std::endl;
        } else {
            std::cerr << "SQL error test: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
        }
        sqlite3_finalize(stmt);
        sqlite3_close(db);

    }

    void login()
    {

        int rc = sqlite3_open("your_database.db", &db);  // Replace with your SQLite database file

        if (rc) {
            std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }
        std::string Entered_Name;
        std::cout<<"Please enter the user name ";
        std::cin>>Entered_Name;
        std::string query = "SELECT * FROM Customers WHERE username = ?";
        
        rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

        sqlite3_bind_text(stmt,2,Entered_Name.c_str(),-1,SQLITE_STATIC);
        std::cout<<"Hellowrold"<<std::endl;

        if(rc != SQLITE_OK)
        {
            std::cerr  << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
        }
        std::cout<<"Hellowrold"<<std::endl;

        // while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        // // Access and print the data from each column

        // for (int i = 0; i < columnCount; i++) {
        //     const char* columnName = sqlite3_column_name(stmt, i);
        //     const char* columnValue = (const char*)sqlite3_column_text(stmt, i);
        //     std::cout << columnName << ": " << columnValue << " ";
        // }
        // std::cout << std::endl;
    // }
        // rc = sqlite3_exec(db,query.c_str(),0,0,0);
        if ((rc = sqlite3_step(stmt))==  SQLITE_ROW) {
            const char* columnValue = "";
            int columnCount = sqlite3_column_count(stmt);
            for (int i = 0; i < columnCount; i++) {
            columnValue = (const char*)sqlite3_column_text(stmt,1);
            }
            std::cout<<columnValue<<std::endl;
            std::cout<<"Please enter the password ";
            std::string enterPassword;
            std::cin>>enterPassword;
            std::string salted_password = enterPassword + "SALT"; // You should use a proper salt
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256_CTX sha256;
            SHA256_Init(&sha256);
            SHA256_Update(&sha256, salted_password.c_str(), salted_password.size());
            SHA256_Final(hash, &sha256);

            std::string hashed_password(reinterpret_cast<const char*>(hash), SHA256_DIGEST_LENGTH);
            
            std::cout<<hashed_password<<std::endl;
            if ( columnValue  == hashed_password) {
                std::cout << "Login successful" << std::endl;
            } else {
                std::cout << "Login failed" << std::endl;
            }

        sqlite3_finalize(stmt);
        sqlite3_close(db);
        }
         else{
            std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
            sqlite3_finalize(stmt);
            sqlite3_close(db);
            return;
         }
    }
};
int main() {


    // sqlite3* db;
    // int rc = sqlite3_open("your_database.db", &db);  // Replace with your SQLite database file

    // if (rc) {
    //     std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    //     sqlite3_close(db);
    //     return rc;
    // }


    // // Replace these with the user's input
    // std::string entered_username = "anil";
    // std::string entered_password = "anilkumar";
    // // std::cout<<"Please enter the password "<<std::endl;
    // // std::string entered_password;
    // // std::cin>>entered_password;

    // std::string enteredSalt = entered_password + "SALT";
    // unsigned char previoushash[SHA256_DIGEST_LENGTH];
    // SHA256_CTX sha256;
    // SHA256_Init(&sha256);
    // SHA256_Update(&sha256, enteredSalt.c_str(), enteredSalt.size());
    // SHA256_Final(previoushash, &sha256);
    
    // std::string previous_hashed_password(reinterpret_cast<char*>(previoushash), SHA256_DIGEST_LENGTH);
    // // Construct the SQL query to retrieve user data
    // std::string query = "SELECT username, password_hash FROM users WHERE username = '" + entered_username + "';";
    
    // sqlite3_stmt* stmt;
    // rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

    // if (rc != SQLITE_OK) {
    //     std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    //     sqlite3_close(db);
    //     return rc;
    // }

    // // // Retrieve and compare passwords
    // if (sqlite3_step(stmt) == SQLITE_ROW) {
    //     std::string stored_password_hash = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));

    //     std::cout<<"Please enter the password ";
    //     std::string enterPassword;
    //     std::cin>>enterPassword;
    //     // Hash the entered password
    //     std::string salted_password = enterPassword + "SALT"; // You should use a proper salt
    //     unsigned char hash[SHA256_DIGEST_LENGTH];
    //     // SHA256_CTX sha256;
    //     SHA256_Init(&sha256);
    //     SHA256_Update(&sha256, salted_password.c_str(), salted_password.size());
    //     SHA256_Final(hash, &sha256);

    //     std::string hashed_password(reinterpret_cast<char*>(hash), SHA256_DIGEST_LENGTH);

    //     if (previous_hashed_password == hashed_password) {
    //         std::cout << "Login successful" << std::endl;
    //     } else {
    //         std::cout << "Login failed" << std::endl;
    //     }
    // // } else {
    // //     std::cout << "User not found" << std::endl;
    // // }

    // // // Clean up
    // // sqlite3_finalize(stmt);
    // // sqlite3_close(db);

    // createAccount();
    BankAccount one;
    // one.createAccount();
    one.login();

    // return 0;
}
