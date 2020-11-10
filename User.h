#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include "Date.h"

class User
{
private:
    std::string username;
    std::string password;
    std::string fullName;
    Date born;
    std::vector<std::string> typeMusic;

public:
    User();
    User(const std::string &, const std::string &, const std::string &, const Date &, const std::vector<std::string> &);
    User(const User &);
    User &operator=(const User &);

    std::string getUsername()const;
    std::string getPassword()const;
    std::string getFullName()const;
    Date getBornDate()const;
    std::vector<std::string> getTypesOfMusic()const;
};

#endif