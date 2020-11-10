#include "User.h"

User::User() : username(""), password(""), fullName(""), born(0, 0, 2020), typeMusic({})
{
}
User::User(const User &other)
    : username(other.username), password(other.password), fullName(other.fullName), born(other.born), typeMusic(other.typeMusic)
{
}
User::~User()
{
}
void User::copy(const User &other)
{
    setUsername(other.username);
    setPassword(other.password);
    setFullName(other.fullName);
    setBornDate(other.born);
    setTypeMusic(other.typeMusic);
}
User &User::operator=(const User &other)
{
    if (this != &other)
    {
        copy(other);
    }
    return *this;
}
std::string User::getUsername() const { return this->username; }
std::string User::getPassword() const { return this->password; }
std::string User::getFullName() const { return this->fullName; }
Date User::getBornDate() const { return this->born; }
std::vector<std::string> User::getTypesOfMusic() const { return this->typeMusic; }

void User::setUsername(const std::string &_data)
{
    this->username = _data;
}
void User::setPassword(const std::string &_data)
{
    this->password = _data;
}
void User::setFullName(const std::string &_data)
{
    this->fullName = _data;
}
void User::setBornDate(const Date &_data)
{
    this->born = _data;
}
void User::setTypeMusic(const std::vector<std::string> &_data)
{
    this->typeMusic = _data;
}