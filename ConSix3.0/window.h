#ifndef WINDOW_H_CONSIX
#define WINDOW_H_CONSIX

#include <windows.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <commdlg.h>
#include <commctrl.h>
#include <mmsystem.h>
#include <vector>
#include <ocidl.h>
#include <olectl.h>
#include "FileDlg.h"
#include "resource.h"

#pragma warning(disable:4996)
#pragma warning(disable:4244)

#pragma comment(lib,"winmm.lib")
#pragma comment(lib,"FileDlg.lib")

using namespace std;

#define GAP 1
#define ALLOW 5
#define MARGIN 10
#define RATIO 0.8
#define PI 3.14159

#define BLACK 0 //黑子、黑方
#define WHITE 1 //白子、白方
#define EMPTY 2 //空子

typedef unsigned char BYTE;

extern HINSTANCE hInst;
extern char CurDir[MAX_PATH-100];//当前应用程序的目录

VOID ErrorBox(LPTSTR ErrorInfo); //错误提示框
VOID MsgBox(LPTSTR msg); //消息提示框

#endif