#include "include/admin.hpp"
#include "include/database.hpp"
#include <iostream>
#include <string>
using namespace std;

admin::admin() {
    personalAcc.level = privilege::ADMIN;
}

void admin::signup() {
    string pass1, pass2;

    personalAcc.level = privilege::ADMIN;

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
            if (db->registerUser(name, personalAcc.email, personalAcc.password, "ADMIN")) {
                cout << "Admin account created successfully!" << endl;
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

void admin::addMovie() {
    string title, description;
    int genreChoice, ratingChoice;
    
    cout << "\n=== Add New Movie ===" << endl;
    
    cin.ignore();
    cout << "Enter movie title: ";
    getline(cin, title);
    
    cout << "\nSelect genre:" << endl;
    cout << "1. ACTION\n2. DRAMA\n3. COMEDY\n4. HORROR\n5. ROMANCE\n6. THRILLER\n7. ANIMATION\n8. SCIFI" << endl;
    cout << "Choice: ";
    cin >> genreChoice;
    
    string genre;
    switch(genreChoice) {
        case 1: genre = "ACTION"; break;
        case 2: genre = "DRAMA"; break;
        case 3: genre = "COMEDY"; break;
        case 4: genre = "HORROR"; break;
        case 5: genre = "ROMANCE"; break;
        case 6: genre = "THRILLER"; break;
        case 7: genre = "ANIMATION"; break;
        case 8: genre = "SCIFI"; break;
        default: genre = "DRAMA";
    }
    
    cout << "\nSelect rating:" << endl;
    cout << "1. G\n2. PG\n3. PG13\n4. R\n5. NC17" << endl;
    cout << "Choice: ";
    cin >> ratingChoice;
    
    string rating;
    switch(ratingChoice) {
        case 1: rating = "G"; break;
        case 2: rating = "PG"; break;
        case 3: rating = "PG13"; break;
        case 4: rating = "R"; break;
        case 5: rating = "NC17"; break;
        default: rating = "PG";
    }
    
    cin.ignore();
    cout << "Enter description: ";
    getline(cin, description);
    
    if (db->addMovie(title, genre, rating, description)) {
        cout << "Movie added successfully!" << endl;
    } else {
        cout << "Error adding movie." << endl;
    }
}

void admin::readMovie() {
    cout << "\n=== All Movies ===" << endl;
    vector<movie> movies = db->getAllMovies();
    
    if (movies.empty()) {
        cout << "No movies in the system." << endl;
        return;
    }
    
    for (const auto& m : movies) {
        cout << "Title: " << m.movieName << endl;
        cout << "-------------------" << endl;
    }
}

void admin::updateMovie() {
    int movieId;
    string title, description;
    int genreChoice, ratingChoice;
    
    cout << "\n=== Update Movie ===" << endl;
    cout << "Enter movie ID to update: ";
    cin >> movieId;
    
    cin.ignore();
    cout << "Enter new title: ";
    getline(cin, title);
    
    cout << "\nSelect genre:" << endl;
    cout << "1. ACTION\n2. DRAMA\n3. COMEDY\n4. HORROR\n5. ROMANCE\n6. THRILLER\n7. ANIMATION\n8. SCIFI" << endl;
    cout << "Choice: ";
    cin >> genreChoice;
    
    string genre;
    switch(genreChoice) {
        case 1: genre = "ACTION"; break;
        case 2: genre = "DRAMA"; break;
        case 3: genre = "COMEDY"; break;
        case 4: genre = "HORROR"; break;
        case 5: genre = "ROMANCE"; break;
        case 6: genre = "THRILLER"; break;
        case 7: genre = "ANIMATION"; break;
        case 8: genre = "SCIFI"; break;
        default: genre = "DRAMA";
    }
    
    cout << "\nSelect rating:" << endl;
    cout << "1. G\n2. PG\n3. PG13\n4. R\n5. NC17" << endl;
    cout << "Choice: ";
    cin >> ratingChoice;
    
    string rating;
    switch(ratingChoice) {
        case 1: rating = "G"; break;
        case 2: rating = "PG"; break;
        case 3: rating = "PG13"; break;
        case 4: rating = "R"; break;
        case 5: rating = "NC17"; break;
        default: rating = "PG";
    }
    
    cin.ignore();
    cout << "Enter new description: ";
    getline(cin, description);
    
    if (db->updateMovie(movieId, title, genre, rating, description)) {
        cout << "Movie updated successfully!" << endl;
    } else {
        cout << "Error updating movie." << endl;
    }
}

void admin::deleteMovie() {
    int movieId;
    
    cout << "\n=== Delete Movie ===" << endl;
    cout << "Enter movie ID to delete: ";
    cin >> movieId;
    
    if (db->deleteMovie(movieId)) {
        cout << "Movie deleted successfully!" << endl;
    } else {
        cout << "Error deleting movie." << endl;
    }
}

void admin::addShowtime() {
    int movieId, screenNum;
    string datetime;
    double price;
    
    cout << "\n=== Add Showtime ===" << endl;
    cout << "Enter movie ID: ";
    cin >> movieId;
    
    cout << "Enter screen number (1-5): ";
    cin >> screenNum;
    
    cin.ignore();
    cout << "Enter date and time (YYYY-MM-DD HH:MM): ";
    getline(cin, datetime);
    
    cout << "Enter ticket price: $";
    cin >> price;
    
    if (db->addShowtime(movieId, datetime, screenNum, price)) {
        cout << "Showtime added successfully!" << endl;
    } else {
        cout << "Error adding showtime." << endl;
    }
}

void admin::showStatistics() {
    cout << "\n=== Cinema Statistics ===" << endl;
    cout << "Total Revenue: $" << db->getTotalRevenue() << endl;
    cout << "Total Tickets Sold: " << db->getTotalTicketsSold() << endl;
}