#include "Song.h"
/**
 * @brief Construct a new Song:: Song object
 * 
 * @param _title 
 * @param _author 
 * @param _genres 
 * @param _album 
 * @param _year 
 * @param _rating 
 */
Song::Song(const std::string &_title, const std::string &_author, const std::string &_genres, const std::string &_album, unsigned int _year, double _rating)
    : title(_title), author(_author), genres(_genres), album(_album), year(_year), rating(_rating)
{
    this->ratings.push_back(_rating);
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната title
 * 
 * @param title 
 */
void Song::setTitle(const std::string &title)
{
    this->title = title;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната author
 * 
 * @param author 
 */
void Song::setAuthor(const std::string &author)
{
    this->author = author;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната genres
 * 
 * @param genres 
 */
void Song::setGenres(const std::string &genres)
{
    this->genres = genres;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната album
 * 
 * @param album 
 */
void Song::setAlbum(const std::string &album)
{
    this->album = album;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната year
 * 
 * @param year 
 */
void Song::setYear(const unsigned int &year)
{
    this->year = year;
}
/**
 * @brief Функция, която изчислява средния рейтинг на гласувалите
 * 
 * @param rating 
 */
void Song::setRating(double rating)
{
    if (this->ratings.size() <= 1)
    {

        this->rating = rating;
    }
    else
    {
        this->rating = std::accumulate(ratings.begin(), ratings.end(), 0.0) / ratings.size();
    }
}
/**
 * @brief Функция, която се използва за копи конструктора
 * 
 * @param other 
 */
void Song::copy(const Song &other)
{
    setTitle(other.title);
    setAuthor(other.author);
    setGenres(other.genres);
    setAlbum(other.album);
    setYear(other.year);
    setRating(other.rating);
}
/**
 * @brief Оператор за присвояване от една песен на друга
 * 
 * @param other 
 * @return Song& 
 */
Song &Song::operator=(const Song &other)
{
    if (this != &other)
    {
        copy(other);
    }
    return *this;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната title;
 * 
 * @return std::string 
 */
std::string Song::getTitle() const
{
    return this->title;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната authors;
 * 
 * @return std::string 
 */
std::string Song::getAuthor() const
{
    return this->author;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната genres;
 * 
 * @return std::string 
 */
std::string Song::getGenres() const
{
    return this->genres;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната album;
 * 
 * @return std::string 
 */
std::string Song::getAlbum() const
{
    return this->album;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната year;
 * 
 * @return unsigned int 
 */
unsigned int Song::getYear() const
{
    return this->year;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната rating;
 * 
 * @return double 
 */
double Song::getRating() const
{
    return this->rating;
}
/**
 * @brief Мутатор извеждащ стойността на член-данната ratings;
 * 
 * @return std::vector<double> 
 */
std::vector<double> Song::getRatings()
{
    return this->ratings;
}
/**
 * @brief Оператор за печатане на Песен в поток
 * 
 * @param out 
 * @param song 
 * @return std::ostream& 
 */
std::ostream &operator<<(std::ostream &out, const Song &song)
{
    out << "Song->Title->" << song.title << ";Author->" << song.author << ";Genre->" << song.genres << ";Album->" << song.album << ";Year->"
        << song.year << ";Rating->" << song.rating << ";"
        << song.isDefaultRating << ";";
    if (song.ratings.size() == 1 && song.isDefaultRating && song.ratings[0] == 0)
    {
        out << "0;r->;";
    }
    else
    {
        out << song.ratings.size() << ";r->";
        for (auto &&element : song.ratings)
        {
            out << element << ";";
        }
    }
    out << song.userRate.size() << ";vU->";
    for (auto &&element : song.userRate)
    {
        out << element << ";";
    }

    return out;
}
/**
 * @brief Функция, която чете от поток данните за песента и ги добавя в класа
 * 
 * @param in 
 * @param count 
 * @return int 
 */
int Song::readHelper(std::istream &in, int count)
{
    in.seekg(count + 13);
    std::string _title;
    std::getline(in, _title, ';');
    count += _title.size() + 13;
    count += 9;
    in.seekg(count);
    std::string _author;
    std::getline(in, _author, ';');
    count += _author.size() + 8;
    in.seekg(count);
    std::string _genres;
    std::getline(in, _genres, ';');
    count += _genres.size() + 8;
    in.seekg(count);
    std::string _album;
    std::getline(in, _album, ';');
    count += _album.size() + 7;
    in.seekg(count);
    std::string _year;
    std::getline(in, _year, ';');
    count += _year.size() + 9;
    in.seekg(count);
    std::string _rating;
    std::getline(in, _rating, ';');
    this->setTitle(_title);
    this->setAuthor(_author);
    this->setGenres(_genres);
    this->setAlbum(_album);
    this->setYear(std::stoi(_year));
    this->setRating(std::atof(_rating.c_str()));
    count += _rating.size() + 1;
    in.seekg(count);
    std::string isDef;
    std::getline(in, isDef, ';');
    isDefaultRating = isDef == "1";
    count += isDef.size() + 1;
    in.seekg(count);
    int rSize;
    std::string rateS;
    std::getline(in, rateS, ';');
    rSize = std::stoi(rateS);
    if (rSize == 0)
    {
        count += rateS.size() + 5;
    }
    else
    {
        count += rateS.size() + 4;
        for (int i = 0; i < rSize; ++i)
        {
            in.seekg(count);
            std::string rate;
            std::getline(in, rate, ';');
            count += rate.size() + 1;
            setAverageRating(std::atof(rate.c_str()));
        }
    }

    in.seekg(count);
    std::string cV;
    std::getline(in, cV, ';');
    int cS;
    if (cV.empty())
    {
        cS = 0;
    }
    else
    {
        cS = std::stoi(cV);
    }
    count += cV.size() + 5;
    for (size_t i = 0; i < cS; ++i)
    {
        in.seekg(count);
        std::string temp;
        std::getline(in, temp, ';');
        count += temp.size() + 1;
        this->userRate.push_back(temp);
    }
    if (cS == 0)
    {
        in.seekg(count);
    }

    return count;
}
/**
 * @brief функция четяща от поток
 * 
 * @param in 
 * @return int 
 */
int Song::read(std::istream &in)
{
    return readHelper(in, 0);
}
/**
 * @brief Функция, която добавя рейтинг от текущия потребител
 * 
 * @param rate 
 */
void Song::setAverageRating(const double &rate)
{
    this->ratings.push_back(rate);
}
/**
 * @brief Добавяне на информация за песента от конзолата
 * 
 */
void Song::addingSongInfo()
{
    std::string songName, author, genre, album, year;
    std::cout << "Write the name of the song: ";
    std::getline(std::cin, songName);
    std::cout << "\nWrite the author of the song: ";
    std::getline(std::cin, author);
    std::cout << "\nWrite the genre of the song: ";
    std::getline(std::cin, genre);
    std::cout << "\nWrite the album name of the song: ";
    std::getline(std::cin, album);
    std::cout << "\nWrite the year of the song: ";
    std::getline(std::cin, year);
    setTitle(songName);
    setAuthor(author);
    setGenres(genre);
    setAlbum(album);
    setYear(std::stoi(year));
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната userRate
 * 
 * @param user 
 */
void Song::setUserRateName(const std::string &user)
{
    this->userRate.push_back(user);
}
/**
 * @brief Мутатор извеждащ стойността на член-данната userRate;
 * 
 * @return std::vector<std::string> 
 */
std::vector<std::string> Song::getUserRateNames() const
{
    return this->userRate;
}
/**
 * @brief Функция която принтира в конзолата информция за песента
 * 
 */
void Song::printSongInfo() const
{
    std::cout << "Title: " << title << " , "
              << "Author: " << author << " , "
              << "Genre: " << genres << " , "
              << "Album: " << album << " , "
              << "Year: " << year;
}
/**
 * @brief Оператор за сравнение на 2 песни по заглавие
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Song::operator<(const Song &other) const
{
    return this->title < other.title;
}
/**
 * @brief Оператор за сравнение на 2 песни по заглавие
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Song::operator>(const Song &other) const
{
    return this->title > other.title;
}
/**
 * @brief Оператор за сравнение на 2 песни по заглавие
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Song::operator==(const Song &other) const
{
    return this->title == other.title;
}
/**
 * @brief Оператор за сравнение на 2 песни по заглавие
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Song::operator!=(const Song &other) const
{
    return this->title != other.title;
}
/**
 * @brief Оператор за сравнение на 2 песни по заглавие
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Song::operator<=(const Song &other) const
{
    return this->title <= other.title;
}
/**
 * @brief Оператор за сравнение на 2 песни по заглавие
 * 
 * @param other 
 * @return true 
 * @return false 
 */
bool Song::operator>=(const Song &other) const
{
    return this->title >= other.title;
}