#ifndef CNGDLG_H_CONSIX
#define CNGDLG_H_CONSIX

#include "window.h"

//�½���Ϸ�Ի�����
class CNGDlg
{
public:
	int nResult; //�Ի��򷵻صĽ��
	BYTE side; //side�������ֶ���ģʽ
	int depth; //�������
	int ID; //��ѡ�ؼ���ID

	CNGDlg();
	~CNGDlg();	

	VOID OnCreate(WORD DlgID,HINSTANCE hInst=(HINSTANCE)::GetModuleHandle(NULL),HWND hParent=NULL);	//�����Ի���
	VOID OnInit(HWND hWnd); //�Ի����ʼ��
	VOID OnPaint(HWND hWnd); //�Ի������
	VOID OnCommand(HWND hWnd,WPARAM wParam,LPARAM lParam); //�Ի���ؼ���Ϣ��Ӧ
	
	VOID UpdateRadio(HWND hWnd); //���µ�ѡ��ť
};
#endif