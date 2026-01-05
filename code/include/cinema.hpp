#ifndef CINEMA_HPP
#define CINEMA_HPP

#include <iostream>
#include <employee.hpp>
#include <admin.hpp>
#include <screen.hpp>
//#include <movie.hpp>

using namespace std;

class cinema
{
private:
    string location;
    double cinemaRevenue;
    int ticketsSoldThisMonth;
    double averageOccupancyRate;
    employee* employees;
    admin adm;
    movie* availableMovies;
    screen* screens;

public:

    double getAverageRevenue();
    void getMnothlyReport();

};

#endif 