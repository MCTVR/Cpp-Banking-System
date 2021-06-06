/*
OPEN SOURCED BANKING SYSTEM WITH C++
MIT LICENSE
MADE BY MCTVR
V1.0
*/

#include "globSys/GlobSysFunc.hpp"

void menu() {
    const char *menustring = "    BANKING SYSTEM\n"
    "        WELCOME!\n"
    
    "   1. Create a New Account\n"
    "   2. Check Details of Existing Account\n"
    "   3. New Transaction\n"
    "   4. Exit\n";
    using namespace std;
    cout << menustring << endl;
    cout << "Select: ";
    int choice;
    cin >> choice;
    switch(choice) {
        case 1:
            create_new_account();
            break;
        case 2:
            deatils_of_account();
            break;
        case 3:
            new_transaction();
            break;
        case 4:
            std::cout << "********************************\nThank you for using our service.\nHave a nice day! Goodbye!\n********************************\n";
            exit(0);
            break;
    }
}

int main() {
    char *sql;
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    rc = sqlite3_open("./customer/customer.db", &db);

    if ( rc ){
        printf("ERROR! Error Code: 134GRI6S7H");
        exit(0);
    } else{
        printf("\n");
    }
    menu();
}