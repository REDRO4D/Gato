#include <stdio.h>
#include <conio.h>
#include <windows.h>

void gotoxy(int x, int y);
void drawBoard();
void drawCircle(int PosX, int PosY);
void drawCross(int posX, int posY);
void showPieces(char pieces[3][3]);

bool menu(int tecla);
bool choosePiece();
int game(bool extremeMode, int key, bool player1cross);
bool choosePiece();
void showGameOver(int player);
void drumAnimation();

char getKey(int key);
void refresh();
char gameOver(char pieces[3][3]);

int main(){
	/*
		x aumenta de 16 + 10 de los caracteres
		y aumenta de 8
	*/
	/*
		ancho = 120 caracteres
		alto = 29 caracteres
	*/
	system("title Gato");
	system("color F1");//06
	
	short int posX = 50;
	short int posY = 100;
	int key,mode=0,player;
	bool player1cross, extremeMode;
	
	while(true){
		extremeMode = menu(key);
		player1cross = choosePiece();
		player = game(extremeMode, key, player1cross);
		showGameOver(player);
	}
	return 0;
	
}

void gotoxy(int x, int y){
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X=x;
	dwPos.Y=y;
	SetConsoleCursorPosition(hcon,dwPos);
}

void drawBoard(){
	//Inicio del tablero en (40,2)
	
	for(int i=2; i<25; i++){//Primera vertical
		gotoxy(54,i);//+14
		printf("лл");
	}
	
	for(int i=2; i<25; i++){//Segunda vertical
		gotoxy(70,i);//+16
		printf("лл");
	}
	
	for(int i=0; i<45; i+=2){//Primera horizontal
		gotoxy(i+40,9);
		printf("лл");
	}
	
	for(int i=0; i<45; i+=2){//Segunda horizontal 
		gotoxy(i+40,17);//+8
		printf("лл");
	}
	
}

void drawCircle(int posX, int posY){
	for(short int y=0; y<5; y++){//vertical
		for(short int x=0; x<10; x+=2){//horizontal, aumenta de 2 en 2 por los dos caracteres a imprimir
			if(y==0 || y==4){//lado superior e inferior
				gotoxy(posX+x,posY+y);
				printf("лл");
			}
			if(x==0 || x==8){//lado izquierdo y derecho
				if(y==0 || y==4){
					gotoxy(posX+x,posY+y);//Quita las esquinas para internar hacer un circulo
					printf("  ");
				}else{
					gotoxy(posX+x,posY+y);
					printf("лл");
				}				
			}
		}
	}
}

void drawCross(int posX, int posY){
	short int x1 = 0;
	short int x2 = 8;
	
	for(short int y=0; y<5; y++){//vertical
		gotoxy(posX+x1,posY+y);
		printf("лл");
		
		gotoxy(posX+x2,posY+y);
		printf("лл");
		
		x1+=2;
		x2-=2;
	}
}

