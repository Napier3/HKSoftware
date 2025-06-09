//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//XFileType.cpp  CXFileType


#include "stdafx.h"
#include "XFileType.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CXFileTypePostfix::CXFileTypePostfix()
{

}

CXFileTypePostfix::~CXFileTypePostfix()
{

}

BOOL CXFileTypePostfix::CopyOwn(CBaseObject* pDest)
{
	return CExBaseObject::CopyOwn(pDest);
}

CBaseObject* CXFileTypePostfix::Clone()
{
	CXFileTypePostfix *p = new CXFileTypePostfix();
	Copy(p);
	return p;
}

long CXFileTypePostfix::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	return CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);
}

long CXFileTypePostfix::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	return CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
}

//////////////////////////////////////////////////////////////////////////
//
CXFileType::CXFileType()
{
	//初始化属性

	//初始化成员变量
}

CXFileType::~CXFileType()
{
}

long CXFileType::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	return 0;
}

long CXFileType::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	return 0;
}
// 
// long CXFileType::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
// {
// 	CExBaseObject::SerializeOwn(oBinaryBuffer);
// 
// 	if(oBinaryBuffer.IsCalSizeMode())
// 	{
// 	}
// 	else if(oBinaryBuffer.IsReadMode())
// 	{
// 	}
// 	else if(oBinaryBuffer.IsWriteMode())
// 	{
// 	}
// 	return 0;
// }
// 
// void CXFileType::InitAfterRead()
// {
// }
// 
// BOOL CXFileType::IsEqualOwn(CBaseObject* pObj)
// {
// 	if(this == pObj)
// 	{
// 		return TRUE;
// 	}
// 
// 	if (!CExBaseObject::IsEqualOwn(pObj))
// 	{
// 		return FALSE;
// 	}
// 
// 	CXFileType *p = (CXFileType*)pObj;
// 
// 	return TRUE;
// }
// 
// BOOL CXFileType::CopyOwn(CBaseObject* pDest)
// {
// 	if(this == pDest)
// 	{
// 		return TRUE;
// 	}
// 
// 	CExBaseObject::CopyOwn(pDest);
// 
// 	CXFileType *p = (CXFileType*)pDest;
// 
// 	return TRUE;
// }
// 
// CBaseObject* CXFileType::Clone()
// {
// 	CXFileType *p = new CXFileType();
// 	Copy(p);
// 	return p;
// }
// 

CExBaseObject* CXFileType::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CDataMngrXmlRWKeys *pXmlKeys = (CDataMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->CDataTypeValueKey())
	{
		pNew = new CXFileTypePostfix();
	}

	return pNew;
}

CXFileTypePostfix* CXFileType::AddNewPostfix(const CString &strName, const CString &strID)
{
	CXFileTypePostfix *pNew = (CXFileTypePostfix *)FindByID(strID);
	
	if (pNew != NULL)
	{
		return pNew;
	}
	
	pNew = new CXFileTypePostfix();
	pNew->m_strID = strID;
	pNew->m_strName = strName;
	AddNewChild(pNew);

	return pNew;
}


void CXFileType::InitXFilePostfix(CExBaseList &oList, BOOL bOnllySearchMainTypeFile)
{
	POS pos = GetHeadPosition();
	CXFileTypePostfix *pPostfix = NULL;

	if (bOnllySearchMainTypeFile)
	{
		if (pos != NULL)
		{
			pPostfix = (CXFileTypePostfix *)GetNext(pos);
			CXFileTypePostfix *pNew = new CXFileTypePostfix();
			pNew->m_strName = pPostfix->m_strName;
			pNew->m_strID = pPostfix->m_strID;
			pNew->m_strID.MakeLower();
			oList.AddNewChild(pNew);
		}
	}
	else
	{
		while(pos != NULL)
		{
			pPostfix = (CXFileTypePostfix *)GetNext(pos);
			CXFileTypePostfix *pNew = new CXFileTypePostfix();
			pNew->m_strName = pPostfix->m_strName;
			pNew->m_strID = pPostfix->m_strID;
			pNew->m_strID.MakeLower();
			oList.AddNewChild(pNew);
		}
	}
}

BOOL CXFileType::FindFileType(const CString &strFilePostfix)
{
	CXFileTypePostfix *pFind = NULL;
	pFind = (CXFileTypePostfix *)FindByID(strFilePostfix);

	return (pFind != NULL);
}

