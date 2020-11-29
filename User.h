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
    std::vector<std::string> genres;
    void copy(const User &);
    //void erase();

public:
    User();
    User(const std::string &, const std::string &, const std::string &, const Date &, const std::vector<std::string> &);
    User(const User &);
    User &operator=(const User &);
    ~User();

    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;
    Date getBornDate() const;
    std::vector<std::string> getTypesOfMusic() const;
    void setUsername(const std::string &);
    void setPassword(const std::string &);
    void setFullName(const std::string &);
    void setBornDate(const Date &);
    void setGenres(const std::vector<std::string> &);
    void addTypesOfMusic(const std::string&);
};

#endif