#pragma once
#include "CBlueToothBase.h"
#include "../../Module/XfileMngrBase/XFileMngr.h"
#include "../../Module/System/TickCount32.h"

#define WM_SEND_FILE_LIST (WM_USER + 1088)
#define WM_CONTINRUE_SEND (WM_USER+3212)
#define WM_END_SEND       (WM_USER+3213)

class CBlueToothClient :public CBlueToothBase
{
public:
	CBlueToothClient(void);
	~CBlueToothClient(void);

	CWnd* m_pParentWnd;
	void SetParentWnd(CWnd *pParent)	{	m_pParentWnd = pParent;	}

	CTickCount32 m_oTickCount32;
	BOOL m_bJudgeOverTime;

	CString m_strFileNameList;
	CString m_strDownLoadFileName;
	CFile m_oLoadFile;

	CWinThread *m_pThread;

	ULONG	RunClientMode(_In_ BTH_ADDR RemoteAddr, _In_ int iMaxCxnCycles);

	static UINT	StartBlueTooth(LPVOID lpParameter);

	virtual void DealDataBeforeSend()	{	}
	virtual void HandleClientCommand(BYTE *strCmmd);

	void StartBlueTooth_Thread();
};
