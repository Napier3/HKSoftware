//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//WndChildCtrlsAdjustGlobal.h

#pragma once

#include "ExBaseList.h"

#define WCCACLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define WCCACLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define WCCACLASSID_CWNDADJCELL       (WCCACLASSID_EXLISTCLASS + 0X00000000)
#define WCCACLASSID_CWNDADJCELLLIST       (WCCACLASSID_EXLISTCLASS + 0X00000001)
#define WCCACLASSID_CWNDADJROW       (WCCACLASSID_EXLISTCLASS + 0X00000002)
#define WCCACLASSID_CWNDADJCOL       (WCCACLASSID_EXLISTCLASS + 0X00000003)
#define WCCACLASSID_CWNDADJTOOL       (WCCACLASSID_EXLISTCLASS + 0X00000004)

class CWndChildCtrlsAdjustXmlRWKeys : public CXmlRWKeys
{
protected:
	CWndChildCtrlsAdjustXmlRWKeys();
	virtual ~CWndChildCtrlsAdjustXmlRWKeys();
	static long g_nWCCARef;

public:
	static CWndChildCtrlsAdjustXmlRWKeys* g_pXmlKeys;
	static CWndChildCtrlsAdjustXmlRWKeys* Create();
	static void Release();

public:

public:
};



class CWndChildCtrlsAdjustConstGlobal
{
private:
	CWndChildCtrlsAdjustConstGlobal();
	virtual ~CWndChildCtrlsAdjustConstGlobal();

public:
	static CWndChildCtrlsAdjustConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CWndChildCtrlsAdjustConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

};
