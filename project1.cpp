#include<iostream>
#include "game_control.h"
#include "game_playing.h"
int height;
int width;
int mode;
int result;
int help;
int main(){
	srand(time(NULL));
	game_control A;
	game_playing B;
	A.final_control();
	return 0;
}
