//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacros.cpp  CTestMacros


#include "stdafx.h"
#include "TestMacros.h"
#include "../API/GlobalConfigApi.h"

#ifndef NOT_USE_XLANGUAGE
//#include "../XLanguage/XLanguageResource.h"
#include "../XLanguage/XLanguageMngr.h"
#endif

#include "../API/FileApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CString CTestMacros::g_strOldMacroTestDataTypeFile         = _T("MacroTestDataTye.xml");			//测试功能参数数据类型文件

CTestMacros::CTestMacros()
{
	//初始化属性

	//初始化成员变量
	m_pMacroScriptMngr = NULL;
	m_pDataTypes = NULL;
	m_bOpenFlag = FALSE;
	m_bOpenByXLang = FALSE;
}

CTestMacros::~CTestMacros()
{
	if (m_pMacroScriptMngr != NULL)
	{
		delete m_pMacroScriptMngr;
		m_pMacroScriptMngr = NULL;
	}

	if (m_pDataTypes != NULL)
	{
		delete m_pDataTypes;
		m_pDataTypes = NULL;
	}
}

long CTestMacros::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strProgIDKey, oNode, m_strProgID);

	return 0;
}

long CTestMacros::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strProgIDKey, oElement, m_strProgID);

	return 0;
}

long CTestMacros::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CExBaseObject::SerializeOwn(oBinaryBuffer);

	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strProgID);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strProgID);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strProgID);
	}
	return 0;
}

void CTestMacros::InitAfterRead()
{
	POS pos = m_listMacrosInclude.GetHeadPosition();
	CTestMacrosInclude *p = NULL;

	while (pos != NULL)
	{
		p = (CTestMacrosInclude *)m_listMacrosInclude.GetNext(pos);
		p->OpenMacrosIncludeFile(m_strMacroFilePath);
		AppendEx(*p);
	}
}

BOOL CTestMacros::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTestMacros *p = (CTestMacros*)pObj;

	if(m_strProgID != p->m_strProgID)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTestMacros::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CTestMacros *p = (CTestMacros*)pDest;

	p->m_strProgID = m_strProgID;
	return TRUE;
}

CBaseObject* CTestMacros::Clone()
{
	CTestMacros *p = new CTestMacros();
	Copy(p);
	return p;
}

long CTestMacros::InitListCtrlColumns(CListCtrl *pListCtrl)
{
#ifdef NOT_USE_XLANGUAGE
	pListCtrl->InsertColumn(0, _T("编号"));
#else
	pListCtrl->InsertColumn(0, g_sLangTxt_Index/*_T("编号")*/);
#endif

	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("ID"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("ProgID"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTestMacros::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strID);
	pListCtrl->SetItemText(lItemIndex, 3, m_strProgID);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

BOOL CTestMacros::CanPaste(UINT nClassID)
{
	if (nClassID == TMCLASSID_CTESTMACRO)
	{
		return TRUE;
	}

	return FALSE;
}

CExBaseObject* CTestMacros::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCTestMacroKey)
	{
		pNew = new CTestMacro();
	}
	else if (strClassID == pXmlKeys->m_strCTestMacrosIncludeKey)
	{
		bAddToTail = FALSE;
		pNew = new CTestMacrosInclude();
		m_listMacrosInclude.AddTail(pNew);
	}

	return pNew;
}

CExBaseObject* CTestMacros::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TMCLASSID_CTESTMACRO)
	{
		pNew = new CTestMacro();
	}

	return pNew;
}

void CTestMacros::FreeMacroScriptMngr()
{
	if (m_pMacroScriptMngr != NULL)
	{
		delete m_pMacroScriptMngr;
		m_pMacroScriptMngr = NULL;
	}
}

void CTestMacros::SetMacroScriptMngr(CExBaseObject *pMacroScriptMngr)
{
	FreeMacroScriptMngr();
	m_pMacroScriptMngr = pMacroScriptMngr;		
}

void CTestMacros::OpenDataTypeFile(const CString &strDataTypeFile)
{
	if (m_pDataTypes != NULL)
	{
		return ;
	}

	m_pDataTypes = new CDataTypes();
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile += strDataTypeFile;

	BOOL bTrue = m_pDataTypes->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	
	//兼容老版本的程序
	if (!bTrue)
	{
		strFile = _P_GetConfigPath();
		strFile += g_strOldMacroTestDataTypeFile;
		m_pDataTypes->OpenXmlFile(strFile, CDataMngrXmlRWKeys::g_pXmlKeys);
	}
}

