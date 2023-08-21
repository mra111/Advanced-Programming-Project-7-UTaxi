#ifndef MY_SERVER_HPP
#define MY_SERVER_HPP

#include "../server/server.hpp"

using namespace std;

class My_Server : public Server {
public:
    My_Server (int port);
};

#endif