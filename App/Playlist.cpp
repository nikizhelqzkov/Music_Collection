#include "Playlist.h"
/**
 * @brief Construct a new Playlist:: Playlist object
 * 
 * @param _name 
 * @param _list 
 */
Playlist::Playlist(const std::string &_name, const std::vector<Song> &_list)
    : name(_name), list(_list) {}
/**
 * @brief Помощна функция, която помага за копи конструктора
 * 
 * @param other 
 */
void Playlist::copy(const Playlist &other)
{
    setName(other.name);
    setList(other.list);
}
/**
 * @brief Оператор, който присвоява от една плейлиста към класа Плейлиста
 * 
 * @param other 
 * @return Playlist& 
 */
Playlist &Playlist::operator=(const Playlist &other)
{
    if (this != &other)
    {
        copy(other);
    }
    return *this;
}

/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната name
 * 
 * @param _name 
 */
void Playlist::setName(const std::string &_name)
{
    name = _name;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната list
 * 
 * @param _list 
 */
void Playlist::setList(const std::vector<Song> &_list)
{
    list = _list;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната name
 * 
 * @return std::string 
 */
std::string Playlist::getName() const
{
    return name;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната list
 * 
 * @return std::vector<Song> 
 */
std::vector<Song> Playlist::getList() const
{
    return list;
}
/**
 * @brief Оператор за печатане на плейлиста в поток
 * 
 * @param out 
 * @param playlist 
 * @return std::ostream& 
 */
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
/**
 * @brief функция за четене на данни за плейлиста от поток
 * 
 * @param in 
 * @param count 
 * @return int 
 */
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
        std::vector<Song> v;
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
/**
 * @brief Функция която чете вика хелпъра
 * 
 * @param in 
 * @return int 
 */
int Playlist::read(std::istream &in)
{
    return readHelper(in, 0);
}
/**
 * @brief Функция, която принтира информация за песните в плейлистата
 * 
 */
void Playlist::printSongs() const
{
    int count = 1;
    for (auto &&s : list)
    {
        std::cout << count << " song-> ";
        ++count;
        s.printSongInfo();
        std::cout << "\n";
    }
    std::cout << "\n";
}