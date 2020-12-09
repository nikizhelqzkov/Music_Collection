#include "Register.h"

bool Register::registrate()
{

    std::string username;
    bool isBusyReg = false;
    do
    {
        isBusyReg = false;
        std::cout << "Write your username: ";
        std::cin >> username;
        std::ifstream in(username + ".txt");
        if (in.is_open())
        {
            isBusyReg = true;
            std::cout << "This username is busy\n\n";
        }
    } while (isBusyReg);
    std::cout << "\nWrite your password: ";
    std::string password;
    std::cin >> password;
    std::cin.ignore();
    std::cout << "Write your full name: ";
    std::string fullName;
    std::getline(std::cin, fullName, '\n');
    std::cout << "\nEnter your date of birth:\n";
    Date regDate;
    regDate.read();
    std::cout << "Enter your favourite genre:\n";
    std::vector<std::string> genres;
    char c;

    do
    {
        std::cin.ignore();
        std::string genre;
        std::cout << "Genre: ";
        std::getline(std::cin, genre, '\n');
        genres.push_back(genre);
        std::cout << "Do you want more genres(y,n): ";

        do
        {
            std::cin >> c;

            switch (c)
            {
            case 'y':
                std::cout << "Ok :)\n";
                break;
            case 'n':
                std::cout << "Ok :(\n";
                break;
            default:
                std::cout << "Error symbol! Try again!!!\n";
                break;
            }
        } while (c != 'y' && c != 'n');
    } while (c == 'y');
    Playlist p("", {});
    User user(username, password, fullName, regDate, genres, {p});
    std::ofstream output(username + ".txt");
    if (!output.is_open())
    {
        std::cerr << "Error with opening file \n";
        return false;
    }
    if (output.fail())
    {
        std::cerr << "Error \n";
        return false;
    }
    else
    {
        
        output << user;
        std::cout << "SUCCESSFUL REGISTRATION!!!\n";
        output.close();
        Register n;
        setUsername(username);
        return true;
    }
}
std::string Register::getUsername() const
{
    return userName;
}
void Register::setUsername(std::string _username)
{
    userName = _username;
}
