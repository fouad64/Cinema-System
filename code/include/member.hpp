#ifndef MEMBER_HPP
#define MEMBER_HPP

#include <iostream>
#include <frequent.hpp>

using namesapce std;

class member
{
protected:
    string name;
    account personalAcc;    

public:
    member();

    bool login();
    virtual void signup()= 0;
    void recoverPassword();
};

#endif