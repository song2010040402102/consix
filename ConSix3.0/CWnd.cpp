#include "CWnd.h"

CWnd::CWnd()
{
	ClsName="WINDOW";
	WndName="Window";	
}

CWnd::~CWnd()
{

}

HFONT CWnd::CreateSimpleFont(int width,int height)
{
	HFONT hFont;
	hFont=CreateFont(
		height,
		width,
		0,
		0,
		FW_NORMAL,
		FALSE,
		FALSE,
		FALSE,
		DEFAULT_CHARSET,
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,
		DEFAULT_PITCH,
		NULL
		);
	return hFont;
}

bool CWnd::InsideRect(const RECT* rt,const int &x,const int &y)
{
	if((rt->left+ALLOW)<x && x<(rt->right-ALLOW) && (rt->top+ALLOW)<y && y<(rt->bottom-ALLOW))
		return true;
	else
		return false;
}