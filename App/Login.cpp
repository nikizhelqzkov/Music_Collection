#include "Login.h"
/**
 * @brief Помощна функция, която проверява дали потребителя има профил в системата
 * 
 * @param username 
 * @param password 
 * @return true 
 * @return false 
 */
bool Login::login(std::string username, std::string password)
{
    std::ifstream input(username + ".txt");
    if (!input.is_open())
    {
        return false;
    }
    int res = 10 + username.size() + 11;
    input.seekg(res);
    std::string userPass;
    std::getline(input, userPass, ';');
    return userPass == password;
}
/**
 * @brief UI за логин на потребител и връща отговор дали е логнат успешно или не
 * 
 * @return true 
 * @return false 
 */
bool Login::userLogin()
{
    std::cout << "WRITE YOUR USERNAME AND PASSWORD \n";
    std::cin.ignore();
    std::string username;
    std::string password;
    std::cout << "username: ";
    std::getline(std::cin, username);
    std::cout << "\npassword: ";
    std::getline(std::cin, password);
    std::cout << std::endl;

    if (login(username, password))
    {
        std::cout << "Successful login\n";
        Login n;
        setUsername(username);
        return true;
    }
    else
    {
        std::cout << "Ivalid username or password\n";
        return false;
    }
}
/**
 * @brief Мутатор извеждащ стойността на член-данната userName;
 * 
 * @return std::string 
 */
std::string Login::getUsername() const
{
    return userName;
}
/**
 * @brief Мутатор с аргумент, който се вкарва в член-данната userName
 * 
 * @param _username 
 */
void Login::setUsername(std::string _username)
{
    userName = _username;
}