bool menu(int tecla){
	int option = 2;
	char p=168,O=224,r=22;
	bool ready = false, extremeMode = false;
	do{
		drawBoard();
		drawCircle(42,3);
		drawCircle(74,3);
		drawCircle(42,19);
		drawCircle(74,19);
		
		drawCross(58,3);
		drawCross(42,11);
		drawCross(74,11);
		drawCross(58,19);
		
		gotoxy(10,6);
		printf("%cC%cMO SE JUEGA?",p,O);
		for(int i=9;i<26;i++){
			gotoxy(i,7);
			printf("Ф");
		}
		
		gotoxy(7,12);
		printf("CAMBIAR MODO DE JUEGO");
		for(int i=6;i<29;i++){
			gotoxy(i,13);
			printf("Ф");
		}
		
		gotoxy(14,23);
		printf("JUGAR");
		for(int i=13;i<20;i++){
			gotoxy(i,24);
			printf("Ф");
		}
		
		switch(option){
			case 0:{//Como se juega
				for(int i=9;i<26;i++){
					gotoxy(i,7);
					printf("%c",223);
				}
				gotoxy(17,7);
				break;
			}
			case 1:{//Modos de juego
				for(int i=6;i<29;i++){
					gotoxy(i,13);
					printf("%c",223);
				}
				gotoxy(17,13);
				break;
			}
			case 2:{//Jugar
				for(int i=13;i<20;i++){
					gotoxy(i,24);
					printf("%c",223);
				}
				gotoxy(16,24);
				break;
			}
		}
		
		tecla = getch();
		refresh();
		
		switch( getKey(tecla) ){
			case 'u':{
				if(option>0){
					option--;
				}
				break;
			}
			case 'd':{
				if(option<2){
					option++;
				}
				break;
			}
			case 'e':{
				switch(option){
					case 0:{
						
						break;
					}
					case 1:{
						extremeMode = !extremeMode;
						printf("Modo de juego cambiado a ");
						if(extremeMode){
							printf("'Modo invisible'");
						}else{
							printf("'Modo normal'");
						}
						break;
					}
					case 2:{
						ready=true;
						break;
					}
				}
				break;
			}
		}
	}while(ready!=true);
	return extremeMode;
}

bool choosePiece(){
	char p=168,tecla;
	bool piece = false, ready = false;
	/*
		ancho = 120 caracteres
		alto = 29 caracteres
	*/
	do{
		refresh();
		gotoxy(48,2);
		printf("JUGADOR 1, ELIJA SU FICHA");
		
		for(int i=4; i<29; i++){
			gotoxy(60,i);
			printf("л");
		}
		
		drawCircle(25,14);
		drawCross(85,14);
		
		if(piece==false){//Circle
			for(int i=0; i<20; i++){
				gotoxy(20+i,20);
				printf("л");
			}
		}else{
			for(int i=0; i<20; i++){
				gotoxy(80+i,20);
				printf("л");
			}
		}
		
		tecla = getch();
		
		switch(getKey(tecla)){
			case 'l':{
				piece = false;
				break;
			}
			case 'r':{
				piece = true;
				break;
			}
			case 'e':{
				ready = true;
				break;
			}
		}
	}while(ready!=true);
	
	return piece;
}


