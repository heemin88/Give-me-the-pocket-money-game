#include   <stdlib.h>
#include   <stdio.h>
#include   <curses.h>
#include   <string.h>
#include   <unistd.h>
#include   <termios.h>
#include "rank.h"

#define SIZE 30


int namecheck(rank *ranklist,char name[]){
	int i;
	for(i=0;i<SIZE;i++){
		if(strcmp(ranklist[i].name, name)==0)
			return 1;
	}
	return 0;
}
int newRank(int score, rank *ranklist){
	rank temp;
	int i;
	move(0,5);
	addstr("if you want to check your ranking, enter your nickname\n");
	refresh();
	while(1){
		
		move(1,5);
		addstr("nickname : ");
		getstr(temp.name);
		refresh();
		move(2,5);
		addstr("                                                               ");
		if(namecheck(ranklist,temp.name)==0)
			break;
		else
		{
			move(2,5);
			addstr("The same nickname already exists. Please re-enter.");
			refresh();
		}
	}
	temp.score = score;

	for(i = 0 ;i<SIZE;i++){
   		if(temp.score >=ranklist[i].score){
      			for(int j = SIZE-1; j>i;j--){
         			ranklist[j] = ranklist[j-1];
      			}
      			ranklist[i] = temp;
      			break;
   		}
	}
	if(i==SIZE){
		move(2,5);
   		addstr("your score is out of rankings :(\n try again!");
   		refresh();
   	}

}
void get_rank(rank *ranklist){
	int i = 0;
	FILE * fp = fopen("ranklist.txt","r");
	while(1){
		if(feof(fp))
			break;
		fscanf(fp,"%s %d\n", ranklist[i].name, &ranklist[i].score);
		i++;	
	}
	for(i; i<SIZE; i++){
		strcpy(ranklist[i].name,"\0");
		ranklist[i].score = 0;
	}
	fclose(fp);
}
void set_rank(rank *ranklist){
	FILE *fp = fopen("ranklist.txt","w");
	for(int i = 0; i<SIZE ; i++){
		if(!strcmp(ranklist[i].name,"\0"))
			break;
		fprintf(fp, "%s %d\n", ranklist[i].name, ranklist[i].score);
	}
	fclose(fp);
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

