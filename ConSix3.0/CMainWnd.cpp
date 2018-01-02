#include "CMainWnd.h"

CStatusBar StatusBar;
CNGDlg ngDlg;
CThread thread;

CSearch game; //定义游戏类
Point CurPoint;  //记录走过的点
Step CurStep;  //记录走过的步

int BlcTimeMin,BlcTimeSec,WhtTimeMin,WhtTimeSec;  //黑方和白方所用的分与秒

DWORD WINAPI ComToCom(LPVOID lpParam)
{
	CMainWnd *pMainWnd=(CMainWnd *)lpParam;	
	while(1)
	{
		if(game.GameStart==false)return 0;	
		if(game.StepID==0)  //电脑走的第一步
		{									    
			game.Board[9][9]=BLACK;  //第一步走正中间最好					 					 					 													 		

			CurStep.First.X=9;CurStep.First.Y=9;CurStep.First.side=BLACK;
			CurStep.Second.X=-1;CurStep.Second.Y=-1;CurStep.Second.side=BLACK;	
			game.UpdateBoard(CurStep,BLACK);	//更新棋盘
		}
		if(game.Player==BLACK &&game.StepID!=0)
		{
			game.ComputerColor=BLACK;
			CurStep=game.ComputerMove();  //这是算法的核心
			int X1=CurStep.First.X;int Y1=CurStep.First.Y;CurStep.First.side=BLACK;
			int X2=CurStep.Second.X;int Y2=CurStep.Second.Y;CurStep.Second.side=BLACK;		
			game.Board[X1][Y1]=BLACK;
			game.Board[X2][Y2]=BLACK;
			game.UpdateBoard(CurStep,BLACK);
		}
		else if(game.Player==WHITE)
		{
			game.ComputerColor=WHITE;
			CurStep=game.ComputerMove();  //这是算法的核心
			int X1=CurStep.First.X;int Y1=CurStep.First.Y;CurStep.First.side=WHITE;
			int X2=CurStep.Second.X;int Y2=CurStep.Second.Y;CurStep.Second.side=WHITE;		
			game.Board[X1][Y1]=WHITE;
			game.Board[X2][Y2]=WHITE;
			game.UpdateBoard(CurStep,WHITE);
		}
		game.PointHistory.push_back(CurStep.First);	//记录电脑走过的点
		game.PointHistory.push_back(CurStep.Second);
		game.StepHistory.push_back(CurStep);  //记录电脑走过的步	
		
			
		game.Player=NEXT(game.Player);	//轮到对方走
		game.StepID++;	//每走一步ID加一次	
		InvalidateRect(pMainWnd->hWnd,&pMainWnd->rtBoard,FALSE);
		pMainWnd->PlaySnd(0);	//播放落子声音		

		pMainWnd->OutputPointHistory(game.PointHistory);

		if(game.WinOrLose(BLACK)==WINLOSE)	//判断输赢
		{				
			MsgBox("黑棋赢了 ！");
			game.GameStart=false;					 
		}
		if(game.WinOrLose(WHITE)==WINLOSE)
		{				
			MsgBox("白棋赢了 ！");
			game.GameStart=false;					 
		}
	}	
	return 0;
}

DWORD WINAPI ComToPer(LPVOID lpParam)
{
	CMainWnd *pMainWnd=(CMainWnd *)lpParam;
	if(game.GameStart==false)return 0;
	if(game.StepID==0)  //电脑走的第一步
	{									    
		game.Board[9][9]=BLACK;  //第一步走正中间最好					 					 					 													 		

		CurStep.First.X=9;CurStep.First.Y=9;CurStep.First.side=BLACK;
		CurStep.Second.X=-1;CurStep.Second.Y=-1;CurStep.Second.side=BLACK;	
		game.UpdateBoard(CurStep,BLACK);	//更新棋盘
	}
	else if(game.ComputerColor==BLACK)
	{
		CurStep=game.ComputerMove();  //这是算法的核心
		int X1=CurStep.First.X;int Y1=CurStep.First.Y;CurStep.First.side=BLACK;
		int X2=CurStep.Second.X;int Y2=CurStep.Second.Y;CurStep.Second.side=BLACK;		
		game.Board[X1][Y1]=BLACK;
		game.Board[X2][Y2]=BLACK;
		game.UpdateBoard(CurStep,BLACK);
	}
	else if(game.ComputerColor==WHITE)
	{
		CurStep=game.ComputerMove();  //这是算法的核心
		int X1=CurStep.First.X;int Y1=CurStep.First.Y;CurStep.First.side=WHITE;
		int X2=CurStep.Second.X;int Y2=CurStep.Second.Y;CurStep.Second.side=WHITE;		
		game.Board[X1][Y1]=WHITE;
		game.Board[X2][Y2]=WHITE;
		game.UpdateBoard(CurStep,WHITE);
	}
	game.PointHistory.push_back(CurStep.First);	//记录电脑走过的点
	game.PointHistory.push_back(CurStep.Second);
	game.StepHistory.push_back(CurStep);  //记录电脑走过的点与步		
		
	game.Player=NEXT(game.Player);	//轮到对方走
	game.StepID++;	//每走一步ID加一次
	InvalidateRect(pMainWnd->hWnd,&pMainWnd->rtBoard,FALSE);
	pMainWnd->PlaySnd(0);	//播放落子声音		

	pMainWnd->OutputPointHistory(game.PointHistory);

	if(game.WinOrLose(BLACK)==WINLOSE)	//判断输赢
	{				
		MsgBox("黑棋赢了 ！");
		game.GameStart=false;					 
	}
	if(game.WinOrLose(WHITE)==WINLOSE)
	{				
		MsgBox("白棋赢了 ！");
		game.GameStart=false;					 
	}
	return 0;
}
	
