//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//TestMacrosFile.cpp  CTestMacrosFile


#include "stdafx.h"
#include "TestMacrosFile.h"
#include "../XLanguage/XLanguageResource.h"
#include "../API/FileApi.h"
#include "../API/GlobalConfigApi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTestMacrosFile::CTestMacrosFile()
{
	//初始化属性

	//初始化成员变量
	m_strDllCallFile = _T("DLLCallConfig.xml");
	m_nEnable = TRUE;
}

CTestMacrosFile::~CTestMacrosFile()
{
}

long CTestMacrosFile::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_GetAttibuteValue(pXmlKeys->m_strNameKey, oNode, m_strName);
	xml_GetAttibuteValue(pXmlKeys->m_strIDKey, oNode, m_strID);
	xml_GetAttibuteValue(pXmlKeys->m_strOldIDKey, oNode, m_strOldID); //lijq 2020-2-14
	xml_GetAttibuteValue(pXmlKeys->m_strFileKey, oNode, m_strFile);
	xml_GetAttibuteValue(pXmlKeys->m_strCmmFileKey, oNode, m_strCmmFile);
	xml_GetAttibuteValue(pXmlKeys->m_strTestTypeFileKey, oNode, m_strTestTypeFile);
	xml_GetAttibuteValue(pXmlKeys->m_strDataTypeFileKey, oNode, m_strDataTypeFile);
	xml_GetAttibuteValue(pXmlKeys->m_strDvmFileKey, oNode, m_strDvmFile);
	xml_GetAttibuteValue(pXmlKeys->m_strExpandConfigFileKey, oNode, m_strExpandConfigFile);
	xml_GetAttibuteValue(pXmlKeys->m_strActiveMacroTestKey, oNode, m_strActiveMacroTest);
	xml_GetAttibuteValue(pXmlKeys->m_strRecordProgIDKey, oNode, m_strRecordProgID);
	xml_GetAttibuteValue(pXmlKeys->m_strDllCallFileKey, oNode, m_strDllCallFile);

	return 0;
}

long CTestMacrosFile::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strNameKey, oElement, m_strName);
	xml_SetAttributeValue(pXmlKeys->m_strIDKey, oElement, m_strID);
	xml_SetAttributeValue(pXmlKeys->m_strOldIDKey, oElement, m_strOldID);//lijq 2020-2-14
	xml_SetAttributeValue(pXmlKeys->m_strFileKey, oElement, m_strFile);
	xml_SetAttributeValue(pXmlKeys->m_strCmmFileKey, oElement, m_strCmmFile);
	xml_SetAttributeValue(pXmlKeys->m_strTestTypeFileKey, oElement, m_strTestTypeFile);
	xml_SetAttributeValue(pXmlKeys->m_strDataTypeFileKey, oElement, m_strDataTypeFile);
	xml_SetAttributeValue(pXmlKeys->m_strDvmFileKey, oElement, m_strDvmFile);
	xml_SetAttributeValue(pXmlKeys->m_strExpandConfigFileKey, oElement, m_strExpandConfigFile);

	xml_SetAttributeValue(pXmlKeys->m_strActiveMacroTestKey, oElement, m_strActiveMacroTest);
	xml_SetAttributeValue(pXmlKeys->m_strRecordProgIDKey, oElement, m_strRecordProgID);

	//2018-2-13
	xml_SetAttributeValue(pXmlKeys->m_strDllCallFileKey, oElement, m_strDllCallFile);
	return 0;
}

long CTestMacrosFile::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	if(oBinaryBuffer.IsCalSizeMode())
	{
		BinarySerializeCalLen(oBinaryBuffer, m_strName);
		BinarySerializeCalLen(oBinaryBuffer, m_strOldID);
		BinarySerializeCalLen(oBinaryBuffer, m_strFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strCmmFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strTestTypeFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strDataTypeFile);
		BinarySerializeCalLen(oBinaryBuffer, m_strDvmFile);
	}
	else if(oBinaryBuffer.IsReadMode())
	{
		BinarySerializeRead(oBinaryBuffer, m_strName);
		BinarySerializeRead(oBinaryBuffer, m_strOldID);
		BinarySerializeRead(oBinaryBuffer, m_strFile);
		BinarySerializeRead(oBinaryBuffer, m_strCmmFile);
		BinarySerializeRead(oBinaryBuffer, m_strTestTypeFile);
		BinarySerializeRead(oBinaryBuffer, m_strDataTypeFile);
		BinarySerializeRead(oBinaryBuffer, m_strDvmFile);
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
		BinarySerializeWrite(oBinaryBuffer, m_strName);
		BinarySerializeWrite(oBinaryBuffer, m_strOldID);
		BinarySerializeWrite(oBinaryBuffer, m_strFile);
		BinarySerializeWrite(oBinaryBuffer, m_strCmmFile);
		BinarySerializeWrite(oBinaryBuffer, m_strTestTypeFile);
		BinarySerializeWrite(oBinaryBuffer, m_strDataTypeFile);
		BinarySerializeWrite(oBinaryBuffer, m_strDvmFile);
	}
	return 0;
}

