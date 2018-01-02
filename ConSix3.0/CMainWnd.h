#ifndef CMAINWND_H_CONSIX
#define CMAINWND_H_CONSIX

#include "CWnd.h"
#include "CSearch.h"
#include "CStatusBar.h"
#include "CNGDlg.h"
#include "CThread.h"

#define MAINWNDTIMER 1 //主窗体计时器ID
#define NEXT(S) (S^1) //下一个选手

//主窗体类
class CMainWnd :public CWnd
{
public:	
	HMENU hMainMenu; //主菜单
	BYTE board[19][19]; //棋盘（19*19）
	RECT rtBoard; //棋盘所在的矩形
 
	int side; //棋盘的边长
	COLORREF BkColor; //背景颜色 
	COLORREF BoardColor; //棋盘颜色
	
	int count; //作为计数器使用
	BYTE player;  //选手

	bool debug_hashID; //调试使用

	CMainWnd();
	~CMainWnd();

	//注册窗体和创建窗体
	BOOL RegisterWnd(HINSTANCE hInst);
	BOOL CreateWnd();
		
	//窗体消息处理函数
	VOID OnPaint(WPARAM wParam,LPARAM lParam);
	VOID OnSize(WPARAM wParam,LPARAM lParam);
	VOID OnNotify(WPARAM wParam,LPARAM lParam);
	VOID OnCommand(WPARAM wParam,LPARAM lParam);
	VOID OnLButtonDown(WPARAM wParam,LPARAM lParam);
	VOID OnMouseMove(WPARAM wParam,LPARAM lParam);
	VOID OnTimer(WPARAM wParam,LPARAM lParam);
	VOID OnClose(WPARAM wParam,LPARAM lParam);
	VOID OnDestroy(WPARAM wParam,LPARAM lParam);		

	//使用说明
	VOID Instructions();
	
	bool FillBkAndBoard(); //填充背景颜色
	bool DrawBoard(); //绘制棋盘
	bool DrawChess(HDC hBlcDC,HDC hWhtDC,HDC hCurBlcDC,HDC hCurWhtDC,int d); //绘制棋子

	bool PlaySnd(int sel); //播放wav声音文件

	VOID CreateAndAdjustStatusBar(); //状态条的创建和大小调整
	VOID GetClientRectEx(RECT* rt); //获取真实绘制客户区矩形

	VOID NewGame(); //新建游戏
	VOID StartGame(); //启动游戏
	VOID HumanMove(int x,int y); //人类走棋
	VOID PerToPer(int x,int y); //人人对弈
	VOID OutputPointHistory(vector<Point> PointHistory); //输出走过的点
	VOID OpenToolOfCM(); //打开棋谱工具
	bool Readcm(); //读取棋谱
	VOID ReadcmAndStartEngine(); //读取棋谱之后启动搜索引擎
	VOID Savecm(); //保存棋谱
	VOID CalHashID(int x,int y); //计算两个点的HASHID
	VOID MsgEdit(char *msg); //文本框消息
};

#endif

