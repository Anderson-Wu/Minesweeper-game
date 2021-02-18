game.exe: game_playing.o game_control.o project1.o
	g++ -o game project1.o game_control.o game_playing.o -lncurses
	
game_control.o: game_control.cpp game_control.h
	g++ -c game_control.cpp -lncurses
	
game_playing.o: game_playing.cpp game_playing.h
	g++ -c game_playing.cpp -lncurses
	
project1.o: project1.cpp game_control.o game_playing.o
	g++ -c project1.cpp -lncurses

clean :
	rm game_control.o game_playing.o project1.o Mine.txt game.exe
