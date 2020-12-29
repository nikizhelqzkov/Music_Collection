#ifndef LOGIN_INCLUDED
#define LOGIN_INCLUDED
#include "User.h"
#include <fstream>
/**
 * @brief Класа логин е направен за проверка дали даден потребител има профил в ситемата или не
 * 
 */
class Login
{
private:
  bool login(std::string username, std::string password);
  std::string userName;

public:
  Login() = default;
  ~Login() = default;
  bool userLogin();
  std::string getUsername() const;
  void setUsername(std::string username);
};

#endif