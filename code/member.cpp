#include "../include/member.hpp"
#include <iostream>
#include <string>

member::member() {

}

void member::signup() {
	string pass1; string pass2;

	cout<<"Enter email: "; cin >>personalAcc::email;
	
	while true {
		cout << "Enter password: "; cin >> pass1;
		cout << "Re-type password: "; cin >> pass2;
	
		if (pass1 == pass2) {
			cout << "account created Successfuly";
			personalAcc::password = pass2;
			
			return;
		}
		else {
			cout << "Password doesnt match" << endl;
		}
	}


}