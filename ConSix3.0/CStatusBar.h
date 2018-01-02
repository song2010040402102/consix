#ifndef CSTATUSBAR_H_CONSIX
#define CSTATUSBAR_H_CONSIX

#include "window.h"

//�����ҷ�װ�ļ򵥵�״̬����ֱ���ü���
class CStatusBar
{
public:
	HWND hWnd;	
	int num;
	char *text;
	bool viewed;

	CStatusBar();
	~CStatusBar();
	BOOL CreateStatusBar(HWND hParentWnd,int num,int* width);
	BOOL DestroyStatusBar();
	BOOL SetStatusBar(int index,char*text);
	VOID ShowStatusBar();
	VOID HideStatusBar();
};

#endif
