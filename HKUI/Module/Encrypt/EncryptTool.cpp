// EncryptTool.cpp: implementation of the CEncryptTool class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "EncryptTool.h"
#include "..\API\GloblaDrawFunctions.h"


CEncryptTool *g_pEncryptTool = NULL;

class CEncrypt_Register
{
public:
	void Free()
	{
		if (g_pEncryptTool != NULL)
		{
			delete g_pEncryptTool;
			g_pEncryptTool = NULL;
		}
	}

public:
	CEncrypt_Register()
	{
		g_pEncryptTool = NULL;
	}

	virtual ~CEncrypt_Register()
	{
		Free();
	}

}g_oEncrypt_Register;


void Encrypt_RegisterTool(CEncryptTool *pTool)
{
	g_oEncrypt_Register.Free();
	g_pEncryptTool = pTool;
	g_pEncryptTool->OpenLocalEncryptFile();
}


//////////////////////////////////////////////////////////////////////////
//

//////////////////////////////////////////////////////////////////////    
// Construction/Destruction    
//////////////////////////////////////////////////////////////////////    
// 
// CEncryptToolDlg::CEncryptToolDlg(CWnd* pParent /*= NULL*/)   
// : CDynDialogEx(pParent)   
// {   
// 	m_bAddSystemButtons = FALSE;   
// }   
// 
// CEncryptToolDlg::~CEncryptToolDlg()   
// {   
// 
// }   
// 
// BEGIN_MESSAGE_MAP(CEncryptToolDlg, CDynDialogEx)   
// 	//{{AFX_MSG_MAP(CXMatchDataObjEditDlg)    
// 	//}}AFX_MSG_MAP   
// END_MESSAGE_MAP()   
// 
// 
// BOOL CEncryptToolDlg::OnInitDialog()   
// {   
// 	BOOL bRet = CDynDialogEx::OnInitDialog();   
// 
// 	//SetWindowPos(NULL, 0, 0, 190, 190, SWP_SHOWWINDOW);
// 	CRect rc;
// 	GetClientRect(&rc);
// 
// 	CreateEdit(m_editValue, CRect(12, 12, 195, 34), 1609, this);
// 	CreateButton(m_btnOK, _T("确定"), CRect(212, 12, 284, 34), IDOK, this);
// 	CreateButton(m_btnCancel, _T("取消"), CRect(295, 12, 368, 34), IDOK, this);
// 	m_editValue.SetWindowText(m_strValue);
// 	SetWindowText(m_strDataName);
// 
// 	m_editValue.SetFont(g_pGlobalFont14);
// 	m_btnOK.SetFont(g_pGlobalFont14);
// 	m_btnCancel.SetFont(g_pGlobalFont14);
// 
// 	return bRet;   
// }   
// 
// int CEncryptToolDlg::DoModal()   
// {   
// 	CRect rect(0,0,252,28);   
// 	SetDlgRect(rect);
// 	//	AddDlgControl(_T("LISTBOX"), _T("ListboxText"), STYLE_LISTBOX, EXSTYLE_LISTBOX, &rect, &m_lstBox, IDC_LIST_DATAS);   
// 	int iRet = CDynDialogEx::DoModal();   
// 
// 	return iRet;   
// }   
// 
// void CEncryptToolDlg::OnCancel()
// {
// 	CDialog::OnCancel();
// }
// 
// void CEncryptToolDlg::OnOK()
// {
// 	m_editValue.GetWindowText(m_strValue);
// 
// 	CDialog::OnOK();
// }


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


/*
文本的格式如下
${{@\nBinaryData\0\0...\n@\nBinaryText\0...@......}}$ 
*/



CEncryptTool::CEncryptTool()
{
	m_nUseRegisterFile = -1;
	m_nShowSysName = 0;
	m_nShowOwnship = 0;
	m_nShowDev = 0;
	m_nShowUserCop = 0;
	m_nShowUser = 0;

	m_bRegistered = FALSE;
	ZeroMemory(m_pEncryptTextBuffer, EncryptTextBuffer_Len);
	strcpy(m_pEncryptTextBuffer, "${{123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF123456789ABCEDF>>#");
}

CEncryptTool::~CEncryptTool()
{
	
}

