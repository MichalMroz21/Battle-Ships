#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define boardSizeX 10
#define boardSizeY 21

struct ship {
	int size;
	int isPlaced;
	int pos[2];
	char dir;
	int cannon[2];
	int engine[2];
	int availableshots;
	int spy[5][2];
	int howManySpies;
};
typedef struct ship Ship;


struct player {
	Ship Car[10];
	Ship Bat[10];
	Ship Cru[10];
	Ship Des[10];
	int tilesDestroyed;
	int sum;
};
typedef struct player Player;

void inputHandle(char* str, int* group, int* prevGroup, char** plansza, Player* pA, Player* pB, int* nextPlayer, int* count, int* initPosA, int* initPosB, int* planszaX, int* planszaY, int* extendedShips);

void klamraHandle(char* str, int* group, int* prevGroup, char** plansza, Player* pA, Player* pB, int* nextPlayer, int* count, int* planszaY);

void placeShipHandle(char* str, int* group, char** plansza, Player* pA, Player* pB, int* initPosA, int* initPosB, int* planszaY);

void setFleetHandle(char* str, Player* pA, Player* pB);

void shootExtHandle(char* str, int* group, char** plansza, Player* pA, Player* pB, int* planszaX, int* planszaY);

void placeShipExtHandle(char* str, int* group, char** plansza, Player* pA, Player* pB, int* planszaX, int* planszaY);

void initPosHandle(char* str, int* initPosA, int* initPosB);

void reefHandle(char* str, char** plansza, int* planszaX, int* planszaY);

void boardSizeHandle(char* str, char** plansza, int* planszaX, int* planszaY);

void moveHandle(char* str, int* group, char** plansza, Player* pA, Player* pB, int* planszaY, int* planszaX);

void shootHandle(char* str, char** plansza, Player* pA, Player* pB, int* planszaX, int* planszaY);

void spyHandle(char* str, int* group, char** plansza, Player* pA, Player* pB, int* planszaY);

void saveHandle(char** plansza, Player* pA, Player* pB, int* nextPlayer, int* initPosA, int* initPosB, int* planszaX, int* planszaY, int* extendedShips);

void setUpPlayer(Player* p, int CarQ, int BatQ, int CruQ, int DesQ);

void printBoard(int sizeY, int sizeX, char** plansza, Player* pA, Player* pB, int group);

void printBoardExt(int sizeY, int sizeX, char** plansza, Player* pA, Player* pB, int group);

void placeShip(int y, int x, char d, Ship* ship, char** plansza, int* group, char* str, int* initPosA, int* initPosB, int sizeY);

void placeShipExt(Player* p, int y, int x, char d, Ship* ship, char** plansza, int* group, char* str, int* zeroones, int sizeY, int sizeX);

void shoot(int y, int x, char** plansza, Player* pA, Player* pB, char* str, int sizeY, int sizeX);

void shootExt(int y, int x, char** plansza, Player* pA, Player* pB, char* str, int sizeY, int sizeX, Ship* ship);

void freeMemory(char** plansza, int sizeY);

void Move(Ship* ship, char direction, char** plansza, int sizeY, int sizeX, char* str);

int constructNumber(int tab[3], int n);

int main(void) {

	Player pA;
	Player pB;

	int nextPlayer = 1;
	int count = 0;

	int extendedShips = 0;

	int initPosA[4];
	int initPosB[4];

	initPosA[0] = 0;
	initPosA[1] = 0;
	initPosA[2] = 9;
	initPosA[3] = 9;
	initPosB[0] = 11;
	initPosB[1] = 0;
	initPosB[2] = 20;
	initPosB[3] = 9;

	setUpPlayer(&pA, 1, 2, 3, 4);
	setUpPlayer(&pB, 1, 2, 3, 4);

	int group; int prevGroup;

	int planszaY = boardSizeY;
	int planszaX = boardSizeX;

	char** plansza = (char**)malloc(planszaY * sizeof * plansza); 
	for (int i = 0; i < boardSizeY; i++) {
		plansza[i] = (char*)malloc(planszaX * sizeof * *plansza);
	}

	for (int i = 0; i < boardSizeY; i++) {
		for (int j = 0; j < boardSizeX; j++) {
			plansza[i][j] = ' ';
		}
	}



	while (!feof(stdin)) {

		char str[100];

		if (fgets(str, sizeof(str), stdin) == NULL) {
			freeMemory(plansza, planszaY);
		}

		str[strcspn(str, "\n")] = 0; //usuwa newline

		inputHandle(str, &group, &prevGroup, plansza, &pA, &pB, &nextPlayer, &count, initPosA, initPosB, &planszaX, &planszaY, &extendedShips);

	}


}

void inputHandle(char* str, int* group, int* prevGroup, char** plansza, Player* pA, Player* pB, int* nextPlayer, int* count, int* initPosA, int* initPosB, int* planszaX, int* planszaY, int* extendedShips) {

	if (str[0] == '[') {

		klamraHandle(str, group, prevGroup, plansza, pA, pB, nextPlayer, count, planszaY);

	}

	if (str[0] == 'P' && str[1] == 'R' && str[2] == 'I') {

		if ((str[6] - '0') == 0) {

			printBoard(*planszaY, *planszaX, plansza, pA, pB, *group);

		}
		else {

			printBoardExt(*planszaY, *planszaX, plansza, pA, pB, *group);

		}

	}

	if (str[0] == 'P' && str[1] == 'L' && str[2] == 'A')
	{

		placeShipHandle(str, group, plansza, pA, pB, initPosA, initPosB, planszaY);

	}

	if (str[0] == 'S' && str[1] == 'E' && str[2] == 'T' && str[3] == '_' && str[4] == 'F') {

		setFleetHandle(str, pA, pB);

	}

	if (str[0] == 'N' && str[1] == 'E' && str[2] == 'X') {

		int data = 0;
		int i = 0;
		int j = 0;
		while (str[i] != '\0') {

			if (str[i] == ' ') {
				j++;
				i++;
				continue;
			}

			if (j == 1) data = (str[i] - 'A') + 1;
			i++;
		}

		*nextPlayer = data;

	}


	if ((str[0] == 'S' && str[1] == 'H' && str[2] == 'O' && (*extendedShips == 1))) {

		shootExtHandle(str, group, plansza, pA, pB, planszaX, planszaY);

	}

	if (str[0] == 'S' && str[1] == 'H' && str[2] == 'I') {

		placeShipExtHandle(str, group, plansza, pA, pB, planszaX, planszaY);

	}

	if (str[0] == 'I' && str[1] == 'N' && str[2] == 'I' && str[3] == 'T' && str[4] == '_' && str[5] == 'P') {

		initPosHandle(str, initPosA, initPosB);

	}

	if (str[0] == 'R' && str[1] == 'E' && str[2] == 'E' && str[3] == 'F') {

		reefHandle(str, plansza, planszaX, planszaY);

	}

	if (str[0] == 'B' && str[1] == 'O' && str[2] == 'A' && str[3] == 'R' && str[4] == 'D' && str[5] == '_' && str[6] == 'S') {

		boardSizeHandle(str, plansza, planszaX, planszaY);

	}

	if (str[0] == 'M' && str[1] == 'O' && str[2] == 'V' && str[3] == 'E') {

		moveHandle(str, group, plansza, pA, pB, planszaY, planszaX);

	}

	if ((str[0] == 'S' && str[1] == 'H' && str[2] == 'O') && (*extendedShips == 0)) {

		shootHandle(str, plansza, pA, pB, planszaX, planszaY);

	}

	if (str[0] == 'E' && str[1] == 'X' && str[2] == 'T' && str[3] == 'E' && str[4] == 'N') {

		*extendedShips = 1;

	}

	if (str[0] == 'S' && str[1] == 'P' && str[2] == 'Y') {

		spyHandle(str, group, plansza, pA, pB, planszaY);

	}
	if (str[0] == 'S' && str[1] == 'A' && str[2] == 'V' && str[3] == 'E') {

		saveHandle(plansza, pA, pB, nextPlayer, initPosA, initPosB, planszaX, planszaY, extendedShips);

	}
}

