#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

//Variable...

int GameOver;
const int width = 80;
const int height = 20;
int x,y;
int Applex,Appley;
int score = 0;
int velocity = 1;

int Tailx[100], Taily[100];
int nTail;

enum eDirection{ STOP = 0, LEFT, RIGHT, UP, DOWN};
enum eDirection dir;


//Functions...

void Setup(){

	GameOver = 0;
	dir = STOP;
	x = width/2;
	y = height/2;
	Applex = rand() % width;
	Appley = rand() % height;


}

void Draw(){



	//Creating GameMap...

	//Starting Wall...
	for(int i = 0; i < width + 2; i++)
		printf("#");


	printf("\n");





	for(int i = 0; i <  height ; i++){
		for(int j = 0; j < width ; j++){
			if(j == 0){
				printf("#");
			}
			if(y == i && x == j){
				printf("o");
			}
			else if(Appley == i && Applex == j){
				printf("*");
			}
			else{

                int track = 0;

                for(int k = 0; k < nTail; k++){
                    if(Tailx[k] == j && Taily[k] == i){
                        printf("o");
                        track = 1;
                    }
                }

                if(!track){
                    printf(" ");
                }


			}

			if(j == width - 1){
				printf("#");
			}
		}
		printf("\n");


	}





	//Ending Wall...
	for(int i = 0; i < width + 2; i++)
		printf("#");

	printf("\n");
    printf("SCORE : %d ",score);
	system("cls");//Clear console...
}


void Input(){

	if(kbhit()){

		switch(getch()){

			case 'a':
				dir = LEFT;
				break;

			case 'd':
				dir = RIGHT;
				break;

			case 'w':
				dir = UP;
				break;

			case 's':
				dir = DOWN;
				break;

			case 'x':
				GameOver = 1;
				break;

		}
	}
}

void Logic(){

    int prevx = Tailx[0];
    int prevy = Taily[0];
    int prec2x,prev2y;

    // Tail follows the snake head coordinates...

    Tailx[0] = x;
    Taily[0] = y;

    for(int i = 1; i < nTail; i++){
        prec2x = Tailx[i];
        prev2y = Taily[i];

        Tailx[i] = prevx;
        Taily[i] = prevy;

        prevx = prec2x;
        prevy = prev2y;
    }
	switch (dir){

		case LEFT:
			x -= velocity;
			break;

		case RIGHT:
			x += velocity;
			break;

		case UP:
			y -= velocity;
			break;

		case DOWN:
			y += velocity;
			break;

	}

	if(x > width || x < 0 || y >  height || y < 0){
		GameOver = 1;
	}

	if(x == Applex && y == Appley){
        score = score + 1;
        Applex = rand() % width;
        Appley = rand() % height;
        nTail++;
	}
}


int main(){

	Setup();

	while (GameOver == 0){

	Draw();
	Input();
	Logic();

	}

    return 0;
}
