#ifndef ADMIN_HPP
#define ADMIN_HPP

#include <member.hpp>

class admin: public member
{
private:


public:

    admin();

    void addMovie();
    void updateMovie();
    void deleteMovie();
    void readMovie();
    void addCinema();
    void removeCinema();
    void assignMovieToCinema();
    void assignEmployeeToCinema();
    void removeEmployeeFromCinema();
    void showCompanyStatistics();
}