void setUpPlayer(Player* p, int CarQ, int BatQ, int CruQ, int DesQ) {

  //INICJALIZACJA DANYCH

	(*p).tilesDestroyed = 0;
	(*p).sum = 0;

	for (int i = 0; i < 10; i++) {


		for (int j = 0; j < 5; j++) {

			(*p).Car[i].spy[j][0] = -1;
			(*p).Car[i].spy[j][1] = -1;
			(*p).Bat[i].spy[j][0] = -1;
			(*p).Bat[i].spy[j][1] = -1;
			(*p).Cru[i].spy[j][0] = -1;
			(*p).Cru[i].spy[j][1] = -1;
			(*p).Des[i].spy[j][0] = -1;
			(*p).Des[i].spy[j][1] = -1;

		}

		(*p).Car[i].size = 5 * ((i + 1) <= CarQ);
		(*p).sum += (*p).Car[i].size;
		(*p).Car[i].availableshots = (*p).Car[i].size;
		(*p).Car[i].isPlaced = 0;
		(*p).Car[i].dir = '\0';
		(*p).Car[i].pos[0] = -1;
		(*p).Car[i].pos[1] = -1;
		(*p).Car[i].cannon[0] = -1;
		(*p).Car[i].cannon[1] = -1;
		(*p).Car[i].engine[0] = -1;
		(*p).Car[i].engine[1] = -1;
		(*p).Car[i].howManySpies = 0;

		(*p).Bat[i].size = 4 * ((i + 1) <= BatQ);
		(*p).sum += (*p).Bat[i].size;
		(*p).Bat[i].availableshots = (*p).Bat[i].size;
		(*p).Bat[i].isPlaced = 0;
		(*p).Bat[i].dir = '\0';
		(*p).Bat[i].pos[0] = -1; (*p).Bat[i].pos[1] = -1;
		(*p).Bat[i].cannon[0] = -1;
		(*p).Bat[i].cannon[1] = -1;
		(*p).Bat[i].engine[0] = -1;
		(*p).Bat[i].engine[1] = -1;
		(*p).Bat[i].howManySpies = 0;

		(*p).Cru[i].size = 3 * ((i + 1) <= CruQ);
		(*p).sum += (*p).Cru[i].size; (*p).Cru[i].availableshots = (*p).Cru[i].size;
		(*p).Cru[i].isPlaced = 0;
		(*p).Cru[i].dir = '\0';
		(*p).Cru[i].pos[0] = -1;
		(*p).Cru[i].pos[1] = -1;
		(*p).Cru[i].cannon[0] = -1;
		(*p).Cru[i].cannon[1] = -1;
		(*p).Cru[i].engine[0] = -1;
		(*p).Cru[i].engine[1] = -1;
		(*p).Cru[i].howManySpies = 0;

		(*p).Des[i].size = 2 * ((i + 1) <= DesQ);
		(*p).sum += (*p).Des[i].size;
		(*p).Des[i].availableshots = (*p).Des[i].size;
		(*p).Des[i].isPlaced = 0;
		(*p).Des[i].dir = '\0';
		(*p).Des[i].pos[0] = -1; (*p).Des[i].pos[1] = -1;
		(*p).Des[i].cannon[0] = -1;
		(*p).Des[i].cannon[1] = -1;
		(*p).Des[i].engine[0] = -1;
		(*p).Des[i].engine[1] = -1;
		(*p).Des[i].howManySpies = 0;


	}
}

void printBoard(int sizeY, int sizeX, char** plansza, Player* pA, Player* pB, int group) {
	if (group == 1 || group == 2) {

		Player* p = pA;

		if (group == 1) p = pA;
		if (group == 2) p = pB;

		int** board = (int**)malloc(sizeY * sizeof * board);
		for (int i = 0; i < sizeY; i++) {
			board[i] = (int*)malloc(sizeX * sizeof * *board);
		}


		for (int i = 0; i < sizeY; i++) {
			for (int j = 0; j < sizeX; j++) {
				board[i][j] = '?';
			}
		}

		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				if (((*p).Car[i].spy[j][0] != (-1)) && ((*p).Car[i].spy[j][1] != (-1))) {

					int y = (*p).Car[i].spy[j][0];
					int x = (*p).Car[i].spy[j][1];
					board[y][x] = plansza[y][x];

					if (!((y + 1) == sizeY))
						board[y + 1][x] = plansza[y + 1][x];

					if (!((x + 1) == sizeX))
						board[y][x + 1] = plansza[y][x + 1];

					if ((!(x + 1 == sizeX)) && (!(y + 1 == sizeY)))
						board[y + 1][x + 1] = plansza[y + 1][x + 1];

					if (!(y - 1 == (-1)))
						board[y - 1][x] = plansza[y - 1][x];

					if ((!(y - 1 == (-1))) && (!(x + 1 == sizeX)))
						board[y - 1][x + 1] = plansza[y - 1][x + 1];

					if ((!(y - 1 == (-1))) && (!(x - 1 == (-1))))
						board[y - 1][x - 1] = plansza[y - 1][x - 1];

					if (!(x - 1 == (-1)))
						board[y][x - 1] = plansza[y][x - 1];

					if ((!(y + 1 == sizeY)) && (!(x - 1 == (-1))))
						board[y + 1][x - 1] = plansza[y + 1][x - 1];
				}

			}
		}

		for (int i = 0; i < 10; i++) {

			if ( ((*p).Car[i].pos[0] != (-1)) && ((*p).Car[i].pos[1] != (-1)) ) {
        
				int range = 0;

				if (plansza[(*p).Car[i].pos[0]][(*p).Car[i].pos[1]] == 'x') {
          range = 1;
        }

				else range = 5;

				for (int m = 0; m < sizeY; m++) {
					for (int n = 0; n < sizeX; n++) {
						double dist = sqrt(abs((*p).Car[i].pos[0] - m) * abs((*p).Car[i].pos[0] - m)   +    abs((*p).Car[i].pos[1] - n) * abs((*p).Car[i].pos[1] - n));
						if (dist <= range) board[m][n] = plansza[m][n];
					}
				}
			}
			if (((*p).Bat[i].pos[0] != (-1) ) && ((*p).Bat[i].pos[1] != (-1) )) {

				int range = 0;

				if (plansza[(*p).Bat[i].pos[0]][(*p).Bat[i].pos[1]] == 'x') {
          range = 1;
        }

				else range = 4;

				for (int m = 0; m < sizeY; m++) {
					for (int n = 0; n < sizeX; n++) {
						double dist = sqrt(abs((*p).Bat[i].pos[0] - m) * abs((*p).Bat[i].pos[0] - m)    +    abs((*p).Bat[i].pos[1] - n) * abs((*p).Bat[i].pos[1] - n));
						if (dist <= range) board[m][n] = plansza[m][n];
					}
				}
			}
			if (((*p).Cru[i].pos[0] != (-1) ) && ((*p).Cru[i].pos[1] != (-1)) ) {

				int range = 0;

				if (plansza[(*p).Cru[i].pos[0]][(*pA).Cru[i].pos[1]] == 'x') {
          range = 1;
        }

				else range = 3;

				for (int m = 0; m < sizeY; m++) {
					for (int n = 0; n < sizeX; n++) {
						double dist = sqrt(abs((*p).Cru[i].pos[0] - m) * abs((*p).Cru[i].pos[0] - m)    +    abs((*p).Cru[i].pos[1] - n) * abs((*p).Cru[i].pos[1] - n));
						if (dist <= range) board[m][n] = plansza[m][n];
					}
				}
			}
			if (((*p).Des[i].pos[0] != (-1)) && ((*p).Des[i].pos[1] != (-1))) {
				int range = 0;
				if (plansza[(*p).Des[i].pos[0]][(*p).Des[i].pos[1]] == 'x') {
          range = 1;
        }
				else range = 2;
				for (int m = 0; m < sizeY; m++) {
					for (int n = 0; n < sizeX; n++) {
						double dist = sqrt(abs((*p).Des[i].pos[0] - m) * abs((*p).Des[i].pos[0] - m)     +     abs((*p).Des[i].pos[1] - n) * abs((*p).Des[i].pos[1] - n));
						if (dist <= range) board[m][n] = plansza[m][n];
					}
				}
			}


		}

		for (int i = 0; i < sizeY; i++) {
			for (int j = 0; j < sizeX; j++) {
				printf("%c", board[i][j]);
			}
			printf("%s", "\n");
		}

		freeMemory((char**)board, sizeY);

	}

	else if (group == 0) {
		for (int i = 0; i <= (sizeY - 1); i++) {
			for (int j = 0; j < sizeX; j++) {
				printf("%c", plansza[i][j]);
			}
			printf("%s", "\n");
		}
	}

	int partsA = 0;
	int partsB = 0;
	for (int i = 0; i < 10; i++) {

		partsA += ((*pA).Car[i].size) * ((*pA).Car[i].isPlaced);
		partsA += ((*pA).Bat[i].size) * ((*pA).Bat[i].isPlaced);
		partsA += ((*pA).Cru[i].size) * ((*pA).Cru[i].isPlaced);
		partsA += ((*pA).Des[i].size) * ((*pA).Des[i].isPlaced);
		partsB += ((*pB).Car[i].size) * ((*pB).Car[i].isPlaced);
		partsB += ((*pB).Bat[i].size) * ((*pB).Bat[i].isPlaced);
		partsB += ((*pB).Cru[i].size) * ((*pB).Cru[i].isPlaced);
		partsB += ((*pB).Des[i].size) * ((*pB).Des[i].isPlaced);

	}

	partsA -= (*pA).tilesDestroyed;
	partsB -= (*pB).tilesDestroyed;

	if (group == 0) {
		printf("%s", "\n");
		printf("PARTS REMAINING:: A : %d B : %d", partsA, partsB);
		printf("%s", "\n");
	}

}