BOOL CALLBACK AboutDlgProc(HWND hWnd,UINT uMsg,WPARAM wParam,LPARAM lParam)//关于对话框处理函数
{
	int ID=LOWORD(wParam);
	switch(uMsg)
	{
	case WM_INITDIALOG:
		return TRUE;
	case WM_COMMAND:		
		if(ID==IDB_OK ||ID==IDCANCEL)
			EndDialog(hWnd,0);
		return TRUE;
	default:		
		break;
	}
	return FALSE;
}

VOID Int64ToStr(LONGLONG num,char *str)
{
	for(int i=0;i<64;i++,str--)
		(*(str+63))=((num>>i)&(LONGLONG)1)+'0';
	return;
}
CMainWnd::CMainWnd()
{
	ClsName="MAINWND";
	WndName="ConSix3.0";
	BkColor=RGB(0,0,0);
	BoardColor=RGB(255,255,0);		
	debug_hashID=false;
}

CMainWnd::~CMainWnd()
{

}

BOOL CMainWnd::RegisterWnd(HINSTANCE hInst)
{		
	wc.hInstance=hInst;
	wc.lpszClassName=ClsName;
	wc.lpfnWndProc=(WNDPROC)WndProc;
	wc.hIcon=LoadIcon(hInst,MAKEINTRESOURCE(IDI_CONSIX));
	wc.lpszMenuName=MAKEINTRESOURCE(IDR_MAIN_MENU);
	wc.hCursor=LoadCursor(NULL,IDC_ARROW);
	wc.hbrBackground=(HBRUSH)GetStockObject(WHITE_BRUSH);	
	wc.style=CS_HREDRAW |CS_VREDRAW |CS_DBLCLKS;
	wc.cbWndExtra=0;
	wc.cbClsExtra=0;
	if(RegisterClass(&wc)==NULL)
	{
		ErrorBox("RegisterMainWindowClass failed");
		return FALSE;
	}
	return TRUE;
}

BOOL CMainWnd::CreateWnd()
{
	hMainMenu=LoadMenu(wc.hInstance,MAKEINTRESOURCE(IDR_MAIN_MENU));

	hWnd=CreateWindow(
		ClsName,//Class name
		WndName,//Window name		
		WS_VISIBLE |
		WS_OVERLAPPED |	
		WS_CAPTION |
		WS_SYSMENU |		
		WS_MAXIMIZEBOX |
		WS_MINIMIZEBOX |		
		WS_SIZEBOX |
		WS_CLIPCHILDREN |//Excludes the area occupied by child windows when drawing occurs within the parent window.
		WS_CLIPSIBLINGS ,//Excludes the area occupied by child windows when drawing occurs within another child window.
		0,0,//左上角
		700,720,//Default size
		(HWND)NULL,//No parent window		
		hMainMenu,//Main menu
		wc.hInstance,//Application instance
		NULL//Do not create MDI client window
		);
	if(hWnd==NULL)
	{		
		ErrorBox("CreateMainWindow failed");		
		return FALSE;
	}	
	CreateAndAdjustStatusBar();
	ShowWindow(hWnd,SW_NORMAL);
	UpdateWindow(hWnd);
	return TRUE;
}

VOID CMainWnd::OnPaint(WPARAM wParam,LPARAM lParam)
{
	hDC=BeginPaint(hWnd,&ps);	
	
	GetClientRectEx(&rtClient);
	hMemDC=CreateCompatibleDC(hDC);//创建与显示器DC兼容的内存DC
	hBitmap=CreateCompatibleBitmap(hDC,rtClient.right,rtClient.bottom);
	hOldBitmap=(HBITMAP)SelectObject(hMemDC,hBitmap);
		
	DrawBoard();//绘制棋盘

	BitBlt(hDC,0,0,rtClient.right,rtClient.bottom,hMemDC,0,0,SRCCOPY);	//从内存往显示器拷贝
		
	DeleteObject(hBitmap);
	DeleteDC(hMemDC);
	DeleteDC(hDC);

	EndPaint(hWnd,&ps);
	return;
}

