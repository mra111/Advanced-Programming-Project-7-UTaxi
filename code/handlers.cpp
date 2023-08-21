#include "handlers.hpp"

using namespace std;

Signup_Handler::Signup_Handler (App *input_app) {
    app = input_app;
}

Response *Signup_Handler::callback (Request *req) {
    string username = req->getBodyParam ("username");
    string role = req->getBodyParam ("role");
    
    Response* res;
    
    try {
        app->sign_up (username, role);
        cout << "username: " << username << "role: " << role << endl;

        res = Response::redirect ("/ok_page");
    }
    catch (Bad_Request) {
        res = Response::redirect ("/bad_request");
    }
    

    return res;
}

Request_Trip_Handler::Request_Trip_Handler (App *input_app) {
    app = input_app;
}

Response *Request_Trip_Handler::callback (Request *req) {
    string username = req->getBodyParam ("username");
    string origin = req->getBodyParam ("origin");
    string destination = req->getBodyParam ("destination");
    string in_hurry = req->getBodyParam ("in_hurry");
    string body;
    vector<Trip*> trips_list;

    Response* res;
    
    try {
        res = new Response;

        app->request_trip (username, origin, destination, in_hurry);
        trips_list = app->get_trips ();

        res->setHeader ("Content-Type", "text/html");

        body = "<!DOCTYPE html>";
        body += "<html>";
        body += "<head>";
        body += "<title>UTAXI</title>";
        body += "<link rel=\"stylesheet\" href=\"style.css\">";
        body += "</head>";
        body += "<body>";
        body += "<h1>UTAXI</h1>";
        body += "<p class=\"ok_massage\">ok</p>";
        body += "<br />";
        body += "<p>Trip ID: " + to_string (trips_list[trips_list.size () - 1]->get_id ()) + "</p>";
        body += "<br />";
        body += "<br />";
        body += "<br />";
        body += "<br />";
        body += "<a class=\"home_button\" href = \"/\">home</a>";
        body += "</body>";
        body += "</html>";

        res->setBody (body);
    }
    catch (Bad_Request) {
        res = Response::redirect ("/bad_request");
    }
    catch (Permission_Denied) {
        res = Response::redirect ("/permission_denied");
    }
    catch (Not_Found) {
        res = Response::redirect ("/not_found");
    }

    return res;
}

Find_Cost_Handler::Find_Cost_Handler (App *input_app) {
    app = input_app;
}

Response *Find_Cost_Handler::callback (Request *req) {
    string username = req->getBodyParam ("username");
    string origin = req->getBodyParam ("origin");
    string destination = req->getBodyParam ("destination");
    string in_hurry = req->getBodyParam ("in_hurry");
    string body;
    double cost;

    Response *res;

    try {
        res = new Response;

        cost = app->find_cost (username, origin, destination, in_hurry);

        res->setHeader ("Content-Type", "text/html");

        body = "<!DOCTYPE html>";
        body += "<html>";
        body += "<head>";
        body += "<title>UTAXI</title>";
        body += "<link rel=\"stylesheet\" href=\"style.css\">";
        body += "</head>";
        body += "<body>";
        body += "<h1>UTAXI</h1>";
        body += "<h2>Trips Cost</h2>";
        body += "<p>Cost: " + to_string (cost) + "</p>";
        body += "<br />";
        body += "<a class=\"back_button\" href = \"/request_trip\">back</a>";
        body += "<br />";
        body += "<br />";
        body += "<br />";
        body += "<a class=\"home_button\" href = \"/\">home</a>";
        body += "</body>";
        body += "</html>";

        res->setBody (body);
    }
    catch (Permission_Denied) {
        res = Response::redirect ("/permission_denied");
    }
    catch (Not_Found) {
        res = Response::redirect ("/not_found");
    }

    return res;
}

Cancel_Trip_Handler::Cancel_Trip_Handler (App *input_app) {
    app = input_app;
}

Response *Cancel_Trip_Handler::callback (Request *req) {
    string username = req->getBodyParam ("username");
    int trip_id = stoi (req->getBodyParam ("tripid"));

    Response* res;

    try {
        app->cancel_trip (trip_id, username);
        res = Response::redirect ("/ok_page");
    }
    catch (Bad_Request) {
        res = Response::redirect ("/bad_request");
    }
    catch (Permission_Denied) {
        res = Response::redirect ("/permission_denied");
    }
    catch (Not_Found) {
        res = Response::redirect ("/not_found");
    }

    return res;
}

Show_Trips_Handler::Show_Trips_Handler (App *input_app) {
    app = input_app;
}

