#include <curses.h>
#include <unistd.h>
#include "mainScreen.h"

int main(void){
	int a;
	initscr();
	clear();
	a = printmain();
	if (a==0)
	{
		clear();
		addstr("end game..");
		refresh();
		sleep(2);
		endwin();
	}	
	else
		clear();
}
