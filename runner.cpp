#include <curses.h>
#include <cstdlib>
#include <ctime>

#define bRead(value, bit) (((value) >> (bit)) & 0x01)
#define cactus '|'
#define player '@'

void sleep(int);
void init();

int main() {
	init();

	int map = 0, plry = 10, score = 0, asd = 2;

	while (true) {
		if (!bRead(map, 1) && !bRead(map, 2) && !bRead(map, 3) && !bRead(map, 4) && !bRead(map, 5)) map |= 1UL;

		if (plry < 10) {
			if (asd) asd -= 1;
			else {
				asd = 2;
				mvwaddch(stdscr, plry, 14, ' ');
				++plry;
			}
		}

		if (getch() == KEY_UP && plry >= 9) {
			mvwaddch(stdscr, plry, 14, ' ');
			--plry;
		}

		if (plry == 10 && bRead(map, 28)) break;
		if (bRead(map, 29)) ++score;

		move(10, 11);
		for (int j = 31; j >= 0; --j) {
			waddch(stdscr, (bRead(map, j) ? cactus | COLOR_PAIR(1) : ' '));
		}
		
		mvwaddch(stdscr, plry, 14, player);

		mvwaddch(stdscr, 5, 42, cactus | COLOR_PAIR(1));
		wprintw(stdscr, " - %d", score);

		map <<= 1;
		refresh();
		sleep(150);
	}
	sleep(2000);

	endwin();
	return 0;
}

void sleep(int mseconds) {
    clock_t startClock = clock();
    while(clock() < startClock + (((float)mseconds / 1000) * CLOCKS_PER_SEC));
}

void init() {
	srand(static_cast<unsigned int>(time(NULL)));

	initscr();
	start_color();
	init_pair(1, COLOR_GREEN, 0);
	curs_set(false);
	keypad(stdscr, true);
	nodelay(stdscr, true);
	noecho();
}

//By B.S.M
