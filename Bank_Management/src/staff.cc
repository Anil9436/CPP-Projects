#include "Bank-main.hpp"

void staff::Welcome()
{
    std::cout<<"============"<<" Welcome To Bank "<<"========"<<std::endl;
    std::cout<<"===="<<" Please Create an account to enjoy benefits "<<"======="<<std::endl;
}
int staff::login()
{
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
    std::cin>>eUsername;;
    std::string query = "SELECT hashedPassword FROM STAFF_TABLE WHERE eUsername  = ?";

    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

    sqlite3_bind_text(stmt, 1, eUsername.c_str(), -1, SQLITE_STATIC);

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
        }
    } else {
        std::cerr << "Username not found." << std::endl;
    }

    // Clean up
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}
void staff::showCaccoutDetails(customer& obj){
    int rc = sqlite3_open("bank_management.db", &db);
    std::cout<<"Please enter the customer name: ";
    std::cin>>obj.CustomerName;
    std::string command  = "SELECT * FROM CUSTOMER_TABLE WHERE CustomerName = ? ;";
    
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
void staff::manageCDetails(customer& obj){
    
} 
void staff::debitORcredit(customer& obj){
    if(0 != obj.login() )
    {
        return;
    }
    std::string query;
    std::cout<<"Please choose 1 for credit and 2 for debit:\n"<<
                "1: FOR CREDIT \n"<<
                "2: FOR DEBIT \n";
    int option;
    int rc = sqlite3_open("bank_management.db", &db);
    std::cin>>option;
    switch (option)
    {
    case 1:
        std::cout<< "How much you want to credit:  "<<std::endl;
        double credit;
        std::cin>>credit;
        query = "SELECT balance FROM CUSTOMER_TABLE WHERE CustomerName = '" + obj.CustomerName + "'";
        rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
        if (rc != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
        }
        rc = sqlite3_step(stmt);
        if(rc == SQLITE_ROW)
        {
            double n = sqlite3_column_double(stmt, 0);
            double res = n + credit ; 
            std::string resStr = std::to_string(res);
            query = "UPDATE CUSTOMER_TABLE SET balance = '" + resStr + "' WHERE CustomerName = '" + obj.CustomerName + "'";
            rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
            if (rc != SQLITE_OK) {
            std::cerr << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
            }
            rc = sqlite3_step(stmt);
           std::cout<<"The balance in the account is " << res <<std::endl;
        }
        break;
    case 2:
         std::cout<< "How much you want to DEBIT:  "<<std::endl;
        double in;
        std::cin>>in;
        query = "SELECT balance FROM CUSTOMER_TABLE WHERE CustomerName = '" + obj.CustomerName + "'";
        rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
        if (rc != SQLITE_OK) {
        std::cerr << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return;
        }
        rc = sqlite3_step(stmt);
        if(rc == SQLITE_ROW)
        {
            double n = sqlite3_column_double(stmt, 0);
            double res = n - in ; 
            std::string resStr = std::to_string(res);
            query = "UPDATE CUSTOMER_TABLE SET balance = '" + resStr + "' WHERE CustomerName = '" + obj.CustomerName + "'";
            rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
            if (rc != SQLITE_OK) {
            std::cerr << sqlite3_errmsg(db) << std::endl;
            sqlite3_close(db);
            return;
            }
            rc = sqlite3_step(stmt);
           std::cout<<"The balance in the account is " << res <<std::endl;
        }
        break;
    default:
        break;
    }
    
}
void staff::createaccounttocustomer(customer& obj){
    int rc = sqlite3_open("bank_management.db", &db);
    const char* CreateEmployeeTable = "CREATE TABLE IF NOT EXISTS CUSTOMER_TABLE ("
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
    std::cout<<obj.hashedPassword<<std::endl;
    const std::string query = "INSERT INTO CUSTOMER_TABLE (customerID, CustomerName, hashed_password, phonenumber, account_number, balance, address) VALUES (?, ?, ?, ?, ?, ?, ?);";
    rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << sqlite3_errmsg(db) <<"\n";
        sqlite3_close(db);
        return;
    }
    sqlite3_bind_int(stmt,1,obj.customerID);
    sqlite3_bind_text(stmt,2,obj.CustomerName.c_str(),-1,SQLITE_STATIC);
    sqlite3_bind_text(stmt,3,obj.hashedPassword.c_str(),-1,SQLITE_STATIC);
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
void staff::removecustomeraccount(customer& obj){
    std::cout<<"Please enter the Customer name you want to remove: ";
    std::cin>>obj.CustomerName;
    int rc = sqlite3_open("bank_management.db", &db);
    const char* query = "DELETE FROM CUSTOMER_TABLE WHERE CustomerName = ? ;";
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
void staff::support(){
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    // Generate a random number between 1 and 10
    int random_number = std::rand() % 10 + 1;

    // Print the random number
    std::cout << "Please reach out to the cabin number: " << random_number << std::endl;
}
void staff::logout(){
    if(loginStatus)
    {
        loginStatus  = false;
        return;
    }
    return;
}