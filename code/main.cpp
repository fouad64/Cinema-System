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
    string name, email, password;
    cout << "Enter your email: ";
    cin >> email;

    cout << "Enter your password: ";
    cin >> password;

    cout << "Enter your name: ";
    cin >> name;

    const char* sql = "INSERT INTO users(name, email, password, role) VALUES(?, ?, ?, ?)";

    sqlite3_stmt* stmt;

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        cout << "Prepare failed: " << sqlite3_errmsg(db) << endl;
        return 0;
    }

    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, password.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, "customer", -1, SQLITE_TRANSIENT);

    if (sqlite3_step(stmt) != SQLITE_DONE)
    {
        cout << "Insert failed: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return 0;
    }

    sqlite3_finalize(stmt);
    return 1;
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
