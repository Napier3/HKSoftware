//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XFileTypes.cpp  CXFileTypes


#include "stdafx.h"
#include "XFileTypes.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXFileTypes::CXFileTypes()
{
	//初始化属性

	//初始化成员变量
}

CXFileTypes::~CXFileTypes()
{
}
// 
// long CXFileTypes::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
// {
// 	CXXmlRWKeys *pXmlKeys = (CXXmlRWKeys*)pXmlRWKeys;
// 
// 	xml_GetAttibuteValue(pXmlKeys->m_strRootPathKey, oNode, m_strRootPath);
// 	
// 
// 	return 0;
// }
// 
// long CXFileTypes::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
// {
// 	CXXmlRWKeys *pXmlKeys = (CXXmlRWKeys*)pXmlRWKeys;
// 
// 	xml_SetAttributeValue(pXmlKeys->m_strRootPathKey, oElement, m_strRootPath);
// 
// 	return 0;
// }
// 
// long CXFileTypes::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
// {
// 	if(oBinaryBuffer.IsCalSizeMode())
// 	{
// 		BinarySerializeCalLen(oBinaryBuffer, m_strRootPath);
// 	}
// 	else if(oBinaryBuffer.IsReadMode())
// 	{
// 		BinarySerializeRead(oBinaryBuffer, m_strRootPath);
// 	}
// 	else if(oBinaryBuffer.IsWriteMode())
// 	{
// 		BinarySerializeWrite(oBinaryBuffer, m_strRootPath);
// 	}
// 
// 	return 0;
// }
// 
// void CXFileTypes::InitAfterRead()
// {
// }
// 
// BOOL CXFileTypes::IsEqualOwn(CBaseObject* pObj)
// {
// 	if(this == pObj)
// 	{
// 		return TRUE;
// 	}
// 
// 	CXFileTypes *p = (CXFileTypes*)pObj;
// 
// 	return TRUE;
// }
// 
// BOOL CXFileTypes::CopyOwn(CBaseObject* pDest)
// {
// 	if(this == pDest)
// 	{
// 		return TRUE;
// 	}
// 
// 	CXFileTypes *p = (CXFileTypes*)pDest;
// 	p->m_strRootPath = m_strRootPath;
// 
// 	return TRUE;
// }
// 
// CBaseObject* CXFileTypes::Clone()
// {
// 	CXFileTypes *p = new CXFileTypes();
// 	Copy(p);
// 	return p;
// }
// 
// BOOL CXFileTypes::CanPaste(UINT nClassID)
// {
// 	if (nClassID == UICLASSID_CUIBASEFILETYPE)
// 	{
// 		return TRUE;
// 	}
// 
// 	return FALSE;
// }
// 
CExBaseObject* CXFileTypes::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->CDataTypeKey())
	{
		pNew = new CXFileType();
	}

	return pNew;
}

// CExBaseObject* CXFileTypes::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
// {
// 	CExBaseObject *pNew  = NULL;
// 
// 
// 	if (nClassID == UICLASSID_CUIBASEFILETYPE)
// 	{
// 		pNew = new CXFileType();
// 	}
// 
// 	return pNew;
// }

CXFileType* CXFileTypes::AddFileType(const CString &strName, const CString &strID, const CString &strExe, const CString &strRunMode)
{
	CXFileType *pNew = new CXFileType();
	pNew->m_strID = strID;
	pNew->m_strName = strName;
	pNew->m_strExe = strExe;
	pNew->m_strRunMode = strRunMode;
	AddNewChild(pNew);

	return pNew;
}


void CXFileTypes::InitXFilePostfix(CExBaseList &oList, BOOL bOnllySearchMainTypeFile)
{
	POS pos = GetHeadPosition();
	CXFileType *pFileType = NULL;

	while(pos != NULL)
	{
		pFileType = (CXFileType *)GetNext(pos);
		pFileType->InitXFilePostfix(oList, bOnllySearchMainTypeFile);
	}
}

