#include "../include/customer.hpp"
#include <iostream>
#include <string>

void customer::signup() {
	string pass1; string pass2;
	
	personalAcc::level = CUSTOMER;

	cout << "Enter email: ";
	cin.ignore();
	cin >> personalAcc::email;
	

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