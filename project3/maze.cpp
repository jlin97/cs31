#include "grid.h"
#include <string>
#include <cctype>
#include <iostream>

using namespace std;

// function prototypes
bool isValidDirection(char direction);
bool isPartWellFormed(string part);
bool isRouteWellFormed(string route);
int navigateSegment(int r, int c, char dir, int maxSteps);
int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps);
bool positionShift(int& currentRow, int& currentColumn, char direction, int nSteps);

int main()
{
	setSize(9, 9);      // make a 3 by 4 grid
	setWall(1, 4);      // put a wall at (1,4)
	setWall(2, 2);      // put a wall at (2,2)
	setWall(2, 4);
	setWall(3, 4);

	setWall(5, 3);
	setWall(6, 3);
	setWall(7, 3);
	setWall(9, 6);

	setWall(5, 6);

	draw(6, 6, 7, 7);    // draw the grid, showing an S at (3,1)
						 //    start position, and an E at (3,4)
	while (1) {
		int x;
		string test;
		getline(cin, test);
		int a = navigateRoute(6, 6, 7, 7, test, x);
		cout << "Function returned: " << a << endl;
		cout << x << " steps taken." << endl;
	}

} 
//tests for if a string is syntactically correct
bool isRouteWellFormed(string route) {
	int i = 0;
	if (route == "") {
		return true;
	}
	if (!isValidDirection(route[0])) {   // checking the first index for if it is a valid direction
		return false;
	}
	while (i < (int)route.size()) {
		if (isValidDirection(route[i])) {    // checking if the next index is a direction
			i++;							 // if so, move to the next index and restart the while loop
			continue;
		}
		else {
			if (isprint(route[i]) && !isdigit(route[i])) {
				return false;			// if the index is printable but not a digit, return false
			}
			int count = 0;				// rest of indices should only have digits until the end of the iteration
			int j = i; // 0+3 = 3 --> only until 2
			while (j < i + 3 && isdigit(route[j])) {    // loops to i+3 and until route[j] is not a digit 
				count++;					// stores number of chars that are digits in a counter
				j++;
			}
			if (count > 2) {	// if count exceeds 2, return false
				return false;
			}
			i += count;  // starts the next iteration at the index of the next letter
		}
	}
	return true;			// test passed
}
//checks if a char is a direction (not case-sensitive)
bool isValidDirection(char direction) {
	direction = toupper(direction);   // not case-sensitive
	if (direction == 'N' || direction == 'S' || direction == 'W' || direction == 'E') {
		return true;
	}
	return false;
}
/*checks the possibility to transverse in a direction for a number of steps, and returns either a -1
 for invalid inputs or the max no. steps  */
