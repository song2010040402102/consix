#ifndef CONSIX_H_CONSIX
#define CONSIX_H_CONSIX

#include "window.h"
#include "CMainWnd.h"

HINSTANCE hInst; //全局实例句柄
CMainWnd MainWnd; //主窗体类

char CurDir[MAX_PATH-100];//当前应用程序的目录

bool InitRest(); //对应用程序的声誉部分进行初始化
VOID GetAndDispatchMessage(); //从消息队列中获取消息并把消息发给窗口处理函数

//Windows 消息对应的处理函数
VOID OnPaint(HWND hWnd,WPARAM wParam,LPARAM lParam);
VOID OnSize(HWND hWnd,WPARAM wParam,LPARAM lParam);
VOID OnNotify(HWND hWnd,WPARAM wParam,LPARAM lParam);
VOID OnCommand(HWND hWnd,WPARAM wParam,LPARAM lParam);
VOID OnLButtonDown(HWND hWnd,WPARAM wParam,LPARAM lParam);
VOID OnKeyDown(HWND hWnd,WPARAM wParam,LPARAM lParam);			
VOID OnMouseMove(HWND hWnd,WPARAM wParam,LPARAM lParam);
VOID OnTimer(HWND hWnd,WPARAM wParam,LPARAM lParam);
VOID OnClose(HWND hWnd,WPARAM wParam,LPARAM lParam);
VOID OnDestroy(HWND hWnd,WPARAM wParam,LPARAM lParam);

#endif