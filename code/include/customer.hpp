#ifndef CSUTOMER_HPP
#define CUSTOMER_HPP

#include <string>
#include <member.hpp>
#include <reservation.hpp>

class customer: public member
{
private:
    
    string customerId;
    string phone;
    reservation* reservations;
public:

    customer();

    void reserveSeats();
    void viewAvailableMovies();
    void cancelReservation();

};

#endif