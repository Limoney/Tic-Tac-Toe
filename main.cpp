#include <iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <cstdlib>

using namespace std;
char plansza[3][3]{ ' ',' ',' ',	' ',' ',' ',	' ',' ',' ', };	//|zmienne globalne i funkcje|
int height, width, j = -1, l = 0;									
void Move();														
void DrawMap();													
void ChcekPosition();												
void GameState();													
bool Round();														
bool CheckArray();													
void dev();															
void Restart();														
void MapRestart();													
int x = 4, y = 2;													
int m = 0, n = 0;													
int PlayersTurn = 0;												
char Winner;														
void Menu();														
void MenuTile();													
void StartGame();													
int GameMode = 0;													
void CheckGameMode();												
char KoniecGry;														
//
////////////////////////////////////////////////
//
void gotoxy(int x, int y)
{
	COORD c;

	c.X = x;

	c.Y = y;

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//
////////////////////////////////////////////////
//
int main()
{
	Menu();
	return 0;
}
//
////////////////////////////////////////////////
//
void Move()
{
	gotoxy(x, y);
	char PlayerMove;
	while (true)
	{
		gotoxy(x, y);  PlayerMove = getch();
		system("cls");
		switch (PlayerMove)
		{
		case 'a': x -= 9;	n--;				 ChcekPosition();
			DrawMap(); gotoxy(x, y);
			break;
		case 'd': x += 9;	n++;				 ChcekPosition();
			DrawMap(); gotoxy(x, y);
			break;
		case 's': y += 4;	m++;				 ChcekPosition();
			DrawMap(); gotoxy(x, y);
			break;
		case 'w': y -= 4;	m--;				 ChcekPosition();
			DrawMap(); gotoxy(x, y);
			break;
		case 'e':	KoniecGry = 'n'; MapRestart(); Menu();
			break;
		case 'x':
			if (Round() == true)
			{
				if (CheckArray() == false)
				{
					DrawMap();
					PlayersTurn--;
					system("cls"); DrawMap();
					cout << "to pole jest juz zajete!" << endl;
				}
				else
				{
					plansza[m][n] = 'x'; DrawMap(); GameState();
				}
			}
			else
			{
				DrawMap();
				cout << "Teraz jest tura O";
				PlayersTurn--;
			}
			break;
		case 'o':
			if (Round() == false)
			{
				if (CheckArray() == false)
				{
					DrawMap();
					PlayersTurn--;
					system("cls"); DrawMap();
					cout << "to pole jest juz zajete!" << endl;
				}
				else
				{
					plansza[m][n] = 'o'; DrawMap();	GameState();
				}
			}
			else
			{
				DrawMap();
				cout << "Teraz jest tura X";
				PlayersTurn--;
			}
			break;
		default:	DrawMap();	cout << "Nie ma takiej opcji" << endl; cout << PlayerMove;
		}
	}
}
//
////////////////////////////////////////////////
//
void DrawMap()
{
	for (int i = 3; i > 0; i--)
	{
		for (int i = 0; i < 3; i++)
		{
			cout << "---------";
		}
		cout << endl;
		while (l < 9)
		{
			if (l < 3 || l>5)
			{
				cout << "|       |";
			}
			else cout << "|   " << plansza[j][l] << "   |";
			if (l == 2 || l == 5 || l == 8)
			{
				cout << endl;
			}
			l++;
		}
		l = 0;
		j++;
	}
	cout << "---------------------------" << endl;
	dev();//do usuniecia
	j = -1;
	l = 0;
}
//
////////////////////////////////////////////////
//
void ChcekPosition()
{
	if (x < 4)
	{
		x = 4;		n++;
	}
	else if (x > 22)
	{
		x = 22;		n--;
	}
	else if (y < 2)
	{
		y = 2;		m++;
	}
	else if (y > 10)
	{
		y = 10;		m--;
	}
}
//
////////////////////////////////////////////////
//
void GameState()
{
	//poziom
	if ((plansza[0][0] != ' ') && (plansza[0][0] == plansza[0][1]) && (plansza[0][1] == plansza[0][2]))
	{
		CheckGameMode(); Restart();
	}

	else if ((plansza[1][0] != ' ') && (plansza[1][0] == plansza[1][1]) && (plansza[1][1] == plansza[1][2]))
	{
		CheckGameMode(); Restart();
	}

	else if ((plansza[2][0] != ' ') && (plansza[2][0] == plansza[2][1]) && (plansza[2][1] == plansza[2][2]))
	{
		CheckGameMode(); Restart();
	}




	//pion
	else if ((plansza[0][0] != ' ') && (plansza[0][0] == plansza[1][0]) && (plansza[1][0] == plansza[2][0]))
	{
		CheckGameMode(); Restart();
	}

	else if ((plansza[0][1] != ' ') && (plansza[0][1] == plansza[1][1]) && (plansza[1][1] == plansza[2][1]))
	{
		CheckGameMode(); Restart();
	}

	else if ((plansza[0][2] != ' ') && (plansza[0][2] == plansza[1][2]) && (plansza[1][2] == plansza[2][2]))
	{
		CheckGameMode(); Restart();
	}




	//skosy
	else if ((plansza[0][0] != ' ') && (plansza[0][0] == plansza[1][1]) && (plansza[1][1] == plansza[2][2]))
	{
		CheckGameMode(); Restart();
	}

	else if ((plansza[0][2] != ' ') && (plansza[0][2] == plansza[1][1]) && (plansza[1][1] == plansza[2][0]))
	{
		CheckGameMode();  Restart();
	}




	//remis
	else if ((plansza[0][0] != ' ') && (plansza[0][1] != ' ') && (plansza[0][2] != ' ') && (plansza[1][0] != ' ') && (plansza[1][1] != ' ') && (plansza[1][2] != ' ') && (plansza[2][0] != ' ') && (plansza[2][1] != ' ') && (plansza[2][2] != ' '))
	{
		cout << endl << "Remis" << endl; Restart();
	}//naprawic buga powodujacego wyswietlenie remisu przy pelnej planszy po wygranej!
}
//
////////////////////////////////////////////////
//
bool Round()
{
	PlayersTurn++;
	if (PlayersTurn % 2 == 0)
	{
		Winner = 'X';
		return true;
	}
	else
	{
		Winner = 'O';
		return false;
	}
}
//
////////////////////////////////////////////////
//
bool CheckArray()
{
	if (plansza[m][n] == 'x' || plansza[m][n] == 'o')	return false;
	else												return true;
}
//
////////////////////////////////////////////////
//
void Restart()
{
	do
	{
		KoniecGry = NULL;
		cout << "Koniec gry! Chcesz zagrac jeszcze raz? (t/n)"; KoniecGry = getch();
		if (KoniecGry == 'n')
		{
			MapRestart();
			Menu();
		}
		else  if (KoniecGry == 't')
		{
			MapRestart();
		}
		else
		{
			cout << "Wybierz opcje tak lub nie!" << endl;
		}
	} while ((KoniecGry != 'n') && (KoniecGry != 't'));
}
//
////////////////////////////////////////////////
//
void MapRestart()
{
	PlayersTurn = 0;
	system("cls");
	//"c" i "g" to kolejne odpowiedniki l i j do czyszczenia tablicy
	int g = 0, c = 0;
	for (int i = 0; i <= 8; i++)
	{
		plansza[g][c] = ' ';
		c++;
		if (c == 3)
		{
			c = 0;
			g++;
		}
	}
	if (KoniecGry == 'n')GameMode = 0;
	if (KoniecGry == 't')DrawMap();
}
//
////////////////////////////////////////////////
//
void dev()
{
	//dev 
	cout << endl << "m:" << m << endl;
	cout << "n:" << n << endl;
	cout << "x:" << x << endl;
	cout << "y:" << y << endl;
	cout << "Tura:" << PlayersTurn << endl;
	if (PlayersTurn % 2 == 0)
	{
		cout << "Tura O" << endl;
	}
	else
	{
		cout << "Tura X" << endl;
	}
	//dev
}
//
////////////////////////////////////////////////
//
void Menu()
{
	system("cls");
	int Choose;
	int tiles = 5;
	for (int i = 0; i <= tiles; i++) { MenuTile(); }
	gotoxy(2, 2);  cout << "1) Kolko i krzyzyk - Klasyczne";
	gotoxy(2, 7);  cout << "2) Kolko i krzyzyk - Misere";
	gotoxy(2, 12); cout << "3) Sterowanie";
	gotoxy(2, 17); cout << "4) O Autorze";
	gotoxy(2, 22); cout << "5)  Wyjscie";
	gotoxy(2, 27); cout << "Twoj Wybor: ";

	while (true)
	{
		Choose = getch();
		switch (Choose)
		{
		case 49: system("cls"); GameMode = 1; StartGame();  break;
		case 50: system("cls"); GameMode = 2; StartGame();  break;
		case 51:  break;
		case 52:  break;
		case 53:  exit(0); break;
		//default: cout << "Nie ma takiej opcji!";
		}
	}
}
//
////////////////////////////////////////////////
//
void MenuTile()
{
								  cout << "------------------------------------" << endl;
	for (int i = 0; i < 3; i++)   cout << "|                                  |" << endl;
								  cout << "------------------------------------" << endl;
}
//
////////////////////////////////////////////////
//
void StartGame()
{
	while (true)
	{
		DrawMap();
		Move();
	}
}
//
////////////////////////////////////////////////
//
void CheckGameMode()
{
	if (GameMode == 1)
	{
		cout << endl << "Wygrywa " << Winner << "!" << endl;
	}
	else if (GameMode == 2)
	{
		if (Winner == 'X')	Winner = 'O';
		else Winner = 'X';
		cout << endl << "Wygrywa " << Winner << "!" << endl;
	}
}
