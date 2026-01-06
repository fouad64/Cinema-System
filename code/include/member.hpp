#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <iostream>
#include "frequent.hpp"

using namespace std;

class Database; 

class member
{
protected:
    string name;
    account personalAcc;
    int userId; 
    static Database* db;

public:
    member();

    bool login();
    virtual void signup() = 0;
    
    bool validateEmail(const std::string& email);
    bool validatePassword(const std::string& password);

    void recoverPassword();
    
 
    int getUserId() const { return userId; }
    string getEmail() const { return personalAcc.email; }
};

#endif