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

        inUser.close();
        std::cout << "SO, YOUR DATA IS FINE!!!\n\nWELCOME TO THE MENU!\nYOU CAN CHOOSE ONE OF THESE OPTION:\n\n";
        bool repeat = false;
        do
        {
            repeat = false;
            std::cout << "\n\nYour option:\n";
            std::cout << "1)Edit your profile\n";
            std::cout << "2)Add Song to the system\n";
            std::cout << "3)Generate new Playlist\n";
            std::cout << "4)Load Playlist by name\n";
            std::cout << "5)Songs info in your Playlist by name\n";
            std::cout << "6)Set rating to some song\n";
            std::cout << "7)Exit\n\n";
            std::cout << "Choose number from 1 to 6 : ";
            int c;
            std::cin >> c;
            if (c == 1)
            {
            }
            else if (c == 2)
            {
            }
            else if (c == 3)
            {
            }
            else if (c == 4)
            {
            }
            else if (c == 5)
            {
            }
            else if (c == 6)
            {
            }
            else if (c == 7)
            {
                std::cout << "\nYOU CHOOSE EXIT!\n\naddiHAVE A NICE DAY!!!!\n";
                return;
            }
            else
            {
                std::cout << "\nError number! Try again!!!\n\n";
                repeat = true;
            }
        } while (repeat);
    }
}