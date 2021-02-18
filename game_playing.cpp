#include "game_playing.h"
extern int height;
extern int width;
extern int mode;
extern int result;
extern int help;
game_playing::game_playing(){
	result = 3;
	x = 0;
	y = 0;
	flag_number = 0;
	if (mode == 0){
		height = width = 10;
		bombs = 10;
		help = 3;
		total = height * width;
	}
	else{
		height = width = 20;
		bombs = 40;
		help = 5;
		total = height * width;
	}
	vector<int> temp(width);
	for (int i = 0;i < height;i++){
		graph.push_back(temp);
	}
	mvprintw(0,40,"time : ");
	mvprintw(5,40,"press 'c' to open a grid");
	mvprintw(2,40,"press 'f' to set a flag");
	mvprintw(3,40,"press 'h' for a hint! Now hint left : %d",help);
	mvprintw(4,40,"press 'q' to quit");
	mvprintw(1,40,"press 's' to start");
	mvprintw(6,40,"total bombs : %d",bombs);
	mvprintw(7,40,"now flags number : 0");
	refresh();			
    cursor_move();
}

void game_playing::cursor_move(){
	int  instruction;
	time_t t1,t2;
	bool  first_step = true;
	bool win_or_lose = true;
	halfdelay(1);
	while(1){		
		if (win_or_lose == false)
			break;
		move(y,x);
		instruction = getch();
		switch(instruction){
			case KEY_LEFT :
				if (!first_step){
					t2 = time(NULL);
					mvprintw(0,40,"time : %-d",t2-t1);
					refresh();
				}
				if (--x < 0)
					x += width;
					break;
			case KEY_RIGHT :
				if (!first_step){
					t2 = time(NULL);
					mvprintw(0,40,"time : %-d",t2-t1);
					refresh();
				}
				if (++x > width-1)
					x = 0;
					break;
			case KEY_UP :
				if (!first_step){
					t2 = time(NULL);
					mvprintw(0,40,"time : %-d",t2-t1);
					refresh();
				}
				if (--y < 0)
					y += height;
					break;
			case KEY_DOWN :
				if (!first_step){
					t2 = time(NULL);
					mvprintw(0,40,"time : %-d",t2-t1);
					refresh();
				}
				if (++y > height-1)
					y = 0;
					break;
			case ERR :
				if (!first_step){
					t2 = time(NULL);
					mvprintw(0,40,"time : %-d",t2-t1);
					refresh();
				}
				break;
			default :
				if (instruction == 'q')
					return;
				if (first_step){
					game_random(y,x);
					total -= bombs;
					BFS(y,x);
					first_step = false;
					time(&t1);
					t2 = time(NULL);
					mvprintw(0,40,"time : %-d",t2-t1);
					refresh();
				}
				else{		 
					if(gameover_detection(y,x,instruction) == false){
						win_or_lose = false;
					}
					t2 = time(NULL);
					mvprintw(0,40,"time : %-d",t2-t1);
					refresh();
				}
		}
		mvprintw(3,40,"press 'h' for a hint! Now hint left : %d",help);
		mvprintw(7,40,"now flags number : %-3d",flag_number);
		refresh();
		if (total == 0){
			win_or_lose = true;
			break;
		}
	}
		
	if (win_or_lose == false){	
		result = 0;
	}else{
		result  = 1;
	}
}



