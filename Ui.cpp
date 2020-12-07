//  #include "User.h"
#include "Login.h"
#include "Register.h"

void start()
{
    std::cout << "WELCOME TO THE MUSIC COLLECTION :)\n";
    char lOrR;
    bool login = false, reg = false;
    bool isOk = false;
    std::string file;
    do
    {
        do
        {
            login = false;
            reg = false;
            std::cout << "Chooose Login(l) or Register(r)\n l or r: ";
            std::cin >> lOrR;
            if (lOrR == 'l')
            {
                login = true;
            }
            else if (lOrR == 'r')
            {
                reg = true;
            }
            else
            {
                std::cout << "Error symbol!!! Try again!!! \n";
            }
        } while (!login && !reg);

        if (login)
        {
            isOk = false;
            Login log;
            if (log.userLogin())
            {
                isOk = true;
                file = log.getUsername() + ".txt";
            }
            else
            {
                std::cout << "\n\n Try again\n\n";
            }
        }

        else
        {
            Register reg;
            if (reg.registrate())
            {
                isOk = true;
                file = reg.getUsername() + ".txt";
            }
            else
            {
                std::cout << "\n\n Try again\n\n";
            }
        }
    } while (!isOk);

    if (isOk)
    {
        std::vector<Song> songs;

        //chetene na pesni
        std::ifstream inSongs("Songs.txt");
        if (inSongs.is_open())
        {
            std::cout << "Openining song source!!!\n\n";
        }
        else
        {
            "Problem with songs source!!! :(\n\n";
        }
        int countS = 0;
        std::string songS;
        std::getline(inSongs, songS, ';');
        countS += songS.size() + 1;
        int sizeSongs = std::stoi(songS);
        inSongs.seekg(countS);
        for (int i = 0; i < sizeSongs; ++i)
        {
            Song s("", "", "", "", 0, 0);
            countS = s.readHelper(inSongs, countS);
            songs.push_back(s);
        }

        //chetene operacii

        inSongs.close();
        std::ifstream inUser(file);
        std::cout << "Openining User's data!!!\n\n";
        User u;
        u.read(inUser);
    }
}