#ifndef Song_INCLUDED
#define Song_INCLUDED
#include <string>

class Song
{
private:
    std::string title;
    std::string author;
    std::string genres;
    std::string album;
    unsigned int year;
    double rating;
    void copy(const Song &);

public:
    Song() = delete;
    Song(const std::string &title, const std::string &author, const std::string &genres, const std::string &album, unsigned int year, double rating);
    ~Song();
    void setTitle(const std::string &title);
    void setAuthor(const std::string &author);
    void setGenres(const std::string &genres);
    void setAlbum(const std::string &album);
    void setYear(const unsigned int &year);
    void setRating(const double &rating);

    Song &operator=(const Song &);
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getGenres() const;
    std::string getAlbum() const;
    unsigned int getYear() const;
    double getRating() const;

};

#endif