int game(bool extremeMode, int key, bool player1cross){
	char pieces[3][3];
	int pos[2][2];
	short int player = 1;
	short int x,y;
	
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			pos[i][j] = 0;
		}
	}
	
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			pieces[i][j] = 32;
		}
	}
	
	refresh();
	do{
		switch(getKey(key)){
			case 'u':{
				if(player==1){
					if(pos[0][1]>0){
						pos[0][1]--;
					}
				}else{
					if(pos[1][1]>0){
						pos[1][1]--;
					}
				}
				break;
			}
			case 'd':{
				if(player==1){
					if(pos[0][1]<2){
						pos[0][1]++;
					}
				}else{
					if(pos[1][1]<2){
						pos[1][1]++;
					}
				}
				break;
			}
			case 'l':{
				if(player==1){
					if(pos[0][0]>0){
						pos[0][0]--;
					}
				}else{
					if(pos[1][0]>0){
						pos[1][0]--;
					}
				}
				break;
			}
			case 'r':{
				if(player==1){
					if(pos[0][0]<2){
						pos[0][0]++;
					}
				}else{
					if(pos[1][0]<2){
						pos[1][0]++;
					}
				}
				break;
			}
			case 'e':{
				if(player==1){
					pos[1][0] = 0;
					pos[1][1] = 0;
					if(pieces[ pos[0][1] ][ pos[0][0] ] == ' '){
						if(player1cross){
							pieces[ pos[0][1] ][ pos[0][0] ] = 'x';
						}else{
							pieces[ pos[0][1] ][ pos[0][0] ] = 'o';
						}
						player=!player;
					}else{
						gotoxy(55,28);
						printf("Espacio ocupado");
					}
				}else{
					pos[0][0] = 0;
					pos[0][1] = 0;
					if(pieces[ pos[1][1] ][ pos[1][0] ] == ' '){
						if(!player1cross){
							pieces[ pos[1][1] ][ pos[1][0] ] = 'x';
						}else{
							pieces[ pos[1][1] ][ pos[1][0] ] = 'o';
						}
						player=!player;
					}else{
						gotoxy(55,28);
						printf("Espacio ocupado");
					}
				}
				break;
			}
		}
		
		drawBoard();
		
		if(player == 1){
			switch(pos[0][0]){
				case 0:{
					x = 42;
					break;
				}
				case 1:{
					x = 58;
					break;
				}
				case 2:{
					x = 74;
					break;
				}
			}
			switch(pos[0][1]){
				case 0:{
					y = 3;
					break;
				}
				case 1:{
					y = 11;
					break;
				}
				case 2:{
					y = 19;
					break;
				}
			}
			if(player1cross){
				drawCross(x,y);
			}else{
				drawCircle(x,y);
			}
			gotoxy(x, y+5);
			printf("%c%c  J1  %c%c",196,196,196,196);
		}else{
			switch(pos[1][0]){
				case 0:{
					x = 42;
					break;
				}
				case 1:{
					x = 58;
					break;
				}
				case 2:{
					x = 74;
					break;
				}
			}
			switch(pos[1][1]){
				case 0:{
					y = 3;
					break;
				}
				case 1:{
					y = 11;
					break;
				}
				case 2:{
					y = 19;
					break;
				}
			}
			if(!player1cross){
				drawCross(x,y);
			}else{
				drawCircle(x,y);
			}
			gotoxy(x, y+5);
			printf("%c%c  J2  %c%c",196,196,196,196);
		}
		
		if(!extremeMode){
			showPieces(pieces);
		}
		
		
		if( gameOver(pieces) == ' '){
			key = getch();
		}
		refresh();
	}while(gameOver(pieces) == ' ');
	
	if(gameOver(pieces) != '-'){
		if(player==1){//Correcion de ganador
			player=2;
		}else{
			player = 1;
		}
	}else{
		player = 0;
	}
	return player;
}

void player(int player){
	switch(player){
		case 1:{
			
			break;
		}
		
		case 2:{
			
			break;
		}
	}
}

void refresh(){
	fflush(stdin);
	system("cls");
}

char getKey(int key){
	char _key;
	switch(key){
		case 119:
		case 72:{
			//printf("UP / ARRIBA");
			_key = 'u';
			break;
		}
		case 97:
		case 75:{
			//printf("LEFT / IZQUIERDA");
			_key = 'l';
			break;
		}
		case 115:
		case 80:{
			//printf("DOWN / ABAJO");
			_key = 'd';
			break;
		}
		case 100:
		case 77:{
			//printf("RIGHT / DERECHA");
			_key = 'r';
			break;
		}
		case 13:{
			//printf("ENTER");
			_key = 'e';
			break;
		}
		default:{
			//printf("DIFERENT KEY: %d",tecla);
			_key = 'Д';
			break;
		}
	}
	return _key;
}

void showPieces(char pieces[3][3]){
	short int x,y;
	
	for(int i=0; i<3; i++){//Vericales
		switch(i){
			case 0:{
				y = 3;
				break;
			}
			case 1:{
				y = 11;
				break;
			}
			case 2:{
				y = 19;
				break;
			}
		}
		for(int j=0; j<3; j++){//Horizontales
			switch(j){
				case 0:{
					x = 42;
					break;
				}
				case 1:{
					x = 58;
					break;
				}
				case 2:{
					x = 74;
					break;
				}
			}
			switch(pieces[i][j]){
				case 'x':{
					drawCross(x,y);
					break;
				}
				case 'o':{
					drawCircle(x,y);
					break;
				}
			}
		}
	}
}

