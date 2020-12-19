#ifndef __RANK_H
#define __RANK_H

#include   <stdlib.h>
#include   <stdio.h>
#include   <curses.h>
#include   <string.h>
#include   <unistd.h>
#include   <termios.h>

typedef struct rank{
	char name[10];
	int score;
}rank;


int namecheck(rank *ranklist,char name[]);
int newRank(int score, rank * ranklist);
void get_rank(rank *ranklist);
void set_rank(rank *ranklist);
void printrank(rank * ranklist);
void tty_mode(int how);
void set_cr_echo_mode(void);


#endif
