#include <iostream>
#include <cstdio>
#include <conio.h>
#include <cstdlib>
#include<Windows.h>
#include "time.h" // needed to use time functions
#include "stdlib.h" // needed to use rand function

using namespace std;


//Declared Function prototypes
void mainMenu();
int exitGame();
int tryAgain();
void instructions();
void playGame(int gameGrid[8][8]);
void gameBoard(int gameGrid[8][8]);
void updateGameBoard(int gameGrid[8][8]);
char selectLetter(int gameGrid);
void playerMove(int gameGrid[][8]);
void swapGems(int arr[8][8], int x1, int y1, int x2, int y2);
void findMatches(int board[][8]);
void yMatchesRemove(int board[][8], int width, int height, int count, int x, int y);
void xMatchesRemove(int board[][8], int width, int height, int count, int x, int y);
void cascade(int gameGrid[][8], int width, int height);
void replaceGems(int gameGrid[][8], int width);


int main()
{
	int height = 8;
	int width = 8;
	//array for game board this is passed into functions to update it.
	int gameGrid[8][8];
	//variables stored to hold player input then passed into swapGems function
	int x1, y1, x2, y2;

	int playAgain = 0;

	srand(time(NULL)); // 'seeds' random number generator with current time

	//Variable to hold the number of turns the player has
	int turns = 20;

	printf("****BEJEWELLED****\n\n");

	//calls the main menu function to display menu options and get user input
	mainMenu();
	//has the gameGrid passed into the function so the random letter are set up
	playGame(gameGrid);

	bool isDone = false;

	//variable to keep the while loop running while it is true
	while (isDone == false)
	{
		//makes sure there are no matches before the game starts
		findMatches(gameGrid);
		findMatches(gameGrid);
		findMatches(gameGrid);

		//prints updated board after matches are removed
		updateGameBoard(gameGrid);

		//prints the number of turns the player has left
		printf("Turns Left: %d\n\n", turns);
		int rowCheck;
		int columnCheck;
		
		tryAgain();
		do
		{
			printf("enter row of letter you want to move or press '0' to quit:");
			scanf_s("%d", &x1);

			//allows the player to quit the game
			if (x1 == 0)
			{
				return 0;
			}

			printf("enter column of letter you want to move or press '0' to quit:");
			scanf_s("%d", &y1);

			//allows the player to quit the game
			if (y1 == 0)
			{
				return 0;
			}

			printf("enter the row you want the letter to move to or press '0' to quit:");
			scanf_s("%d", &x2);


			//allows the player to quit the game
			if (x2 == 0)
			{
				return 0;
			}

			printf("enter the column you want to move the leter to or press '0' to quit:");
			scanf_s("%d", &y2);

			//allows the player to quit the game
			if (y2 == 0)
			{
				return 0;
			}

			rowCheck = abs(x2 - x1);
			columnCheck = abs(y2 - y1);

		} while ((rowCheck != 1) && (columnCheck != 1) && (x1 <= height) && (y1 <= width) && (x2 <= height) && (y2 <= width));
			
		
		
		swapGems(gameGrid, x1 -= 1, y1 -= 1, x2 -= 1, y2 -= 1);

		//finds matches after player takes turn
		findMatches(gameGrid);

		//updates board again to show player
		updateGameBoard(gameGrid);


		//takes 1 away from the turns variable
		turns--;

		//Game ends
		if (turns == 0)
		{
			printf("\n\nGame Over!\n\n");
			isDone = true;
		}
	}

	printf("Enter a 1 if you would like to play again or 0 to quit: ");
	scanf_s("%d", &playAgain);

	if (playAgain == 1)
	{
		return main();
	}
	else
	{
		return 0;
	}

}

