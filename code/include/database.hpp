#ifndef DATABASE_HPP
#define DATABASE_HPP

#include "../sqlite3.h"
#include <string>
#include <vector>
#include "frequent.hpp"

using namespace std;

class Database {
private:
    sqlite3* db;
    string dbPath;
    char* errorMsg;
    
public:
    Database(const string& path = "cinema.db");
    ~Database();
    
    bool connect();
    void disconnect();
    
    bool registerUser(const string& name, const string& email, 
                     const string& password, const string& role);
    bool validateLogin(const string& email, const string& password, string& role, int& userId);
    bool emailExists(const string& email);
    
    bool addMovie(const string& title, const string& genre, 
                  const string& rating, const string& description);
    vector<movie> getAllMovies();
    bool updateMovie(int movieId, const string& title, const string& genre,
                     const string& rating, const string& description);
    bool deleteMovie(int movieId);
    
    bool addShowtime(int movieId, const string& datetime, int screenNum, double price);
    void showAvailableShowtimes();
    bool updateShowtimeSeats(int showtimeId, int seatsBooked);
    
    int createReservation(int customerId, int showtimeId, int numTickets, 
                         const string& seatNumbers, double totalPrice);
    void showUserReservations(int customerId);
    bool cancelReservation(int reservationId);
    
    double getTotalRevenue();
    int getTotalTicketsSold();
    
    string getLastError();
};

#endif