char gameOver(char pieces[3][3]){
	char winner = ' ';
	int numberPieces = 0;
	
	//Horizontales
	for(int i=0; i<3; i++){
		if(pieces[i][0] == 'x' && pieces[i][1] == 'x' && pieces[i][2] == 'x'){
			winner = 'x';
			break;
		}else if(pieces[i][0] == 'o' && pieces[i][1] == 'o' && pieces[i][2] == 'o'){
			winner = 'o';
			break;
		}
	}
	
	//Verticales
	for(int i=0; i<3; i++){
		if(pieces[0][i] == 'x' && pieces[1][i] == 'x' && pieces[2][i] == 'x'){
			winner = 'x';
			break;
		}else if(pieces[0][i] == 'o' && pieces[1][i] == 'o' && pieces[2][i] == 'o'){
			winner = 'o';
			break;
		}
	}
	
	//Diagonal a la derecha
	if(pieces[0][0] == 'x' && pieces[1][1] == 'x' && pieces[2][2] == 'x'){
		winner = 'x';
	}else if(pieces[0][0] == 'o' && pieces[1][1] == 'o' && pieces[2][2] == 'o'){
		winner = 'o';
	}
	
	//Diagonal a la izquierda
	if(pieces[0][2] == 'x' && pieces[1][1] == 'x' && pieces[2][0] == 'x'){
		winner = 'x';
	}else if(pieces[0][2] == 'o' && pieces[1][1] == 'o' && pieces[2][0] == 'o'){
		winner = 'o';
	}
	
	//Gato
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if(pieces[i][j] == 'x' || pieces[i][j] == 'o'){
				numberPieces++;
			}
		}
	}
	if(numberPieces == 9 && winner==' '){
		winner = '-';
	}
	
	return winner;
}

