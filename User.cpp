#include "User.h"

User::User()
{
}
User::User(const std::string &_username, const std::string &_password, const std::string &_fullName, const Date &_born, const std::vector<std::string> &_genres, const std::vector<Playlist> &_playlists)
    : username(_username), password(_password), fullName(_fullName), born(_born), genres(_genres), playlists(_playlists)
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
    setPlaylist(other.playlists);
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
std::vector<std::string> User::getGenres() const
{
    return this->genres;
}
std::vector<Playlist> User::getPlaylists() const
{
    return this->playlists;
}
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
void User::setPlaylist(const std::vector<Playlist> &_playlists)
{
    this->playlists = _playlists;
}
void User::addTypesOfMusic(const std::string &type)
{
    this->genres.push_back(type);
}
std::ostream &operator<<(std::ostream &out, const User &user)
{
    out << "Username->" << user.username << ";Password->" << user.password << ";FullName->" << user.fullName << ";Born->" << user.born << ";Genres->";
    for (auto &&element : user.genres)
    {
        out << element << ",";
    }
    out << ";Playlists->";
    // for (auto &&element : user.playlists)
    // {
    //     out<<element<<",";
    // }
    for (size_t i = 0; i < user.playlists.size() - 1; i++)
    {
        out << user.playlists[i] << ",";
    }
    out << user.playlists[user.playlists.size() - 1] << ";";
    out << "!\n";
    return out;
}