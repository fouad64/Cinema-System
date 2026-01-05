#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <iostream>
#include <frequent.hpp>

using namespace std;

class screen
{
private:
    string screeningTech;
    seatingTier Tier;
    double ticketPrice;
    int capacity;
    int currentOccupancy;

public:
    screen();

    double getOccupancyPercentage();
    void updateOccupancy();
};

#endif