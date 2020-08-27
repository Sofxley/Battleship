#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "colours.h"

using namespace std;

//Author's note: For now it is 1.0 v. of the program. In the future I might add some new features to it or update its 'mechanics'.
//Btw taking into account my own interest in doing that.
//No matter what, criticism is welcome, as well as comments & advices on improvements. Have fun.



enum Direction { v = 0, h = 1 };   //enum w/ possible directions
int max_flag = 0; 
int point = 0;   //variable for storing successful hits

class Ship
{
private:
	int grid[10][10];
	int c = 0;
	int r = 0; 
	int dir = 0;
	int ships[10][10];

	void Init_Grid()  //init grid with 0 - sea
	{
		for (int r = 0; r < 10; r++)
		{
			for (int c = 0; c < 10; c++)
			{
				grid[r][c] = 0;
			}
		}
	}
public:
	//Ship(){}; 

	void Print_Board()
	{
		cout << "    |0|1|2|3|4|5|6|7|8|9|\n" << endl;
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				if (j == 0)
					cout << i << "|  ";
				if (j != 10)        //creating n|n|n|... begin-with-board
					cout << "|";

				if (grid[i][j] == 1)   //if the coord is miss
				{
					Color(8); //change console`s color to gray
					cout << "1";
					Color(15); //back to white color
				}
				else if (grid[i][j] == 5)  //if the coord is sunk
				{
					Color(18);  //blue
					cout << "5";
					Color(15); 
				}
				else { cout << 0; }
			}
			cout <<"|"<< endl;
		}
		cout << endl;
	}

	int rand_column(int boatsize)
	{
		switch (boatsize) //create random col based on boatsize in order to not go over the edge of the grid
		{
		case 1:
			if (dir == 1) // if horizonal
				c = rand() % 9;
			else  //if not then it is vertical
				c = rand() % 10;
			break;
		case 2:
			if (dir == 1)
				c = rand() % 8;
			else 
				c = rand() % 10;
			break;
		case 3:
			if (dir == 1)
				c = rand() % 7;
			else 
				c = rand() % 10;
			break;
		case 4:
			if (dir == 1)
				c = rand() % 6;
			else 
				c = rand() % 10;
			break;
		default: throw exception("The random column was not created. It might be due to changes in init_ships funct, boatsize exactly. Add more cases in switch to fix that if it is as I assumed.");
		}
		return c;
	}

	int rand_row(int boatsize)
	{
		switch (boatsize) //create random row based on boatsize in order to not go over the edge of the grid
		{
		case 1:
			if (dir == 1)
				r = rand() % 10;
			else 
				r = rand() % 9;
			break;
		case 2:
			if (dir == 1)
				r = rand() % 10;
			else 
				r = rand() % 8;
			break;
		case 3:
			if (dir == 1)
				r = rand() % 10;
			else 
				r = rand() % 7;
			break;
		case 4:
			if (dir == 1)
				r = rand() % 10;
			else 
				r = rand() % 6;
			break;
		default: throw exception("The random row was not created. It might be due to changes in init_ships funct, boatsize exactly. Add more cases in switch to fix that if it is as I assumed.");
		}
		return r;
	}

	void init_ships() //
	{
		Init_Grid();  //firstly fill the grid w/ sea and then ships arr
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				ships[i][j] = 0;
			}
		}
		set_ships(4); //create a ship any size depending on rand_col & rand_row functs
		set_ships(4);
		set_ships(3);
		set_ships(3);
		set_ships(3);
		set_ships(2);
		set_ships(2);
		set_ships(2);
		set_ships(2);

		/*for (int i = 0; i < 10; i++)   //uncomment to see board with ships on it
		{
			for (int j = 0; j < 10; j++)
			{
				int s = ships[i][j];
				grid[i][j] = s;
			}
		}*/
	}

	void set_ships(int boatsize)  
	{
		srand(time(0)); //for random data
		int free_check = 0; 

		max_flag = max_flag+ boatsize;

		bool operation = false;  //switch for whether the ship was set in a right way

		while (operation != true) 
		{

			dir = static_cast<Direction>(rand() % 2);    //converting enum to int: vertical=0,horizontal=1
			c = rand_column(boatsize);
			r = rand_row(boatsize);
			switch (dir)
			{
			case 0:   // if direction = vertical
				free_check = check_nearby_coord(c, r, dir, boatsize);      //funct for checking if space around the future ship is free 
				if (free_check == 0)  //if everthing is sea, append ship in array
				{
					for (int i = 0; i < boatsize; i++)
					{
						ships[r + i][c] = 5;
					}
					operation = true;
				}
				break;
			case 1:
				free_check = check_nearby_coord(c, r, dir, boatsize); 
				if (free_check == 0)   //if everything is sea, append ship in array
				{
					for (int i = 0; i < boatsize; i++)
					{
						ships[r][c + i] = 5;
					}
					operation = true;
				}
				break;
			default: throw exception("The direction was not chosen correctly.");
			}
		}
	}
	int check_nearby_coord(int c, int r, int dir, int boatsize)
	{
		switch (dir)
		{
		case 0:
			for (int i = r - 1; i <= r + boatsize; i++)
			{
				if (ships[i][c] != 0 || ships[i][c - 1] != 0 || ships[i][c + 1] != 0)
				{
					return 1;
				}
			}
			return 0;
			break;
		case 1:
			for (int i = c - 1; i <= c + boatsize; i++)
			{
				if (ships[r][i] != 0 || ships[r + 1][i] != 0 || ships[r - 1][i] != 0)
					return 1;
			}
			return 0;
			break;
		default: throw exception("The direction was not chosen correctly. It is not possible to check the coordinates around the chosen one earlier. ");
		}
	}

	void check_sunk_or_hit(int x, int y)
	{
		if (ships[x + 1][y] == 5 || ships[x - 1][y] == 5 || ships[x][y + 1] == 5 || ships[x][y - 1] == 5)
		{  //if in ships array there is a part of a ship around the chosen coordinate not having been bombed
			cout << "You hit the boat! Search for remnants." << endl;
			grid[x][y] = 5; 
			ships[x][y] = 8; //as a way to skip the bombed coordinate, but search for the left ones 
		}
		else {
			cout << "You sunk the boat!"<<endl; 
			grid[x][y] = 5;
		}
	}
	
	void play()
	{
		int x = -1; int y = -1;
		while (x > 9 || x < 0 || y>9 || y < 0)
		{
			cout << "Input the coordinates: ";
			cin >> x; cin >> y;
		}
		if (ships[x][y] == 5)
		{
			check_sunk_or_hit(x, y);
			point++;
		}
		else if (ships[x][y] == 8 || grid[x][y]==1)
		{
			cout << "You have already bombed this coordinate before!"<<endl; 
		}
		else {
			cout << "You have missed!" << endl;
			grid[x][y] = 1;
		}
		Print_Board(); //update the board
		
	}
};

int main()
{
	Ship user;

	string str; 
	cout << "Enter 'play' to start: ";
	getline(cin, str);
	try
	{
		if (str == "play")
		{
			user.init_ships();   //getting coordinates for ships 
			user.Print_Board();

			int hits_made = 0; //variable for storing how many hits were made throughout the game
			while (point != max_flag)
				//the game continues until the player reaches the maximum of successful hits - sum of sizes of all the ships "planted" on the board
			{
				user.play();
				hits_made++;
			}
			cout << "Congrats! You have won!" << endl;
			cout << "You needed " << hits_made << " hits to finish." << endl;
		}
		else
		{
			throw exception("Input string doesn't match the required one - 'play'. Pay attention.");
		}
	}
	catch (exception &ex)
	{
		cout << ex.what() << endl;
	}
	return 0;
}