bool CMainWnd::DrawBoard()//绘制棋盘
{	
	FillBkAndBoard();//填充背景

	int d=side/20;
	double pixel=((double)side)/600;
	HPEN hPen,hOldPen;
	hPen=CreatePen(PS_SOLID,(int)(2*pixel),RGB(0,0,0));
	hOldPen=(HPEN)SelectObject(hMemDC,hPen);

	int fWidth,fHeight;
	HFONT hFont,hOldFont;
	fWidth=(int)(d/3);
	fHeight=(int)(d*2/3);
	hFont=CreateSimpleFont(fWidth,fHeight);
	hOldFont=(HFONT)SelectObject(hMemDC,hFont);
	
	char letter[2],number[3];
	memset(letter,0,sizeof(letter));
	memset(number,0,sizeof(number));
	int i,j;
	for(i=0;i<19;i++)
	{			
		letter[0]='A'+i;
		itoa(i,number,10);
		TextOut(hMemDC,(int)(rtBoard.left+side*(i+1)/20-fWidth/2),rtBoard.top,letter,1);//绘制文字
		if(i<10)
		{
			TextOut(hMemDC,(int)(rtBoard.left+side*(i+1)/20-fWidth/2),rtBoard.bottom-fHeight,number,1);
		}
		else
		{
			TextOut(hMemDC,(int)(rtBoard.left+side*(i+1)/20-fWidth),rtBoard.bottom-fHeight,number,2);
		}				
		MoveToEx(hMemDC,rtBoard.left+d,(int)(rtBoard.top+side*(i+1)/20),NULL);//绘制线
		LineTo(hMemDC,rtBoard.right-d,(int)(rtBoard.top+side*(i+1)/20));
	}
	for(i=0;i<19;i++)
	{
		letter[0]='A'+i;
		itoa(i,number,10);
		TextOut(hMemDC,rtBoard.left+fWidth,(int)(rtBoard.top+side*(i+1)/20-fHeight/2),letter,1);
		if(i<10)
		{
			TextOut(hMemDC,rtBoard.right-fWidth*2,(int)(rtBoard.top+side*(i+1)/20-fHeight/2),number,1);
		}
		else
		{
			TextOut(hMemDC,rtBoard.right-fWidth*2,(int)(rtBoard.top+side*(i+1)/20-fHeight/2),number,2);
		}
		MoveToEx(hMemDC,rtBoard.left+side*(i+1)/20,rtBoard.top+d,NULL);
		LineTo(hMemDC,rtBoard.left+side*(i+1)/20,rtBoard.bottom-d);
	}
	
	HDC hBlcDC,hWhtDC,hCurBlcDC,hCurWhtDC;
	hBlcDC=CreateCompatibleDC(hDC);
	hWhtDC=CreateCompatibleDC(hDC);
	hCurBlcDC=CreateCompatibleDC(hDC);
	hCurWhtDC=CreateCompatibleDC(hDC);

	HBITMAP hBlcBmp,hWhtBmp,hCurBlcBmp,hCurWhtBmp;
	hBlcBmp=CreateCompatibleBitmap(hDC,d,d);
	hWhtBmp=CreateCompatibleBitmap(hDC,d,d);
	hCurBlcBmp=CreateCompatibleBitmap(hDC,d,d);
	hCurWhtBmp=CreateCompatibleBitmap(hDC,d,d);

	SelectObject(hBlcDC,hBlcBmp);
	SelectObject(hWhtDC,hWhtBmp);
	SelectObject(hCurBlcDC,hCurBlcBmp);
	SelectObject(hCurWhtDC,hCurWhtBmp);

	DrawChess(hBlcDC,hWhtDC,hCurBlcDC,hCurWhtDC,d);//绘制棋子
	
	for(i=0;i<19;i++)
	{
		for(j=0;j<19;j++)
		{
			if(game.Board[i][j]==BLACK)
			{
				if((CurStep.First.X==i &&CurStep.First.Y==j) ||(CurStep.Second.X==i &&CurStep.Second.Y==j))
					BitBlt(hMemDC,rtBoard.left+side*(i+1)/20-d/2,rtBoard.top+side*(j+1)/20-d/2,d,d,hCurBlcDC,0,0,SRCCOPY);
				else
					BitBlt(hMemDC,rtBoard.left+side*(i+1)/20-d/2,rtBoard.top+side*(j+1)/20-d/2,d,d,hBlcDC,0,0,SRCCOPY);
			}
			if(game.Board[i][j]==WHITE)
			{
				if((CurStep.First.X==i &&CurStep.First.Y==j) ||(CurStep.Second.X==i &&CurStep.Second.Y==j))
					BitBlt(hMemDC,rtBoard.left+side*(i+1)/20-d/2,rtBoard.top+side*(j+1)/20-d/2,d,d,hCurWhtDC,0,0,SRCCOPY);
				else
					BitBlt(hMemDC,rtBoard.left+side*(i+1)/20-d/2,rtBoard.top+side*(j+1)/20-d/2,d,d,hWhtDC,0,0,SRCCOPY);
			}			
		}
	}	
	DeleteObject(hPen);
	DeleteObject(hFont);

	DeleteObject(hBlcBmp);
	DeleteObject(hWhtBmp);
	DeleteObject(hCurBlcBmp);
	DeleteObject(hCurBlcBmp);

	DeleteDC(hBlcDC);
	DeleteDC(hWhtDC);
	DeleteDC(hCurBlcDC);
	DeleteDC(hCurWhtDC);
	return true;
}

bool CMainWnd::FillBkAndBoard()
{	
	SIZE siBmp;
	BITMAP bitmap;
	GetObject(hBitmap,sizeof(BITMAP),&bitmap);
	siBmp.cx=bitmap.bmWidth;
	siBmp.cy=bitmap.bmHeight;

	LOGBRUSH lb;
	lb.lbColor=BkColor;
	lb.lbStyle=BS_SOLID;
	HBRUSH hBkBrush,hBoardBrush,hOldBrush;
	hBkBrush=CreateBrushIndirect(&lb);
	hOldBrush=(HBRUSH)SelectObject(hMemDC,hBkBrush);
	PatBlt(hMemDC,0,0,siBmp.cx,siBmp.cy,PATCOPY);
	SetBkMode(hMemDC,TRANSPARENT);
		
	side=(siBmp.cx>siBmp.cy? siBmp.cy:siBmp.cx);
	side-=(MARGIN*2);
	
	rtBoard.left=(int)((siBmp.cx-side)/2);
	rtBoard.top=(int)((siBmp.cy-side)/2);
	rtBoard.right=rtBoard.left+side;
	rtBoard.bottom=rtBoard.top+side;		

	lb.lbColor=BoardColor;
	hBoardBrush=CreateBrushIndirect(&lb);
	hOldBrush=(HBRUSH)SelectObject(hMemDC,hBoardBrush);
	PatBlt(hMemDC,rtBoard.left,rtBoard.top,(rtBoard.right-rtBoard.left),(rtBoard.bottom-rtBoard.top),PATCOPY);
	return true;
}

