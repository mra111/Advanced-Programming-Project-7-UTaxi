#include "app.hpp"

using namespace std;


App::App (string input_file_name) {
    trip_id = 1;
    file_name = input_file_name;
}

App::~App () {
    int i;

    for (i = 0; i < passengers_list.size (); i++) {
        delete passengers_list[i];
    }

    for (i = 0; i < drivers_list.size (); i++) {
        delete drivers_list[i];
    }

    for (i = 0; i < trips_list.size (); i++) {
        delete trips_list[i];
    }

    for (i = 0; i < locations_list.size (); i++) {
        delete locations_list[i];
    }
}

int App::find_passenger (string name) {
    int i;

    for (i = 0; i < passengers_list.size (); i++) {
        if (name == passengers_list[i]->get_name ()) {
            return i;
        }
    }

    return NOT_FIND;
}

int App::find_driver (string name) {
    int i;

    for (i = 0; i < drivers_list.size (); i++) {
        if (name == drivers_list[i]->get_name ()) {
            return i;
        }
    }

    return NOT_FIND;
}

int App::find_word (string word, vector<string> words_list) {
    int i;

    for (i = 0; i < words_list.size (); i++) {
        if (word == words_list[i]) {
            return i;
        }
    }

    return NOT_FIND;
}

int App::find_trip (int id) {
    int i;

    for (i = 0; i < trips_list.size (); i++) {
        if (id == trips_list[i]->get_id ()) {
            return i;
        }
    }

    return NOT_FIND;
}

int App::find_location (string name) {
    int i;

    for (i = 0; i < locations_list.size (); i++) {
        if (name == locations_list[i]->get_name ()) {
            return i;
        }
    }

    return NOT_FIND;
}

void App::separate_commands (string commands) {
    string word;

    commands_word.clear ();

    istringstream ss (commands);

    while (ss >> word) {
        commands_word.push_back (word);
    }    
}

void App::read_file () {
    fstream input_file (file_name);
    string line;
    string word;
    string location_name;
    double location_latitude;
    double location_longitude;
    int location_traffic;
    int i;

    getline (input_file, line);

    while (getline (input_file, line)) {
        stringstream str (line);

        getline (str, location_name, ',');

        getline (str, word, ',');
        location_latitude = stod (word);

        getline (str, word, ',');
        location_longitude = stod (word);

        getline (str, word, ',');
        location_traffic = stoi (word);

        locations_list.push_back (new Location (location_name, location_latitude, location_longitude, 
                                  location_traffic));
    }

    input_file.close ();
}

void App::sort_trips_by_id () {
    int i;
    int j;

    for (i = 0; i < trips_list.size (); i++) {
        for (j = i; j < trips_list.size (); j++) {
            if (trips_list[i]->get_id () > trips_list[j]->get_id ()) {
                swap (trips_list[i], trips_list[j]);
            }
        }
    }
}

void App::sort_trips_by_cost () {
    int i;
    int j;

    for (i = 0; i < trips_list.size (); i++) {
        for (j = i; j < trips_list.size (); j++) {
            if (trips_list[i]->get_cost () < trips_list[j]->get_cost ()) {
                swap (trips_list[i], trips_list[j]);
            }
        }
    }
}

void App::check_signup_command () {
    if (commands_word.size () != 7 || find_word ("username", commands_word) == NOT_FIND || 
        find_word ("role", commands_word) == NOT_FIND) {
        throw Bad_Request ();
    }
}

void App::check_request_command () {
    if (commands_word.size () != 11 || find_word ("username", commands_word) == NOT_FIND || 
        find_word ("origin", commands_word) == NOT_FIND || 
        find_word ("destination", commands_word) == NOT_FIND || find_word ("in_hurry", commands_word) == NOT_FIND) {
        throw Bad_Request ();
    }

    if (find_word ("yes", commands_word) == NOT_FIND && find_word ("no", commands_word) == NOT_FIND) {
        throw Bad_Request ();
    }
}

void App::check_show_trips_command () {
    if (commands_word.size () != 7 || find_word ("username", commands_word) == NOT_FIND || find_word ("sort_by_cost", commands_word) == NOT_FIND) {
        if (commands_word.size () != 7 || find_word ("username", commands_word) == NOT_FIND || 
            find_word ("id", commands_word) == NOT_FIND) {
            throw Bad_Request ();
        }
    }
}

void App::check_trips_command () {
    if (commands_word.size () != 7 || find_word ("username", commands_word) == NOT_FIND || 
        find_word ("id", commands_word) == NOT_FIND) {
        throw Bad_Request ();
    }
}

void App::sign_up (string name, string roll) {
    if (find_passenger (name) != NOT_FIND || find_driver (name) != NOT_FIND) {
        throw Bad_Request ();
    }

    if (roll == "passenger") {
        passengers_list.push_back (new Passenger (name));
    }

    else if (roll == "driver") {
        drivers_list.push_back (new Driver (name));
    }

    else {
        throw Bad_Request ();
    }
}

