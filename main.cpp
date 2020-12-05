// #include "User.cpp"
// #include "Date.cpp"
// #include "Playlist.cpp"
// #include "Song.cpp"
// #include<fstream>
#include "User.h"
#include "Login.h"
#include "Register.h"

//g++ main.cpp User.cpp Date.cpp Playlist.cpp Song.cpp Login.cpp Register.cpp

int main()
{
    Date fDate(25, 6, 2000);
    std::vector<std::string> v = {"chalga", "rap"};
    Song s1("Kavala Kuchek", "Krisko", "Chalga", "Krisko", 2020, 9.5);
    Song s2("Nartsis", "Tsvetina ft. Toni", "Chalga", "Tsvetina Collection", 2020, 9);
    Playlist p1("mazno", {s1, s2});
    Playlist p2("mazno2", {s1, s2});
    User niki("nikizhelqzkov", "nikiumnikazdr", "Nikolay Zhelyazkov", fDate, v, {p1, p2});
    // User niki("nikizhelqzkov", "nikiumnikazdr", "Nikolay Zhelyazkov", Date(25, 6, 2000), v, p1);
    niki.setBornDate(Date(25, 7, 2001));
    niki.addTypesOfMusic("Pop");
    //std::cout << niki;

    // std::ofstream output(niki.getUsername() + ".txt");
    // output << niki;
    // output.close();
    // std::cout << std::stoi(" 2020");
    // Register::registrate();
    // Login::userLogin();
    std::ifstream in("nikizhelqzkov.txt");
    User newUser;
    newUser.read(in);
    in.close();
    std::cout << newUser;
    // std::ifstream in("song.txt");
    // Song s("", "", "", "", 0, 0);
    // std::cout << s.read(in)<<std::endl;
    // std::cout << s << std::endl;

    // std::ifstream in("Playlist.txt");
    // Playlist p3("", {});
    // std::cout << p3.read(in)<<std::endl;
    // std::cout << p3;

    return 0;
}