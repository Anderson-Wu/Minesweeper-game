#include "game_control.h"
extern int height;
extern int width;
extern int mode;
extern int result;
extern int help;

game_control::game_control(){
	initscr();
	cbreak();
	noecho();
	keypad(stdscr,TRUE);
	start_screen(2);
	select();
}

void game_control::start_screen(int i){
	while(i--){
		erase();
		printw("                    Welcome to play Minesweeper game ~                                  \n\n");
        printw("               /|__/|                                ,-.__.-,                           \n");
        printw("              / 0,0  |                              (``-''-//).___..--'''`-._           \n");
    	printw("            /_____   |                               `6_ 6  )   `-.  (     ).`-.__.`)   \n");
        printw("           /^ ^ ^ \\  |                              (_Y_.)'  ._   )  `._ `. ``-..-'    \n");
	  	printw("          |^ ^ ^ ^ |w|                          _..`--'_..-_/  /--'_.' ,'               \n");
    	printw("           \\m___m__|_|                        (il),-''  (li),'  ((!.-'                 \n");
	    printw("                                                                                        \n");
		printw("               EASY                                            HARD                     \n");
		refresh();
		sleep(1);
		erase();
		printw("                    Welcome to play Minesweeper game ~                                  \n\n");
    	printw("               /|__/|                                ,-.__.-,                           \n");
        printw("              / -,-  |                              (``-''-//).___..--'''`-._           \n");
	    printw("            /_____   |                               `I_ I  )   `-.  (     ).`-.__.`)   \n");
    	printw("           /^ ^ ^ \\  |                              (_Y_.)'  ._   )  `._ `. ``-..-'    \n");
        printw("          |^ ^ ^ ^ |w|                          _..`--'_..-_/  /--'_.' ,'               \n");
	    printw("           \\m___m__|_|                        (il),-''  (li),'  ((!.-'                 \n");
		printw("                                                                                        \n");
		printw("               EASY                                            HARD                     \n");
		refresh();
		sleep(1);
	}	
}	


void game_control::select(){
	int c;
	int direct = 0;
	start_color();
	int row,col;
	init_pair(1,COLOR_CYAN, COLOR_WHITE);
	init_pair(2,COLOR_WHITE,COLOR_BLACK);
	attron(COLOR_PAIR(1));
	mvprintw(9,15,"EASY");
	attroff(COLOR_PAIR(1));
	refresh();
	while(1){
		c = getch();
		switch (c){
			case KEY_LEFT : 
				attron(COLOR_PAIR(2));
                mvprintw(9,63,"HARD");
                attroff(COLOR_PAIR(2));
				attron(COLOR_PAIR(1));
              	mvprintw(9,15,"EASY");
              	attroff(COLOR_PAIR(1));
				break;
			case KEY_RIGHT : 
				attron(COLOR_PAIR(2));
                mvprintw(9,15,"EASY");
                attroff(COLOR_PAIR(2));
                attron(COLOR_PAIR(1));
                mvprintw(9,63,"HARD");
                attroff(COLOR_PAIR(1));
				break;
			    
			default :
				getyx(stdscr,row,col);
				mvprintw(0,0,"%d",col);
				if (col == 67){
					mode =  1;
				erase();
				printw("                    |\n");
				printw("                    |\n");
			    printw("                    |\n");
				printw("                    |\n");
				printw("                    |\n");
				printw("                    |\n");
				printw("                    |\n");
				printw("                    |\n");
			    printw("                    |\n");
				printw("                    |\n");
				printw("                    |\n");
				printw("                    |\n");
				printw("                    |\n");
				printw("                    |\n");
			    printw("                    |\n");
				printw("                    |\n");
				printw("                    |\n");
				printw("                    |\n");
				printw("                    |\n");
				printw("                    |\n");
				printw("____________________|");					
				}
				else{
					mode  = 0;
				erase();
				printw("          |\n");
				printw("          |\n");
			    printw("          |\n");
				printw("          |\n");
				printw("          |\n");
				printw("          |\n");
				printw("          |\n");
				printw("          |\n");
				printw("          |\n");
			    printw("          |\n");
				printw("__________|");

				}

				refresh();
					return;
		}
		refresh();
	} 			
}	

game_control::final_control(){
	erase();
	if (result == 0)
	    mvprintw(0,0,"                   Oh no, you lose it~            ");
	else if (result == 3)
		mvprintw(0,0,"                   You press quit ");
	else 
		mvprintw(0,0,"                   Congratulations !!! you are Minesweeper professor~   ");
	refresh();
	sleep(5);
	endwin();
	
	
	
}
	
