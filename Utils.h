#ifndef NUM_H
#define NUM_H
#include "boot.h"
namespace number
{
    bool isHasSong(const std::vector<Song> &songs, const std::string &name);
    bool isNumber(const std::string &s);
    bool isDoubleNumber(const std::string &s);
} // namespace number
#endif

#ifndef TEXT_I
#define TEXT_I
namespace text
{
    bool isSameNamePl(User &user, std::string name);
    bool isHasGenres(const std::vector<std::string> &list, const std::string &name);
} // namespace text
#endif
#ifndef OUTPUT_H
#define OUTPUT_H
namespace output
{
    void printingSongs(const std::vector<Song> &sv);

    bool getPlaylist(const User &u, std::string name, Playlist &pl);

    void printingOneSong(const Playlist &pl, int pos);

    void printSongInfo(const User &u, std::string name);

} // namespace output
#endif