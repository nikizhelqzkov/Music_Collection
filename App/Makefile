
all: play

play: main.o User.o Date.o Playlist.o Song.o Login.o Register.o Generator.o Ui.o Utils.o
	  g++ main.o User.o Date.o Playlist.o Song.o Login.o Register.o Generator.o Ui.o Utils.o -o play

main.o: main.cpp
		g++ -c main.cpp

User.o: User.cpp
		g++ -c User.cpp

Date.o: Date.cpp
		g++ -c Date.cpp
Playlist.o: Playlist.cpp
		g++ -c Playlist.cpp

Song.o: Song.cpp
		g++ -c Song.cpp

Login.o: Login.cpp
		 g++ -c Login.cpp

Register.o: Register.cpp
		    g++ -c Register.cpp

Generator.o: Generator.cpp
			 g++ -c Generator.cpp

Ui.o: Ui.cpp
	  g++ -c Ui.cpp

Utils.o: Utils.cpp
		 g++ -c Utils.cpp
