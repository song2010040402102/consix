#include "ConSix.h"

//入口函数
int APIENTRY WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nShowCmd)
{
	hInst=hInstance;//记录本应用程序的实例句柄		
	if(!MainWnd.RegisterWnd(hInst) ||!MainWnd.CreateWnd())//创建主窗体

	{
		return 0;
	}	
	if(!InitRest())//初始化应用程序剩下的设置
	{
		return 0;
	}
	GetAndDispatchMessage();//获取消息并派发消息至指定窗体的消息处理程序
	return 0;
}

LRESULT CALLBACK WndProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)//窗体的回调函数 
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
	return DefWindowProc(hWnd,uMsg,wParam,lParam); //窗体消息的默认处理函数
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

VOID OnCommand(HWND hWnd,WPARAM wParam,LPARAM lParam)//菜单按钮消息
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

VOID OnClose(HWND hWnd,WPARAM wParam,LPARAM lParam)//点击关闭按钮触发
{
	if(hWnd==MainWnd.hWnd)
	{
		MainWnd.OnClose(wParam,lParam);
	}	
	return;
}

VOID OnDestroy(HWND hWnd,WPARAM wParam,LPARAM lParam)//当执行DestroyWindow触发
{
	if(hWnd==MainWnd.hWnd)
	{
		MainWnd.OnDestroy(wParam,lParam);
	}	
	return;
}

bool InitRest()
{
	GetCurrentDirectory(sizeof(CurDir),CurDir);//获取程序的当前的目录	
	return true;
}

VOID GetAndDispatchMessage()
{
	BOOL fGotMessage;
	HACCEL hAccTable;
	MSG msg;
	hAccTable=LoadAccelerators(hInst,MAKEINTRESOURCE(IDR_ACCELERATOR));//载入快捷键
	while(1)
	{
		fGotMessage=GetMessage(&msg,NULL,0,0);//Get all messages in the main thread,include messages of all window created by main thread.
		if(fGotMessage==0 ||fGotMessage==-1)
		{			
			return;
		}
		if(!TranslateAccelerator(msg.hwnd,hAccTable,&msg))//把快捷键消息转换成字符消息
		{
			TranslateMessage(&msg);//如果没有快捷键消息则转换其它消息
			DispatchMessage(&msg);//派发消息
		}			
	}
}

void DisplayImage(HDC hDC, LPCTSTR szImagePath,RECT *rt)//展示jpg等常用格式的图片
{
	HANDLE hFile=CreateFile(szImagePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL); //从指定的路径szImagePath中读取文件句柄
	DWORD dwFileSize=GetFileSize(hFile, NULL); //获得图片文件的大小，用来分配全局内存
	HGLOBAL hImageMemory=GlobalAlloc(GMEM_MOVEABLE, dwFileSize); //给图片分配全局内存
	void *pImageMemory=GlobalLock(hImageMemory); //锁定内存
	DWORD dwReadedSize; //保存实际读取的文件大小
	ReadFile(hFile, pImageMemory, dwFileSize, &dwReadedSize, NULL); //读取图片到全局内存当中
	GlobalUnlock(hImageMemory); //解锁内存CloseHandle(hFile); //关闭文件句柄
	IStream *pIStream;//创建一个IStream接口指针，用来保存图片流
	IPicture *pIPicture;//创建一个IPicture接口指针，表示图片对象
	CreateStreamOnHGlobal(hImageMemory, false, &pIStream); //用全局内存初使化IStream接口指针
	OleLoadPicture(pIStream, 0, false, IID_IPicture, (LPVOID*)&(pIPicture));//用OleLoadPicture获得IPicture接口指针
	//得到IPicture COM接口对象后，你就可以进行获得图片信息、显示图片等操作
	OLE_XSIZE_HIMETRIC hmWidth;
	OLE_YSIZE_HIMETRIC hmHeight;	
	pIPicture->get_Width(&hmWidth); //用接口方法获得图片的宽和高
	pIPicture->get_Height(&hmHeight);	
	pIPicture->Render(hDC,rt->left,rt->top,rt->right-rt->left,rt->bottom-rt->top,0,hmHeight,hmWidth,-hmHeight,NULL); //在指定的DC上绘出图片
	GlobalFree(hImageMemory); //释放全局内存
	pIStream->Release(); //释放
	pIPicture->Release(); //释放pIPicture
}

VOID SetText(HWND hWnd,LPCTSTR str)//设置文本框文本内容
{
	SendMessage(hWnd,WM_SETTEXT,(WPARAM)0,(LPARAM)str);	//添加内容
	SendMessage(hWnd,EM_SETSEL,(WPARAM)-2,(LPARAM)-1);	//设置焦点到末尾
}

VOID GetText(HWND hWnd,LPCTSTR str,int size)//设置文本框文本内容
{	
	SendMessage(hWnd,WM_GETTEXT,size,(LPARAM)str);	//添加内容
}

VOID ErrorBox(LPTSTR ErrorInfo)//错误提示框
{
	CHAR error1[50],error2[20];
	strcpy(error1,ErrorInfo);
	sprintf(error2," with error %d",GetLastError());	
	strcat(error1,error2);	
	MessageBox(MainWnd.hWnd,error1,"error",MB_OK);
}

VOID MsgBox(LPTSTR msg)//消息框
{
	MessageBox(MainWnd.hWnd,msg,"OK",MB_OK);
}