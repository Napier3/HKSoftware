//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
public:
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	void OpenIniFile();
	void SaveIniFile();

//˽�г�Ա����
private:
	CString GetIniFile();

//˽�г�Ա�������ʷ���
public:
	CString GetName();
	void SetName(const CString &strName);

	CString GetID();
	void SetID(const CString &strID);
	
	CString GetPSW();
	void SetPSW(const CString &strPsw);

	BOOL IsAdmin()	{	return g_strAdminID == m_strID;	}
};

