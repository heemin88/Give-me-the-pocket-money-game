#include <curses.h>
#include "mainScreen.h"

int printmain(void){
	char a;
	move (0,0);
	//standout();
	//addstr("I need some pocket money!");
	addstr("    ====================================================================\n");
	addstr("         *******      **       *    ********   ********   ****\n");
	addstr("            *         *  *     *    *          *          *   **\n");
	addstr("            *         *   *    *    *******    *******    *    **\n");
	addstr("            *         *     *  *    *          *          *    **\n");
	addstr("            *         *     *  *    *          *          *   **\n");
	addstr("         *******      *       **    ********   ********   ****\n\n");
	

	addstr("         **        **      ***      **       *   *******  **      **\n");
	addstr("         * *      * *    *     *    *  *     *   *         **    **\n");
	addstr("         *  *    *  *   *       *   *   *    *   *******      ** \n");
	addstr("         *   *  *   *    *     *    *     *  *   *            **\n");
	addstr("         *    *     *      ***      *       **   ********     **\n");
	addstr("    ====================================================================\n");
	refresh();
	standend();
	move(20,20);
	addstr("if you want start, preess 's'");
	refresh();
	move (21,20);
	addstr("if you want quit, preess 'q'");
	refresh();
	while(1){
		a = getchar();
		if (a=='s'||a=='S')
			return 1;
		else if(a=='q'||a=='Q')
			return 0;
		else
		{
			move(24,20);
			addstr("only 'q'or 's' please");
			
			refresh();
		}
	}
}
