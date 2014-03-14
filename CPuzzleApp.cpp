// Program: CS 215 Project 3
// Author: Scott Walker
// Date: Fall 2013
// File: CPuzzleApp.cpp
// Description: This file contains all of the methods for the application that creates a GUI.

#include <afxwin.h>
#include "CPuzzleApp.h"

BOOL CPuzzleApp::InitInstance ()
{
	m_pMainWnd = new CPuzzleWin ();
	m_pMainWnd->SetWindowPos(m_pMainWnd, 400, 150, 500, 520, SWP_NOZORDER);
	m_pMainWnd->ShowWindow (m_nCmdShow);
	m_pMainWnd->UpdateWindow ();

	return TRUE;
}

CPuzzleApp GraphicsApp;