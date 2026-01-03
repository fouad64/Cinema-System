#include <iostream>
#include <cinema.hpp>

using namespace std;

class company 
{
private:

    string headQuarters;
    double totalRevenue;
    int totalTicketsSold;
    int totalCustomers;
    cinema* cinemas;
    employee* employees;

public:

    company();
    void generateAnnualReport();
};