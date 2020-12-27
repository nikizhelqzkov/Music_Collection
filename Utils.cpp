
#include "Utils.h"
bool number::isHasSong(const std::vector<Song> &songs, const std::string &name)
{
    for (auto &&s : songs)
    {
        if (s.getTitle() == name)
        {
            return true;
        }
    }
    return false;
}
bool number::isNumber(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool number::isDoubleNumber(const std::string &s)
{
    char *end = nullptr;
    strtod(s.c_str(), &end); //funkciq koqto promenq end pointera s \0, ako e uzspeshen casta!!!
    return end != s.c_str() && *end == '\0';
}

bool text::isSameNamePl(User &user, std::string name)
{
    for (auto &&element : user.getPlaylists())
    {
        if (element.getName() == name)
        {
            return true;
        }
    }
    return false;
}
bool text::isHasGenres(const std::vector<std::string> &list, const std::string &name)
{
    for (auto &&s : list)
    {
        if (s == name)
        {
            return true;
        }
    }
    return false;
}

void output::printingSongs(const std::vector<Song> &sv)
{
    std::ofstream out("Songs.txt");
    out << sv.size() << ";";
    for (auto &&element : sv)
    {
        out << element;
    }
}

bool output::getPlaylist(const User &u, std::string name, Playlist &pl)
{
    for (int i = 0; i < u.getPlaylists().size(); ++i)
    {
        if (u.getPlaylists()[i].getName() == name)
        {
            pl = u.getPlaylists()[i];
            return true;
        }
    }
    return false;
}
void output::printingOneSong(const Playlist &pl, int pos)
{
    std::cout << "Starting song number " << pos << " -> ";
    pl.getList()[pos - 1].printSongInfo();
    std::cout << std::endl;
}
void output::printSongInfo(const User &u, std::string name)
{
    Playlist current;
    int pos = -1;
    bool isHere = false;
    for (int i = 0; i < u.getPlaylists().size(); ++i)
    {
        if (u.getPlaylists()[i].getName() == name)
        {
            pos = i;
            isHere = true;
        }
    }

    if (!isHere)
    {
        std::cout << "This playlist is missing! Try again!!!\n";
    }
    else
    {
        std::cout << "\nYou choose playlist: " << u.getPlaylists()[pos].getName() << "\nThat is your playlists' songs information:\n";
        for (int i = 1; i <= u.getPlaylists()[pos].getList().size(); ++i)
        {
            std::cout << "Song " << i << " -> ";
            u.getPlaylists()[pos].getList()[i - 1].printSongInfo();
            std::cout << std::endl;
        }
    }
}
