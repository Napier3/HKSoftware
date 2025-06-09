#pragma once

#include "../../../Module/BaseClass/ExBaseList.h"

class CXPkgFullRcvJdgInterface : public CExBaseObject
{
public:
	CXPkgFullRcvJdgInterface(){};
	virtual ~CXPkgFullRcvJdgInterface(){};
	
	virtual long XPkgFullRcvJdg(BYTE *pBuffer, long nBufLen, long &nPkgLen) = 0;
};

class CXPkgFullRcvJdg_101 : public CXPkgFullRcvJdgInterface
{
public:
	CXPkgFullRcvJdg_101();
	virtual ~CXPkgFullRcvJdg_101();
	
	virtual long XPkgFullRcvJdg(BYTE *pBuffer, long nBufLen, long &nPkgLen);
};

class CXPkgFullRcvJdg_103 : public CXPkgFullRcvJdgInterface
{
public:
	CXPkgFullRcvJdg_103();
	virtual ~CXPkgFullRcvJdg_103();

	virtual long XPkgFullRcvJdg(BYTE *pBuffer, long nBufLen, long &nPkgLen);
};


class CXPkgFullRcvJdg_104 : public CXPkgFullRcvJdgInterface
{
public:
	CXPkgFullRcvJdg_104();
	virtual ~CXPkgFullRcvJdg_104();

	virtual long XPkgFullRcvJdg(BYTE *pBuffer, long nBufLen, long &nPkgLen);
};


class CXPkgFullRcvJdgTool : public CExBaseList
{
private:
	CXPkgFullRcvJdgTool(void);
	virtual ~CXPkgFullRcvJdgTool(void);

public:
	static CXPkgFullRcvJdgTool *g_pXPkgFullRcvJdgTool;
	static long g_nXPkgFullRcvJdgToolRef;
	static CXPkgFullRcvJdgTool* Create();
	static void Release();

	static CXPkgFullRcvJdgInterface* CreateXPkgFullRcvJdg(const CString &strID);
	
};
