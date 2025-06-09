// WordCommandBarMngr.h: interface for the CWordCommandBarMngr class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_WORDCOMMANDBARMNGR_H__)
#define _WORDCOMMANDBARMNGR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\BaseClass\ExBaseList.h"
//#include "..\..\Module\Office\mso9.h"
#include "mso9.h"
#include "WordCommandBar.h"

class CWordCommandBarMngr : public CWordCommandBarMngrBase  
{
public:
	CWordCommandBarMngr();
	virtual ~CWordCommandBarMngr();

public:
	void InitWordCommandBarMngr(MSO9::_CommandBars cmdbars, BOOL bHide=TRUE);
	void RestoreWordCommandBars(MSO9::_CommandBars cmdbars);
	BOOL LoadWordCommandBarMngr(MSO9::_CommandBars cmdbars);
};

#endif // !defined(_WORDCOMMANDBARMNGR_H__)
