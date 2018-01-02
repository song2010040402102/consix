#include "CThread.h"

CThread::CThread()
{
	hThread=NULL;
}

CThread::~CThread()
{

}

/***�����߳�***/
HANDLE CThread::StartThread(
				   LPTHREAD_START_ROUTINE lpStartAddress,
				   LPVOID lpParameter,
				   LPSECURITY_ATTRIBUTES lpThreadAttributes,
				   DWORD dwStackSize,
				   DWORD dwCreationFlags,
				   LPDWORD lpThreadId
				   )
{
	hThread=CreateThread(
		lpThreadAttributes,
		dwStackSize,
		lpStartAddress,
		lpParameter,
		dwCreationFlags,
		lpThreadId
		);
	if(hThread==NULL)
	{
		MsgBox("CreateThread failed");		
	}
	return hThread;
}

/***��ֹ�߳�***/
BOOL CThread::StopThread()
{
	if(!TerminateThread(hThread,0))
	{
		ErrorBox("TerminateThread failed");
		return FALSE;
	}
	return TRUE;
}