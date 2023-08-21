#ifndef PASSENGER_HPP
#define PASSENGER_HPP

#include "person.hpp"

using namespace std;


class Passenger : public Person {
public:
    Passenger (string input_name);  
};

#endif