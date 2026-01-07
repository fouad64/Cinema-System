#include "include/database.hpp"
#include <iostream>
#include <sstream>

Database::Database(const string& path) : dbPath(path), db(nullptr), errorMsg(nullptr) {
    connect();
}

Database::~Database() {
    disconnect();
}

bool Database::connect() {
    int exit = sqlite3_open(dbPath.c_str(), &db);
    if (exit != SQLITE_OK) {
        cerr << "Error opening database: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    // Enable foreign key enforcement
    if (sqlite3_exec(db, "PRAGMA foreign_keys = ON;", nullptr, nullptr, &errorMsg) != SQLITE_OK) {
        cerr << "Failed to enable foreign keys: " << (errorMsg ? errorMsg : "unknown") << endl;
        if (errorMsg) {
            sqlite3_free(errorMsg);
            errorMsg = nullptr;
        }
        // Not fatal; continue with connection
    }

    return true;
}

void Database::disconnect() {
    if (db) {
        sqlite3_close(db);
        db = nullptr;
    }
}

bool Database::registerUser(const string& name, const string& email, 
                           const string& password, const string& role) {
    string sql = "INSERT INTO users (name, email, password, role) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    
    sqlite3_bind_text(stmt, 1, name.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, email.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, password.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, role.c_str(), -1, SQLITE_TRANSIENT);
    
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    
    return success;
}

bool Database::validateLogin(const string& email, const string& password, string& role, int& userId) {
    string sql = "SELECT user_id, password, role FROM users WHERE email = ?;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);
    
    bool found = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        userId = sqlite3_column_int(stmt, 0);
        string dbPassword = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        role = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        
        if (dbPassword == password) {
            found = true;
        }
    }
    
    sqlite3_finalize(stmt);
    return found;
}

bool Database::emailExists(const string& email) {
    string sql = "SELECT COUNT(*) FROM users WHERE email = ?;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    
    sqlite3_bind_text(stmt, 1, email.c_str(), -1, SQLITE_TRANSIENT);
    
    bool exists = false;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        exists = (sqlite3_column_int(stmt, 0) > 0);
    }
    
    sqlite3_finalize(stmt);
    return exists;
}

bool Database::addMovie(const string& title, const string& genre, 
                       const string& rating, const string& description) {
    string sql = "INSERT INTO movies (title, genre, rating, description) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    
    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, genre.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, rating.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, description.c_str(), -1, SQLITE_TRANSIENT);
    
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    
    return success;
}

vector<movie> Database::getAllMovies() {
    vector<movie> movies;
    string sql = "SELECT movie_id, title, genre, rating FROM movies;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return movies;
    }
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        movie m;
        m.movieName = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        
        string genreStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        string ratingStr = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        
        // Note: You'd need to convert strings to enums here
        // For simplicity, storing as strings in the struct
        
        movies.push_back(m);
    }
    
    sqlite3_finalize(stmt);
    return movies;
}

bool Database::updateMovie(int movieId, const string& title, const string& genre,
                          const string& rating, const string& description) {
    string sql = "UPDATE movies SET title = ?, genre = ?, rating = ?, description = ? WHERE movie_id = ?;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    
    sqlite3_bind_text(stmt, 1, title.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, genre.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, rating.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, description.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 5, movieId);
    
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    
    return success;
}


bool Database::deleteMovie(int movieId) {
    string checkSql = "SELECT COUNT(*) FROM showtimes WHERE movie_id = ?;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, checkSql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare check statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    
    sqlite3_bind_int(stmt, 1, movieId);
    
    int showtimeCount = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        showtimeCount = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    
    if (showtimeCount > 0) {
        cout << "Cannot delete movie: " << showtimeCount << " showtime(s) exist for this movie." << endl;
        cout << "Please delete all showtimes first, or use CASCADE delete." << endl;
        return false;
    }
    
    string sql = "DELETE FROM movies WHERE movie_id = ?;";
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare delete statement: " << sqlite3_errmsg(db) << endl;
        return false;
    }
    
    sqlite3_bind_int(stmt, 1, movieId);
    
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    
    if (!success) {
        cerr << "Failed to delete movie: " << sqlite3_errmsg(db) << endl;
    } else if (sqlite3_changes(db) == 0) {
        cout << "No movie found with ID " << movieId << endl;
        success = false;
    }
    
    sqlite3_finalize(stmt);
    return success;
}

