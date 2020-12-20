#ifndef Generator_H
#define Generator_H
#include "boot.h"

class Generator
{
private:
    bool isHasSong(const std::vector<Song> &songs, const std::string &name) const;
    bool isSameNamePl(User &user, std::string name) const;
    bool isHasGenres(const std::vector<std::string> &list, const std::string &name) const;
    bool isNumber(const std::string &s) const;
    bool isDoubleNumber(const std::string &s) const;
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