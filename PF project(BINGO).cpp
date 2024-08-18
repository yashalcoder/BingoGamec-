#include<iostream>
#include<cstdlib>
#include<string>
#include<cstring>
#include<iomanip>
#include<fstream>


using namespace std;

void mainMenu();
void boardrand(int board[][5]);
void PlayGame();
void Printboard(int board[5][5]);
bool toss();
void moves(int& score1, int& score2, int board1[5][5], int board2[5][5], bool& t, string player1, string player2);
void score(int board1[][5], int board2[][5], int& score1, int& score2);
void filehandling(string player1, string player2, int score1, int score2);
void gengameid(int& gameid);


bool check1 = 0, check2 = 0, check3 = 0, check4 = 0, check5 = 0, check6 = 0, check7 = 0, check8 = 0, check9 = 0, check10 = 0, check11 = 0, check12 = 0;
bool checkk1 = 0, checkk2 = 0, checkk3 = 0, checkk4 = 0, checkk5 = 0, checkk6 = 0, checkk7 = 0, checkk8 = 0, checkk9 = 0, checkk10 = 0, checkk11 = 0, checkk12 = 0;
int gameid;

int main()
{
	mainMenu();


	system("pause");
	return 0;
}

void mainMenu()
{
	gengameid(gameid);

	check1 = 0, check2 = 0, check3 = 0, check4 = 0, check5 = 0, check6 = 0, check7 = 0, check8 = 0, check9 = 0, check10 = 0, check11 = 0, check12 = 0;
	checkk1 = 0, checkk2 = 0, checkk3 = 0, checkk4 = 0, checkk5 = 0, checkk6 = 0, checkk7 = 0, checkk8 = 0, checkk9 = 0, checkk10 = 0, checkk11 = 0, checkk12 = 0;
	system("color F0");
	char x;
	char exitt;
	bool check = true;
	while (check == true)
	{
		cout << "\t\t\t\t\t Welcome To Bingo\n";     //displaying menu
		cout << "\t\t\t\t\t 1.Play Game \n";
		cout << "\t\t\t\t\t 2.Game History \n";
		cout << "\t\t\t\t\t 3.How To Play \n";
		cout << "\t\t\t\t\t 4.Exit \n\n";
		cout << "\t\t\t\t\t Select An Option From Above:";
		cin >> x;


		if (x == '1')           //selecting conditions from the above menu
		{
			PlayGame();					//start the game
			check = false;
		}
		else if (x == '2') // Game History
		{
			system("color 0F");
			cout << "\n\n\t\t\t\t\t Game History\n\n";
			char ch;
			ifstream fin;
			fin.open("gamehistory.txt");
			while (!fin.eof())
			{
				fin.get(ch);
				if (!fin.eof())
					cout << ch;

			}
			fin.close();
			system("pause");
			system("cls");
			mainMenu();
		}
		else if (x == '3')   //game instructions
		{
			system("cls");
			cout << "game instructons\n\n";

			cout << "1. Each Game contains a unique id.\n";
			cout << "2. There Will be two Unique Random Number (1-25) BINGO Cards" << endl;
			cout << "3. the player who won the toss whould start the game" << endl;
			cout << "5. The cards will be switched at each player's turn." << endl;								//instructons
			cout << "6. Each Player will choose a number in his turn from the Card " << endl;
			cout << "7. Selected number will be replaced with 0 " << endl;
			cout << "8. The same number in another Player's Card will be replaced with 0." << endl;
			cout << "9. For a winning card, check  combinations of below\n";

			cout << "Score is added to the player when any row (or column or diagonal) is equal to 0." << endl;
			cout << "Winner will be the player who will First Reach the Score 5.\n" << endl;

			system("pause");


			check = true;
		}
		else if (x == '4')				//exiting
		{
			cout << "are you sure You Want To Exit:Y OR N\n";
			cin >> exitt;
			switch (exitt)
			{
			case 'Y':
			case 'y':
				check = false;
				exit(0);						//confirming if user wants to exit
				break;
			case 'n':
			case'N':
				system("cls");
				check = true;
			}

		}
		else
		{
			cout << "Enter Correct Input\n\n";
			check = true;
			system("pause");
			system("cls");
		}


	}
	return;
}

void boardrand(int board[][5])						//Function for inserting random numbers in the board from 1-25
{


	int i, j, num = 1;

	while (num <= 25)
	{
		i = rand() % 5;
		j = rand() % 5;

		if (board[i][j] == 0)
		{
			board[i][j] = num;
			++num;
		}
	}



	return;


}

