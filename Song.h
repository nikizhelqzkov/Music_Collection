#ifndef Song_INCLUDED
#define Song_INCLUDED
#include <string>
#include <vector>
#include <numeric>

#include <iostream>
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
    bool isDefaultRating = true;
    std::vector<double> ratings;
    std::vector<std::string> userRate;

public:
    Song() = default;
    Song(const std::string &title, const std::string &author, const std::string &genres, const std::string &album, unsigned int year, double rating);
    ~Song();
    void setTitle(const std::string &title);
    void setAuthor(const std::string &author);
    void setGenres(const std::string &genres);
    void setAlbum(const std::string &album);
    void setYear(const unsigned int &year);
    void setRating(double rating);
    void setAverageRating(const double&);
    Song &operator=(const Song &);
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getGenres() const;
    std::string getAlbum() const;
    unsigned int getYear() const;
    std::vector<double>getRatings();
    double getRating() const;
    friend std::ostream &operator<<(std::ostream &, const Song &);
    int read(std::istream &in);
    int readHelper(std::istream &in, int count);
    void addingSongInfo();
    void setUserRateName(const std::string &user);
    std::vector<std::string> getUserRateNames() const;
    void printSongInfo()const;
};

#endif