Response *Show_Trips_Handler::callback (Request *req) {
    string username = req->getBodyParam ("username");
    string sort = req->getBodyParam ("sort");
    string body;
    vector<Trip*> trips_list = app->get_trips ();
    int i;

    Response *res;

    try {
        res = new Response;

        if (app->find_driver (username) == NOT_FIND) {
            if (app->find_passenger (username) != NOT_FIND) {
                throw Permission_Denied ();
            }
            else {
                throw Not_Found ();
            }
        }

        if (sort == "id") {
            app->sort_trips_by_id ();
        }
        else {
            app->sort_trips_by_cost ();
        }


        res->setHeader ("Content-Type", "text/html");

        body = "<!DOCTYPE html>";
        body += "<html>";
        body += "<head>";
        body += "<title>UTAXI</title>";
        body += "<link rel=\"stylesheet\" href=\"style.css\">";
        body += "</head>";
        body += "<body>";
        body += "<h1>UTAXI</h1>";
        body += "<h2>Trips List</h2>";
    
        if (trips_list.size () == 0) {
            body += "<p class=\"empty\">EMPTY</p>";
        }
        else {
            body += "<table>";
            body += "<tr>";
            body += "<th>ID</th>";
            body += "<th>Passenger</th>";
            body += "<th>Origin</th>";
            body += "<th>Destination</th>";
            body += "<th>Cost</th>";
            body += "<th>Status</th>";
            body += "<th> </th>";
            body += "</tr>";
        }

        for (i = 0; i < trips_list.size (); i++) {
            body += "<tr>";
            body += "<td>" + to_string (trips_list[i]->get_id ()) + "</td>";
            body += "<td>" + trips_list[i]->get_passenger ()->get_name () + "</td>";
            body += "<td>" + trips_list[i]->get_origin ()->get_name () + "</td>";
            body += "<td>" + trips_list[i]->get_destination ()->get_name () + "</td>";
            body += "<td>" + to_string (trips_list[i]->get_cost ()) + "</td>";
            body += "<td>" + trips_list[i]->get_status_massage () + "</td>";
            if (trips_list[i]->is_waiting () == true && app->is_person_in_trip (username) == false) {
                body += "<td><a class=\"option_button\" type=\"submit\" href=\"/accept_trip?username=" + 
                        username + "&tripid=" + to_string (trips_list[i]->get_id ()) + "\">Accept</a>";
            }
            else if (trips_list[i]->is_traveling () == true && trips_list[i]->get_driver ()->get_name () == username) {
                body += "<td><a class=\"option_button\" type=\"submit\" href=\"/finish_trip?username=" + 
                        username + "&tripid=" + to_string (trips_list[i]->get_id ()) + "\">Finish</a>";
            }
            else {
                body += "<td> </td>";
            }
            body += "</tr>";
        }
    
        if (trips_list.size () != 0) {
            body += "</table>";
        }

        body += "<br />";
        body += "<a class=\"home_button\" href = \"/\">home</a>";
        body += "</body>";
        body += "</html>";

        res->setBody (body);
    }
    catch (Permission_Denied) {
        res = Response::redirect ("/permission_denied");
    }
    catch (Not_Found) {
        res = Response::redirect ("/not_found");
    }

    return res;
}

Accept_Trip_Handler::Accept_Trip_Handler (App *input_app) {
    app = input_app;
}

Response *Accept_Trip_Handler::callback (Request *req) {
    string username = req->getBodyParam ("username");
    int id = stoi (req->getBodyParam ("tripid"));

    cout << username << " " << id << endl;

    Response* res;

    try {
        app->accept_trip (id, username);
        res = Response::redirect ("/ok_page");
    }
    catch (Bad_Request) {
        res = Response::redirect ("/bad_request");
    }
    catch (Permission_Denied) {
        res = Response::redirect ("/permission_denied");
    }
    catch (Not_Found) {
        res = Response::redirect ("/not_found");
    }

    return res;
}

Accept_Trip_Info_Handler::Accept_Trip_Info_Handler (App *input_app) {
    app = input_app;
}

Response *Accept_Trip_Info_Handler::callback (Request *req) {
    string username = req->getQueryParam ("username");
    int id = stoi (req->getQueryParam ("tripid"));
    string body;

    Response *res = new Response;

    res->setHeader ("Content-Type", "text/html");

    body = "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<title>UTAXI</title>";
    body += "<link rel=\"stylesheet\" href=\"style.css\">";
    body += "</head>";
    body += "<body>";
    body += "<h1>UTAXI</h1>";
    body += "<h2>Accept Trip</h2>";
    body += "<form action=\"accept_trip\", method=\"post\">";
    body += "<input name=\"username\" value=\"" + username + "\" readonly />";
    body += "<input name=\"tripid\" value=\"" + to_string (id) + "\" readonly />";
    body += "<br />";
    body += "<button type=\"submit\">Accept</button>";
    body += "</form>";
    body += "</body>";
    body += "</html>";

    res->setBody (body);

    return res;
}

Finish_Trip_Handler::Finish_Trip_Handler (App *input_app) {
    app = input_app;
}

Response *Finish_Trip_Handler::callback (Request *req) {
    string username = req->getBodyParam ("username");
    int id = stoi (req->getBodyParam ("tripid"));

    Response* res;

    try {
        app->finish_trip (id, username);
        res = Response::redirect ("/ok_page");
    }
    catch (Bad_Request) {
        res = Response::redirect ("/bad_request");
    }
    catch (Permission_Denied) {
        res = Response::redirect ("/permission_denied");
    }
    catch (Not_Found) {
        res = Response::redirect ("/not_found");
    }

    return res;
}

Finish_Trip_Info_Handler::Finish_Trip_Info_Handler (App *input_app) {
    app = input_app;
}

Response *Finish_Trip_Info_Handler::callback (Request *req) {
    string username = req->getQueryParam ("username");
    int id = stoi (req->getQueryParam ("tripid"));
    string body;

    Response *res = new Response;

    res->setHeader ("Content-Type", "text/html");

    body = "<!DOCTYPE html>";
    body += "<html>";
    body += "<head>";
    body += "<title>UTAXI</title>";
    body += "<link rel=\"stylesheet\" href=\"style.css\">";
    body += "</head>";
    body += "<body>";
    body += "<h1>UTAXI</h1>";
    body += "<h2>Finish Trip</h2>";
    body += "<form action=\"finish_trip\", method=\"post\">";
    body += "<input name=\"username\" value=\"" + username + "\" readonly />";
    body += "<input name=\"tripid\" value=\"" + to_string (id) + "\" readonly />";
    body += "<br />";
    body += "<button type=\"submit\">Finish</button>";
    body += "</form>";
    body += "</body>";
    body += "</html>";

    res->setBody (body);

    return res;
}