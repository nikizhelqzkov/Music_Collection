#include "User.h"

User::User()
{
}
User::User(const std::string &_username, const std::string &_password, const std::string &_fullName, const Date &_born, const std::vector<std::string> &_genres) 
: username(_username), password(_password), fullName(_fullName), born(_born), genres(_genres)
{
}
User::User(const User &other)
    : username(other.username), password(other.password), fullName(other.fullName), born(other.born), genres(other.genres)
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
    setGenres(other.genres);
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
std::vector<std::string> User::getTypesOfMusic() const { return this->genres; }

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
void User::setGenres(const std::vector<std::string> &_data)
{
    this->genres = _data;
}
void User::addTypesOfMusic(const std::string& type){
    this->genres.push_back(type);
}