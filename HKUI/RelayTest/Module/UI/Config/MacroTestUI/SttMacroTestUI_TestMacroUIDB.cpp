//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SttMacroTestUI_TestMacroUIDB.cpp  CSttMacroTestUI_TestMacroUIDB


#include "stdafx.h"
#include "SttMacroTestUI_TestMacroUIDB.h"
#include "../../../../../Module/API/GlobalConfigApi.h"
#include "../../../../../Module/XLanguage/XLanguageMngr.h"
#include "../../../../../Module/API/FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define g_strSttTestMacroUIMngrFile  _T("test-macro-ui-mngr.xml")

CSttMacroTestUI_TestMacroUIDB* CSttMacroTestUI_TestMacroUIDB::g_pSttTestMacroUIDB = NULL;
long CSttMacroTestUI_TestMacroUIDB::g_nSttTestMacroUIDBRef = 0;
CString CSttMacroTestUI_TestMacroUIDB::g_strMacroFileID;

CSttMacroTestUI_TestMacroUIDB* CSttMacroTestUI_TestMacroUIDB::Create(const CString &strSysPath)
{
	g_nSttTestMacroUIDBRef++;

	if (g_nSttTestMacroUIDBRef == 1)
	{
		CSttTestCtrrlMacroTestUIMngrXmlRWKeys::Create();
		g_pSttTestMacroUIDB = new CSttMacroTestUI_TestMacroUIDB();
		g_pSttTestMacroUIDB->Open(strSysPath);

#ifndef NOT_USE_XLANGUAGE
		xlang_TranslateByResourceFileEx(g_pSttTestMacroUIDB, g_strSttTestMacroUIMngrFile);
#endif
	}

	return g_pSttTestMacroUIDB;
}

void CSttMacroTestUI_TestMacroUIDB::Release()
{
	g_nSttTestMacroUIDBRef--;

	if (g_nSttTestMacroUIDBRef == 0)
	{
		CSttTestCtrrlMacroTestUIMngrXmlRWKeys::Release();
		delete g_pSttTestMacroUIDB;
		g_pSttTestMacroUIDB = NULL;
	}
}

CSttMacroTestUI_TestMacroUIDB::CSttMacroTestUI_TestMacroUIDB()
{
	//初始化属性

	//初始化成员变量
	m_pTestMacroUIMngr = NULL;
	m_pTestMacroUIs = NULL;
}

CSttMacroTestUI_TestMacroUIDB::~CSttMacroTestUI_TestMacroUIDB()
{
}

long CSttMacroTestUI_TestMacroUIDB::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strMacro_FileKey, oNode, m_strMacroFile);
	xml_GetAttibuteValue(pXmlKeys->m_strMacro_IdKey, oNode, m_strMacroID);
	return 0;
}

long CSttMacroTestUI_TestMacroUIDB::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strMacro_FileKey, oElement, m_strMacroFile);
	xml_SetAttributeValue(pXmlKeys->m_strMacro_IdKey, oElement, m_strMacroID);
	return 0;
}

long CSttMacroTestUI_TestMacroUIDB::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strMacroFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strMacroID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strMacroFile);
		BinarySerializeRead(oBinaryBuffer, m_strMacroID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strMacroFile);
		BinarySerializeWrite(oBinaryBuffer, m_strMacroID);
	}
	return 0;
}

void CSttMacroTestUI_TestMacroUIDB::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIMNGR)
		{
			m_pTestMacroUIMngr = (CSttMacroTestUI_TestMacroUIMngr*)p;
		}
		else if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIS)
		{
			m_pTestMacroUIs = (CSttMacroTestUI_TestMacroUIs*)p;
		}
	}

	if (m_pTestMacroUIMngr == NULL)
	{
		m_pTestMacroUIMngr = (CSttMacroTestUI_TestMacroUIMngr*)AddNewChild(new CSttMacroTestUI_TestMacroUIMngr());
	}

	if (m_pTestMacroUIs == NULL)
	{
		m_pTestMacroUIs = (CSttMacroTestUI_TestMacroUIs*)AddNewChild(new CSttMacroTestUI_TestMacroUIs());
	}

}

