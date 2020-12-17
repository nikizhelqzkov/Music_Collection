#include "User.h"

User::User()
{
}
User::User(const std::string &_username, const std::string &_password, const std::string &_fullName, const Date &_born, const std::vector<std::string> &_genres, const std::vector<Playlist> &_playlists)
    : username(_username), password(_password), fullName(_fullName), born(_born), genres(_genres), playlists(_playlists)
{
}
User::User(const User &other)
    : username(other.username), password(other.password), fullName(other.fullName), born(other.born), genres(other.genres)
{
}

User::~User()
{
}
void User::copy(const User &other)
{
    setUsername(other.username);
    setPassword(other.password);
    setFullName(other.fullName);
    setBornDate(other.born);
    setGenres(other.genres);
    setPlaylist(other.playlists);
}
User &User::operator=(const User &other)
{
    if (this != &other)
    {
        copy(other);
    }
    return *this;
}
std::string User::getUsername() const { return this->username; }
std::string User::getPassword() const { return this->password; }
std::string User::getFullName() const { return this->fullName; }
Date User::getBornDate() const { return this->born; }
std::vector<std::string> User::getGenres() const
{
    return this->genres;
}
std::vector<Playlist> User::getPlaylists() const
{
    return this->playlists;
}

void User::setUsername(const std::string &_data)
{
    this->username = _data;
}
void User::setPassword(const std::string &_data)
{
    this->password = _data;
}
void User::setFullName(const std::string &_data)
{
    this->fullName = _data;
}
void User::setBornDate(const Date &_data)
{
    this->born = _data;
}
void User::setGenres(const std::vector<std::string> &_data)
{
    this->genres = _data;
}
void User::setPlaylist(const std::vector<Playlist> &_playlists)
{
    this->playlists = _playlists;
}
void User::addTypesOfMusic(const std::string &type)
{
    this->genres.push_back(type);
}

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

void User::changeUserName()
{
    std::string uN;
    std::string oldUsername = this->username + ".txt";
    bool isOk = true;
    std::cin.ignore();
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
void User::changePassword()
{
    std::string newPassword;
    std::cin.ignore();
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
void User::changeFullName()
{
    std::string newFullName;
    std::cin.ignore();
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
void User::changeBornDate()
{
    std::cout << "You are changing your born date: \n";
    this->born.read();
    std::ofstream output(this->username + ".txt");
    output << *this;
    std::cout << "Your born date had been changed!!!\n\n";
}
void User::addGenre()
{
    bool isOk = true;
    std::string genre;
    std::cin.ignore();
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
void User::removeGenre()
{
    if (genres.size() < 1)
    {
        std::cout << "You don't have any genres\n";
        return;
    }
    std::cin.ignore();
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
void User::removePlaylist()
{
    if (playlists.size() == 1 && playlists[0].getName().empty())
    {
        std::cout << "You don't have any playlists!!!\n";
        return;
    }
    std::cin.ignore();
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
void User::addPlaylist(const Playlist &p)
{
    playlists.push_back(p);
}