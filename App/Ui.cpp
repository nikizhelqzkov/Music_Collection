#include "Ui.h"
/**
 * @brief Функция, която извършва основата част от визуалния изглед на приложението
 * 
 */
void UI::start()
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
        std::string systemV;
        int c;

        do
        {
            repeat = false;
            std::cout << "\n\nYour options:\n";
            std::cout << "1)Edit your profile\n";
            std::cout << "2)Add Song to the system\n";
            std::cout << "3)Generate new Playlist\n";
            std::cout << "4)Load Playlist by name\n";
            std::cout << "5)Songs info in your Playlist by name\n";
            std::cout << "6)Set rating to some song\n";
            std::cout << "7)Exit\n\n";
            std::cout << "Choose number from 1 to 7 : ";
            std::getline(std::cin, systemV);

            if (!systemV.empty() && isNumber(systemV))
            {
                c = std::stoi(systemV);
            }
            else
            {
                c = -1;
            }
            if (c == 1)
            {
                std::cout << "\n\nYou choose: Edit your profile!\nChoose one of the options:\n\n";
                bool editRep = false;
                std::string systemF;
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
                    std::getline(std::cin, systemF);
                    if (!systemF.empty() && isNumber(systemF))
                    {
                        cEditProfile = std::stoi(systemF);
                    }
                    else
                    {
                        cEditProfile = -1;
                    }
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
                std::cout << "You chose to add new Playlist to the system!!!\n\n";
                std::cout << "YOUR VALID CRITERIA ARE:\n";
                std::cout << "1)Getting songs higher than your rating (0-10)\n";
                std::cout << "2)Turning on/off some genres to be add in the playlist\n";
                std::cout << "3)Adding songs with your favourtie genre\n";
                std::cout << "4)Getting songs later/equal/before some year\n\n";
                Generator g;
                g.generate(songs, u);
                std::ofstream output(u.getUsername() + ".txt");
                output << u;
                output.close();
                repeat = true;
            }
            else if (c == 4)
            {
                if (u.getPlaylists().size() < 1)
                {
                    std::cout << "YOU DON'T HAVE ANY PLAYLISTST!!!!\n";
                }
                else
                {
                    u.allPlaylistsNames();
                    std::string name;

                    std::cout << "Write the name of the playlist: ";
                    std::getline(std::cin, name);
                    Playlist plR;
                    bool isRead = getPlaylist(u, name, plR);
                    if (!isRead)
                    {
                        std::cout << "That playlist is missing!!! Try again!!!\n";
                    }

                    else
                    {
                        bool moreStartingSong = false;
                        std::string num;
                        std::cout << "Your songs from the playlist: \n";
                        plR.printSongs();
                        do
                        {
                            moreStartingSong = false;
                            std::cout << "Write number of song between 1 and " << plR.getList().size() << ": ";
                            std::getline(std::cin, num);
                            int number = !num.empty() ? std::stoi(num) : -1;
                            if (number < 1 || number > plR.getList().size())
                            {
                                std::cin.ignore();
                                std::cout << "Error number of song! Try again? (y for yes and other word for no): ";
                                std::string isAgain;
                                std::getline(std::cin, isAgain);
                                if (isAgain == "y")
                                {
                                    std::cout << "You will try again!!!\n";
                                    moreStartingSong = true;
                                }
                            }
                            else
                            {
                                printingOneSong(plR, number);
                                std::cout << "Do you want to start other song from this playlist? (y for yes and other word for no): ";
                                std::string isAgain;
                                std::getline(std::cin, isAgain);
                                if (isAgain == "y")
                                {
                                    std::cout << "You will start another song!!!\n";
                                    moreStartingSong = true;
                                }
                            }

                        } while (moreStartingSong);
                    }
                }
                repeat = true;
            }
            else if (c == 5)
            {
                if (u.getPlaylists().size() < 1)
                {
                    std::cout << "YOU DON'T HAVE ANY PLAYLISTST!!!!\n";
                }
                else
                {
                    u.allPlaylistsNames();
                    std::string name;

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
                        std::cin.ignore();
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