bool CMainWnd::DrawChess(HDC hBlcDC,HDC hWhtDC,HDC hCurBlcDC,HDC hCurWhtDC,int d)
{
	double pixel=0.8,shadow=0.7;
	BOOL Alias=true;

	int red=255-GetRValue(BoardColor);
	int green=255-GetGValue(BoardColor);
	int blue=255-GetBValue(BoardColor);

	COLORREF pb,pw;
	double di,dj,d2=(double)d/2.0-5e-1,r=d2-2e-1,f=sqrt(3.0);
	double x,y,z,xr,xg,hh;
	int g;	

	for (int i=0; i<d; i++)
	{
		for (int j=0; j<d; j++)
		{	
			di=i-d2; dj=j-d2;
			hh=r-sqrt(di*di+dj*dj);
			if (hh>=0)
			{	z=r*r-di*di-dj*dj;
			    if (z>0) z=sqrt(z)*f;
			    else z=0;
				x=di; y=dj;
				xr=sqrt(6*(x*x+y*y+z*z));
				xr=(2*z-x+y)/xr;
				if (xr>0.9) xg=(xr-0.9)*10;
				else xg=0;
				if (hh>pixel || !Alias)
				{
					g=(int)(10+10*xr+xg*140);
					pb=(g<<16)|(g<<8)|g;
					g=(int)(200+10*xr+xg*45);
					pw=(g<<16)|(g<<8)|g;
				}
				else
				{	hh=(pixel-hh)/pixel;
					g=(int)(10+10*xr+xg*140);
					double shade;
					if (di-dj<r/3) shade=1;
					else shade=shadow;

					pb=(//(255<<24)|
					    (((int)((1-hh)*g+hh*shade*red))<<16)
						|(((int)((1-hh)*g+hh*shade*green))<<8)
						|((int)((1-hh)*g+hh*shade*blue)));

					g=(int)(200+10*xr+xg*45);

					pw=(//(255<<24)|
					    (((int)((1-hh)*g+hh*shade*red))<<16)
						|(((int)((1-hh)*g+hh*shade*green))<<8)
						|((int)((1-hh)*g+hh*shade*blue)));
				}
			}
			else pb=pw=BoardColor;
					
			SetPixel(hBlcDC,j,i,pb);
			SetPixel(hWhtDC,j,i,pw);			
			
			SetPixel(hCurBlcDC,j,i,pb);
			SetPixel(hCurWhtDC,j,i,pw);			
		}
	}
	HPEN hPen=CreatePen(PS_SOLID,1,RGB(255,0,0));

	HPEN hOldPen=(HPEN)SelectObject(hCurBlcDC,hPen);
	MoveToEx(hCurBlcDC,d/2,d/4,NULL);LineTo(hCurBlcDC,d/2,d*3/4);
	MoveToEx(hCurBlcDC,d/4,d/2,NULL);LineTo(hCurBlcDC,d*3/4,d/2);	
	SelectObject(hCurBlcDC,hOldPen);	
	
	hOldPen=(HPEN)SelectObject(hCurWhtDC,hPen);
	MoveToEx(hCurWhtDC,d/2,d/4,NULL);LineTo(hCurWhtDC,d/2,d*3/4);
	MoveToEx(hCurWhtDC,d/4,d/2,NULL);LineTo(hCurWhtDC,d*3/4,d/2);	
	SelectObject(hCurWhtDC,hOldPen);	 
	return true;
}

VOID CMainWnd::OnSize(WPARAM wParam,LPARAM lParam)
{
	CreateAndAdjustStatusBar();
	return;
}

VOID CMainWnd::OnNotify(WPARAM wParam,LPARAM lParam)
{
	return;
}

VOID CMainWnd::OnCommand(WPARAM wParam,LPARAM lParam)//菜单控制
{
	int ID=LOWORD(wParam);	
	switch(ID)
	{	
	case IDM_GAME_NEW:
		NewGame();
		break;	
	case IDM_EXIT:
		OnClose(wParam,lParam);		
		break;
	case IDM_OUTPUT_ALL_LINE:
		game.OutputAllLineInfo();
		break;
	case IDM_CREATE_SEARCH_RECORD:
		game.SearchRecord=(game.SearchRecord? false:true);
		CheckMenuItem(hMainMenu,IDM_CREATE_SEARCH_RECORD,(game.SearchRecord?MF_CHECKED:MF_UNCHECKED));
		break;
	case IDM_CM_TOOL:
		OpenToolOfCM();
		break;
	case IDM_CM_READ:
		Readcm();
		break;
	case IDM_AND_START_ENGINE:
		ReadcmAndStartEngine();
		break;
	case IDM_CM_SAVE:
		Savecm();
		break;
	case IDM_HASHID:
		debug_hashID=(debug_hashID==true?false:true);
		CheckMenuItem(hMainMenu,IDM_HASHID,(debug_hashID?MF_CHECKED:MF_UNCHECKED));
		break;
	case IDM_INSTRUCTION:
		Instructions();
		break;
	case IDM_ABOUT:
		DialogBox(wc.hInstance,MAKEINTRESOURCE(IDD_ABOUT),hWnd,(DLGPROC)AboutDlgProc);
		break;
	default:
		break;
	}	
	return;
}

