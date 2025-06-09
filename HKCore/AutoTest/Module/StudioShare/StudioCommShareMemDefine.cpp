// StudioCommShareMemDefine.cpp
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "StudioCommShareMemDefine.h"
#include "..\..\..\Module\Encrypt\XDes2.h"

CStudioCommShareMemServer::CStudioCommShareMemServer()
{
	m_pMemServer = NULL;
}

CStudioCommShareMemServer::~CStudioCommShareMemServer()
{
	if (m_pMemServer != NULL)
	{
		delete m_pMemServer;
	}
}

BOOL CStudioCommShareMemServer::CreateServer()
{
	if (m_pMemServer == NULL)
	{
		CString strPath;
		strPath = _P_GetBinPath();
		strPath += STUDIO_CMM_MEMFILENAME;
		m_pMemServer = new CShareMemServerEx(strPath, STUDIO_CMM_MAPNAME, STUDIO_CMM_MAPSIZE);
	}

	BYTE *pBuffer = (BYTE*)m_pMemServer->GetBuffer();

	return (pBuffer != NULL);
}

// //////////////////////////////////////////////////////////////////////////
// //////////////////////////////////////////////////////////////////////////
CStudioCommShareMemClient::CStudioCommShareMemClient()
{
	m_pClient = NULL;

	m_pdwExeMsg            = NULL;
	m_pdwExeMsgRevWnd      = NULL;
	m_pdwExeMsgRevThread   = NULL;
	m_pdwExeCommand        = NULL;
	m_pdwExeFileMaxCount   = NULL;
	m_pdwExeFileCount      = NULL;
	m_pdwExeFileBegin      = NULL;
	m_pdwExeFileLen        = NULL;
}


CStudioCommShareMemClient::~CStudioCommShareMemClient()
{
	FreeClient();
}


void CStudioCommShareMemClient::FreeClient()
{
	if (m_pClient != NULL)
	{
		m_pClient->UnMapView();
		delete m_pClient;
		m_pClient = NULL;
	}
}


BYTE* CStudioCommShareMemClient::MapView(volatile __int64 &n64BeginPos, DWORD dwLen)//32M
{
	ASSERT (m_pClient != NULL);

	if (m_pClient == NULL)
	{
		return NULL;
	}

	if (CLogPrint::g_pLogPrint != NULL)
	{
		CLogPrint::LogFormatString(NULL, LOGLEVEL_TRACE, _T("64Begin=%I64d  Len = %08X"), n64BeginPos, dwLen);
	}

	BYTE *pBuffer = (BYTE*)m_pClient->MapView(m_n64AreaBeginPos, m_dwOnceMapSize);
	ASSERT(pBuffer != NULL);

	if (pBuffer != NULL)
	{
		pBuffer = (BYTE*)m_pClient->LocatePos(0);
	}

	return pBuffer;
}


BOOL CStudioCommShareMemClient::CreateClient(UINT nExeID)
{
	m_strID = STUDIO_CMM_MAPNAME;
	long nBeginPos = STUDIO_CMM_BUF_EXE_BUFFERLEN * nExeID;
	long nLen = STUDIO_CMM_BUF_EXE_BUFFERLEN;

	m_n64Length = STUDIO_CMM_MAPSIZE;    //文件的大小
	m_n64AreaBeginPos = nBeginPos;  //数据起始位置
	m_dwOnceMapSize = STUDIO_CMM_BUF_EXE_BUFFERLEN;
	m_n64AreaEndPos = STUDIO_CMM_MAPSIZE;

	if (m_pClient != NULL)
	{
		delete m_pClient;
	}

	m_pClient = new CShareMemClientEx(FILE_MAP_READ|FILE_MAP_WRITE, m_strID);
	BYTE *pBuffer = MapView(m_n64AreaBeginPos, m_dwOnceMapSize);

	if (pBuffer != NULL)
	{
		InitExeDatas();
	}

	return (pBuffer != NULL);
}

BOOL CStudioCommShareMemClient::IsValidate()
{
	return m_pClient->IsValid();
}

