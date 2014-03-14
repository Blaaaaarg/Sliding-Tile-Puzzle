// Program: CS215 Project2
// Author: Scott Walker
// Date: Fall 2013
// File: Puzzle.h
// Description: This is the class file for the puzzle. The tiles array
// represents the actual puzzle in memory. The methods allow for
// scrambling the puzzle, displaying the puzzle, altering the puzzle,
// and checking puzzle equality.

#include <afxwin.h>
#include "CPuzzleTile.h"

using namespace std;

class Puzzle
{
	public:
		Puzzle ();
		void Init (const int d, const int W, const int H);
		void Display (CPaintDC * dc);
		bool Resize();
		void Redraw (const int XSize, const int YSize);
		void Scramble ();
		bool operator == (const Puzzle & P);
		CRect Move (const char key_down);
		CRect Move (CPoint point);
		int GetBlankX();
		int GetBlankY();
		void SetBlankX(const int i);
		void SetBlankY(const int j);
		int GetDims();

	private:
		COLORREF CurrentColor;
		char CurrentShape;
		int CurrentXSize;
		int CurrentYSize;
		int CurrentX;
		int CurrentY;
		int BlankX;
		int BlankY;
		int dimensions;
		string CurrentImage;

		CPuzzleTile tiles [20][20];
};