void showGameOver(int player){
	drumAnimation();
	switch(player){
		case 0:{//Empate
			printf("\n\n\n\n\n");
			printf("                         лллллл    лл  лллллллл  лллллл    лллллллл  лллллллл                  лл\n");
			printf("                         лл  лл    лл  лл    лл  лл    лл     лл     лл                      лл\n");
			printf("                         лл  лл    лл  лл    лл  лл    лл     лл     лл            лллл    лл\n");
			printf("                         лл  лл    лл  лл    лл  лл    лл     лл     лл            лллл  лл\n");
			printf("                         лл  лл    лл  лл    лл  лл    лл     лл     лл                  лл\n");
			printf("                         лл  лл    лл  лл    лл  лл    лл     лл     лл                  лл\n");
			printf("                         лл    лл  лл  лллллллл  лл    лл     лл     лллллллл            лл\n");
			printf("                         лл    лл  лл  лл    лл  лл    лл     лл     лл            лллл  лл\n");
			printf("                         лл    лл  лл  лл    лл  лл    лл     лл     лл            лллл   лл\n");
			printf("                         лл    лл  лл  лл    лл  лл    лл     лл     лл                     лл\n");
			printf("                         лл    лллллл  лл    лл  лллллл    лллллллл  лллллллл                 лл\n");
			break;
		}
		
		case 1:{
			printf("\n\n\n\n\n");
			printf("     лллллллл  лл                    лл  лл    лл  лллллллл  лллллллл  лллллл    лллллллл  лллллл            лл   \n");
			printf("     лл        лл                    лл  лл    лл  лл        лл    лл  лл    лл  лл    лл  лл    лл        лллл   \n");
			printf("     лл        лл                    лл  лл    лл  лл        лл    лл  лл    лл  лл    лл  лл    лл       лл лл   \n");
			printf("     лл        лл                    лл  лл    лл  лл        лл    лл  лл    лл  лл    лл  лл    лл          лл   \n");
			printf("     лл        лл                    лл  лл    лл  лл        лл    лл  лл    лл  лл    лл  лл    лл          лл   \n");
			printf("     лллллллл  лл                    лл  лл    лл  лл        лл    лл  лл    лл  лл    лл  лл    лл          лл   \n");
			printf("     лл        лл                    лл  лл    лл  лллллллл  лллллллл  лл    лл  лл    лл  лллллл            лл   \n");
			printf("     лл        лл                    лл  лл    лл  лл    лл  лл    лл  лл    лл  лл    лл  лл    лл          лл   \n");
			printf("     лл        лл                    лл  лл    лл  лл    лл  лл    лл  лл    лл  лл    лл  лл    лл          лл   \n");
			printf("     лл        лл                    лл  лл    лл  лл    лл  лл    лл  лл    лл  лл    лл  лл    лл          лл   \n");
			printf("     лллллллл  лллллллл        лллллллл  лллллллл  лллллллл  лл    лл  лллллл    лллллллл  лл    лл       лллллллл\n");
			break;
		}
		
		case 2:{
			printf("\n\n\n");
			printf("     лллллллл  лл                    лл  лл    лл  лллллллл  лллллллл  лллллл    лллллллл  лллллл         лллллллл\n");
			printf("     лл        лл                    лл  лл    лл  лл        лл    лл  лл    лл  лл    лл  лл    лл             лл\n");
			printf("     лл        лл                    лл  лл    лл  лл        лл    лл  лл    лл  лл    лл  лл    лл             лл\n");
			printf("     лл        лл                    лл  лл    лл  лл        лл    лл  лл    лл  лл    лл  лл    лл             лл\n");
			printf("     лл        лл                    лл  лл    лл  лл        лл    лл  лл    лл  лл    лл  лл    лл             лл\n");
			printf("     лллллллл  лл                    лл  лл    лл  лл        лл    лл  лл    лл  лл    лл  лл    лл             лл\n");
			printf("     лл        лл                    лл  лл    лл  лллллллл  лллллллл  лл    лл  лл    лл  лллллл         лллллллл\n");
			printf("     лл        лл                    лл  лл    лл  лл    лл  лл    лл  лл    лл  лл    лл  лл    лл       лл      \n");
			printf("     лл        лл                    лл  лл    лл  лл    лл  лл    лл  лл    лл  лл    лл  лл    лл       лл      \n");
			printf("     лл        лл                    лл  лл    лл  лл    лл  лл    лл  лл    лл  лл    лл  лл    лл       лл      \n");
			printf("     лллллллл  лллллллл        лллллллл  лллллллл  лллллллл  лл    лл  лллллл    лллллллл  лл    лл       лллллллл\n");
			break;
		}
	}
	printf("\n\n\n\n\n\n\n                                      PRESIONE CUALQUER TECLA PARA REGRESAR AL MENU");
	getch();
	refresh();
}

