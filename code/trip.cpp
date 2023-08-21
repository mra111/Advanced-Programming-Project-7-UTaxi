#include "trip.hpp"

using namespace std;


Trip::Trip (int input_id, Location* input_origin, Location* input_destination, Passenger* input_passenger, 
            string input_in_hurry_status) {
    id = input_id;
    status = WAITING;
    origin = input_origin;
    destination = input_destination;
    passenger = input_passenger;
    driver = NULL;
    
    if (input_in_hurry_status == "yes") {
        in_hurry_status = IN_HERRY;
    }
    else {
        in_hurry_status = NOT_IN_HERRY;
    }

    find_dist ();
    find_cost ();
}

string Trip::get_status_massage () {
    if (status == WAITING) {
       return "waiting";
    }
    else if (status == TRAVELING) {
        return "traveling";
    }
    else {
        return "finished";
    }
}

Passenger* Trip::get_passenger () {
    return passenger;
}

Driver* Trip::get_driver () {
    return driver;
}

int Trip::get_id () {
    return id;
}

Location* Trip::get_origin () {
    return origin;
}

Location* Trip::get_destination () {
    return destination;
}

bool Trip::is_waiting () {
    if (status == WAITING) {
        return true;
    }
    else {
        return false;
    }
}

bool Trip::is_traveling () {
    if (status == TRAVELING) {
        return true;
    }
    else {
        return false;
    }
}

void Trip::accept (Driver* input_driver) {
    status = TRAVELING;
    driver = input_driver;
}

void Trip::finish () {
    status = FINISHED;
}

void Trip::find_dist () {
    dist = 110.5 * sqrt (pow (destination->get_latidudes () - origin->get_latidudes (), 2) + 
                         pow (destination->get_longitudes () - origin->get_longitudes (), 2));
}

void Trip::find_cost () {
    if (in_hurry_status == IN_HERRY) {
        cost = 1.2 * dist * (origin->get_traffic () + destination->get_traffic ()) * 10000;
    }
    else {
        cost = dist * (origin->get_traffic () + destination->get_traffic ()) * 10000;
    }
}

double Trip::get_cost () {
    return cost;
}