void CTestMacrosFile::InitAfterRead()
{
	m_pActiveMacroTest = (CTestMacroConfig *)FindByID(m_strActiveMacroTest);

	if (m_pActiveMacroTest == NULL)
	{
		m_pActiveMacroTest = (CTestMacroConfig *)GetHead();
	}
}

BOOL CTestMacrosFile::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CTestMacrosFile *p = (CTestMacrosFile*)pObj;

	if(m_strName != p->m_strName)
	{
		return FALSE;
	}

	if(m_strFile != p->m_strFile)
	{
		return FALSE;
	}

	if(m_strCmmFile != p->m_strCmmFile)
	{
		return FALSE;
	}

	if(m_strTestTypeFile != p->m_strTestTypeFile)
	{
		return FALSE;
	}

	if(m_strDataTypeFile != p->m_strDataTypeFile)
	{
		return FALSE;
	}

	if(m_strDvmFile != p->m_strDvmFile)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CTestMacrosFile::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTestMacrosFile *p = (CTestMacrosFile*)pDest;

	p->m_strName = m_strName;
	p->m_strOldID = m_strOldID;
	p->m_strFile = m_strFile;
	p->m_strCmmFile = m_strCmmFile;
	p->m_strTestTypeFile = m_strTestTypeFile;
	p->m_strDataTypeFile = m_strDataTypeFile;
	p->m_strDvmFile = m_strDvmFile;
	return TRUE;
}

CBaseObject* CTestMacrosFile::Clone()
{
	CTestMacrosFile *p = new CTestMacrosFile();
	Copy(p);
	return p;
}


CExBaseObject* CTestMacrosFile::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTestMacroXmlRWKeys *pXmlKeys = (CTestMacroXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCTestMacroConfigKey)
	{
		pNew = new CTestMacroConfig();
	}
	else if (strClassID == pXmlKeys->m_strCTestMacroConfigsKey)
	{
		pNew = new CTestMacroConfigs();
	}

	return pNew;
}

CExBaseObject* CTestMacrosFile::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == TMCLASSID_CTESTMACROCONFIG)
	{
		pNew = new CTestMacroConfig();
	}
	else if (nClassID == TMCLASSID_CTESTMACROCONFIGS)
	{
		pNew = new CTestMacroConfigs();
	}

	return pNew;
}

long CTestMacrosFile::InitListCtrlColumns(CListCtrl *pListCtrl)
{
	pListCtrl->InsertColumn(0, g_sLangTxt_Index/*_T("编号")*/);
	pListCtrl->SetColumnWidth(0, 80);
	pListCtrl->InsertColumn(1, _T("Name"));
	pListCtrl->SetColumnWidth(1, 80);
	pListCtrl->InsertColumn(2, _T("File"));
	pListCtrl->SetColumnWidth(2, 80);
	pListCtrl->InsertColumn(3, _T("CmmFile"));
	pListCtrl->SetColumnWidth(3, 80);
	pListCtrl->InsertColumn(4, _T("TestTypeFile"));
	pListCtrl->SetColumnWidth(4, 80);
	pListCtrl->InsertColumn(5, _T("DataTypeFile"));
	pListCtrl->SetColumnWidth(5, 80);
	pListCtrl->SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT);
	return 0;
}

long CTestMacrosFile::UpdateListCtrl(CListCtrl *pListCtrl, long lItemIndex)
{
	CString strTemp;
	strTemp.Format(_T("%d"), lItemIndex+1);
	pListCtrl->SetItemText(lItemIndex, 0, strTemp);
	pListCtrl->SetItemText(lItemIndex, 1, m_strName);
	pListCtrl->SetItemText(lItemIndex, 2, m_strFile);
	pListCtrl->SetItemText(lItemIndex, 3, m_strCmmFile);
	pListCtrl->SetItemText(lItemIndex, 4, m_strTestTypeFile);
	pListCtrl->SetItemText(lItemIndex, 5, m_strDataTypeFile);
	pListCtrl->SetItemData(lItemIndex, (DWORD)this);
	return 0;
}

void CTestMacrosFile::GetAllIecConfigFileType(CDataType *pDataType)
{
	CTestMacroConfig *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CTestMacroConfig *)GetNext(pos);

		if (p->GetClassID() != TMCLASSID_CTESTMACROCONFIG)
		{
			continue;
		}

		if (p->m_strIecConfigFile.GetLength() <= 1)
		{
			continue;
		}

		if (pDataType->FindByID(p->m_strIecConfigFile) == NULL)
		{
			pDataType->AddNewValue(p->m_strIecConfigFile, p->m_strIecConfigFile, pDataType->GetCount());
		}
	}
}

