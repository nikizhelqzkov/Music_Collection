#include "Generator.h"
bool Generator::isHasSong(const std::vector<Song> &songs, const std::string &name) const
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
bool Generator::isSameNamePl(User &user, std::string name) const
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
bool Generator::isHasGenres(const std::vector<std::string> &list, const std::string &name) const
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
bool Generator::isNumber(const std::string &s) const
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool Generator::isDoubleNumber(const std::string &s) const
{
    char *end = nullptr;
    strtod(s.c_str(), &end); //funkciq koqto promenq end pointera s \0, ako e uzspeshen casta!!!
    return end != s.c_str() && *end == '\0';
}
int Generator::firstCriteria(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList)
{

    std::cout << "You have chosen critetia for rating!";
    std::string r;
    std::vector<Song> temp;
    double rating;
    int count = 0;
    bool ok = false;
    do
    {
        ok = false;
        std::cout << "\nSo, Rating higher than: ";
        std::getline(std::cin, r);
        rating = isDoubleNumber(r) ? std::atof(r.c_str()) : -1;
        if (rating >= 0 && rating < 10)
        {
            ok = true;
        }
        else
        {
            std::cout << "Error rating!!! Try again!!!";
        }

    } while (!ok);

    int plRes = plSize;
    for (auto &&s : songs)
    {
        if (count == plSize)
        {
            std::sort(temp.begin(), temp.end());
            plList.insert(plList.end(), temp.begin(), temp.end());
            return count;
        }
        if (s.getRating() >= rating && !isHasSong(plList, s.getTitle()))
        {

            temp.push_back(s);
            ++count;
            --plRes;
        }
    }
    std::sort(temp.begin(), temp.end());
    plList.insert(plList.end(), temp.begin(), temp.end());
    return count;
}
int Generator::pushingViaGenres(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, const std::vector<std::string> &genres)
{
    int plRes = plSize;
    int count = 0;
    std::vector<Song> temp;
    for (auto &&s : songs)
    {
        if (count == plSize)
        {
            std::sort(temp.begin(), temp.end());
            plList.insert(plList.end(), temp.begin(), temp.end());
            return count;
        }

        if (isHasGenres(genres, s.getGenres()) && !isHasSong(plList, s.getTitle()))
        {
            temp.push_back(s);
            --plRes;
            ++count;
        }
    }
    std::sort(temp.begin(), temp.end());
    plList.insert(plList.end(), temp.begin(), temp.end());
    return count;
}
int Generator::pushingNotViaGenres(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, const std::vector<std::string> &genres)
{
    int plRes = plSize;
    int count = 0;
    std::vector<Song> temp;
    for (auto &&s : songs)
    {
        if (count == plSize)
        {
            std::sort(temp.begin(), temp.end());
            plList.insert(plList.end(), temp.begin(), temp.end());
            return count;
        }

        if (!isHasGenres(genres, s.getGenres()) && !isHasSong(plList, s.getTitle()))
        {
            temp.push_back(s);
            --plRes;
            ++count;
        }
    }
    std::sort(temp.begin(), temp.end());
    plList.insert(plList.end(), temp.begin(), temp.end());
    return count;
}
int Generator::thirdCriteria(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, const User &u)
{
    std::cout << "You have chosen critetia for only favourite genres!\n";
    int count = pushingViaGenres(songs, plSize, plList, u.getGenres());
    return count;
}
int Generator::secondCriteria(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList)
{
    std::cout << "You have chosen critetia for turn on or turn off some genres!";
    bool okOnOrOff = false;
    std::string onOrOff;
    int plRes = plSize;
    int count = 0;
    do
    {
        okOnOrOff = false;
        std::cout << "Write turn on(on) or turn off(off): ";
        std::getline(std::cin, onOrOff);
        if (onOrOff == "on" || onOrOff == "off")
        {
            okOnOrOff = true;
        }
        else
        {
            std::cout << "Error text!!! Try again!!!\n";
        }
    } while (!okOnOrOff);
    std::vector<std::string> genres;
    if (onOrOff == "on")
    {
        bool on = false;

        do
        {
            on = false;
            std::cout << "Write genre to be used for priority song genres: ";
            std::string temp;
            std::getline(std::cin, temp);
            if (temp.empty())
            {
                std::cout << "Empty text!!! Try again!!!\n";
            }
            else
            {
                genres.push_back(temp);
                std::string yOrN;
                std::cout << "More genres(y for yes and other for no): ";
                std::getline(std::cin, yOrN);
                if (yOrN != "y")
                {
                    on = true;
                }
            }
        } while (!on);
        count = pushingViaGenres(songs, plSize, plList, genres);
    }
    else if (onOrOff == "off")
    {
        bool off = false;
        do
        {
            off = false;
            std::cout << "Write genre to be not used for priority song genres: ";
            std::string temp;
            std::getline(std::cin, temp);
            if (temp.empty())
            {
                std::cout << "Empty text!!! Try again!!!\n";
            }
            else
            {
                genres.push_back(temp);
                std::string yOrN;
                std::cout << "More genres(y for yes and other for no): ";
                std::getline(std::cin, yOrN);
                if (yOrN != "y")
                {
                    off = true;
                }
            }
        } while (!off);
        count = pushingNotViaGenres(songs, plSize, plList, genres);
    }
    return count;
}
int Generator::fourthCriteria(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList)
{
    std::cout << "You have chosen critetia for year!";
    std::string y;
    std::vector<Song> temp;
    int year;

    bool okYear = false;
    std::string bEA;
    do
    {
        okYear = false;
        std::cout << "Write before, equal or after: ";
        std::getline(std::cin, bEA);
        if (bEA == "before" || bEA == "equal" || bEA == "after")
        {
            okYear = true;
        }
        else
        {
            std::cout << "Error word!!! Try again!!!\n";
        }
    } while (!okYear);
    int plRes = plSize;
    int count = 0;
    bool isOkYear = false;
    do
    {
        isOkYear = false;
        std::cout << "Write year: ";
        std::getline(std::cin, y);
        year = isNumber(y) ? std::stoi(y) : -1;
        if (year >= 0)
        {
            isOkYear = true;
        }
        else
        {
            std::cout << "Error year!!! Try again!!!\n";
        }

    } while (!isOkYear);

    for (auto &&s : songs)
    {
        if (count == plSize)
        {
            std::sort(temp.begin(), temp.end());
            plList.insert(plList.end(), temp.begin(), temp.end());
            return count;
        }
        if (bEA == "before")
        {
            if (s.getYear() < year && !isHasSong(plList, s.getTitle()))
            {
                temp.push_back(s);
                --plRes;
                ++count;
            }
        }
        else if (bEA == "equal")
        {
            if (s.getYear() == year && !isHasSong(plList, s.getTitle()))
            {
                temp.push_back(s);
                --plRes;
                ++count;
            }
        }
        else if (bEA == "after")
        {
            if (s.getYear() > year && !isHasSong(plList, s.getTitle()))
            {
                temp.push_back(s);
                --plRes;
                ++count;
            }
        }
    }
    std::sort(temp.begin(), temp.end());
    plList.insert(plList.end(), temp.begin(), temp.end());
    return count;
}
int Generator::tokenizator(const std::string &input, const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, const User &u)
{
    if (input == "1")
    {
        return firstCriteria(songs, plSize, plList);
    }
    else if (input == "2")
    {
        return secondCriteria(songs, plSize, plList);
    }
    else if (input == "3")
    {
        return thirdCriteria(songs, plSize, plList, u);
    }
    return fourthCriteria(songs, plSize, plList);
}
void Generator::generate(const std::vector<Song> &songs, User &user)
{

    std::queue<std::string> instructions;
    std::map<std::string, int> instr;
    instr["1"] = 0;
    instr["2"] = 0;
    instr["3"] = 0;
    instr["4"] = 0;
    std::queue<std::string> logicOp;
    bool isOkSize = false;
    std::string sizeOfP;
    int size;
    do
    {
        isOkSize = false;
        std::cout << "Write the size of the new playlist(between 1 and 20): ";
        std::getline(std::cin, sizeOfP);
        size = !sizeOfP.empty() ? std::stoi(sizeOfP) : -1;
        if (isNumber(sizeOfP) && (size > 0 && size <= 20))
        {
            isOkSize = true;
        }
        else
        {
            std::cout << "Error number! Try again!!\n";
        }
    } while (!isOkSize);

    std::string sCr;

    int criteria;
    bool isOkCriteria = false;
    do
    {
        isOkCriteria = false;
        std::cout << "Write how many criteria do u want(between 0 and 4): ";
        std::getline(std::cin, sCr);
        criteria = !sCr.empty() ? std::stoi(sCr) : -1;
        if (isNumber(sCr) && (criteria >= 0 && criteria <= 4))
        {
            isOkCriteria = true;
        }
        else
        {
            std::cout << "Error number! Try again!!\n";
        }
    } while (!isOkCriteria);

    bool isEmptyCriteria = criteria == 0;
    int count = 1;
    while (criteria > 1)
    {
        std::string temp;
        std::cout << count << " criteria: "
                  << "Write the number between 1 and 4: ";
        std::getline(std::cin, temp);

        if (isNumber(temp) && (std::stoi(temp) > 0 && std::stoi(temp) <= 4) && instr[temp] == 0)
        {
            instructions.push(temp);
            instr[temp]++;
            bool isOkLog = false;
            std::string log;
            do
            {
                isOkLog = false;
                std::cout << "Write logic AND(&) or logic OR(|): ";

                std::getline(std::cin, log);
                if (log == "&" || log == "|")
                {
                    isOkLog = true;
                }
                else
                {
                    std::cout << "Error logic operator! Try again!!!\n";
                }

            } while (!isOkLog);
            logicOp.push(log);
            --criteria;
            ++count;
        }
        else
        {
            if (instr[temp] != 0)
            {
                std::cout << "You have chosen this before!!! Try again!!!\n";
            }
            else
            {
                std::cout << "Error number!!! Try again\n";
            }
        }
    }
    while (criteria == 1)
    {

        std::string temp;
        std::cout << count << " criteria: "
                  << "Write the number between 1 and 4: ";
        std::getline(std::cin, temp);
        if (isNumber(temp) && (std::stoi(temp) > 0 && std::stoi(temp) <= 4) && instr[temp] == 0)
        {
            instr[temp]++;
            instructions.push(temp);
            --criteria;
            ++count;
        }
        else
        {
            if (instr[temp] != 0)
            {
                std::cout << "You have chosen this before!!! Try again!!!\n";
            }
            else
            {
                std::cout << "Error number!!! Try again\n";
            }
        }
    }
    Playlist pl;
    std::vector<Song> sList;
    int resSize = size;

    if ((count - 1) == 0)
    {
        //pushkane na size pesni v pleilistata
        if (size > songs.size())
        {
            sList = songs;
            std::cout << "Your playlist size is bigger than our song collection\n";
            std::cout << "Your playlist size is " << sList.size() << " songs!!!\n";
            std::sort(sList.begin(), sList.end());
            pl.setList(sList);
        }
        else
        {
            for (int i = 0; i < size; ++i)
            {
                sList.push_back(songs[i]);
            }
            std::sort(sList.begin(), sList.end());
            std::cout << "You do not have any criteria, so we added random songs for you!!!\n";
            std::cout << "Your playlist size is " << sList.size() << " songs!!!\n";
            pl.setList(sList);
        }
    }
    else if (count - 1 == 1)
    {
        std::string cr = instructions.front();
        int countSongs = tokenizator(cr, songs, resSize, sList, user);
        std::cout << "You chose one criterion!\n";
        if (countSongs == 0)
        {
            std::cout << "We do not have any good songs for you :(\n\n";
            return;
        }
        std::cout << "We added " << countSongs << " songs for you\n";
        instructions.pop();
        resSize -= countSongs;
    }
    else if (count - 1 == 2)
    {
        int countA = 0, countB = 0;
        std::string pr = instructions.front();
        instructions.pop();
        std::string pr2 = instructions.front();
        instructions.pop();
        std::string op = logicOp.front();
        logicOp.pop();
        if (op == "&")
        {
            countA = tokenizator(pr, songs, (resSize * 60) / 100, sList, user);
            countB = tokenizator(pr2, songs, (resSize * 40) / 100, sList, user);
            std::cout << "From the first criteria you have " << countA << " songs!\n";
            std::cout << "From the second criteria you have " << countB << " songs!\n";
            if ((countA + countB) == 0)
            {
                std::cout << "We do not have any good songs for you :(\n\n";
                return;
            }
            resSize -= (countA + countB);
            std::cout << "Your playlist will be with " << (countA + countB) << " songs\n";
        }
        else if (op == "|")
        {
            countA = tokenizator(pr, songs, resSize, sList, user);
            if (countA == 0)
            {
                std::cout << "\nFirst preority didn't find any songs for you!\n\n";
                countB = tokenizator(pr2, songs, resSize, sList, user);
            }
            else
            {
                std::cout << "From the first criteria you have " << countA << " songs!\n";
            }
            if (countB + countA == 0)
            {
                std::cout << "We do not have any good songs for you :(\n\n";
                return;
            }
            else
            {
                std::cout << "Your playlist will be with " << (countA + countB) << " songs\n";
            }
            resSize -= (countB + countA);
        }
    }
    else if (count - 1 == 3)
    {
        int countA = 0, countB = 0, countC = 0;
        std::string pr = instructions.front();
        instructions.pop();
        std::string pr2 = instructions.front();
        instructions.pop();
        std::string pr3 = instructions.front();
        instructions.pop();
        std::string op = logicOp.front();
        logicOp.pop();
        std::string op2 = logicOp.front();
        logicOp.pop();

        if (op == "&" && op2 == "&")
        {
            countA = tokenizator(pr, songs, (resSize * 35) / 100, sList, user);
            countB = tokenizator(pr2, songs, (resSize * 33) / 100, sList, user);
            countC = tokenizator(pr3, songs, (resSize * 32) / 100, sList, user);
            if (countB + countA + countC == 0)
            {
                std::cout << "We do not have any good songs for you :(\n\n";
                return;
            }
            std::cout << "From the first criteria you have " << countA << " songs!\n";
            std::cout << "From the second criteria you have " << countB << " songs!\n";
            std::cout << "From the third criteria you have " << countC << " songs!\n";
            std::cout << "Your playlist will be with " << (countA + countB + countC) << " songs\n";
            resSize -= (countA + countB + countC);
        }
        else if (op == "&" && op2 == "|")
        {
            countA = tokenizator(pr, songs, (resSize * 60) / 100, sList, user);
            std::cout << "From the first criteria you have " << countA << " songs!\n";
            countB = tokenizator(pr2, songs, (resSize * 40) / 100, sList, user);
            if (countB == 0)
            {
                std::cout << "\nSecond preority didn't find any songs for you!\n\n";
                countC = tokenizator(pr3, songs, (resSize * 40) / 100, sList, user);
                std::cout << "From the third criteria you have " << countC << " songs!\n";
            }
            else
            {
                std::cout << "From the second criteria you have " << countB << " songs!\n";
            }
            if (countB + countA + countC == 0)
            {
                std::cout << "We do not have any good songs for you :(\n\n";
                return;
            }
            std::cout << "Your playlist will be with " << (countA + countB + countC) << " songs\n";
            resSize -= (countA + countB + countC);
        }
        else if (op == "|" && op2 == "&")
        {
            countA = tokenizator(pr, songs, (resSize * 60) / 100, sList, user);
            if (countA == 0)
            {
                std::cout << "\nFirst preority didn't find any songs for you!\n\n";
                countB = tokenizator(pr2, songs, (resSize * 60) / 100, sList, user);
                countC = tokenizator(pr3, songs, (resSize * 40) / 100, sList, user);
            }
            else
            {
                std::cout << "From the first criteria you have " << countA << " songs!\n";
            }
            if (countA + countB + countC == 0)
            {
                std::cout << "We do not have any good songs for you :(\n\n";
                return;
            }
            std::cout << "From the second criteria you have " << countB << " songs!\n";
            std::cout << "From the third criteria you have " << countC << " songs!\n";
            std::cout << "Your playlist will be with " << (countA + countB + countC) << " songs\n";

            resSize -= (countB + countC + countA);
        }
        else if (op == "|" && op2 == "|")
        {
            countA = tokenizator(pr, songs, resSize, sList, user);
            if (countA == 0)
            {
                std::cout << "\nFirst preority didn't find any songs for you!\n\n";
                countB = tokenizator(pr2, songs, resSize, sList, user);
                if (countB == 0)
                {
                    std::cout << "\nSecond preority didn't find any songs for you!\n\n";
                    countC = tokenizator(pr3, songs, resSize, sList, user);
                    if (countC == 0)
                    {
                        std::cout << "We do not have any good songs for you :(\n\n";
                        return;
                    }
                }
                else
                {
                    std::cout << "From the second criteria you have " << countB << " songs!\n";
                }

                std::cout << "From the third criteria you have " << countC << " songs!\n";
            }
            else
            {
                std::cout << "From the first criteria you have " << countA << " songs!\n";
            }
            std::cout << "Your playlist will be with " << (countA + countB + countC) << " songs\n";
            resSize -= (countB + countC + countA);
        }
    }
    else if (count - 1 == 4)
    {
        int countA = 0, countB = 0, countC = 0, countD = 0;
        std::string pr = instructions.front();
        instructions.pop();
        std::string pr2 = instructions.front();
        instructions.pop();
        std::string pr3 = instructions.front();
        instructions.pop();
        std::string pr4 = instructions.front();
        instructions.pop();
        std::string op = logicOp.front();
        logicOp.pop();
        std::string op2 = logicOp.front();
        logicOp.pop();
        std::string op3 = logicOp.front();
        logicOp.pop();

        if (op == "&" && op2 == "&" && op3 == "&")
        {
            countA = tokenizator(pr, songs, (resSize * 30) / 100, sList, user);
            countB = tokenizator(pr2, songs, (resSize * 26) / 100, sList, user);
            countC = tokenizator(pr3, songs, (resSize * 24) / 100, sList, user);
            countD = tokenizator(pr4, songs, (resSize * 20) / 100, sList, user);

            if (countB + countA + countC + countD == 0)
            {
                std::cout << "We do not have any good songs for you :(\n\n";
                return;
            }
            std::cout << "From the first criteria you have " << countA << " songs!\n";
            std::cout << "From the second criteria you have " << countB << " songs!\n";
            std::cout << "From the third criteria you have " << countC << " songs!\n";
            std::cout << "From the fourth criteria you have " << countD << " songs!\n";
            std::cout << "Your playlist will be with " << (countA + countB + countC + countD) << " songs";
            resSize -= (countA + countB + countC + countD);
        }
        else if (op == "&" && op2 == "&" && op3 == "|")
        {
            countA = tokenizator(pr, songs, (resSize * 35) / 100, sList, user);
            countB = tokenizator(pr2, songs, (resSize * 33) / 100, sList, user);
            std::cout << "From the first criteria you have " << countA << " songs!\n";
            std::cout << "From the second criteria you have " << countB << " songs!\n";
            countC = tokenizator(pr3, songs, (resSize * 32) / 100, sList, user);
            if (countC == 0)
            {
                std::cout << "\nThird preority didn't find any songs for you!\n\n";
                countD = tokenizator(pr4, songs, (resSize * 32) / 100, sList, user);
                std::cout << "From the fourth criteria you have " << countD << " songs!\n";
            }
            else
            {
                std::cout << "From the third criteria you have " << countC << " songs!\n";
            }
            if (countB + countA + countC + countD == 0)
            {
                std::cout << "We do not have any good songs for you :(\n\n";
                return;
            }
            std::cout << "Your playlist will be with " << (countA + countB + countC + countD) << " songs\n";
            resSize -= (countA + countB + countC + countD);
        }
        else if (op == "&" && op2 == "|" && op3 == "&")
        {
            countA = tokenizator(pr, songs, (resSize * 35) / 100, sList, user);
            std::cout << "From the first criteria you have " << countA << " songs!\n";
            countB = tokenizator(pr2, songs, (resSize * 33) / 100, sList, user);
            if (countB == 0)
            {
                std::cout << "\nSecond preority didn't find any songs for you!\n\n";
                countC = tokenizator(pr3, songs, (resSize * 33) / 100, sList, user);
                std::cout << "From the third criteria you have " << countC << " songs!\n";
            }
            else
            {
                std::cout << "From the second criteria you have " << countB << " songs!\n";
            }

            countD = tokenizator(pr4, songs, (resSize * 32) / 100, sList, user);
            std::cout << "From the fourth criteria you have " << countD << " songs!\n";
            if (countB + countA + countC + countD == 0)
            {
                std::cout << "We do not have any good songs for you :(\n\n";
                return;
            }
            std::cout << "Your playlist will be with " << (countA + countB + countC + countD) << " songs\n";
            resSize -= (countA + countB + countC + countD);
        }
        else if (op == "&" && op2 == "|" && op3 == "|")
        {
            countA = tokenizator(pr, songs, (resSize * 60) / 100, sList, user);
            std::cout << "From the first criteria you have " << countA << " songs!\n";
            countB = tokenizator(pr2, songs, (resSize * 40) / 100, sList, user);
            if (countB == 0)
            {
                std::cout << "\nSecond preority didn't find any songs for you!\n\n";
                countC = tokenizator(pr3, songs, (resSize * 40) / 100, sList, user);
                if (countC == 0)
                {
                    std::cout << "\nThird preority didn't find any songs for you!\n\n";
                    countD = tokenizator(pr4, songs, (resSize * 40) / 100, sList, user);
                }
                else
                {
                    std::cout << "From the third criteria you have " << countC << " songs!\n";
                }
            }
            else
            {
                std::cout << "From the second criteria you have " << countB << " songs!\n";
            }
            if (countB + countA + countC + countD == 0)
            {
                std::cout << "We do not have any good songs for you :(\n\n";
                return;
            }
            std::cout << "Your playlist will be with " << (countA + countB + countC + countD) << " songs\n";
            resSize -= (countA + countB + countC + countD);
        }
        else if (op == "|" && op2 == "&" && op3 == "&")
        {
            countA = tokenizator(pr, songs, (resSize * 35) / 100, sList, user);
            if (countA == 0)
            {
                std::cout << "\nFirst preority didn't find any songs for you!\n\n";
                countB = tokenizator(pr2, songs, (resSize * 35) / 100, sList, user);
                std::cout << "From the second criteria you have " << countB << " songs!\n";
            }
            else
            {
                std::cout << "From the first criteria you have " << countA << " songs!\n";
            }

            countC = tokenizator(pr3, songs, (resSize * 33) / 100, sList, user);
            std::cout << "From the third criteria you have " << countC << " songs!\n";
            countD = tokenizator(pr4, songs, (resSize * 32) / 100, sList, user);
            std::cout << "From the fourth criteria you have " << countD << " songs!\n";
            if (countB + countA + countC + countD == 0)
            {
                std::cout << "We do not have any good songs for you :(\n\n";
                return;
            }
            std::cout << "Your playlist will be with " << (countA + countB + countC + countD) << " songs\n";
            resSize -= (countA + countB + countC + countD);
        }
        else if (op == "|" && op2 == "&" && op3 == "|")
        {
            countA = tokenizator(pr, songs, (resSize * 60) / 100, sList, user);
            if (countA == 0)
            {
                std::cout << "\nFirst preority didn't find any songs for you!\n\n";
                countB = tokenizator(pr2, songs, (resSize * 60) / 100, sList, user);
                std::cout << "From the second criteria you have " << countB << " songs!\n";
            }
            else
            {
                std::cout << "From the first criteria you have " << countA << " songs!\n";
            }

            countC = tokenizator(pr3, songs, (resSize * 40) / 100, sList, user);
            if (countC == 0)
            {
                std::cout << "\nThird preority didn't find any songs for you!\n\n";
                countD = tokenizator(pr4, songs, (resSize * 40) / 100, sList, user);
                std::cout << "From the fourth criteria you have " << countD << " songs!\n";
            }
            else
            {
                std::cout << "From the third criteria you have " << countC << " songs!\n";
            }

            if (countB + countA + countC + countD == 0)
            {
                std::cout << "We do not have any good songs for you :(\n\n";
                return;
            }
            std::cout << "Your playlist will be with " << (countA + countB + countC + countD) << " songs\n";

            resSize -= (countA + countB + countC + countD);
        }
        else if (op == "|" && op2 == "|" && op3 == "&")
        {
            countA = tokenizator(pr, songs, (resSize * 60) / 100, sList, user);
            if (countA == 0)
            {
                std::cout << "\nFirst preority didn't find any songs for you!\n\n";
                countB = tokenizator(pr2, songs, (resSize * 60) / 100, sList, user);
                if (countB == 0)
                {
                    std::cout << "\nSecond preority didn't find any songs for you!\n\n";
                    countC = tokenizator(pr3, songs, (resSize * 60) / 100, sList, user);
                    std::cout << "From the third criteria you have " << countC << " songs!\n";
                }
                else
                {
                    std::cout << "From the second criteria you have " << countB << " songs!\n";
                }
            }
            else
            {
                std::cout << "From the first criteria you have " << countA << " songs!\n";
            }

            countD = tokenizator(pr4, songs, (resSize * 40) / 100, sList, user);
            std::cout << "From the fourth criteria you have " << countD << " songs!\n";
            if (countB + countA + countC + countD == 0)
            {
                std::cout << "We do not have any good songs for you :(\n\n";
                return;
            }
            std::cout << "Your playlist will be with " << (countA + countB + countC + countD) << " songs\n";

            resSize -= (countA + countB + countC + countD);
        }
        else if (op == "|" && op2 == "|" && op3 == "|")
        {
            countA = tokenizator(pr, songs, resSize, sList, user);
            if (countA == 0)
            {
                std::cout << "\nFirst preority didn't find any songs for you!\n\n";
                countB = tokenizator(pr2, songs, resSize, sList, user);
                if (countB == 0)
                {
                    std::cout << "\nSecond preority didn't find any songs for you!\n\n";
                    countC = tokenizator(pr3, songs, resSize, sList, user);
                    if (countC == 0)
                    {
                        std::cout << "\nThird preority didn't find any songs for you!\n\n";
                        countD = tokenizator(pr4, songs, resSize, sList, user);
                        std::cout << "From the fourth criteria you have " << countD << " songs!\n";
                    }
                    else
                    {
                        std::cout << "From the third criteria you have " << countC << " songs!\n";
                    }
                }
                else
                {
                    std::cout << "From the second criteria you have " << countB << " songs!\n";
                }
            }
            else
            {
                std::cout << "From the first criteria you have " << countA << " songs!\n";
            }
            if (countB + countA + countC + countD == 0)
            {
                std::cout << "We do not have any good songs for you :(\n\n";
                return;
            }
            std::cout << "Your playlist will be with " << (countA + countB + countC + countD) << " songs\n";
            resSize -= (countA + countB + countC + countD);
        }
    }
    pl.setList(sList);
    bool nPl = false;
    std::string nameOfPlaylist;
    do
    {
        nPl = false;
        std::cout << "Write name for the newest playlist: ";
        std::getline(std::cin, nameOfPlaylist);
        if (nameOfPlaylist.empty())
        {
            std::cout << "Empty name!! Try again!!!\n";
        }
        else
        {
            nPl = true;
        }

    } while (!nPl);
    pl.setName(nameOfPlaylist);
    std::cout << "Your new playlist is called: " << nameOfPlaylist << " and has " << sList.size() << " songs!!!\n\n";
    user.addPlaylist(pl);
}