bool game_playing::gameover_detection(int row,int col,int instruction){
	init_pair(1,COLOR_CYAN, COLOR_WHITE);
	init_pair(2,COLOR_WHITE,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_RED,COLOR_BLACK);
	bool returnflag;
	if (instruction == 'h'){
		int a,b;
		returnflag = true;
		while(help){
			a = rand()%height;
			b = rand()%width;
			if (flag.count({a,b}))
				break;
			if (graph[a][b] != UNCOVER && graph[a][b] != BOMB){
				if (graph[a][b] > 0){
					attron(COLOR_PAIR(4));
					mvprintw(a,b,"%c",graph[a][b]+48);
					attroff(COLOR_PAIR(4));
					BFS(a,b);
				}
				else if (graph[a][b] == 0){
					attron(COLOR_PAIR(2));
					mvprintw(a,b,"%c",graph[a][b]+48);
					attroff(COLOR_PAIR(2));
					BFS(a,b);
				}
				help--;
				break;
			}		
		}
	}
	else if (graph[row][col] == UNCOVER)
		returnflag = true;
	else if (instruction == 'c'){
		if (graph[row][col] == BOMB)
			returnflag =  false;	
		else{
			BFS(row,col);	
			returnflag =  true;
		}
	}
	else{
		if (!flag.count({row,col})){
			flag.insert({row,col});
			attron(COLOR_PAIR(3));
			mvaddch(row,col,'f');
			attroff(COLOR_PAIR(3));
			flag_number++;
		}
		else{
			flag.erase({row,col});
			mvaddch(row,col,' ');
			flag_number--;
		}
		returnflag = true;
	}
	return returnflag;
}


