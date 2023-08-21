#ifndef HANDLERS_HPP
#define HANDLERS_HPP

using namespace std;

#include <iostream>
#include "../server/server.hpp"
#include "app.hpp"


class Signup_Handler : public RequestHandler {
public:
    Signup_Handler (App *input_app);
    Response *callback (Request *);
private:
    App *app;
};

class Request_Trip_Handler : public RequestHandler {
public:
    Request_Trip_Handler (App *input_app);
    Response *callback (Request *);
private:
    App *app;
};

class Find_Cost_Handler : public RequestHandler {
public:
    Find_Cost_Handler (App *input_app);
    Response *callback (Request *);
private:
    App *app;
};

class Cancel_Trip_Handler : public RequestHandler {
public:
    Cancel_Trip_Handler (App *input_app);
    Response *callback (Request *);
private:
    App *app;
};

class Show_Trips_Handler : public RequestHandler {
public:
    Show_Trips_Handler (App *input_app);
    Response *callback (Request *);
private:
    App *app;
};

class Accept_Trip_Handler : public RequestHandler {
public:
    Accept_Trip_Handler (App *input_app);
    Response *callback (Request *);
private:
    App *app;
};

class Accept_Trip_Info_Handler : public RequestHandler {
public:
    Accept_Trip_Info_Handler (App *input_app);
    Response *callback (Request *);
private:
    App *app;
};

class Finish_Trip_Handler : public RequestHandler {
public:
    Finish_Trip_Handler (App *input_app);
    Response *callback (Request *);
private:
    App *app;
};

class Finish_Trip_Info_Handler : public RequestHandler {
public:
    Finish_Trip_Info_Handler (App *input_app);
    Response *callback (Request *);
private:
    App *app;
};

#endif