#include "Playlist.h"
Playlist::Playlist(const std::string &_name, const std::vector<Song> &_list)
    : name(_name), list(_list) {}

Playlist::~Playlist()
{
}

void Playlist::copy(const Playlist &other)
{
    setName(other.name);
    setList(other.list);
}
Playlist &Playlist::operator=(const Playlist &other)
{
    if (this != &other)
    {
        copy(other);
    }
    return *this;
}
void Playlist::setName(const std::string &_name)
{
    name = _name;
}
void Playlist::setList(const std::vector<Song> &_list)
{
    list = _list;
}
std::string Playlist::getName() const
{
    return name;
}
std::vector<Song> Playlist::getList() const
{
    return list;
}
std::ostream &operator<<(std::ostream &out, const Playlist &playlist)
{
    if (playlist.name == "")
    {
        return out;
    }
    out << "Playlist->Name->" << playlist.name << ";SongList->";
    for (auto &&element : playlist.list)
    {
        out << element;
    }
    return out;
}