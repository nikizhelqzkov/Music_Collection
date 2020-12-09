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
    out << "Playlist->Name->" << playlist.name << ";" << playlist.list.size() << ";SongList->";
    for (auto &&element : playlist.list)
    {
        out << element;
    }
    return out;
}

int Playlist::readHelper(std::istream &in, int count)
{
    count += 16;
    std::string playlistName;
    in.seekg(count);
    std::getline(in, playlistName, ';');
    if (!playlistName.empty())
    {
        count += playlistName.size() + 1;
        in.seekg(count);
        std::string s;
        std::getline(in, s, ';');
        int size = std::stoi(s);
        count += s.size() + 11;
        in.seekg(count);
        std::vector<Song>v;
        for (int i = 0; i < size; ++i)
        {
           
            Song temp;
            count = temp.readHelper(in, count);
            v.push_back(temp);
        }

        this->setName(playlistName);
        this->setList(v);
    }
    return count;
}
int Playlist::read(std::istream &in)
{
    return readHelper(in, 0);
}