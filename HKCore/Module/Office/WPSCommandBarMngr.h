// WPSCommandBarMngr.h: interface for the CWPSCommandBarMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_WPSCOMMANDBARMNGR_H__)
#define _WPSCOMMANDBARMNGR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\BaseClass\ExBaseList.h"
//#include "..\..\Module\Office\KSO.h"
#include "KSO.h"
#include "WordCommandBar.h"

class CWPSCommandBarMngr : public CWordCommandBarMngrBase  
{
public:
	CWPSCommandBarMngr();
	virtual ~CWPSCommandBarMngr();

public:
	void InitWordCommandBarMngr(KSO::_CommandBars cmdbars, BOOL bHide=TRUE);
	void RestoreWordCommandBars(KSO::_CommandBars cmdbars);
	BOOL LoadWordCommandBarMngr(KSO::_CommandBars cmdbars);
};
#endif // !defined(_WORDCOMMANDBARMNGR_H__)
