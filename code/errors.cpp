#include "errors.hpp"

using namespace std;


Empty::Empty () {

}

void Empty::show_massage () {
    cout << "EMPTY" << endl;
}


Not_Found::Not_Found () {

}

void Not_Found::show_massage () {
    cout << "Not Found" << endl;
}


Bad_Request::Bad_Request () {

}

void Bad_Request::show_massage () {
    cout << "Bad Request" << endl;
}


Permission_Denied::Permission_Denied () {

}

void Permission_Denied::show_massage () {
    cout << "Permission Denied" << endl;
}