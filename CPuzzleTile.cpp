// Program: CS 215 Project 3
// Author: Scott Walker
// Date: Fall 2013
// File: CPuzzleTitle.cpp
// Description: This file contains all of the methods for the tiles of the puzzle.

#include <math.h>
#include "CPuzzleTile.h"

using namespace std;

CPuzzleTile::CPuzzleTile ()
{
	// This is the default constructor for the tiles of the puzzle, which assigns meaningless values to the attributes that
	// will later be replaced.
	Color = RGB (255, 255, 255);
	WhichShape = 'S';
	CenterX = 100;
	CenterY = 100;
	XSize = 10;
	YSize = 10;
	Number = 0;
	Where = CRect (100, 100, 120, 120);
}

CPuzzleTile::CPuzzleTile (COLORREF C, char S, int X, int Y, int Z, int W, string I, int N)
{
	// This is a constructor that assings useful values to the tiles to create a puzzle.
	// The color is currently not implemented. The shape is set to square since that is the obvious shape for a tile.
	// The Center variables are the coordinates for each tile. The Size variables are how large each tile is, X is width
	// and Y is height. Number is the number representing the location of the tile relative to the others (when solved).
	// Where is a CRect that stores the tile sizes and can be drawn to the screen. The imagename is self explanatory.
	Color = C;
	WhichShape = S;
	CenterX = X;
	CenterY = Y;
	XSize = Z;
	YSize = W;
	Number = N;
	Where = CRect (CenterX - Z / 2, CenterY - W / 2, CenterX + Z / 2, CenterY + W / 2);
	ImageName = I;
}

void CPuzzleTile::Paint (CPaintDC * dc, const int dimensions)
{
	// This method draws an individual tile to the screen by using the dimensions and location that each tile stores.
	dc->Rectangle (Where);
	if (ImageName != "")
	{
		CBitmap Image;
		int res = Image.LoadBitmap(ImageName.c_str());
		CDC memDC;
		memDC.CreateCompatibleDC(dc);
		memDC.SelectObject(&Image);
		dc->TransparentBlt (Where.left - 1, Where.top - 1, Where.Width() - 2, 
							Where.Height() - 2, &memDC, (((Number - 1) % dimensions))  * (80 / dimensions),
							((Number - 1) / dimensions) * (80 / dimensions), 80 / dimensions, 80 / dimensions, SRCCOPY); // right, down
	}
	dc->DrawText(to_string(GetNumber()).c_str(), CRect(CenterX - 40 / dimensions, CenterY - 40 / dimensions, 
				CenterX + 40 / dimensions + 20, CenterY + 40 / dimensions + 20), DT_LEFT);
}

CRect CPuzzleTile::GetWhere () const
{
	// This returns the coordinates of the current tile.
	return Where;
}

bool CPuzzleTile::InShape (int x, int y) const
{
	// This method checks to see if a point from a mouse click is within one of the tiles. This is used for the mouse
	// functionality.
	if (WhichShape == 'S')
	{
		if (x <= Where.right && x >= Where.left && y <= Where.bottom && y >= Where.top)
		{
			return true;
		}
	}
	return false;
}

void CPuzzleTile::Move (int dx, int dy)
{
	// This method changes the location of the tile when the player makes a move. It does this by changing the CRect and
	// center coodinates for each tile.
	Where.left += dx;
	Where.right += dx;
	Where.top += dy;
	Where.bottom += dy;
	CenterX += dx;
	CenterY += dy;
}

int CPuzzleTile::GetNumber()
{
	// This method gets the stored number of the current tile.
	return Number;
}

void CPuzzleTile::SetSize(const int x, const int y)
{
	// Change the tile size
	CRect temp = Where;
	Where.right = temp.right + (x / 2);
	Where.bottom = temp.bottom + (y / 2);
	Where.left = temp.left - (x / 2);
	Where.top = temp.top - (y / 2);
	XSize = y;
	YSize = x;
}

void CPuzzleTile::SetCenter(const int x, const int y)
{
	// Change the tile center
	CenterX = x;
	CenterY = y;
}

int CPuzzleTile::GetXSize()
{
	// Return the width of the tile.
	return XSize;
}

int CPuzzleTile::GetYSize()
{
	// Return the height of the tile.
	return YSize;
}