VOID CMainWnd::Instructions()
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si,sizeof(si));
	si.cb=sizeof(si);
	si.dwFlags=STARTF_USESHOWWINDOW |STARTF_USESTDHANDLES;	
	si.wShowWindow=SW_SHOW;
	si.hStdError=GetStdHandle(STD_ERROR_HANDLE);
	
	char AppName[MAX_PATH] = TEXT("C:\\WINDOWS\\NOTEPAD.EXE");//资源管理器程序	
	char FileName[MAX_PATH];// =  TEXT("C:\\1.doc");	
	strcpy(FileName,CurDir);
	strcat(FileName,"\\Instructions.txt");

	char CmdLine[2*MAX_PATH]={0};
	sprintf(CmdLine,"\"%s\" \"%s\"",AppName,FileName);
	if(!CreateProcess(NULL,CmdLine,NULL,NULL,false,0,NULL,NULL,&si,&pi))//打开引擎进程
	{
		ErrorBox("CreateProcess failed");
		return;
	}
	SetCurrentDirectory(CurDir);
	return;
}

VOID CMainWnd::CalHashID(int x,int y)
{
	static int count=0;
	static int x1=0;
	static int y1=0;
	count++;
	if(count==1)
	{
		x1=x;y1=y;
	}
	if(count==2)
	{
		count=0;
		LONGLONG hashkey[2][2]={0};
		hashkey[0][0]=game.Rand64(0,x1,y1);hashkey[0][1]=game.Rand64(0,x,y);
		hashkey[1][0]=game.Rand64(1,x1,y1);hashkey[1][1]=game.Rand64(1,x,y);

		LONGLONG hashID[2]={0};
		hashID[0]=hashkey[0][0]^hashkey[0][1];
		hashID[1]=hashkey[1][0]^hashkey[1][1];

		char strPoint[2][2][70]={0};
		Int64ToStr(hashkey[0][0],strPoint[0][0]);
		Int64ToStr(hashkey[0][1],strPoint[0][1]);
		Int64ToStr(hashkey[1][0],strPoint[1][0]);
		Int64ToStr(hashkey[1][1],strPoint[1][1]);

		char strStep[2][70]={0};
		Int64ToStr(hashID[0],strStep[0]);
		Int64ToStr(hashID[1],strStep[1]);

		char str[2][300]={0};
		sprintf(str[0],"Black:\r\nHashkey for point(%2d,%2d):\t%s\r\nHashkey for point(%2d,%2d):\t%s\r\nHashID for step(%2d,%2d;%2d,%2d):\t%s\r\n",x1,y1,strPoint[0][0],x,y,strPoint[0][1],x1,y1,x,y,strStep[0]);
		sprintf(str[1],"White:\r\nHashkey for point(%2d,%2d):\t%s\r\nHashkey for point(%2d,%2d):\t%s\r\nHashID for step(%2d,%2d;%2d,%2d):\t%s\r\n",x1,y1,strPoint[1][0],x,y,strPoint[1][1],x1,y1,x,y,strStep[1]);
		char msg[700]={0};
		strcpy(msg,str[0]);strcat(msg,"\r\n");strcat(msg,str[1]);
		MsgEdit(msg);
	}	
}

VOID CMainWnd::MsgEdit(char *msg)
{
	HWND hEdit=CreateWindow(
		"EDIT",
		"Msg",		
		WS_VISIBLE |WS_OVERLAPPEDWINDOW |WS_HSCROLL |WS_VSCROLL |
		ES_LEFT |ES_MULTILINE |ES_READONLY |ES_AUTOHSCROLL |ES_AUTOVSCROLL,
		CW_USEDEFAULT,
		0,
		CW_USEDEFAULT,
		0,
		hWnd,
		NULL,
		hInst,
		NULL
		);			
	SetText(hEdit,msg);		
	ShowWindow(hEdit,SW_SHOW);
	UpdateWindow(hEdit);
	return;
}

VOID CMainWnd::OnLButtonDown(WPARAM wParam,LPARAM lParam)
{	
	int x,y;
	x=LOWORD(lParam);
	y=HIWORD(lParam);

	if(!InsideRect(&rtBoard,x,y))
		return;			
	x=(int)((x-rtBoard.left-side/40)*20/side);//把棋盘坐标转换成数组坐标
	y=(int)((y-rtBoard.top-side/40)*20/side);	
	
	if(debug_hashID)
	{
		CalHashID(x,y);
		return;
	}
	if(game.ComputerColor==BLACK)  //电脑先走的情况
	{							
		if(game.Player==WHITE)  //人执白后走
		{									
			HumanMove(x,y);								 									
		}
		if(game.Player==BLACK)//电脑执黑先走
		{					   					
			thread.StartThread(ComToPer,this);	//执行电脑走黑棋								            				  				
		}
	}
	if(game.ComputerColor==WHITE)  //人先走的情况
	{						
		if(game.Player==BLACK)//人执黑先走
		{			
			HumanMove(x,y);									 				
		}
		if(game.Player==WHITE)
		{
			thread.StartThread(ComToPer,this);//电脑执白后走				 							  								
		}						  						      
	}
	if(game.ComputerColor==EMPTY)
	{
		PerToPer(x,y);
	}
	game.PointID++;
	OutputPointHistory(game.PointHistory);
	return;
}

