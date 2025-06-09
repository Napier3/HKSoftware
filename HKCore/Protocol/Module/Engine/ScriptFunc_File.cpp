#include "StdAfx.h"
#include "ScriptFunc_File.h"
#include "PpEngineDataMngrCntr.h"

#include "../../../Module/API/GlobalConfigApi.h"
#include "../../../Module/API/FileApi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CFileTrans* g_pCFileTrans = NULL;

CFileTrans::CFileTrans()
{
	for (unsigned int i = 0; i < MAX_SECTION_NUM; i++)
	{
		m_uSectionLen[i] = 0;
		m_pSectionData[i] = NULL;
	}
	m_nCurSection = 0;
}

CFileTrans::~CFileTrans()
{
	for (unsigned int i = 0; i < MAX_SECTION_NUM; i++)
	{
		if (m_pSectionData[i])
			delete[] m_pSectionData[i];
	}
}

void CFileTrans::AddSectionData(int nSection, BYTE* pData, int nLength)
{
	BYTE* pOldData = NULL;
	if (m_uSectionLen[nSection - 1] != 0)
	{
		pOldData = new BYTE[m_uSectionLen[nSection - 1]];

		if (!pOldData)
			return;

		memcpy(pOldData, m_pSectionData[nSection - 1], m_uSectionLen[nSection - 1]);
	}
	delete[] m_pSectionData[nSection - 1];
	int nLen = m_uSectionLen[nSection - 1] + nLength;
	m_pSectionData[nSection - 1] = new BYTE[nLen];

	if (pOldData)
	{
		memcpy(m_pSectionData[nSection - 1], pOldData, m_uSectionLen[nSection - 1]);
		delete[] pOldData;
	}

	memcpy(m_pSectionData[nSection - 1] + m_uSectionLen[nSection - 1], pData, nLength);
	m_uSectionLen[nSection - 1] = nLen;
}

//======================================================================================


void script_AddSectionData(CTScriptSingleVM *pXvm, long nIndex, long nBytes)
{
	if (g_pCFileTrans == NULL)
		g_pCFileTrans = new CFileTrans();

	if (g_pCFileTrans == NULL)
		return;

	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());
	if (pByteBlock == NULL)
	{
		return;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return;
	}

	long nLength = pByteBlock->GetByteBlockLength();
	if (nIndex + nBytes <= nLength)
	{
		g_pCFileTrans->AddNewSection();
		g_pCFileTrans->AddSectionData(g_pCFileTrans->GetCurSection(), pByteBlock->m_pBuffer + nIndex, nBytes);
	}
}