void placeShip(int y, int x, char d, Ship* ship, char** plansza, int* group, char* str, int* initPosA, int* initPosB, int sizeY) {


	if ( (ship->size) == 0) {
		printf("INVALID OPERATION \"%s\": ALL SHIPS OF THE CLASS ALREADY SET", str);
		freeMemory(plansza, sizeY);
		exit(0);
	}

	if ( (ship->isPlaced) == 1) {
		printf("INVALID OPERATION \"%s\": SHIP ALREADY PRESENT", str);
		freeMemory(plansza, sizeY);
		exit(0);
	}

	ship->isPlaced = 1;
	ship->dir = d;
	ship->pos[0] = y;
	ship->pos[1] = x;
	ship->cannon[0] = y;
	ship->cannon[1] = x;

	if (d == 'N') ship->cannon[0]++;
	else if (d == 'S') ship->cannon[0]--;
	else if (d == 'W') ship->cannon[1]++;
	else if (d == 'E') ship->cannon[1]--;

	int temp1 = x; 
  int temp2 = y;

	for (int j = 0; j < ship->size; j++) {

		if (*group == 1) {
			if (y > initPosA[2] || x > initPosA[3] || x < initPosA[1] || y < initPosA[0]) { //y: 0-9, x: 0-9
				printf("INVALID OPERATION \"%s\": NOT IN STARTING POSITION", str);
				freeMemory(plansza, sizeY);
				exit(0);
			}

		}

		if (*group == 2) {
			if (y < initPosB[0] || x>initPosB[3] || x < initPosB[1] || y>initPosB[2]) { //y: 11-20, x: 0-9
				printf("INVALID OPERATION \"%s\": NOT IN STARTING POSITION", str);
				freeMemory(plansza, sizeY);
				exit(0);
			}

		}

		int A = ((y + 1) < boardSizeY);
		int B = ((y - 1) >= 0);
		int C = ((x + 1) < boardSizeX);
		int D = ((x - 1) >= 0);

  //A, B, C, D wystepuja aby nie bylo BAD_ALLOC tzn. wyjscia poza tablice, wewnatrz indexu - zeruja aby nie bylo BAD_ALLOC, rowniez zeruja w takim wypadku wyrazenie ifowe aby plansza[0][0] na przyklad nie byla uwzgledniana jako 1, ma byc nie uwzgledniana.

		if (((plansza[(y + 1) * A][x] == '+') * A) || ((plansza[(y - 1) * B][x] == '+') * B) || ((plansza[y][(x + 1) * C] == '+') * C) || ((plansza[y][(x - 1) * D] == '+') * D) || ((plansza[(y - 1) * B][(x - 1) * D] == '+') * B * D) || ((plansza[(y - 1) * B][(x + 1) * C] == '+') * B * C) || ((plansza[(y + 1) * A][(x - 1) * D] == '+') * A * D) || ((plansza[(y + 1) * A][(x + 1) * C] == '+') * A * C)) {
			printf("INVALID OPERATION \"%s\": PLACING SHIP TOO CLOSE TO OTHER SHIP", str);
			freeMemory(plansza, sizeY);
			exit(0);
		}

		if (d == 'N') y++;
		else if (d == 'S') y--;
		else if (d == 'W') x++;
		else if (d == 'E') x--;

	}

	x = temp1; y = temp2;

	for (int j = 0; j < ship->size; j++) {

		if (plansza[y][x] == '#') {
			printf("INVALID OPERATION \"%s\": PLACING SHIP ON REEF", str);
			freeMemory(plansza, sizeY);
			exit(0);
		}

		plansza[y][x] = '+';

		if (d == 'N') y++;
		else if (d == 'S') y--;
		else if (d == 'W') x++;
		else if (d == 'E') x--;

	}

	if (d == 'N') y--;
	else if (d == 'S') y++;
	else if (d == 'W') x--;
	else if (d == 'E') x++;

	ship->engine[0] = y;
	ship->engine[1] = x;


}

void placeShipExt(Player* p, int y, int x, char d, Ship* ship, char** plansza, int* group, char* str, int* zeroones, int sizeY, int sizeX) {


	if ((ship->size) == 0) {
		printf("INVALID OPERATION \"%s\": ALL SHIPS OF THE CLASS ALREADY SET", str);
		freeMemory(plansza, sizeY);
		exit(0);
	}

	if ((ship->isPlaced) == 1) {
		printf("INVALID OPERATION \"%s\": SHIP ALREADY PRESENT", str);
		freeMemory(plansza, sizeY);
		exit(0);
	}
	ship->isPlaced = 1;
	ship->cannon[0] = y;
	ship->cannon[1] = x;

	if (d == 'N') ship->cannon[0]++;
	else if (d == 'S') ship->cannon[0]--;
	else if (d == 'W') ship->cannon[1]++;
	else if (d == 'E') ship->cannon[1]--;

	int temp1 = x; int temp2 = y;

	for (int j = 0; j < ship->size; j++) {

		if (*group == 1) {
			if (y > 9) {
				printf("INVALID OPERATION \"%s\": NOT IN STARTING POSITION", str);
				freeMemory(plansza, sizeY);
				exit(0);
			}
		}

		if (*group == 2) {
			if (y < 11) {
				printf("INVALID OPERATION \"%s\": NOT IN STARTING POSITION", str);
				freeMemory(plansza, sizeY);
				exit(0);
			}
		}

		int A = ((y + 1) < sizeY);
		int B = ((y - 1) >= 0);
		int C = ((x + 1) < sizeX);
		int D = ((x - 1) >= 0);

    //komentarz do tego w funkcji wyzej

		if (((plansza[(y + 1) * A][x] == '+') * A) || ((plansza[(y - 1) * B][x] == '+') * B) || ((plansza[y][(x + 1) * C] == '+') * C) || ((plansza[y][(x - 1) * D] == '+') * D) || ((plansza[(y - 1) * B][(x - 1) * D] == '+') * B * D) || ((plansza[(y - 1) * B][(x + 1) * C] == '+') * B * C) || ((plansza[(y + 1) * A][(x - 1) * D] == '+') * A * D) || ((plansza[(y + 1) * A][(x + 1) * C] == '+') * A * C)) {
			printf("INVALID OPERATION \"%s\": PLACING SHIP TOO CLOSE TO OTHER SHIP", str);
			freeMemory(plansza, sizeY);
			exit(0);
		}

		if (d == 'N') y++;
		else if (d == 'S') y--;
		else if (d == 'W') x++;
		else if (d == 'E') x--;

	}

	x = temp1; y = temp2;

	for (int j = 0; j < ship->size; j++) {

		if (plansza[y][x] == '#') {
			printf("INVALID OPERATION \"%s\": PLACING SHIP ON REEF", str);
			freeMemory(plansza, sizeY);
			exit(0);
		}

		if (zeroones[j] == 1) plansza[y][x] = '+';
		else if (zeroones[j] == 0) { 
      plansza[y][x] = 'x'; (*p).tilesDestroyed++; 
      }

		if (d == 'N') y++;
		else if (d == 'S') y--;
		else if (d == 'W') x++;
		else if (d == 'E') x--;

	}

}