int navigateSegment(int r, int c, char dir, int maxSteps) {
	int steps = 0;
	char upperDir = toupper(dir);
	if (r < 1 || c < 1 || r > getRows() || c > getCols()) {
		return -1;
	}
	else if ((isWall(r, c)) || maxSteps < 0 || (isprint(dir) && !isValidDirection(dir))) { 
		// checks for walls, negativeSteps
		// and for validity of char as printable but not a direction
			return -1;
	}

	else if (upperDir == 'N') {
		if (maxSteps > r - 1) {  // if the number of maxSteps exceeds the row position
			maxSteps = r - 1;    // change maxSteps to equal such a number
		}
		int r2 = r;
		while (steps < maxSteps && !isWall(r2 - 1, c)) {		//as long as steps is less than maxSteps and variable-1 is a valid wall, loop
			r2--;
			steps++;
		}
	}
	else if (upperDir == 'W') {
		if (maxSteps > c - 1) {    // if the number of maxSteps exceeds the col position
			maxSteps = c - 1;		 // change maxSteps to equal such a number
		}
		int c2 = c;
		while (steps < maxSteps && !isWall(r, c2 - 1)) {		//as long as steps is less than maxSteps and variable-1 is a valid wall, loop
			c2--;
			steps++;
		}
	}
	else if (upperDir == 'S') {
		if (maxSteps > getRows() - r) {			// if the number of maxSteps exceeds the row position
			maxSteps = getRows() - r;			 // change maxSteps to equal such a number
		}
		int r2 = r;
		while (steps < maxSteps && !isWall(r2 + 1, c)) {		//as long as steps is less than maxSteps and variable-1 is a valid wall, loop
			r2++;
			steps++;
		}
	}
	else if (upperDir == 'E') {	
		if (maxSteps > getCols() - c) {			// if the number of maxSteps exceeds the col position
			maxSteps = getCols() - c;				 // change maxSteps to equal such a number
		}	
		int c2 = c;
		while (steps < maxSteps && !isWall(r, c2 + 1)) {
			c2++;
			steps++;
		}
	}
	return steps;
}
/*transverses through the entire route with 4 possible outcomes:
3: hit a wall or attempted to transverse out of the map
2: syntactically incorrect
1: was able to transverse across the route string but did not reach the endpoint
0: transversed across the route string and reached the endpoint */
int navigateRoute(int sr, int sc, int er, int ec, string route, int& nsteps) {
	int currentRow = sr, currentColumn = sc;   // new variables to trace through the route
	if (sr < 1 || sr > getRows() || sc < 1 || sc > getCols() || er < 1 || er > getRows() || ec < 1 || ec > getCols()) {     
		return 2;						  // checking for starting and ending out of bounds
	}
	else if (!isRouteWellFormed(route) || isWall(sr, sc) || isWall(er, er)) {
		return 2;           // invalidity checks
	}
	else {
		nsteps = 0;
		char dir;  // passed validity test, first char is sure to be a direction
		int i = 0, totalSteps = 0;
		while (i < (int)route.size()) {   // looping through the rest of the route
			int one = 1;
			dir = route[i];
			int indexCount = 0; // for the digit portion of each segment
			if (isValidDirection(route[i]) && (!isdigit(route[i + 1]))) {		 //checking if there's another direction after the
				if (!positionShift(currentRow, currentColumn, dir, one)) {	     //direction without digits in between
					nsteps = totalSteps;								      	// testing through positionShift to see if there is a wall
					return 3;					// if so, nsteps becomes steps travelled; 3 returned
				}
				nsteps = totalSteps;               // in case of e.g. nnnnnnnnnn
				totalSteps++;                      // increment steps travelled and index of loop
				i++;
				continue;          // goes back to the start of the loop to check for another direction after
			}
			// only digits in this part of the segment
			i++;
			int j = i;
			string segmentsteps;
			while (isdigit(route[j]) && j < (int)route.size()) {     // segmentsteps represents the no. of steps in string form
				segmentsteps += route[j];   // will continue adding to segmentsteps until index reaches a non-digit
				j++;
				indexCount++;
			}
			int digitsteps = atoi(segmentsteps.c_str());  // casted segmentsteps to an int digitsteps

			totalSteps += navigateSegment(currentRow, currentColumn, dir, digitsteps);  //adds steps from segment to total
			if (!positionShift(currentRow, currentColumn, dir, digitsteps)) {  // shifts the position of the robot for the segment
				nsteps = totalSteps;										   // in the test, if true, it means there are no walls
				return 3;													   // if false, it means the robot has encountered a wall
			}

			i += indexCount; // moves the index to the next segment
		}

		nsteps = totalSteps;   // final replacement of nsteps after loop

		if (currentRow == er && currentColumn == ec) {   // testing if the positions after transversed match the requested end points
			return 0;
		}
		return 1;			// mismatch
	}
}
//shifts the position of the robot and returns whether the robot reached any obstacles [wall/off the grid]
bool positionShift(int& currentRow, int& currentColumn, char direction, int digitsteps) {
	int i = 0, limit = 0;
	direction = toupper(direction);        // change the direction char to uppercase
	if (direction == 'N') {
		i = currentRow;						// i is used for the loop so currentRow is unchanged
		limit = currentRow - digitsteps;
		while (i >= limit && i > -1) {       // has to have an iteration of i=0 so that i can be tested for isWall	
			if (i == 0) {					// testing for out of bounds
				return false;
			}
			else if (isWall(i, currentColumn)) {	// testing for walls
				return false;
			}
			currentRow--;            // move one row north
			i--;
		}
		currentRow++;            // final fix after testing ahead for one extra step of the route segment
	}
	else if (direction == 'W') {
		i = currentColumn;
		limit = currentColumn - digitsteps;
		while (i >= limit && i > -1) {		// same logic as N as both decrement rows
			if (i == 0) {                 // testing for out of bounds
				return false;   
			}
			else if (isWall(currentRow, i)) {     // testing for walls
				return false;
			}
			currentColumn--;            // move one column left
			i--;
		}
		currentColumn++;	// final fix after testing ahead for one extra step of the route segment
	}
	else if (direction == 'E') {
		i = currentColumn;
		limit = currentColumn + digitsteps;
		while (i <= limit && i < getCols() + 2) {  // getCols()+2 so that getCols()+1 will be tested in out-of-bounds check
			if (i == getCols() + 1) {		// getCols() is still valid, but getCols()+1 is out of bounds
				return false;            
			}
			else if (isWall(currentRow, i)) { // isWall will never reach getCols() + 1 because if statement above will return false

			}
			currentColumn++;            // move one column right
			i++;
		}
		currentColumn--;	// final fix after testing ahead for one extra step of the route segment
	}
	else if (direction == 'S') {
		i = currentRow;
		limit = currentRow + digitsteps;
		while (i <= limit && i < getRows() + 2) {  // getRow()+2 so that getRows()+1 will be tested in out-of-bounds check
			if (i == getRows() + 1) {		// getRows() is still valid, but getRows()+1 is out of bounds
				return false;
			}
			else if (isWall(i, currentColumn)) {   // isWall will never reach getRows() + 1 because if statement above will return false
				return false;
			}
			currentRow++;       // move one row south
			i++;
		}
		currentRow--;		// final fix after testing ahead for one extra step of the route segment
	}
	return true;
}