// WordCommandBar.h: interface for the CWordCommandBar class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_WORDCOMMANDBAR_H__)
#define _WORDCOMMANDBAR_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\BaseClass\ExBaseList.h"
//#include "mso9.h"

/*
 *	Word命令工具栏管理，在系统退出时，恢复工具栏
 *  因为测试客户端需要将工具栏全部隐藏
 *  如果系统出现异常而终止，则需要恢复状态
 */

class CWordCommandBar : public CExBaseObject  
{
public:
	long	m_bEnable;
	long	m_bVisible;
	long    m_nIndex;
	
	CWordCommandBar();
	virtual ~CWordCommandBar();

	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
};

class CWordCommandBarMngrBase : public CExBaseList  
{
public:
	CWordCommandBarMngrBase();
	virtual ~CWordCommandBarMngrBase();

	void Init();
	void EndIt();

	long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	BOOL SaveWordCommandBarMngr();
	CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

public:
	CString	m_strCmdBarsCfgFile;
};

#endif // !defined(_WORDCOMMANDBARMNGR_H__)