void CStudioCommShareMemClient::InitExeDatas()
{
	BYTE *pBuffer = (BYTE*)m_pClient->GetBuffer();

	if (pBuffer == NULL)
	{
		return;
	}

	m_pdwExeMsg            = (DWORD*)pBuffer;		pBuffer += sizeof(DWORD);
	m_pdwExeMsgRevWnd      = (DWORD*)pBuffer;		pBuffer += sizeof(DWORD);
	m_pdwExeMsgRevThread   = (DWORD*)pBuffer;		pBuffer += sizeof(DWORD);
	m_pdwExeCommand        = (DWORD*)pBuffer;		pBuffer += sizeof(DWORD);
	m_pdwExeFileMaxCount   = (DWORD*)pBuffer;		pBuffer += sizeof(DWORD);
	m_pdwExeFileCount      = (DWORD*)pBuffer;		pBuffer += sizeof(DWORD);
	m_pdwExeFileBegin      = (DWORD*)pBuffer;		pBuffer += sizeof(DWORD);
	m_pdwExeFileLen        = (DWORD*)pBuffer;		pBuffer += sizeof(DWORD);
}

CString CStudioCommShareMemClient::GetString(long nPos, long nLen)
{
	BYTE *pBuffer = (BYTE*)m_pClient->GetBuffer();

	if (pBuffer == NULL)
	{
		return _T("");
	}

	char pString[2048];
	memcpy(pString, pBuffer+nPos, nLen);
	pString[nLen] = 0;
	CString strText;
	strText = pString;

	return strText;
}

void CStudioCommShareMemClient::SetString(long nPos, const CString &strText)
{
	BYTE *pBuffer = (BYTE*)m_pClient->GetBuffer();

	if (pBuffer == NULL)
	{
		return;
	}

	char pString[2048];
	long nLen = CString_to_char(strText, pString);
	char *pTemp = (char*)pBuffer+nPos;
	memcpy(pTemp, pString, nLen);
	pTemp += nLen;
	*pTemp = 0;
}

void CStudioCommShareMemClient::UpdateMemClient()
{
	if (m_pClient != NULL)
	{
		return;
	}

	m_pClient->FlushView();
}

long CStudioCommShareMemClient::GetFilePos(long nIndex)
{
	return STUDIO_CMM_BUF_EXE_FILEBEGIN + STUDIO_CMM_BUF_EXE_FILELEN * nIndex;
}

void CStudioCommShareMemClient::WriteFile(long nIndex, const CString &strFile)
{
	SetString(GetFilePos(nIndex), strFile);
}

CString CStudioCommShareMemClient::ReadFile(long nIndex)
{
	return GetString(GetFilePos(nIndex), STUDIO_CMM_BUF_EXE_FILELEN);
}

