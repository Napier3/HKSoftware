#pragma once
#include "CBlueToothBase.h"
#include "../../Module/XfileMngrBase/XFileMngr.h"
#include "../../Module/System/TickCount32.h"

#define WM_FILE_SEND_PROG    (WM_USER + 1037)
#define WM_THREAD_CLOSE_SEVER  (WM_USER + 1038)
#define WM_CONTINRUE_SEND	 (WM_USER + 1039)
#define WM_END_SEND			 (WM_USER + 1040)

class CBlueToothService :public CBlueToothBase
{
public:
	CBlueToothService(void);
	~CBlueToothService(void);

	CString     m_strSendFile;
	
	CWnd* m_pParentWnd;
	CWinThread *m_pThread;

	ULONG	RunServerMode(_In_ int iMaxCxnCycles);

	static UINT	StartBlueTooth(LPVOID lpParameter);

	void    JointFileName(CExBaseObject* pObj,CString &strFileName,int nFileType);
	void    ReSetFileLoadFlag(CExBaseObject* pObj,BOOL bflag);

	void	SetParentWnd(CWnd *pParent)	{	m_pParentWnd = pParent;	}
	
	void StartBlueTooth_Thread();
};
