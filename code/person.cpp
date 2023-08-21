#include "person.hpp"

using namespace std;


Person::Person (string input_name) {
    name = input_name;
    status = NOT_IN_TRIP;
}

string Person::get_name () {
    return name;
}

bool Person::is_in_trip () {
    if (status == IN_TRIP) {
        return true;
    }
    else {
        return false;
    }
}

void Person::add_trip (Trip* trip) {
    trips.push_back (trip);
}

int Person::find_trip (int id) {
    int i;

    for (i = 0; i < trips.size (); i++) {
        if (id == trips[i]->get_id ()) {
            return i;
        }
    }

    return NOT_FIND;
}

void Person::cancel_person_trip (int id) {
    int trip_index = find_trip (id);

    trips.erase (trips.begin () + trip_index);
}

void Person::start_trip () {
    status = IN_TRIP;
}

void Person::finish_trip () {
    status = NOT_IN_TRIP;
}