// EncryptTool.h: interface for the CEncryptTool class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(_EncryptTool_H__)
#define _EncryptTool_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "../API/HexTransApi.h"
#include "SystemCode.h"
#include "EncryptBase.h"

#include "../DialogBase/DynDialogEx.h"
#include "../XLanguage/XLanguageResource.h"
#define EncryptTextBuffer_Len  4096
#define EncryptElemBuffer_Len  512

#define ENCRYPT_INDEX_COMPANY         0
#define ENCRYPT_INDEX_USER            1
#define ENCRYPT_INDEX_MAXUSECOUNT     2
#define ENCRYPT_INDEX_CURUSECOUNT     3
#define ENCRYPT_INDEX_SN              4
#define ENCRYPT_INDEX_DEVCODE         5
#define ENCRYPT_INDEX_AUTOTEST        6
#define ENCRYPT_INDEX_DEV             7
#define ENCRYPT_INDEX_MAX             8

static long ENCRYPT_LEN[ENCRYPT_INDEX_MAX] = {128, 128, 8, 8, 128, 512, 8, 8};

class CEncryptTool : public CEncryptBase
{
public:
	CEncryptTool();
	virtual ~CEncryptTool();

//属性定义
private:
	char m_pEncryptTextBuffer[EncryptTextBuffer_Len];
	char m_pBuffer[EncryptElemBuffer_Len];

protected:
	BOOL m_bRegistered;

protected:
	long GetBeginPos(long nID);
	long GetLen(long nID);
	long GetBuffer(long nID, char *pBuffer);

	void InitEncrypt(long nID, CString &strText);
	void InitEncrypt(long nID, long &nValue);
	BOOL ValidateBuffer(char *pBuffer, long nLen);
	void InitEncrypt(long nID, DWORD &dwValue);

public:
	BOOL    InitEncrypt();

public:
	virtual BOOL    IsEncrypt();//		{	return m_bRegistered;	}
	virtual void    OpenLocalEncryptFile();

	BOOL IsUseRegisterFile();
	BOOL IsShowSysName()	{	return m_nShowSysName;	}
	BOOL IsShowOwnship()	{	return m_nShowOwnship;	}
	BOOL IsShowDev()	{	return m_nShowDev;	}
	BOOL IsShowUserCop()	{	return m_nShowUserCop;	}
	BOOL IsShowUser()	{	return m_nShowUser;	}

private:
	long m_nUseRegisterFile;
	long m_nShowSysName;
	long m_nShowOwnship;
	long m_nShowDev;
	long m_nShowUserCop;
	long m_nShowUser;
	

	BOOL OpenEncryptConfigFile(const long nXmlRWType = _PUGI_XML_TYPE_);
};

extern CEncryptTool *g_pEncryptTool;
void Encrypt_RegisterTool(CEncryptTool *pTool);

inline void Encrypt_RegisterFileTool()
{
	Encrypt_RegisterTool(new CEncryptTool());
}

inline void Encrypt_ReloadEncryptFile()
{
	if (g_pEncryptTool != NULL)
	{
		g_pEncryptTool->OpenLocalEncryptFile();
	}
}

inline BOOL Encrypt_IsEncrypt()
{
	if (g_pEncryptTool == NULL)
	{
		return FALSE;
	}

	return g_pEncryptTool->IsEncrypt();
}


inline BOOL Encrypt_CanUseAutoTest()
{
	if (!Encrypt_IsEncrypt())
	{
		return FALSE;
	}

	return g_pEncryptTool->CanUseAutoTest();
}

inline BOOL Encrypt_CanUseDevStudio()
{
	if (!Encrypt_IsEncrypt())
	{
		return FALSE;
	}

	return g_pEncryptTool->CanUseDevStudio();
}

#define String_Encrypt_None  _T("没有授权")/*g_sLangTxt_NotAuthorized2*/

inline CString Encrypt_GetSysName()
{
	if (g_pEncryptTool == NULL)
	{
		return String_Encrypt_None;
	}

	return g_pEncryptTool->GetSysName();
}

inline CString Encrypt_GetCompany()
{
	if (g_pEncryptTool == NULL)
	{
		return String_Encrypt_None;
	}

	return g_pEncryptTool->GetOwnership();
}

inline CString Encrypt_GetUser()
{
	if (g_pEncryptTool == NULL)
	{
		return String_Encrypt_None;
	}

	return g_pEncryptTool->GetUser();
}


inline CString Encrypt_GetUserCop()
{
	if (g_pEncryptTool == NULL)
	{
		return String_Encrypt_None;
	}

	return g_pEncryptTool->GetUserCop();
}

inline CString Encrypt_GetUserCode()
{
	if (g_pEncryptTool == NULL)
	{
		return String_Encrypt_None;
	}

	return g_pEncryptTool->GetUserCode();
}

CString Encrypt_GetUserMsg();
// {
// 	if (!Encrypt_IsEncrypt())
// 	{
// 		return g_sLangTxt_NotAuthorized/*_T("你使用的系统没有授权")*/;
// 	}
// 
// 	CString strMsg;
// 	
// 	/*_T("版权所有：%s      授权用户单位：%s     授权用户名：%s")*/
// 	strMsg.Format(_T("%s %s      %s %s     %s %s")
// 		, g_sLangTxt_RightsReserved
// 		, g_sLangTxt_UserUnits
// 		, g_sLangTxt_User2
// 		, Encrypt_GetCompany(), Encrypt_GetUserCop(), Encrypt_GetUser());
// 
// 	return strMsg;
// }

void Encrypt_LogUserMsg();
BOOL Encrypt_IsUseRegisterFile();

//2021-7-30  一下几个函数必须先判断IsUseRegisterFile
inline BOOL Encrypt_IsShowSysName()	{	return g_pEncryptTool->IsShowSysName();	}
inline BOOL Encrypt_IsShowOwnship()	{	return g_pEncryptTool->IsShowOwnship();	}
inline BOOL Encrypt_IsShowDev()		{	return g_pEncryptTool->IsShowDev();	}
inline BOOL Encrypt_IsShowUserCop()	{	return g_pEncryptTool->IsShowUserCop();	}
inline BOOL Encrypt_IsShowUser()		{	return g_pEncryptTool->IsShowUser();	}

#endif // !defined(_EncryptTool_H__)
