#include "Song.h"

Song::Song(const std::string &_title, const std::string &_author, const std::string &_genres, const std::string &_album, unsigned int _year, double _rating)
    : title(_title), author(_author), genres(_genres), album(_album), year(_year), rating(_rating) {}

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
void Song::setRating(const double &rating)
{
    this->rating = rating;
}
// if(!el)
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