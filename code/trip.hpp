#ifndef TRIP_HPP
#define TRIP_HPP

#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include "location.hpp"

using namespace std;

#define WAITING 1
#define TRAVELING 2
#define FINISHED 3
#define IN_HERRY 1
#define NOT_IN_HERRY 0

class Passenger;
class Driver;


class Trip {
public:
    Trip (int input_id, Location* input_origin, Location* input_destination, Passenger* input_passenger, 
          string input_in_hurry_status);
    int get_id ();
    string get_status_massage ();
    Passenger* get_passenger ();
    Driver* get_driver ();
    Location* get_origin ();
    Location* get_destination ();
    bool is_waiting ();
    bool is_traveling ();
    void accept (Driver* input_driver);
    void finish ();
    double get_cost ();
    
private:
    void find_dist ();
    void find_cost ();

    int id;
    int status;
    double dist;
    double cost;
    int in_hurry_status;
    Passenger* passenger;
    Driver* driver;
    Location* origin;
    Location* destination;
};

#endif