//	m_strUseRegisterFileKey   = L"use-register-file";
BOOL CEncryptTool::OpenEncryptConfigFile(const long nXmlRWType)
{
	CString strFile;
	strFile = _P_GetCommonBinPath();
	strFile += _T("EncryptConfig.xml");

	CXmlRWDocBase *pRWDoc = xml_CreateXmlRWDoc(nXmlRWType);

	try
	{
		if ( !xml_OpenFile(pRWDoc, strFile) )
		{
			delete pRWDoc;
			return FALSE;
		}
	}
	catch (...)
	{
		delete pRWDoc;
		return FALSE;
	}

	CXmlRWNodeBase *pDocRoot = pRWDoc->GetFirstRootNode();
	CString strNodeName = pDocRoot->GetNodeName();
	CXmlRWNodeListBase *pList = pDocRoot->GetChildNodes();
	CXmlRWNodeBase *pChild = pList->GetChild(0);
	strNodeName = pChild->GetNodeName();
	//pDocRoot = pDocRoot->GetChildNode(_T("use-register-file"));

	try
	{
		if (pDocRoot != NULL)
		{
			pDocRoot->xml_GetElementText(L"use-register-file", m_nUseRegisterFile);
			pDocRoot->xml_GetElementText(L"show-sysname", m_nShowSysName);
			pDocRoot->xml_GetElementText(L"show-ownship", m_nShowOwnship);
			pDocRoot->xml_GetElementText(L"show-dev", m_nShowDev);
			pDocRoot->xml_GetElementText(L"show-usercop", m_nShowUserCop);
			pDocRoot->xml_GetElementText(L"show-user", m_nShowUser);
		}
	}
	catch(...)
	{

	}

	delete pRWDoc;
	return TRUE;
}

BOOL CEncryptTool::IsUseRegisterFile()
{

	if (m_nUseRegisterFile == -1)
	{
		OpenEncryptConfigFile();
#ifdef USE_Old_EngineSystemDefine
		m_nUseRegisterFile = 1;
#endif
	}

	return (m_nUseRegisterFile == 1);
}

long CEncryptTool::GetBeginPos(long nID)
{
	long nBeginPos = 0;
	long nIndex = 0;

	for (nIndex=0; nIndex<=ENCRYPT_INDEX_MAX; nIndex++)
	{
		if (nID == nIndex)
		{
			break;
		}

		nBeginPos += ENCRYPT_LEN[nIndex];
	}
	
	return nBeginPos;
}

long CEncryptTool::GetLen(long nID)
{
	long nLen = 0;
	long nIndex = 0;

	for (nIndex=0; nIndex<=ENCRYPT_INDEX_MAX; nIndex++)
	{
		if (nID == nIndex)
		{
			nLen = ENCRYPT_LEN[nIndex];
			break;
		}
	}

	return nLen;
}

long CEncryptTool::GetBuffer(long nID, char *pBuffer)
{
	long nBeginPos = GetBeginPos(nID);
	long nLen = GetLen(nID);
	ASSERT (nLen >= 8 && nLen <= EncryptElemBuffer_Len);

	char *pBufferSrc = m_pEncryptTextBuffer+nBeginPos;

	if (ValidateBuffer(pBufferSrc, nLen))
	{
		memcpy(pBuffer, pBufferSrc+2, nLen-4);
		nLen-=4;
	}
	else
	{
		*pBuffer = 0;
		nLen = 0;
	}

	return nLen;
}

BOOL CEncryptTool::InitEncrypt()
{
	InitEncrypt(ENCRYPT_INDEX_COMPANY, m_strDev);
	InitEncrypt(ENCRYPT_INDEX_USER, m_strUserName);
	InitEncrypt(ENCRYPT_INDEX_SN, m_strSN);
	InitEncrypt(ENCRYPT_INDEX_MAXUSECOUNT, m_nMaxUseCount);
	InitEncrypt(ENCRYPT_INDEX_CURUSECOUNT, m_nCurrUseCount);
	InitEncrypt(ENCRYPT_INDEX_DEVCODE, m_strDevCode);
	InitEncrypt(ENCRYPT_INDEX_AUTOTEST, m_dwAutoTest);
	InitEncrypt(ENCRYPT_INDEX_DEV, m_dwDevStudio);

	return TRUE;
}
// 
// BOOL CEncryptTool::IsEncrypt()
// {
// 	CString strCode;
// 	CString strMachine;
// 
// 	strMachine = GetMachineCode();
// 	strCode = GetRegisterCode(strMachine);
// 
// 	if (m_strSN.Compare(strCode) != 0)
// 	{
// 		m_bRegistered = FALSE;
// 	}
// 	else
// 	{
// 		m_bRegistered = TRUE;
// 	}
// 
// 	return m_bRegistered;
// }

