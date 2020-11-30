#ifndef LOGIN_INCLUDED
#define LOGIN_INCLUDED
#include "User.h"
#include <fstream>
 class Login
 {
 private:
   static bool login(std::string username, std::string password);
 public:
    static bool userLogin();
 };
 
 
 


#endif