//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgFile.cpp  CIecCfgFile


#include "stdafx.h"
#include "IecCfgFile.h"

CIecCfgFile::CIecCfgFile()
{
	//初始化属性
	m_strName = _T("NewIecCfgFile");
	m_strID.Empty();

	//初始化成员变量
	m_pIecCfgDatasMngr = new CIecCfgDatasMngr();
#ifndef _PSX_IDE_QT_
	m_pRefFrameWnd = NULL;
#endif
}

CIecCfgFile::~CIecCfgFile()
{
	if (m_pIecCfgDatasMngr != NULL)
	{
		delete m_pIecCfgDatasMngr;
		m_pIecCfgDatasMngr = NULL;
	}
}

long CIecCfgFile::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlReadOwn(oNode, pXmlRWKeys);

	CIecCfgToolXmlRWKeys *pXmlKeys = (CIecCfgToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CIecCfgFile::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);

	CIecCfgToolXmlRWKeys *pXmlKeys = (CIecCfgToolXmlRWKeys*)pXmlRWKeys;

	return 0;
}

void CIecCfgFile::InitAfterRead()
{
}

BOOL CIecCfgFile::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CExBaseObject::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CIecCfgFile *p = (CIecCfgFile*)pObj;

	return TRUE;
}

BOOL CIecCfgFile::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseObject::CopyOwn(pDest);

	CIecCfgFile *p = (CIecCfgFile*)pDest;

	return TRUE;
}

CBaseObject* CIecCfgFile::Clone()
{
	CIecCfgFile *p = new CIecCfgFile();
	Copy(p);
	return p;
}

BOOL CIecCfgFile::IsModified()
{
	ASSERT (m_pIecCfgDatasMngr != NULL);

	return iecfg_IsModified(m_pIecCfgDatasMngr);
}

void CIecCfgFile::SetModified(BOOL bModified)
{
	ASSERT (m_pIecCfgDatasMngr != NULL);

	return iecfg_SetModified(m_pIecCfgDatasMngr, bModified);
}

void CIecCfgFile::CreateDefaultCfgDataMngr()
{
	m_pIecCfgDatasMngr->CreateDefaultCfgDataMngr();
}

BOOL CIecCfgFile::Save(BOOL bIsAT02D_CFG)//周宏军 20200616  增加AT02配置
{
	CExBaseObject *pAncestor = (CExBaseObject *)GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);
	BOOL bRet = FALSE;

	if (pAncestor == NULL)
	{
		ASSERT (m_pIecCfgDatasMngr != NULL);
		bRet = m_pIecCfgDatasMngr->SaveAsIecCfgFile(m_strID,bIsAT02D_CFG);
	}
	else
	{
		bRet = ((CIecCfgFileDevice*)pAncestor)->Save(bIsAT02D_CFG);
	}

	return bRet;
}

BOOL CIecCfgFile::SaveAs(const CString &strFile,BOOL bIsAT02D_CFG)
{
	CExBaseObject *pAncestor = (CExBaseObject *)GetAncestor(IFTCLASSID_CIECCFGFILE_DEVICE);

	if (pAncestor == NULL)
	{
		ASSERT (m_pIecCfgDatasMngr != NULL);
		m_strID = strFile;
		m_strName = GetPathFileNameFromFilePathName(strFile);
// 		CString strTmp;
// 		strTmp = ChangeFileName(strFile,_T("NewAT02D-Cfg"));
// 		CIecCfgDatasMngr *pNewCfgDatas = m_pIecCfgDatasMngr->GetAT02D_IecCfgDatasMngr();
// 		pNewCfgDatas->SaveAsIecCfgFile(strTmp,bIsAT02D_CFG);
// 		delete pNewCfgDatas;

// 		if (!IsFileExist(strFile))
// 		{
// 		}
		m_pIecCfgDatasMngr->m_nVertion = 0;//另存为时,将版本设置为0

		return m_pIecCfgDatasMngr->SaveAsIecCfgFile(strFile,bIsAT02D_CFG);
	}
	else
	{
		return ((CIecCfgFileDevice*)pAncestor)->SaveAs(strFile,bIsAT02D_CFG);
	}
}

BOOL CIecCfgFile::Open(const CString &strFile)
{
	BOOL b = m_pIecCfgDatasMngr->OpenIecCfgFile(strFile);

	if (b)
	{
		m_strID = strFile;
		m_strName = GetLastFolderNameFromPathName(strFile);
	}

	return b;
}

