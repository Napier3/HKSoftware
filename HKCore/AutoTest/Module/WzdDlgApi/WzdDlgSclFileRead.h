#if !defined(_CWzdDlgSclFileRead_h__)
#define _CWzdDlgSclFileRead_h__
#include "SCLApi/WzdSclFileRead.h"
#include "WzdDlgSendState.h"

class CWzdDlgSclFileRead : public CSclFileRead
{
public:
	CWzdDlgSclFileRead();
	virtual ~CWzdDlgSclFileRead();

public:
	BOOL ReadSclFile(const CString &strFile, CWnd *pOwnerWnd,  CSclStation *pSclStation);
	static UINT ReadSCLThread(LPVOID pParam);

	CWzdDlgSendState m_DlgProgress;
	static UINT ReadSCLNewThread(LPVOID pParam);
};

extern ST_BOOLEAN g_bUseSmemEnable;

#endif
