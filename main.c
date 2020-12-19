#include <curses.h>
#include <unistd.h>
#include "rank.h"
#include "mainScreen.h"

#define SIZE 30

int main(void){
	int a;
	rank ranklist[SIZE];
	get_rank(ranklist);
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
		return 0;
	}	
	clear();
	tty_mode(0);
	set_cr_echo_mode();
	newRank(5,ranklist);
	tty_mode(1);
	printrank(ranklist);
	set_rank(ranklist);
	sleep(8);
	endwin();
	
}
