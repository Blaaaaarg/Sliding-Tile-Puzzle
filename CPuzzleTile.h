// Program: CS 215 Project 3
// Author: Scott Walker
// Date: Fall 2013
// File: CPuzzleTitle.h
// Description: This file contains all of the class which contains the information necessary for the tiles of the puzzle. 

#include <afxwin.h>
#include <string>

using namespace std;

class CPuzzleTile
{
public:
	CPuzzleTile ();
	CPuzzleTile (COLORREF C, char S, int X, int Y, int Z, int W, string I, int N);
	CRect GetWhere () const;
	bool InShape (int x, int y) const;
	void Move (int dx, int dy);
	void Paint (CPaintDC * dc, const int dimensions);
	int GetNumber();
	void SetSize(const int x, const int y);
	void SetCenter(const int x, const int y);
	int GetXSize();
	int GetYSize();

private:
	COLORREF Color;
	char WhichShape;
	int CenterX;
	int CenterY;
	int XSize;
	int YSize;
	int Number;
	string ImageName;
	CRect Where;
};
