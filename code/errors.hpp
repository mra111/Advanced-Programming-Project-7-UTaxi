#ifndef ERRORS_HPP
#define ERRORS_HPP

#include <iostream>
#include <string>

using namespace std;


class Empty {
public:
    Empty ();
    void show_massage ();
};

class Not_Found {
public:
    Not_Found ();
    void show_massage ();
};

class Bad_Request {
public:
    Bad_Request ();
    void show_massage ();
};

class Permission_Denied {
public:
    Permission_Denied ();
    void show_massage ();
};


#endif