VOID CMainWnd::HumanMove(int x,int y)
{	
	vector<Point>::iterator iter;		
	if(game.StepID==0)  //人走的第一步
	{		
		if(game.Board[x][y]!=EMPTY)return;

		game.Board[x][y]=BLACK;  //加载棋子  
		CurPoint.X=x;CurPoint.Y=y;CurPoint.side=BLACK;
		CurStep.First=CurPoint;			

		CurPoint.X=-1;CurPoint.Y=-1;CurPoint.side=BLACK;
		CurStep.Second=CurPoint;
		
		game.PointHistory.push_back(CurStep.First);
		game.PointHistory.push_back(CurStep.Second);  //存储人走过的点		
			
		game.StepHistory.push_back(CurStep);  //存储人走的步

		game.UpdateBoard(CurStep,BLACK);	//更新棋盘

		game.Player=NEXT(game.Player);	
		game.StepID++;
	}	
	else if(game.ComputerColor==BLACK &&game.StepID!=0) //电脑执黑，人的招法
	{
		if(game.Board[x][y]!=EMPTY)return;

		game.Board[x][y]=WHITE;  //加载棋子                 
		CurPoint.X=x;CurPoint.Y=y;CurPoint.side=WHITE;
		game.PointHistory.push_back(CurPoint); //存储人走过的点

		if((game.PointID)%2==1) //当人落第二点才能记录人走的每一步
		{		
			int i;
			for(i=0,iter=game.PointHistory.end();i<1;i++)
			{
				CurStep.Second=*(--iter);
				CurStep.First=*(--iter);				
			}
			game.StepHistory.push_back(CurStep);//存储人过走的步

			game.UpdateBoard(CurStep,WHITE);	//更新棋盘

			game.Player=NEXT(game.Player);
			game.StepID++;
		}			
	}
	else if(game.ComputerColor==WHITE &&game.StepID!=0)	 //电脑执白，人的招法
	{
		if(game.Board[x][y]!=EMPTY)return;

		game.Board[x][y]=BLACK;  //加载棋子                 
		CurPoint.X=x;CurPoint.Y=y;CurPoint.side=BLACK;
		game.PointHistory.push_back(CurPoint);  //存储人走过的点

		if((game.PointID)%2==0) //当人落第二点才能记录人走的每一步
		{		
			int i;
			for(i=0,iter=game.PointHistory.end();i<1;i++)
			{
				CurStep.Second=*(--iter);
				CurStep.First=*(--iter);				
			}
			game.StepHistory.push_back(CurStep);//存储人走过的步

			game.UpdateBoard(CurStep,BLACK);	//更新棋盘

			game.Player=NEXT(game.Player);
			game.StepID++;
		}			
	}
	InvalidateRect(hWnd,&rtBoard,FALSE);
	PlaySnd(0);	//播放落子声音		
	if(game.WinOrLose(BLACK)==WINLOSE)  //判断输赢
	{					
		MsgBox("黑棋赢了 ！");
		game.GameStart =false;		
	} 
	if(game.WinOrLose(WHITE)==WINLOSE)
	{					
		MsgBox("白棋赢了 ！");
		game.GameStart =false;		
	} 
	return;
}

VOID CMainWnd::PerToPer(int x,int y)
{
	if(game.Board[x][y]!=EMPTY)return;
	vector<Point>::iterator iter;
	if(game.StepID ==0)  //先走一个黑子
	{					
		CurPoint.X=x;CurPoint.Y=y;CurPoint.side=BLACK;
		CurStep.First=CurPoint;	

		CurPoint.X=-1;CurPoint.Y=-1;CurPoint.side=BLACK;					
		CurStep.Second=CurPoint;
	
		game.PointHistory.push_back(CurStep.First);
		game.PointHistory.push_back(CurStep.Second);
		
		game.StepHistory.push_back(CurStep);

		game.Board[x][y]=BLACK;
		game.UpdateBoard(CurStep,BLACK);
		game.Player=NEXT(game.Player); 		
		game.StepID++;			
	}
	
	else if(game.Player==WHITE&&game.StepID!=0 )  //再走两个白子
	{					
		CurPoint.X=x;CurPoint.Y=y;CurPoint.side=WHITE;
		game.PointHistory.push_back(CurPoint);
		game.Board[x][y]=WHITE;

		if(game.PointID%2==0)
		{			
			iter=game.PointHistory.end()-1;
			CurStep.Second=*(iter);
			CurStep.First=*(iter-1);
			 
			game.StepHistory.push_back(CurStep);
			game.UpdateBoard(CurStep,WHITE);
			game.Player=NEXT(game.Player); 	
			game.StepID++;
		}							
	}
	else if(game.Player==BLACK &&game.StepID!=0 )//再走两个黑子
	{				
		CurPoint.X=x;CurPoint.Y=y;CurPoint.side=BLACK;
		game.PointHistory.push_back(CurPoint);
		game.Board[x][y]=BLACK;
		if(game.PointID%2==0)
		{   
			iter=game.PointHistory.end()-1;
			CurStep.Second=*(iter);
			CurStep.First=*(iter-1);
			 
			game.StepHistory.push_back(CurStep);
			game.UpdateBoard(CurStep,BLACK);
			game.Player=NEXT(game.Player); 
			game.StepID++;
		}			
	}
	InvalidateRect(hWnd,&rtBoard,FALSE);
	PlaySnd(0);	//播放落子声音		
	if(game.WinOrLose(BLACK)==WINLOSE)  //判断输赢
	{					
		MsgBox("黑棋赢了 ！");
		game.GameStart =false;		
	} 
	if(game.WinOrLose(WHITE)==WINLOSE)
	{					
		MsgBox("白棋赢了 ！");
		game.GameStart =false;		
	} 
	return;
}

VOID CMainWnd::OnMouseMove(WPARAM wParam,LPARAM lParam)
{                                               
	int x,y;
	x=LOWORD(lParam);
	y=HIWORD(lParam);
	
	return;
}

