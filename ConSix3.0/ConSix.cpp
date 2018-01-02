#include "ConSix.h"

//��ں���
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	hInst=hInstance;//��¼��Ӧ�ó����ʵ�����		
	if(!MainWnd.RegisterWnd(hInst) ||!MainWnd.CreateWnd())//����������

	{
		return 0;
	}	
	if(!InitRest())//��ʼ��Ӧ�ó���ʣ�µ�����
	{
		return 0;
	}
	GetAndDispatchMessage();//��ȡ��Ϣ���ɷ���Ϣ��ָ���������Ϣ�������
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)//����Ļص����� 
{	
	switch(uMsg)
	{			
	case WM_PAINT:
		OnPaint(hWnd,wParam,lParam);		
		break;
	case WM_SIZE:
		OnSize(hWnd,wParam,lParam);
		break;
	case WM_NOTIFY:
		OnNotify(hWnd,wParam,lParam);
		break;
	case WM_COMMAND:
		OnCommand(hWnd,wParam,lParam);
		break;	
	case WM_LBUTTONDOWN:		
		OnLButtonDown(hWnd,wParam,lParam);
		break;
	case WM_KEYDOWN:		
		OnKeyDown(hWnd,wParam,lParam);
		break;
	case WM_MOUSEMOVE:
		OnMouseMove(hWnd,wParam,lParam);
		break;
	case WM_TIMER:
		OnTimer(hWnd,wParam,lParam);
		break;		
	case WM_CLOSE:
		OnClose(hWnd,wParam,lParam);	
		break;
	case WM_DESTROY:		
		OnDestroy(hWnd,wParam,lParam);		
		break;	
	default:
		break;
	}
	return DefWindowProc(hWnd,uMsg,wParam,lParam); //������Ϣ��Ĭ�ϴ�����
}

VOID OnPaint(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	if(hWnd==MainWnd.hWnd)
	{
		MainWnd.OnPaint(wParam,lParam);
	}	
	return;
}

VOID OnSize(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	if(hWnd==MainWnd.hWnd)
	{
		MainWnd.OnSize(wParam,lParam);
	}	
	return;
}

VOID OnNotify(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	if(hWnd==MainWnd.hWnd)
	{
		MainWnd.OnNotify(wParam,lParam);
	}	
	return;
}

VOID OnCommand(HWND hWnd,WPARAM wParam,LPARAM lParam)//�˵���ť��Ϣ
{
	if(hWnd==MainWnd.hWnd)
	{
		MainWnd.OnCommand(wParam,lParam);
	}
	return;
}

VOID OnLButtonDown(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	if(hWnd==MainWnd.hWnd)
	{
		MainWnd.OnLButtonDown(wParam,lParam);
	}	
	return;
}	

VOID OnKeyDown(HWND hWnd,WPARAM wParam,LPARAM lParam)
{	
	if((int)wParam==112)
	{
		MainWnd.Instructions();
	}
	return;
}
VOID OnMouseMove(HWND hWnd,WPARAM wParam,LPARAM lParam)
{
	if(hWnd==MainWnd.hWnd)
	{
		MainWnd.OnMouseMove(wParam,lParam);
	}	
	return;
}	

VOID OnTimer(HWND hWnd,WPARAM wParam,LPARAM lParam)
{	
	if(hWnd==MainWnd.hWnd)
	{
		MainWnd.OnTimer(wParam,lParam);
	}
	return;
}

VOID OnClose(HWND hWnd,WPARAM wParam,LPARAM lParam)//����رհ�ť����
{
	if(hWnd==MainWnd.hWnd)
	{
		MainWnd.OnClose(wParam,lParam);
	}	
	return;
}

VOID OnDestroy(HWND hWnd,WPARAM wParam,LPARAM lParam)//��ִ��DestroyWindow����
{
	if(hWnd==MainWnd.hWnd)
	{
		MainWnd.OnDestroy(wParam,lParam);
	}	
	return;
}

bool InitRest()
{
	GetCurrentDirectory(sizeof(CurDir),CurDir);//��ȡ����ĵ�ǰ��Ŀ¼	
	return true;
}

