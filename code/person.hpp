#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <vector>
#include "trip.hpp"

using namespace std;

#define NOT_FIND -1
#define IN_TRIP 1
#define NOT_IN_TRIP 0


class Person {
public:
    Person (string input_name);
    string get_name ();
    bool is_in_trip ();
    void add_trip (Trip* trip);
    int find_trip (int id);
    void cancel_person_trip (int id);
    void start_trip ();
    void finish_trip ();    

protected:
    string name;
    int status;
    vector<Trip*> trips; 
};

#endif