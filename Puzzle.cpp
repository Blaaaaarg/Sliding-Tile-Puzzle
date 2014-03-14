// Program: CS215 Project2
// Author: Scott Walker
// Date: Fall 2013
// File: Puzzle.cpp
// Description: This file has all the methods for creating, drawing, and
// maniulating the puzzle with user input.

#include <ctime>
#include <cstdlib>
#include "Puzzle.h"

#define DEFWINSIZE 480

using namespace std;

Puzzle::Puzzle ()
{
	dimensions = 4;
	int CurrentNumber;
	CurrentColor = RGB(255, 255, 255);
	CurrentShape = 'S';
	// Find the size that each tile should be based on the size of the window.
	CurrentXSize = DEFWINSIZE / dimensions;
	CurrentYSize =  DEFWINSIZE / dimensions;
	srand(time(NULL));
	// Randomize the image used by the puzzle.
	if (rand() % 3 == 0)
	{
		CurrentImage = "FLOWER_BMP";
	}
	else if (rand() % 3 == 1)
	{
		CurrentImage = "DOG_BMP";
	}
	else
	{
		CurrentImage = "PACMAN_BMP";
	}
    // Initialize the values of the tiles array (the tiles of the puzzle).
    int number = 0, i = 0, j = 0;
    for (j = 0; j < dimensions; j++)
    {
        for (i = 0; i < dimensions; i++)
	    {
	        number++;
			if (number == dimensions * dimensions)
			{
				SetBlankX(i);
				SetBlankY(j);
			}
			// These X and Y coordinates are for the center of each tile.
			CurrentX = (CurrentXSize / 2) + i * CurrentXSize;
			CurrentY = (CurrentYSize / 2) + j * CurrentYSize;
			CurrentNumber = number;
			tiles[i][j] = CPuzzleTile(CurrentColor, CurrentShape, CurrentX, CurrentY, CurrentXSize, CurrentYSize, 
					CurrentImage, CurrentNumber);   
	    }
    }  
}

void Puzzle::Init(const int d, const int W, const int H)
{
	dimensions = d;
	int CurrentNumber;
	CurrentColor = RGB(255, 255, 255);
	CurrentShape = 'S';
	// Find the size that each tile should be based on the size of the window.
	CurrentXSize = W / dimensions;
	CurrentYSize =  H / dimensions;
	srand(time(NULL));
	// Randomize the image used by the puzzle.
	if (rand() % 3 == 0)
	{
		CurrentImage = "FLOWER_BMP";
	}
	else if (rand() % 3 == 1)
	{
		CurrentImage = "DOG_BMP";
	}
	else
	{
		CurrentImage = "PACMAN_BMP";
	}
    // Initialize the values of the tiles array (the tiles of the puzzle).
    int number = 0, i = 0, j = 0;
    for (j = 0; j < dimensions; j++)
    {
        for (i = 0; i < dimensions; i++)
	    {
	        number++;
			if (number == dimensions * dimensions)
			{
				SetBlankX(i);
				SetBlankY(j);
			}
			// These X and Y coordinates are for the center of each tile.
			CurrentX = (CurrentXSize / 2) + i * CurrentXSize;
			CurrentY = (CurrentYSize / 2) + j * CurrentYSize;
			CurrentNumber = number;
			tiles[i][j] = CPuzzleTile(CurrentColor, CurrentShape, CurrentX, CurrentY, CurrentXSize, CurrentYSize,
					CurrentImage, CurrentNumber);   
	    }
    }  
}

void Puzzle::Redraw(const int X, const int Y)
{
	// This method updates the size and center location of each tile for when the window is resized.

	// Find the size that each tile should be based on the size of the window.
	CurrentXSize = X / dimensions;
	CurrentYSize =  Y / dimensions;
    // Change the size of each tile and its center coordinates. 
    int number = 0, i = 0, j = 0;
    for (j = 0; j < dimensions; j++)
    {
        for (i = 0; i < dimensions; i++)
	    {
			tiles[i][j].SetSize(CurrentXSize, CurrentYSize);
			CurrentX = (CurrentXSize / 2) + i * CurrentXSize;
			CurrentY = (CurrentYSize / 2) + j * CurrentYSize;
			tiles[i][j].SetCenter(CurrentX, CurrentY);
	    }
	}  
}

void Puzzle::Display (CPaintDC * dc)
{
    // This function creates the user interface to the puzzle program by calling the draw method for each tile except
	// the last tile since it is swapped.
	
	for (int i = 0; i < dimensions; i++)
	{
		for (int j = 0; j < dimensions; j++)
		{
			if (tiles[i][j].GetNumber() != dimensions * dimensions)
			{
				tiles[i][j].Paint(dc, dimensions);
			}
		}
	}
	
}
    
