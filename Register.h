#ifndef REGISTER_INCLUDED
#define REGISTER_INCLUDED
#include "User.h"
#include <fstream>
class Register
{
private:
    std::string userName;

public:
    bool registrate();
    std::string getUsername()const;
    void setUsername(std::string username);
};

#endif