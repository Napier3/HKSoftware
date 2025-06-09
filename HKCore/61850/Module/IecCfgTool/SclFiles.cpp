//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//SclFiles.cpp  CSclFiles


#include "stdafx.h"
#include "SclFiles.h"

CSclFiles::CSclFiles()
{
	//初始化属性

	//初始化成员变量
	m_pCurrOpenSclFile = NULL;
}

CSclFiles::~CSclFiles()
{
}

long CSclFiles::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecCfgToolXmlRWKeys *pXmlKeys = (CIecCfgToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CSclFiles::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecCfgToolXmlRWKeys *pXmlKeys = (CIecCfgToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CSclFiles::InitAfterRead()
{
}

BOOL CSclFiles::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CSclFiles *p = (CSclFiles*)pObj;

	return TRUE;
}

BOOL CSclFiles::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CSclFiles *p = (CSclFiles*)pDest;

	return TRUE;
}

CBaseObject* CSclFiles::Clone()
{
	CSclFiles *p = new CSclFiles();
	Copy(p);
	return p;
}

CExBaseObject* CSclFiles::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecCfgToolXmlRWKeys *pXmlKeys = (CIecCfgToolXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCSclFileKey)
	{
		pNew = new CSclFile();
	}

	return pNew;
}

CExBaseObject* CSclFiles::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IFTCLASSID_CSCLFILE)
	{
		pNew = new CSclFile();
	}

	return pNew;
}

CSclFile* CSclFiles::Open()
{
	CFileDialog FileDialog(TRUE,NULL,NULL,OFN_HIDEREADONLY,
		_T("icd,cid,scd (*.icd;*.cid;*.scd)| *.icd;*.cid;*.scd|icd (*.icd)|*.icd|cid (*.cid)|*.cid|scd (*.scd)|*.scd||"));

	UINT nRet = FileDialog.DoModal();

	if (IDOK != nRet)
	{
		return NULL;
	}

	CString strPath = FileDialog.GetPathName();
	BOOL bICD=TRUE;
	CString strTemp = strPath.Right(3);
	strTemp.MakeLower();

	if (strTemp != _T("icd") && strTemp !=_T("scd") && strTemp != _T("cid"))
	{
		return NULL;
	}

	return Open(strPath);
}

CSclFile* CSclFiles::Open(const CString &strSclFile)
{
	CSclFile *pSclFile = (CSclFile*)FindByID(strSclFile);

	if (pSclFile != NULL)
	{
		if (pSclFile->GetRefFrameWnd() == NULL)
		{
			pSclFile->Open(strSclFile);
		}
	}
	else
	{
		pSclFile = new CSclFile();
		pSclFile->Open(strSclFile);
		AddNewChild(pSclFile);
	}

	m_pCurrOpenSclFile = pSclFile;

	return pSclFile;
}

BOOL CSclFiles::FreeSclFileRead(CSclFile *pSclFile)
{
	m_pCurrOpenSclFile = NULL;
	return TRUE;
}

