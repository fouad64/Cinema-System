#ifndef FREQUENT_HPP
#define FREQUENT_HPP

#include <string>

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

enum class seatingTier
{
    PREMIUM, REGULAR, VIP
};

struct account
{
    std::string email;
    std::string password;
    privilege level;
};

struct movie
{
    string movieName;
    genre movieGenre;
    rating movieRating;
    string cinemasAvailableAt;
};

struct reservation
{
    string reservationID;
    string* seats;
    string movieTitle;
    string showTime;
    string status;
};

#endif