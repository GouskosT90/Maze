/**********************************************
* Program:  aMazing.C                         *
* Author:   Eileen Peluso                     *
*                                             *
* Abstract: Driver program for the Maze       *
**********************************************/
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "Maze.h"

using namespace std;

int main(int argc, char * argv[]) {
	Maze myMaze;	       // Maze object defined
	char filename[20];
	int row, column;           // Holds the mouse's location

	if (argc == 1){
		cout << "Enter the name of the file that contains the maze: ";
		cin >> filename;
	}
	else
		strcpy(filename, argv[1]);

	if (myMaze.OpenAndLoad(filename)){	// open the input file
		system("clear");
		myMaze.DisplayMaze();
	}
	else {
		cerr << "Maze's input file could not be opened" << endl;
		return 1;
	}

	myMaze.GetMouseLocation(row, column);
	while (!myMaze.ValidMouseLocation(row, column)){
		cout << "That mouse location was either outside of the maze or in a wall." << endl;
		myMaze.GetMouseLocation(row, column);
	}

	if (myMaze.RecursiveWayOut(row, column)){
		system("clear");
		myMaze.DisplayMaze();
		cout << endl << "Congratulations! You made it out of the maze." << endl;
	}
	else {
		system("clear");
		myMaze.DisplayMaze();
		cout << endl << "You did not find your way out of the maze." << endl;
	}

	return 0;
}
