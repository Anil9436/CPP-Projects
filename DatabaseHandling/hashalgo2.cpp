#include<iostream>
#include<sqlite3.h>
#include<openssl/sha.h>
#include<string>


int main()
{
    sqlite3* db;
    sqlite3_stmt* stmt;
    int rc = sqlite3_open("your_database.db", &db);  
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }
    std::string Entered_Name;
    std::cout<<"Please enter the user name ";
    std::cin>>Entered_Name;
    std::string query = "SELECT password_hash FROM Dummy WHERE username = ?";


    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

    sqlite3_bind_text(stmt, 1, Entered_Name.c_str(), -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }

    // Execute the query and get the hashed password from the result
    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        const char* hashedPasswordFromDB = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        std::cout<<hashedPasswordFromDB<<std::endl;
        // Now you can compare the hashed password with the entered password
        std::string enteredPassword;
        std::cout << "Enter your password: ";
        std::cin >> enteredPassword;

        // Hash the entered password using your hashing method
        std::string enteredSalt = enteredPassword + "SALT";
        unsigned char hashValue[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, enteredSalt.c_str(), enteredSalt.size());
        SHA256_Final(hashValue, &sha256);

        std::string hashedEnteredPassword(reinterpret_cast<char*>(hashValue), SHA256_DIGEST_LENGTH);

        // Compare the hashed passwords
        if (hashedEnteredPassword == hashedPasswordFromDB) {
            std::cout << "Password is correct." << std::endl;
        } else {
            std::cout << "Password is incorrect." << std::endl;
        }
    } else {
        std::cerr << "Username not found." << std::endl;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);

    
}