void game_playing::BFS(int row,int col){
	init_pair(1,COLOR_CYAN, COLOR_WHITE);
	init_pair(2,COLOR_WHITE,COLOR_BLACK);
	init_pair(3,COLOR_GREEN,COLOR_BLACK);
	init_pair(4,COLOR_RED,COLOR_BLACK);
	if (graph[row][col] > 0){
		attron(COLOR_PAIR(4));
		mvaddch(row,col,graph[row][col]+48);
		attroff(COLOR_PAIR(4));
		graph[row][col] = UNCOVER;
		total--;
		keypad(stdscr,TRUE);
		return ;
	}
	else if (graph[row][col] == UNCOVER){
		return;
	}
	else{
		queue<pair<int,int>> q;
		q.push({row,col});
		graph[row][col] = UNCOVER;
		int a,b;
		while (!q.empty()){
			a = q.front().first;
			b = q.front().second;
			total--;
			mvaddch(a,b,'0');
			q.pop();
			if (a-1 >= 0 && b-1 >= 0 && !(flag.count({a-1,b-1}))){//左上
				if (graph[a-1][b-1] == 0){
					q.push({a-1,b-1});
					graph[a-1][b-1] = UNCOVER;
				}
				else if (graph[a-1][b-1] > 0){
					attron(COLOR_PAIR(4));
					mvprintw(a-1,b-1,"%c",graph[a-1][b-1]+48);
					attroff(COLOR_PAIR(4));
					graph[a-1][b-1] = UNCOVER;
					total--;
				}
			}

			if (b-1 >= 0 &&!(flag.count({a,b-1}))){//左
				if (graph[a][b-1] == 0){
					q.push({a,b-1});
					graph[a][b-1] = UNCOVER;
				}
				else if (graph[a][b-1] > 0){
					attron(COLOR_PAIR(4));
					mvprintw(a,b-1,"%c",graph[a][b-1]+48);
					attroff(COLOR_PAIR(4));
					graph[a][b-1] = UNCOVER;
					total--;
				}
			}

			if (a+1 < height && b-1 >= 0 &&!(flag.count({a+1,b-1}))){//左下
				if (graph[a+1][b-1] == 0){
					q.push({a+1,b-1});
					graph[a+1][b-1] = UNCOVER;
				}
				else if (graph[a+1][b-1] > 0){
					attron(COLOR_PAIR(4));
					mvprintw(a+1,b-1,"%c",graph[a+1][b-1]+48);
					attroff(COLOR_PAIR(4));
					graph[a+1][b-1] = UNCOVER;
					total--;
				}
			}

			if (a-1 >= 0 &&!(flag.count({a-1,b}))){//中上
				if (graph[a-1][b] == 0){
					q.push({a-1,b});
					graph[a-1][b] = UNCOVER;
				}
					else if (graph[a-1][b] > 0){
						attron(COLOR_PAIR(4));
						mvprintw(a-1,b,"%c",graph[a-1][b]+48);
						attroff(COLOR_PAIR(4));
						graph[a-1][b] = UNCOVER;
						total--;
					}
			}

			if (a+1 < height  &&!(flag.count({a+1,b}))){//中下
				if (graph[a+1][b] == 0){
					q.push({a+1,b});
					graph[a+1][b] = UNCOVER;
				}
				else if (graph[a+1][b] > 0){
					attron(COLOR_PAIR(4));
					mvprintw(a+1,b,"%c",graph[a+1][b]+48);
					attroff(COLOR_PAIR(4));
					graph[a+1][b] = UNCOVER;
					total--;
				}
			}

			if (a-1 >= 0 && b+1 < width  &&!(flag.count({a-1,b+1}))){//右上
				if (graph[a-1][b+1] == 0){
					q.push({a-1,b+1});
					graph[a-1][b+1] = UNCOVER;
				}
				else if (graph[a-1][b+1] > 0){
					attron(COLOR_PAIR(4));
					mvprintw(a-1,b+1,"%c",graph[a-1][b+1]+48);
					attroff(COLOR_PAIR(4));
					graph[a-1][b+1] = UNCOVER;
					total--;
				}
	        }

			if (b+1 < width  &&!(flag.count({a,b+1}))){//右中
				if (graph[a][b+1] == 0){
					q.push({a,b+1});
					graph[a][b+1] = UNCOVER;
				}
				else if (graph[a][b+1] > 0){
					attron(COLOR_PAIR(4));
					mvprintw(a,b+1,"%c",graph[a][b+1]+48);
					attroff(COLOR_PAIR(4));
					graph[a][b+1] = UNCOVER;
					total--;
				}
			}

			if (a+1 < height && b+1 < width &&!(flag.count({a+1,b+1}))){//右下
				if (graph[a+1][b+1] == 0){
					q.push({a+1,b+1});
					graph[a+1][b+1] = UNCOVER;
				}
				else if (graph[a+1][b+1] > 0){
					attron(COLOR_PAIR(4));
					mvprintw(a+1,b+1,"%c",graph[a+1][b+1]+48);
					attroff(COLOR_PAIR(4));
					graph[a+1][b+1] = UNCOVER;
					total--;
				}	
			}
		}
	}
}


	
void game_playing::game_random(int row,int col){
	queue<pair<int,int>> temp_queue;
	int index = 0;
	set<pair<int,int>> temp_set;
	while (index < bombs){
		pair<int,int> temp_pair;
		temp_pair.first = rand()%height;
		temp_pair.second = rand()%width;
		if (!temp_set.count(temp_pair) && temp_pair.first != row && temp_pair.second != col){
			temp_set.insert(temp_pair);
			graph[temp_pair.first][temp_pair.second] = BOMB;
			temp_queue.push(temp_pair);
			index++;
		}
	}

	while (!temp_queue.empty()){
		pair<int,int> temp_pair;
		temp_pair = temp_queue.front();
		temp_queue.pop();
				
		int d = temp_pair.first;
		int e = temp_pair.second;

		if (d-1 >= 0 && e-1 >= 0 && graph[d-1][e-1] != BOMB){//左上
			graph[d-1][e-1]++;
		}

		if (e-1 >= 0 && graph[d][e-1] != BOMB){//左
			graph[d][e-1]++;
		}

		if (d+1 < height && e-1 >= 0 && graph[d+1][e-1] != BOMB){//左下
			graph[d+1][e-1]++;
		}
				
		if (d-1 >= 0 && graph[d-1][e] != BOMB){//中上
			graph[d-1][e]++;
		}

		if (d+1 < height && graph[d+1][e] != BOMB){//中下
			graph[d+1][e]++;
		}
		if (d-1 >= 0 && e+1 < width && graph[d-1][e+1] != BOMB){//右上
			graph[d-1][e+1]++;
		}

		if (e+1 < width && graph[d][e+1] != BOMB){//右中
			graph[d][e+1]++;
		}

		if (d+1 < height && e+1 < width && graph[d+1][e+1] != BOMB){//右下
			graph[d+1][e+1]++;	
		}
	}
	
	fstream file;
	file.open("Mine.txt",ios::out);
	for (int i = 0;i < height;i++){
		for (int j = 0; j < width;j++){
			if (graph[i][j] == -2)
				file << 'b';
			else
				file << graph[i][j];
				
		}
		file << '\n';
	}
	file.close();
	
}

