#ifndef CNGDLG_H_CONSIX
#define CNGDLG_H_CONSIX

#include "window.h"

//新建游戏对话框类
class CNGDlg
{
public:
	int nResult; //对话框返回的结果
	BYTE side; //side代表四种对弈模式
	int depth; //搜索深度
	int ID; //所选控件的ID

	CNGDlg();
	~CNGDlg();	

	VOID OnCreate(WORD DlgID,HINSTANCE hInst=(HINSTANCE)::GetModuleHandle(NULL),HWND hParent=NULL);	//创建对话框
	VOID OnInit(HWND hWnd); //对话框初始化
	VOID OnPaint(HWND hWnd); //对话框绘制
	VOID OnCommand(HWND hWnd,WPARAM wParam,LPARAM lParam); //对话框控件消息响应
	
	VOID UpdateRadio(HWND hWnd); //更新单选按钮
};
#endif