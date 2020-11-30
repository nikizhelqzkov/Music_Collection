#include "Login.h"

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
bool Login::userLogin()
{
    std::cout << "WRITE YOUR USERNAME AND PASSWORD \n";
    std::string username;
    std::string password;
    std::cout << "username: ";
    std::cin >> username;
    std::cout << "\npassword: ";
    std::cin >> password;
    std::cout << std::endl;

    if (login(username, password))
    {
        std::cout << "Successful login\n";
        return true;
    }
    else
    {
        std::cout << "Ivalid username or password\n";
        return false;
    }
}