#include "location.hpp"

using namespace std;


Location::Location (string input_name, double input_latidudes, double input_longitudes, int input_traffic) {
    name = input_name;
    latidudes = input_latidudes;
    longitudes = input_longitudes;
    traffic = input_traffic;
}

string Location::get_name () {
    return name;
}

double Location::get_latidudes () {
    return latidudes;
}

double Location::get_longitudes () {
    return longitudes;
}

int Location::get_traffic () {
    return traffic;
}