CString CTestMacrosFile::GetActiveMacroID(const CString &strType)
{
	CTestMacroConfigs *pFind = FindTestMacroConfigs(strType);

	if (pFind == NULL)
	{
		return m_strActiveMacroTest;
	}
	else
	{
		return pFind->m_strActiveMacroTest;
	}
}

CTestMacroConfigs* CTestMacrosFile::FindTestMacroConfigs(const CString &strType)
{
	CExBaseObject *p = NULL;
	POS pos = GetHeadPosition();
	CTestMacroConfigs *pFind = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == TMCLASSID_CTESTMACROCONFIGS)
		{
			if ( ((CTestMacroConfigs*)p)->m_strType == strType )
			{
				pFind = (CTestMacroConfigs*)p;
				break;
			}
		}
	}

	return pFind;
}

CString CTestMacrosFile::GetTestMacroCfgFile(const CString &strFileName)
{
	CString strFile;
	strFile = _P_GetConfigPath();
	strFile.AppendFormat(_T("%s/%s"), m_strID.GetString(), strFileName.GetString());

	if (IsFileExist(strFile))
	{
		return strFile;
	}

	strFile = _P_GetConfigPath();
	strFile += strFileName.GetString();
	return strFile;
}

void CTestMacrosFile::CreateMacroFileFolder()
{
	CString strOldPath, strNewPath;
	strOldPath = _P_GetConfigPath();
	strNewPath = strOldPath + m_strID;
	strNewPath += _T("/");

	CreateAllDirectories(strNewPath);
#ifndef _PSX_IDE_QT_		//yyj
	::CopyFile(strOldPath + m_strFile,                    strNewPath + m_strFile, FALSE);
	::CopyFile(strOldPath + m_strTestTypeFile,       strNewPath + m_strTestTypeFile, FALSE);
	::CopyFile(strOldPath + m_strDataTypeFile,       strNewPath + m_strDataTypeFile, FALSE);
	::CopyFile(strOldPath + m_strCmmFile,             strNewPath + m_strCmmFile, FALSE);
	::CopyFile(strOldPath + m_strDllCallFile,             strNewPath + m_strDllCallFile, FALSE);
	::CopyFile(strOldPath + m_strExpandConfigFile,   strNewPath + m_strExpandConfigFile, FALSE);
#endif
}

void CTestMacrosFile::DeleteMacroFiles()
{
	CString strOldPath;
	strOldPath = _P_GetConfigPath();
#ifndef _PSX_IDE_QT_		//yyj
	::DeleteFile(strOldPath + m_strFile);
	::DeleteFile(strOldPath + m_strTestTypeFile);
	::DeleteFile(strOldPath + m_strDataTypeFile);
	::DeleteFile(strOldPath + m_strCmmFile);
	::DeleteFile(strOldPath + m_strDllCallFile);
	::DeleteFile(strOldPath + m_strExpandConfigFile);
#endif
}

CString CTestMacrosFile::GetFileWithPath(const CString &strFile)
{
	return TM_GetFileWithPath(m_strID, strFile);
}

CString  CTestMacrosFile::File(BOOL bAddPath)
{	
	if (bAddPath)
	{
		return GetFileWithPath(m_strFile);
	}

	return m_strFile;	
}

CString  CTestMacrosFile::CmmFile(BOOL bAddPath)
{
	if (bAddPath)
	{
		return GetFileWithPath(m_strCmmFile);
	}

	return m_strCmmFile;
}

CString  CTestMacrosFile::TestTypeFile(BOOL bAddPath)
{
	if (bAddPath)
	{
		return GetFileWithPath(m_strTestTypeFile);
	}

	return m_strTestTypeFile;
}

CString  CTestMacrosFile::DataTypeFile(BOOL bAddPath)
{
	if (bAddPath)
	{
		return GetFileWithPath(m_strDataTypeFile);
	}

	return m_strDataTypeFile;
}

CString  CTestMacrosFile::DvmFile(BOOL bAddPath)
{
	if (bAddPath)
	{
		return GetFileWithPath(m_strDvmFile);
	}

	return m_strDvmFile;
}

CString  CTestMacrosFile::ExpandConfigFile(BOOL bAddPath)
{
	if (bAddPath)
	{
		return GetFileWithPath(m_strExpandConfigFile);
	}

	return m_strExpandConfigFile;
}

CString  CTestMacrosFile::DllCallFile(BOOL bAddPath)
{
	if (bAddPath)
	{
		return GetFileWithPath(m_strDllCallFile);
	}

	return m_strDllCallFile;
}


BOOL TM_IsTestMacroFile(const CString &strFile)
{
	CString strTemp;

	strTemp = strFile.Right(3);
	strTemp.MakeLower();

	if (strTemp == _T("xml"))
	{
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}


CString TM_GetFileWithPath(const CString &strMacroFileID, const CString &strFileName)
{
	return strMacroFileID + _P_FOLDER_PATH_SEPARATOR_ + strFileName;
}

