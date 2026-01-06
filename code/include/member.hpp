#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <iostream>
#include "sqlite3.h"
#include "db_utils.h"

using namespace std;

class member
{
protected:
    int u_id;
    string role;    

public:
    member();

    bool login(sqlite3* db, string& role);
    bool signup(sqlite3* db);

    void recoverPassword();
};

#endif