void App::request_trip (string username, string origin_name, string destination_name, string in_hurry) {
    int passenger_index = find_passenger (username);
    int origin_index = find_location (origin_name);
    int destination_index = find_location (destination_name);

    if (passenger_index != NOT_FIND && origin_index != NOT_FIND && 
        destination_index != NOT_FIND) {
        if (passengers_list[passenger_index]->is_in_trip () == false) {
            trips_list.push_back (new Trip (trip_id, locations_list[origin_index], 
                                            locations_list[destination_index], 
                                            passengers_list[passenger_index], in_hurry));

            passengers_list[passenger_index]->add_trip (trips_list[trips_list.size () - 1]);
            passengers_list[passenger_index]->start_trip ();

            cout << trip_id << endl;

            trip_id = trip_id + 1;
        }
        else {
            throw Bad_Request ();
        }
    }

    else if (find_driver (username) != NOT_FIND) {
        throw Permission_Denied ();
    }

    else {
        throw Not_Found ();
    }

}

void App::show_trips (string name) {
    int i;

    if (find_driver (name) != NOT_FIND) {
        if (trips_list.size () > 0) {
            for (i = 0; i < trips_list.size (); i++) {
                cout << trips_list[i]->get_id () << " " << trips_list[i]->get_passenger ()->get_name () << 
                        " " << trips_list[i]->get_origin ()->get_name () << " " << 
                        trips_list[i]->get_destination ()->get_name () << " ";
                printf ("%.2f ", trips_list[i]->get_cost ());
                cout << trips_list[i]->get_status_massage () << endl;
            }
        }
        else {
            throw Empty ();
        }
    }
    else {
        throw Permission_Denied ();
    }
}

void App::show_trip_information (int id, string name) {
    int trip_index = find_trip (id);

    if (find_driver (name) == NOT_FIND) {
        if (find_passenger (name) != NOT_FIND) {
            throw Permission_Denied ();
        }
        else {
            throw Not_Found ();
        }
    }

    if (trip_index == NOT_FIND) {
        throw Not_Found ();
    }

    cout << trips_list[trip_index]->get_id () << " " << trips_list[trip_index]->get_passenger ()->get_name () << 
            " " << trips_list[trip_index]->get_origin ()->get_name () << " " << 
            trips_list[trip_index]->get_destination ()->get_name () << " ";
    printf ("%.2f ", trips_list[trip_index]->get_cost ());
    cout << trips_list[trip_index]->get_status_massage () << endl;
}

void App::cancel_trip (int id, string name) {
    int passenger_index = find_passenger (name);
    int trip_index = find_trip (id);

    if (passengers_list[passenger_index]->find_trip (id) == NOT_FIND) {
        if (find_trip (id) != NOT_FIND) {
            throw Permission_Denied ();
        }
        else {
            throw Not_Found ();
        }
    }

    if (trips_list[trip_index]->is_waiting () == false) {
        throw Bad_Request ();
    }

    passengers_list[passenger_index]->cancel_person_trip (id);
    passengers_list[passenger_index]->finish_trip ();

    trips_list.erase (trips_list.begin () + trip_index);

    cout << "OK" << endl;
}

void App::accept_trip (int id, string name) {
    int driver_index = find_driver (name);
    int trip_index = find_trip (id);

    if (driver_index == NOT_FIND) {
        if (find_passenger (name) != NOT_FIND) {
            throw Permission_Denied ();
        }
        else {
            throw Not_Found ();
        }
    }

    if (trip_index == NOT_FIND) {
        throw Not_Found ();
    }

    if (drivers_list[driver_index]->is_in_trip () == true || trips_list[trip_index]->is_waiting () == false) {
        throw Bad_Request ();
    }

    trips_list[trip_index]->accept (drivers_list[driver_index]);
    drivers_list[driver_index]->add_trip (trips_list[trip_index]);
    drivers_list[driver_index]->start_trip ();

    cout << "OK" << endl;
}

void App::finish_trip (int id, string name) {
    int driver_index = find_driver (name);
    int trip_index = find_trip (id);
    int passenger_index;

    if (driver_index == NOT_FIND) {
        if (find_passenger (name) != NOT_FIND) {
            throw Permission_Denied ();
        }
        else {
            throw Not_Found ();
        }
    }

    if (trip_index == NOT_FIND) {
        throw Not_Found ();
    }

    if (drivers_list[driver_index]->find_trip (id) == NOT_FIND) {
        throw Not_Found ();
    }

    passenger_index = find_passenger (trips_list[trip_index]->get_passenger ()->get_name ());

    trips_list[trip_index]->finish ();
    passengers_list[passenger_index]->finish_trip ();
    drivers_list[driver_index]->finish_trip ();

    cout << "OK" << endl;
}

double App::find_cost (string username, string origin_name, string destination_name, string in_hurry) {
    int passenger_index = find_passenger (username);
    int origin_index = find_location (origin_name);
    int destination_index = find_location (destination_name);

    if (passenger_index != NOT_FIND && origin_index != NOT_FIND && destination_index != NOT_FIND) {

        Trip trip (0, locations_list[origin_index], locations_list[destination_index], 
                   passengers_list[passenger_index], in_hurry);

        return trip.get_cost ();
    }

    else if (find_driver (username) != NOT_FIND) {
        throw Permission_Denied ();
    }

    else {
        throw Not_Found ();
    }
}