VOID CMainWnd::OnTimer(WPARAM wParam,LPARAM lParam)
{	
	if(game.Player==BLACK) //计算黑方的时间
	{				
		BlcTimeSec++;
		if(BlcTimeSec==60)
		{
			BlcTimeMin++;
			BlcTimeSec=0;
		}				
	}
	if(game.Player==WHITE)	//计算白方的时间
	{				
		WhtTimeSec++;
		if(WhtTimeSec==60)
		{
			WhtTimeMin++;
			WhtTimeSec=0;
		}				
	}	
	char TimeBlc[20]={0};
	char TimeWht[20]={0};
	sprintf(TimeBlc,"黑方用时：%2d : %2d",BlcTimeMin,BlcTimeSec);
	sprintf(TimeWht,"白方用时：%2d : %2d",WhtTimeMin,WhtTimeSec);
	StatusBar.SetStatusBar(1,TimeBlc);
	StatusBar.SetStatusBar(2,TimeWht);

	if(game.ComputerColor==BLACK)
	{
		if(BlcTimeMin*60+BlcTimeSec>14*60+30)
		{
			game.LargeDepth[BLACK]=5;
		}
	}	
	else if(game.ComputerColor==WHITE)
	{
		if(WhtTimeMin*60+WhtTimeSec>14*60+30)
		{
			game.LargeDepth[WHITE]=5;
		}
	}
	return;
}

VOID CMainWnd::OnClose(WPARAM wParam,LPARAM lParam)
{	
	DestroyWindow(hWnd);
	return;
}

VOID CMainWnd::OnDestroy(WPARAM wParam,LPARAM lParam)
{
	PostQuitMessage(0);
	return;
}

VOID CMainWnd::CreateAndAdjustStatusBar()
{
	if(StatusBar.hWnd!=NULL)
	{
		StatusBar.DestroyStatusBar();		
	}	
	RECT rt;
	GetClientRect(hWnd,&rt);
	int width[3];
	width[0]=rt.right*0.6;
	width[1]=rt.right*0.8;
	width[2]=rt.right;
	if(StatusBar.hWnd==NULL)
	{
		StatusBar.CreateStatusBar(hWnd,3,width);
		StatusBar.ShowStatusBar();
	}		
	return;
}

VOID CMainWnd::GetClientRectEx(RECT* rt)
{	
	GetClientRect(hWnd,rt);	
	if(StatusBar.viewed==true)//如果状态条显示，则主窗体的客户端矩形不包括状态条
	{
		RECT rtSB;
		GetWindowRect(StatusBar.hWnd,&rtSB);
		rt->bottom-=(rtSB.bottom-rtSB.top);
	}
	return; 
}

VOID CMainWnd::NewGame()
{
	ngDlg.OnCreate(IDD_GAME_NEW);		
	if(ngDlg.ID==IDOK)
	{
		StartGame();
	}
	return;
}

VOID CMainWnd::StartGame()
{	
	game.InitGame();
	InvalidateRect(hWnd,&rtBoard,FALSE);

	game.GameStart=true;
	SetTimer(hWnd,0,1000,NULL);			

	game.MaxDepthBackUp=ngDlg.depth;
	game.LargeDepthBackUp=11; //备份最大深度和拓展深度	

	if(ngDlg.side==0)
	{
		game.ComputerColor=EMPTY;
	}
	else if(ngDlg.side==1)
	{		
		game.ComputerColor=WHITE;
		game.MaxDepth[WHITE]=ngDlg.depth; //水平线深度，可选择。默认为5
		game.LargeDepth[WHITE]=game.LargeDepthBackUp; //拓展深度默认为9

		game.ReadCM(WHITE);
	}
	else if(ngDlg.side==2)
	{							
		game.ComputerColor=BLACK;
		game.MaxDepth[BLACK]=ngDlg.depth; //水平线深度，可选择。默认为5
		game.LargeDepth[BLACK]=game.LargeDepthBackUp; //拓展深度默认为9

		game.ReadCM(BLACK);
		thread.StartThread(ComToPer,this);
	}
	else if(ngDlg.side==3)
	{
		game.ComToCom=true;
		game.ComputerColor=BLACK;//此时电脑颜色先赋值为黑色，以后随着选手的改变而改变
		game.MaxDepth[BLACK]=ngDlg.depth; //水平线深度，可选择。默认为5
		game.LargeDepth[BLACK]=game.LargeDepthBackUp; //拓展深度默认为9
		game.MaxDepth[WHITE]=ngDlg.depth; //水平线深度，可选择。默认为5
		game.LargeDepth[WHITE]=game.LargeDepthBackUp; //拓展深度默认为9

		game.ReadCM(BLACK);
		game.ReadCM(WHITE);
		thread.StartThread(ComToCom,this);
	}
	return;
}

bool CMainWnd::PlaySnd(int sel)
{
	char filename[MAX_PATH]={0};
	strcpy(filename,CurDir);
	switch(sel)
	{
	case 0:
		strcat(filename,"\\wav\\落子.wav");
		break;
	default:
		break;
	}	
	if(!PlaySound(filename,NULL,SND_NOWAIT |SND_FILENAME))
	{
		ErrorBox("PlaySound failed");
		return false;
	}
	return true;
}

VOID CMainWnd::OutputPointHistory(vector<Point> PointHistory)
{
	FILE *F1=fopen("PointHistory.txt","w");
	fprintf(F1,"J,-1,-1\n");
	for(vector<Point>::iterator iter=PointHistory.begin();iter!=PointHistory.end();iter++)
	{
		if(iter->side==BLACK)
			fprintf(F1,"B,%d,%d\n",iter->X,iter->Y);
		if(iter->side==WHITE)
			fprintf(F1,"W,%d,%d\n",iter->X,iter->Y);
	}
	fprintf(F1,"V,-1,-1");
	fclose(F1);
}

