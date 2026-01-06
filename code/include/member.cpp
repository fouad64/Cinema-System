#include "member.hpp"
#include "database.hpp"
#include <iostream>
#include <string>

Database* member::db = nullptr;

member::member() {
    if (db == nullptr) {
        db = new Database("cinema.db");
    }
}

bool member::validateEmail(const string& email) {
    if (email.find('@') == string::npos) {
        cout << "Invalid email format! Email must contain @" << endl;
        return false;
    }

    size_t atPos = email.find('@');
    if (email.find('.', atPos) == string::npos) {
        cout << "Invalid email format! Email must have a domain (e.g., @gmail.com)" << endl;
        return false;
    }

    if (email.length() < 5) {
        cout << "Email too short!" << endl;
        return false;
    }

    return true;
}

bool member::validatePassword(const string& password) {
    if (password.length() < 8) {
        cout << "Password must be at least 8 characters long!" << endl;
        return false;
    }

    bool hasDigit = false;
    for (char c : password) {
        if (isdigit(c)) {
            hasDigit = true;
            break;
        }
    }

    if (!hasDigit) {
        cout << "Password must contain at least one number!" << endl;
        return false;
    }

    return true;
}

bool member::login() {
    string email, password;
    
    cout << "=== Login ===" << endl;
    cout << "Enter email: ";
    cin >> email;
    
    cout << "Enter password: ";
    cin >> password;
    
    string role;
    int userId;
    
    if (db->validateLogin(email, password, role, userId)) {
        cout << "Login successful! Welcome back." << endl;
        personalAcc.email = email;
        personalAcc.password = password;
        
        if (role == "ADMIN") {
            personalAcc.level = privilege::ADMIN;
        } else if (role == "EMPLOYEE") {
            personalAcc.level = privilege::EMPLOYEE;
        } else {
            personalAcc.level = privilege::CUSTOMER;
        }
        
        return true;
    } else {
        cout << "Invalid email or password!" << endl;
        return false;
    }
}

void member::recoverPassword() {
    string email;
    
    cout << "=== Password Recovery ===" << endl;
    cout << "Enter your email: ";
    cin >> email;
    
    if (!db->emailExists(email)) {
        cout << "Email not found in our system." << endl;
        return;
    }
    
    cout << "Email found! In a real system, we would send a recovery link." << endl;

}