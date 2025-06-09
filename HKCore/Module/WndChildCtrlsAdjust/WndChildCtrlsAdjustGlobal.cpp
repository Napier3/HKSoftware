//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//WndChildCtrlsAdjustGlobal.cpp

#include "stdafx.h"
#include "WndChildCtrlsAdjustGlobal.h"

//////////////////////////////////////////////////////////////////////////
//CWndChildCtrlsAdjustXmlRWKeys

CWndChildCtrlsAdjustXmlRWKeys* CWndChildCtrlsAdjustXmlRWKeys::g_pXmlKeys = NULL;
long CWndChildCtrlsAdjustXmlRWKeys::g_nWCCARef = 0;


CWndChildCtrlsAdjustXmlRWKeys::CWndChildCtrlsAdjustXmlRWKeys()
{
}

CWndChildCtrlsAdjustXmlRWKeys::~CWndChildCtrlsAdjustXmlRWKeys()
{
}

CWndChildCtrlsAdjustXmlRWKeys* CWndChildCtrlsAdjustXmlRWKeys::Create()
{
	g_nWCCARef++;

	if (g_nWCCARef == 1)
	{
		g_pXmlKeys = new CWndChildCtrlsAdjustXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CWndChildCtrlsAdjustXmlRWKeys::Release()
{
	g_nWCCARef--;

	if (g_nWCCARef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CWndChildCtrlsAdjustConstGlobal

long CWndChildCtrlsAdjustConstGlobal::g_nGlobalRef = 0;
CWndChildCtrlsAdjustConstGlobal* CWndChildCtrlsAdjustConstGlobal::g_pGlobal = NULL;


CWndChildCtrlsAdjustConstGlobal::CWndChildCtrlsAdjustConstGlobal()
{

//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CWndChildCtrlsAdjustConstGlobal::~CWndChildCtrlsAdjustConstGlobal()
{
}

CWndChildCtrlsAdjustConstGlobal* CWndChildCtrlsAdjustConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CWndChildCtrlsAdjustConstGlobal();
	}

	return g_pGlobal;
}

void CWndChildCtrlsAdjustConstGlobal::Release()
{
	g_nGlobalRef--;

	if (g_nGlobalRef == 0)
	{
		delete g_pGlobal;
		g_pGlobal = NULL;
	}
}

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()
//	m_oFuncParaDataTypes.AddNew(g_pstrVariableType_CString, g_pstrVariableType_CString);

//定义全局常量，例如  static CString g_pstrVariableType_CString;