int constructNumber(int tab[3], int n) {

	int a = 0;
	a += tab[0];

	for (int i = 1; i < n; i++) {
		a *= 10;
		a += tab[i];
	}

	return a;
}

void shoot(int y, int x, char** plansza, Player* pA, Player* pB, char* str, int sizeY, int sizeX) {

	if ((y > (sizeY - 1)) || y < 0 || (x > (sizeX - 1)) || x < 0) {

		printf("INVALID OPERATION \"%s\": FIELD DOES NOT EXIST", str);
		freeMemory(plansza, sizeY);
		exit(0);

	}

	int notAllShips = 0;

	for (int i = 0; i < 10; i++) {
		if ((((*pA).Car[i].size > 0) && ((*pA).Car[i].isPlaced == 0)) || (((*pA).Bat[i].size > 0) && ((*pA).Bat[i].isPlaced == 0)) || (((*pA).Cru[i].size > 0) && ((*pA).Cru[i].isPlaced == 0))
			|| (((*pA).Des[i].size > 0) && ((*pA).Des[i].isPlaced == 0)) || (((*pB).Car[i].size > 0) && ((*pB).Car[i].isPlaced == 0)) || (((*pB).Bat[i].size > 0) && ((*pB).Bat[i].isPlaced == 0))
			|| (((*pB).Cru[i].size > 0) && ((*pB).Cru[i].isPlaced == 0)) || (((*pB).Des[i].size > 0) && ((*pB).Des[i].isPlaced == 0))) {
			notAllShips = 1;
		}
	}

	if (notAllShips) {
		printf("INVALID OPERATION \"%s\": NOT ALL SHIPS PLACED", str);
		freeMemory(plansza, sizeY);
		exit(0);
	}

	if (plansza[y][x] == 'x') return;

	if (plansza[y][x] == '+') {

		if (y >= 11) (*pB).tilesDestroyed++;
		if (y <= 9) (*pA).tilesDestroyed++;

		plansza[y][x] = 'x';

	}

	if ((*pB).tilesDestroyed == (*pB).sum) {
		printf("A won");
		freeMemory(plansza, sizeY);
		exit(0);
	}

	if ((*pA).tilesDestroyed == (*pA).sum) {
		printf("B won");
		freeMemory(plansza, sizeY);
		exit(0);
	}


}

void freeMemory(char** plansza, int sizeY) {
	for (int i = 0; i < sizeY; i++) {
		free(plansza[i]);
	}
	free(plansza);
}

void Move(Ship* ship, char direction, char** plansza, int sizeY, int sizeX, char* str) {

	int y = ship->pos[0];
	int x = ship->pos[1];

	int temp1 = y;
	int temp2 = x;

	for (int j = 0; j < ship->size; j++) {

		plansza[y][x] = ' ';


		if (ship->dir == 'N') {

			y++;

			if (y >= sizeY) {
				printf("INVALID OPERATION \"%s\": SHIP WENT FROM BOARD", str);
				freeMemory(plansza, sizeY);
				exit(0);
			}

		}
		else if (ship->dir == 'S') {
			y--;

			if (y < 0) {
				printf("INVALID OPERATION \"%s\": SHIP WENT FROM BOARD", str);
				freeMemory(plansza, sizeY);
				exit(0);
			}

		}
		else if (ship->dir == 'W') {
			x++;

			if (x >= sizeX) {
				printf("INVALID OPERATION \"%s\": SHIP WENT FROM BOARD", str);
				freeMemory(plansza, sizeY);
				exit(0);
			}

		}
		else if (ship->dir == 'E') {
			x--;

			if (x < 0) {
				printf("INVALID OPERATION \"%s\": SHIP WENT FROM BOARD", str);
				freeMemory(plansza, sizeY);
				exit(0);
			}

		}
	}

	y = temp1;
	x = temp2;

	if (direction == 'F') {

		if (ship->dir == 'N') { 
      y--; ship->pos[0]--; 
    }

		if (ship->dir == 'S') { 
      y++; ship->pos[0]++; 
    }

		if (ship->dir == 'W') { 
      x--; ship->pos[1]--; 
    }

		if (ship->dir == 'E') {
      x++; ship->pos[1]++; 
    }

	}

	if (y >= sizeY) {
		printf("INVALID OPERATION \"%s\": SHIP WENT FROM BOARD", str);
		freeMemory(plansza, sizeY);
		exit(0);
	}
	if (y < 0) {
		printf("INVALID OPERATION \"%s\": SHIP WENT FROM BOARD", str);
		freeMemory(plansza, sizeY);
		exit(0);
	}
	if (x >= sizeX) {
		printf("INVALID OPERATION \"%s\": SHIP WENT FROM BOARD", str);
		freeMemory(plansza, sizeY);
		exit(0);
	}
	if (x < 0) {
		printf("INVALID OPERATION \"%s\": SHIP WENT FROM BOARD", str);
		freeMemory(plansza, sizeY);
		exit(0);
	}

	for (int j = 0; j < ship->size; j++) {

		plansza[y][x] = '+';


		if (ship->dir == 'N') {

			y++;

			if (y >= sizeY) {
				printf("INVALID OPERATION \"%s\": SHIP WENT FROM BOARD", str);
				freeMemory(plansza, sizeY);
				exit(0);
			}

		}
		else if (ship->dir == 'S') {

			y--;

			if (y < 0) {
				printf("INVALID OPERATION \"%s\": SHIP WENT FROM BOARD", str);
				freeMemory(plansza, sizeY);
				exit(0);
			}

		}
		else if (ship->dir == 'W') {

			x++;

			if (x >= sizeX) {
				printf("INVALID OPERATION \"%s\": SHIP WENT FROM BOARD", str);
				freeMemory(plansza, sizeY);
				exit(0);
			}

		}
		else if (ship->dir == 'E') {

			x--;

			if (x < 0) {
				printf("INVALID OPERATION \"%s\": SHIP WENT FROM BOARD", str);
				freeMemory(plansza, sizeY);
				exit(0);
			}

		}
	}

}

