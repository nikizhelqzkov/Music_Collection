#ifndef USER_H
#define USER_H
#include <string>
#include <vector>
#include "Date.h"
#include "Playlist.h"
#include <fstream>
class User
{
private:
    std::string username;
    std::string password;
    std::string fullName;
    Date born;
    std::vector<std::string> genres;
    std::vector<Playlist> playlists;
    void copy(const User &);

public:
    User();
    User(const std::string &username, const std::string &password, const std::string &fullName, const Date &born, const std::vector<std::string> &genres, const std::vector<Playlist> &playlists);
    User(const User &);
    User &operator=(const User &);
    ~User();
    std::string getUsername() const;
    std::string getPassword() const;
    std::string getFullName() const;
    Date getBornDate() const;
    std::vector<std::string> getGenres() const;
    std::vector<Playlist> getPlaylists() const;
    bool getRepVote() const;
    void setUsername(const std::string &);
    void setPassword(const std::string &);
    void setFullName(const std::string &);
    void setBornDate(const Date &);
    void setGenres(const std::vector<std::string> &);
    void setPlaylist(const std::vector<Playlist> &);
    void setRepVote(const bool &);
    void addTypesOfMusic(const std::string &);
    friend std::ostream &operator<<(std::ostream &, const User &);
    int read(std::istream &in);
    void changeUserName();
    void changePassword();
    void changeFullName();
    void changeBornDate();
    void addGenre();
    void removeGenre();
    void removePlaylist();
    void addPlaylist(const Playlist&);
    void allPlaylistsNames()const;
};

#endif