void PlayGame()											//starting game
{

	int score1 = 0, score2 = 0;
	int board1[5][5] = { 0 };
	int board2[5][5] = { 0 };
	string player1, player2;
	bool turn;
	srand(time(0));

	cout << "Enter Player1 Name: ";						//Inserting players name
	
	getline(cin, player1);

	cout << "Enter Player2 Name: ";
	getline(cin, player2);



	turn = toss();
	if (turn)
	{
		cout << player1 << " Wins The Toss\n\n";				//toss for starting the game
	}
	else
	{
		cout << player2 << " Wins The Toss\n\n";
	}
	system("pause");
	boardrand(board1);
	boardrand(board2);										//inserting random numbers in the boards



	while (score1 < 5 && score2 < 5)
	{
		moves(score1, score2, board1, board2, turn, player1, player2);				// taking inputs from user
		score(board1, board2, score1, score2);											//calculting score




	}
	if (score2 >= 5)									//winning conditions
	{
		system("color 0B");

		cout << "\n" << "\t\t\t\t\t" << player2 << " WINS \n";
		cout << "\n" << "\t\t\t\t\t" << "Your Score IS:" << score2 << endl;
		cout << "\n" << "\t\t\t\t\t" << "Your GameId Is:" << gameid << endl;
		cout << "\n" << "\t\t\t\t\t";



	}
	else if (score1 >= 5)
	{
		system("color 04");
		cout << "\n" << "\t\t\t\t\t" << player1 << " WINS \n";
		cout << "\n" << "\t\t\t\t\t" << "Your Score IS:" << score1 << endl;
		cout << "\n" << "\t\t\t\t\t" << "Your GameId Is:" << gameid << endl;
		cout << "\n" << "\t\t\t\t\t";


	}

	filehandling(player1, player2, score1, score2);


hereee:
	char exitt;														//asking user if he wants to exit or return to main menu
	system("pause");
	system("cls");
	cout << "Press Y IF You Want To Exit OR N To Return to Main Menu:";
	cin >> exitt;
	switch (exitt)
	{
	case 'Y':
	case 'y':

		exit(0);
		break;
	case 'n':
	case 'N':
		system("cls");
		main();
		break;

	default:																	//displaying error for incorrect input
		cout << "enter Correct Input!!\n";
		goto hereee;
	}



	return;
}

bool toss()									//function for toss
{
	if (rand() % 2 == 0)
		return true;
	else
		return false;
}

void Printboard(int board[5][5])							//function for printing board
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 5; j++)
		{
			if (j == 0 || j < 5 || i == 0 || i <= 5)
			{
				cout << setw(3) << board[i][j] << "|";

			}

			else
			{
				cout << " ";
			}

		}
		cout << endl;

	}
	return;
}

// function for making moves taking inputs from user

void moves(int& score1, int& score2, int board1[5][5], int board2[5][5], bool& t, string player1, string player2)
{
	bool fcheck = true;
	if (score1 != 5 || score2 != 5)
	{


		if (t) {
			system("cls");
			system("color 04");											//coloring the console and text			
			cout << "ITS " << player1 << "'s Turn\n\n";
			cout << "Your Score IS:" << score1 << endl;						//displaying user scorre

			Printboard(board1);										//printing board
		reenter:																			//goto func used incase of wrong input
			char ch[10];
			int num;
			cout << "Choose a Number From Above Card:";
			cin >> ch;															//taking input
			num = atoi(ch);																	//func used for converting char array to int

			if (!(num > 0 && num <= 25))
			{
				cout << "Wrong Input\n\n";														//displaying error incase of wrong input
				goto reenter;
			}

			for (int i = 0; i < 5; ++i)
			{
				for (int j = 0; j < 5; ++j)
				{
					if (board1[i][j] == num)
					{
						fcheck = true;
						//searching board if enterd number is in it

					}
					else if (board1[i][j] != num)
					{
						fcheck = false;
					}
					if (fcheck)
					{
						board1[i][j] = 0;											//replacing the number with zero
						break;
					}

				}
				if (fcheck)												//breaking loop if number is found
					break;
			}

			if (fcheck == false)												//displaying error if number is not in the board 
			{


				cout << "Wrong Input!!! Please Chose a Number From Above Card\n\n";
				goto reenter;														//using goto incase of wrong input

			}
			for (int i = 0; i < 5; ++i)
			{													//removing number from the second board
				for (int j = 0; j < 5; ++j)
				{
					if (board2[i][j] == num)
					{
						board2[i][j] = 0;

					}

				}
			}


			t = false;									//changing value for other players turn
		}
		else
		{
			system("cls");
			system("color 0B");																//coloring console and text
			cout << "ITS " << player2 << "'s Turn\n\n";

			cout << "Your Score IS:" << score2 << endl;

			Printboard(board2);														//printing board				
		reenter1:
			char ch[10];
			int num;
			cout << "Choose a Number From Above Card:";
			cin >> ch;																//taking input from user
			num = atoi(ch);


			if (!(num > 0 && num <= 25))											//displaying error incase of wrong input
			{
				cout << "Wrong Input\n\n";
				goto reenter1;
			}

			for (int i = 0; i < 5; ++i)												//finding and removing number from board
			{
				for (int j = 0; j < 5; ++j)
				{
					if (board2[i][j] == num)
					{
						fcheck = true;
					}
					else
					{
						fcheck = false;
					}
					if (fcheck)
					{
						board2[i][j] = 0;
						break;
					}

				}
				if (fcheck)
					break;

			}

			if (fcheck == false)								//displayin errror if no is not present in the board	
			{

				cout << "Wrong Input!!! Please Chose a Number From Above Card\n\n";
				goto reenter1;

			}

			//removing number from second board
			for (int i = 0; i < 5; ++i)
			{
				for (int j = 0; j < 5; ++j)
				{
					if (board1[i][j] == num)
					{

						board1[i][j] = 0;

					}

				}
			}


			//changing turn value for other persons turn
			t = true;
		}
	}


	return;
}