void shootExt(int y, int x, char** plansza, Player* pA, Player* pB, char* str, int sizeY, int sizeX, Ship* ship) {


	if ((ship->availableshots) <= (0)) {
		printf("INVALID OPERATION \"%s\": TOO MANY SHOOTS", str);
		freeMemory(plansza, sizeY);
		exit(0);
	}

	ship->availableshots--;

	if (plansza[ship->cannon[0]][ship->cannon[1]] == 'x') {
		printf("INVALID OPERATION \"%s\": SHIP CANNOT SHOOT", str);
		freeMemory(plansza, sizeY);
		exit(0);
	}

	double dist = sqrt(abs(ship->cannon[0] - y) * abs(ship->cannon[0] - y) + abs(ship->cannon[1] - x) * abs(ship->cannon[1] - x));
	if ((ship->size) != 5) {

		if (dist > (ship->size)) {
			printf("INVALID OPERATION \"%s\": SHOOTING TOO FAR", str);
			freeMemory(plansza, sizeY);
			exit(0);
		}
	}

	if ((y > (sizeY - 1)) || y < 0 || (x > (sizeX - 1)) || x < 0) {

		printf("INVALID OPERATION \"%s\": FIELD DOES NOT EXIST", str);
		freeMemory(plansza, sizeY);
		exit(0);

	}

	int notAllShips = 0;

	for (int i = 0; i < 10; i++) {
		if ((((*pA).Car[i].size > 0) && ((*pA).Car[i].isPlaced == 0)) || (((*pA).Bat[i].size > 0) && ((*pA).Bat[i].isPlaced == 0)) || (((*pA).Cru[i].size > 0) && ((*pA).Cru[i].isPlaced == 0))
			|| (((*pA).Des[i].size > 0) && ((*pA).Des[i].isPlaced == 0)) || (((*pB).Car[i].size > 0) && ((*pB).Car[i].isPlaced == 0)) || (((*pB).Bat[i].size > 0) && ((*pB).Bat[i].isPlaced == 0))
			|| (((*pB).Cru[i].size > 0) && ((*pB).Cru[i].isPlaced == 0)) || (((*pB).Des[i].size > 0) && ((*pB).Des[i].isPlaced == 0))) {
			notAllShips = 1;
		}
	}

	if (notAllShips) {
		printf("INVALID OPERATION \"%s\": NOT ALL SHIPS PLACED", str);
		freeMemory(plansza, sizeY);
		exit(0);
	}



	if (plansza[y][x] == 'x') return;
	if (plansza[y][x] == '+') {

		if (y >= 11) (*pB).tilesDestroyed++;
		if (y <= 9) (*pA).tilesDestroyed++;

		plansza[y][x] = 'x';

	}

	if ((*pB).tilesDestroyed == (*pB).sum) {
		printf("A won");
		freeMemory(plansza, sizeY);
		exit(0);
	}
	if ((*pA).tilesDestroyed == (*pA).sum) {
		printf("B won");
		freeMemory(plansza, sizeY);
		exit(0);
	}

}

void printBoardExt(int sizeY, int sizeX, char** plansza, Player* pA, Player* pB, int group) {

	char** board = (char**)malloc(sizeY * sizeof * board);

	for (int i = 0; i < sizeY; i++) {
		board[i] = (char*)malloc(sizeX * sizeof * *board);
	}


	for (int i = 0; i < sizeY; i++) {
		for (int j = 0; j < sizeX; j++) {
			board[i][j] = plansza[i][j];
		}
	}

	for (int i = 0; i < sizeY; i++) {

		for (int j = 0; j < sizeX; j++) {


			for (int k = 0; k < 10; k++) {

				if (board[i][j] != 'x') {

					if ((*pA).Des[k].cannon[0] == i && (*pA).Des[k].cannon[1] == j) board[i][j] = '%';
					else if ((*pB).Des[k].cannon[0] == i && (*pB).Des[k].cannon[1] == j) board[i][j] = '%';
					else if ((*pA).Des[k].engine[0] == i && (*pA).Des[k].engine[1] == j) board[i][j] = '%';
					else if ((*pB).Des[k].engine[0] == i && (*pB).Des[k].engine[1] == j) board[i][j] = '%';
					else if ((*pA).Des[k].pos[0] == i && (*pA).Des[k].pos[1] == j) board[i][j] = '@';
					else if ((*pB).Des[k].pos[0] == i && (*pB).Des[k].pos[1] == j) board[i][j] = '@';

					else if ((*pA).Car[k].cannon[0] == i && (*pA).Car[k].cannon[1] == j) board[i][j] = '!';
					else if ((*pB).Car[k].cannon[0] == i && (*pB).Car[k].cannon[1] == j) board[i][j] = '!';
					else if ((*pA).Car[k].engine[0] == i && (*pA).Car[k].engine[1] == j) board[i][j] = '%';
					else if ((*pB).Car[k].engine[0] == i && (*pB).Car[k].engine[1] == j) board[i][j] = '%';
					else if ((*pA).Car[k].pos[0] == i && (*pA).Car[k].pos[1] == j) board[i][j] = '@';
					else if ((*pB).Car[k].pos[0] == i && (*pB).Car[k].pos[1] == j) board[i][j] = '@';

					else if ((*pA).Bat[k].cannon[0] == i && (*pA).Bat[k].cannon[1] == j) board[i][j] = '!';
					else if ((*pB).Bat[k].cannon[0] == i && (*pB).Bat[k].cannon[1] == j) board[i][j] = '!';
					else if ((*pA).Bat[k].engine[0] == i && (*pA).Bat[k].engine[1] == j) board[i][j] = '%';
					else if ((*pB).Bat[k].engine[0] == i && (*pB).Bat[k].engine[1] == j) board[i][j] = '%';
					else if ((*pA).Bat[k].pos[0] == i && (*pA).Bat[k].pos[1] == j) board[i][j] = '@';
					else if ((*pB).Bat[k].pos[0] == i && (*pB).Bat[k].pos[1] == j) board[i][j] = '@';
 
 
					else if ((*pA).Cru[k].cannon[0] == i && (*pA).Cru[k].cannon[1] == j) board[i][j] = '!';
					else if ((*pB).Cru[k].cannon[0] == i && (*pB).Cru[k].cannon[1] == j) board[i][j] = '!';
					else if ((*pA).Cru[k].engine[0] == i && (*pA).Cru[k].engine[1] == j) board[i][j] = '%';
					else if ((*pB).Cru[k].engine[0] == i && (*pB).Cru[k].engine[1] == j) board[i][j] = '%';
					else if ((*pA).Cru[k].pos[0] == i && (*pA).Cru[k].pos[1] == j) board[i][j] = '@';
					else if ((*pB).Cru[k].pos[0] == i && (*pB).Cru[k].pos[1] == j) board[i][j] = '@';

				}


			}

		}
	}







	printf("  0123456789"); printf("%s", "\n");

	int counter = 0;

	for (int i = 0; i <= (sizeY - 1); i++) {

		if (counter >= 0 && counter <= 9) printf("0%d", counter++);
		else printf("%d", counter++);

		for (int j = 0; j < sizeX; j++) {
			printf("%c", board[i][j]);
		}

		printf("%s", "\n");
	}


	int partsA = 0;
	int partsB = 0;

	for (int i = 0; i < 10; i++) {

		partsA += ((*pA).Car[i].size) * ((*pA).Car[i].isPlaced);
		partsA += ((*pA).Bat[i].size) * ((*pA).Bat[i].isPlaced);
		partsA += ((*pA).Cru[i].size) * ((*pA).Cru[i].isPlaced);
		partsA += ((*pA).Des[i].size) * ((*pA).Des[i].isPlaced);
		partsB += ((*pB).Car[i].size) * ((*pB).Car[i].isPlaced);
		partsB += ((*pB).Bat[i].size) * ((*pB).Bat[i].isPlaced);
		partsB += ((*pB).Cru[i].size) * ((*pB).Cru[i].isPlaced);
		partsB += ((*pB).Des[i].size) * ((*pB).Des[i].isPlaced);

	}

	partsA -= (*pA).tilesDestroyed;
	partsB -= (*pB).tilesDestroyed;

	if (group == 0) {
		printf("PARTS REMAINING:: A : %d B : %d", partsA, partsB);
		printf("%s", "\n");
	}

	freeMemory(board, sizeY);


}

