#include "Song.h"

Song::Song(const std::string &_title, const std::string &_author, const std::string &_genres, const std::string &_album, unsigned int _year, double _rating)
    : title(_title), author(_author), genres(_genres), album(_album), year(_year), rating(_rating)
{
    this->ratings.push_back(_rating);
}

Song::~Song() {}

void Song::setTitle(const std::string &title)
{
    this->title = title;
}
void Song::setAuthor(const std::string &author)
{
    this->author = author;
}
void Song::setGenres(const std::string &genres)
{
    this->genres = genres;
}
void Song::setAlbum(const std::string &album)
{
    this->album = album;
}
void Song::setYear(const unsigned int &year)
{
    this->year = year;
}
void Song::setRating(double rating)
{
    std::cout << "\n\nrating size: " << ratings.size() << " \n\n";
    ratings.push_back(rating);
    std::cout << "\n\nrating size: " << ratings.size() << " \n\n";
    if (this->ratings.size() <= 1)
    {
        this->rating = rating;
    }
    else if (ratings.size() == 2 && isDefaultRating)
    {
        ratings.erase(ratings.begin());
        isDefaultRating = false;
    std::cout<<"Here 2\n";
        this->rating = ratings[0];
    }
    else
    {
         std::cout<<"Here 3\n";
        this->rating = std::accumulate(ratings.begin(), ratings.end(), 0.0) / ratings.size();
    }
}
void Song::copy(const Song &other)
{
    setTitle(other.title);
    setAuthor(other.author);
    setGenres(other.genres);
    setAlbum(other.album);
    setYear(other.year);
    setRating(other.rating);
}
Song &Song::operator=(const Song &other)
{
    if (this != &other)
    {
        copy(other);
    }
    return *this;
}
std::string Song::getTitle() const
{
    return this->title;
}
std::string Song::getAuthor() const
{
    return this->author;
}
std::string Song::getGenres() const
{
    return this->genres;
}
std::string Song::getAlbum() const
{
    return this->album;
}
unsigned int Song::getYear() const
{
    return this->year;
}
double Song::getRating() const
{
    return this->rating;
}
std::ostream &operator<<(std::ostream &out, const Song &song)
{
    out << "Song->Title->" << song.title << ";Author->" << song.author << ";Genre->" << song.genres << ";Album->" << song.album << ";Year->" << song.year << ";Rating->" << song.rating << ";" << song.userRate.size() << ";vU->";
    for (auto &&element : song.userRate)
    {
        out << element << ";";
    }

    return out;
}
int Song::readHelper(std::istream &in, int count)
{
    /*int res = 10 + username.size() + 11;
    input.seekg(res);*/
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
    std::string cV;
    std::getline(in, cV, ';');
    int cS = std::stoi(cV);
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
        count += 1;
    }

    return count;
}
int Song::read(std::istream &in)
{
    return readHelper(in, 0);
}

void Song::setAverageRating(const std::vector<double> &ratings)
{
}
void Song::addingSongInfo()
{
    std::string songName, author, genre, album, year;
    std::cin.ignore();
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
void Song::setUserRateName(const std::string &user)
{
    this->userRate.push_back(user);
}
std::vector<std::string> Song::getUserRateNames() const
{
    return this->userRate;
}