void Puzzle::Scramble ()
{
    // This method sscrambles the puzzle by seeding the random function
    // with a time value, a integer value from an uninitialized memory
    // address, and reseeding with the random numbers. It converts the 
    // final random move by converting the random number to a move: w,
    // a, s, d.
	
    // root_times has biggest effect on the scramble. For best results,
    // root_times should be larger than 15.
    int i, root_times = dimensions * dimensions, reseed = 3;
    int * mem;
    // The root_times limiting this loop determines the multiplyiers for
    // the number of random moves. Total random moves is root_times^2.
    for (int k = 0; k < root_times; k++)
    {
	int r;
	mem = &r;
	r = r + k;
	srand (*(mem));
	// Reseed limiting this loop determines the number of times to
	// reseed the random function before making a random move.
	for (int t = 0; t < reseed; t++)
	{
	    srand(rand());
	    r = r + 1;
	    srand(rand() + *(mem)); 
	}
	srand (rand());
	i = rand() % 4;		
	switch (i)
	{
	    case (0):
		Move('A');
		break;
	    case (1):
		Move('S');
		break;
	    case (2):
		Move('D');
		break;
	    case (3):
		Move('W');
		break;
	}
	for (int l = 0; l < root_times; l++)
	{
	    srand (time (NULL));
	    for (int t = 0; t < reseed; t++)
	    {
			srand(rand());
			r = r + 1;
			srand(rand() + *(mem) + (time (NULL))); 
			}
			srand(rand());
			i = rand() % 4;		
			switch (i)
			{
				case (0):
	   	  	    Move('A');
				break;
				case (1):
				Move('S');
				break;
				case (2):
				Move('D');
				break;
				case (3):
			    Move('W');
				break;
			}
		}
    }
}

bool Puzzle::operator == (const Puzzle & P)
{
    // This method checks to see if the puzzle has been put in order by
    // comparing each tile with the value that the tile would be if it was
    // correct.

    int k = 0;
    for (int i = 0; i < dimensions; i++)
    {
        for (int j = 0; j < dimensions; j++)
        {
			k++;
			if (tiles[j][i].GetNumber() != k)
	        {
	        return false;
	        }
        }
    }	
    return true;
}

CRect Puzzle::Move (const char key_down)
{
    // This method moves a tile by switching a selected tile with the
    // "blank" number 16 tile. The character passed to the method tells
    // it which direction to switch tiles.
    
    int k = GetBlankX(), l = GetBlankY();
	CRect oldWhere, newWhere;
	CPuzzleTile temp;
    temp = tiles[k][l];
    // This switch statement finds the correct task to perform given the
    // keyboard input. It will only perform a swap if there is actually a 
    // tile to swap with.
    switch(key_down)
    {
	case ('D'):
	    if (k < dimensions - 1)
	    {
				oldWhere = tiles[k + 1][l].GetWhere();
                tiles[k][l] = tiles[k + 1][l];
                tiles[k + 1][l] = temp;
				SetBlankX(k + 1);
				tiles[k][l].Move(-CurrentXSize, 0);
				tiles[k + 1][l].Move(CurrentXSize, 0);
				newWhere = tiles[k][l].GetWhere();
				return oldWhere | newWhere;
	    }
   	   break;
	case ('A'):
	    if (k > 0)
	    {
				oldWhere = tiles[k - 1][l].GetWhere();
                tiles[k][l] = tiles[k - 1][l];
                tiles[k - 1][l] = temp;
				SetBlankX(k - 1);
				tiles[k][l].Move(CurrentXSize, 0);
				tiles[k - 1][l].Move(-CurrentXSize, 0);
				newWhere = tiles[k][l].GetWhere();
				return oldWhere | newWhere;
	    }
        break;
	case ('S'):
	    if (l < dimensions - 1)
	    {
				oldWhere = tiles[k][l + 1].GetWhere();
                tiles[k][l] = tiles[k][l + 1];
                tiles[k][l + 1] = temp;
				SetBlankY(l + 1);
				tiles[k][l].Move(0, -CurrentYSize);
				tiles[k][l + 1].Move(0, -CurrentYSize);
				newWhere = tiles[k][l].GetWhere();
				return oldWhere | newWhere;
	    }
	    break;
	case ('W'):
	    if (l > 0)
	    {
				oldWhere = tiles[k][l - 1].GetWhere();
                tiles[k][l] = tiles[k][l - 1];
                tiles[k][l - 1] = temp;
				SetBlankY(l - 1);
				tiles[k][l].Move(0, CurrentYSize);
				tiles[k][l - 1].Move(0, CurrentYSize);
				newWhere = tiles[k][l].GetWhere();
				return oldWhere | newWhere;
	    }
	    break;
	case ('Q'):
	    exit(1);
	    break;
    }
	return NULL;
}

int Puzzle::GetBlankX()
{
	// Get the X coordinate of the blank tile
	return BlankX;
}

int Puzzle::GetBlankY()
{
	// Get the Y coordinate of the blank tile
	return BlankY;
}

void Puzzle::SetBlankX(const int i)
{
	// Set the X coordinate of the blank tile
	BlankX = i;
}

void Puzzle::SetBlankY(const int j)
{
	// Set the Y coordinate of the blank tile
	BlankY = j;
}

CRect Puzzle::Move (CPoint point)
{
	// This is an overloaded Move function that takes a point from a click on the window and converts that into a 
	// regular Move function.	
	for (int i = 0; i < dimensions; i++)
	{
		for (int j = 0; j < dimensions; j++)
		{
			if (tiles[i][j].InShape(point.x, point.y))
			{
				if (i == BlankX - 1 && j == BlankY)
				{
					return(Move('A'));
				}
				else if (i == BlankX + 1 && j == BlankY)
				{
					return(Move('D'));
				}
				else if (i == BlankX && j == BlankY - 1)
				{
					return(Move('W'));
				}
				else if (i == BlankX && j == BlankY + 1)
				{
					return(Move('S'));
				}
			}
		}
	}
}

int Puzzle::GetDims()
{
	// This function retrieves the dimensions of the puzzle.
	return dimensions;
}

bool Puzzle::Resize()
{
	if (CurrentXSize != tiles[1][1].GetXSize() || CurrentYSize != tiles[1][1].GetYSize())
	{
		return true;
	}
	return false;
}