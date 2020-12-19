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


int newRank(int score, rank *ranklist){
	rank temp;
	int i;
	move(0,5);
	addstr("if you want to check your ranking, enter your nickname\n");
	refresh();
	move(1,5);
	addstr("nickname : ");
	getstr(temp.name);
	refresh();
	temp.score = score;

	for(i = 0 ;i<SIZE;i++){
   		if(temp.score > ranklist[i].score){
      			for(int j = SIZE-1; j>i;j--){
         			ranklist[j] = ranklist[j-1];
      			}
      			ranklist[i] = temp;
      			break;
   		}
	}
	if(i==SIZE)
   		addstr("your score is out of rankings :(\n try again!");

}
void initialrank(rank *ranklist){
   for(int i=0;i<SIZE;i++){
      strcpy(ranklist[i].name ,"\0");
      ranklist[i].score = 0;
   }
}
void printrank(rank * ranklist){
   int i = 0;
   char score[50];
   char explain[50];
   sprintf(explain,"%7s%17s%18s","RANK","NAME","SCORE");
   move(3,5);
   addstr(explain);
   move(4,5);
   addstr("=================================================\n");
   refresh();
   while( strcmp(ranklist[i].name, "\0") ){
   	move(i+5,5);
	sprintf(score,"%5d%18s%18d",i+1,ranklist[i].name,ranklist[i].score);
	addstr(score);
   	refresh();
	i++;
   }
}
void tty_mode(int how)
{
/*how == 0 => save current mode, how == 1 => restore mode*/
	static struct termios original_mode;
	if( how == 0)
		tcgetattr(0,&original_mode);
	else
		tcsetattr(0,TCSANOW, &original_mode);
}
void set_cr_echo_mode(void){
	struct termios ttystate;
	tcgetattr(0,&ttystate);

	ttystate.c_lflag |= (ECHO | ICANON);

	tcsetattr(0,TCSANOW,&ttystate);
}

