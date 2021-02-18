#include<ncurses.h>
#include<unistd.h>
using namespace std;
class game_control{
	public :
		game_control();
		final_control();
		void start_screen(int);
		void select();
};
