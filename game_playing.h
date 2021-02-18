#include<ncurses.h>
#include<vector>
#include<set>
#include<queue>
#include<ctime>
#include<utility>
#include<ctime>
#include<iostream>
#include<fstream>
#define BOMB -2
#define UNCOVER -1
using namespace std;
class game_playing{
	public :
		int bombs;
		int total;
		int x,y;
		int flag_number;
		vector<vector<int>> graph;
		set<pair<int,int>> flag;
		
		game_playing();
		void cursor_move();
		bool gameover_detection(int,int,int);
		void BFS(int,int);
		void game_random(int,int);
};
