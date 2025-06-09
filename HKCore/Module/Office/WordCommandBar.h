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
 *	Word�������������ϵͳ�˳�ʱ���ָ�������
 *  ��Ϊ���Կͻ�����Ҫ��������ȫ������
 *  ���ϵͳ�����쳣����ֹ������Ҫ�ָ�״̬
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
