#ifndef CTHREAD_H_CONSIX
#define CTHREAD_H_CONSIX

#include "window.h"

//�����ҷ�װ���̣߳�ֱ���ü���
class CThread
{
public:
	HANDLE hThread;

	CThread();
	~CThread();
	HANDLE StartThread(LPTHREAD_START_ROUTINE lpStartAddress,
				   LPVOID lpParameter,
				   LPSECURITY_ATTRIBUTES lpThreadAttributes=NULL,
				   DWORD dwStackSize=0,
				   DWORD dwCreationFlags=0,
				   LPDWORD lpThreadId=0
				   );
	BOOL StopThread();
};
#endif