void score(int board1[][5], int board2[][5], int& score1, int& score2)							//function for calculating score
{
	//checking rows columns and diagonals for calculating score

	if (board1[0][0] == 0 && board1[0][1] == 0 && board1[0][2] == 0 && board1[0][3] == 0 && board1[0][4] == 0 && check1 == 0)
	{
		score1 = score1 + 1;
		check1 = 1;
	}
	if (board1[1][0] == 0 && board1[1][1] == 0 && board1[1][2] == 0 && board1[1][3] == 0 && board1[1][4] == 0 && check2 == 0)
	{
		score1 = score1 + 1;
		check2 = 1;
	}
	if (board1[2][0] == 0 && board1[2][1] == 0 && board1[2][2] == 0 && board1[2][3] == 0 && board1[2][4] == 0 && check3 == 0)
	{
		score1 = score1 + 1;
		check3 = 1;
	}
	if (board1[3][0] == 0 && board1[3][1] == 0 && board1[3][2] == 0 && board1[3][3] == 0 && board1[3][4] == 0 && check4 == 0)
	{
		score1 = score1 + 1;
		check4 = 1;
	}
	if (board1[4][0] == 0 && board1[4][1] == 0 && board1[4][2] == 0 && board1[4][3] == 0 && board1[4][4] == 0 && check5 == 0)
	{
		score1 = score1 + 1;
		check5 = 1;
	}
	if (board1[0][0] == 0 && board1[1][0] == 0 && board1[2][0] == 0 && board1[3][0] == 0 && board1[4][0] == 0 && check6 == 0)
	{
		score1 = score1 + 1;
		check6 = 1;
	}
	if (board1[0][1] == 0 && board1[1][1] == 0 && board1[2][1] == 0 && board1[3][1] == 0 && board1[4][1] == 0 && check7 == 0)
	{
		score1 = score1 + 1;
		check7 = 1;
	}
	if (board1[0][2] == 0 && board1[1][2] == 0 && board1[2][2] == 0 && board1[3][2] == 0 && board1[4][2] == 0 && check8 == 0)
	{
		score1 = score1 + 1;
		check8 = 1;
	}
	if (board1[0][3] == 0 && board1[1][3] == 0 && board1[2][3] == 0 && board1[3][3] == 0 && board1[4][3] == 0 && check9 == 0)
	{
		score1 = score1 + 1;
		check9 = 1;
	}
	if (board1[0][4] == 0 && board1[1][4] == 0 && board1[2][4] == 0 && board1[3][4] == 0 && board1[4][4] == 0 && check10 == 0)
	{
		score1 = score1 + 1;
		check10 = 1;
	}
	if (board1[0][0] == 0 && board1[1][1] == 0 && board1[2][2] == 0 && board1[3][3] == 0 && board1[4][4] == 0 && check11 == 0)
	{
		score1 = score1 + 1;
		check11 = 1;
	}
	if (board1[0][4] == 0 && board1[1][3] == 0 && board1[2][2] == 0 && board1[3][1] == 0 && board1[4][0] == 0 && check12 == 0)
	{
		score1 = score1 + 1;
		check12 = 1;
	}
	//using different statements for board 2

	if (board2[0][0] == 0 && board2[0][1] == 0 && board2[0][2] == 0 && board2[0][3] == 0 && board2[0][4] == 0 && checkk1 == 0)
	{
		score2 = score2 + 1;
		checkk1 = 1;
	}
	if (board2[1][0] == 0 && board2[1][1] == 0 && board2[1][2] == 0 && board2[1][3] == 0 && board2[1][4] == 0 && checkk2 == 0)
	{
		score2 = score2 + 1;
		checkk2 = 1;
	}
	if (board2[2][0] == 0 && board2[2][1] == 0 && board2[2][2] == 0 && board2[2][3] == 0 && board2[2][4] == 0 && checkk3 == 0)
	{
		score2 = score2 + 1;
		checkk3 = 1;
	}
	if (board2[3][0] == 0 && board2[3][1] == 0 && board2[3][2] == 0 && board2[3][3] == 0 && board2[3][4] == 0 && checkk4 == 0)
	{
		score2 = score2 + 1;
		checkk4 = 1;
	}
	if (board2[4][0] == 0 && board2[4][1] == 0 && board2[4][2] == 0 && board2[4][3] == 0 && board2[4][4] == 0 && checkk5 == 0)
	{
		score2 = score2 + 1;
		checkk5 = 1;
	}
	if (board2[0][0] == 0 && board2[1][0] == 0 && board2[2][0] == 0 && board2[3][0] == 0 && board2[4][0] == 0 && checkk6 == 0)
	{
		score2 = score2 + 1;
		checkk6 = 1;
	}
	if (board2[0][1] == 0 && board2[1][1] == 0 && board2[2][1] == 0 && board2[3][1] == 0 && board2[4][1] == 0 && checkk7 == 0)
	{
		score2 = score2 + 1;
		checkk7 = 1;
	}
	if (board2[0][2] == 0 && board2[1][2] == 0 && board2[2][2] == 0 && board2[3][2] == 0 && board2[4][2] == 0 && checkk8 == 0)
	{
		score2 = score2 + 1;
		checkk8 = 1;
	}
	if (board2[0][3] == 0 && board2[1][3] == 0 && board2[2][3] == 0 && board2[3][3] == 0 && board2[4][3] == 0 && checkk9 == 0)
	{
		score2 = score2 + 1;
		checkk9 = 1;
	}
	if (board2[0][4] == 0 && board2[1][4] == 0 && board2[2][4] == 0 && board2[3][4] == 0 && board2[4][4] == 0 && checkk10 == 0)
	{
		score2 = score2 + 1;
		checkk10 = 1;
	}
	if (board2[0][0] == 0 && board2[1][1] == 0 && board2[2][2] == 0 && board2[3][3] == 0 && board2[4][4] == 0 && checkk11 == 0)
	{
		score2 = score2 + 1;
		checkk11 = 1;
	}
	if (board2[0][4] == 0 && board2[1][3] == 0 && board2[2][2] == 0 && board2[3][1] == 0 && board2[4][0] == 0 && checkk12 == 0)
	{
		score2 = score2 + 1;
		checkk12 = 1;
	}

	return;
}