void klamraHandle(char* str, int* group, int* prevGroup, char** plansza, Player* pA, Player* pB, int* nextPlayer, int* count, int* planszaY) {

	for (int i = 0; i < 10; i++) {

		(*pA).Car[i].availableshots = (*pA).Car[i].size;
		(*pB).Car[i].availableshots = (*pB).Car[i].size;
		(*pA).Bat[i].availableshots = (*pA).Bat[i].size;
		(*pB).Bat[i].availableshots = (*pB).Bat[i].size;
		(*pA).Cru[i].availableshots = (*pA).Cru[i].size;
		(*pB).Cru[i].availableshots = (*pB).Cru[i].size;
		(*pA).Des[i].availableshots = (*pA).Des[i].size;
		(*pB).Des[i].availableshots = (*pB).Des[i].size;

	}

	if (str[1] == 's') {
		*prevGroup = *group;
		*group = 0;
		*count = 0;
		return;
	}

	else {

		if ((*nextPlayer != ((str[7] - 'A') + 1)) && (*count == 0) && (!feof(stdin))) {
			printf("INVALID OPERATION \"%s \": THE OTHER PLAYER EXPECTED", str);
			freeMemory(plansza, *planszaY);
			exit(0);
		}

		else {

			*count = *count + 1;

			if (*count == 2) {
				if (*nextPlayer == 1) *nextPlayer = 2;
				else *nextPlayer = 1;
				*count = 0;
			}

			*prevGroup = *group;
			*group = (str[7] - 'A') + 1;
			return;

		}

	}


}

void placeShipHandle(char* str, int* group, char** plansza, Player* pA, Player* pB, int* initPosA, int* initPosB, int* planszaY) {
	int i = 0; 
  int j = 0;
	int k = 0; 
  int l = 0;
	int m = 0;
	int x = 0; 
  int y = 0;

	int xt[3]; 
  int yt[3];

	int shipIndex = 0;
	char d = '\0';
	char spaceStr[4];

	while (str[i] != '\0')
	{

		if (str[i] == ' ')
		{
			j++; i++;
			continue;
		}

		switch (j)
		{

		case 0: break;

		case 1:
			yt[l++] = (str[i] - '0');
			break;

		case 2:
			xt[m++] = (str[i] - '0');
			break;

		case 3:
			d = (str[i]);
			break;

		case 4:
			shipIndex = (str[i] - '0');
			break;

		case 5:
			spaceStr[k++] = str[i];
			break;

		}

		i++;

	}

	spaceStr[3] = '\0';

	Ship* ship = &((*pA).Car[shipIndex]);

	y = constructNumber(yt, l);
	x = constructNumber(xt, m);

	if (!strcmp("CAR", spaceStr)) {
		if (*group == 1) ship = &(*pA).Car[shipIndex];
		if (*group == 2) ship = &(*pB).Car[shipIndex];
	}
	if (!strcmp("BAT", spaceStr)) {
		if (*group == 1) ship = &(*pA).Bat[shipIndex];
		if (*group == 2) ship = &(*pB).Bat[shipIndex];
	}
	if (!strcmp("CRU", spaceStr)) {
		if (*group == 1) ship = &(*pA).Cru[shipIndex];
		if (*group == 2) ship = &(*pB).Cru[shipIndex];
	}
	if (!strcmp("DES", spaceStr)) {
		if (*group == 1) ship = &(*pA).Des[shipIndex];
		if (*group == 2) ship = &(*pB).Des[shipIndex];
	}


	placeShip(y, x, d, ship, plansza, group, str, initPosA, initPosB, *planszaY);
}

void setFleetHandle(char* str, Player* pA, Player* pB) {

	int i = 0; 
  int j = 0;
	int m = 0; 
  int n = 0;
	int o = 0; 
  int p = 0;
	char g = '\0';
	int numbers[4];
	int number1[3];
	int number2[3];
	int number3[3];
	int number4[3];
	while (str[i] != '\0') {

		if (str[i] == ' ')
		{
			j++; i++;
			continue;
		}

		switch (j)
		{
		case 0: break;

		case 1:
			g = str[i];
			break;

		case 2:
			number1[m++] = (str[i] - '0');
			break;

		case 3:
			number2[n++] = (str[i] - '0');
			break;

		case 4:
			number3[o++] = (str[i] - '0');
			break;

		case 5:
			number4[p++] = (str[i] - '0');
			break;

		}

		i++;

	}

	numbers[0] = constructNumber(number1, m);
	numbers[1] = constructNumber(number2, n);
	numbers[2] = constructNumber(number3, o);
	numbers[3] = constructNumber(number4, p);

	if (g == 'A') setUpPlayer(pA, numbers[0], numbers[1], numbers[2], numbers[3]);
	else if (g == 'B') setUpPlayer(pB, numbers[0], numbers[1], numbers[2], numbers[3]);

}

void shootExtHandle(char* str, int* group, char** plansza, Player* pA, Player* pB, int* planszaX, int* planszaY) {

	int i = 0; 
  int j = 0;
	int k = 0;
	int numbers[2];
	int number1[3];
	int number2[3];
	int m = 0; 
  int n = 0;
	int shipIndex = 0;
	char spaceStr[4];

	while (str[i] != '\0')
	{

		if (str[i] == ' ')
		{
			j++; i++;
			continue;
		}
		switch (j)
		{

		case 0: break;

		case 1:
			shipIndex = (str[i] - '0');
			break;

		case 2:
			spaceStr[k++] = str[i];
			break;

		case 3:
			number1[m++] = (str[i] - '0');
			break;

		case 4:
			number2[n++] = (str[i] - '0');
			break;

		}

		i++;

	}

	numbers[0] = constructNumber(number1, m);
	numbers[1] = constructNumber(number2, n);

	spaceStr[3] = '\0';

	Ship* ship = &((*pA).Car[shipIndex]);


	if (!strcmp("CAR", spaceStr)) {
		if (*group == 1) ship = &(*pA).Car[shipIndex];
		if (*group == 2) ship = &(*pB).Car[shipIndex];
	}
	if (!strcmp("BAT", spaceStr)) {
		if (*group == 1) ship = &(*pA).Bat[shipIndex];
		if (*group == 2) ship = &(*pB).Bat[shipIndex];
	}
	if (!strcmp("CRU", spaceStr)) {
		if (*group == 1) ship = &(*pA).Cru[shipIndex];
		if (*group == 2) ship = &(*pB).Cru[shipIndex];
	}
	if (!strcmp("DES", spaceStr)) {
		if (*group == 1) ship = &(*pA).Des[shipIndex];
		if (*group == 2) ship = &(*pB).Des[shipIndex];
	}

	shootExt(numbers[0], numbers[1], plansza, pA, pB, str, *planszaY, *planszaX, ship);

}

void placeShipExtHandle(char* str, int* group, char** plansza, Player* pA, Player* pB, int* planszaX, int* planszaY) {

	int i = 0; 
  int j = 0;
	int k = 0; 
  int l = 0;
	int m = 0; 
  int n = 0;
	int x = 0; 
  int y = 0;
	int xt[3]; 
  int yt[3];
	int shipIndex = 0;
	char d = '\0';
	char spaceStr[4];
	char pplayer = '\0';
	int zeroones[5];

	for (int o = 0; o < 5; o++) zeroones[o] = 0;

  //pobieranie danych z str

	while (str[i] != '\0')
	{

		if (str[i] == ' ')
		{
			j++; i++;
			continue;
		}

		switch (j)
		{

		case 0: break;

		case 1:
			pplayer = str[i];
			break;

		case 2:
			yt[l++] = (str[i] - '0');
			break;

		case 3:
			xt[m++] = (str[i] - '0');
			break;

		case 4:
			d = (str[i]);
			break;

		case 5:
			shipIndex = (str[i] - '0');
			break;

		case 6:
			spaceStr[k++] = str[i];
			break;

		case 7:
			zeroones[n++] = (str[i] - '0');
		}

		i++;

	}

	spaceStr[3] = '\0';

	Ship* ship = &((*pA).Car[shipIndex]);

	y = constructNumber(yt, l);
	x = constructNumber(xt, m);

  //wybranie odpowiedniego statku

	if (!strcmp("CAR", spaceStr)) {
		if (pplayer == 'A') ship = &(*pA).Car[shipIndex];
		if (pplayer == 'B') ship = &(*pB).Car[shipIndex];
	}
	if (!strcmp("BAT", spaceStr)) {
		if (pplayer == 'A') ship = &(*pA).Bat[shipIndex];
		if (pplayer == 'B') ship = &(*pB).Bat[shipIndex];
	}
	if (!strcmp("CRU", spaceStr)) {
		if (pplayer == 'A') ship = &(*pA).Cru[shipIndex];
		if (pplayer == 'B') ship = &(*pB).Cru[shipIndex];
	}
	if (!strcmp("DES", spaceStr)) {
		if (pplayer == 'A') ship = &(*pA).Des[shipIndex];
		if (pplayer == 'B') ship = &(*pB).Des[shipIndex];
	}

	if (pplayer == 'A') placeShipExt(pA, y, x, d, ship, plansza, group, str, zeroones, *planszaY, *planszaX);
	if (pplayer == 'B') placeShipExt(pB, y, x, d, ship, plansza, group, str, zeroones, *planszaY, *planszaX);

}

