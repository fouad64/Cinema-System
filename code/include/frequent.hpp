#ifndef FREQUENT_HPP
#define FREQUENT_HPP

#include <string>

using namespace std;

enum class privilege
{
    ADMIN, EMPLOYEE, CUSTOMER
};

enum class rating
{
    G, PG, PG13, R, NC17
};

enum class genre
{
    ACTION, DRAMA, COMEDY, HORROR, ROMANCE, THRILLER, ANIMATION, SCIFI
};

struct account
{
    string email;
    string password;
    privilege level;
};

struct movie
{
    string movieName;
    genre movieGenre;
    rating movieRating;
    string description;
};

struct reservation
{
    string reservationID;
    string seats;           // Changed from string* to string (comma-separated like "A1,A2,B3")
    string movieTitle;
    string showTime;
    string status;
    int numTickets;
    double totalPrice;
};

#endif