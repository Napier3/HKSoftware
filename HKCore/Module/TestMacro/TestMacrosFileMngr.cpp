//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacrosFileMngr.cpp  CTestMacrosFileMngr


#include "stdafx.h"
#include "TestMacrosFileMngr.h"
#include "../XLanguage/XLanguageResource.h"
#include "../XLanguage/XLanguageMngr.h"

#include "TestMacroInterface.h"
#include"../API/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString CTestMacrosFileMngr::g_strDefaultMacroTestEngineProgID = _T("PonovoVm.TestEngine");
CString CTestMacrosFileMngr::g_strDefaultIecConfigFile = _T("ixml");


const CString CTestMacrosFileMngr::g_strTestMacrosFileMngrFile = _T("TestMacroFileMngr.xml");
CTestMacrosFileMngr* CTestMacrosFileMngr::g_pTestMacrosFileMngr = NULL;
long  CTestMacrosFileMngr::g_nTestMacrosFileMngrRef = 0;

CTestMacrosFileMngr* CTestMacrosFileMngr::Create(BOOL bUseAts)
{
	g_nTestMacrosFileMngrRef++;

	if (g_nTestMacrosFileMngrRef == 1)
	{
		g_pTestMacrosFileMngr = new CTestMacrosFileMngr();
		g_pTestMacrosFileMngr->OpenXmlFile(bUseAts);
	}

	return g_pTestMacrosFileMngr;
}

void CTestMacrosFileMngr::Release()
{
	g_nTestMacrosFileMngrRef--;

	if (g_nTestMacrosFileMngrRef == 0)
	{
		delete g_pTestMacrosFileMngr;
		g_pTestMacrosFileMngr = NULL;
	}
}


CString CTestMacrosFileMngr::GetActiveMacroTestProgID(const CString &strFile, const CString &strType)
{
	if (g_pTestMacrosFileMngr == NULL)
	{
		return g_strDefaultMacroTestEngineProgID;
	}
	else
	{
		return g_pTestMacrosFileMngr->In_GetActiveMacroTestProgID(strFile, strType);
	}
}

void CTestMacrosFileMngr::AdjustToNewVersion()
{
	if (g_pTestMacrosFileMngr != NULL)
	{
		g_pTestMacrosFileMngr->In_AdjustToNewVersion();
	}
}

void CTestMacrosFileMngr::InitByAuthoritys(const CString &strAuthoritys)
{
	if (g_pTestMacrosFileMngr != NULL)
	{
		g_pTestMacrosFileMngr->In_InitByAuthoritys(strAuthoritys);
	}
}

CTestMacrosFileMngr::CTestMacrosFileMngr()
{
	//初始化属性

	//初始化成员变量
	m_nVersion = TEST_MACRO_FILE_MNGR_VERSION_1;
}

CTestMacrosFileMngr::~CTestMacrosFileMngr()
{
}

long CTestMacrosFileMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strVersionKey, oNode, m_nVersion);

	return 0;
}

long CTestMacrosFileMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strVersionKey, oElement, m_nVersion);

	return 0;
}

long CTestMacrosFileMngr::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

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

void CTestMacrosFileMngr::InitAfterRead()
{
}

BOOL CTestMacrosFileMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTestMacrosFileMngr *p = (CTestMacrosFileMngr*)pObj;

	return TRUE;
}

BOOL CTestMacrosFileMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CTestMacrosFileMngr *p = (CTestMacrosFileMngr*)pDest;

	return TRUE;
}

CBaseObject* CTestMacrosFileMngr::Clone()
{
	CTestMacrosFileMngr *p = new CTestMacrosFileMngr();
	Copy(p);
	return p;
}

long CTestMacrosFileMngr::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, g_sLangTxt_Index/*_T("编号")*/);
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTestMacrosFileMngr::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

BOOL CTestMacrosFileMngr::CanPaste(UINT nClassID)
{
	if (nClassID == TMCLASSID_CTESTMACROSFILE)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTestMacrosFileMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTestMacrosFileKey)
	{
		pNew = new CTestMacrosFile();
	}

	return pNew;
}

CExBaseObject* CTestMacrosFileMngr::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TMCLASSID_CTESTMACROSFILE)
	{
		pNew = new CTestMacrosFile();
	}

	return pNew;
}

void CTestMacrosFileMngr::OpenXmlFile(BOOL bUseAts)
{
	CString strFile;

	if (bUseAts)
	{
		strFile = _P_GetInstallPath();
		strFile += _T("e-Report/Config/");
	}
	else
	{
		strFile = _P_GetConfigPath();
	}

	strFile += g_strTestMacrosFileMngrFile;

	CBaseObject::OpenXmlFile(strFile, CTestMacroXmlRWKeys::CTestMacrosFileMngrKey(), CTestMacroXmlRWKeys::g_pXmlKeys);

	AdjustToNewVersion();

	//xlang_TranslateByResourceFile(this, g_strTestMacrosFileMngrFile);
	//20161212  lijq
#ifndef NOT_USE_XLANGUAGE
	xlang_TranslateByResourceFileEx(this, g_strTestMacrosFileMngrFile);
#endif
}

