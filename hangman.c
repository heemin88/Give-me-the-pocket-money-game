#include <unistd.h>

#include <fcntl.h>

#include <sys/stat.h>

#include <sys/types.h>

#include <stdlib.h>

#include <stdio.h>

#include <string.h>

#include <time.h>

#include <curses.h>

#include <sys/time.h>

#include <unistd.h>
#include <signal.h>

#define location_x 33

#define location_y 13

#define MAX 50

#define N "                                                        "

//num:random 수 ,line:word[num]의 글자수 , location_x/location_y: _ _ _ _첫번째 위치

 

char ans;

void handler();

static int money =0;//누적된 돈

int chance =1000; //한 게임마다 얻을 수 있는 용돈

int num; //랜덤으로 들고오는 값

int line; //글자수

char word[MAX][MAX]={0,};

char mean[MAX][MAX]={0,};

FILE *fp;

void gameStart();

char money1[5],chance1[5],i1[5];

int valid(char* , const char* ,int ,int[]);

int check_value(int[] ,int );

void handler2(){
	clear();
	refresh();
	endwin();
	exit(1);
}


int main()

{
    gameStart();
}

 

void gameStart(){

    fp = fopen("words.txt","r");
    if(fp==0){
        fprintf(stderr,"file open error\n");
        exit(1);
    }

    for (int i = 0 ; i < 50 ; i ++){
        fscanf(fp,"%s %s",word[i],mean[i]);
    }
    signal(SIGINT,handler);
    signal(SIGQUIT,handler2);
    while(1){

 	initscr();
        clear();

        if(ans =='n'){
            break;
        }
        
        line =0;
        move(0,50);
        addstr("Press Ctrl-c to end the game.");
        refresh();
        srand(time(NULL));
        //num=0;
        num = rand()%50;
        for(int i =0 ;word[num][i]!=0;i++){
            line ++;
        }

        int value[line];

        chance = 1000;

        for(int i=0;i<line;i++){
              value[i]=0;
        }

        for(int i=0;i<10;i++){
            if(ans == 'n'){
                break;
            }

            move(1,2);
            addstr(N);
            move(1,2);
            addstr("<playing...>");
            sprintf(i1,"%d",(10-i));
            move(27,68);
            addstr("count: ");
            addstr(i1);
            addstr(N);
            sprintf(money1,"%d",money);
            sprintf(chance1,"%d",chance);
            move(28,27);
            addstr("total_money: ");
            addstr(money1);
            addstr("     ");
            addstr("the money that you can get: ");
            addstr(chance1);
            addstr(N);
            if(chance!=0){
                for(int i=0;i<line;i++){
                    move(location_y,location_x+(i*2));
                    addstr("_");
                }
                refresh();
                int compare;
                char input[1];
                move(15,33);
                addstr("push: ");
                refresh();
                scanf("%c",input);
                compare=valid(input,word[num],line,value);
                if(compare==0){
                	move(21,2);
			addstr("   *   *   ");
			move(23,2);
			addstr(N);
			move(23,2);
			addstr("    * *");
			move(24,2);
			addstr(N);
			move(24,2);
			addstr("  *     *");
			move(25,2);
			addstr(N);
			move(25,2);
			addstr(" *       *");

                    move(7,31);
                    addstr("no...try again");
                    addstr("    ");
                    for(int k=0;k<14;k++){
                        move(6,31+k);
                        addstr("-");
                        move(8,31+k);
                        addstr("-");
                    }

                    chance=chance-100;

                }else{

                    move(7,30);
                    addstr(N);
                    move(6,30);
                    addstr(N);
                    move(8,30);
                    addstr(N);
                    
                    
                    move(21,2);
                    addstr("   *   *   ");
                    move(23,2);
                    addstr(N);
                    move(23,2);
                    addstr(" *       *");
                    move(24,2);
                    addstr(N);
                    move(24,2);
                    addstr("  *     *");
                    move(25,2);
                    addstr(N);
                    move(25,2);
                    addstr("    * *");
                    move(7,36);
                    addstr("yes!!");
                    addstr(N);

                    for(int k=0;k<5;k++){
                        move(6,36+k);
                        addstr("-");
                        addstr(N);
                        move(8,36+k);
                        addstr("-");
                        addstr(N);
                    }
                i=i-1;
                }

            }

            if(check_value(value,line)==0){

                move(3,50);
                addstr("meaning: ");
                addstr(mean[num]);
                refresh();
                break;

            }
        }
        if(chance ==0){
        
        	move(6,50);
        	addstr(N);
        	move(6,50);
        	addstr("result: ");
        	addstr(word[num]);
        	refresh();
        	sleep(3);
        	
        	chance=0;
        	sprintf(i1,"%d",chance);
        	move(27,68);
        	addstr("count: ");
        	addstr(i1);
        	
        	
        	clear();
        	move(location_y,location_x);
		addstr("         ");
		move(location_y+1,location_x);
		addstr("you are lose...");
		move(location_y+2,location_x);
		addstr("bye!");
		refresh();
		sleep(3);
        	
        
        	endwin();
                break;
            }

        move(1,2);
        addstr(N);
        move(1,2);
        addstr("<done...>");
	
        money=money+chance;
        chance=0;
        sprintf(money1,"%d",money);
        sprintf(chance1,"%d",chance);
        move(28,27);
        addstr("total_money: ");
        addstr(money1);
        addstr("     ");
        addstr("the money that you can get: ");
        addstr(chance1);
        addstr(N);
        refresh();
        sleep(3);
        endwin();

    }


    fclose(fp);

}

 

void handler(){

    clear();

    move(LINES-1,30);

    addstr("Will you continue the game?(y/n)");

    refresh();

    ans = getc(stdin);

    move(LINES-1,30);

    addstr("                                                             ");

    refresh();

}

int check_value(int v[],int line){
	int i=0;
	for(i;i<line;i++){
		if(v[i]==0) break; 
	}
	if(i==line)  return 0;
	else return 1;
}

int valid(char* input,const char* answer,int line,int v[]){
	int k=0;
	 for(int i=0;i<line;i++){
        if((v[i]==0)&&(input[0]==answer[i])){
        move(location_y-1,location_x+(i*2));
        addstr(input);
        move(location_y-1,location_x+(i*2)+1);
        addstr(" ");
        //addstr(answer);
        refresh();
        k=1;
        v[i]=1;
        }
    }
	if(k==1)	return 1;
	return 0;
}

