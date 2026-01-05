#include "../include/admin.hpp"
#include <iostream>
#include <string>
using namespace std;

void admin::signup() {
	string pass1; string pass2;

	personalAcc.level = privilege::ADMIN;

	cout << "Enter email: ";
	cin.ignore();
	cin >> personalAcc.email;
	// if (emailExists(personalAcc.email)) {
//     cout << "Email already registered!" << endl;
//     return;
// }


	while (true) {
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