void CTestMacrosFileMngr::SaveXmlFile()
{
	m_nVersion = TEST_MACRO_FILE_MNGR_VERSION;
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += g_strTestMacrosFileMngrFile;

	CBaseObject::SaveXmlFile(strFile, CTestMacroXmlRWKeys::g_pXmlKeys);
}

CTestMacrosFile* CTestMacrosFileMngr::FindByFile(const CString &strFile)
{
	//2017-10-29 m_strTestMacroFile==>m_strTestMacroFileID
	//2017-10-29  测试功能ID
	if (!TM_IsTestMacroFile(strFile))
	{
		return (CTestMacrosFile*)FindByID(strFile);
	}

	CTestMacrosFile *pFile = NULL;
	CTestMacrosFile *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pFile = (CTestMacrosFile*)GetNext(pos);

		if (pFile->File(FALSE) == strFile)
		{
			pFind = pFile;
			break;
		}
	}

	return pFind;
}


CTestMacrosFile* CTestMacrosFileMngr::FindByFile(const CString &strMacroFile, const CString &strCommCmdFile)
{
	//2017-10-29 m_strTestMacroFile==>m_strTestMacroFileID
	//2017-10-29  测试功能ID
	if (!TM_IsTestMacroFile(strMacroFile))
	{
		return (CTestMacrosFile*)FindByID(strMacroFile);
	}

	CTestMacrosFile *pFile = NULL;
	CTestMacrosFile *pFind = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		pFile = (CTestMacrosFile*)GetNext(pos);

		if (pFile->File(FALSE) == strMacroFile && pFile->CmmFile(FALSE) == strCommCmdFile)
		{
			pFind = pFile;
			break;
		}
	}

	return pFind;
}

CString CTestMacrosFileMngr::In_GetActiveMacroTestProgID(const CString &strFile, const CString &strType)
{
	CTestMacrosFile *pFind = FindByFile(strFile);

	if (pFind != NULL)
	{
		return pFind->GetActiveMacroID(strType);
	}
	else
	{
		return g_strDefaultMacroTestEngineProgID;
	}
}

void CTestMacrosFileMngr::GetAllIecConfigFileType(CDataType *pDataType)
{
	ASSERT (g_pTestMacrosFileMngr != NULL);

	g_pTestMacrosFileMngr->In_GetAllIecConfigFileType(pDataType);
}

void CTestMacrosFileMngr::In_GetAllIecConfigFileType(CDataType *pDataType)
{
	CTestMacrosFile *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CTestMacrosFile *)GetNext(pos);
		p->GetAllIecConfigFileType(pDataType);
	}
}

void CTestMacrosFileMngr::In_AdjustToNewVersion()
{
	if (m_nVersion >= TEST_MACRO_FILE_MNGR_VERSION_2)
	{
		return;
	}

	CTestMacrosFile *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CTestMacrosFile *)GetNext(pos);
		p->CreateMacroFileFolder();
	}

	pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CTestMacrosFile *)GetNext(pos);
		p->DeleteMacroFiles();
	}

	SaveXmlFile();
}


void CTestMacrosFileMngr::In_InitByAuthoritys(const CString &strAuthoritys)
{
	//如果为空，则为老版本的软件，返回不错处理
	if (strAuthoritys.GetLength() <= 3)
	{
		return;
	}

	CTestMacrosFile *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CTestMacrosFile *)GetNext(pos);
		
		if (strAuthoritys.Find(p->m_strID) >= 0)
		{
			p->m_nEnable = 1;
		}
		else
		{
			p->m_nEnable = 0;
		}
	}
}

CString CTestMacrosFileMngr::FindTestMacroFileByID(const CString &strTestMacroFileID, CTestMacrosFile **ppMacroFile)
{
	ASSERT (g_pTestMacrosFileMngr != NULL);

	if (g_pTestMacrosFileMngr == NULL)
	{
		return TM_GetDefaultTestMacrosFile();
	}

	CTestMacrosFile *pFile = (CTestMacrosFile*)g_pTestMacrosFileMngr->FindByID(strTestMacroFileID);
	ASSERT( pFile != NULL );
	*ppMacroFile = pFile;

	if (pFile == NULL)
	{
		//lijq 2020-02-14 兼容测试功能ID标准化带来的问题：ID改变
		return  CTestMacrosFileMngr::FindTestMacroFileByID_Old(strTestMacroFileID, ppMacroFile);;
	}

	return pFile->File(FALSE);
}


CString CTestMacrosFileMngr::FindTestMacroFileByID_Old(const CString &strTestMacroFileID, CTestMacrosFile **ppMacroFile)
{
	ASSERT (g_pTestMacrosFileMngr != NULL);

	if (g_pTestMacrosFileMngr == NULL)
	{
		return TM_GetDefaultTestMacrosFile();
	}

	POS pos = g_pTestMacrosFileMngr->GetHeadPosition();
	CTestMacrosFile *p = NULL, *pFind = NULL;

	while (pos != NULL)
	{
		p = (CTestMacrosFile *)g_pTestMacrosFileMngr->GetNext(pos);

		if (p->OldID() == strTestMacroFileID)
		{
			pFind = p;
			break;
		}
	}

	ASSERT( pFind != NULL );
	*ppMacroFile = pFind;

	if (pFind == NULL)
	{
		return TM_GetDefaultTestMacrosFile();
	}

	return pFind->File(FALSE);
}