//Displays menu and gets users menu choice
void mainMenu()
{
	//variable to store players choice
	int menuChoice;

	//printing menu options
	printf("****Main Menu****\n\n");
	printf("1. Play Game\n");
	printf("2. Instructions\n");
	printf("3. Exit Game\n\n");

	//getting user to enter choice
	printf("Enter a choice (1, 2 or 3):");
	scanf_s("%d", &menuChoice);

	//checks menuChoice with each of the cases below and if true runs the code in that case
	switch (menuChoice)
	{
	case 1:
		system("CLS");

		break;
	case 2:
		instructions();
		break;
	case 3:

		break;
		//checks for invalid input
	default:
		printf("Invalid Input!");
		_getch();
		system("CLS");
		return mainMenu();
		break;
	}
}

int tryAgain()
{
	return 1;
}

int exitGame()
{
	printf("Press any key to continue...\n");
	_getch();
	return 0;
}

//displays instructions and gives user option to start game, got to main menu or quit
void instructions()
{
	//clears the text on the screen from before the function
	system("CLS");
	int playerChoice;
	printf("****Instructions****\n\n");

	//prints instructions
	printf("- The game will load an 8x8 grid of random gems.\n");
	printf("- the aim is to line up 3 or more gems in a row to remove them.\n");
	printf("- To move the gems you first need to enter the coordinates of the gem you want to move.\n");
	printf("- Then enter the coordinates of the gem you want to swap it with it.\n");
	printf("- This gem has to be above, below or next to the gem you are moving otherwise its an invalid move.\n");
	printf("- You have 20 turns till the game ends.\n");


	printf("1. Main Menu\n");
	printf("2. Play Game\n");
	printf("3. Exit Game\n");
	printf("What do you want to do?");
	scanf_s("%d", &playerChoice);

	//checks playerChoice with each of the cases below and if true runs the code in that case
	switch (playerChoice)
	{
	case 1:
		system("CLS");
		mainMenu();
		break;
	case 2:
		system("CLS");

		break;
	default:
		printf("Invalid input!");
		_getch();
		return instructions();
	}
}

//reads in the gamegrid array and passes it to the gameBoard function
void playGame(int gameGrid[][8])
{
	printf("****Play Game****\n\n");
	gameBoard(gameGrid);
}

//prints out the game board with random letters
//only called once in program
void gameBoard(int gameGrid[8][8])
{
	int width = 8;
	int height = 8;
	int coord = 1;

	printf("0 1 2 3 4 5 6 7 8\n"); //gives the board coordinates

	//prints the array
	for (int i = 0; i < height; i++)
	{
		printf("%d ", coord); //gives the board coordinates
		for (int j = 0; j < width; j++)
		{
			gameGrid[i][j] = (rand() % 5); // generates random integer between 0 and 4;

			//selectletter function takes the random numbers in the grid and gives it a letter to display.
			printf("%c ", selectLetter(gameGrid[i][j]));
		}
		printf("\n");
		coord++;
	}
}

//called more than GameBoard becasue it doesnt randomise the values in the array again
//keeps previous values.
void updateGameBoard(int gameGrid[8][8])
{
	system("CLS");
	int width = 8;
	int height = 8;
	int coord = 1;

	//Prints updated array
	printf("0 1 2 3 4 5 6 7 8\n"); //gives the board coordinates
	for (int i = 0; i < height; i++)
	{
		printf("%d ", coord); //gives the board coordinates
		for (int j = 0; j < width; j++)
		{
			printf("%c ", selectLetter(gameGrid[i][j]));
		}
		printf("\n");
		coord++;
	}
}

//gives each random value in array a letter
char selectLetter(int gameGrid)
{
	char randLetter;

	switch (gameGrid)
	{
	case 0:
		randLetter = 'A';
		break;
	case 1:
		randLetter = 'B';
		break;
	case 2:
		randLetter = 'C';
		break;
	case 3:
		randLetter = 'D';
		break;
	case 4:
		randLetter = 'E';
		break;

	}

	//for setting the removed values to blanks
	if (gameGrid == 5)
	{
		randLetter = ' ';
	}

	return randLetter;
}

