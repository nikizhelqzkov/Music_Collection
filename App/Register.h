#ifndef REGISTER_INCLUDED
#define REGISTER_INCLUDED
#include "User.h"
#include <fstream>
/**
 * @brief Класа Регистер е направен за създаване на потребител в системата и добавяне на неговите предпочитания, и добавяне във файловата система
 * 
 */
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