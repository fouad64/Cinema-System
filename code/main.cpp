#include <iostream>
#include <string>
#include "sqlite3.h"
#include "db_utils.h"
#include "./include/admin.hpp"
#include "./include/customer.hpp"
#include "./include/frequent.hpp"

using namespace std;



int reg(sqlite3* db)
{
    sqlite3_stmt* stmt;
    string query;
    string name,email,password,role;
    cout << "Enter your email: ";
    cin >> email;
    cout << "\nEnter your password: ";
    cin >> password;
    cout<< "\nName: ";
    cin >> name;
    role = 'customer';
    query = "INSERT INTO users(name,email,password,role) VALUES('" + name +"', '" + email + "', '" + password + "', 'customer')";
    if(executeSQL(db, "BEGIN TRANSACTION;"))
    if(executeSQL(db, query))
    if(executeSQL(db, "COMMIT;")) return 1;

}

int main()
{
    sqlite3* db;
    if (sqlite3_open("cinema.db", &db)) {
        cerr << "Can't open database: " << sqlite3_errmsg(db) << endl;
        return 1;
    }


    if(reg(db)) cout << "\nregistered successfully!!";


    return 0;
}
