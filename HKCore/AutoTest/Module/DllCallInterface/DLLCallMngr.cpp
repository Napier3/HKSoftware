//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//DLLCallMngr.cpp  CDllCallDefMngr


#include "stdafx.h"
#include "DLLCallMngr.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//CDllCallDefFile

CDllCallDefFile::CDllCallDefFile()
{
	//初始化属性

	//初始化成员变量
}

CDllCallDefFile::~CDllCallDefFile()
{
}

// CDllCallDefFile* CDllCallDefFile::Create()
// {
// 	CString strFile;
// 	strFile = _P_GetConfigFilePath(_T("DLLCallConfig.xml"));
// 	OpenXmlFile(strFile, CDllCallXmlRWKeys::g_pXmlKeys);
// }

CExBaseObject* CDllCallDefFile::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDllCallXmlRWKeys *pXmlKeys = (CDllCallXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDllCallDefKey)
	{
		pNew = new CDllCallDef();
	}

	return pNew;
}

CExBaseObject* CDllCallDefFile::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DLCLCLASSID_CDLLCALL)
	{
		pNew = new CDllCallDef();
	}

	return pNew;
}

BOOL CDllCallDefFile::OpenDllCallDefFile(const CString &strDllCallFile)
{
	CString strFile;

	if (strDllCallFile.GetLength() == 0)
	{
		strFile = _P_GetConfigFilePath(_T("DLLCallConfig.xml"));
	}
	else
	{
		strFile = _P_GetConfigFilePath(strDllCallFile);
	}

	m_strName = strDllCallFile;
	m_strName.MakeLower();
	m_strID = m_strName;

	BOOL bRet = OpenXmlFile(strFile, CDllCallXmlRWKeys::g_pXmlKeys);

	if (!bRet)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("DLL Call Config File [%s] not exist!"), strFile);
	}

	return bRet;
}

//////////////////////////////////////////////////////////////////////////
//CDllCallDefMngr
CDllCallDefMngr* CDllCallDefMngr::g_pDllCallDefMngr = NULL;
long CDllCallDefMngr::g_nDllCallDefMngrRef = 0;

CDllCallDefMngr::CDllCallDefMngr()
{
	//初始化属性

	//初始化成员变量
}

CDllCallDefMngr::~CDllCallDefMngr()
{
}

CDllCallDefMngr* CDllCallDefMngr::Create()
{
	CDllCallXmlRWKeys::Create();
	g_nDllCallDefMngrRef++;

	if (g_nDllCallDefMngrRef == 1)
	{
		g_pDllCallDefMngr = new CDllCallDefMngr();
// 		CString strFile;
// 		strFile = _P_GetConfigFilePath(_T("DLLCallConfig.xml"));
// 		g_pDllCallDefMngr->OpenXmlFile(strFile, CDllCallXmlRWKeys::g_pXmlKeys);
	}

	return g_pDllCallDefMngr;
}

void CDllCallDefMngr::Release()
{
	g_nDllCallDefMngrRef--;

	if (g_nDllCallDefMngrRef == 0)
	{
		delete g_pDllCallDefMngr;
		g_pDllCallDefMngr = NULL;
	}

	CDllCallXmlRWKeys::Release();
}

CDllCallDefFile* CDllCallDefMngr::GetDllCallFile(const CString &strDllCallFile)
{
	ASSERT (g_pDllCallDefMngr != NULL);
	return g_pDllCallDefMngr->In_GetDllCallFile(strDllCallFile);
}

CDllCallDefFile* CDllCallDefMngr::In_GetDllCallFile(const CString &strDllCallFile)
{
	CString strTemp;
	strTemp = strDllCallFile;
	strTemp.MakeLower();

	CDllCallDefFile *pFind = (CDllCallDefFile*)FindByID(strTemp);

	if (pFind != NULL)
	{
		return pFind;
	}

	pFind = new CDllCallDefFile();
	pFind->OpenDllCallDefFile(strTemp);
	AddNewChild(pFind);

	return pFind;
}

long CDllCallDefMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CDllCallXmlRWKeys *pXmlKeys = (CDllCallXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDllCallDefMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CDllCallXmlRWKeys *pXmlKeys = (CDllCallXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CDllCallDefMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CDllCallDefMngr::InitAfterRead()
{
}

BOOL CDllCallDefMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CDllCallDefMngr *p = (CDllCallDefMngr*)pObj;

	return TRUE;
}

BOOL CDllCallDefMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CDllCallDefMngr *p = (CDllCallDefMngr*)pDest;

	return TRUE;
}

CBaseObject* CDllCallDefMngr::Clone()
{
	CDllCallDefMngr *p = new CDllCallDefMngr();
	Copy(p);
	return p;
}

BOOL CDllCallDefMngr::CanPaste(UINT nClassID)
{
	if (nClassID == DLCLCLASSID_CDLLCALL)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CDllCallDefMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDllCallXmlRWKeys *pXmlKeys = (CDllCallXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCDllCallDefKey)
	{
		pNew = new CDllCallDef();
	}

	return pNew;
}

CExBaseObject* CDllCallDefMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == DLCLCLASSID_CDLLCALL)
	{
		pNew = new CDllCallDef();
	}

	return pNew;
}