void App::show_cost (string username, string origin_name, string destination_name, string in_hurry) {
    double cost;

    cost = find_cost (username, origin_name, destination_name, in_hurry);

    printf ("%2f", cost);
}

bool App::is_person_in_trip (string username) {
    int person_index;
    
    person_index = find_passenger (username);

    if (person_index != NOT_FIND) {
        if (passengers_list[person_index]->is_in_trip () == true) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        person_index = find_driver (username);

        if (person_index != NOT_FIND) {
            if (drivers_list[person_index]->is_in_trip () == true) {
                return true;
            }
            else {
                return false;
            }
        }
        else {
            throw Not_Found ();
        }
    }
}

void App::post_signup_command () {
    string name;
    string role;

    check_signup_command ();

    name = commands_word[find_word ("username", commands_word) + 1];
    role = commands_word[find_word ("role", commands_word) + 1];
    
    sign_up (name, role);
}

void App::post_trips_command () {
    string in_herry;
    string name;
    string origin;
    string destination;

    check_request_command ();

    name = commands_word[find_word ("username", commands_word) + 1];
    origin = commands_word[find_word ("origin", commands_word) + 1];
    destination = commands_word[find_word ("destination", commands_word) + 1];
    in_herry = commands_word[find_word ("in_hurry", commands_word) + 1];

    request_trip (name, origin, destination, in_herry);
}

void App::get_trips_command () {
    string name;
    int id;

    check_show_trips_command ();
    name = commands_word[find_word ("username", commands_word) + 1];

    if (find_word ("sort_by_cost", commands_word) != NOT_FIND) {
        if (commands_word[find_word ("sort_by_cost", commands_word) + 1] == "yes") {
            sort_trips_by_cost ();
        }
        else {
            sort_trips_by_id ();
        }

        show_trips (name);
    }

    else {
        id = stoi (commands_word[find_word ("id", commands_word) + 1]);

        show_trip_information (id, name);
    }
}

void App::delete_trips_command () {
    string name;
    int id;

    check_trips_command ();
    name = commands_word[find_word ("username", commands_word) + 1];
    id = stoi (commands_word[find_word ("id", commands_word) + 1]);

    cancel_trip (id, name);
}

void App::post_accept_command () {
    string name;
    int id;

    check_trips_command ();

    name = commands_word[find_word ("username", commands_word) + 1];
    id = stoi (commands_word[find_word ("id", commands_word) + 1]);

    accept_trip (id, name);
}

void App::post_finish_command () {
    string name;
    int id;

    check_trips_command ();

    name = commands_word[find_word ("username", commands_word) + 1];
    id = stoi (commands_word[find_word ("id", commands_word) + 1]);

    finish_trip (id, name);
}

void App::get_cost_command () {
    string in_hurry;
    string name;
    string origin;
    string destination;

    check_request_command ();

    name = commands_word[find_word ("username", commands_word) + 1];
    origin = commands_word[find_word ("origin", commands_word) + 1];
    destination = commands_word[find_word ("destination", commands_word) + 1];
    in_hurry = commands_word[find_word ("in_hurry", commands_word) + 1];

    show_cost (name, origin, destination, in_hurry);
}

vector<Trip*> App::get_trips () {
    return trips_list;
}

void App::run () {
    string commands;
    
    read_file ();

    while (getline (cin, commands)) {
        separate_commands (commands);

        try {

            if (commands_word.size () < 3) {
                throw Bad_Request ();
            }


            if (commands_word[0] == "POST" && commands_word[1] == "signup") {
                post_signup_command ();
            }

            else if (commands_word[0] == "POST" && commands_word[1] == "trips") {
                post_trips_command ();
            }

            else if (commands_word[0] == "GET" && commands_word[1] == "trips") {
                get_trips_command ();
            }

            else if (commands_word[0] == "DELETE" && commands_word[1] == "trips") {
                delete_trips_command ();
            }

            else if (commands_word[0] == "POST" && commands_word[1] == "accept") {
                post_accept_command ();
            }

            else if (commands_word[0] == "POST" && commands_word[1] == "finish") {
                post_finish_command ();
            }

            else if (commands_word[0] == "GET" && commands_word[1] == "cost") {
                get_cost_command ();
            }

            else {
                if (commands_word[0] == "POST" || commands_word[0] == "GET" || commands_word[0] == "DELETE") {
                    throw Not_Found ();
                }
                else {
                    throw Bad_Request ();
                }
            }

        }

        catch (Empty error) {
            error.show_massage ();
        }

        catch (Not_Found error) {
            error.show_massage ();
        }

        catch (Bad_Request error) {
            error.show_massage ();
        }

        catch (Permission_Denied error) {
            error.show_massage ();
        }
    }
}