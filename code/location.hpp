#ifndef LOCATION_HPP
#define LOCATION_HPP

#include <string>

using namespace std;


class Location {
public:
    Location (string input_name, double input_latidudes, double input_longitudes, int input_traffic);
    string get_name ();
    double get_latidudes ();
    double get_longitudes ();
    int get_traffic ();

private:
    string name;
    double latidudes;
    double longitudes;
    int traffic;
};

#endif