VOID GetAndDispatchMessage()
{
	BOOL fGotMessage;
	HACCEL hAccTable;
	MSG msg;
	hAccTable=LoadAccelerators(hInst,MAKEINTRESOURCE(IDR_ACCELERATOR));//�����ݼ�
	while(1)
	{
		fGotMessage=GetMessage(&msg,NULL,0,0);//Get all messages in the main thread,include messages of all window created by main thread.
		if(fGotMessage==0 ||fGotMessage==-1)
		{			
			return;
		}
		if(!TranslateAccelerator(msg.hwnd,hAccTable,&msg))//�ѿ�ݼ���Ϣת�����ַ���Ϣ
		{
			TranslateMessage(&msg);//���û�п�ݼ���Ϣ��ת��������Ϣ
			DispatchMessage(&msg);//�ɷ���Ϣ
		}			
	}
}

void DisplayImage(HDC hDC, LPCTSTR szImagePath,RECT *rt)//չʾjpg�ȳ��ø�ʽ��ͼƬ
{
	HANDLE hFile=CreateFile(szImagePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); //��ָ����·��szImagePath�ж�ȡ�ļ����
	DWORD dwFileSize=GetFileSize(hFile, NULL); //���ͼƬ�ļ��Ĵ�С����������ȫ���ڴ�
	HGLOBAL hImageMemory=GlobalAlloc(GMEM_MOVEABLE, dwFileSize); //��ͼƬ����ȫ���ڴ�
	void *pImageMemory=GlobalLock(hImageMemory); //�����ڴ�
	DWORD dwReadedSize; //����ʵ�ʶ�ȡ���ļ���С
	ReadFile(hFile, pImageMemory, dwFileSize, &dwReadedSize, NULL); //��ȡͼƬ��ȫ���ڴ浱��
	GlobalUnlock(hImageMemory); //�����ڴ�CloseHandle(hFile); //�ر��ļ����
	IStream *pIStream;//����һ��IStream�ӿ�ָ�룬��������ͼƬ��
	IPicture *pIPicture;//����һ��IPicture�ӿ�ָ�룬��ʾͼƬ����
	CreateStreamOnHGlobal(hImageMemory, false, &pIStream); //��ȫ���ڴ��ʹ��IStream�ӿ�ָ��
	OleLoadPicture(pIStream, 0, false, IID_IPicture, (LPVOID*)&(pIPicture));//��OleLoadPicture���IPicture�ӿ�ָ��
	//�õ�IPicture COM�ӿڶ������Ϳ��Խ��л��ͼƬ��Ϣ����ʾͼƬ�Ȳ���
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;	
	pIPicture->get_Width(&hmWidth); //�ýӿڷ������ͼƬ�Ŀ�͸�
	pIPicture->get_Height(&hmHeight);	
	pIPicture->Render(hDC,rt->left,rt->top,rt->right-rt->left,rt->bottom-rt->top,0,hmHeight,hmWidth,-hmHeight,NULL); //��ָ����DC�ϻ��ͼƬ
	GlobalFree(hImageMemory); //�ͷ�ȫ���ڴ�
	pIStream->Release(); //�ͷ�
	pIPicture->Release(); //�ͷ�pIPicture
}

VOID SetText(HWND hWnd,LPCTSTR str)//�����ı����ı�����
{
	SendMessage(hWnd,WM_SETTEXT,(WPARAM)0,(LPARAM)str);	//�������
	SendMessage(hWnd,EM_SETSEL,(WPARAM)-2,(LPARAM)-1);	//���ý��㵽ĩβ
}

VOID GetText(HWND hWnd,LPCTSTR str,int size)//�����ı����ı�����
{	
	SendMessage(hWnd,WM_GETTEXT,size,(LPARAM)str);	//�������
}

VOID ErrorBox(LPTSTR ErrorInfo)//������ʾ��
{
	CHAR error1[50],error2[20];
	strcpy(error1,ErrorInfo);
	sprintf(error2," with error %d",GetLastError());	
	strcat(error1,error2);	
	MessageBox(MainWnd.hWnd,error1,"error",MB_OK);
}

VOID MsgBox(LPTSTR msg)//��Ϣ��
{
	MessageBox(MainWnd.hWnd,msg,"OK",MB_OK);
}