BOOL  CXFileType::XCopyFile(CXFile *pSrcFile, CXFolder *pFolder, BOOL bFailIfExists)
{
	CString strFolder = pFolder->GetFolderPath(TRUE);
	return XCopyFile(pSrcFile, strFolder, bFailIfExists);
}

BOOL  CXFileType::XCopyFile(CXFile *pSrcFile, const CString &strFolder, BOOL bFailIfExists)
{
	POS pos = GetHeadPosition();
	CXFileTypePostfix *p = NULL;
	CString strSrcFile;
	strSrcFile = pSrcFile->GetTotalFileName();
	BOOL bTrue = TRUE;

	while (pos != NULL)
	{
		p = (CXFileTypePostfix *)GetNext(pos);
		strSrcFile = ChangeFilePostfix(strSrcFile, p->m_strID);
		xfile_XCopyFile(strSrcFile, strFolder, bFailIfExists);
	}

	return TRUE;
}

BOOL CXFileType::XImportFile(const CString &strFile, CXFolder *pFolder, BOOL bFailIfExists)
{
	POS pos = GetHeadPosition();
	CXFileTypePostfix *p = NULL;
	BOOL bTrue = TRUE;
	CString strSrcFile;
	strSrcFile = strFile;
	CString strFolder;
	strFolder = pFolder->GetFolderPath(TRUE);

	while (pos != NULL)
	{
		p = (CXFileTypePostfix *)GetNext(pos);
		strSrcFile = ChangeFilePostfix(strSrcFile, p->m_strID);
		xfile_XCopyFile(strSrcFile, strFolder, bFailIfExists);
	}

	return TRUE;
}

BOOL CXFileType::XOpenXFile(CXFile *pFile)
{
	

	return FALSE;
}

BOOL CXFileType::XDeleteXFile(CXFile *pFile)
{
	POS pos = GetHeadPosition();
	CXFileTypePostfix *p = NULL;
	CString strSrcFile;
	strSrcFile = pFile->GetTotalFileName();

	while (pos != NULL)
	{
		p = (CXFileTypePostfix *)GetNext(pos);
		strSrcFile = ChangeFilePostfix(strSrcFile, p->m_strID);
		X_DeleteFile(strSrcFile);
	}

	return TRUE;
}

BOOL CXFileType::XEditXFile(CXFile *pFile, const CString &strDestName)
{
	POS pos = GetHeadPosition();
	CXFileTypePostfix *p = NULL;
	CString strSrcFile;
	strSrcFile = pFile->GetTotalFileName();
	CString strDestFile;
	strDestFile = GetPathFromFilePathName(strSrcFile);
	strDestFile += strDestName;

	while (pos != NULL)
	{
		p = (CXFileTypePostfix *)GetNext(pos);
		strSrcFile = ChangeFilePostfix(strSrcFile, p->m_strID);
		strDestFile = ChangeFilePostfix(strDestFile, p->m_strID);
#ifndef _PSX_IDE_QT_
		::MoveFile(strSrcFile, strDestFile);
#else
		char* pstrSrcFile,*pstrDestFile;
		CString_to_char(strSrcFile, &pstrSrcFile);
		CString_to_char(strDestFile, &pstrDestFile);
		rename(pstrSrcFile, pstrDestFile);
		delete pstrSrcFile;
		delete pstrDestFile;
#endif
	}

	return TRUE;
}


void CXFileType::GetXFileDlgString(CString &strXFileFilter, CString &strXFilePostFix)
{
	POS pos = GetHeadPosition();

	if (pos == NULL)
	{
		return;
	}

	CXFileTypePostfix *p = NULL;
	CString strTemp;
	p = (CXFileTypePostfix *)GetNext(pos);

    strTemp.Format(_T("%s(*.%s)|*.%s"), p->m_strName.GetString(), p->m_strID.GetString(), p->m_strID.GetString());

	if (strXFilePostFix.GetLength() == 0)
	{
		strXFilePostFix = p->m_strID;
	}

	strXFileFilter += strTemp;
}

BOOL CXFileType::ValidateFilePostfix(const CString &strFilePostfix)
{
	CXFileTypePostfix *p = NULL;
	p = (CXFileTypePostfix *)FindByID(strFilePostfix);

	return (p != NULL);
}

