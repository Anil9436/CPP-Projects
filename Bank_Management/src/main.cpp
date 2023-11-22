#include "Bank-main.hpp"


int main() {
    staff sone;
    customer cone{0,0};
    admin aone;
    // aone.createSelfAccount();
    // aone.logout();
    // aone.login();
    // aone.Welcome();
    // aone.createaccouttocustomer(cone);
    // aone.createaccouttoStaff(sone);
    // sone.createaccounttocustomer(cone);
    cone.logout();
    sone.manageCDetails(cone);
    // sone.debitORcredit(cone);
    // aone.createaccouttocustomer(cone);
    
}   