void CStudioCommShareMemClient::PostCommand(UINT nCmd, UINT nCmdParam)
{
	if (m_pdwExeMsgRevWnd == NULL)
	{
		return;
	}

	HWND hWnd = (HWND)*m_pdwExeMsgRevWnd;

	if (!::IsWindow(hWnd))
	{
		return;
	}

	::PostMessage(hWnd, *m_pdwExeMsg, nCmd, nCmdParam);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CStudioCommShareMemMngr::CStudioCommShareMemMngr()
{
	m_pStudioCommShareMemServer = NULL;
	m_pStudioCommShareMemClient = NULL;
}

CStudioCommShareMemMngr::~CStudioCommShareMemMngr()
{
	if (m_pStudioCommShareMemServer != NULL)
	{
		delete m_pStudioCommShareMemServer;
		m_pStudioCommShareMemServer = NULL;
	}

	if (m_pStudioCommShareMemClient != NULL)
	{
		delete m_pStudioCommShareMemClient;
		m_pStudioCommShareMemClient = NULL;
	}
}

CStudioCommShareMemMngr* CStudioCommShareMemMngr::g_pStudioCommShareMemMngr = NULL;
long CStudioCommShareMemMngr::g_nStudioCommShareMemMngr = 0;
CString CStudioCommShareMemMngr::m_strUserName;

	
CStudioCommShareMemMngr* CStudioCommShareMemMngr::Create()
{
	g_nStudioCommShareMemMngr++;

	if (g_nStudioCommShareMemMngr == 1)
	{
		g_pStudioCommShareMemMngr = new CStudioCommShareMemMngr();
	}

	return g_pStudioCommShareMemMngr;
}

CStudioCommShareMemClient* CStudioCommShareMemMngr::GetLogin()
{
	return GetExeShareMem(STUDIO_EXE_ID_LOGIN);
}

CStudioCommShareMemClient* CStudioCommShareMemMngr::GetMainExe()
{
	return GetExeShareMem(STUDIO_EXE_ID_MAIN);
}

CStudioCommShareMemClient* CStudioCommShareMemMngr::GetAutoTestExe()
{
	return GetExeShareMem(STUDIO_EXE_ID_AUTOTEST);
}

CStudioCommShareMemClient* CStudioCommShareMemMngr::GetGbDevExe()
{
	return GetExeShareMem(STUDIO_EXE_ID_GBDEV);
}

CStudioCommShareMemClient* CStudioCommShareMemMngr::GetRptDevExe()
{
	return GetExeShareMem(STUDIO_EXE_ID_RPTDEV);
}

CStudioCommShareMemClient* CStudioCommShareMemMngr::GetPpDevExe()
{
	return GetExeShareMem(STUDIO_EXE_ID_PPDEV);
}

CStudioCommShareMemClient* CStudioCommShareMemMngr::GetPpEngineExe()
{
	return GetExeShareMem(STUDIO_EXE_ID_PPENGINE);
}

CStudioCommShareMemClient* CStudioCommShareMemMngr::GetExeShareMem(UINT nExeID)
{
	ASSERT (g_pStudioCommShareMemMngr != NULL);

	if (g_pStudioCommShareMemMngr == NULL)
	{
		return NULL;
	}

	return g_pStudioCommShareMemMngr->CreeateShareMem(nExeID);
}

void CStudioCommShareMemMngr::Release()
{
	g_nStudioCommShareMemMngr--;

	if (g_nStudioCommShareMemMngr == 0)
	{
		delete g_pStudioCommShareMemMngr;
		g_pStudioCommShareMemMngr = NULL;
	}
}

CString CStudioCommShareMemMngr::GetUserName()
{
	if (g_pStudioCommShareMemMngr == NULL)
	{
		return m_strUserName;
	}

	if (m_strUserName.GetLength() > 0)
	{
		return m_strUserName;
	}

	CStudioCommShareMemClient *pLogin = GetLogin();

	CString strUserName = pLogin->GetString(0, 1024);
// 	CXAes oXAes;
// 	m_strUserName = oXAes.InvCipher(strUserName);
	m_strUserName = xdes_Decrypt(strUserName);

	return m_strUserName;
}

void CStudioCommShareMemMngr::SetUserName(const CString &strUserName)
{
	if (g_pStudioCommShareMemMngr == NULL)
	{
		return;
	}

	CStudioCommShareMemClient *pLogin = GetLogin();
// 	CXAes oXAes;
// 	CString strTemp = oXAes.Cipher(strUserName);
	CString strTemp = xdes_Encrypt(strUserName);
	pLogin->SetString(0, strTemp);
}

CStudioCommShareMemClient* CStudioCommShareMemMngr::CreeateShareMem(UINT nExeID)
{
	if (m_pStudioCommShareMemServer == NULL)
	{
		m_pStudioCommShareMemServer = new CStudioCommShareMemServer();
		m_pStudioCommShareMemServer->CreateServer();
	}

	CStudioCommShareMemClient *pFind = FindByExeID(nExeID);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = new CStudioCommShareMemClient();
	pFind->m_nExeID = nExeID;
	AddNewChild(pFind);

	if (pFind->CreateClient(nExeID))
	{
		return pFind;
	}

	return pFind;
}

CStudioCommShareMemClient* CStudioCommShareMemMngr::FindByExeID(UINT nExeID)
{
	CStudioCommShareMemClient *p = NULL;
	CStudioCommShareMemClient *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CStudioCommShareMemClient *)GetNext(pos);

		if (p->m_nExeID == nExeID)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}



//////////////////////////////////////////////////////////////////////////

BOOL studio_cmd_autotest_to_main_testbegin(const CString &strProjectFile)
{
	CStudioCommShareMemClient *pMain = CStudioCommShareMemMngr::GetMainExe();
	CStudioCommShareMemClient *pAutoTest = CStudioCommShareMemMngr::GetAutoTestExe();

	if (!pMain->IsValidate())
	{
		return FALSE;
	}

	pAutoTest->WriteFile(STUDIO_CMD_FILE_INDEX_PROJECT, strProjectFile);
	pMain->PostCommand(STUDIO_CMD_AUTOTEST_TO_MAIN_TESTBEGIN, 0);

	return TRUE;
}

BOOL studio_cmd_autotest_to_main_teststop(const CString &strProjectFile)
{
	CStudioCommShareMemClient *pMain = CStudioCommShareMemMngr::GetMainExe();
	CStudioCommShareMemClient *pAutoTest = CStudioCommShareMemMngr::GetAutoTestExe();

	if (!pMain->IsValidate())
	{
		return FALSE;
	}

	pAutoTest->WriteFile(STUDIO_CMD_FILE_INDEX_PROJECT, strProjectFile);
	pMain->PostCommand(STUDIO_CMD_AUTOTEST_TO_MAIN_TESTSTOP, 0);

	return TRUE;
}

