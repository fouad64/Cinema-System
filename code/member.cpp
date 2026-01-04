#include "../include/member.hpp"
#include <iostream>
#include <string>

member::member() {

}

bool member::validateEmail(const string& email) {
    // Check if email contains @
    if (email.find('@') == string::npos) {
        cout << "Invalid email format! Email must contain @" << endl;
        return false;
    }

    // Check if email contains domain
    size_t atPos = email.find('@');
    if (email.find('.', atPos) == string::npos) {
        cout << "Invalid email format! Email must have a domain (e.g., @gmail.com)" << endl;
        return false;
    }

    // Check minimum length
    if (email.length() < 5) {
        cout << "Email too short!" << endl;
        return false;
    }

    return true;
}


bool member::validatePassword(const string& password) {
    // Check minimum length
    if (password.length() < 8) {
        cout << "Password must be at least 8 characters long!" << endl;
        return false;
    }

    // Check for at least one digit
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