bool Database::addShowtime(int movieId, const string& datetime, int screenNum, double price) {
    string sql = "INSERT INTO showtimes (movie_id, show_datetime, screen_number, ticket_price) VALUES (?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cerr << "Failed to prepare addShowtime: " << sqlite3_errmsg(db) << endl;
        return false;
    }

    if (sqlite3_bind_int(stmt, 1, movieId) != SQLITE_OK ||
        sqlite3_bind_text(stmt, 2, datetime.c_str(), -1, SQLITE_TRANSIENT) != SQLITE_OK ||
        sqlite3_bind_int(stmt, 3, screenNum) != SQLITE_OK ||
        sqlite3_bind_double(stmt, 4, price) != SQLITE_OK) {
        cerr << "Failed to bind addShowtime parameters: " << sqlite3_errmsg(db) << endl;
        sqlite3_finalize(stmt);
        return false;
    }

    int rc = sqlite3_step(stmt);
    bool success = (rc == SQLITE_DONE);
    if (!success) {
        cerr << "Failed to execute addShowtime: " << sqlite3_errmsg(db) << " (rc=" << rc << ")" << endl;
    }

    sqlite3_finalize(stmt);
    return success;
}

void Database::showAvailableShowtimes() {
    string sql = "SELECT s.showtime_id, m.title, s.show_datetime, s.screen_number, "
                 "s.available_seats, s.ticket_price FROM showtimes s "
                 "JOIN movies m ON s.movie_id = m.movie_id "
                 "WHERE s.available_seats > 0 ORDER BY s.show_datetime;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cout << "Error fetching showtimes" << endl;
        return;
    }
    
    cout << "\n=== Available Showtimes ===" << endl;
    cout << "ID\tMovie\t\t\tDateTime\t\tScreen\tSeats\tPrice" << endl;
    cout << "-------------------------------------------------------------------" << endl;
    
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string datetime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int screen = sqlite3_column_int(stmt, 3);
        int seats = sqlite3_column_int(stmt, 4);
        double price = sqlite3_column_double(stmt, 5);
        
        cout << id << "\t" << title << "\t\t" << datetime << "\t" 
             << screen << "\t" << seats << "\t$" << price << endl;
    }
    
    sqlite3_finalize(stmt);
}

bool Database::updateShowtimeSeats(int showtimeId, int seatsBooked) {
    string sql = "UPDATE showtimes SET available_seats = available_seats - ? WHERE showtime_id = ?;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    
    sqlite3_bind_int(stmt, 1, seatsBooked);
    sqlite3_bind_int(stmt, 2, showtimeId);
    
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    
    return success;
}

int Database::createReservation(int customerId, int showtimeId, int numTickets, 
                               const string& seatNumbers, double totalPrice) {
    string sql = "INSERT INTO reservations (customer_id, showtime_id, num_tickets, seat_numbers, total_price) "
                 "VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return -1;
    }
    
    sqlite3_bind_int(stmt, 1, customerId);
    sqlite3_bind_int(stmt, 2, showtimeId);
    sqlite3_bind_int(stmt, 3, numTickets);
    sqlite3_bind_text(stmt, 4, seatNumbers.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_double(stmt, 5, totalPrice);
    
    if (sqlite3_step(stmt) == SQLITE_DONE) {
        int reservationId = sqlite3_last_insert_rowid(db);
        sqlite3_finalize(stmt);
        
        // Update available seats
        updateShowtimeSeats(showtimeId, numTickets);
        
        return reservationId;
    }
    
    sqlite3_finalize(stmt);
    return -1;
}