void swapGems(int arr[8][8], int x1, int y1, int x2, int y2) {

	//temporarily stores the first gem coordinates
	int temp = arr[x1][y1];
	//sets the first gem equal to the second gem
	arr[x1][y1] = arr[x2][y2];
	// sets the second gem equal to the first gem
	arr[x2][y2] = temp;
}

//finds matches of 3 or more and removes them
void findMatches(int gameGrid[8][8])
{
	int width = 8;
	int height = 8;

	bool stopLoop = false;
	int count = 1;

	//////////////////////////////
	//////checking each row//////
	//////////////////////////////
	//loops through every element of the array
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			stopLoop = false;
			while (stopLoop == false)
			{
				//checks see if the gem infront is the same as current gem
				if ((gameGrid[i][j]) == (gameGrid[i][j + count]))
				{
					count++;
				}
				else stopLoop = true;

			}

			//if the function has counted 3 or more of the same gems in a row it will remove the gems
			if ((count >= 3) && (j < width - 2))
			{
				//removes the gems and sets them to blanks
				yMatchesRemove(gameGrid, width, height, count, i, j);
				count = 1;
			}
			else if (count <= 2)
			{
				count = 1;
			}

		}
	}

	count = 1;

	/////////////////////////////
	////checking each column////
	/////////////////////////////

	//loops through every value in array
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			stopLoop = false;
			while (stopLoop == false)
			{
				//checks to see if the gem below is the same as the current gem
				if ((gameGrid[i][j]) == (gameGrid[i + count][j]))
				{
					count++;
				}
				else stopLoop = true;
			}

			//if the function has counted 3 or more of the same gems in a row it will remove the gems
			if ((count >= 3) && (i < height - 2))
			{
				//removes the gems and sets them to blanks
				xMatchesRemove(gameGrid, width, height, count, i, j);
				count = 1;

			}
			else if (count <= 2)
			{
				count = 1;
			}
		}
	}
	//brings values down and replaces with new values
	cascade(gameGrid, width, height);
}

//removes matches in the rows
void yMatchesRemove(int board[8][8], int width, int height, int count, int x, int y)
{
	int matchesCount = count + y;
	for (int i = y; i < matchesCount; i++)
	{
		board[x][i] = 5; //sets the y value of array to a 5 which is a blank space when printed
	}
}

//removes matches in the columns
void xMatchesRemove(int board[8][8], int width, int height, int count, int x, int y)
{
	int matchesCount = count + x;
	for (int i = x; i < matchesCount; i++)
	{
		board[i][y] = 5; //sets the x value of array to a 5 which is a blank space when printed
	}
}

//moves gems down when blank space is below
void cascade(int gameGrid[][8], int width, int height)
{
	int isDone = 0;

	while (isDone < 5) //runs the code ten times
	{
		//loops through every element of the array
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width; j++)
			{
				//if the current gem is not blank and the gem below is the gem gets moved down
				if ((gameGrid[i][j] != 5) && (gameGrid[i + 1][j] == 5))
				{
					//moves the current gem to the space below it
					gameGrid[i][j] ^= gameGrid[i + 1][j];
					//moves the empty space to where the gem was
					gameGrid[i + 1][j] ^= gameGrid[i][j];
					gameGrid[i][j] ^= gameGrid[i + 1][j];

					isDone = 1;
				}
			}
		}
		isDone++;
		//replaces empty spaces with new gems
		replaceGems(gameGrid, width);
		updateGameBoard(gameGrid);
		//allows you to see the cascade happen
		Sleep(100);  //time delay
	}

}
//replaces empy spaces with new random gems
void replaceGems(int gameGrid[][8], int width)
{
	int stop = 0;
	//loops through the top row only
	for (int i = 0; i < width; i++)
	{
		int randLetter = (rand() % 5);
		//sets any blank spaces to a random letter
		if (gameGrid[0][i] == 5)
		{
			gameGrid[0][i] = randLetter;
			updateGameBoard(gameGrid);
		}
	}
}