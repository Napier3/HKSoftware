#pragma once 

#include "../../../Module/BaseClass/ExBaseList.h"

#define SCRIPT_FUN_PKG				0X00001
#define SCRIPT_FUN_PROCEDURE		0X00002
#define SCRIPT_FUN_ALL		0X00003

class CPpScriptMethodInfo: public CExBaseObject
{
public:
	CPpScriptMethodInfo(DWORD dwFlag=SCRIPT_FUN_ALL)
	{
		m_dwFlag = dwFlag;
	}

	virtual ~CPpScriptMethodInfo()	{}

	//接口
public:
	CString GetMethodString();

	//属性
public:
	//函数名
	CString m_strMethodName;
	//返回值类型
	CString m_strReturnType;
	//参数列表
	CString m_strParaList;
	//函数说明
	CString m_strMethodInfo;

	DWORD m_dwFlag;
};

class CPpScriptMethodsInfo : public CExBaseList
{
private:
	CPpScriptMethodsInfo();
	virtual ~CPpScriptMethodsInfo()	{}

	static long g_nRef;

public:
	static CPpScriptMethodsInfo* g_pPpScriptMethods;
	static CPpScriptMethodsInfo* Create();
	static void Release();
};