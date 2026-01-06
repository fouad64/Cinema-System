#ifndef CUSTOMER_HPP
#define CUSTOMER_HPP

#include <string>
#include "member.hpp"

class customer: public member
{
private:
    string customerId;
    string phone;

public:
    customer();
    void signup() override;
    void reserveSeats();
    void viewAvailableMovies();
    void cancelReservation();
    void viewMyReservations();
};

#endif