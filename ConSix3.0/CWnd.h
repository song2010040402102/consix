#ifndef CWND_H_CONSIX
#define CWND_H_CONSIX

#include "window.h"

VOID SetText(HWND hWnd,LPCTSTR str); //设置窗体文本
VOID GetText(HWND hWnd,LPCTSTR str,int size); //获取窗体的文本
void DisplayImage(HDC hDC, LPCTSTR szImagePath,RECT *rt); //展示图片

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam); //窗体的回调函数

//通用窗体类
class CWnd
{
public:		
	WNDCLASS wc; //注册的窗体类
	HWND hWnd; //窗体句柄
	LPTSTR WndName; //窗体标题名
	LPTSTR ClsName;	 //窗体类名

	RECT rtWindow; //窗体相对桌面所在的的矩形区域
	RECT rtClient; //窗体客户区矩形区域

	HDC hDC; //屏幕DC
	HDC hMemDC; //内存DC
	HBITMAP hBitmap; //位图句柄	
	HBITMAP hOldBitmap; //之前的位图的句柄
	PAINTSTRUCT ps;	//绘图结构
	
	CWnd();
	~CWnd();
	HFONT CreateSimpleFont(int width,int height); //创建简单的字体
	bool InsideRect(const RECT* rt,const int &x,const int &y); //判断点是否在矩形内
};

#endif