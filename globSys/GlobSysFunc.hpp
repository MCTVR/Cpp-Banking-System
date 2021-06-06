/*
OPEN SOURCED BANKING SYSTEM WITH C++
MIT LICENSE
MADE BY MCTVR
V1.0
*/

#ifndef GLOB_FUNC
#define GLOB_FUNC

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cmath>
#include <string.h>
#include <fstream>

void new_transaction() {
    int ID;
    std::string pwd;
    std::string cardnum;

    int payee_ID;
    std::string payee_cardnum;

    std::cout << "Enter your ID: ";
    std::cin >> ID;

    std::cout << "\nEnter your Password: ";
    std::cin >> pwd;

    std::cout << "\nEnter your Card Number: ";
    std::cin >> cardnum;

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("./customer/customer.db", &db);
    if( rc ){
        printf("ERROR! Error Code: 134GRI6S7I\n");
        exit(0);
    }else{
        printf("ACCOUNT VALID\n");
    }

    /* Create SQL statement */
    std::string select_customer_data_tmp = std::string("SELECT BALANCE FROM CUSTOMER WHERE ID=" + std::to_string(ID) + std::string(" AND CARDNUM=") + std::string(cardnum) + std::string(" AND PWD='") + std::string(pwd) + "';");

    char *sql = &select_customer_data_tmp[0];

    class balance {
        public: 
            static int callbalance(void *data, int argc, char **argv, char **azColName) {
                int i;
                char *result;
                for(i=0; i<argc; i++) {
                    printf("********************\nInfo Loaded\n%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
                    std::ofstream cacheFile("./Cache/cache.dat");
                    cacheFile << argv[i];
                    cacheFile.close();
                }
                return 0;
            }
    };
    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, balance::callbalance, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        printf("error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        exit(0);
    } else{
        std::string pwd;
        double long amount_to_pay;

        std::cout << "Enter Payee's ID: ";
        std::cin >> payee_ID;

        std::cout << "Enter Payee's Card Number: ";
        std::cin >> payee_cardnum;

        std::cout << "Enter amount to pay the payee: ";
        std::cin >> amount_to_pay;

        std::ifstream infile("./Cache/cache.dat");

        std::string BALANCE;
        infile >> BALANCE;
        remove("./Cache/cache.dat");

        class payeebalance {
            public: 
                static int callpayeebalance(void *data, int argc, char **argv, char **azColName) {
                    int i;
                    char *result;
                    for(i=0; i<argc; i++) {
                        std::ofstream cacheFile("./Cache/cache.dat");
                        cacheFile << argv[i];
                        cacheFile.close();
                    }
                    return 0;
                }
        };

        std::string customer_balance_tmp = std::string("SELECT BALANCE FROM CUSTOMER WHERE ID=" + std::to_string(payee_ID) + std::string(" AND CARDNUM=") + std::string(payee_cardnum) + std::string("; "));

        char *customer_balance_sql = &customer_balance_tmp[0];

        rc = sqlite3_exec(db, customer_balance_sql, payeebalance::callpayeebalance, 0, &zErrMsg);
        if( rc != SQLITE_OK ){
            printf("error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            exit(0);
        }else{}
        sqlite3_close(db);

        if (amount_to_pay > 0 && amount_to_pay <= std::strtold(BALANCE.c_str(), NULL)) {
        } else {
            std::cout << "Invalid Amount! Please Try Again.";
            exit(0);
        }
        sqlite3 *db;
        char *zErrMsg = 0;
        int rc;
        const char* data = "Callback function called";

        /* Open database */
        rc = sqlite3_open("./customer/customer.db", &db);
        if( rc ){
            printf("ERROR! Error Code: 7Q7R7LC8MLU\n");
            exit(0);
        } else{}

        std::ifstream file("./Cache/cache.dat");
        std::string payee_BALANCE;
        file >> payee_BALANCE;
        remove("./Cache/cache.dat");
        
        long double amount_to_add = std::strtold(payee_BALANCE.c_str(), NULL) + amount_to_pay;
        long double amount_to_deduct_from_payer = std::strtold(BALANCE.c_str(), NULL) - amount_to_pay;

        //std::cout << amount_to_add << "\n";
        //std::cout << amount_to_deduct_from_payer << "\n";

        std::string deduct_balance_tmp = std::string("UPDATE CUSTOMER set BALANCE=" + std::to_string(amount_to_deduct_from_payer) + std::string(" where ID=") + std::to_string(ID) + std::string(" AND CARDNUM=") + std::string(cardnum) + std::string("; "));

        char *deduct_sql = &deduct_balance_tmp[0];

        /* Execute SQL statement */
        rc = sqlite3_exec(db, deduct_sql, NULL, 0, &zErrMsg);
        if( rc != SQLITE_OK ){
            printf("error1: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            exit(0);
        }else{}
        sqlite3_close(db);

        /* Create SQL statement */
        std::string customer_data_tmp = std::string("UPDATE CUSTOMER SET BALANCE=" + std::to_string(amount_to_add) + std::string(" WHERE ID=") + std::to_string(payee_ID) + std::string(" AND CARDNUM=") + std::string(payee_cardnum) + std::string("; "));

        //std::cout << customer_data_tmp;

        char *update_sql = &customer_data_tmp[0];

        /* Execute SQL statement */
        sqlite3_open("./customer/customer.db", &db);
        rc = sqlite3_exec(db, update_sql, NULL, 0, &zErrMsg);
        if( rc != SQLITE_OK ){
            printf("error10: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            exit(0);
        }else{
            printf("Transaction Successful\n");
        }
        sqlite3_close(db);

        rc = sqlite3_open("./customer/transactions.db", &db);
        if( rc ){
            printf("ERROR! Error Code: 7Q7R7LC8MLU\n");
            exit(0);
        } else{}

        time_t now = time(0);
        char *DATE = ctime(&now);

        long long int TRANSACTION_CERT = (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count()) / 10 + payee_ID - ID + std::strtold(payee_cardnum.c_str(), NULL) - std::strtold(cardnum.c_str(), NULL);
        std::string APPROVAL = "1";

        /* Create SQL statement */
        std::string trans_data_tmp = std::string("INSERT INTO TRANSACTIONS (DATE,TRANSACTION_CERT,PAYEE_ID,PAYEE_CARDNUM,PAYER_ID,PAYER_CARDNUM,TRANSACTION_AMOUNT,APPROVAL)\n" "VALUES (" + std::string("'") + std::string(DATE) + std::string("', ") + std::string("'") + std::to_string(TRANSACTION_CERT) + std::string("', ") + std::to_string(payee_ID) + std::string(", ") + std::string(payee_cardnum) + std::string(", ") + std::to_string(ID) + std::string(", ") + std::string(cardnum) + std::string(", ") + std::to_string(amount_to_pay) + std::string(", ") + std::string(APPROVAL) + std::string(");"));

        //std::cout << trans_data_tmp;

        char *update_trans_sql = &trans_data_tmp[0];

        /* Execute SQL statement */
        rc = sqlite3_exec(db, update_trans_sql, payeebalance::callpayeebalance, 0, &zErrMsg);
        if( rc != SQLITE_OK ){
            printf("error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
            exit(0);
        }else{
            printf("Transaction Successful\n");
        }
        sqlite3_close(db);

    }

    sqlite3_close(db);

    const char *menustring = "    BANKING SYSTEM\n"
    "        CONTINUE? \n"
    
    "   1. New Transaction\n"
    "   2. Exit\n";
    using namespace std;
    cout << menustring << endl;
    cout << "Select: ";
    int choice;
    cin >> choice;
    switch(choice) {
        case 1:
            new_transaction();
            break;
        case 2:
            std::cout << "********************************\nThank you for using our service.\nHave a nice day! Goodbye!\n********************************\n";
            exit(0);
            break;
    }
}

void create_new_account() {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    int ID;
    std::string name;
    int age;
    std::string pwd;
    long double balance = 0.0;
    
    long long int cardnum;

    long long int timestamp = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();


    srand(timestamp);
    int min = 0;
    int max = 114514;

    ID = rand() % (max - min + 1) + min;

    std::cout << "Enter your Name: ";
    std::cin >> name;

    std::cout << "\nEnter your Age (in Numbers): ";
    std::cin >> age;

    std::cout << "\nEnter your Password (Recommend: Mixed Numbers & Characters): ";
    std::cin >> pwd;

    cardnum = pow((ID % age), 2) + 10000017 + timestamp % 114514;

    std::cout << "Your ID (MARK THIS DOWN SAFELY) : " << ID << "\n" << std::endl;
    std::cout << "Your Card Number (MARK THIS DOWN SAFELY): " << cardnum << "\n" << std::endl;

    std::string customer_data_tmp = std::string("INSERT INTO CUSTOMER (ID,NAME,AGE,CARDNUM,PWD,BALANCE) \n") + std::string("VALUES (") + std::to_string(ID) + std::string(", '") + std::string(name) + std::string("', ") + std::to_string(age) + std::string(", ") + std::to_string(cardnum) + ", '" + std::string(pwd) + std::string("', ") + std::to_string(balance) + std::string("); ");

    char *sql = &customer_data_tmp[0];

   rc = sqlite3_open("./customer/customer.db", &db);
   rc = sqlite3_exec(db, sql, NULL, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      printf("error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      printf("Account Created Successfully\n");
   }
   sqlite3_close(db);

       const char *menustring = "    BANKING SYSTEM\n"
    "        CONTINUE? \n"
    
    "   1. New Transaction\n"
    "   2. Exit\n";
    using namespace std;
    cout << menustring << endl;
    cout << "Select: ";
    int choice;
    cin >> choice;
    switch(choice) {
        case 1:
            new_transaction();
            break;
        case 2:
            std::cout << "********************************\nThank you for using our service.\nHave a nice day! Goodbye!\n********************************\n";
            exit(0);
            break;
    }
}

int callback(void *data, int argc, char **argv, char **azColName) {
    int i;
    for(i=0; i<argc; i++){
        printf("%s: %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("********************\n\n");
    return 0;
}

void deatils_of_account() {

    int ID;
    std::string pwd;

    std::cout << "Enter your ID: ";
    std::cin >> ID;

    std::cout << "\nEnter your Password: ";
    std::cin >> pwd;

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    const char* data = "Callback function called";

    /* Open database */
    rc = sqlite3_open("./customer/customer.db", &db);
    if( rc ){
        printf("ERROR! Error Code: 5I2CV8TU\n");
        exit(0);
    }else{
        printf("\n********************\nInfo Loaded\n");
    }

    /* Create SQL statement */
    std::string select_customer_data_tmp = std::string("SELECT NAME, ID, CARDNUM, BALANCE FROM CUSTOMER WHERE ID=" + std::to_string(ID) + std::string(" AND PWD='") + std::string(pwd) + "';");

    char *sql = &select_customer_data_tmp[0];

    /* Execute SQL statement */
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    if( rc != SQLITE_OK ){
        printf("error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
        exit(0);
    }else{
        printf("Operation Executed Successfully\n");
    }
    sqlite3_close(db);

    const char *menustring = "    BANKING SYSTEM\n"
    "        CONTINUE? \n"
    
    "   1. Create a New Account\n"
    "   2. New Transaction\n"
    "   3. Exit\n";
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
            new_transaction();
            break;
        case 3:
            std::cout << "********************************\nThank you for using our service.\nHave a nice day! Goodbye!\n********************************\n";
            exit(0);
            break;
    }
}

#endif