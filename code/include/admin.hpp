#ifndef ADMIN_HPP
#define ADMIN_HPP

#include "member.hpp"

class admin: public member
{
public:
    admin();
    void signup() override;
    void addMovie();
    void updateMovie();
    void deleteMovie();
    void readMovie();
    void addShowtime();
    void showStatistics();
};

#endif