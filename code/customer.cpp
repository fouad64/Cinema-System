#include "include/customer.hpp"
#include "include/database.hpp"
#include <iostream>
#include <string>
#include <sstream>

customer::customer() {
    personalAcc.level = privilege::CUSTOMER;
}

void customer::signup() {
    string pass1, pass2;
    
    personalAcc.level = privilege::CUSTOMER;

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);
    
    cout << "Enter email: ";
    cin >> personalAcc.email;
    
    // Validate email
    if (!validateEmail(personalAcc.email)) {
        return;
    }
    
    // Check if email exists
    if (db->emailExists(personalAcc.email)) {
        cout << "Email already registered!" << endl;
        return;
    }
    
    cout << "Enter phone number: ";
    cin >> phone;

    while (true) {
        cout << "Enter password: "; 
        cin >> pass1;
        
        // Validate password
        if (!validatePassword(pass1)) {
            continue;
        }
        
        cout << "Re-type password: "; 
        cin >> pass2;

        if (pass1 == pass2) {
            personalAcc.password = pass2;
            
            // Save to database
            if (db->registerUser(name, personalAcc.email, personalAcc.password, "CUSTOMER")) {
                cout << "Account created successfully!" << endl;
            } else {
                cout << "Error creating account. Please try again." << endl;
            }
            
            return;
        }
        else {
            cout << "Password doesnt match" << endl;
        }
    }
}

void customer::viewAvailableMovies() {
    cout << "\n=== Available Movies ===" << endl;
    vector<movie> movies = db->getAllMovies();
    
    if (movies.empty()) {
        cout << "No movies available at the moment." << endl;
        return;
    }
    
    for (const auto& m : movies) {
        cout << "Title: " << m.movieName << endl;
        cout << "-------------------" << endl;
    }
    
    cout << "\nTo see showtimes, choose 'View Showtimes' option." << endl;
}

void customer::reserveSeats() {
    // First show available showtimes
    db->showAvailableShowtimes();
    
    int showtimeId, numTickets;
    string seats;
    
    cout << "\nEnter showtime ID: ";
    cin >> showtimeId;
    
    cout << "Enter number of tickets: ";
    cin >> numTickets;
    
    cin.ignore();
    cout << "Enter seat numbers (comma-separated, e.g., A1,A2,B5): ";
    getline(cin, seats);
    
    // Simple price calculation (would normally get from showtime)
    double ticketPrice = 10.0; // Default price
    double totalPrice = ticketPrice * numTickets;
    
    int reservationId = db->createReservation(userId, showtimeId, numTickets, seats, totalPrice);
    
    if (reservationId > 0) {
        cout << "\nReservation successful!" << endl;
        cout << "Reservation ID: " << reservationId << endl;
        cout << "Total Price: $" << totalPrice << endl;
        cout << "Seats: " << seats << endl;
    } else {
        cout << "Error making reservation. Please try again." << endl;
    }
}

void customer::cancelReservation() {
    // Show user's reservations first
    db->showUserReservations(userId);
    
    int reservationId;
    cout << "\nEnter reservation ID to cancel: ";
    cin >> reservationId;
    
    if (db->cancelReservation(reservationId)) {
        cout << "Reservation cancelled successfully!" << endl;
    } else {
        cout << "Error cancelling reservation. It may not exist or is already cancelled." << endl;
    }
}

void customer::viewMyReservations() {
    db->showUserReservations(userId);
}