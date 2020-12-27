#ifndef Generator_H
#define Generator_H
#include "Utils.h"
using namespace number;
using namespace text;
class Generator
{
private:
    void pushingToEnd(const std::vector<Song> &songs, std::vector<Song> &plList, const int &plRes);
    int firstCriteria(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList);
    int pushingViaGenres(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, const std::vector<std::string> &genres);
    int pushingNotViaGenres(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, const std::vector<std::string> &genres);
    int thirdCriteria(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, const User &u);
    int secondCriteria(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList);
    int fourthCriteria(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList);
    int tokenizator(const std::string &input, const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, const User &u);

public:
    Generator() = default;
    ~Generator() = default;
    void generate(const std::vector<Song> &songs, User &user);
};
#endif