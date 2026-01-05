#include "../include/customer.hpp"
#include <iostream>
#include <string>

/*
customer::customer(string ID,string phoneNum) : customerId(ID) , phone(phoneNum) {
	
	reservation = nullptr;
}
*/
void customer::signup() {
	string pass1; string pass2;
	
	personalAcc.level = privilege::CUSTOMER;

	cout << "Enter email: ";
	cin.ignore();
	cin >> personalAcc.email;
	// if (emailExists(personalAcc.email)) {
//     cout << "Email already registered!" << endl;
//     return;
// }

	while ( true ) 
{
		cout << "Enter password: "; cin >> pass1;
		cout << "Re-type password: "; cin >> pass2;

		if (pass1 == pass2) {
			cout << "account created Successfuly";
			personalAcc.password = pass2;

			return;
		}
		else {
			cout << "Password doesnt match" << endl;

		}
	}


}