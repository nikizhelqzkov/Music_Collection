#include <map>
#include "Ui.cpp"
#include <queue>
#include <string>
#include <algorithm>
#include <functional>
bool isHasSong(const std::vector<Song> &songs, const std::string &name)
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
bool isHasGenres(const std::vector<std::string> &list, const std::string &name)
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
bool isNumber(const std::string &s)
{
    return !s.empty() && std::find_if(s.begin(),
                                      s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

bool isDoubleNumber(const std::string &s)
{
    char *end = nullptr;
    strtod(s.c_str(), &end); //funkciq koqto promenq end pointera s \0, ako e uzspeshen casta!!!
    return end != s.c_str() && *end == '\0';
}

int firstCriteria(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList)
{
    // std::cin.ignore();
    std::cout << "You have chosen critetia for rating!";
    std::string r;
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
            return count;
        }
        if (s.getRating() >= rating && !isHasSong(plList, s.getTitle()))
        {
            plList.push_back(s);
            ++count;
            --plRes;
        }
    }
    return count;
}
int pushingViaGenres(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, const std::vector<std::string> &genres)
{
    int plRes = plSize;
    int count = 0;
    for (auto &&s : songs)
    {
        if (count == plSize)
        {
            return count;
        }

        if (isHasGenres(genres, s.getGenres()) && !isHasSong(plList, s.getTitle()))
        {
            plList.push_back(s);
            --plRes;
            ++count;
        }
    }
    return count;
}
int pushingNotViaGenres(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, const std::vector<std::string> &genres)
{
    int plRes = plSize;
    int count = 0;
    for (auto &&s : songs)
    {
        if (count == plSize)
        {
            return count;
        }

        if (!isHasGenres(genres, s.getGenres()) && !isHasSong(plList, s.getTitle()))
        {
            plList.push_back(s);
            --plRes;
            ++count;
        }
    }
    return count;
}
int thirdCriteria(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, const User &u)
{
    //std::cin.ignore();
    std::cout << "You have chosen critetia for only favourite genres!\n";
    int count = pushingViaGenres(songs, plSize, plList, u.getGenres());
    return count;
}
int secondCriteria(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList)
{
    //std::cin.ignore();
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
int fourthCriteria(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList)
{
    //std::cin.ignore();
    std::cout << "You have chosen critetia for year!";
    std::string y;
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
            return count;
        }
        if (bEA == "before")
        {
            if (s.getYear() < year && !isHasSong(plList, s.getTitle()))
            {
                plList.push_back(s);
                --plRes;
                ++count;
            }
        }
        else if (bEA == "equal")
        {
            if (s.getYear() == year && !isHasSong(plList, s.getTitle()))
            {
                plList.push_back(s);
                --plRes;
                ++count;
            }
        }
        else if (bEA == "after")
        {
            if (s.getYear() > year && !isHasSong(plList, s.getTitle()))
            {
                plList.push_back(s);
                --plRes;
                ++count;
            }
        }
    }
    return count;
}
int tokenizator(const std::string &input, const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, const User &u)
{
    //plRes,sList,user
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
    else if (input == "4")
    {
        return fourthCriteria(songs, plSize, plList);
    }
    std::invalid_argument("Error input");
    return -1;
}
void generate(const std::vector<Song> &songs, const User &user)
{
    std::cin.ignore();
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
            pl.setList(sList);
        }
        else
        {
            for (int i = 0; i < size; ++i)
            {
                sList.push_back(songs[i]);
            }
            pl.setList(sList);
        }
    }
    else if (count - 1 == 1)
    {
        std::string cr = instructions.front();
        int countSongs = tokenizator(cr, songs, resSize, sList, user);
        instructions.pop();
        std::cout << "\n\nSIze--> " << sList.size() << "  =  " << count << std::endl;
        //instructions.front() -> vzemane na preoritet , tip na preoritet
        //100% ot pesnite po tozi preoritet dokato ima takiva i posle drgite do size
        //instructions.pop();
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

            // std::cout << "Size-> " << resSize << " , " << (resSize * 60) / 100 << " , " << res40 << "\n";
            countA = tokenizator(pr, songs, (resSize * 60) / 100, sList, user);
            countB = tokenizator(pr2, songs, (resSize * 40) / 100, sList, user);
            resSize -= (countA + countB);
            std::cout << "Sizes: A-> " << countA << " B-> " << countB << "\n";
        }
        else if (op == "|")
        {
            countA = tokenizator(pr, songs, resSize, sList, user);
            if (countA == 0)
            {
                std::cout << "\nFirst preority didn't find any songs for you!\n\n";
                countB = tokenizator(pr2, songs, resSize, sList, user);
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
            resSize -= (countA + countB + countC);
            std::cout << "Sizes: A-> " << countA << " B-> " << countB << " C-> " << countC << "\n";
        }
        else if (op == "&" && op2 == "|")
        {
            countA = tokenizator(pr, songs, (resSize * 60) / 100, sList, user);
            countB = tokenizator(pr2, songs, (resSize * 40) / 100, sList, user);
            if (countB == 0)
            {
                std::cout << "\nSecond preority didn't find any songs for you!\n\n";
                countC = tokenizator(pr3, songs, (resSize * 40) / 100, sList, user);
            }
            resSize -= (countA + countB + countC);

            std::cout << "Sizes: A-> " << countA << " B-> " << countB << " C-> " << countC << "\n";
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

            resSize -= (countB + countC + countA);
            std::cout << "Sizes: A-> " << countA << " B-> " << countB << " C-> " << countC << "\n";
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
                }
            }
            resSize -= (countB + countC + countA);
            std::cout << "Sizes: A-> " << countA << " B-> " << countB << " C-> " << countC << "\n";
        }
        std::cout << "More spaces: " << resSize << "\n";
        for (auto &&s : sList)
        {
            s.printSongInfo();
            std::cout << "\n";
        }
    }
    else if (count - 1 == 4)
    {
        //vzemame chetirite preoriteta chrez front i pop
        // pravim 3 dvoiki i mezdu tqh log operaciq
        //izpulnqvame kato pri count - 2 i imame 30 26 24 20
    }
    //append 2 vectors vector1.insert( vector1.end(), vector2.begin(), vector2.end() );
}