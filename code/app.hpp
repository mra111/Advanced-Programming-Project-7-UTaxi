#ifndef APP_HPP
#define APP_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "passenger.hpp"
#include "driver.hpp"
#include "trip.hpp"
#include "errors.hpp"
#include "location.hpp"

using namespace std;

#define NOT_FIND -1


class App {
public:
    App (string input_file_name);
    ~App ();
    void run ();
    void read_file ();
    void sign_up (string name, string roll);
    void request_trip (string username, string origin_name, string destination_name, string in_hurry);
    void show_trips (string name);
    void show_trip_information (int id, string name);
    void cancel_trip (int id, string name);
    void accept_trip (int id, string name);
    void finish_trip (int id, string name);
    double find_cost (string username, string origin_name, string destination_name, string in_hurry);
    void show_cost (string username, string origin_name, string destination_name, string in_hurry);
    void post_signup_command ();
    void post_trips_command ();
    void get_trips_command ();
    void delete_trips_command ();
    void post_accept_command ();
    void post_finish_command ();
    void get_cost_command ();
    int find_driver (string name);
    int find_passenger (string name);
    void sort_trips_by_id ();
    void sort_trips_by_cost ();
    bool is_person_in_trip (string username);
    vector<Trip*> get_trips ();

private:
    int find_word (string word, vector<string> words_list);
    int find_trip (int id);
    int find_location (string name);
    void separate_commands (string commands);
    void check_signup_command ();
    void check_request_command ();
    void check_show_trips_command ();
    void check_trips_command ();

    vector<Passenger*> passengers_list;
    vector<Driver*> drivers_list;
    vector<Trip*> trips_list;
    vector<Location*> locations_list;
    vector<string> commands_word;
    int trip_id;
    string file_name;
};

#endif