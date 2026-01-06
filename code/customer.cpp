#include "./include/customer.hpp"

Customer::Customer(sqlite3* database, int uid) : db(database), user_id(uid) {}

void Customer::viewMovies()
{

    const char* sql = "SELECT movie_id, title, genre, rating, description FROM movies;";
    sqlite3_stmt* stmt;
    if(sqlite3_prepare_v2(db, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "Failed to parse SQL Query";
        return;
    }

    std::cout << "\nAvailable Movies are\n";
    while (sqlite3_step(stmt) == SQLITE3_ROW)
    {
        std::cout   << "ID: " << sqlite3_column_int(stmt, 0)
                    << ", Title: " << sqlite3_column_text(stmt, 1)
                    << ", Genre: " << sqlite3_column_text(stmt, 2)
                    << ", Rating: " << sqlite3_column_double(stmt, 3)
                    << ", Desc: " << sqlite3_column_text(stmt, 4) << std::endl;
    }
    sqlite3_finalize(stmt);
}


void Customer::reserveMovie() {
    int movie_id, num_tickets;
    std::cout << "Enter Movie ID to make a reservation: ";
    std::cin >> movie_id;
    std::cout << "Number of tickets: ";
    std::cin >> num_tickets;

    std::string sql = "INSERT INTO reservations (customer_id, showtime_id, num_tickets) "
                      "VALUES (" + std::to_string(user_id) + "," +
                      std::to_string(movie_id) + "," +
                      std::to_string(num_tickets) + ");";
    if (executeSQL(db, sql))
        std::cout << "Reservation made successfully!\n";
}
