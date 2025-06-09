//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XUser.cpp  CXUser


#include "stdafx.h"
#include "XUserLogin.h"

#include "..\IniFileMngr\IniFile.h"
#include "..\Encrypt\XDes2.h"

CString CXUserLogin::g_strAdminID;
CString CXUserLogin::g_strAdminPSW;

const CString  USER_LOGIN_KEY_LOGIN =  _T("login");
const CString  USER_LOGIN_KEY_SAVE_LOGIN  = _T("save-login");
const CString  USER_LOGIN_KEY_USER =  _T("user");
const CString  USER_LOGIN_KEY_PSW =  _T("psw");

void CXUserLogin::InitAdminUserAndPSW()
{
	CString strTemp;
	strTemp  = _T("a");
	strTemp += _T("d");
	strTemp += _T("m");
	strTemp += _T("i");
	strTemp += _T("n");
	g_strAdminID = xdes_Encrypt(strTemp);

	strTemp  = _T("p");
	strTemp += _T("o");
	strTemp += _T("w");
	strTemp += _T("e");
	strTemp += _T("r");
	strTemp += _T("s");
	strTemp += _T("k");
	strTemp += _T("y");
	g_strAdminPSW = xdes_Encrypt(strTemp);
}

CXUserLogin::CXUserLogin()
{
	m_nSaveLogin = 0;
	//初始化属性

	//初始化成员变量
}

CXUserLogin::~CXUserLogin()
{
}

void CXUserLogin::OpenIniFile()
{
	CString strFile;
	strFile = GetIniFile();

	CIniFile oIniFile;
	
	if (!oIniFile.SetIniFile(strFile))
	{
		return;
	}

	CString strText = oIniFile.GetKeyValue(USER_LOGIN_KEY_LOGIN, USER_LOGIN_KEY_SAVE_LOGIN);

	if (strText.GetLength() > 0)
	{
		m_nSaveLogin = CString_To_long(strText);
	}

	m_strName = oIniFile.GetKeyValue(USER_LOGIN_KEY_LOGIN, USER_LOGIN_KEY_USER);
	m_strPSW = oIniFile.GetKeyValue(USER_LOGIN_KEY_LOGIN, USER_LOGIN_KEY_PSW);
}

void CXUserLogin::SaveIniFile()
{
	CString strText;
	strText.Format(_T("%d"), m_nSaveLogin);

	CIniFile oIniFile;
	oIniFile.InsertKey(USER_LOGIN_KEY_LOGIN, USER_LOGIN_KEY_SAVE_LOGIN, strText);
	oIniFile.InsertKey(USER_LOGIN_KEY_LOGIN, USER_LOGIN_KEY_USER, m_strName);
	oIniFile.InsertKey(USER_LOGIN_KEY_LOGIN, USER_LOGIN_KEY_PSW, m_strPSW);

	CString strFile;
	strFile = GetIniFile();
	oIniFile.SaveAs(strFile);
}

CString CXUserLogin::GetIniFile()
{
	CString strFile;

	strFile = _P_GetConfigPath();
	strFile += _T("Login.ini");

	return strFile;
}

long CXUserLogin::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strPSW);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strPSW);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strPSW);
	}
	return 0;
}

CString CXUserLogin::GetName()
{
// 	CXAes oXAes;
// 	return oXAes.InvCipher(m_strName);
	return xdes_Decrypt(m_strName);
}

void CXUserLogin::SetName(const CString &strName)
{
	//CXAes oXAes;
	//m_strName = oXAes.Cipher(strName);
	m_strName = xdes_Encrypt(strName);
}

CString CXUserLogin::GetID()
{
// 	CXAes oXAes;
// 	return oXAes.InvCipher(m_strID);
	return xdes_Decrypt(m_strID);
}

void CXUserLogin::SetID(const CString &strID)
{
// 	CXAes oXAes;
// 	m_strID = oXAes.Cipher(strID);
	m_strID = xdes_Encrypt(strID);
}

CString CXUserLogin::GetPSW()
{
// 	CXAes oXAes;
// 	return oXAes.InvCipher(m_strPSW);
	return xdes_Decrypt(m_strPSW);
}

void CXUserLogin::SetPSW(const CString &strPsw)
{
// 	CXAes oXAes;
// 	m_strPSW = oXAes.Cipher(strPsw);
	m_strPSW = xdes_Encrypt(strPsw);
}

