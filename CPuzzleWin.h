// Program: CS 215 Project 3
// Author: Scott Walker
// Date: Fall 2013
// File: CPuzzleWin.h
// Description: This file contains the class that stores all of the information for the window.

#include <afxwin.h>
#include "Puzzle.h"

class CPuzzleWin : public CFrameWnd
{
	public:
		CPuzzleWin ();
		afx_msg void OnPaint ();
		afx_msg void OnKeyDown (UINT achar, UINT repeat, UINT flags);
		afx_msg void OnLButtonDown (UINT flags, CPoint point);
		CPoint current;

	private:
		Puzzle puzzle;
		Puzzle finished;
		DECLARE_MESSAGE_MAP ()
};