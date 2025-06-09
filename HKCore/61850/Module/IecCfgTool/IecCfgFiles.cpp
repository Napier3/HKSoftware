//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgFiles.cpp  CIecCfgFiles


#include "stdafx.h"
#include "IecCfgFiles.h"

CIecCfgFiles::CIecCfgFiles()
{
	//初始化属性

	//初始化成员变量
	m_nViewOnlyUsedInChs = 0;
	m_nViewChsPath = 0;
}

CIecCfgFiles::~CIecCfgFiles()
{
}

long CIecCfgFiles::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecCfgToolXmlRWKeys *pXmlKeys = (CIecCfgToolXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strViewOnlyUsedInChsKey, oNode, m_nViewOnlyUsedInChs);
	xml_GetAttibuteValue(pXmlKeys->m_strViewChsPathKey, oNode, m_nViewChsPath);

	return 0;
}

long CIecCfgFiles::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecCfgToolXmlRWKeys *pXmlKeys = (CIecCfgToolXmlRWKeys*)pXmlRWKeys;
	xml_SetAttributeValue(pXmlKeys->m_strViewOnlyUsedInChsKey, oElement, m_nViewOnlyUsedInChs);
	xml_SetAttributeValue(pXmlKeys->m_strViewChsPathKey, oElement, m_nViewChsPath);

	return 0;
}

void CIecCfgFiles::InitAfterRead()
{
}

BOOL CIecCfgFiles::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	if (m_nViewOnlyUsedInChs != ((CIecCfgFiles*)pObj)->m_nViewOnlyUsedInChs)
	{
		return FALSE;
	}

	if (m_nViewChsPath != ((CIecCfgFiles*)pObj)->m_nViewChsPath)
	{
		return FALSE;
	}

	CIecCfgFiles *p = (CIecCfgFiles*)pObj;

	return TRUE;
}

BOOL CIecCfgFiles::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecCfgFiles *p = (CIecCfgFiles*)pDest;
	p->m_nViewOnlyUsedInChs = m_nViewOnlyUsedInChs;
	p->m_nViewChsPath = m_nViewChsPath;

	return TRUE;
}

CBaseObject* CIecCfgFiles::Clone()
{
	CIecCfgFiles *p = new CIecCfgFiles();
	Copy(p);
	return p;
}

CExBaseObject* CIecCfgFiles::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CIecCfgToolXmlRWKeys *pXmlKeys = (CIecCfgToolXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgFileKey)
	{
		pNew = new CIecCfgFile();
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgFileDeviceKey)
	{
		pNew = new CIecCfgFileDevice();
	}

	return pNew;
}

CExBaseObject* CIecCfgFiles::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;


	if (nClassID == IFTCLASSID_CIECCFGFILE)
	{
		pNew = new CIecCfgFile();
	}

	return pNew;
}


//////////////////////////////////////////////////////////////////////////
void CIecCfgFiles::AdjustIecCfgFile(CIecCfgFile *pIecfgFile)
{
	if (pIecfgFile->GetClassID() != IFTCLASSID_CIECCFGFILE_DEVICE)//.CIecCfgFileDevice类
	{
		return;
	}

	POS pos = GetHeadPosition();
	CIecCfgFile *pFile = NULL;
	BOOL bModified = FALSE;
	CExBaseList listTemp;
	POS posPrev = pos;

	while (pos != NULL)
	{
		posPrev = pos;
		pFile = (CIecCfgFile *)GetNext(pos);

		if (pFile->GetClassID() == IFTCLASSID_CIECCFGFILE_DEVICE)
		{
			if (pIecfgFile != pFile)//如果静态变量g_pIecCfgTool的成员变量m_pIecCfgFiles中的基类中的data与pIecfgFile不一致，将其移除，将值存放在listTemp中；
			{
				RemoveAt(posPrev);//移除一个CNode，但是Date中的值还在；
				listTemp.AddTail(pFile);//将值存放在listTemp中；
			}
		}
	}
}


CIecCfgFile* CIecCfgFiles::NewIecCfgFile(const CString &strFileType)
{
	CIecCfgFile *pRet = NULL;

	if (strFileType == g_strIecCfgFilePostfix)
	{
		pRet = new CIecCfgFile();
		pRet->CreateDefaultCfgDataMngr();
		AddNewChild(pRet, TRUE);
	}
	else
	{
		CIecCfgFileDevice *pNew = new CIecCfgFileDevice();
		pNew->CreateIecCfgDatasMngr();
		AddNewChild(pNew, TRUE);
		pRet = pNew;
	}

	AdjustIecCfgFile(pRet);

	return pRet;
}

