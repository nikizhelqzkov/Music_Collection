#include "User.h"

//g++ main.cpp User.cpp Date.cpp

int main()
{
    Date fDate(25, 6, 2000);
    std::cout << fDate << std::endl;
    std::vector<std::string> v = {"chalga", "rap"};
    User niki("nikizhelqzkov", "nikiumnikazdr", "Nikolay Zhelyazkov", Date(25, 6, 2000), {"chalga", "rap"});
    User kiki = niki;
    std::cout << kiki.getFullName() << std::endl;
    niki.setBornDate(Date(25, 7, 2001));
    niki.addTypesOfMusic("Pop");
    std::cout << niki.getBornDate();
    std::cout << "Types of music: ";
    for (auto &&types : niki.getTypesOfMusic())
    {
        std::cout << types << " ";
    }

    return 0;
}