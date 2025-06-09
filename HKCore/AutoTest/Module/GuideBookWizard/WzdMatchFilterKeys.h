//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//WzdMatchFilterKeys.h  CWzdMatchFilterKeys

#pragma once

#include "..\..\..\Module\FilterText\FilterTextMngr.h"


class CWzdMatchFilterKeys : public CFilterTextMngr
{
protected:
	CWzdMatchFilterKeys();
	virtual ~CWzdMatchFilterKeys();

	static CWzdMatchFilterKeys *g_pFilterTextMngr;
	static long m_nFilterTextMngrRef;

public:
	static CWzdMatchFilterKeys* Create();
	static CWzdMatchFilterKeys* GetWzdMatchFilterKeys();
	static void Release();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

