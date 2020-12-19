#ifndef RANK_H
#define RANK_H

#include   <stdlib.h>
#include   <stdio.h>
#include   <curses.h>
#include   <string.h>
#include   <unistd.h>
#include   <termios.h>
#include "rank.h"

#define SIZE 30
typedef struct rank{
	char name[10];
	int score;
}rank;

int namecheck(rank *ranklist,char name[]);
int newRank(int score, rank * ranklist);
void initialrank(rank *ranklist);
void printrank(rank * ranklist);
void tty_mode(int how);
void set_cr_echo_mode(void);

#endif RANK_H