void filehandling(string player1, string player2, int score1, int score2)				//storing data in file
{
	ofstream fout;
	fout.open("gamehistory.txt", ios::app);
	if (!(fout.is_open()))
	{
		cout << "File cannot open.";

	}
	fout << "Game ID:" << gameid;
	fout << endl;
	fout << "Players Name:" << player1 << "\t" << player2;
	fout << endl;
	fout << player1 << "'s score:" << score1 << endl;
	fout << player2 << "'s score:" << score2;
	fout << endl << endl;
	fout.close();

	fout.open("gameid.txt", ios::app);
	if (!(fout.is_open()))
	{
		cout << "File cannot open.";

	}
	fout << gameid << " ";
	fout.close();


	return;
}
void gengameid(int& gameid)				//generating game id
{

	srand(time(0));
	int gid;
	bool gen = 1;

	ifstream fin;
	ofstream fout;
	fout.open("gameid.txt", ios::app);						//using another file for unique game id 
	fout << rand() % 10000 << " ";
	fout.close();

	fin.open("gameid.txt");
up:
	gameid = rand() % 10000;
	while (!(fin.eof()))
	{
		if (!(fin.eof()))											//checking for unique game id searching in file
		{
			fin >> gid;
			if (gid == gameid)
			{
				gen = false;
			}
			else {
				gen = true;
			}
		}
	}
	if (gen == false)
		goto up;

	fin.close();

	return;
}




