void Database::showUserReservations(int customerId) {
    string sql = "SELECT r.reservation_id, m.title, s.show_datetime, r.num_tickets, "
                 "r.seat_numbers, r.total_price, r.status FROM reservations r "
                 "JOIN showtimes s ON r.showtime_id = s.showtime_id "
                 "JOIN movies m ON s.movie_id = m.movie_id "
                 "WHERE r.customer_id = ? ORDER BY s.show_datetime;";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        cout << "Error fetching reservations" << endl;
        return;
    }
    
    sqlite3_bind_int(stmt, 1, customerId);
    
    cout << "\n=== Your Reservations ===" << endl;
    cout << "ID\tMovie\t\t\tDateTime\t\tTickets\tSeats\t\tPrice\tStatus" << endl;
    cout << "---------------------------------------------------------------------------------" << endl;
    
    bool hasReservations = false;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        hasReservations = true;
        int id = sqlite3_column_int(stmt, 0);
        string title = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        string datetime = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        int tickets = sqlite3_column_int(stmt, 3);
        string seats = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        double price = sqlite3_column_double(stmt, 5);
        string status = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 6));
        
        cout << id << "\t" << title << "\t\t" << datetime << "\t" 
             << tickets << "\t" << seats << "\t$" << price << "\t" << status << endl;
    }
    
    if (!hasReservations) {
        cout << "No reservations found." << endl;
    }
    
    sqlite3_finalize(stmt);
}

bool Database::cancelReservation(int reservationId) {
    // First get the reservation details to update seats
    string getSql = "SELECT showtime_id, num_tickets FROM reservations WHERE reservation_id = ? AND status = 'active';";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, getSql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    
    sqlite3_bind_int(stmt, 1, reservationId);
    
    int showtimeId = -1;
    int numTickets = 0;
    
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        showtimeId = sqlite3_column_int(stmt, 0);
        numTickets = sqlite3_column_int(stmt, 1);
    }
    sqlite3_finalize(stmt);
    
    if (showtimeId == -1) {
        return false; // Reservation not found or already cancelled
    }
    
    // Update reservation status
    string updateSql = "UPDATE reservations SET status = 'cancelled' WHERE reservation_id = ?;";
    
    if (sqlite3_prepare_v2(db, updateSql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return false;
    }
    
    sqlite3_bind_int(stmt, 1, reservationId);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    
    if (success) {
        // Return seats to showtime
        string seatsSql = "UPDATE showtimes SET available_seats = available_seats + ? WHERE showtime_id = ?;";
        if (sqlite3_prepare_v2(db, seatsSql.c_str(), -1, &stmt, nullptr) == SQLITE_OK) {
            sqlite3_bind_int(stmt, 1, numTickets);
            sqlite3_bind_int(stmt, 2, showtimeId);
            sqlite3_step(stmt);
            sqlite3_finalize(stmt);
        }
    }
    
    return success;
}

double Database::getTotalRevenue() {
    string sql = "SELECT SUM(total_price) FROM reservations WHERE status = 'active';";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return 0.0;
    }
    
    double revenue = 0.0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        revenue = sqlite3_column_double(stmt, 0);
    }
    
    sqlite3_finalize(stmt);
    return revenue;
}

int Database::getTotalTicketsSold() {
    string sql = "SELECT SUM(num_tickets) FROM reservations WHERE status = 'active';";
    sqlite3_stmt* stmt;
    
    if (sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK) {
        return 0;
    }
    
    int tickets = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW) {
        tickets = sqlite3_column_int(stmt, 0);
    }
    
    sqlite3_finalize(stmt);
    return tickets;
}

string Database::getLastError() {
    if (db) {
        return string(sqlite3_errmsg(db));
    }
    return "Database not connected";
}