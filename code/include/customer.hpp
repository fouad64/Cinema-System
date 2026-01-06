#ifndef CSUTOMER_HPP
#define CUSTOMER_HPP

#include "../sqlite3.h"
#include <iostream>
#include "../db_utils.h"
class Customer {
    sqlite3* db;
    int user_id;
public:
    Customer(sqlite3* database, int uid);
    void viewMovies();
    void reserveMovie();
};
#endif // CUSTOMER_H