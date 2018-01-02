#ifndef CWND_H_CONSIX
#define CWND_H_CONSIX

#include "window.h"

VOID SetText(HWND hWnd,LPCTSTR str); //���ô����ı�
VOID GetText(HWND hWnd,LPCTSTR str,int size); //��ȡ������ı�
void DisplayImage(HDC hDC, LPCTSTR szImagePath,RECT *rt); //չʾͼƬ

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam); //����Ļص�����

//ͨ�ô�����
class CWnd
{
public:		
	WNDCLASS wc; //ע��Ĵ�����
	HWND hWnd; //������
	LPTSTR WndName; //���������
	LPTSTR ClsName;	 //��������

	RECT rtWindow; //��������������ڵĵľ�������
	RECT rtClient; //����ͻ�����������

	HDC hDC; //��ĻDC
	HDC hMemDC; //�ڴ�DC
	HBITMAP hBitmap; //λͼ���	
	HBITMAP hOldBitmap; //֮ǰ��λͼ�ľ��
	PAINTSTRUCT ps;	//��ͼ�ṹ
	
	CWnd();
	~CWnd();
	HFONT CreateSimpleFont(int width,int height); //�����򵥵�����
	bool InsideRect(const RECT* rt,const int &x,const int &y); //�жϵ��Ƿ��ھ�����
};

#endif