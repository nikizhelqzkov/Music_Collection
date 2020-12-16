#include <map>
#include "Ui.cpp"
#include <queue>
#include <string>
#include <algorithm>

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

int firstCriterii(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList)
{
    std::cin.ignore();
    std::cout << "You have chosen critetii for rating!";
    std::string r;
    double rating;
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
        if (plList.size() == plSize)
        {
            return 0;
        }
        if (s.getRating() >= rating)
        {
            plList.push_back(s);
            --plRes;
        }
    }
    return plRes;
}
int pushingViaGenres(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, const std::vector<std::string> &genres)
{
    int plRes = plSize;
    for (auto &&s : songs)
    {
        if (plList.size() == plSize)
        {
            return 0;
        }
        if (std::binary_search(genres.begin(), genres.end(), s.getGenres()))
        {
            plList.push_back(s);
            --plRes;
        }
    }
    return plRes;
}
int thirdCriterii(const std::vector<Song> &songs, const int &plSize, std::vector<Song> &plList, User &u)
{
    std::cin.ignore();
    std::cout << "You have chosen critetii for only favourite genres!";
    int plRes = pushingViaGenres(songs, plSize, plList, u.getGenres());
    return plRes;
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
        size = std::stoi(sizeOfP);
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
        criteria = std::stoi(sCr);
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

        if (cr == "1")
        {
            resSize = firstCriterii(songs, resSize, sList);
        }
        instructions.pop();
        //instructions.front() -> vzemane na preoritet , tip na preoritet
        //100% ot pesnite po tozi preoritet dokato ima takiva i posle drgite do size
        //instructions.pop();
    }
    else if (count - 1 == 2)
    {
        //vzemame 2 preoriteta chrez front i pop
        //vzemame front na log op
        //ako e | -> 1 preoritet e s predimstvo , no ako nqma pesen za nego raboti vtoriq
        // ako e && -> 50% za vseki preoritet pochvaiki ot purviq i ako ima mqsto shte se dobavqt oshte ot purviq
    }
    else if (count - 1 == 3)
    {
        //vzemame trite preoriteta chrez front i pop
        //vzemame 2 dvoiki i mezdu tqh log operaciq
        //izpulnqvame sushtoto kato pri count - 2 i imame 35% 33% 32%
    }
    else if (count - 1 == 4)
    {
        //vzemame chetirite preoriteta chrez front i pop
        // pravim 3 dvoiki i mezdu tqh log operaciq
        //izpulnqvame kato pri count - 2 i imame 30 26 24 20
    }
}