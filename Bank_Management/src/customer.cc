#include "Bank-main.hpp"

void customer::Welcome(){

}
int customer::login(){
     if(loginStatus)
    {
        std::cout<<"Please LogOut and try logging in "<<std::endl;
        return -1;
    }
    int rc = sqlite3_open("bank_management.db", &db);  
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }
    std::cout<<"Please enter the user name: ";
    std::cin>>CustomerName;
    std::string query = "SELECT hashed_password FROM CUSTOMER_TABLE WHERE CustomerName = ?";

    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

    sqlite3_bind_text(stmt, 1, CustomerName.c_str(), -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return -1;
    }

    rc = sqlite3_step(stmt);

    if (rc == SQLITE_ROW) {
        const char* hashedPasswordFromDB = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        // Now you can compare the hashed password with the entered password
        std::string enteredPassword;
        std::cout << "Enter your password: ";
        std::cin >> enteredPassword;
        // Hash the entered password using your hashing method
        std::string enteredSalt = enteredPassword + HASHKEY ;
        unsigned char hashValue[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, enteredSalt.c_str(), enteredSalt.size());
        SHA256_Final(hashValue, &sha256);

        std::string hashedEnteredPassword(reinterpret_cast<char*>(hashValue), SHA256_DIGEST_LENGTH);
        // Compare the hashed passwords
        if (hashedEnteredPassword == hashedPasswordFromDB) {
            std::cout << "Login Success" << std::endl;
            loginStatus = true;
        } else {
            std::cout << "Password is incorrect." << std::endl;
            return -1;
        }
    } else {
        std::cerr << "Username not found." << std::endl;
        return -1;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}
void customer::showaccoutDetails(){}
void customer::manageDetails(){} //shows balance, shows address, 
void customer::debitorcredit(){}
void customer::logout(){
    if(loginStatus)
    {
        loginStatus = false;
        return;
    }
    return;
}