void script_Fis103SaveRCDFile(CTScriptSingleVM *pXvm, const char* strPath, long nFileNameLen)
{
	if (g_pCFileTrans == NULL)
		return;

	int nLen = 0;
	for (int i = 0; i < g_pCFileTrans->GetCurSection(); i++)
	{
		nLen += g_pCFileTrans->GetSectionLength(i);
	}

	char* pBuffer = new char[nLen];
	if (!pBuffer)
		return;

	char* p = pBuffer;
	for (int i = 0; i < g_pCFileTrans->GetCurSection(); i++)
	{
		memcpy(p, g_pCFileTrans->GetSectionData(i), g_pCFileTrans->GetSectionLength(i));
		p += g_pCFileTrans->GetSectionLength(i);
	}

	CString szPathHead(strPath);
	if ("\\" != szPathHead.Right(1))
		szPathHead += "\\";

	p = pBuffer;
	char szName[100] = { 0 };
	memcpy(szName, p, nFileNameLen);
	p += nFileNameLen;
	p += 7;	
	
	// HDR文件
	CString szFileName = szPathHead + szName;
	szFileName += ".hdr";	
	
	// open file
	CStdioFile AccidentFile;
	if (0 == AccidentFile.Open(szFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		delete g_pCFileTrans;
		g_pCFileTrans = NULL;
		delete[] pBuffer;
		//CString strErr = "open hdr file error";
		//strErr += szFileName;
		//MessageBox(NULL, strErr, "Err", MB_OK);
		return;
	}

	BYTE btType = *(BYTE*)p;
	if (btType != 1)
	{
		//CString strErr = "hdr file type error";
		//strErr += szFileName;
		//MessageBox(NULL, strErr, "Err", MB_OK);
		return;
	}

	p += 1;
	int nHdrLen = *(DWORD*)p;
	p += 4;
	AccidentFile.Write(p, nHdrLen);
	AccidentFile.Close();

	//cfg文件
	p += nHdrLen;
	szFileName.Replace(_T(".hdr"), _T(".cfg"));	// open file
	if (0 == AccidentFile.Open(szFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		//CString strErr = "open cfg file error";
		//strErr += szFileName;
		//MessageBox(NULL, strErr, "Err", MB_OK);
		return;
	}
	
	btType = *(BYTE*)p;
	if (btType != 2)
	{
		//CString strErr = "cfg file type error";
		//strErr += szFileName;
		//MessageBox(NULL, strErr, "Err", MB_OK);
		return;
	}
	p += 1;
	int nCfgLen = *(DWORD*)p;
	p += 4;

	AccidentFile.Write(p, nCfgLen);
	AccidentFile.Close();
	p += nCfgLen;

	//dat文件
	szFileName.Replace(_T(".cfg"), _T(".dat"));
	if (0 == AccidentFile.Open(szFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		//CString strErr = "open dat file error";
		//strErr += szFileName;
		//MessageBox(NULL, strErr, "Err", MB_OK);
		return;
	}

	btType = *(BYTE*)p;
	if (btType != 3)
	{
		//CString strErr = "dat file type error";
		//strErr += szFileName;
		//MessageBox(NULL, strErr, "Err", MB_OK);
		return;
	}	
	
	p += 1;
	int nDatLen = *(DWORD*)p;
	p += 4;
	AccidentFile.Write(p, nDatLen);
	AccidentFile.Close();
	delete g_pCFileTrans;
	g_pCFileTrans = NULL;
	delete[] pBuffer;
}

void script_Fis103SaveCommonFile(CTScriptSingleVM *pXvm, const char* strPath, long nFileNameLen)
{
	if (g_pCFileTrans == NULL)
		return;

	int nLen = 0;
	for (int i = 0; i < g_pCFileTrans->GetCurSection(); i++)
	{
		nLen += g_pCFileTrans->GetSectionLength(i);
	}

	char* pBuffer = new char[nLen];
	if (!pBuffer)
		return;

	char* p = pBuffer;
	for (int i = 0; i < g_pCFileTrans->GetCurSection(); i++)
	{
		memcpy(p, g_pCFileTrans->GetSectionData(i), g_pCFileTrans->GetSectionLength(i));
		p += g_pCFileTrans->GetSectionLength(i);
	}

	CString szPathHead(strPath);
	if ("\\" != szPathHead.Right(1))
		szPathHead += "\\";

	p = pBuffer;
	char szName[100];
	sprintf(szName, p, nFileNameLen);
	p += nFileNameLen;
	p += 7;

	// 通用文件
	CString szFileName = szPathHead + szName;

	// open file
	CStdioFile CommonFile;
	if (0 == CommonFile.Open(szFileName, CFile::modeCreate | CFile::modeWrite | CFile::typeText))
	{
		delete g_pCFileTrans;
		g_pCFileTrans = NULL;
		delete[] pBuffer;
		//CString strErr = "open hdr file error";
		//strErr += szFileName;
		//MessageBox(NULL, strErr, "Err", MB_OK);
		return;
	}

	int nFileLen = *(DWORD*)p;
	p += 4;
	CommonFile.Write(p, nFileLen);
	CommonFile.Close();

	delete g_pCFileTrans;
	g_pCFileTrans = NULL;
	delete[] pBuffer;
}

//////////////////////////////////////////////////////////////////////////
//

class CScriptFunc_FilesMngr : public CExBaseList
{
	class CScriptFunc_File : public CExBaseObject
	{
	public:
		CScriptFunc_File()
		{
			m_bFileOpened = FALSE;
			m_pVmRef = NULL;
		}

		virtual ~CScriptFunc_File()
		{

		}

		CFile m_oFile;
		CTScriptSingleVM *m_pVmRef;
		BOOL m_bFileOpened;

	public:
		CString GetRcdFile(const CString &strPath, const CString &strFileName, BOOL bCreate)
		{
			CString strFile;
			CString strPathEx;

			if (strPath.GetLength() == 0)
			{
				strPathEx = _P_GetDBPath();
			}
			else
			{
				if (strPath.Right(1) == _T("\\"))
				{
					strPathEx = strPath;
				}
				else
				{
					strPathEx = strPath + _T("\\");
				}
			}

			if (bCreate)
			{
				CreateAllDirectories(strPathEx);
			}

			strFile = strPathEx + strFileName;

			return strFile;
		}

		long CreateRcdFile(const CString &strPath, const CString &strFileName)
		{
			if (m_bFileOpened)
			{
				m_oFile.Close();
			}

			CString strFile = GetRcdFile(strPath, strFileName, TRUE);
			
			m_bFileOpened = m_oFile.Open(strFile, CFile::modeCreate | CFile::modeWrite);

			if (!m_bFileOpened)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Create RCD File [%s] failed"), strFile);
			}

			return 1;
		}

		long OpenRcdFile(const CString &strPath, const CString &strFileName)
		{
			if (m_bFileOpened)
			{
				m_oFile.Close();
			}

			CString strFile = GetRcdFile(strPath, strFileName, FALSE);

			m_bFileOpened = m_oFile.Open(strFile, CFile::modeRead);

			if (!m_bFileOpened)
			{
				CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Create RCD File [%s] failed"), strFile);
			}

			return 1;
		}

		//////////////////////////////////////////////////////////////////////////
		//Write File
		long WriteRcdFile(BYTE *pBuffer, long nBytes)
		{
			if (!m_bFileOpened)
			{
				return 0;
			}

			m_oFile.Write(pBuffer, nBytes);

			return 1;
		}

		//////////////////////////////////////////////////////////////////////////
		//Read File
		long ReadRcdFile(BYTE *pBuffer, long nBytes)
		{
			if (!m_bFileOpened)
			{
				return 0;
			}

			return m_oFile.Read(pBuffer, nBytes);
		}

		long GetFileLength()
		{
			if (!m_bFileOpened)
			{
				return 0;
			}

			return m_oFile.GetLength();
		}

		long GetFileLeftLength()
		{
			if (!m_bFileOpened)
			{
				return 0;
			}

			long nLen = m_oFile.GetLength();
			long nPos = m_oFile.GetPosition();
			return nLen - nPos - 1;
		}

		//////////////////////////////////////////////////////////////////////////
		//CloseFile
		long CloseRcdFile(CTScriptSingleVM *pXvm)
		{
			if (!m_bFileOpened)
			{
				return 0;
			}

			m_oFile.Close();

			return 1;
		}
	};

public:
	CScriptFunc_FilesMngr()
	{

	}
	virtual ~CScriptFunc_FilesMngr()
	{

	}

private:
	CScriptFunc_File* FindFile(CTScriptSingleVM *pXvm)
	{
		POS pos = GetHeadPosition();
		CScriptFunc_File *pFile = NULL;

		while (pos != NULL)
		{
			pFile = (CScriptFunc_File *)GetNext(pos);

			if (pFile->m_pVmRef == pXvm)
			{
				return pFile;
			}
		}

		return NULL;
	}

public:
	long CreateRcdFile(CTScriptSingleVM *pXvm, const CString &strPath, const CString &strFileName);
	long WriteRcdFile(CTScriptSingleVM *pXvm, BYTE *pBuffer, long nBytes);
	long CloseRcdFile(CTScriptSingleVM *pXvm);

	long OpenRcdFile(CTScriptSingleVM *pXvm, const CString &strPath, const CString &strFileName);
	long ReadRcdFile(CTScriptSingleVM *pXvm, BYTE *pBuffer, long nBytes);
	long GetFileLength(CTScriptSingleVM *pXvm);
	long GetFileLeftLength(CTScriptSingleVM *pXvm);
	

}g_oScriptFunc_FilesMngr;


long CScriptFunc_FilesMngr::CreateRcdFile(CTScriptSingleVM *pXvm, const CString &strPath, const CString &strFileName)
{
	CScriptFunc_FilesMngr::CScriptFunc_File *pFile = NULL;

	pFile = FindFile(pXvm);

	if (pFile == NULL)
	{
		pFile = new CScriptFunc_FilesMngr::CScriptFunc_File();
		pFile->m_pVmRef = pXvm;
		AddTail(pFile);
	}

	return pFile->CreateRcdFile(strPath, strFileName);
}

long CScriptFunc_FilesMngr::WriteRcdFile(CTScriptSingleVM *pXvm, BYTE *pBuffer, long nBytes)
{
	CScriptFunc_FilesMngr::CScriptFunc_File *pFile = NULL;

	pFile = FindFile(pXvm);

	if (pFile == NULL)
	{
		return 0;
	}

	pFile->WriteRcdFile(pBuffer, nBytes);

	return 1;
}

long CScriptFunc_FilesMngr::CloseRcdFile(CTScriptSingleVM *pXvm)
{
	CScriptFunc_FilesMngr::CScriptFunc_File *pFile = NULL;

	pFile = FindFile(pXvm);

	if (pFile == NULL)
	{
		return 0;
	}

	pFile->CloseRcdFile(pXvm);

	return 1;
}

long CScriptFunc_FilesMngr::OpenRcdFile(CTScriptSingleVM *pXvm, const CString &strPath, const CString &strFileName)
{
	CScriptFunc_FilesMngr::CScriptFunc_File *pFile = NULL;

	pFile = FindFile(pXvm);

	if (pFile == NULL)
	{
		pFile = new CScriptFunc_FilesMngr::CScriptFunc_File();
		pFile->m_pVmRef = pXvm;
		AddTail(pFile);
	}

	return pFile->OpenRcdFile(strPath, strFileName);
}

long CScriptFunc_FilesMngr::ReadRcdFile(CTScriptSingleVM *pXvm, BYTE *pBuffer, long nBytes)
{
	CScriptFunc_FilesMngr::CScriptFunc_File *pFile = NULL;

	pFile = FindFile(pXvm);

	if (pFile == NULL)
	{
		return 0;
	}

	return pFile->ReadRcdFile(pBuffer, nBytes);
}

long CScriptFunc_FilesMngr::GetFileLength(CTScriptSingleVM *pXvm)
{
	CScriptFunc_FilesMngr::CScriptFunc_File *pFile = NULL;

	pFile = FindFile(pXvm);

	if (pFile == NULL)
	{
		return 0;
	}

	return pFile->GetFileLength();
}

long CScriptFunc_FilesMngr::GetFileLeftLength(CTScriptSingleVM *pXvm)
{
	CScriptFunc_FilesMngr::CScriptFunc_File *pFile = NULL;

	pFile = FindFile(pXvm);

	if (pFile == NULL)
	{
		return 0;
	}

	return pFile->GetFileLeftLength();
}



long script_CreateFile(CTScriptSingleVM *pXvm, const char *pszPath, const char* pszFileName)
{
	CString strPath, strFileName;
	strFileName = pszFileName;

	CPpEngineData *pEngineData = (CPpEngineData*)pXvm->GetRefData();
	strPath = pEngineData->m_strRcdFilePath;

	if (strFileName.GetLength() < 2)
	{
		return 0;
	}

	return g_oScriptFunc_FilesMngr.CreateRcdFile(pXvm, strPath, strFileName);
}

long script_WriteFile(CTScriptSingleVM *pXvm, long nIndex, long nBytes)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if (pByteBlock == NULL)
	{
		return 0;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return 0;
	}

	long nLength = pByteBlock->GetByteBlockLength();

	if (nIndex + nBytes <= nLength)
	{
		g_oScriptFunc_FilesMngr.WriteRcdFile(pXvm, pByteBlock->m_pBuffer + nIndex, nBytes);
	}

	return 0;
}

long script_CloseFile(CTScriptSingleVM *pXvm)
{
	g_oScriptFunc_FilesMngr.CloseRcdFile(pXvm);

	return 0;
}

long script_OpenRcdFile(CTScriptSingleVM *pXvm, const char *pszPath, const char *pszFileName)
{
	CString strPath, strFileName;
	strFileName = pszFileName;

	CPpEngineData *pEngineData = (CPpEngineData*)pXvm->GetRefData();
	strPath = pEngineData->m_strRcdFilePath;

	if (strFileName.GetLength() < 2)
	{
		return 0;
	}

	return g_oScriptFunc_FilesMngr.OpenRcdFile(pXvm, strPath, strFileName);  //20200819  CreateRcdFile  改为OpenRcdFile
}

long script_ReadRcdFile(CTScriptSingleVM *pXvm, long nIndex, long nBytes)
{
	CByteBlock *pByteBlock = PPS_GetByteBlock((CPpEngineData*)pXvm->GetRefData());

	if (pByteBlock == NULL)
	{
		return 0;
	}

	if (pByteBlock->m_pBuffer == NULL)
	{
		return 0;
	}

	long nLength = pByteBlock->GetByteBlockLength();

	if (nIndex + nBytes <= nLength)
	{
		g_oScriptFunc_FilesMngr.ReadRcdFile(pXvm, pByteBlock->m_pBuffer + nIndex, nBytes);
	}

	return 0;
}

long script_GetFileLength(CTScriptSingleVM *pXvm)
{
	return g_oScriptFunc_FilesMngr.GetFileLength(pXvm);
}

long script_GetFileLeftLength(CTScriptSingleVM *pXvm)
{
	return g_oScriptFunc_FilesMngr.GetFileLeftLength(pXvm);
}

