#include "Register.h"
/**
 * @brief Функция, която създава нов профил на потребителя
 * 
 * @return true 
 * @return false 
 */
bool Register::registrate()
{
    std::cin.ignore();

    std::string username;
    bool isBusyReg = false;
    do
    {
        isBusyReg = false;
        std::cout << "Write your username: ";
        std::getline(std::cin, username);
        std::ifstream in(username + ".txt");
        if (in.is_open())
        {
            isBusyReg = true;
            std::cout << "This username is busy\n\n";
        }
    } while (isBusyReg);
    std::cout << "\nWrite your password: ";
    std::string password;
    std::getline(std::cin, password);
    std::cout << "Write your full name: ";
    std::string fullName;
    std::getline(std::cin, fullName, '\n');
    std::cout << "\nEnter your date of birth:\n";
    Date regDate;
    regDate.read();
    std::cout << "Enter your favourite genre:\n";
    std::vector<std::string> genres;
    std::string c;

    do
    {
        std::string genre;
        std::cout << "Genre: ";
        std::getline(std::cin, genre, '\n');
        genres.push_back(genre);
        std::cout << "Do you want more genres(y,n): ";

        do
        {

            std::getline(std::cin, c);
            if (c == "y")
            {
                std::cout << "Ok :)\n";
            }
            else if (c == "n")
            {
                std::cout << "Ok :(\n";
            }
            else
            {
                std::cout << "Error symbol! Try again!!!\n";
            }
        } while (c != "y" && c != "n");
    } while (c == "y");

    User user;
    user.setUsername(username);
    user.setPassword(password);
    user.setFullName(fullName);
    user.setBornDate(regDate);
    user.setGenres(genres);
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
/**
 * @brief Мутатор извеждащ стойността на член-данната userName;
 * 
 * @return std::string 
 */
std::string Register::getUsername() const
{
    return userName;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната userName
 * 
 * @param _username 
 */
void Register::setUsername(std::string _username)
{
    userName = _username;
}
