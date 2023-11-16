#include "main.hpp"

sqlite3* db;
sqlite3_stmt* stmt;
void admin::Welcome(){
    std::cout<<"============"<<" Welcome To Bank "<<"========"<<std::endl;
    std::cout<<"===="<<" Please Create an account to enjoy benefits "<<"======="<<std::endl;
}
void admin::createSelfAccount(){
    int rc = sqlite3_open("bank_management.db", &db);
    const char* CreateEmployeeTable = "CREATE TABLE IF NOT EXISTS ADMIN_TABLE ("
                    "adminID INTEGER,"
                    "adminUsername TEXT NOT NULL,"
                    "hashedPassword TEXT NOT NULL"
                    ");";

    rc = sqlite3_exec(db, CreateEmployeeTable, 0, 0, 0);
    if (rc != SQLITE_OK) {
        std::cerr<< "SQL error: "<< sqlite3_errmsg(db)<<"\n";
        sqlite3_close(db);
        return;
    }
    std::cout<<"Please enter the AdminID: ";
    std::cin>>adminID;
    std::cout<<"Please Enter the username: ";
    std::cin>>adminUsername;
    std::cout<<"Please Enter the password: ";
    std::cin>>password;
    std::string HashedPassword = password + HASHKEY ;
    unsigned char hashValue[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, HashedPassword.c_str(), HashedPassword.size());
    SHA256_Final(hashValue, &sha256);
    std::string hashed_password(reinterpret_cast<char*>(hashValue), SHA256_DIGEST_LENGTH);
    hashedPassword = hashed_password;
    const std::string query = "INSERT INTO ADMIN_TABLE (adminID, adminUsername, hashedPassword) VALUES (?, ?, ?);";
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
        sqlite3_close(db);
        return;
    }
    sqlite3_bind_int(stmt,1,adminID);
    sqlite3_bind_text(stmt,2,adminUsername.c_str(),-1,SQLITE_STATIC);
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
void admin::login(){

    if(loginStatus)
    {
        std::cout<<"Please LogOut and try logging in "<<std::endl;
        return;
    }

    int rc = sqlite3_open("bank_management.db", &db);  
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
    }
    std::cout<<"Please enter the user name: ";
    std::cin>>adminUsername;;
    std::string query = "SELECT hashedPassword FROM ADMIN_TABLE WHERE adminUsername  = ?";

    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

    sqlite3_bind_text(stmt, 1, adminUsername.c_str(), -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
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
            std::cout<<loginStatus<<std::endl;
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
void admin::showPaccoutDetails(){
    int rc = sqlite3_open("bank_management.db", &db);
    const char* command  = "SELECT * FROM ADMIN_TABLE;";
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
void admin::showEaccoutDetails( staff& obj){
    int rc = sqlite3_open("bank_management.db", &db);
    std::cout<<"Please enter the Existing Employee name: ";
    std::cin>>obj.eUsername;
    std::string command  = "SELECT * FROM STAFF_TABLE WHERE eUsername = ? ;";
    
    rc = sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, obj.eUsername.c_str(), -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
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
void admin::showCaccoutDetails( customer& obj){
    int rc = sqlite3_open("bank_management.db", &db);
    std::cout<<"Please enter the customer name: ";
    std::cin>>obj.CustomerName;
    std::string command  = "SELECT * FROM CUSTOMER_TABLE2 WHERE CustomerName = ? ;";
    
    rc = sqlite3_prepare_v2(db, command.c_str(), -1, &stmt, 0);
    sqlite3_bind_text(stmt, 1, obj.CustomerName.c_str(), -1, SQLITE_STATIC);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
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
void admin::createaccouttoStaff(staff& obj){
    int rc = sqlite3_open("bank_management.db", &db);
    const char* CreateEmployeeTable = "CREATE TABLE IF NOT EXISTS STAFF_TABLE ("
                    "employeeID INTEGER,"
                    "eUsername TEXT NOT NULL,"
                    "hashedPassword TEXT NOT NULL"
                    ");";

    rc = sqlite3_exec(db, CreateEmployeeTable, 0, 0, 0);
    if (rc != SQLITE_OK) {
        std::cerr<< "SQL error: "<< sqlite3_errmsg(db)<<"\n";
        sqlite3_close(db);
        return;
    }
    std::cout<<"Please enter the EmployeeID: ";
    std::cin>>obj.employeeID;
    std::cout<<"Please Enter the Eusername: ";
    std::cin>>obj.eUsername;
    std::cout<<"Please Enter the password: ";
    std::cin>>obj.password;
    std::string HashedPassword = password + HASHKEY ;
    unsigned char hashValue[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, HashedPassword.c_str(), HashedPassword.size());
    SHA256_Final(hashValue, &sha256);
    std::string hashed_password(reinterpret_cast<char*>(hashValue), SHA256_DIGEST_LENGTH);
    obj.hashedPassword = hashed_password;
    const std::string query = "INSERT INTO STAFF_TABLE (employeeID, eUsername, hashedPassword) VALUES (?, ?, ?);";
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
        sqlite3_close(db);
        return;
    }
    sqlite3_bind_int(stmt,1,obj.employeeID);
    sqlite3_bind_text(stmt,2,obj.eUsername.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,3,hashed_password.c_str(),-1,SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        std::cout << "Account Created for the employee." << std::endl;
    } else {
        std::cerr << "SQL error test: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);


}
void admin::createaccouttocustomer( customer& obj){
    int rc = sqlite3_open("bank_management.db", &db);
    const char* CreateEmployeeTable = "CREATE TABLE IF NOT EXISTS CUSTOMER_TABLE2 ("
                    "customerID INTEGER,"
                    " CustomerName TEXT NOT NULL,"
                    " hashed_password TEXT NOT NULL,"
                    " phonenumber INTEGER NOT NULL,"
                    " account_number DOUBLE NOT NULL,"
                    " balance DOUBLE NOT NULL,"
                    " address TEXT NOT NULL"
                    ");";

    rc = sqlite3_exec(db, CreateEmployeeTable, 0, 0, 0);
    if (rc != SQLITE_OK) {
        std::cerr<< "SQL error: "<< sqlite3_errmsg(db)<<"\n";
        sqlite3_close(db);
        return;
    }
    std::cout<<"Please enter the customerID: ";
    std::cin>>obj.customerID;
    std::cout<<"Please Enter the username: ";
    std::cin>>obj.CustomerName;
    std::cout<<"Please Enter the password: ";
    std::cin>>obj.password;
    std::cout<<"Please Enter mobile number: ";
    std::cin>>obj.phonenumber;
    std::cout<<"Please Enter account number: ";
    std::cin>>obj.account_number;
    std::cout<<"Please Enter you address: ";
    std::cin>>obj.address;
    std::string HashedPassword = password + HASHKEY ;
    unsigned char hashValue[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, HashedPassword.c_str(), HashedPassword.size());
    SHA256_Final(hashValue, &sha256);
    std::string hashed_password(reinterpret_cast<char*>(hashValue), SHA256_DIGEST_LENGTH);
    obj.hashedPassword = hashed_password;
    const std::string query = "INSERT INTO CUSTOMER_TABLE2 (customerID, CustomerName, hashed_password, phonenumber, account_number, balance, address) VALUES (?, ?, ?, ?, ?, ?, ?);";
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
        sqlite3_close(db);
        return;
    }
    sqlite3_bind_int(stmt,1,obj.customerID);
    sqlite3_bind_text(stmt,2,obj.CustomerName.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,3,hashed_password.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_double(stmt,4,obj.phonenumber);
    sqlite3_bind_double(stmt,5,obj.account_number);
    sqlite3_bind_double(stmt,6,obj.balance);
    sqlite3_bind_text(stmt,7,obj.address.c_str(),-1,SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
        std::cout << "Account Created for the Customer" << std::endl;
    } else {
        std::cerr << "SQL error test: " << sqlite3_errmsg(db) << std::endl;
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
}
void admin::removeStaffaccount( staff& obj){
    std::cout<<"Please enter the Employee name you want to remove: ";
    std::cin>>obj.eUsername;
    int rc = sqlite3_open("bank_management.db", &db);
    const char* query = "DELETE FROM STAFF_TABLE WHERE eUsername = ? ;";
    rc = sqlite3_prepare_v2(db, query , -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
        sqlite3_close(db);
        return;
    }
    sqlite3_bind_text(stmt,1,obj.eUsername.c_str(),-1,SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
    std::cout << "Employee Deleted from the table successfully." << std::endl;
    }else {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    }
}
void admin::removecustomeraccount( customer& obj){
    std::cout<<"Please enter the Customer name you want to remove: ";
    std::cin>>obj.CustomerName;
    int rc = sqlite3_open("bank_management.db", &db);
    const char* query = "DELETE FROM CUSTOMER_TABLE2 WHERE CustomerName = ? ;";
    rc = sqlite3_prepare_v2(db, query , -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
        sqlite3_close(db);
        return;
    }
    sqlite3_bind_text(stmt,1,obj.CustomerName.c_str(),-1,SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_DONE) {
    std::cout << "Customer Deleted from the table successfully." << std::endl;
    }else {
    std::cerr << "SQL error: " << sqlite3_errmsg(db) << std::endl;
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    }
}
void admin::logout(){

    if(loginStatus)
    {
        loginStatus = false;
        return;
    }
    return;

}