BOOL CSttMacroTestUI_TestMacroUIDB::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CSttMacroTestUI_TestMacroUIDB *p = (CSttMacroTestUI_TestMacroUIDB*)pObj;

	if(m_strMacroFile != p->m_strMacroFile)
	{
		return FALSE;
	}

	if(m_strMacroID != p->m_strMacroID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CSttMacroTestUI_TestMacroUIDB::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CSttMacroTestUI_TestMacroUIDB *p = (CSttMacroTestUI_TestMacroUIDB*)pDest;

	p->m_strMacroFile = m_strMacroFile;
	p->m_strMacroID = m_strMacroID;
	return TRUE;
}

CBaseObject* CSttMacroTestUI_TestMacroUIDB::Clone()
{
	CSttMacroTestUI_TestMacroUIDB *p = new CSttMacroTestUI_TestMacroUIDB();
	Copy(p);
	return p;
}

CBaseObject* CSttMacroTestUI_TestMacroUIDB::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CSttMacroTestUI_TestMacroUIDB *p = new CSttMacroTestUI_TestMacroUIDB();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CSttMacroTestUI_TestMacroUIDB::CanPaste(UINT nClassID)
{
	if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIS)
	{
		return TRUE;
	}

	if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIMNGR)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CSttMacroTestUI_TestMacroUIDB::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CSttTestCtrrlMacroTestUIMngrXmlRWKeys *pXmlKeys = (CSttTestCtrrlMacroTestUIMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSttMacroTestUI_TestMacroUIsKey)
	{
		pNew = new CSttMacroTestUI_TestMacroUIs();
	}
	else if (strClassID == pXmlKeys->m_strCSttMacroTestUI_TestMacroUIMngrKey)
	{
		pNew = new CSttMacroTestUI_TestMacroUIMngr();
	}

	return pNew;
}

CExBaseObject* CSttMacroTestUI_TestMacroUIDB::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIS)
	{
		pNew = new CSttMacroTestUI_TestMacroUIs();
	}
	else if (nClassID == MACROTESTUIMNGRCLASSID_CSTTMACROTESTUI_TESTMACROUIMNGR)
	{
		pNew = new CSttMacroTestUI_TestMacroUIMngr();
	}

	return pNew;
}

CSttMacroTestUI_TestMacroUI* CSttMacroTestUI_TestMacroUIDB::FindTestMacroUI(const CString &strMacroUiId)
{
	if (g_pSttTestMacroUIDB == NULL)
	{
		return NULL;
	}

	if (g_pSttTestMacroUIDB->m_pTestMacroUIs == NULL)
	{
		return NULL;
	}

	return (CSttMacroTestUI_TestMacroUI*)g_pSttTestMacroUIDB->m_pTestMacroUIs->FindByID(strMacroUiId);
}

BOOL CSttMacroTestUI_TestMacroUIDB::Open(const CString &strSysPath)
{
	ASSERT (CSttTestCtrrlMacroTestUIMngrXmlRWKeys::g_pXmlKeys != NULL);
	CString strConfigFolderPath;

	if (strSysPath.GetLength() == 0)
	{
		strConfigFolderPath = _P_GetConfigPath();
	}
	else
	{
		strConfigFolderPath = strSysPath + g_pszKeyConfig;
		strConfigFolderPath += _T("/");
	}

	m_strFile = strConfigFolderPath;

	if (!g_strMacroFileID.IsEmpty())
	{
		m_strFile += g_strMacroFileID;
		m_strFile += _T("/");
	}

	m_strFile += g_strSttTestMacroUIMngrFile;

	if ((!IsFileExist(m_strFile))&&(!g_strMacroFileID.IsEmpty()))
	{
		m_strFile = strConfigFolderPath + g_strSttTestMacroUIMngrFile;
	}

	return OpenFile(m_strFile);
}

BOOL CSttMacroTestUI_TestMacroUIDB::OpenFile(const CString &strFile)
{
	return OpenXmlFile(strFile, CSttTestCtrrlMacroTestUIMngrXmlRWKeys::g_pXmlKeys);
}