#ifndef CONSIX_H_CONSIX
#define CONSIX_H_CONSIX

#include "window.h"
#include "CMainWnd.h"

HINSTANCE hInst; //ȫ��ʵ�����
CMainWnd MainWnd; //��������

char CurDir[MAX_PATH-100];//��ǰӦ�ó����Ŀ¼

bool InitRest(); //��Ӧ�ó�����������ֽ��г�ʼ��
VOID GetAndDispatchMessage(); //����Ϣ�����л�ȡ��Ϣ������Ϣ�������ڴ�����

//Windows ��Ϣ��Ӧ�Ĵ�����
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