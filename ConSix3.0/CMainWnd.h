#ifndef CMAINWND_H_CONSIX
#define CMAINWND_H_CONSIX

#include "CWnd.h"
#include "CSearch.h"
#include "CStatusBar.h"
#include "CNGDlg.h"
#include "CThread.h"

#define MAINWNDTIMER 1 //�������ʱ��ID
#define NEXT(S) (S^1) //��һ��ѡ��

//��������
class CMainWnd :public CWnd
{
public:	
	HMENU hMainMenu; //���˵�
	BYTE board[19][19]; //���̣�19*19��
	RECT rtBoard; //�������ڵľ���
 
	int side; //���̵ı߳�
	COLORREF BkColor; //������ɫ 
	COLORREF BoardColor; //������ɫ
	
	int count; //��Ϊ������ʹ��
	BYTE player;  //ѡ��

	bool debug_hashID; //����ʹ��

	CMainWnd();
	~CMainWnd();

	//ע�ᴰ��ʹ�������
	BOOL RegisterWnd(HINSTANCE hInst);
	BOOL CreateWnd();
		
	//������Ϣ������
	VOID OnPaint(WPARAM wParam,LPARAM lParam);
	VOID OnSize(WPARAM wParam,LPARAM lParam);
	VOID OnNotify(WPARAM wParam,LPARAM lParam);
	VOID OnCommand(WPARAM wParam,LPARAM lParam);
	VOID OnLButtonDown(WPARAM wParam,LPARAM lParam);
	VOID OnMouseMove(WPARAM wParam,LPARAM lParam);
	VOID OnTimer(WPARAM wParam,LPARAM lParam);
	VOID OnClose(WPARAM wParam,LPARAM lParam);
	VOID OnDestroy(WPARAM wParam,LPARAM lParam);		

	//ʹ��˵��
	VOID Instructions();
	
	bool FillBkAndBoard(); //��䱳����ɫ
	bool DrawBoard(); //��������
	bool DrawChess(HDC hBlcDC,HDC hWhtDC,HDC hCurBlcDC,HDC hCurWhtDC,int d); //��������

	bool PlaySnd(int sel); //����wav�����ļ�

	VOID CreateAndAdjustStatusBar(); //״̬���Ĵ����ʹ�С����
	VOID GetClientRectEx(RECT* rt); //��ȡ��ʵ���ƿͻ�������

	VOID NewGame(); //�½���Ϸ
	VOID StartGame(); //������Ϸ
	VOID HumanMove(int x,int y); //��������
	VOID PerToPer(int x,int y); //���˶���
	VOID OutputPointHistory(vector<Point> PointHistory); //����߹��ĵ�
	VOID OpenToolOfCM(); //�����׹���
	bool Readcm(); //��ȡ����
	VOID ReadcmAndStartEngine(); //��ȡ����֮��������������
	VOID Savecm(); //��������
	VOID CalHashID(int x,int y); //�����������HASHID
	VOID MsgEdit(char *msg); //�ı�����Ϣ
};

#endif

