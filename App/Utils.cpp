
#include "Utils.h"
/**
 * @brief Функция, която проверява дали дадения стринг е целочислено число
 * 
 * @param s 
 * @return true 
 * @return false 
 */
bool number::isNumber(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}
/**
 * @brief Функция, която проверява дали дадения стринг е дробно число
 * 
 * @param s 
 * @return true 
 * @return false 
 */
bool number::isDoubleNumber(const std::string &s)
{
    char *end = nullptr;
    /**   funkciq koqto promenq end pointera s \0, ako e uzspeshen casta!!!*/
    strtod(s.c_str(), &end);
    return end != s.c_str() && *end == '\0';
}
/**
 * @brief Функция, която проверява дали името съвпада с плейлистата
 * 
 * @param user 
 * @param name 
 * @return true 
 * @return false 
 */
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
/**
 * @brief Функция, която проверява дали съществува дадения жанр
 * 
 * @param list 
 * @param name 
 * @return true 
 * @return false 
 */
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
/**
 * @brief Булева функция, която проверява дали има песен с даденото име
 * 
 * @param songs 
 * @param name 
 * @return true 
 * @return false 
 */
bool text::isHasSong(const std::vector<Song> &songs, const std::string &name)
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
/**
 * @brief Функция, която печата песни в файла с песните на системата
 * 
 * @param sv 
 */
void output::printingSongs(const std::vector<Song> &sv)
{
    std::ofstream out("Songs.txt");
    out << sv.size() << ";";
    for (auto &&element : sv)
    {
        out << element;
    }
}
/**
 * @brief Мутатор, който намира дадената плейлиста
 * 
 * @param u 
 * @param name 
 * @param pl 
 * @return true 
 * @return false 
 */
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
/**
 * @brief Функция, която печата на екрана информация за една песен на дадена позиция от плейлистата
 * 
 * @param pl 
 * @param pos 
 */
void output::printingOneSong(const Playlist &pl, int pos)
{
    std::cout << "Starting song number " << pos << " -> ";
    pl.getList()[pos - 1].printSongInfo();
    std::cout << std::endl;
}
/**
 * @brief Функция, която печата на екрана информация за всичките песни, които има потребителя
 * 
 * @param u 
 * @param name 
 */
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