BOOL CIecCfgFile::Open()
{
	CString strPath;
	strPath = _P_GetLibraryPath();
	long nLen = strPath.GetLength();

	if (m_strID.GetLength() <= nLen)
	{
		return FALSE;
	}

	if (!IsFileExist(m_strID))
	{
		return FALSE;
	}

	return Open(m_strID);
}

CString CIecCfgFile::GetName()
{
	if (m_pIecCfgDatasMngr->GetParent() == NULL)
	{
		return m_strName;
	}
	else
	{
		return m_pIecCfgDatasMngr->m_strName;
	}
}


CIecCfgDatasSMV* iecfg_GetIecCfgDatasSMV(CIecCfgFile *pIecCfgFile)
{
	if (pIecCfgFile == NULL)
	{
		return NULL;
	}

	ASSERT (pIecCfgFile->m_pIecCfgDatasMngr != NULL);

	CIecCfgDatasSMV *pDatasSmv = pIecCfgFile->m_pIecCfgDatasMngr->GetSmvMngr();
	ASSERT (pDatasSmv != NULL);

	return pDatasSmv;
}

CIecCfgDatasSmvIn* iecfg_GetIecCfgDatasSmvIn(CIecCfgFile *pIecCfgFile)
{
	if (pIecCfgFile == NULL)
	{
		return NULL;
	}

	ASSERT (pIecCfgFile->m_pIecCfgDatasMngr != NULL);

	CIecCfgDatasSmvIn *pDatasSmvIn = pIecCfgFile->m_pIecCfgDatasMngr->GetSmvInMngr();
	ASSERT (pDatasSmvIn != NULL);

	return pDatasSmvIn;
}

void CIecCfgFile::SetIecCfgSmvRates(CIecCfgSmvRates *pRates)
{
	CIecCfgDatasSMV *pDatasSmv = m_pIecCfgDatasMngr->GetSmvMngr();
	ASSERT (pDatasSmv != NULL);

	CIecCfgSmvRates *pDest = pDatasSmv->GetIecCfgSmvRates();
	pRates->Copy(pDest);
	iecfg_SetModified(pDest);
}

void CIecCfgFile::SetIecCfgSmvCommon(CIecCfgDataSmvCommon *pSmvCommon)
{
	CIecCfgDatasSMV *pDatasSmv = m_pIecCfgDatasMngr->GetSmvMngr();
	ASSERT (pDatasSmv != NULL);

	for (int i=0;i<m_pIecCfgDatasMngr->GetSMVCount();i++)
	{
		CIecCfgDataBase *pCfgData = (CIecCfgDataBase*)m_pIecCfgDatasMngr->GetSmvMngr()->GetIecCfgData(i);
		CIecCfgSmvDataBase *pSmvDataBase = (CIecCfgSmvDataBase*)pCfgData;
		pSmvDataBase->m_nSampleRate = pSmvCommon->m_nSampleRate;

		if (pSmvDataBase->GetClassID() == CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			CIecCfg6044CommonData *pCommonData = (CIecCfg6044CommonData*)pSmvDataBase;
			pCommonData->m_nBaudRate = pSmvCommon->m_nBaudRate;
			pCommonData->m_nDcVol = pSmvCommon->m_nDcVol;
			pCommonData->m_nDcCur = pSmvCommon->m_nDcCur;
			pCommonData->m_nDcNeuatralVol = pSmvCommon->m_nDcNeuatralVol;
			pCommonData->m_dDcVolPrim = pSmvCommon->m_dDcVolPrim;
			pCommonData->m_dDcCurPrim = pSmvCommon->m_dDcCurPrim;
			pCommonData->m_dDcNeutralPrim = pSmvCommon->m_dDcNeutralPrim;

			pCommonData->m_nSCP = pSmvCommon->m_nSCP;
			pCommonData->m_nSCM = pSmvCommon->m_nSCM;
			pCommonData->m_nSV = pSmvCommon->m_nSV;
			pCommonData->m_dInomProt = pSmvCommon->m_dInomProt;
			pCommonData->m_dInomMeas = pSmvCommon->m_dInomMeas;
			pCommonData->m_fUNom = pSmvCommon->m_fUNom;
		}

		pSmvDataBase->m_bNoQuality = pSmvCommon->m_bNoQuality;
	}
	iecfg_SetModified(pSmvCommon);
}

void CIecCfgFile::SetIecfgDataMngr(CIecCfgDatasMngr *pIecfgDataMngr)
{
	if (m_pIecCfgDatasMngr != NULL)
	{
		delete m_pIecCfgDatasMngr;
	}

	m_pIecCfgDatasMngr = pIecfgDataMngr;
}

