//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UserDBGlobal.h

#pragma once

#include "../Encrypt/XDes2.h"
#include "../BaseClass/ExBaseList.h"

#define USRDCLASSID_BASECLASS       (CLASSID_BASECLASS + 0X00010000)
#define USRDCLASSID_EXLISTCLASS       (CLASSID_EXLISTCLASS + 0X00010000)

#define USRDCLASSID_CXUSER       (USRDCLASSID_EXLISTCLASS + 0X00000000)
#define USRDCLASSID_CXUSERMNGR       (USRDCLASSID_EXLISTCLASS + 0X00000001)

class CUserDBXmlRWKeys : public CXmlRWKeys
{
protected:
	CUserDBXmlRWKeys();
	virtual ~CUserDBXmlRWKeys();
	static long g_nUSRDRef;

public:
	static CUserDBXmlRWKeys* g_pXmlKeys;
	static CUserDBXmlRWKeys* Create();
	static void Release();

public:
	BSTR m_strCXUserMngrKey; //user-mngr
	BSTR m_strCXUserKey; //user
	BSTR m_strPSWKey; //psw

public:
	static BSTR CXUserMngrKey()  {   return g_pXmlKeys->m_strCXUserMngrKey;  }
	static BSTR CXUserKey()  {   return g_pXmlKeys->m_strCXUserKey;  }
	static BSTR PSWKey()  {   return g_pXmlKeys->m_strPSWKey;  }
};

class CXUser;
class CXUserMngr;

class CUserDBConstGlobal
{
private:
	CUserDBConstGlobal();
	virtual ~CUserDBConstGlobal();

	CXUserMngr *m_pUserMngr;
	CXUser *m_pCurrUser;

public:
	static CUserDBConstGlobal* Create();
	static void Release();

private:
	static long g_nGlobalRef;
	static CUserDBConstGlobal *g_pGlobal;

private:
//定义全局常量管理对象，例如  CExBaseList m_oVariableDataTypes

//定义全局常量管理对象初始化函数，例如  void InitVariableDataTypes()

public:
//定义全局常量管理对象访问函数，例如  static CExBaseList* GetVariableDataTypes()	{	return &(g_pGlobal->m_oVariableDataTypes);	}

//定义全局常量，例如  static CString g_pstrVariableType_CString;

	static CXUser* GetCurrUser();
	static CXUser* Login(const CString &strUser, const CString &strPSW);
	static void AddUser(CXUser *pUser);
	static void DeleteUser(CXUser *pUser);
	static CString GetLoginError();
	static CXUserMngr* GetUserMngr();
	static CString GetUserName();
	static CString GetUserNameText();

private:
	CXUser* In_Login(const CString &strUser, const CString &strPSW);
	void In_AddUser(CXUser *pUser);
	void In_DeleteUser(CXUser *pUser);

};

#ifndef _PSX_IDE_QT_     //yyj
#include "..\DialogBase\DynDialogEx.h"
#endif

#define XUSRID_COMBO_USERNAME              0X0002000
#define XUSRID_EDIT_USERPSW                0X0002001
#define XUSRID_STC_USERNAME                0X0002002
#define XUSRID_STC_USERPSW                 0X0002003
