//  #include "User.h"
#include "Login.h"
#include "Register.h"

void start()
{
    std::cout << "WELCOME TO THE MUSIC COLLECTION :)\n";
    char lOrR;
    bool login = false, reg = false;
    bool isOk = false;
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
                std::vector<Song> songs;
                //chetene na pesni
                std::ifstream inSongs("Songs.txt");
                //chetene operacii

                inSongs.close();
                std::string file;

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
                std::vector<Song> songs;
                //chetene na pesni
                std::ifstream inSongs("Songs.txt");
                //chetene operacii
                std::cout << "Openining song source!!!\n\n";
                inSongs.close();
                std::string file;

                file = reg.getUsername() + ".txt";
                std::cout << reg.getUsername();
                std::ifstream inUser(file);
                std::cout << "Openining User's data!!!\n\n";
                User u;
                u.read(inUser);
            }
            else
            {
                std::cout << "\n\n Try again\n\n";
            }
        }
    } while (!isOk);
}