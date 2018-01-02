#include "CNGDlg.h"

CNGDlg *pNGDlg=NULL;

BOOL CALLBACK NGDlgProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)
{	
	switch(uMsg)
	{
	case WM_INITDIALOG:
		pNGDlg->OnInit(hWnd);
		return TRUE;
	case WM_COMMAND:
		pNGDlg->OnCommand(hWnd,wParam,lParam);		
		break;
	case WM_PAINT:
		pNGDlg->OnPaint(hWnd);
		break;
	default:		
		break;
	}
	return FALSE;
}

CNGDlg::CNGDlg()
{	
	pNGDlg=this;
	side=2;//代表电脑执黑，人执白，0、1、2、3对应二进制编码为：00、01、10、11，刚好对应4中对弈模式:人人、人机、机人、机机
	depth=5;//深度默认为5
}

CNGDlg::~CNGDlg()
{
	
}

VOID CNGDlg::OnCreate(WORD DlgID,HINSTANCE hInst,HWND hParent)
{
	nResult=DialogBox(hInst,MAKEINTRESOURCE(DlgID),hParent,NGDlgProc);
	return;	
}

VOID CNGDlg::OnInit(HWND hWnd)
{
	/*默认电脑执黑，人执白。*/
	SendMessage(GetDlgItem(hWnd,IDR_BLC_COM),BM_SETCHECK,(WPARAM)BST_CHECKED,(LPARAM)0);
	SendMessage(GetDlgItem(hWnd,IDR_BLC_PER),BM_SETCHECK,(WPARAM)BST_UNCHECKED,(LPARAM)0);
	SendMessage(GetDlgItem(hWnd,IDR_WHT_COM),BM_SETCHECK,(WPARAM)BST_UNCHECKED,(LPARAM)0);
	SendMessage(GetDlgItem(hWnd,IDR_WHT_PER),BM_SETCHECK,(WPARAM)BST_CHECKED,(LPARAM)0);

	/*添加搜索深度*/
	SendMessage(GetDlgItem(hWnd,IDC_DEPTH),CB_ADDSTRING,(WPARAM)0,(LPARAM)"1");
	SendMessage(GetDlgItem(hWnd,IDC_DEPTH),CB_ADDSTRING,(WPARAM)0,(LPARAM)"2");	
	SendMessage(GetDlgItem(hWnd,IDC_DEPTH),CB_ADDSTRING,(WPARAM)0,(LPARAM)"3");	
	SendMessage(GetDlgItem(hWnd,IDC_DEPTH),CB_ADDSTRING,(WPARAM)0,(LPARAM)"4");
	SendMessage(GetDlgItem(hWnd,IDC_DEPTH),CB_ADDSTRING,(WPARAM)0,(LPARAM)"5");

	/*默认搜索深度为5*/
	SendMessage(GetDlgItem(hWnd,IDC_DEPTH),CB_SELECTSTRING,(WPARAM)0,(LPARAM)"5");
	return;
}

VOID CNGDlg::OnPaint(HWND hWnd)
{
	return;
}

VOID CNGDlg::OnCommand(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	ID=LOWORD(wParam);
	switch(ID)
	{		
	case IDCANCEL:
		side=2;depth=5;//如果点击取消重置数据
	case IDOK:		
		::EndDialog(hWnd,nResult);
		break;
	case IDR_BLC_COM:		
	case IDR_BLC_PER:
		side^=2;
		UpdateRadio(hWnd);
		break;
	case IDR_WHT_COM:
	case IDR_WHT_PER:
		side^=1;
		UpdateRadio(hWnd);
		break;
	case IDC_DEPTH:
		depth=SendMessage(GetDlgItem(hWnd,IDC_DEPTH),CB_GETCURSEL,(WPARAM)0,(LPARAM)0)+1;
		break;
	}	
	return;
}

VOID CNGDlg::UpdateRadio(HWND hWnd)
{	
	if(side==0)//人人对弈
	{
		SendMessage(GetDlgItem(hWnd,IDR_BLC_COM),BM_SETCHECK,(WPARAM)BST_UNCHECKED,(LPARAM)0);
		SendMessage(GetDlgItem(hWnd,IDR_BLC_PER),BM_SETCHECK,(WPARAM)BST_CHECKED,(LPARAM)0);
		SendMessage(GetDlgItem(hWnd,IDR_WHT_COM),BM_SETCHECK,(WPARAM)BST_UNCHECKED,(LPARAM)0);
		SendMessage(GetDlgItem(hWnd,IDR_WHT_PER),BM_SETCHECK,(WPARAM)BST_CHECKED,(LPARAM)0);
	}
	else if(side==1)//人机对弈，人执黑，电脑执白
	{
		SendMessage(GetDlgItem(hWnd,IDR_BLC_COM),BM_SETCHECK,(WPARAM)BST_UNCHECKED,(LPARAM)0);
		SendMessage(GetDlgItem(hWnd,IDR_BLC_PER),BM_SETCHECK,(WPARAM)BST_CHECKED,(LPARAM)0);
		SendMessage(GetDlgItem(hWnd,IDR_WHT_COM),BM_SETCHECK,(WPARAM)BST_CHECKED,(LPARAM)0);
		SendMessage(GetDlgItem(hWnd,IDR_WHT_PER),BM_SETCHECK,(WPARAM)BST_UNCHECKED,(LPARAM)0);
	}
	else if(side==2)//人机对弈，电脑执黑，人执白
	{
		SendMessage(GetDlgItem(hWnd,IDR_BLC_COM),BM_SETCHECK,(WPARAM)BST_CHECKED,(LPARAM)0);
		SendMessage(GetDlgItem(hWnd,IDR_BLC_PER),BM_SETCHECK,(WPARAM)BST_UNCHECKED,(LPARAM)0);
		SendMessage(GetDlgItem(hWnd,IDR_WHT_COM),BM_SETCHECK,(WPARAM)BST_UNCHECKED,(LPARAM)0);
		SendMessage(GetDlgItem(hWnd,IDR_WHT_PER),BM_SETCHECK,(WPARAM)BST_CHECKED,(LPARAM)0);
	}
	else if(side==3)//机机对弈
	{
		SendMessage(GetDlgItem(hWnd,IDR_BLC_COM),BM_SETCHECK,(WPARAM)BST_CHECKED,(LPARAM)0);
		SendMessage(GetDlgItem(hWnd,IDR_BLC_PER),BM_SETCHECK,(WPARAM)BST_UNCHECKED,(LPARAM)0);
		SendMessage(GetDlgItem(hWnd,IDR_WHT_COM),BM_SETCHECK,(WPARAM)BST_CHECKED,(LPARAM)0);
		SendMessage(GetDlgItem(hWnd,IDR_WHT_PER),BM_SETCHECK,(WPARAM)BST_UNCHECKED,(LPARAM)0);
	}
	return;
}