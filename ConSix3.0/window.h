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

#define BLACK 0 //���ӡ��ڷ�
#define WHITE 1 //���ӡ��׷�
#define EMPTY 2 //����

typedef unsigned char BYTE;

extern HINSTANCE hInst;
extern char CurDir[MAX_PATH-100];//��ǰӦ�ó����Ŀ¼

VOID ErrorBox(LPTSTR ErrorInfo); //������ʾ��
VOID MsgBox(LPTSTR msg); //��Ϣ��ʾ��

#endif