BOOL studio_cmd_autotest_to_main_testclose(const CString &strProjectFile)
{
	CStudioCommShareMemClient *pMain = CStudioCommShareMemMngr::GetMainExe();
	CStudioCommShareMemClient *pAutoTest = CStudioCommShareMemMngr::GetAutoTestExe();

	if (!pMain->IsValidate())
	{
		return FALSE;
	}

	pAutoTest->WriteFile(STUDIO_CMD_FILE_INDEX_PROJECT, strProjectFile);
	pMain->PostCommand(STUDIO_CMD_AUTOTEST_TO_MAIN_TESTCLOSE, 0);

	return TRUE;
}

BOOL studio_cmd_autotest_to_main_tasksave(const CString &strTaskFile)
{
	CStudioCommShareMemClient *pMain = CStudioCommShareMemMngr::GetMainExe();
	CStudioCommShareMemClient *pAutoTest = CStudioCommShareMemMngr::GetAutoTestExe();

	if (!pMain->IsValidate())
	{
		CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("Error:autotest_to_main_tasksave(%s)"), strTaskFile);
		return FALSE;
	}

	CLogPrint::LogFormatString(LOGLEVEL_TRACE, _T("autotest_to_main_tasksave(%s)"), strTaskFile);
	pAutoTest->WriteFile(STUDIO_CMD_FILE_INDEX_TASK, strTaskFile);
	pMain->PostCommand(STUDIO_CMD_AUTOTEST_TO_MAIN_TASKSAVE, 0);

	return TRUE;
}

BOOL studio_cmd_autotest_to_main_createtask(const CString &strTaskFile)
{
	CStudioCommShareMemClient *pMain = CStudioCommShareMemMngr::GetMainExe();
	CStudioCommShareMemClient *pAutoTest = CStudioCommShareMemMngr::GetAutoTestExe();

	if (!pMain->IsValidate())
	{
		return FALSE;
	}

	pAutoTest->WriteFile(STUDIO_CMD_FILE_INDEX_TASK, strTaskFile);
	pMain->PostCommand(STUDIO_CMD_AUTOTEST_TO_MAIN_CREATETASK, 0);

	return TRUE;
}

BOOL studio_cmd_autotest_to_main_createtest(const CString &strProjectFile)
{
	CStudioCommShareMemClient *pMain = CStudioCommShareMemMngr::GetMainExe();
	CStudioCommShareMemClient *pAutoTest = CStudioCommShareMemMngr::GetAutoTestExe();

	if (!pMain->IsValidate())
	{
		return FALSE;
	}

	pAutoTest->WriteFile(STUDIO_CMD_FILE_INDEX_PROJECT, strProjectFile);
	pMain->PostCommand(STUDIO_CMD_AUTOTEST_TO_MAIN_CREATETEST, 0);

	return TRUE;
}

//主程序 - 自动测试
BOOL studio_cmd_main_to_autotest_opentest(const CString &strTaskFile, const CString &strProjectFile)
{
	CStudioCommShareMemClient *pMain = CStudioCommShareMemMngr::GetMainExe();
	CStudioCommShareMemClient *pAutoTest = CStudioCommShareMemMngr::GetAutoTestExe();

	if (!pMain->IsValidate())
	{
		return FALSE;
	}

	pMain->WriteFile(STUDIO_CMD_FILE_INDEX_TASK, strTaskFile);
	pMain->WriteFile(STUDIO_CMD_FILE_INDEX_PROJECT, strProjectFile);
	pAutoTest->PostCommand(STUDIO_CMD_MAIN_TO_AUTOTEST_OPENTEST, 0);

	return TRUE;
}


//测试模板编辑 - 主程序
BOOL studio_cmd_gbdev_to_main_save(const CString &strGbFile)
{
	return FALSE;
}

BOOL studio_cmd_gbdev_to_main_close(const CString &strGbFile)
{
	return FALSE;
}

//主程序 - 测试模板编辑
BOOL studio_cmd_main_to_gbdev_open(const CString &strGbFile)
{
	return FALSE;
}


//规约模板编辑 - 主程序
BOOL studio_cmd_ppdev_to_main_save(const CString &strPpFile)
{
	return FALSE;
}

BOOL studio_cmd_ppdev_to_main_close(const CString &strPpFile)
{
	return FALSE;
}

//主程序 - 规约模板编辑
BOOL studio_cmd_main_to_ppdev_open(const CString &strPpFile)
{
	return FALSE;
}


