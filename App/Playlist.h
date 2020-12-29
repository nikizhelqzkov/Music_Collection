#ifndef PLAYLIST_INCLUDED
#define PLAYLIST_INCLUDED
#include <vector>
#include "Song.h"
/**
 * @brief Клас пазещ данните за една плейлиста
 * 
 */
class Playlist
{
private:
    std::string name;   
    std::vector<Song> list;
    void copy(const Playlist &other);

public:
    Playlist() = default;
    Playlist(const std::string &name, const std::vector<Song> &list);
    ~Playlist() = default;
    Playlist &operator=(const Playlist &other);
    void setName(const std::string &name);
    void setList(const std::vector<Song> &list);
    std::string getName() const;
    std::vector<Song> getList() const;
    friend std::ostream &operator<<(std::ostream &, const Playlist &);
    int readHelper(std::istream &in, int count);
    int read(std::istream &in);
    void printSongs() const;
};

#endif