//////////////////////////////////////////////////////////////////////////
CIecCfgFileDevice::CIecCfgFileDevice()
{
	m_listIecfgFile.SetParent(this);
	m_pIecCfgDevice = new CIecCfgDevice();
	m_pIecCfgDevice->SetParent(this);
}

CIecCfgFileDevice::~CIecCfgFileDevice()
{
	CIecCfgFile *p = NULL, *pFind = NULL;
	POS pos = m_listIecfgFile.GetHeadPosition();

	while (pos != NULL)
	{
		p = (CIecCfgFile *)m_listIecfgFile.GetNext(pos);
		p->m_pIecCfgDatasMngr = NULL;
	}

	delete m_pIecCfgDevice;
	m_pIecCfgDevice = NULL;
}

CIecCfgFile* CIecCfgFileDevice::AddIecfgDataMngr(CIecCfgDatasMngr *pIecfgDataMngr)
{
	CIecCfgFile *pNew = FindIecfgDataMngr(pIecfgDataMngr);

	if (pNew == NULL)
	{
		pNew = new CIecCfgFile();
		pNew->SetIecfgDataMngr(pIecfgDataMngr);
		m_listIecfgFile.AddNewChild(pNew);
	}

	return pNew;
}

CIecCfgFile* CIecCfgFileDevice::FindIecfgDataMngr(CIecCfgDatasMngr *pIecfgDataMngr)
{
	CIecCfgFile *p = NULL, *pFind = NULL;
	POS pos = m_listIecfgFile.GetHeadPosition();

	while (pos != NULL)
	{
		p = (CIecCfgFile *)m_listIecfgFile.GetNext(pos);

		if (p->m_pIecCfgDatasMngr == pIecfgDataMngr)
		{
			pFind = p;
			break;
		}
	}

	return pFind;
}

BOOL CIecCfgFileDevice::DeleteIecfgDataMngr(CIecCfgDatasMngr *pIecfgDataMngr)
{
	CIecCfgFile *pFind = NULL;

	pFind = FindIecfgDataMngr(pIecfgDataMngr);

	if (pFind != NULL)
	{
		m_listIecfgFile.Delete(pFind);
		return TRUE;
	}
	else
	{
		return FALSE;
	}
}

BOOL CIecCfgFileDevice::CloseIecFile(CIecCfgFile *pFile, BOOL bDelete)
{
	if (!bDelete)
	{
		pFile->m_pIecCfgDatasMngr = NULL;
	}

	return m_listIecfgFile.Delete(pFile);
}


BOOL CIecCfgFileDevice::IsModified()
{
	ASSERT (m_pIecCfgDevice != NULL);

	return iecfg_IsModified(m_pIecCfgDevice);
}

void CIecCfgFileDevice::SetModified(BOOL bModified)
{
	ASSERT (m_pIecCfgDevice != NULL);

	return iecfg_SetModified(m_pIecCfgDevice, bModified);
}

BOOL CIecCfgFileDevice::Save(BOOL bIsAT02D_CFG)
{
	ASSERT (m_pIecCfgDevice != NULL);
	m_pIecCfgDevice->SaveAsIecCfgFile(m_strID,bIsAT02D_CFG);

	return TRUE;
}

BOOL CIecCfgFileDevice::SaveAs(const CString &strFile,BOOL bIsAT02D_CFG)
{
	ASSERT (m_pIecCfgDevice != NULL);

	m_strID = strFile;
	m_strName = GetPathFileNameFromFilePathName(strFile);

	return m_pIecCfgDevice->SaveAsIecCfgFile(strFile,bIsAT02D_CFG);
}

BOOL CIecCfgFileDevice::Open(const CString &strFile)
{
	BOOL b = m_pIecCfgDevice->OpenIecCfgFile(strFile);

	if (b)
	{
		m_strID = strFile;
		m_strName = GetLastFolderNameFromPathName(strFile);
	}

	return b;
}

BOOL CIecCfgFileDevice::Open()
{
	CString strPath;
	strPath = _P_GetLibraryPath();
	long nLen = strPath.GetLength();

	if (m_strID.GetLength() <= nLen)
	{
		return FALSE;
	}

	if (!IsFileExist(m_strID))
	{
		return FALSE;
	}

	return Open(m_strID);
}

CIecCfgDatasMngr* CIecCfgFileDevice::CreateIecCfgDatasMngr()
{
	return m_pIecCfgDevice->CreateIecCfgDatasMngr(0);
}

