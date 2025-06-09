//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UserDBGlobal.cpp

#include "stdafx.h"
#include "UserDBGlobal.h"

#include "XUser.h"
#include "XUserMngr.h"
#include "..\XLanguage\XLanguageResource.h"
//////////////////////////////////////////////////////////////////////////
//CUserDBXmlRWKeys

CUserDBXmlRWKeys* CUserDBXmlRWKeys::g_pXmlKeys = NULL;
long CUserDBXmlRWKeys::g_nUSRDRef = 0;


CUserDBXmlRWKeys::CUserDBXmlRWKeys()
{
	m_strCXUserMngrKey = L"user-mngr";
	m_strCXUserKey = L"user";
	m_strPSWKey = L"psw";
}

CUserDBXmlRWKeys::~CUserDBXmlRWKeys()
{
}

CUserDBXmlRWKeys* CUserDBXmlRWKeys::Create()
{
	g_nUSRDRef++;

	if (g_nUSRDRef == 1)
	{
		g_pXmlKeys = new CUserDBXmlRWKeys();
	}

	return g_pXmlKeys;
}

void CUserDBXmlRWKeys::Release()
{
	g_nUSRDRef--;

	if (g_nUSRDRef == 0)
	{
		delete g_pXmlKeys;
		g_pXmlKeys = NULL;
	}
}


//////////////////////////////////////////////////////////////////////////
//CUserDBConstGlobal

long CUserDBConstGlobal::g_nGlobalRef = 0;
CUserDBConstGlobal* CUserDBConstGlobal::g_pGlobal = NULL;


CUserDBConstGlobal::CUserDBConstGlobal()
{
	m_pUserMngr = NULL;
	m_pCurrUser = NULL;
//定义全局常量管理对象初始化函数，例如  InitVariableDataTypes()

}

CUserDBConstGlobal::~CUserDBConstGlobal()
{
	if (m_pUserMngr != NULL)
	{
		delete m_pUserMngr;
		m_pUserMngr = NULL;
	}
}

CUserDBConstGlobal* CUserDBConstGlobal::Create()
{
	g_nGlobalRef++;

	if (g_nGlobalRef == 1)
	{
		g_pGlobal = new CUserDBConstGlobal();
	}

	return g_pGlobal;
}

void CUserDBConstGlobal::Release()
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

CXUser* CUserDBConstGlobal::GetCurrUser()
{
	if (g_pGlobal == NULL)
	{
		return NULL;
	}

	return g_pGlobal->m_pCurrUser;
}

CXUser* CUserDBConstGlobal::Login(const CString &strUser, const CString &strPSW)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return NULL;
	}

	return g_pGlobal->In_Login(strUser, strPSW);
}

void CUserDBConstGlobal::AddUser(CXUser *pUser)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return ;
	}

	g_pGlobal->In_AddUser(pUser);
}

void CUserDBConstGlobal::DeleteUser(CXUser *pUser)
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return ;
	}

	g_pGlobal->In_DeleteUser(pUser);
}

CString CUserDBConstGlobal::GetLoginError()
{
	if (g_pGlobal->m_pUserMngr->m_dwErrorMsg == XUSER_ERRORID_NOUSER)
	{
		return g_sLangTxt_UserUnExist/*_T("用户名不存在")*/;
	}

	if (g_pGlobal->m_pUserMngr->m_dwErrorMsg == XUSER_ERRORID_PSWERROR)
	{
		return g_sLangTxt_PasswordIncorrect/*_T("密码不正确")*/;
	}

	return g_sLangTxt_LoginError/*_T("登录错误")*/;
}

CXUserMngr* CUserDBConstGlobal::GetUserMngr()
{
	ASSERT (g_pGlobal != NULL);

	if (g_pGlobal == NULL)
	{
		return NULL;
	}

	return g_pGlobal->m_pUserMngr;
}

CString CUserDBConstGlobal::GetUserName()
{
	CXUser *pUser = GetCurrUser();

	if (pUser == NULL)
	{
		return _T("");
	}
	else
	{
		return pUser->m_strName;
	}
}

CString CUserDBConstGlobal::GetUserNameText()
{
	CXUser *pUser = GetCurrUser();

	if (pUser == NULL)
	{
		return _T("");
	}
	else
	{
		return pUser->GetName();
	}
}

CXUser* CUserDBConstGlobal::In_Login(const CString &strUser, const CString &strPSW)
{
	if (m_pUserMngr == NULL)
	{
		m_pUserMngr = new CXUserMngr();
		m_pUserMngr->OpenUserDB();
	}

	m_pCurrUser = m_pUserMngr->Login(strUser, strPSW);

	return m_pCurrUser;
}

void CUserDBConstGlobal::In_AddUser(CXUser *pUser)
{
	if (m_pUserMngr == NULL)
	{
		return;
	}

	m_pUserMngr->AddUser(pUser);
}

void CUserDBConstGlobal::In_DeleteUser(CXUser *pUser)
{

}

