#include<iostream>
#include<string>

SHA256_CTX sha256;

class admin{
    private:
    std::string adminUsername{"Null"};
    double adminID;
    protected:
    std::string password{};
    public:
        void login();
        void showPaccoutDetails();
        void showEaccoutDetails();
        void showCaccoutDetails();
        void createaccouttoStaff();
        void createaccouttocustomer();
        void removeStaffaccount();
        void removecustomeraccount();
        void logout();
        friend class staff;
        friend class customer;
};

class staff{
    private:
    std::string username{"Null"};
    double employeeID;
    protected:
    std::string password{""};
    public:
        void login();
        void showCaccoutDetails();
        void manageCDetails(); 
        void debitorcredit();
        void createaccouttocustomer();
        void removecustomeraccount();
        void support();
        void logout();
        friend class customer;

};

class customer{
    private:
    std::string username{"NULL"};
    bool login;
    protected:
    double phonenumber{0};
    std::string password{};
    double account_number{0};
    double balance{0};
    std::string address{"NULL"};
    public:
        void login();
        void showaccoutDetails();
        void manageDetails(); //shows balance, shows address, 
        void debitorcredit();
        void logout();

};
