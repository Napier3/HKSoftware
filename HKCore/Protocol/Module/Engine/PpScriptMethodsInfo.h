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

	//�ӿ�
public:
	CString GetMethodString();

	//����
public:
	//������
	CString m_strMethodName;
	//����ֵ����
	CString m_strReturnType;
	//�����б�
	CString m_strParaList;
	//����˵��
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