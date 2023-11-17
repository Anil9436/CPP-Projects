#include<iostream>
#include<string>
#include<openssl/sha.h>
#include<sqlite3.h>
#include <cstdlib>
#include <ctime>

extern sqlite3* db;
extern sqlite3_stmt* stmt;


#define HASHKEY "SALT091234"


class staff;
class customer;
class admin{
    private:
    bool loginStatus;
    std::string adminUsername{"Null"};
    int adminID;
    std::string password{};
    public:
        std::string hashedPassword{};
        void Welcome();
        void createSelfAccount();
        void login();
        void showPaccoutDetails();
        void logout();
        void showEaccoutDetails( staff& obj);
        void createaccouttoStaff(staff& obj);
        void removeStaffaccount( staff& obj);
        void showCaccoutDetails( customer& obj);
        void createaccouttocustomer( customer& obj);
        void removecustomeraccount( customer& obj);

};

class staff{
    friend class admin;
    private:
    bool loginStatus;
    std::string eUsername{"Null"};
    double employeeID;
    std::string password{""};
    public:
        std::string hashedPassword{};
        void Welcome();
        void login();
        void showCaccoutDetails(customer& );
        void manageCDetails(); 
        void debitORcredit();
        void createaccounttocustomer(customer&);
        void removecustomeraccount(customer&);
        void support();
        void logout();
        

};

class customer{
    friend class admin;
    friend class staff;
    private:
    int customerID;
    std::string CustomerName{"NULL"};
    bool loginStatus;
    protected:
    double phonenumber{0};
    std::string password{};
    double account_number{0};
    double balance{0};
    std::string address{"NULL"};
    public:
        customer(double ac_no,double bal):account_number{ac_no},balance{bal}{};
        std::string hashedPassword{};
        void Welcome();
        void login();
        void showaccoutDetails();
        void manageDetails(); //shows balance, shows address, 
        void debitorcredit();
        void logout();
};
