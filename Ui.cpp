//  #include "User.h"
#include "Login.h"
#include "Register.h"

void printingSongs(const std::vector<Song> &sv)
{
    std::ofstream out("Songs.txt");
    out << sv.size() << ";";
    for (auto &&element : sv)
    {
        out << element;
    }
}

void printSongInfo(const User &u, std::string name)
{
    Playlist current;
    int pos = -1;
    bool isHere = false;
    for (int i = 0; i < u.getPlaylists().size(); ++i)
    {
        if (u.getPlaylists()[i].getName() == name)
        {
            pos = i;
            isHere = true;
        }
    }

    if (!isHere)
    {
        std::cout << "This playlist is missing! Try again!!!\n";
    }
    else
    {
        std::cout << "\nYou choose playlist: " << u.getPlaylists()[pos].getName() << "\nThat is your playlists' songs information:\n";
        for (int i = 1; i <= u.getPlaylists()[pos].getList().size(); ++i)
        {
            std::cout << "Song " << i << " -> ";
            u.getPlaylists()[pos].getList()[i - 1].printSongInfo();
            std::cout << std::endl;
        }
    }
}
void start()
{
    std::cout << "WELCOME TO THE MUSIC COLLECTION :)\n";
    std::string lOrR;
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
            if (lOrR == "l")
            {
                login = true;
            }
            else if (lOrR == "r")
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
            Song s;
            countS = s.readHelper(inSongs, countS);
            songs.push_back(s);
        }

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
            std::cout << "\n\nYour options:\n";
            std::cout << "1)Edit your profile\n";
            std::cout << "2)Add Song to the system\n";
            std::cout << "3)Generate new Playlist\n";
            std::cout << "4)Load Playlist by name\n"; //moga da pitam koq pesen da trygne kato nomer ot 1 do size
            std::cout << "5)Songs info in your Playlist by name\n";
            std::cout << "6)Set rating to some song\n";
            std::cout << "7)Exit\n\n";
            std::cout << "Choose number from 1 to 7 : ";
            int c;
            std::cin >> c;
            if (c == 1)
            {
                std::cout << "\n\nYou choose: Edit your profile!\nChoose one of the options:\n\n";
                bool editRep = false;
                do
                {
                    editRep = false;
                    std::cout << "Your options:\n";
                    std::cout << "1)Edit your username\n";
                    std::cout << "2)Edit your password\n";
                    std::cout << "3)Edit your full name\n";
                    std::cout << "4)Edit your born date\n";
                    std::cout << "5)Add more genres\n";
                    std::cout << "6)Remove some genre\n";
                    std::cout << "7)Remove playlist by name\n";
                    std::cout << "8)Back\n";
                    std::cout << "9)Exit the app\n\n";
                    std::cout << "Choose number from 1 to 9 : ";
                    int cEditProfile;
                    std::cin >> cEditProfile;
                    if (cEditProfile == 1)
                    {
                        u.changeUserName();
                        editRep = true;
                    }
                    else if (cEditProfile == 2)
                    {
                        u.changePassword();
                        editRep = true;
                    }
                    else if (cEditProfile == 3)
                    {
                        u.changeFullName();
                        editRep = true;
                    }
                    else if (cEditProfile == 4)
                    {
                        u.changeBornDate();
                        editRep = true;
                    }
                    else if (cEditProfile == 5)
                    {
                        u.addGenre();
                        editRep = true;
                    }
                    else if (cEditProfile == 6)
                    {
                        u.removeGenre();
                        editRep = true;
                    }
                    else if (cEditProfile == 7)
                    {
                        u.removePlaylist();
                        editRep = true;
                    }
                    else if (cEditProfile == 8)
                    {
                        editRep = false;
                        repeat = true;
                    }
                    else if (cEditProfile == 9)
                    {
                        std::cout << "\nYOU CHOOSE EXIT!\n\nHAVE A NICE DAY!!!!\n";
                        return;
                    }
                    else
                    {
                        std::cout << "\nError number! Try again!!!\n\n";
                        editRep = true;
                    }

                } while (editRep);
            }
            else if (c == 2)
            {
                std::cout << "You chose to add new song to the system!!!\n\n";
                Song s;
                s.addingSongInfo();
                songs.push_back(s);
                printingSongs(songs);
                std::cout << "Your song have been added to the system\n";
                repeat = true;
            }
            else if (c == 3)
            {
            }
            else if (c == 4)
            {
            }
            else if (c == 5)
            {
                if (u.getPlaylists().size() < 1)
                {
                    std::cout << "YOU DON'T HAVE ANY PLAYLISTST!!!!\n";
                }
                else
                {
                    std::string name;
                    std::cin.ignore();
                    std::cout << "Write the name of the playlist: ";
                    std::getline(std::cin, name);
                    printSongInfo(u, name);
                }
                repeat = true;
            }
            else if (c == 6)
            {
                std::cout << "You chose to set rating to some valid song!!!\n";

                std::string nameToRate;
                std::cin.ignore();
                std::cout << "Write the name of the song: ";
                std::getline(std::cin, nameToRate);
                bool r = false;
                int pos = -1;
                do
                {
                    r = false;
                    for (int i = 0; i < songs.size(); ++i)
                    {
                        if (songs[i].getTitle() == nameToRate)
                        {
                            bool isVoted = false;
                            for (int j = 0; j < songs[i].getUserRateNames().size(); ++j)
                            {
                                if (u.getUsername() == songs[i].getUserRateNames()[j])
                                {
                                    isVoted = true;
                                }
                            }
                            if (!isVoted)
                            {
                                r = true;
                                pos = i;
                            }
                        }
                    }
                    if (!r)
                    {
                        std::cout << "This song doesn't exists or you have voted it before!!!\n";
                        break;
                    }

                } while (!r);
                if (!r)
                {
                    repeat = true;
                }
                else
                {
                    double ratingS;
                    bool validR = false;
                    do
                    {
                        validR = false;
                        std::cout << "Rate this Song between 0.0 and 10.0: ";
                        std::cin >> ratingS;
                        if (ratingS < 0.0 && ratingS > 10.0)
                        {
                            std::cout << "Error rating!!! Try again? (y for yes and other symbol for no): ";
                            std::string isAgain;
                            std::getline(std::cin, isAgain);
                            if (isAgain != "y")
                            {
                                std::cout << "Ok, exit the rating system!\n\n";
                                break;
                            }
                        }
                        else
                        {
                            validR = true;
                        }
                    } while (!validR);
                    if (!validR)
                    {
                        repeat = true;
                    }
                    else
                    {
                        songs[pos].setAverageRating(ratingS);
                        songs[pos].setRating(ratingS);
                        songs[pos].setUserRateName(u.getUsername());
                        printingSongs(songs);
                        repeat = true;
                    }
                }
            }
            else if (c == 7)
            {
                std::cout << "\nYOU CHOOSE EXIT!\n\nHAVE A NICE DAY!!!!\n";
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
