//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XUser.h  CXUser

#pragma once

#include "ExBaseList.h"

class CXUserLogin : public CExBaseList
{
public:
	CXUserLogin();
	virtual ~CXUserLogin();


	CString  m_strPSW;
	long    m_nSaveLogin;

	static CString g_strAdminID;
	static CString g_strAdminPSW;

	static void InitAdminUserAndPSW();

//重载函数
public:
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	void OpenIniFile();
	void SaveIniFile();

//私有成员变量
private:
	CString GetIniFile();

//私有成员变量访问方法
public:
	CString GetName();
	void SetName(const CString &strName);

	CString GetID();
	void SetID(const CString &strID);
	
	CString GetPSW();
	void SetPSW(const CString &strPsw);

	BOOL IsAdmin()	{	return g_strAdminID == m_strID;	}
};