void initPosHandle(char* str, int* initPosA, int* initPosB) {

	int i = 0; 
  int j = 0;
	int k = 0; 
  int l = 0;
	int m = 0; 
  int n = 0;
	int number1[3];
	int number2[3];
	int number3[3];
	int number4[3];
	char d = '\0';
	while (str[i] != '\0')
	{

		if (str[i] == ' ')
		{
			j++; i++;
			continue;
		}
		switch (j)
		{
		case 0: break;

		case 1:
			d = str[i];
			break;

		case 2:
			number1[k++] = (str[i] - '0');
			break;

		case 3:
			number2[l++] = (str[i] - '0');
			break;

		case 4:
			number3[m++] = (str[i] - '0');
			break;

		case 5:
			number4[n++] = (str[i] - '0');
			break;

		}

		i++;

	}

	if (d == 'A') {

		initPosA[0] = constructNumber(number1, k);
		initPosA[1] = constructNumber(number2, l);
		initPosA[2] = constructNumber(number3, m);
		initPosA[3] = constructNumber(number4, n);

	}
	if (d == 'B') {

		initPosB[0] = constructNumber(number1, k);
		initPosB[1] = constructNumber(number2, l);
		initPosB[2] = constructNumber(number3, m);
		initPosB[3] = constructNumber(number4, n);

	}

}

void reefHandle(char* str, char** plansza, int* planszaX, int* planszaY) {

	int i = 0; 
  int j = 0;
	int k = 0; 
  int l = 0;
	int number1[3];
	int number2[3];
	int x; 
  int y;

	while (str[i] != '\0')
	{

		if (str[i] == ' ')
		{
			j++; i++;
			continue;
		}

		switch (j)
		{

		case 0: break;

		case 1:
			number1[k++] = (str[i] - '0');
			break;

		case 2:
			number2[l++] = (str[i] - '0');
			break;
		}

		i++;

	}
	y = constructNumber(number1, k);
	x = constructNumber(number2, l);

	if (y >= (*planszaY) || y < 0 || x < 0 || x >= (*planszaX)) {

		printf("INVALID OPERATION \"%s\": REEF IS NOT PLACED ON BOARD", str);
		freeMemory(plansza, *planszaY);
		exit(0);

	}

	plansza[y][x] = '#';

}

void boardSizeHandle(char* str, char** plansza, int* planszaX, int* planszaY) {

	int i = 0; 
  int j = 0;
	int m = 0; 
  int n = 0;

	int numbers[2];
	int number1[3];
	int number2[3];

	while (str[i] != '\0') {

		if (str[i] == ' ')
		{
			j++; i++;
			continue;
		}
		switch (j)
		{
		case 0: break;

		case 1:
			number1[n++] = (str[i] - '0');
			break;

		case 2:
			number2[m++] = (str[i] - '0');
			break;

		}

		i++;

	}

	numbers[0] = constructNumber(number1, n);
	numbers[1] = constructNumber(number2, m);

	for (int o = 0; o < boardSizeY; o++) {
		free(plansza[o]);
	}

	plansza = (char**)realloc(plansza, numbers[0] * sizeof(char*));

	for (int o = 0; o < numbers[0]; o++) {
		plansza[o] = (char*)malloc(numbers[1] * sizeof(char));
	}

	*planszaX = numbers[1];
	*planszaY = numbers[0];
  
	for (int l = 0; l < *planszaY; l++) {
		for (int z = 0; z < *planszaX; z++) {
			plansza[l][z] = ' ';
		}
	}

}

void moveHandle(char* str, int* group, char** plansza, Player* pA, Player* pB, int* planszaY, int* planszaX) {

	int i = 0; 
  int j = 0;
	int k = 0;
	int shipIndex = 0;
	char d = '\0';
	char spaceStr[4];

	while (str[i] != '\0')
	{

		if (str[i] == ' ')
		{
			j++; i++;
			continue;
		}

		switch (j)
		{

		case 0: break;

		case 1:
			shipIndex = (str[i] - '0');
			break;

		case 2:
			spaceStr[k++] = str[i];
			break;

		case 3:
			d = str[i];
			break;

		}

		i++;
	}

	spaceStr[3] = '\0';

	Ship* ship = &((*pA).Car[shipIndex]);


	if (!strcmp("CAR", spaceStr)) {
		if (*group == 1) ship = &(*pA).Car[shipIndex];
		if (*group == 2) ship = &(*pB).Car[shipIndex];
	}
	if (!strcmp("BAT", spaceStr)) {
		if (*group == 1) ship = &(*pA).Bat[shipIndex];
		if (*group == 2) ship = &(*pB).Bat[shipIndex];
	}
	if (!strcmp("CRU", spaceStr)) {
		if (*group == 1) ship = &(*pA).Cru[shipIndex];
		if (*group == 2) ship = &(*pB).Cru[shipIndex];
	}
	if (!strcmp("DES", spaceStr)) {
		if (*group == 1) ship = &(*pA).Des[shipIndex];
		if (*group == 2) ship = &(*pB).Des[shipIndex];
	}

  if(plansza[ship->engine[0]][ship->engine[1]]!='x'){

    Move(ship, d, plansza, *planszaY, *planszaX, str);

  }

}

void shootHandle(char* str, char** plansza, Player* pA, Player* pB, int* planszaX, int* planszaY) {

	int i = 0; 
  int j = 0;
	int m = 0; 
  int n = 0;
	int numbers[2];
	int number1[3];
	int number2[3];
	while (str[i] != '\0') {

		if (str[i] == ' ')
		{
			j++; i++;
			continue;
		}

		switch (j)
		{

		case 0: break;

		case 1:
			number1[n++] = (str[i] - '0');
			break;

		case 2:
			number2[m++] = (str[i] - '0');
			break;
		}

		i++;
	}

	numbers[0] = constructNumber(number1, n);
	numbers[1] = constructNumber(number2, m);

	shoot(numbers[0], numbers[1], plansza, pA, pB, str, *planszaY, *planszaX);

}