BOOL CIecCfgFiles::IsIecFileOpen(const CString &strFile)
{
	CIecCfgFile *pFile = (CIecCfgFile*)FindByID(strFile);

	return (pFile != NULL);
}

CIecCfgFile* CIecCfgFiles::OpenIecFile(const CString &strFile)
{
	CIecCfgFile *pFile = (CIecCfgFile*)FindByID(strFile);

	if (pFile != NULL)
	{
// 		if (pFile->m_pIecCfgDatasMngr == NULL)
// 		{
// 			if (!pFile->Open(strFile))
// 			{
// 				Delete(pFile);
// 				pFile = NULL;
// 			}
// 		}

		return pFile;
	}

	CString strFilePostfix = ParseFilePostfix(strFile);
	strFilePostfix.MakeLower();

	if (strFilePostfix == g_strIecCfgFilePostfix)
	{
		pFile = new CIecCfgFile();
	}
	else if(strFilePostfix == g_strDeviceIecCfgFilePostfix)
	{
		pFile = new CIecCfgFileDevice();
	}
	else
	{
		pFile = new CIecCfgFile();
	}
	
	if (pFile->Open(strFile))
	{
		AddNewChild(pFile, FALSE);
	}
	else
	{
		delete pFile;
		pFile = NULL;
	}

	return pFile;
}

BOOL CIecCfgFiles::CloseIecFile(CIecCfgFile *pFile, BOOL bDelete)
{
	CExBaseObject *pParent = (CExBaseObject*)pFile->GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);

	if (pParent == NULL)
	{
		return Delete(pFile);
	}
	
	CIecCfgFileDevice *pIecCfgFileDevice = (CIecCfgFileDevice*)pParent;

	if (pIecCfgFileDevice == pFile)
	{
		return Delete(pFile);
	}
	else
	{
		return pIecCfgFileDevice->CloseIecFile(pFile, bDelete);
	}
}

BOOL CIecCfgFiles::SaveIecFile(CIecCfgFile *pFile)
{
	return FALSE;
}

BOOL CIecCfgFiles::SaveAsIecFile(CIecCfgFile *pFile)
{
	return FALSE;
}

BOOL CIecCfgFiles::HasIecCfgFileModified(CString &strFiles)
{
	POS pos = GetHeadPosition();
	CIecCfgFile *pFile = NULL;
	BOOL bModified = FALSE;

	while (pos != NULL)
	{
		pFile = (CIecCfgFile *)GetNext(pos);

		if (pFile->IsModified())
		{
			bModified = TRUE;
			strFiles.AppendFormat(_T("\"%s\" "), pFile->m_strName);
		}
	}

	return bModified;
}

BOOL CIecCfgFiles::HasFileInFolder(const CString &strFolder)
{
	POS pos = GetHeadPosition();
	CIecCfgFile *pFile = NULL;
	BOOL bModified = FALSE;
	BOOL bHas = FALSE;

	while (pos != NULL)
	{
		pFile = (CIecCfgFile *)GetNext(pos);

		if (pFile->m_strID.Find(strFolder) == 0)
		{
			bHas = TRUE;
			break;
		}
	}

	return bHas;
}

void CIecCfgFiles::SetIecCfgSmvRates(CIecCfgSmvRates *pRates, CIecCfgFile *pFile)
{
	if (pFile != NULL)
	{
		pFile->SetIecCfgSmvRates(pRates);
	}
	else
	{
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pFile = (CIecCfgFile *)GetNext(pos);
			pFile->SetIecCfgSmvRates(pRates);
		}
	}
}

void CIecCfgFiles::SetIecCfgSmvCommon(CIecCfgDataSmvCommon *pSmvCommon, CIecCfgFile *pFile)
{
	if (pFile != NULL)
	{
		pFile->SetIecCfgSmvCommon(pSmvCommon);
	}
	else
	{
		POS pos = GetHeadPosition();

		while (pos != NULL)
		{
			pFile = (CIecCfgFile *)GetNext(pos);
			pFile->SetIecCfgSmvCommon(pSmvCommon);
		}
	}
}

