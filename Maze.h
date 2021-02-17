/********************************************************
*     Maze.h                                            *
*                                                       *
*     Author:  Theodore Gouskos                         *
*     Date: 9/21/18                                     *
********************************************************/
#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>

using namespace std;

#ifndef _MAZE
#define _MAZE

/********************************************************
*     class declaration                                 *
********************************************************/
class Maze{
  public:
    Maze();
    bool OpenAndLoad(char * filename);
    void GetMouseLocation(int & r, int & c);
    bool ValidMouseLocation(int r, int c);
    bool RecursiveWayOut(int r, int c);
    void DisplayMaze();
  private:
    int rows;		// The number of rows in the maze
    int columns;	// The number of columns in the maze
    char * maze;	// Points to the character array that is dynamically allocated
};

Maze::Maze(){
// pre:	    none
// post:    private data members are initialized as much as possible
// purpose: initiate variables

    rows = 0;
    columns = 0;
    maze = 0;
}

bool Maze::OpenAndLoad(char * filename) {
// pre:		filename either came from the command line or from the user
//          if the file exists, it must have the proper layout
// post:		the file will be opened and the array loaded
// purpose:	to get set up the maze
    ifstream infile(filename);
    if (!infile)
	return 0;		// return false for unsuccessful open!
    infile >> rows >> columns;
    infile.ignore(80, '\n');

    maze = new char[rows * columns];

    for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
		{
			infile >> *(maze + (i * columns + j));
		}

    return 1;			// return true for successful open!
}

void Maze::GetMouseLocation(int & r, int & c){
// pre:  the maze has been opened and loaded
// post: prompts the user for the location of the mouse in the maze (relative to 1)
//         validates that the user entered valid integers
//         call-by-reference parameters are updated
    cout << "Please enter the row (1-" << rows << ") and column (1-" << columns
			<< ") where the mouse is located: ";
    cin >> r >> c;
    while (cin.fail() || cin.peek() != '\n'){
		cin.clear();
		cin.ignore(80, '\n');
		cout << "That input was invalid, please try again." << endl;
		cin >> r >> c;
    }
    r--;      // Adjust for the array indices starting with 0 rather than 1
    c--;
}

bool Maze::ValidMouseLocation(int r, int c){
// pre:   the maze has been opened and loaded
// post:  returns true if the row r and column c identify an open space in the maze
    if ((r < 0) || (r > (rows - 1)) || (c < 0) || (c > (columns - 1)))
		return false;
    if ( *(maze + (r * columns + c)) == '#')
		return false;
	*(maze + (r * columns) + c) = 'X';
    return true;
}

bool Maze::RecursiveWayOut(int r, int c){
// pre:  the maze has been opened and loaded
//          r and c are valid locations inside of the maze
// post: if the way out of the maze has been found, true is returned
//          else false is returned



	if ((r == 0) || (r == rows - 1) || (c == 0) || (c == columns - 1)) //base case, way out
	{
		return true;
	}

	if (*(maze + ((r - 1) * columns) + c) == '.') //North
	{
		*(maze + ((r - 1) * columns) + c) = '*'; //Makes next move an Asterisk
 		r = r - 1; //Changes mouse Row down one
		DisplayMaze();
		if (RecursiveWayOut(r , c))	//recursive call
			return true;
		*(maze + (r * columns) + c) = 'D'; //Changes Path already taken to D
		r = r + 1; //Reverts Mouse change
	}

	if (*(maze + (r * columns) + (c - 1)) == '.')//West
	{
		*(maze + (r * columns) + (c - 1)) = '*'; //Makes next move an Asterisk
		c = c - 1; ////Changes mouse column down one
		DisplayMaze();
		if (RecursiveWayOut(r , c)) //recursive call
			return true;
		*(maze + (r * columns) + c) = 'D'; //Changes Path already taken to D
		c = c + 1; //Reverts Mouse change
	}

	if (*(maze + ((r + 1) * columns) + c) == '.')//South
	{
		*(maze + ((r +1) * columns) + c) = '*'; //Makes next move an Asterisk
		r = r + 1; //Changes mouse Row up one
		DisplayMaze();
		if (RecursiveWayOut(r , c)) //recursive call
			return true;
		*(maze + (r * columns) + c) = 'D'; //Changes Path already taken to D
		r = r - 1; //Reverts Mouse change
		

	}

	if (*(maze + (r * columns) + (c + 1)) == '.') //East
	{
		*(maze + (r * columns) + (c + 1)) = '*'; //Makes next move an Asterisk
		c = c + 1; //Changes mouse column up one
		DisplayMaze();
		if (RecursiveWayOut(r , c)) //recursive call
			return true;
		*(maze + (r * columns) + c) = 'D'; //Changes Path already taken to D
		c = c - 1; //Reverts Mouse change

	}

	return false;
}

void Maze::DisplayMaze(){
// pre:   the maze has been opened and loaded
// post:  the maze is displayed on the screen in table form
    int i, j;			// local values to display the maze
    char mouse;
    for (i = 0; i < rows; i++){
		for (j = 0; j < columns; j++){
			cout << *(maze + (i * columns + j)) << " ";
		}
	cout << endl;
    }
}


#endif