void drumAnimation(){
	short int times = 0;
	
	for(int i=0; i<9; i++){
		refresh();
		printf("\n\n                                                     Y EL GANADOR ES...\n");
		switch(times){
			case 0:{
				printf("\n\n\n");
				printf("                                ВВ                                               ВВ\n");
				printf("                              ВВ                                               ВВ\n");
				printf("                            ВВ                                               ВВ\n");
				printf("                          ВВ                                               ВВ\n");
				printf("                        ВВ                                               ВВ\n");
				printf("                      ВВ                      ВВ                       ВВ                      ВВ\n");
				printf("                                            ВВ                                               ВВ  \n");
				printf("                             лллллллллллл ВВ                                  лллллллллллл ВВ    \n");
				printf("                           лл           ВВл                                 лл           ВВл     \n");
				printf("                         лл           ВВ   лл                             лл           ВВ   лл   \n");
				printf("                         лл         ВВ     лл                             лл         ВВ     лл   \n");
				printf("                         лллл            лллл                             лллл            лллл   \n");
				printf("                         лл лллллллллллллл лл                             лл лллллллллллллл лл   \n");
				printf("                         лл л     лл     л лл                             лл л     лл     л лл   \n");
				printf("                         лл л     лл     л лл                             лл л     лл     л лл   \n");
				printf("                           лл     лл     лл                                 лл     лл     лл     \n");
				printf("                             лллллллллллл                                     лллллллллллл       \n");
				times++;
				break;
			}
			case 1:{
				printf("\n\n\n");
				printf("                                                                         \n");
				printf("                                                                         \n");
				printf("                                                                         \n");
				printf("                                                                         \n");
				printf("                                                                         \n");
				printf("                      ВВВВВВВВВВВВ  ВВВВВВВВВВВВ                       ВВВВВВВВВВВВ  ВВВВВВВВВВВВ\n");
				printf("                                                                                                 \n");
				printf("                             лллллллллллл                                     лллллллллллл       \n");
				printf("                           лл            лл                                 лл            лл     \n");
				printf("                         лл                лл                             лл                лл   \n");
				printf("                         лл                лл                             лл                лл   \n");
				printf("                         лллл            лллл                             лллл            лллл   \n");
				printf("                         лл лллллллллллллл лл                             лл лллллллллллллл лл   \n");
				printf("                         лл л     лл     л лл                             лл л     лл     л лл   \n");
				printf("                         лл л     лл     л лл                             лл л     лл     л лл   \n");
				printf("                           лл     лл     лл                                 лл     лл     лл     \n");
				printf("                             лллллллллллл                                     лллллллллллл       \n");
				times++;
				break;
			}
			case 2:{
				printf("\n\n\n");
				printf("                                    ВВ                                               ВВ          \n");
				printf("                                      ВВ                                               ВВ        \n");
				printf("                                        ВВ                                               ВВ      \n");
				printf("                                          ВВ                                               ВВ    \n");
				printf("                                            ВВ                                               ВВ  \n");
				printf("                      ВВ                      ВВ                       ВВ                      ВВ\n");
				printf("                        ВВ                                               ВВ                      \n");
				printf("                          ВВ лллллллллллл                                  ВВ лллллллллллл       \n");
				printf("                           лВВ           лл                                 лВВ           лл     \n");
				printf("                         лл   ВВ           лл                             лл   ВВ           лл   \n");
				printf("                         лл     ВВ         лл                             лл     ВВ         лл   \n");
				printf("                         лллл            лллл                             лллл            лллл   \n");
				printf("                         лл лллллллллллллл лл                             лл лллллллллллллл лл   \n");
				printf("                         лл л     лл     л лл                             лл л     лл     л лл   \n");
				printf("                         лл л     лл     л лл                             лл л     лл     л лл   \n");
				printf("                           лл     лл     лл                                 лл     лл     лл     \n");
				printf("                             лллллллллллл                                     лллллллллллл       \n");
				times++;
				break;
			}
			case 3:{
				printf("\n\n\n");
				printf("                                                                         \n");
				printf("                                                                         \n");
				printf("                                                                         \n");
				printf("                                                                         \n");
				printf("                                                                         \n");
				printf("                      ВВВВВВВВВВВВ  ВВВВВВВВВВВВ                       ВВВВВВВВВВВВ  ВВВВВВВВВВВВ\n");
				printf("                                                                                                 \n");
				printf("                             лллллллллллл                                     лллллллллллл       \n");
				printf("                           лл            лл                                 лл            лл     \n");
				printf("                         лл                лл                             лл                лл   \n");
				printf("                         лл                лл                             лл                лл   \n");
				printf("                         лллл            лллл                             лллл            лллл   \n");
				printf("                         лл лллллллллллллл лл                             лл лллллллллллллл лл   \n");
				printf("                         лл л     лл     л лл                             лл л     лл     л лл   \n");
				printf("                         лл л     лл     л лл                             лл л     лл     л лл   \n");
				printf("                           лл     лл     лл                                 лл     лл     лл     \n");
				printf("                             лллллллллллл                                     лллллллллллл       \n");
				times = 0;
				break;
			}
		}
		Sleep(100);
	}
	
	refresh();
}
