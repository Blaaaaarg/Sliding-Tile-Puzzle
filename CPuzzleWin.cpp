// Program: CS 215 Project 3
// Author: Scott Walker
// Date: Fall 2013
// File: CPuzzleWin.cpp
// Description: This file contains all of the methods for the window that draws the puzzle.

#include <afxwin.h>
#include "CPuzzleWin.h"

CPuzzleWin::CPuzzleWin ()
{
	// This is the default constructor for the window of the GUI for the puzzle. It displays a message box giving directions
	// and the controls of the game. It also scrambles the puzzle before play begins.
	
	string Message = 
		"Put the picture in order by swapping the blank tile\nwith an adjascent tile.\n\nYou can use the arrow keys, WASD, or the mouse.\n+ (Num Pad): Increase Difficulty\n- (Num Pad): Decrease Difficulty\nQ: Quit\n(If you resize the window change the difficulty)";
	Create (NULL, "Puzzle v1.1");
    MessageBox( _T(Message.c_str()), _T("Directions.....Puzzle v1.1"),
			MB_ICONWARNING | MB_OK);
	puzzle.Scramble();
}

afx_msg void CPuzzleWin::OnPaint ()
{
	// This method tells the window how to update when you modify members of the window. It alerts the user if they win the
	// game. Without this the modified puzzle would not be printed to the screen.
	CPaintDC dc (this);
	if (puzzle == finished)
	{
		MessageBox(_T("You Win!"), _T("WINNER!"), MB_ICONWARNING | MB_OK);
		if (puzzle.GetDims() < 20)
		{   
			CRect rect;
			dc.GetWindow()->GetClientRect(rect);
			puzzle.Init(puzzle.GetDims() + 1, rect.Width(), rect.Height());
			puzzle.Scramble();
			Invalidate();
		}
	}
	puzzle.Display(&dc);
}

afx_msg void CPuzzleWin::OnKeyDown (UINT achar, UINT repeat, UINT flags)
{
	// This method detects if a key is pressed while the window for the puzzle is active. It sends the pressed key to the
	// puzzle class so it can decide what to do for that command.

	// Returning this CRect allows you to IvalidateRect instead of Invalidate, so it does not have to redraw the whole screen.
	CRect modified;
	switch(achar)
	{
	case 'W':
		modified = puzzle.Move('W');
		InvalidateRect(modified);
		break;
	case 'A':
		modified = puzzle.Move('A');
		InvalidateRect(modified);
		break;
	case 'D':
		modified = puzzle.Move('D');
		InvalidateRect(modified);
		break;
	case 'S':
		modified = puzzle.Move('S');
		InvalidateRect(modified);
		break;
	case 'Q':
		puzzle.Move('Q');
		break;
	// The arrow keys
	case 39:
		modified = puzzle.Move('D');
		InvalidateRect(modified);
		break;
	case 37:
		modified = puzzle.Move('A');
		InvalidateRect(modified);
		break;
	case 38:
		modified = puzzle.Move('W');
		InvalidateRect(modified);
		break;
	case 40:
		modified = puzzle.Move('S');
		InvalidateRect(modified);
		break;
	// + and -
	case 107:
		// Increase Difficulty (tiles)
		if (puzzle.GetDims() < 20)
		{
			CPaintDC dc (this);
			CRect rect;
			dc.GetWindow()->GetClientRect(rect);
			puzzle.Init(puzzle.GetDims() + 1, rect.Width(), rect.Height()); 
			puzzle.Scramble();
			Invalidate();
		}
		break;
	case 109:
		// Decrease Difficulty (tiles)
		if (puzzle.GetDims() > 3)
		{
			CPaintDC dc (this);
			CRect rect;
			dc.GetWindow()->GetClientRect(rect);
			puzzle.Init(puzzle.GetDims() - 1, rect.Width(), rect.Height());
			puzzle.Scramble();
			Invalidate();
		}
		break;
	}
}

afx_msg void CPuzzleWin::OnLButtonDown (UINT flags, CPoint point)
{
	// This method detects if the left mouse button is pressed in the window. If it is, then it checks to see if one of the
	// tiles was clicked.


	CRect modified = puzzle.Move(point);
	current = point;
	InvalidateRect(modified);
}

BEGIN_MESSAGE_MAP (CPuzzleWin, CFrameWnd)
	ON_WM_PAINT()
	ON_WM_KEYDOWN()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()