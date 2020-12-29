#include "User.h"
/**
 * @brief Construct a new User:: User object
 * 
 * @param _username 
 * @param _password 
 * @param _fullName 
 * @param _born 
 * @param _genres 
 * @param _playlists 
 */
User::User(const std::string &_username, const std::string &_password, const std::string &_fullName, const Date &_born, const std::vector<std::string> &_genres, const std::vector<Playlist> &_playlists)
    : username(_username), password(_password), fullName(_fullName), born(_born), genres(_genres), playlists(_playlists)
{
}
/**
 * @brief Construct a new User:: User object
 * 
 * @param other 
 */
User::User(const User &other)
    : username(other.username), password(other.password), fullName(other.fullName), born(other.born), genres(other.genres)
{
}
/**
 * @brief Функция, която се използва за копи конструктора
 * 
 * @param other 
 */
void User::copy(const User &other)
{
    setUsername(other.username);
    setPassword(other.password);
    setFullName(other.fullName);
    setBornDate(other.born);
    setGenres(other.genres);
    setPlaylist(other.playlists);
}
/**
 * @brief Оператор за присвояване от една песен на друга
 * 
 * @param other 
 * @return User& 
 */
User &User::operator=(const User &other)
{
    if (this != &other)
    {
        copy(other);
    }
    return *this;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната username
 * 
 * @return std::string 
 */
std::string User::getUsername() const { return this->username; }
/**
 * @brief Мутатор извеждащ стойността на член-данната password
 * 
 * @return std::string 
 */
std::string User::getPassword() const { return this->password; }
/**
 * @brief Мутатор извеждащ стойността на член-данната fullName
 * 
 * @return std::string 
 */
std::string User::getFullName() const { return this->fullName; }
/**
 * @brief Мутатор извеждащ стойността на член-данната born
 * 
 * @return Date 
 */
Date User::getBornDate() const { return this->born; }
/**
 * @brief Мутатор извеждащ стойността на член-данната genres
 * 
 * @return std::vector<std::string> 
 */
std::vector<std::string> User::getGenres() const
{
    return this->genres;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната playlists
 * 
 * @return std::vector<Playlist> 
 */
std::vector<Playlist> User::getPlaylists() const
{
    return this->playlists;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната username
 * 
 * @param _data 
 */
void User::setUsername(const std::string &_data)
{
    this->username = _data;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната password
 * 
 * @param _data 
 */
void User::setPassword(const std::string &_data)
{
    this->password = _data;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната fullName
 * 
 * @param _data 
 */
void User::setFullName(const std::string &_data)
{
    this->fullName = _data;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната born
 * 
 * @param _data 
 */

void User::setBornDate(const Date &_data)
{
    this->born = _data;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната genres
 * 
 * @param _data 
 */
void User::setGenres(const std::vector<std::string> &_data)
{
    this->genres = _data;
}
/**
 * @brief  Мутатор с аргумент, който се вкарва в член-данната playlists
 * 
 * @param _playlists 
 */
void User::setPlaylist(const std::vector<Playlist> &_playlists)
{
    this->playlists = _playlists;
}
/**
 * @brief  Мутатор с аргумент, който се вкарва в член-данната genres
 * 
 * @param type 
 */
void User::addTypesOfMusic(const std::string &type)
{
    this->genres.push_back(type);
}
/**
 * @brief Оператор за печатане на Юзър в поток
 * 
 * @param out 
 * @param user 
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &out, const User &user)
{

    out << "Username->" << user.username << ";Password->"
        << user.password << ";FullName->" << user.fullName
        << ";Born->" << user.born << ";" << user.genres.size()
        << ";Genres->";
    for (auto &&element : user.genres)
    {
        out << element << ";";
    }
    out << user.playlists.size() << ";Playlists->";
    for (auto &&element : user.playlists)
    {
        out << element;
    }

    return out;
}
/**
 * @brief Функция, която чете от поток данните за Юзъра и ги добавя в класа
 * 
 * @param in 
 * @return int 
 */
int User::read(std::istream &in)
{

    int count = 10;

    in.seekg(count);

    std::string username, password, fullName, born;
    std::getline(in, username, ';');
    count += username.size() + 11;
    in.seekg(count);
    std::getline(in, password, ';');
    count += password.size() + 11;
    in.seekg(count);
    std::getline(in, fullName, ';');
    count += fullName.size() + 7;
    in.seekg(count);
    std::getline(in, born, ';');
    count += born.size() + 1;
    in.seekg(count);
    std::string genresSize;
    std::getline(in, genresSize, ';');
    count += genresSize.size() + 9;
    in.seekg(count);
    int gSize = std::stoi(genresSize);
    std::vector<std::string> genres;
    for (int i = 0; i < gSize; ++i)
    {
        std::string genre;
        std::getline(in, genre, ';');
        count += genre.size() + 1;
        in.seekg(count);
        genres.push_back(genre);
    }
    std::string plSize;
    std::getline(in, plSize, ';');
    int playSize = std::stoi(plSize);
    count += plSize.size() + 12;
    in.seekg(count);
    std::vector<Playlist> p;
    for (int i = 0; i < playSize; ++i)
    {
        Playlist playList;
        count = playList.readHelper(in, count);
        p.push_back(playList);
    }
    setUsername(username);
    setPassword(password);
    setFullName(fullName);
    int day = std::stoi(born);
    born.erase(0, 3);
    int month = std::stoi(born);
    born.erase(0, 3);
    int year = std::stoi(born);
    Date bornDate(day, month, year);
    setBornDate(bornDate);
    setGenres(genres);
    setPlaylist(p);
    return count;
}
/**
 * @brief Функция, която сменя потребителското име
 * 
 */
void User::changeUserName()
{
    std::string uN;
    std::string oldUsername = this->username + ".txt";
    bool isOk = true;
    do
    {
        isOk = true;

        std::cout << "What do you want to be your new userName: ";

        std::getline(std::cin, uN);
        if (uN.empty())
        {
            isOk = false;
            std::cout << "You didn't write any name!!!\nTry again\n\n";
        }
        else
        {
            std::ifstream inUser(uN + ".txt");
            if (inUser.is_open())
            {
                isOk = false;
                std::cout << "That username is busy!!!\nTry new one\n\n";
            }
            inUser.close();
        }

    } while (!isOk);
    setUsername(uN);
    std::ofstream usernameOut(uN + ".txt");
    usernameOut << *this;
    std::remove(oldUsername.c_str());
    std::cout << "Your username had been changed with : " << uN << " ! :)\n\n";
}
/**
 * @brief Функция, която сменя паролата
 * 
 */
void User::changePassword()
{
    std::string newPassword;
    bool isOk = true;
    do
    {
        isOk = true;
        std::cout << "What do you want to be your new password: ";
        std::getline(std::cin, newPassword);
        if (newPassword.empty())
        {
            isOk = false;
            std::cout << "You didn't write any password!!!\nTry again\n\n";
        }
    } while (!isOk);
    setPassword(newPassword);
    std::ofstream output(this->username + ".txt");
    output << *this;
    std::cout << "Your password had been changed!!!\n\n";
}
/**
 * @brief Функция, която сменя Пълното име
 * 
 */
void User::changeFullName()
{
    std::string newFullName;
    bool isOk = true;
    do
    {
        isOk = true;
        std::cout << "What do you want to be your new full name: ";
        std::getline(std::cin, newFullName);
        if (newFullName.empty())
        {
            isOk = false;
            std::cout << "You didn't write any password!!!\nTry again\n\n";
        }
    } while (!isOk);
    setFullName(newFullName);
    std::ofstream output(this->username + ".txt");
    output << *this;
    std::cout << "Your full name had been changed!!!\n\n";
}
/**
 * @brief Функция, която сменя Рождената дата
 * 
 */
void User::changeBornDate()
{
    std::cout << "You are changing your born date: \n";
    born.read();
    std::ofstream output(this->username + ".txt");
    output << *this;
    std::cout << "Your born date had been changed!!!\n\n";
}
/**
 * @brief Функция, която добавя жанр в класа
 * 
 */
void User::addGenre()
{
    bool isOk = true;
    std::string genre;
    do
    {
        isOk = true;
        std::cout << "Write your genre: ";
        std::getline(std::cin, genre);
        bool isRep = false;
        for (auto &&element : genres)
        {
            if (element == genre)
            {
                isRep = true;
                std::cout << "Your genre is in your favourites!\nTry again!!!\n";
            }
        }
        if (isRep)
        {
            isOk = false;
        }
        else
        {
            addTypesOfMusic(genre);
            isOk = true;
        }

    } while (!isOk);
    std::ofstream output(this->username + ".txt");
    output << *this;
    std::cout << "Your genres had been changed!!!\n\n";
}
/**
 * @brief Функция, която маха жанр от класа
 * 
 */
void User::removeGenre()
{
    if (genres.size() < 1)
    {
        std::cout << "You don't have any genres\n";
        return;
    }
    bool isOk = true;
    std::string genre;
    do
    {
        isOk = true;
        std::cout << "Write your genre: ";
        std::getline(std::cin, genre);
        bool isRep = false;
        int pos;
        for (int i = 0; i < genres.size(); ++i)
        {
            if (genres[i] == genre)
            {
                isRep = true;
                pos = i;
            }
        }
        if (!isRep)
        {
            isOk = false;
            std::cout << "Your genre is not exists!\nTry again!!!\n";

            std::cout << "Do you want to leave this part? (y for YES  or any other symbol for NO): ";
            std::string c;
            std::getline(std::cin, c);
            if (c == "y")
            {
                return;
            }
        }
        else
        {
            genres.erase(genres.begin() + pos);
            isOk = true;
        }

    } while (!isOk);
    std::ofstream output(this->username + ".txt");
    output << *this;
    std::cout << "Your genres had been changed!!!\n\n";
}
/**
 * @brief Функция, която маха плейлист от класа
 * 
 */
void User::removePlaylist()
{
    if (playlists.size() == 1 && playlists[0].getName().empty())
    {
        std::cout << "You don't have any playlists!!!\n";
        return;
    }
    bool isOk = true;
    std::string pl;
    do
    {
        isOk = true;
        std::cout << "Write your playlist name: ";
        std::getline(std::cin, pl);
        bool isRep = false;
        int pos;
        for (int i = 0; i < this->playlists.size(); ++i)
        {
            if (playlists[i].getName() == pl)
            {
                isRep = true;
                pos = i;
            }
        }
        if (!isRep)
        {
            isOk = false;
            std::cout << "Your playlist name is not exists!\nTry again!!!\n";

            std::cout << "Do you want to leave this part? (y for YES  or any other symbol for NO): ";
            std::string c;
            std::getline(std::cin, c);
            if (c == "y")
            {
                return;
            }
        }
        else
        {
            playlists.erase(this->playlists.begin() + pos);
            isOk = true;
        }

    } while (!isOk);
    std::ofstream output(this->username + ".txt");
    output << *this;
    std::cout << "Your playlists had been changed!!!\n\n";
}
/**
 * @brief Функция, която добавя плейлиста към списъка от плейлисти на класа
 * 
 * @param p 
 */
void User::addPlaylist(const Playlist &p)
{
    playlists.push_back(p);
}
/**
 * @brief Функция, която извежда на екрана всички имена на плейлисти от класа
 * 
 */
void User::allPlaylistsNames() const
{
    std::cout << "Your playlist names are:\n";
    int count = 1;
    for (auto &&pl : playlists)
    {
        std::cout << "Playlist " << count << " -> " << pl.getName() << "\n";
        ++count;
    }
}