void spyHandle(char* str, int* group, char** plansza, Player* pA, Player* pB, int* planszaY) {

	int i = 0; 
  int j = 0;
	int m = 0; 
  int n = 0;
	int shipIndex = 0;
	int numbers[2];
	int number1[3];
	int number2[3];

	while (str[i] != '\0') {

		if (str[i] == ' ')
		{
			j++; i++;
			continue;
		}
		switch (j)
		{
		case 0: break;

		case 1:
			shipIndex = (str[i] - '0');
			break;

		case 2:
			number1[n++] = (str[i] - '0');
			break;

		case 3:
			number2[m++] = (str[i] - '0');
			break;

		}

		i++;
	}

	numbers[0] = constructNumber(number1, n);
	numbers[1] = constructNumber(number2, m);

	if (*group == 1) {
		if ((*pA).Car[shipIndex].howManySpies == 5) {
			printf("INVALID OPERATION \"%s\": ALL PLANES SENT", str);
			freeMemory(plansza, *planszaY);
			exit(0);
		}

		if (plansza[(*pA).Car[shipIndex].cannon[0]][(*pA).Car[shipIndex].cannon[1]] == 'x') {
			printf("INVALID OPERATION \"%s\": CANNOT SEND PLANE", str);
			freeMemory(plansza, *planszaY);
			exit(0);
		}

		(*pA).Car[shipIndex].spy[(*pA).Car[shipIndex].howManySpies][0] = numbers[0];
		(*pA).Car[shipIndex].spy[(*pA).Car[shipIndex].howManySpies][1] = numbers[1];
		(*pA).Car[shipIndex].howManySpies++;

	}
	else if (*group == 2) {

		if ((*pB).Car[shipIndex].howManySpies == 5) {
			printf("INVALID OPERATION \"%s\": ALL PLANES SENT", str);
			freeMemory(plansza, *planszaY);
			exit(0);
		}
    
		if (plansza[(*pB).Car[shipIndex].cannon[0]][(*pB).Car[shipIndex].cannon[1]] == 'x') {
			printf("INVALID OPERATION \"%s\": CANNOT SEND PLANE", str);
			freeMemory(plansza, *planszaY);
			exit(0);
		}

		(*pB).Car[shipIndex].spy[(*pB).Car[shipIndex].howManySpies][0] = numbers[0];
		(*pB).Car[shipIndex].spy[(*pB).Car[shipIndex].howManySpies][1] = numbers[1];
		(*pB).Car[shipIndex].howManySpies++;

	}

}

void saveHandle(char** plansza, Player* pA, Player* pB, int* nextPlayer, int* initPosA, int* initPosB, int* planszaX, int* planszaY, int* extendedShips) {

	printf("[state]\n");

	if (*extendedShips == 1) printf("EXTENDED_SHIPS\n");

	printf("BOARD_SIZE %d %d\n", *planszaY, *planszaX);

	for (int i = 0; i < *planszaY; i++) {
		for (int j = 0; j < *planszaX; j++) {
			if (plansza[i][j] == '#') printf("REEF %d %d\n", i, j);
		}
	}

	char c = *nextPlayer == 1 ? 'A' : 'B';

	printf("NEXT_PLAYER %c\n", c);

	for (int m = 1; m < 3; m++) {

		m == 1 ? printf("INIT_POSITION A %d %d %d %d\n", initPosA[0], initPosA[1], initPosA[2], initPosA[3]) : printf("INIT_POSITION B %d %d %d %d\n", initPosB[0], initPosB[1], initPosB[2], initPosB[3]);

		int CarSumA = 0; int BatSumA = 0; int CruSumA = 0; int DesSumA = 0;
		int CarSumB = 0; int BatSumB = 0; int CruSumB = 0; int DesSumB = 0;

		for (int i = 0; i < 10; i++) {

			if (m == 1) {
				CarSumA += !!(*pA).Car[i].size;
				BatSumA += !!(*pA).Bat[i].size;
				CruSumA += !!(*pA).Cru[i].size;
				DesSumA += !!(*pA).Des[i].size;
			}

			if (m == 2) {
				CarSumB += !!(*pB).Car[i].size;
				BatSumB += !!(*pB).Bat[i].size;
				CruSumB += !!(*pB).Cru[i].size;
				DesSumB += !!(*pB).Des[i].size;
			}

		}

		m == 1 ? printf("SET_FLEET A %d %d %d %d\n", CarSumA, BatSumA, CruSumA, DesSumA) : printf("SET_FLEET B %d %d %d %d\n", CarSumB, BatSumB, CruSumB, DesSumB);

		Player* p = pA;

		if (m == 1) p = pA;
		if (m == 2) p = pB;

		for (int j = 0; j < 10; j++) {

			if ((*p).Car[j].isPlaced == 1) {

				int numbers[5];

				int y = (*p).Car[j].pos[0];
				int x = (*p).Car[j].pos[1];

				for (int k = 0; k < 5; k++) {

					if (plansza[y][x] == '+') numbers[k] = 1;
					if (plansza[y][x] == 'x') numbers[k] = 0;

					if ((*p).Car[j].dir == 'N') y++;
					else if ((*p).Car[j].dir == 'S') y--;
					else if ((*p).Car[j].dir == 'W') x++;
					else if ((*p).Car[j].dir == 'E') x--;

				}




				m == 1 ? printf("SHIP A %d %d %c %d CAR %d%d%d%d%d\n", (*p).Car[j].pos[0], (*p).Car[j].pos[1], (*p).Car[j].dir, j, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]) : printf("SHIP B %d %d %c %d CAR %d%d%d%d%d\n", (*p).Car[j].pos[0], (*p).Car[j].pos[1], (*p).Car[j].dir, j, numbers[0], numbers[1], numbers[2], numbers[3], numbers[4]);

			}

		}

		for (int j = 0; j < 10; j++) {

			if ((*p).Bat[j].isPlaced == 1) {

				int numbers[4];

				int y = (*p).Bat[j].pos[0];
				int x = (*p).Bat[j].pos[1];

				for (int k = 0; k < 4; k++) {

					if (plansza[y][x] == '+') numbers[k] = 1;
					if (plansza[y][x] == 'x') numbers[k] = 0;

					if ((*p).Bat[j].dir == 'N') y++;
					else if ((*p).Bat[j].dir == 'S') y--;
					else if ((*p).Bat[j].dir == 'W') x++;
					else if ((*p).Bat[j].dir == 'E') x--;

				}




				m == 1 ? printf("SHIP A %d %d %c %d BAT %d%d%d%d\n", (*p).Bat[j].pos[0], (*p).Bat[j].pos[1], (*p).Bat[j].dir, j, numbers[0], numbers[1], numbers[2], numbers[3]) : printf("SHIP B %d %d %c %d BAT %d%d%d%d\n", (*p).Bat[j].pos[0], (*p).Bat[j].pos[1], (*p).Bat[j].dir, j, numbers[0], numbers[1], numbers[2], numbers[3]);

			}

		}

		for (int j = 0; j < 10; j++) {

			if ((*p).Cru[j].isPlaced == 1) {

				int numbers[3];

				int y = (*p).Cru[j].pos[0];
				int x = (*p).Cru[j].pos[1];

				for (int k = 0; k < 3; k++) {

					if (plansza[y][x] == '+') numbers[k] = 1;
					if (plansza[y][x] == 'x') numbers[k] = 0;

					if ((*p).Cru[j].dir == 'N') y++;
					else if ((*p).Cru[j].dir == 'S') y--;
					else if ((*p).Cru[j].dir == 'W') x++;
					else if ((*p).Cru[j].dir == 'E') x--;
				}


				m == 1 ? printf("SHIP A %d %d %c %d CRU %d%d%d\n", (*p).Cru[j].pos[0], (*p).Cru[j].pos[1], (*p).Cru[j].dir, j, numbers[0], numbers[1], numbers[2]) : printf("SHIP B %d %d %c %d CRU %d%d%d\n", (*p).Cru[j].pos[0], (*p).Cru[j].pos[1], (*p).Cru[j].dir, j, numbers[0], numbers[1], numbers[2]);

			}

		}

		for (int j = 0; j < 10; j++) {

			if ((*p).Des[j].isPlaced == 1) {

				int numbers[2];

				int y = (*p).Des[j].pos[0];
				int x = (*p).Des[j].pos[1];

				for (int k = 0; k < 2; k++) {

					if (plansza[y][x] == '+') numbers[k] = 1;
					if (plansza[y][x] == 'x') numbers[k] = 0;

					if ((*p).Des[j].dir == 'N') y++;
					else if ((*p).Des[j].dir == 'S') y--;
					else if ((*p).Des[j].dir == 'W') x++;
					else if ((*p).Des[j].dir == 'E') x--;
				}

				m == 1 ? printf("SHIP A %d %d %c %d DES %d%d\n", (*p).Des[j].pos[0], (*p).Des[j].pos[1], (*p).Des[j].dir, j, numbers[0], numbers[1]) : printf("SHIP B %d %d %c %d DES %d%d\n", (*p).Des[j].pos[0], (*p).Des[j].pos[1], (*p).Des[j].dir, j, numbers[0], numbers[1]);

			}

		}

	}


	printf("[state]");

}
