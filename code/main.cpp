#include <string>
#include "app.hpp"
#include "handlers.hpp"
#include "my_server.hpp"

#define PORT 5000

using namespace std;


int main (int argc, char *argv[]) {
    string file = argv[1];
    App app (file);
    My_Server server (PORT);

    app.read_file ();
    
    try {
        server.get ("/style.css", new ShowPage ("static/style.css"));
        server.get ("/taxi.png", new ShowImage ("static/taxi.png"));
        
        server.get ("/signup", new ShowPage ("static/signup.html"));
        server.post ("/signup", new Signup_Handler (&app));

        server.get ("/request_trip", new ShowPage ("static/request_trip.html"));
        server.post ("/request_trip", new Request_Trip_Handler (&app));

        server.post ("/trip_cost", new Find_Cost_Handler (&app));

        server.get ("/cancel_trip", new ShowPage ("static/cancel_trip.html"));
        server.post ("/cancel_trip", new Cancel_Trip_Handler (&app));

        server.get ("/show_trips", new ShowPage ("static/show_trips.html"));
        server.post ("/show_trips", new Show_Trips_Handler (&app));

        server.get ("/accept_trip", new Accept_Trip_Info_Handler (&app));
        server.post ("/accept_trip", new Accept_Trip_Handler (&app));

        server.get ("/finish_trip", new Finish_Trip_Info_Handler (&app));
        server.post ("/finish_trip", new Finish_Trip_Handler (&app));

        server.get ("/ok_page", new ShowPage ("static/ok_page.html"));

        server.setNotFoundErrPage ("static/not_found.html");

        server.get ("/", new ShowPage ("static/home.html"));
        server.get ("/bad_request", new ShowPage ("static/bad_request.html"));
        server.get ("/not_found", new ShowPage ("static/not_found.html"));
        server.get ("/permission_denied", new ShowPage ("static/permission_denied.html"));
        
        server.run ();
    }
    catch (...) { 
        cout << "error" << endl;
    }
    
    return 0;
}