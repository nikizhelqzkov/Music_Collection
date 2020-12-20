#ifndef UI_INCLUDED
#define UI_INCLUDED
#include "Generator.h"
class UI
{
private:
    void printingSongs(const std::vector<Song> &sv) const;
    bool getPlaylist(const User &u, std::string name, Playlist &pl) const;
    void printingOneSong(const Playlist &pl, int pos) const;
    void printSongInfo(const User &u, std::string name) const;
    bool isNumber(const std::string &s) const;
    void printPlaylistSongs(const User&u, const std::string& name)const;
    

public:
    UI() = default;
    ~UI() = default;
    void start();
};

#endif