BOOL CTestMacros::OpenTestMacroFile(const CString &strMacroFile, const CString &strMacroFileID)
{
	if (m_bOpenFlag)
	{
		return TRUE;
	}

	CString strPath;
	CString strName;
	BOOL bOpenByXLang = FALSE;

	if (IsFileExist(strMacroFile))
	{
		strPath = strMacroFile;
	}
	else
	{
		CString strCfgPath;
		strCfgPath = _P_GetConfigPath();
		m_strMacroFilePath.Format(_T("%s%s/"), strCfgPath.GetString(), strMacroFileID.GetString());
		strPath = m_strMacroFilePath + strMacroFile.GetString();
	}

	CString strPath1 = strPath;
	strName = GetPathFileNameFromFilePathName(strPath, '/');

	//shaolei 2024-10-28 多语言转换太慢，debug版本要15s，改为直接打开多语言版本
#ifndef NOT_USE_XLANGUAGE
	long nPos = strPath.Find(_T(".xml"));
	strPath = strPath.Left(nPos);
	strPath += _T("_");
	strPath += xlang_GetCurrLanguageID();
	strPath += _T(".xml");

	if (! IsFileExist(strPath))
	{
		//多语言文件不存在，使用源文件
		strPath = strPath1;
		bOpenByXLang = FALSE;
	}
	else
	{
		bOpenByXLang = TRUE;
	}
#endif

// 	if (IsFileExist(strMacroFile))
// 	{
// 		strName = GetPathFileNameFromFilePathName(strMacroFile, '/');
// 		strPath = strMacroFile;
// 		m_strMacroFilePath = GetPathFromFilePathName(strPath, '/');
// 	}
// 	else
// 	{
// 		strName = strMacroFile;
//         CString strCfgPath;
//         strCfgPath = _P_GetConfigPath();
// 		m_strMacroFilePath.Format(_T("%s%s/"), strCfgPath.GetString(), strMacroFileID.GetString());
// 		strPath = m_strMacroFilePath + strMacroFile.GetString();
// 
// 		//2020-01-26 : 测试功能配置文件通过路径进行分类，首先判断是否为分类模式，之后为兼容之前版本
// 		if (! IsFileExist(strPath))
// 		{
// 			strPath.Format(_T("%s%s"), strCfgPath.GetString(), strMacroFile.GetString());
// 		}
// 	}

	m_strID = strName;
	m_strName = strName;
	m_strMacroFile = strName;

	CTestMacroXmlRWKeys *pXmlKeys = CTestMacroXmlRWKeys::g_pXmlKeys;
	CString strFormatKey;
	strFormatKey = pXmlKeys->m_strFormatKey;
	pXmlKeys->m_strFormatKey = L"create-group";
	m_bOpenFlag = OpenXmlFile(strPath, pXmlKeys->CTestMacrosKey(), pXmlKeys);
	m_bOpenByXLang = (bOpenByXLang && m_bOpenFlag);
	pXmlKeys->m_strFormatKey = strFormatKey.AllocSysString();

	return TRUE;
}

CTestMacro *CTestMacros::GetCloneMacro(const CString& strID)
{
	CTestMacro *pFind = (CTestMacro *)FindByID(strID);
	if (pFind == NULL)
	{
		return NULL;
	}

	CTestMacro *pNew = (CTestMacro *)pFind->Clone();
	return pNew;
}

//lijunqing  2021-8-15
void CTestMacros::InitParas_Dvm()
{
	POS pos = GetHeadPosition();
	CTestMacro *p = NULL;

	while (pos != NULL)
	{
		p = (CTestMacro*)GetNext(pos);
		p->InitParas_Dvm();
	}
}

CDataTypeValue* CTestMacros::GetDataTypeValue(const CString &strMacroID, const CString &strIDPath, const CString &strValue)
{
	if (m_pDataTypes == NULL)
	{
		return NULL;
	}

	CTestMacro *pTestMacro = (CTestMacro *)FindByID(strMacroID);

	if (pTestMacro == NULL)
	{
		return NULL;
	}

	CShortData *pData = pTestMacro->FindDataByID(strIDPath);

	if (pData == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("can not find para by idpath  [%s]"), strIDPath.GetString());
		return NULL;
	}

	CDataType *pDataType = (CDataType *)m_pDataTypes->FindByID(pData->m_strDataTypeID);

	if (pDataType == NULL)
	{
		if (pData->m_strDataTypeID != _T("float"))
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("can not find datatype by id [%s]"), pData->m_strDataTypeID.GetString());
		}
		
		return NULL;
	}

	return pDataType->FindByIndex(strValue);
}

//////////////////////////////////////////////////////////////////////////
//CTestMacrosInclude
CTestMacrosInclude::CTestMacrosInclude()
{

}

CTestMacrosInclude::~CTestMacrosInclude()
{
	RemoveAll();
}

long CTestMacrosInclude::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strCTestMacrosFileKey, oNode, m_strIncludeFile);

	return 0;
}

long CTestMacrosInclude::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strCTestMacrosFileKey, oElement, m_strIncludeFile);

	return 0;
}

void CTestMacrosInclude::OpenMacrosIncludeFile(const CString &strPath)
{
	CString strFile;
	strFile = strPath + m_strIncludeFile;
	OpenTestMacroFile(strFile, _T(""));
}