VOID CMainWnd::OpenToolOfCM()
{
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	ZeroMemory(&si,sizeof(si));
	si.cb=sizeof(si);
	si.dwFlags=STARTF_USESHOWWINDOW |STARTF_USESTDHANDLES;	
	si.wShowWindow=SW_SHOW;
	si.hStdError=GetStdHandle(STD_ERROR_HANDLE);
		
	char FileName[MAX_PATH]={0};
	char dir[MAX_PATH]={0};
	strcpy(FileName,CurDir);
	strcat(FileName,"\\tools\\cmConSix.exe");	

	strcpy(dir,CurDir);
	strcat(dir,"\\tools");	

	if(!CreateProcess(FileName,NULL,NULL,NULL,false,0,NULL,dir,&si,&pi))//打开引擎进程
	{
		ErrorBox("CreateProcess failed");
		return;
	}
	SetCurrentDirectory(CurDir);
	return;
}

bool CMainWnd::Readcm() //读取用户指定路径的棋谱
{	
	game.InitGame();

	char c='\0';
	int x=0,y=0,count=0;
	Point point;
	Step step;

	FILE * FRead=NULL;
	LPCSTR pathCM=NULL;
	char Filter[]="(txt files)|*.txt|(sgf files)|*.sgf|(all files)|*.*||";//滤镜
	CFileDialog FileName(true,NULL,NULL,Filter,hWnd);
	int ID=FileName.DoModal();	
	if(ID==IDOK)
	{
		pathCM=FileName.GetFilePath(); //获取打开对话框的路径
		::SetCurrentDirectory(CurDir);
		FRead=fopen(pathCM,"r");			
		while(!feof(FRead))
		{						
			fscanf(FRead,"%c,%d,%d\n",&c,&x,&y);				
			if(c=='J')continue;
			if(c=='V')break;			
			if(c=='B')
			{
				if(x!=-1){game.Board[x][y]=BLACK;}				
				point.X=x;point.Y=y;point.side=BLACK;
				game.PointHistory.push_back(point);
				if((count%2)==0)
					step.First=point;
				else
				{
					step.Second=point;
					game.UpdateBoard(step,BLACK);
				}
			}		
			if(c=='W')
			{
				game.Board[x][y]=WHITE;	
				point.X=x;point.Y=y;point.side=WHITE;
				game.PointHistory.push_back(point);
				if((count%2)==0)
					step.First=point;
				else
				{
					step.Second=point;
					game.UpdateBoard(step,WHITE);
				}
			}		
			count++;
		}
		fclose(FRead);		
		game.StepID=count/2; 
		game.PointID=count-1; //点击次数应是棋谱黑白子个数减一
		CurStep.First=*(game.PointHistory.end()-2);
		CurStep.Second=*(game.PointHistory.end()-1);			
		InvalidateRect(hWnd,&rtBoard,FALSE);
		return true;
	}	
	return false;
}

VOID CMainWnd::ReadcmAndStartEngine()
{
	if(!Readcm())
		return;

	if(game.StepID%2==1)
		game.ComputerColor=BLACK;
	else
		game.ComputerColor=WHITE;

	game.MaxDepthBackUp=5;
	game.LargeDepthBackUp=11;
	game.MaxDepth[BLACK]=game.MaxDepthBackUp;
	game.MaxDepth[WHITE]=game.MaxDepthBackUp;
	game.LargeDepth[BLACK]=game.LargeDepthBackUp;
	game.LargeDepth[WHITE]=game.LargeDepthBackUp;

	CurStep=game.ComputerMove();

	int X1=CurStep.First.X;int Y1=CurStep.First.Y;CurStep.First.side=game.ComputerColor;
	int X2=CurStep.Second.X;int Y2=CurStep.Second.Y;CurStep.Second.side=game.ComputerColor;		
	game.Board[X1][Y1]=game.ComputerColor;
	game.Board[X2][Y2]=game.ComputerColor;
	game.UpdateBoard(CurStep,game.ComputerColor);	

	game.PointHistory.push_back(CurStep.First);	//记录电脑走过的点
	game.PointHistory.push_back(CurStep.Second);
	game.StepHistory.push_back(CurStep);  //记录电脑走过的步	
					
	game.Player=NEXT(game.Player);	//轮到对方走
	game.StepID++;	//每走一步ID加一次	

	InvalidateRect(hWnd,&rtBoard,FALSE);
	PlaySnd(0);	//播放落子声音		

	return;
}

VOID CMainWnd::Savecm() //把棋谱保存在用户指定的位置
{
	// TODO: Add your command handler code here
	int i=0;	
	char Str='\0';
	FILE * FSave=NULL;	
	LPCTSTR pathCM;	
	vector<Point>::iterator iterP;
		
	char Filter[]="(txt files)|*.txt|(sgf files)|*.sgf|(all files)|*.*||";//滤镜
	CFileDialog FileName(false,NULL,NULL,Filter,hWnd);
	int ID=FileName.DoModal();
	
	if(ID==IDOK)
	{
		pathCM=FileName.GetFilePath();//指定保存的路径

		FSave=fopen(pathCM,"w");		
		fprintf(FSave,"J,-1,-1\n");
		for(iterP=game.PointHistory.begin(),i=0;iterP!=game.PointHistory.end();iterP++,i++)
		{
			if(int(i/2)%2==0)
				Str='B';
			else
				Str='W';
			fprintf(FSave,"%c,%d,%d\n",Str,iterP->X,iterP->Y);

		}
		fprintf(FSave,"V,-1,-1\n");
		fclose(FSave);
	}
}