BOOL CEncryptTool::ValidateBuffer(char *pBuffer, long nLen)
{
	if ((*pBuffer == '@') && (*(pBuffer+1) == 0) && (*(pBuffer+nLen-1) == '@') && (*(pBuffer+nLen-2) == 0))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

void CEncryptTool::InitEncrypt(long nID, CString &strText)
{
	long nBeginPos = GetBeginPos(nID);
	long nLen = GetLen(nID);
	ZeroMemory(m_pBuffer, EncryptElemBuffer_Len);
	GetBuffer(nID, m_pBuffer);
	strText = m_pBuffer;
}

void CEncryptTool::InitEncrypt(long nID, long &nValue)
{
	long nBeginPos = GetBeginPos(nID);
	long nLen = GetLen(nID);
	ZeroMemory(m_pBuffer, EncryptElemBuffer_Len);
	GetBuffer(nID, m_pBuffer);
	nValue = atol(m_pBuffer);
}

void CEncryptTool::InitEncrypt(long nID, DWORD &dwValue)
{
	long nBeginPos = GetBeginPos(nID);
	long nLen = GetLen(nID);
	ZeroMemory(m_pBuffer, EncryptElemBuffer_Len);
	GetBuffer(nID, m_pBuffer);
	dwValue = atol(m_pBuffer);
}

 BOOL CEncryptTool::IsEncrypt()
 {
// 	if (!m_bRegistered)
// 	{
// 		CEncryptBase::IsEncrypt();
// 	}
// 
// 	return m_bRegistered;
	 CString strCode;
	 CString strMachine;

	 CEncryptBase oEncrypt;
	 strMachine = oEncrypt.GetMachineCodeEx();
	 strCode = GetRegisterCode(strMachine);
	 CString strSN = GetSNEx();

	 if (strSN.Compare(strCode) != 0)
	 {
//		 CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("strMachine=%s;strCode=%s;strSN=%s;"),strMachine.GetString(),strCode.GetString(),strSN.GetString());
		 m_bRegistered = FALSE;
		 CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("当前电脑未注册授权,无相关使用权限."));
	 }
	 else
	 {
		 m_bRegistered = TRUE;
	 }

	 if (!m_bRegistered)
	 {
		 POS pos = oEncrypt.GetHeadPosition();
		 CEncryptCode *pCode = NULL;
		 CEncryptCode *pFind = NULL;

		 while (pos != NULL)
		 {
			 pCode = (CEncryptCode *)oEncrypt.GetNext(pos);
			 strMachine = GetMachineCode(pCode);
			 strCode = GetRegisterCode(strMachine);
			 strSN = CodeString(strCode);

			 if (FindSN(strSN) != NULL)
			 {
				 m_bRegistered = TRUE;
				 break;
			 }
		 }
	 }

	 return m_bRegistered;
 }

void CEncryptTool::OpenLocalEncryptFile()
{
	OpenEncryptFile();
	
	IsEncrypt();
// 	CString strCode;
// 	CString strMachine;
// 
// 	CEncryptBase oEncrypt;
// 	strMachine = oEncrypt.GetMachineCodeEx();
// 	strCode = GetRegisterCode(strMachine);
// 	CString strSN = GetSNEx();
// 
// 	if (strSN.Compare(strCode) != 0)
// 	{
// 		m_bRegistered = FALSE;
// 	}
// 	else
// 	{
// 		m_bRegistered = TRUE;
// 	}
// 
// 	if (!m_bRegistered)
// 	{
// 		POS pos = oEncrypt.GetHeadPosition();
// 		CEncryptCode *pCode = NULL;
// 		CEncryptCode *pFind = NULL;
// 
// 		while (pos != NULL)
// 		{
// 			pCode = (CEncryptCode *)oEncrypt.GetNext(pos);
// 			strMachine = GetMachineCode(pCode);
// 			strCode = GetRegisterCode(strMachine);
// 			strSN = CodeString(strCode);
// 
// 			if (FindSN(strSN) != NULL)
// 			{
// 				m_bRegistered = TRUE;
// 				break;
// 			}
// 		}
// 	}
}

inline CString Encrypt_GetUserMsg()
{
	if (!Encrypt_IsEncrypt())
	{
		return g_sLangTxt_NotAuthorized/*_T("你使用的系统没有授权")*/;
	}

	CString strMsg;

	/*_T("版权所有：%s      授权用户单位：%s     授权用户名：%s")*/
	strMsg.Format(_T("%s %s      %s %s     %s %s")
		, g_sLangTxt_RightsReserved
		, g_sLangTxt_UserUnits
		, g_sLangTxt_User2
		, Encrypt_GetCompany(), Encrypt_GetUserCop(), Encrypt_GetUser());

	return strMsg;
}

void Encrypt_LogUserMsg()
{
	if (!Encrypt_IsEncrypt())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_NotAuthorized/*_T("你使用的系统没有授权")*/);
	}

	if (Encrypt_IsShowSysName())
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_pEncryptTool->GetSysName());
	}

	if (Encrypt_IsShowOwnship())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s %s"),  g_sLangTxt_RightsReserved/*_T("版权所有：%s")*/, g_pEncryptTool->GetOwnership());
	}

	if (Encrypt_IsShowDev())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s %s"),  g_sLangTxt_SystemDevelop/*_T("系统开发：%s")*/, g_pEncryptTool->GetDev());
	}


	if (Encrypt_IsShowUserCop())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s %s"),  g_sLangTxt_ClientUnit/*_T("客户单位：%s")*/,  g_pEncryptTool->GetUserCop());
	}

	if (Encrypt_IsShowUser())
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("%s %s"),  g_sLangTxt_UserName/*_T("使用用户：%s")*/, g_pEncryptTool->GetUser());
	}
}

BOOL Encrypt_IsUseRegisterFile()
{
	if (g_pEncryptTool == NULL)
	{
		Encrypt_RegisterTool(new CEncryptTool());
	}

	return g_pEncryptTool->IsUseRegisterFile();
}

