#include "CStatusBar.h"

CStatusBar::CStatusBar()
{
	hWnd=NULL;
	viewed=true;
	num=2;
	text="¾ÍÐ÷";
}

CStatusBar::~CStatusBar()
{
	//DestroyStatusBar();
}

BOOL CStatusBar::CreateStatusBar(HWND hParentWnd,int num,int* width)
{
	hWnd=CreateWindowEx(
		0,
		STATUSCLASSNAME,		
		text,
		SBARS_SIZEGRIP |WS_CHILD |WS_VISIBLE |WS_CLIPSIBLINGS |WS_CLIPCHILDREN,
		0,
		0,
		0,
		0,
		hParentWnd,
		NULL,
		hInst,
		NULL
		);
	if(hWnd==NULL)
	{
		ErrorBox("CreateStatusBar failed");
		return FALSE;
	}
	this->num=num;
	if(SendMessage(hWnd,SB_SETPARTS,(WPARAM)num,(LPARAM)width)==FALSE)
	{
		ErrorBox("SetStatusParts failed");
		return FALSE;
	}	
	return TRUE;
}

BOOL CStatusBar::DestroyStatusBar()
{
	if(DestroyWindow(hWnd)==FALSE)
	{
		ErrorBox("DestoryStatusBar failed");
		return FALSE;
	}	
	hWnd=NULL;
	return TRUE;
}

BOOL CStatusBar::SetStatusBar(int index,char *text)
{
	if(SendMessage(hWnd,SB_SETTEXT,(WPARAM)index,(LPARAM)text)==FALSE)
	{
		ErrorBox("SetStatusText failed");
		return FALSE;
	}
	return TRUE;
}

VOID CStatusBar::ShowStatusBar()
{
	ShowWindow(hWnd,SW_SHOW);
	viewed=true;
	return;
}

VOID CStatusBar::HideStatusBar()
{
	ShowWindow(hWnd,SW_HIDE);
	viewed=false;
	return;
}