CXFileType* CXFileTypes::FindFileType(CXFile *pSrcFile)
{
	CString strFilePostfix;
	strFilePostfix = ParseFilePostfix(pSrcFile->m_strID);

	CXFileType *pXFileType = FindFileType(strFilePostfix);

	return pXFileType;
}

CXFileType* CXFileTypes::FindFileType(const CString &strFilePostfix)
{
	CXFileType *pFind = NULL;
	CXFileType *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXFileType *)GetNext(pos);

		if (p->FindFileType(strFilePostfix))
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

void CXFileTypes::GetAllFilePostfix(CExBaseList &list)
{
	CXFileType *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXFileType *)GetNext(pos);
		list.Append(p);
	}
}

BOOL CXFileTypes::ValidateFilePostfix(const CString &strFilePostfix)
{
	if (GetCount() == 0)
	{
		return TRUE;
	}

	CXFileType *p = NULL;
	POS pos = GetHeadPosition();
	BOOL bFind = FALSE;

	while (pos != NULL)
	{
		p = (CXFileType *)GetNext(pos);

		if (p->ValidateFilePostfix(strFilePostfix))
		{
			bFind = TRUE;
			break;
		}
	}

	return bFind;
}

BOOL  CXFileTypes::XCopyFile(CXFile *pSrcFile, CXFolder *pFolder, BOOL bFailIfExists)
{
	CString strFolder = pFolder->GetFolderPath(TRUE);
	return XCopyFile(pSrcFile, strFolder, bFailIfExists);
}

BOOL  CXFileTypes::XCopyFile(CXFile *pSrcFile, const CString &strFolder, BOOL bFailIfExists)
{
	CXFileType *pFileType = FindFileType(pSrcFile);

	if (pFileType == NULL)
	{
		CString strFile = pSrcFile->GetTotalFileName();
		return xfile_XCopyFile(strFile, strFolder, bFailIfExists);

		return 0;
	}
	else
	{
		return pFileType->XCopyFile(pSrcFile, strFolder, bFailIfExists);
	}
}

BOOL CXFileTypes::XImportFile(const CString &strFile, CXFolder *pFolder, BOOL bFailIfExists)
{
	CString strPostfix = ParseFilePostfix(strFile);
	CXFileType *pFileType = FindFileType(strPostfix);

	if (pFileType == NULL)
	{
		return FALSE;
	}
	else
	{
		return pFileType->XImportFile(strFile, pFolder, bFailIfExists);
	}
}

BOOL CXFileTypes::XOpenXFile(CXFile *pFile)
{
	CXFileType *pFileType = FindFileType(pFile);

	if (pFileType != NULL)
	{
		return pFileType->XOpenXFile(pFile);
	}

	return FALSE;
}

BOOL CXFileTypes::XDeleteXFile(CXFile *pFile)
{
	if (GetCount() == 0)
	{
		CString strSrcFile;
		strSrcFile = pFile->GetTotalFileName();
		X_DeleteFile(strSrcFile);
		return TRUE;
	}

	CXFileType *pFileType = FindFileType(pFile);

	if (pFileType != NULL)
	{
		return pFileType->XDeleteXFile(pFile);
	}

	return FALSE;
}

BOOL CXFileTypes::XEditXFile(CXFile *pFile, const CString &strDestName)
{
	CXFileType *pFileType = FindFileType(pFile);

	if (pFileType != NULL)
	{
		return pFileType->XEditXFile(pFile, strDestName);
	}

	return FALSE;
}

void CXFileTypes::GetXFileDlgString(CString &strXFileFilter, CString &strXFilePostFix)
{
	strXFileFilter.Empty();
	strXFilePostFix.Empty();
	CXFileType *p = NULL;
	POS pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CXFileType *)GetNext(pos);
		p->GetXFileDlgString(strXFileFilter, strXFilePostFix);
	}

	strXFileFilter += _T("||");
}

