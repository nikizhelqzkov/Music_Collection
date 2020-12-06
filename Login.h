#ifndef LOGIN_INCLUDED
#define LOGIN_INCLUDED
#include "User.h"
#include <fstream>
class Login
{
private:
  bool login(std::string username, std::string password);
  std::string userName;

public:
  Login() = default;

  bool userLogin();
  std::string getUsername()const;
  void setUsername(std::string username);
};

#endif