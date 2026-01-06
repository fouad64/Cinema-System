#include <iostream>
#include "include/admin.hpp"
#include "include/customer.hpp"
#include "include/database.hpp"

using namespace std;

void adminMenu(admin& adm) {
    int choice;
    
    while (true) {
        cout << "\n=== Admin Menu ===" << endl;
        cout << "1. Add Movie" << endl;
        cout << "2. View All Movies" << endl;
        cout << "3. Update Movie" << endl;
        cout << "4. Delete Movie" << endl;
        cout << "5. Add Showtime" << endl;
        cout << "6. View Statistics" << endl;
        cout << "7. Logout" << endl;
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1:
                adm.addMovie();
                break;
            case 2:
                adm.readMovie();
                break;
            case 3:
                adm.updateMovie();
                break;
            case 4:
                adm.deleteMovie();
                break;
            case 5:
                adm.addShowtime();
                break;
            case 6:
                adm.showStatistics();
                break;
            case 7:
                return;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

void customerMenu(customer& cust) {
    int choice;
    
    while (true) {
        cout << "\n=== Customer Menu ===" << endl;
        cout << "1. View Available Movies" << endl;
        cout << "2. View Showtimes" << endl;
        cout << "3. Reserve Seats" << endl;
        cout << "4. View My Reservations" << endl;
        cout << "5. Cancel Reservation" << endl;
        cout << "6. Logout" << endl;
        cout << "Choice: ";
        cin >> choice;
        
        Database db;
        
        switch(choice) {
            case 1:
                cust.viewAvailableMovies();
                break;
            case 2:
                db.showAvailableShowtimes();
                break;
            case 3:
                cust.reserveSeats();
                break;
            case 4:
                cust.viewMyReservations();
                break;
            case 5:
                cust.cancelReservation();
                break;
            case 6:
                return;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
}

int main() {
    int choice;
    
    cout << "=== Cinema Management System ===" << endl;
    
    while (true) {
        cout << "\n1. Admin Signup" << endl;
        cout << "2. Admin Login" << endl;
        cout << "3. Customer Signup" << endl;
        cout << "4. Customer Login" << endl;
        cout << "5. Exit" << endl;
        cout << "Choice: ";
        cin >> choice;
        
        switch(choice) {
            case 1: {
                admin adm;
                adm.signup();
                break;
            }
            case 2: {
                admin adm;
                if (adm.login()) {
                    adminMenu(adm);
                }
                break;
            }
            case 3: {
                customer cust;
                cust.signup();
                break;
            }
            case 4: {
                customer cust;
                if (cust.login()) {
                    customerMenu(cust);
                }
                break;
            }
            case 5:
                cout << "Thank you for using Cinema Management System!" << endl;
                return 0;
            default:
                cout << "Invalid choice!" << endl;
        }
    }
    
    return 0;
}