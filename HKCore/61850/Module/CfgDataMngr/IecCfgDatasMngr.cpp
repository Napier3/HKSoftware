//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasMngr.cpp  CIecCfgDatasMngr


#include "stdafx.h"
#include "IecCfgDatasMngr.h"
#include "IecCfgSmvInDatas.h"
#include "../../../Module/API/GlobalConfigApi.h"

#ifdef _use_COnllyCfgFileTool
#include "../OnllyCfgTool/OnllyCfgFileTool.h"
#endif

#ifndef _PSX_IDE_QT_
#include "IecCfgDevice.h"
#endif

#ifndef NOT_USE_XLANGUAGE
#include "../XLanguageResourceIec.h"
#endif

CIecCfgDatasMngr::CIecCfgDatasMngr()
{
	//初始化属性
// 	m_nEnableSMV = 0;
// 	m_nEnableGIN = 0;
// 	m_nEnableGOUT = 0;
	m_nVertion = 0;
	m_strDate = "";

	//初始化成员变量
	m_pGinMngr = NULL;
	m_pSmvMngr = NULL;
	m_pSmvInMngr = NULL;
	m_pGoutMngr = NULL;
	m_pSysParasMngr = NULL;

//	m_pSmvInputMngr = NULL;
	m_nDeviceID = 1;
// 	m_pArtAmpDigdatas = NULL;
//	m_pAnalogMngr = NULL;
// 	m_nEnableAnalog = FALSE;

	m_bModified = FALSE;

#ifdef NOT_USE_XLANGUAGE
    m_strName = _T("IEC61850配置");
#else
	m_strName = g_sLangTxt_Iec61850Config/*_T("IEC61850配置")*/;
#endif
	m_strID = _T("IEC61850CFG");
}

void CIecCfgDatasMngr::InitCfgDataMngr()
{
	DeleteAll();
	InitDatasMngr();
// 	m_nEnableSMV = 1;
// 	m_nEnableGIN = 0;
// 	m_nEnableGOUT = 0;

	GetSmvMngr();
	GetGinMngr();
	GetGoutMngr();
	GetSysParasMngr();

//	GetSmvInputMngr();

 	m_pSmvMngr->SetDataUse(1, 1);
	m_pSmvInMngr->SetDataUse(1, 1);

//	m_pSmvInputMngr->SetDataUse(1,1);
// 	m_pGinMngr->SetDataUse(1, 1);
//	m_pGoutMngr->SetDataUse(1, 1);
//	m_pAnalogMngr->SetDataUse(1, 1);
//	InitArtAmpDigdatas();
//	m_pSmvMngr->SetCount(2, oList);

// 	m_oIecCfgSystemConfig.Open();
// 	CString strFile = m_oIecCfgSystemConfig.GetInitFile();
// 
// 	if (strFile.GetLength() > 0)
// 	{
// 		OpenIecCfgFile(strFile);
// 	}
}

void CIecCfgDatasMngr::CreateDefaultCfgDataMngr(long nCfgDataCount)
{
	DeleteAll();

	m_pGinMngr = NULL;
	m_pSmvMngr = NULL;
	m_pSmvInMngr = NULL;
	m_pGoutMngr = NULL;
	m_pSysParasMngr = NULL;

//	m_pSmvInputMngr = NULL;
//	m_pAnalogMngr = NULL;
// 	m_nEnableSMV = 1;
// 	m_nEnableGIN = 0;
// 	m_nEnableGOUT = 0;

	GetSmvInMngr();
	GetSmvMngr();
	GetGinMngr();
	GetGoutMngr();
	GetSysParasMngr();
///	GetAnalogMngr();
//	GetSmvInputMngr();

 	m_pSmvMngr->SetDataUse(1, nCfgDataCount);
	m_pSmvInMngr->SetDataUse(1, nCfgDataCount);
	m_pGinMngr->SetDataUse(1, nCfgDataCount);
	m_pGoutMngr->SetDataUse(1, nCfgDataCount);

//	m_pSmvInputMngr->SetDataUse(1,nCfgDataCount);

	CIecCfgDataBase *pData = m_pSmvMngr->GetIecCfgData(0);

	if (pData != NULL)
	{
		pData->m_nUseFlag = 1;
	}

	pData = m_pSmvInMngr->GetIecCfgData(0);

	if (pData != NULL)
	{
		pData->m_nUseFlag = 1;
	}

	pData = m_pGinMngr->GetIecCfgData(0);

	if (pData != NULL)
	{
		pData->m_nUseFlag = 1;
	}

	pData = m_pGoutMngr->GetIecCfgData(0);

	if (pData != NULL)
	{
		pData->m_nUseFlag = 1;
	}

//	pData = m_pSmvInputMngr->GetIecCfgData(0);

	if (pData != NULL)
	{
		pData->m_nUseFlag = 1;
	}

	m_pGinMngr->InitAfterRead();
//	m_pAnalogMngr->SetDataUse(1, 1);
//	InitArtAmpDigdatas();
//	m_pSmvMngr->SetCount(2, oList);
//	m_oIecCfgSystemConfig.SetLaIecCfgFile(_T(""));
}

void CIecCfgDatasMngr::InitDatasMngr()
{
	m_pGinMngr = NULL;
	m_pSmvMngr = NULL;
	m_pSmvInMngr = NULL;
	m_pGoutMngr = NULL;
	m_pSysParasMngr = NULL;

//	m_pSmvInputMngr = NULL;
//	m_pAnalogMngr = NULL;
}

CIecCfgDatasMngr::~CIecCfgDatasMngr()
{
	//delete m_pArtAmpDigdatas;
}

long CIecCfgDatasMngr::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlReadOwn(oNode, pXmlRWKeys);

	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	xml_GetAttibuteValue(pXmlKeys->m_strIcdFileKey, oNode, m_strScdFile);
	xml_GetAttibuteValue(pXmlKeys->m_strGinChMapFileNameKey, oNode, m_strGinChMapFileName);
	xml_GetAttibuteValue(pXmlKeys->m_strDateKey, oNode, m_strDate);


// 	xml_GetAttibuteValue(pXmlKeys->m_strEnableSMVKey, oNode, m_nEnableSMV);
// 	xml_GetAttibuteValue(pXmlKeys->m_strEnableGINKey, oNode, m_nEnableGIN);
// 	xml_GetAttibuteValue(pXmlKeys->m_strEnableGOUTKey, oNode, m_nEnableGOUT);
	return 0;
}

long CIecCfgDatasMngr::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseList::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIcdFileKey, oElement, m_strScdFile);
	xml_SetAttributeValue(pXmlKeys->m_strGinChMapFileNameKey, oElement, m_strGinChMapFileName);
	xml_SetAttributeValue(pXmlKeys->m_strDateKey, oElement, m_strDate);
// 	xml_SetAttributeValue(pXmlKeys->m_strEnableSMVKey, oElement, m_nEnableSMV);
// 	xml_SetAttributeValue(pXmlKeys->m_strEnableGINKey, oElement, m_nEnableGIN);
// 	xml_SetAttributeValue(pXmlKeys->m_strEnableGOUTKey, oElement, m_nEnableGOUT);
	return 0;
}

BOOL CIecCfgDatasMngr::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfgDatasMngr *p = (CIecCfgDatasMngr*)pObj;

	if(m_strScdFile != p->m_strScdFile)
	{
		return FALSE;
	}

	if(m_strGinChMapFileName != p->m_strGinChMapFileName)
	{
		return FALSE;
	}

	if(m_strDate != p->m_strDate)
	{
		return FALSE;
	}

	return TRUE;
}

BOOL CIecCfgDatasMngr::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CExBaseList::CopyOwn(pDest);
	CIecCfgDatasMngr *p = (CIecCfgDatasMngr*)pDest;

// 	p->m_nEnableSMV = m_nEnableSMV;
// 	p->m_nEnableGIN = m_nEnableGIN;
// 	p->m_nEnableGOUT = m_nEnableGOUT;
	p->m_strScdFile = m_strScdFile;
	p->m_strGinChMapFileName = m_strGinChMapFileName;
	p->m_strDate = m_strDate;
	return TRUE;
}

CBaseObject* CIecCfgDatasMngr::Clone()
{
	CIecCfgDatasMngr *p = new CIecCfgDatasMngr();
	Copy(p);
	return p;
}

CBaseObject* CIecCfgDatasMngr::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
    CIecCfgDatasMngr *p = new CIecCfgDatasMngr();
    CopyEx(p, bCopyOwn, bCopyChildren);
    return p;
}

void CIecCfgDatasMngr::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	UINT nClassID = 0;

	while (pos != NULL)
	{
		p = GetNext(pos);
		nClassID = p->GetClassID();

		if (nClassID == CFGCLASSID_CIECCFGDATASGIN)
		{
			m_pGinMngr = (CIecCfgGinDatas*)p;
		}
		else if (nClassID == CFGCLASSID_CIECCFGDATASSMV)
		{
			m_pSmvMngr = (CIecCfgDatasSMV*)p;
		}
		else if (nClassID == CFGCLASSID_CIECCFGDATASGOUT)
		{
			m_pGoutMngr = (CIecCfgGoutDatas*)p;
		}
		else if (nClassID == CFGCLASSID_CIECCFGSYSPARAS)
		{
			m_pSysParasMngr = (CIecCfgSysParas *)p;
		}
 		else if (nClassID == CFGCLASSID_CIECCFGDATASSMVINPUT)
 		{
 			m_pSmvInMngr = (CIecCfgDatasSmvIn*)p;
 		}
	}
}

CExBaseObject* CIecCfgDatasMngr::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;


	if (strClassID == pXmlKeys->m_strCIecCfgDatasSMVKey)
	{
		if (m_pSmvMngr == NULL)
		{
			m_pSmvMngr = new CIecCfgDatasSMV();
			return m_pSmvMngr;
		}
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgDatasSmvInKey)
	{
		if (m_pSmvInMngr == NULL)
		{
			m_pSmvInMngr = new CIecCfgDatasSmvIn();
			return m_pSmvInMngr;
		}
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgDatasGinKey)
	{
		if (m_pGinMngr == NULL)
		{
			m_pGinMngr = new CIecCfgGinDatas();
			return m_pGinMngr;
		}
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgDatasGoutKey)
	{
		if (m_pGoutMngr == NULL)
		{
			m_pGoutMngr = new CIecCfgGoutDatas();
			return m_pGoutMngr;
		}
	}
	else if (strClassID == pXmlKeys->m_strCIecCfgSysParasKey)
	{
		if (m_pSysParasMngr == NULL)
		{
			m_pSysParasMngr = new CIecCfgSysParas();
			return m_pSysParasMngr;
		}
	}
// 	else if (strClassID == pXmlKeys->m_strCIecCfgDatasSMVInputKey)
// 	{
// 		if (m_pSmvInputMngr == NULL)
// 		{
// 			m_pSmvInputMngr = new CIecCfgDatasSMVInput();
// 			return m_pSmvInputMngr;
// 		}
// 	}
// 	else if (strClassID == pXmlKeys->m_strCIecCfgDatasAnalogKey)
// 	{
// 		if (m_pAnalogMngr == NULL)
// 		{
// 			m_pAnalogMngr = new CIecCfgDatasAnalog();
// 			return m_pAnalogMngr;
// 		}
// 	}

	return pNew;
}


CIecCfgGinDatas* CIecCfgDatasMngr::GetGinMngr()
{
	if (m_pGinMngr == NULL)
	{
		m_pGinMngr = (CIecCfgGinDatas*)AddNewChild(new CIecCfgGinDatas());
	}

	return m_pGinMngr;
}

CIecCfgDatasSMV* CIecCfgDatasMngr::GetSmvMngr()
{
	if (m_pSmvMngr == NULL)
	{
		m_pSmvMngr = (CIecCfgDatasSMV*)AddNewChild(new CIecCfgDatasSMV());
	}

	return m_pSmvMngr;
}

CIecCfgDatasSmvIn* CIecCfgDatasMngr::GetSmvInMngr()
{
	if (m_pSmvInMngr == NULL)
	{
		m_pSmvInMngr = (CIecCfgDatasSmvIn *)AddNewChild(new CIecCfgDatasSmvIn());
	}

	return m_pSmvInMngr;
}

CIecCfgSysParas* CIecCfgDatasMngr::GetSysParasMngr()
{
	if (m_pSysParasMngr == NULL)
	{
		m_pSysParasMngr = (CIecCfgSysParas*)AddNewChild(new CIecCfgSysParas());
	}

	return m_pSysParasMngr;
}

CIecCfgGoutDatas* CIecCfgDatasMngr::GetGoutMngr()
{
	if (m_pGoutMngr == NULL)
	{
		m_pGoutMngr = (CIecCfgGoutDatas*)AddNewChild(new CIecCfgGoutDatas());
	}

	return m_pGoutMngr;
}

// CIecCfgDatasSMVInput* CIecCfgDatasMngr::GetSmvInputMngr()
// {
// 	if (m_pSmvInputMngr == NULL)
// 	{
// 		m_pSmvInputMngr = (CIecCfgDatasSMVInput*)AddNewChild(new CIecCfgDatasSMVInput());
// 	}
// 
// 	return m_pSmvInputMngr;
// }
// 
// CArtAmpDigdatas* CIecCfgDatasMngr::GetArtAmpDigdatas()
// {
// // 	if (m_pArtAmpDigdatas == NULL)
// // 	{
// // 		InitArtAmpDigdatas();
// // 	}
// 
// 	return m_pArtAmpDigdatas;
// }
// 
// void CIecCfgDatasMngr::SaveArtAmpDigdatasTemp()
// {
// // 	if (m_pArtAmpDigdatas != NULL)
// // 	{
// // 		m_pArtAmpDigdatas->SaveTempFile();
// // 	}
// }
// 
// void CIecCfgDatasMngr::CalArtAmpDigdatas()
// {
// 	if (m_pArtAmpDigdatas == NULL)
// 	{
// 		return;
// 	}
// 
// 	ResetArtAmpDigdatas();
// 
// 	CExBaseList oList;
// 	GetIecCfgSmvDatas(oList, FALSE);
// 	CalArtAmpDigdatas(oList);
// 	oList.RemoveAll();
// 
// // 	GetIecCfgGinDatas(oList);
// // 	CalArtAmpDigdatas(oList);
// // 	oList.RemoveAll();
// // 
// // 	GetIecCfgGoutDatas(oList);
// // 	CalArtAmpDigdatas(oList);
// // 	oList.RemoveAll();
// 
// 	GetIecCfgAnalogDatas(oList);
// 	CalArtAmpDigdatas(oList);
// 	oList.RemoveAll();
// }
// 
// void CIecCfgDatasMngr::CalArtAmpDigdatas(CExBaseList &oList)
// {
// 	POS pos = oList.GetHeadPosition();
// 	CIecCfgDataBase *pCfgData = NULL;
// 	long nHdCnIndex = 0;
// 
// 	while (pos != NULL)
// 	{
// 		pCfgData = (CIecCfgDataBase *)GetNext(pos);
// 		pCfgData->CalArtAmpDigdatas(m_pArtAmpDigdatas, nHdCnIndex);
// 	}
// }
// 
// CArtAmpDigdatas* CIecCfgDatasMngr::InitArtAmpDigdatas()
// {
// 	if (m_pArtAmpDigdatas == NULL)
// 	{
// 		m_pArtAmpDigdatas = new CArtAmpDigdatas();
// 		m_pArtAmpDigdatas->ReadFromFile();
// 	}
// 
// 	return m_pArtAmpDigdatas;
// }
// 
// long CIecCfgDatasMngr::GetCfgDatasEnableCount()
// {
// 	return GetEnableSMV() + GetEnableGIN() + GetEnableGOUT()+GetEnableAnalog();
// }

long CIecCfgDatasMngr::GetEnableSMV()
{
	CIecCfgDatasBase *pMngr = GetSmvMngr();
	return pMngr->GetDataUse();
}

long CIecCfgDatasMngr::GetEnableGIN()
{
	CIecCfgDatasBase *pMngr = GetGinMngr();
	return pMngr->GetDataUse();
}

long CIecCfgDatasMngr::GetEnableGOUT()
{
	CIecCfgDatasBase *pMngr = GetGoutMngr();
	return pMngr->GetDataUse();
}

// long CIecCfgDatasMngr::GetEnableSMVInput()
// {
// 	CIecCfgDatasBase *pMngr = GetSmvInputMngr();
// 	return pMngr->GetDataUse();
// }

void  CIecCfgDatasMngr::SetEnableSMV(long nEnable)
{
	nEnable = ValidateEnable(nEnable);
	CIecCfgDatasBase *pMngr = GetSmvMngr();
	pMngr->SetDataUse(nEnable, 1);
}

void  CIecCfgDatasMngr::SetEnableGIN(long nEnable)
{
	nEnable = ValidateEnable(nEnable);
	CIecCfgDatasBase *pMngr = GetGinMngr();
	pMngr->SetDataUse(nEnable, 1);
}

void  CIecCfgDatasMngr::SetEnableGOUT(long nEnable)
{
	nEnable = ValidateEnable(nEnable);
	CIecCfgDatasBase *pMngr = GetGoutMngr();
	pMngr->SetDataUse(nEnable, 1);
}

// void  CIecCfgDatasMngr::SetEnableSMVInput(long nEnable)
// {
// 	nEnable = ValidateEnable(nEnable);
// 	CIecCfgDatasBase *pMngr = GetSmvInputMngr();
// 	pMngr->SetDataUse(nEnable, 1);
// }

long  CIecCfgDatasMngr::GetSMVCount()
{
	CIecCfgDatasBase *pMngr = GetSmvMngr();
	return pMngr->GetCfgDataCount();
}

long  CIecCfgDatasMngr::GetGINCount()
{
	CIecCfgDatasBase *pMngr = GetGinMngr();
	return pMngr->GetCfgDataCount();
}

long  CIecCfgDatasMngr::GetGOUTCount()
{
	CIecCfgDatasBase *pMngr = GetGoutMngr();
	return pMngr->GetCfgDataCount();
}

long CIecCfgDatasMngr::GetParasSetSel()
{
	CIecCfgSysParas* pIecCfgSysParas = GetSysParasMngr();
	return pIecCfgSysParas->m_nPrimParas;
}

long CIecCfgDatasMngr::GetPrimOutput()
{
	CIecCfgSysParas* pIecCfgSysParas = GetSysParasMngr();
	return pIecCfgSysParas->m_nPrimOutput;
}

// long  CIecCfgDatasMngr::GetSMVInputCount()
// {
// 	CIecCfgDatasBase *pMngr = GetSmvInputMngr();
// 	return pMngr->GetCfgDataCount();
// }

BOOL CIecCfgDatasMngr::SetSMVCount(long nCount, CExBaseList &oListTemp)
{
	return SetCfgDataCount(GetSmvMngr(), nCount, oListTemp);
// 	CIecCfgDatasSMV *pSmvMngr = GetSmvMngr();
// 	long nCountOld = pSmvMngr->GetCfgDataCount();
// 
// 	if (nCountOld == nCount)
// 	{
// 		return FALSE;
// 	}
// 
// 	pSmvMngr->SetCount(nCount, oListTemp);
// 
// 	return TRUE;
}

BOOL CIecCfgDatasMngr::SetGINCount(long nCount, CExBaseList &oListTemp)
{
	return SetCfgDataCount(GetGinMngr(), nCount, oListTemp);
}

BOOL CIecCfgDatasMngr::SetGOUTCount(long nCount, CExBaseList &oListTemp)
{
	return SetCfgDataCount(GetGoutMngr(), nCount, oListTemp);
}

void CIecCfgDatasMngr::SetFiber2IndexByFiberIndex(long nOffset)
{
	if (m_pSmvMngr != NULL)
	{
		m_pSmvMngr->SetFiber2IndexByFiberIndex(nOffset);
	}

	if (m_pSmvInMngr != NULL)
	{
		m_pSmvInMngr->SetFiber2IndexByFiberIndex(nOffset);
	}

	if (m_pGinMngr != NULL)
	{
		m_pGinMngr->SetFiber2IndexByFiberIndex(nOffset);
	}

	if (m_pGoutMngr != NULL)
	{
		m_pGoutMngr->SetFiber2IndexByFiberIndex(nOffset);
	}
}

// BOOL CIecCfgDatasMngr::SetSMVInputCount(long nCount, CExBaseList &oListTemp)
// {
// 	return SetCfgDataCount(GetSmvInputMngr(), nCount, oListTemp);
// }

CIecCfgDataBase* CIecCfgDatasMngr::CreateNewSmvCfgData()
{
// 	m_nEnableSMV = 1;
	CIecCfgDatasSMV *pSmvMngr = GetSmvMngr();
	CIecCfgDataBase *pIecCfg = NULL;
	
	if (pSmvMngr->GetDataUse())
	{
		pIecCfg = (CIecCfgDataBase*)pSmvMngr->CreateIecCfgData();
		pIecCfg->OpenCfgDefaultConfigFile();
		pSmvMngr->AddNewChild(pIecCfg);
	}
	else
	{
		pSmvMngr->SetDataUse(1, 1);
		pIecCfg = (CIecCfgDataBase*)pSmvMngr->GetIecCfgData(0);
	}
	
	return pIecCfg;
}

CIecCfgDataBase* CIecCfgDatasMngr::CreateNewSmvInCfgData()
{
// 	m_nEnableSMV = 1;
	CIecCfgDatasSmvIn *pSmvInMngr = GetSmvInMngr();
	CIecCfgDataBase *pIecCfg = NULL;
	
	if (pSmvInMngr->GetDataUse())
	{
		pIecCfg = (CIecCfgDataBase*)pSmvInMngr->CreateIecCfgData();
		pIecCfg->OpenCfgDefaultConfigFile();
		pSmvInMngr->AddNewChild(pIecCfg);
	}
	else
	{
		pSmvInMngr->SetDataUse(1, 1);
		pIecCfg = (CIecCfgDataBase*)pSmvInMngr->GetIecCfgData(0);
	}
	
	return pIecCfg;
}

// CIecCfgDataBase* CIecCfgDatasMngr::CreateNewSmvInputCfgData()
// {
// 	CIecCfgDatasSMVInput *pSmvInputMngr = GetSmvInputMngr();
// 	CIecCfgDataBase *pIecCfg = NULL;
// 
// 	if (pSmvInputMngr->GetDataUse())
// 	{
// 		pIecCfg = (CIecCfgDataBase*)pSmvInputMngr->CreateIecCfgData();
// 		pIecCfg->OpenCfgDefaultConfigFile();
// 		pSmvInputMngr->AddNewChild(pIecCfg);
// 	}
// 	else
// 	{
// 		pSmvInputMngr->SetDataUse(1, 1);
// 		pIecCfg = (CIecCfgDataBase*)pSmvInputMngr->GetIecCfgData(0);
// 	}
// 	return pIecCfg;
// }


CIecCfgDataBase* CIecCfgDatasMngr::CreateNewGinCfgData()
{
	CIecCfgGinDatas *pGinMngr = GetGinMngr();
	CIecCfgDataBase *pIecCfg = NULL;
	
	if (pGinMngr->GetDataUse())
	{
		pIecCfg = pGinMngr->CreateIecCfgData();
		pIecCfg->OpenCfgDefaultConfigFile();
		pGinMngr->AddNewChild(pIecCfg);
	}
	else
	{
		pGinMngr->SetDataUse(1, 1);
		pIecCfg = (CIecCfgDataBase*)pGinMngr->GetIecCfgData(0);
	}

	return pIecCfg;
}

CIecCfgDataBase* CIecCfgDatasMngr::CreateNewGoutCfgData()
{
	CIecCfgGoutDatas *pGoutMngr = GetGoutMngr();
	CIecCfgDataBase *pIecCfg = NULL;
	
	if (pGoutMngr->GetDataUse())
	{
		pIecCfg = pGoutMngr->CreateIecCfgData();
		pIecCfg->OpenCfgDefaultConfigFile();
		pGoutMngr->AddNewChild(pIecCfg);
	}
	else
	{
		pGoutMngr->SetDataUse(1, 1);
		pIecCfg = (CIecCfgDataBase*)pGoutMngr->GetIecCfgData(0);
	}

	return pIecCfg;
}

CIecCfgDataBase* CIecCfgDatasMngr::GetSmvCfgData(long nIndex)
{
	CExBaseList oList;
	GetIecCfgSmvDatas(oList, FALSE);
	CIecCfgDataBase *pFind = (CIecCfgDataBase*)oList.GetAtIndex(nIndex);
	oList.RemoveAll();
	return pFind;
}

CIecCfgDataBase* CIecCfgDatasMngr::GetGinCfgData(long nIndex)
{
	CExBaseList oList;
	GetIecCfgGinDatas(oList);
	CIecCfgDataBase *pFind = (CIecCfgDataBase*)oList.GetAtIndex(nIndex);
	oList.RemoveAll();
	return pFind;
}

CIecCfgDataBase* CIecCfgDatasMngr::GetGoutCfgData(long nIndex)
{
	CExBaseList oList;
	GetIecCfgGoutDatas(oList);
	CIecCfgDataBase *pFind = (CIecCfgDataBase*)oList.GetAtIndex(nIndex);
	oList.RemoveAll();
	return pFind;
}

BOOL CIecCfgDatasMngr::SetCfgDataCount(CIecCfgDatasBase *pCfgDatas, long nCount, CExBaseList &oListTemp)
{
	long nCountOld = pCfgDatas->GetCfgDataCount();

	if (nCountOld == nCount)
	{
		return FALSE;
	}

	pCfgDatas->SetCount(nCount, oListTemp);

	return TRUE;
}

long CIecCfgDatasMngr::GetSmvType()
{
	if (m_pSmvMngr == NULL)
	{
		return 0;
	}

	return m_pSmvMngr->GetSmvType();
}

BOOL CIecCfgDatasMngr::SetSmvType(long nSmvType)
{
	CIecCfgDatasSMV *pSmvMngr = GetSmvMngr();
	return pSmvMngr->SetSmvType(nSmvType);
}

long CIecCfgDatasMngr::GetSmvInType()
{
	if (m_pSmvInMngr == NULL)
	{
		return 0;
	}

	return m_pSmvInMngr->GetSmvType();
}

BOOL CIecCfgDatasMngr::SetSmvInType(long nSmvType)
{
	CIecCfgDatasSmvIn *pSmvInMngr = GetSmvInMngr();
	return pSmvInMngr->SetSmvType(nSmvType);
}

void CIecCfgDatasMngr::GetIecCfgSmvDatas(CExBaseList &oList, BOOL bGetCommon)
{
	if (m_pSmvMngr != NULL)
	{
		if ( (m_pSmvMngr->GetCfgDataCount() > 0) && (m_pSmvMngr->GetDataUse() > 0) && bGetCommon)
		{
			oList.AddTail(m_pSmvMngr->GetCommonData());
		}

		m_pSmvMngr->GetIecCfgDatas(oList);
	}

}

void CIecCfgDatasMngr::GetIecCfgSmvInDatas(CExBaseList &oList, BOOL bGetCommon)
{
	if (m_pSmvInMngr != NULL)
	{
		if ( (m_pSmvInMngr->GetCfgDataCount() > 0) && (m_pSmvInMngr->GetDataUse() > 0) && bGetCommon)
		{
			oList.AddTail(m_pSmvInMngr->GetCommonData());
		}

		m_pSmvInMngr->GetIecCfgDatas(oList);
	}

}

void CIecCfgDatasMngr::GetIecCfgGinDatas(CExBaseList &oList)
{
	if (m_pGinMngr != NULL)
	{
		m_pGinMngr->GetIecCfgDatas(oList);
	}

}

void CIecCfgDatasMngr::GetIecCfgGoutDatas(CExBaseList &oList)
{
	if (m_pGoutMngr != NULL)
	{
		m_pGoutMngr->GetIecCfgDatas(oList);
	}
}

// long CIecCfgDatasMngr::GetSmvInputType()
// {
// 	if (m_pSmvInputMngr == NULL)
// 	{
// 		return 0;
// 	}
// 
// 	return m_pSmvInputMngr->GetSmvType();
// }
// 
// BOOL CIecCfgDatasMngr::SetSmvInputType(long nSmvType)
// {
// 	CIecCfgDatasSMVInput *pSmvInputMngr = GetSmvInputMngr();
// 	return pSmvInputMngr->SetSmvType(nSmvType);
// }
// 
// void CIecCfgDatasMngr::GetIecCfgSmvInputDatas(CExBaseList &oList, BOOL bGetCommon)
// {
// 	if (m_pSmvInputMngr != NULL)
// 	{
// 		if ( (m_pSmvInputMngr->GetCfgDataCount() > 0) && (m_pSmvInputMngr->GetDataUse() > 0) && bGetCommon)
// 		{
// 			oList.AddTail(m_pSmvInputMngr->GetCommonData());
// 		}
// 
// 		m_pSmvInputMngr->GetIecCfgDatas(oList);
// 	}
// 
// }
// 
// void CIecCfgDatasMngr::GetIecCfgAnalogDatas(CExBaseList &oList)
// {
// 	if (m_pAnalogMngr != NULL)
// 	{
// 		m_pAnalogMngr->GetIecCfgDatas(oList);
// 	}
// }
// 

void CIecCfgDatasMngr::GetIecCfgDatas(CExBaseList &oList, BOOL bGetCommon)
{
	GetIecCfgSmvDatas(oList, bGetCommon);
// 	GetIecCfgAnalogDatas(oList);
	GetIecCfgGinDatas(oList);
	GetIecCfgGoutDatas(oList);
}

BOOL CIecCfgDatasMngr::DeleteCfgData(CIecCfgDataBase *pCfgData)
{
	if (m_pSmvMngr != NULL)
	{
		if (m_pSmvMngr->DeleteCfgData(pCfgData))
		{
			return TRUE;
		}
	}

	if (m_pSmvInMngr != NULL)
	{
		if (m_pSmvInMngr->DeleteCfgData(pCfgData))
		{
			return TRUE;
		}
	}

	if (m_pGinMngr != NULL)
	{
		if (m_pGinMngr->DeleteCfgData(pCfgData))
		{
			return TRUE;
		}
	}

	if (m_pGoutMngr != NULL)
	{
		if (m_pGoutMngr->DeleteCfgData(pCfgData))
		{
			return TRUE;
		}
	}

// 	if (m_pSmvInputMngr != NULL)
// 	{
// 		if (m_pSmvInputMngr->DeleteCfgData(pCfgData))
// 		{
// 			return TRUE;
// 		}
// 	}

	ASSERT (FALSE);
	return FALSE;
}
// 
// void CIecCfgDatasMngr::ResetArtAmpDigdatas()
// {
// 	if (m_pArtAmpDigdatas != NULL)
// 	{
// 		m_pArtAmpDigdatas->ResetArtAmpDigdatas();
// 	}
// }

BOOL CIecCfgDatasMngr::OpenIecCfgFile(const CString &strFile)
{
	DeleteAll();
	InitDatasMngr();
	CString strFilePostfix = ParseFilePostfix(strFile);
	strFilePostfix.MakeLower();
	BOOL bTrue = FALSE;

#ifdef _use_COnllyCfgFileTool
	if (strFilePostfix == _T("f66"))
	{
		COnllyCfgFileTool oTool;
		bTrue = oTool.ReadF66File(strFile, this);
	}
	else
#endif
	{
		bTrue = OpenXmlFile(strFile, GetXmlElementKey(), CCfgDataMngrXmlRWKeys::g_pXmlKeys);
		InitAfterRead2();
	}

	return bTrue;
}

//2022-9-19  lijunqing
void CIecCfgDatasMngr::InitAfterRead2()
{
	if (m_pSmvMngr == NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("格式不正确、版本不兼容，是使用PowerTest配置的文件"));
	}
	else
	{
		m_pSmvMngr->InitCommonFromCfgDatas();
		m_pSmvMngr->InitCfgDatasByCommon();
	}

	GetSmvInMngr();
	m_pSmvInMngr->InitCommonFromCfgDatas();
	m_pSmvInMngr->InitCfgDatasByCommon();

	if (m_pSysParasMngr == NULL)
	{
		GetSysParasMngr();

		//mym 2021-3-24 zhuxiao 
		m_pSysParasMngr->InitPrimRatesFiberParas(IECCFG_MAX_PT_CT_NUM,IECCFG_MAX_PT_CT_NUM,IECCFG_MAX_LC_FIBER_NUM,IECCFG_MAX_ST_FIBER_NUM);
	}
}

//2022-9-19  lijunqing
BOOL CIecCfgDatasMngr::SetIecCfgDataString(const CString &strIecCfgData)
{
	DeleteAll();
	InitDatasMngr();
	BOOL bTrue = FALSE;

	bTrue = SetXml(strIecCfgData, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
	InitAfterRead2();

	return bTrue;
}

void CIecCfgDatasMngr::InitCommon()
{
	GetSmvMngr();
	m_pSmvMngr->InitCommonFromCfgDatas();
	m_pSmvMngr->InitCfgDatasByCommon();

	GetSmvInMngr();
	m_pSmvInMngr->InitCommonFromCfgDatas();
	m_pSmvInMngr->InitCfgDatasByCommon();

	if (m_pSysParasMngr == NULL)
	{
		GetSysParasMngr();

		//mym 2021-3-24 zhuxiao 
		m_pSysParasMngr->InitPrimRatesFiberParas(IECCFG_MAX_PT_CT_NUM,IECCFG_MAX_PT_CT_NUM,IECCFG_MAX_LC_FIBER_NUM,IECCFG_MAX_ST_FIBER_NUM);
	}

// 	m_pSmvInputMngr->InitCommonFromCfgDatas();
// 	m_pSmvInputMngr->InitCfgDatasByCommon();
}

void CIecCfgDatasMngr::DelteteContrlBlocks_Unselected()
{
	if (m_pSmvMngr != NULL)
	{
		m_pSmvMngr->DelteteContrlBlocks_Unselected();
	}

	if (m_pSmvInMngr != NULL)
	{
		m_pSmvInMngr->DelteteContrlBlocks_Unselected();
	}

	if (m_pGinMngr != NULL)
	{
		m_pGinMngr->DelteteContrlBlocks_Unselected();
	}

	if (m_pGoutMngr != NULL)
	{
		m_pGoutMngr->DelteteContrlBlocks_Unselected();
	}
}

BOOL CIecCfgDatasMngr::HasContrlBlock_Selected()
{
	if ((m_pSmvMngr != NULL)&&(m_pSmvMngr->HasContrlBlock_Selected()))
	{
		return TRUE;
	}

	if ((m_pSmvInMngr != NULL)&&(m_pSmvInMngr->HasContrlBlock_Selected()))
	{
		return TRUE;
	}	
	
	if ((m_pGinMngr != NULL)&&(m_pGinMngr->HasContrlBlock_Selected()))
	{
		return TRUE;
	}

	if ((m_pGoutMngr != NULL)&&(m_pGoutMngr->HasContrlBlock_Selected()))
	{
		return TRUE;
	}

	return FALSE;
}

BOOL CIecCfgDatasMngr::HasContrlBlock_Selected(bool bHasLCFiber,bool bHasSTFiber )
{
	/**
	 * 20240520 suyang 增加两个bool量来判断当前设备的LC口、ST口是否为0，当为0时会隐藏对应的控制块
	 *但判断时也会将隐藏的控制块进行判断，所以要区别类型判断
	 */

	if (m_pSmvMngr == NULL)
	{
		GetSmvMngr();
	}
	if (m_pSmvInMngr == NULL)
	{
		GetSmvInMngr();
	}

	if (!bHasLCFiber)
	{
		if (m_pSmvMngr->HasContrlBlock_FT3Selected())
		{
			return TRUE;
		}

		if (m_pSmvInMngr->HasContrlBlock_FT3Selected())
		{
			return TRUE;
		}
		
		
	}
	else if (!bHasSTFiber)
	{
		if (m_pSmvMngr->HasContrlBlock_SV_GOOSESelected())
		{
			return TRUE;
		}

		if (m_pSmvInMngr->HasContrlBlock_SV_GOOSESelected())
		{
			return TRUE;
		}	

		return FALSE;
	}
	else
	{
		if (m_pSmvMngr->HasContrlBlock_Selected())
	{
		return TRUE;
	}

		if (m_pSmvInMngr->HasContrlBlock_Selected())
	{
		return TRUE;
	}	

		if (m_pGinMngr->HasContrlBlock_Selected())
	{
		return TRUE;
	}

		if (m_pGoutMngr->HasContrlBlock_Selected())
	{
		return TRUE;
	}
	}
	
	return FALSE;

}

void CIecCfgDatasMngr::UpdateGinChMapFile()
{
	if (!m_strGinChMapFileName.IsEmpty())
	{
		CString strTmpPath;
		strTmpPath = _P_GetConfigPath();
		strTmpPath += m_strGinChMapFileName;
		strTmpPath += _T(".xml");

		if (IsFileExist(strTmpPath))
		{
			g_strGsChDtID_goose_in_ch = m_strGinChMapFileName;
			CCfgDataMngrConstGlobal::Update_GinAppChDataType();
			CIecCfgGinDatas *pGinMngr = GetGinMngr();
			pGinMngr->InitAfterRead();
		} 
		else
		{
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前配置(name=%s)(id=%s)的Gin通道映射文件名称(%s)对应的文件不存在."),m_strName.GetString(),m_strID.GetString(),
				m_strGinChMapFileName.GetString());
		}
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("当前配置(name=%s)(id=%s)的Gin通道映射文件名称为空."),m_strName.GetString(),m_strID.GetString());
	}
}

void CIecCfgDatasMngr::UpdateFiberIdex2()
{
	if (m_pSmvMngr != NULL)
	{
		m_pSmvMngr->UpdateFiberIdex2();
	}

	if (m_pSmvInMngr != NULL)
	{
		m_pSmvInMngr->UpdateFiberIdex2();
	}

	if (m_pGinMngr != NULL)
	{
		m_pGinMngr->UpdateFiberIdex2();
	}

	if (m_pGoutMngr != NULL)
	{
		m_pGoutMngr->UpdateFiberIdex2();
	}
}

#ifndef _PSX_IDE_QT_
BOOL CIecCfgDatasMngr::SaveAsIecCfgFile()
{
	CWnd *pMainFrame = AfxGetMainWnd();
	m_pSmvMngr->InitCfgDatasByCommon();//zhouhj20190517 对采样值进行赋值
	m_pSmvInMngr->InitCfgDatasByCommon();
// 	char pszFilePath[MAX_PATH];
// 	ZeroMemory(pszFilePath, MAX_PATH);
// 	pMainFrame->SendMessage(WM_SAVEAS_IecCfgFILE, (WPARAM)pszFilePath, (LPARAM)pszFilePath);
//	SaveAsIecCfgFile(CString(pszFilePath));
	return pMainFrame->SendMessage(WM_SAVEAS_IecCfgFILE, 0, 0);
}
#endif
// 
// void CIecCfgDatasMngr::SaveTempIecCfgFile()
// {
// 	CString strFile = iecfg_GetCfgCapFileCfgDatasMngr();
// 	SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
// }
// 
// void CIecCfgDatasMngr::OpenTempIecCfgFile()
// {
// 	CString strFile = iecfg_GetCfgCapFileCfgDatasMngr();
// 
// 	DeleteAll();
// 	InitDatasMngr();
// 
// 	OpenXmlFile(strFile, GetXmlElementKey(), CCfgDataMngrXmlRWKeys::g_pXmlKeys);
// 	m_pSmvMngr->InitCommonFromCfgDatas();
// 	m_pSmvMngr->InitCfgDatasByCommon();
// }

BOOL CIecCfgDatasMngr::SaveAsIecCfgFile(const CString &strFile,BOOL bIsAT02D_CFG)//周宏军 20200616  增加AT02配置
{
	m_bModified = FALSE;
	m_pSmvMngr->InitCfgDatasByCommon();//zhouhj20190517 对采样值进行赋值
	m_pSmvInMngr->InitCfgDatasByCommon();
//	m_strIecCfgFile = strFile;

#ifdef _USE_IN_AT02D_MODE_
	if (bIsAT02D_CFG)
	{
//		long nDelayIndex = 1,nCurIndex = 1,nVolIndex = 1,nGinChIndex = 1,nGoutChIndex = 1;
		long nSV_CBIndex = 1,nGinCBIndex = 1,nGoutCBIndex = 1;
		CExBaseList oSVList,oGinList,oGoutList;
		SetAT02D_ChannelID(&oSVList,&oGinList,&oGoutList,nSV_CBIndex,nGinCBIndex,nGoutCBIndex);
		oSVList.RemoveAll();
		oGinList.RemoveAll();
		oGoutList.RemoveAll();
	}
#endif


	SYSTEMTIME tm;
	::GetLocalTime(&tm);
	m_strDate.Format(_T("%04d-%02d-%02d %02d:%02d:%02d-%03d"),tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
	return SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
}

#ifdef _USE_IN_AT02D_MODE_
void CIecCfgDatasMngr::SetAT02D_ChannelID(CExBaseList *pSVList,CExBaseList *pGinList,CExBaseList *pGoutList,long &nSV_CBIndex,long &nGinCBIndex,long &nGoutCBIndex)
{
	if ((m_pSmvMngr != NULL)&&(pSVList != NULL))
	{
		m_pSmvMngr->SetAT02D_ChannelID(pSVList,nSV_CBIndex);
	}

	if ((m_pSmvInMngr != NULL)&&(pSVList != NULL))
	{
		m_pSmvInMngr->SetAT02D_ChannelID(pSVList,nSV_CBIndex);
	}

	if ((m_pGinMngr != NULL)&&(pGinList != NULL))
	{
		m_pGinMngr->SetAT02D_ChannelID(pGinList,nGinCBIndex);
	}

	if ((m_pGoutMngr != NULL)&&(pGoutList != NULL))
	{
		m_pGoutMngr->SetAT02D_ChannelID(pGoutList,nGoutCBIndex);
	}
}

void CIecCfgDatasMngr::SetAT02D_ChannelID(CExBaseList *pSmvInList,CExBaseList *pSmvOutList,CExBaseList *pGinList,CExBaseList *pGoutList,
										  long &nSVmvIn_CBIndex,long &nSVmvOut_CBIndex,long &nGinCBIndex,long &nGoutCBIndex)
{
	if ((m_pSmvMngr != NULL)&&(pSmvOutList != NULL))
	{
		m_pSmvMngr->SetAT02D_ChannelID(pSmvOutList,nSVmvOut_CBIndex);
	}

	if ((m_pSmvInMngr != NULL)&&(pSmvInList != NULL))
	{
		m_pSmvInMngr->SetAT02D_ChannelID(pSmvInList,nSVmvIn_CBIndex);
	}

	if ((m_pGinMngr != NULL)&&(pGinList != NULL))
	{
		m_pGinMngr->SetAT02D_ChannelID(pGinList,nGinCBIndex);
	}

	if ((m_pGoutMngr != NULL)&&(pGoutList != NULL))
	{
		m_pGoutMngr->SetAT02D_ChannelID(pGoutList,nGoutCBIndex);
	}
}

void CIecCfgDatasMngr::AddAT02D_Dataset(CDvmLogicDevice *pLDevice,long &nSV_DatasetIndex,long &nGin_DatasetIndex,long &nGout_DatasetIndex,BOOL bHasHarm,BOOL bhasMUTestParas)
{
	ASSERT(pLDevice);
// 	CExBaseObject *pCurObj = NULL;
// 	POS pos = pLDevice->GetHeadPosition();
// 
// 	while(pos)
// 	{
// 		pCurObj = pLDevice->GetNext(pos);
// 
// 		if ((pCurObj->m_strID.Find(_T("dsSV"))>=0)||(pCurObj->m_strID.Find(_T("dsGout"))>=0)||(pCurObj->m_strID.Find(_T("dsGin"))>=0))
// 		{
// 			pLDevice->Delete(pCurObj);
// 		}
// 	}

	if (m_pSmvMngr != NULL)
	{
		m_pSmvMngr->AddAT02D_dsSV(pLDevice,nSV_DatasetIndex,bHasHarm,bhasMUTestParas);
	}

	if (m_pSmvInMngr != NULL)
	{
		m_pSmvInMngr->AddAT02D_dsSV(pLDevice,nSV_DatasetIndex,bHasHarm,bhasMUTestParas);
	}

	if (m_pGinMngr != NULL)
	{
		m_pGinMngr->AddAT02D_dsGin(pLDevice,nGin_DatasetIndex);
	}

	if (m_pGoutMngr != NULL)
	{
		m_pGoutMngr->AddAT02D_dsGout(pLDevice,nGout_DatasetIndex);
	}
}

void CIecCfgDatasMngr::AddAT02D_Dataset_SmvInGin(CDvmLogicDevice *pLDevice,long &nSmvIn_DatasetIndex,long &nGin_DatasetIndex,BOOL bHasHarm,BOOL bhasMUTestParas)
{
	ASSERT(pLDevice);
	if (m_pSmvInMngr != NULL)
	{
		m_pSmvInMngr->AddAT02D_dsSV(pLDevice,nSmvIn_DatasetIndex,bHasHarm,bhasMUTestParas);
	}

	if (m_pGinMngr != NULL)
	{
		m_pGinMngr->AddAT02D_dsGin(pLDevice,nGin_DatasetIndex);
	}
}

#endif

BOOL CIecCfgDatasMngr::AddCfgData(long nCfgDataClassID, const CString &strCfgDataFile)
{
	switch (nCfgDataClassID)
	{
	case CFGCLASSID_CIECCFG92DATA:
	case CFGCLASSID_CIECCFG92INPUTDATA:
	case CFGCLASSID_CIECCFG91DATA:
	case CFGCLASSID_CIECCFG6044DATA:
		AddCfgData_Smv(nCfgDataClassID, strCfgDataFile);
		break;
	case CFGCLASSID_CIECCFGGINDATA:
		AddCfgData_Gin(strCfgDataFile);
		break;

	case CFGCLASSID_CIECCFGGOUTDATA:
		AddCfgData_Gout(strCfgDataFile);
		break;
	}

	return FALSE;
}

#ifdef _USE_IN_AT02D_MODE_
CIecCfgDatasMngr* CIecCfgDatasMngr::GetAT02D_IecCfgDatasMngr()
{
	CIecCfgDatasMngr *pAT02D_DatasMngr = new CIecCfgDatasMngr;
	CopyOwn(pAT02D_DatasMngr);

	if (m_pGinMngr != NULL)
	{
		CIecCfgGoutDatas *pNewGoutMngr = new CIecCfgGoutDatas;
		AT02D_CopyGinToGout(m_pGinMngr,pNewGoutMngr);
		pAT02D_DatasMngr->AddNewChild(pNewGoutMngr);
		pNewGoutMngr->SetFiberIndexByFiber2Index();
	}

	if (m_pGoutMngr != NULL)
	{
		CIecCfgGinDatas *pNewGinMngr = new CIecCfgGinDatas;
		AT02D_CopyGoutToGin(m_pGoutMngr,pNewGinMngr);
		pAT02D_DatasMngr->AddNewChild(pNewGinMngr);
		pNewGinMngr->SetFiberIndexByFiber2Index();
	}
	
	CIecCfgDatasSMV *pNewSMVMngr = new CIecCfgDatasSMV;
	pAT02D_DatasMngr->AddNewChild(pNewSMVMngr);
	pAT02D_DatasMngr->InitAfterRead();
	return pAT02D_DatasMngr;
}

void CIecCfgDatasMngr::AT02D_CopyGoutToGin(CIecCfgGoutDatas *pGoutMngr,CIecCfgGinDatas *pNewGinMngr)
{
	pNewGinMngr->DeleteAll();
	pNewGinMngr->m_nDatasCount = pGoutMngr->m_nDatasCount;
	pNewGinMngr->m_nDatasUse = pGoutMngr->m_nDatasUse;
	CIecCfgGoutData *pGoutData = NULL;
	CIecCfgGinData *pGinData = NULL;
	CExBaseObject *pCurObj = NULL;

	POS pos_goose = pGoutMngr->GetHeadPosition();

	while(pos_goose)
	{
		pCurObj = pGoutMngr->GetNext(pos_goose);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGOUTDATA)
		{
			pGoutData = (CIecCfgGoutData *)pCurObj;
			pGinData = new CIecCfgGinData;
			pNewGinMngr->AddNewChild(pGinData);
			pGoutData->AT02D_CopyToGinData(pGinData);
		}
	}
}

void CIecCfgDatasMngr::AT02D_CopyGinToGout(CIecCfgGinDatas *pGinMngr,CIecCfgGoutDatas *pNewGoutMngr)
{
	pNewGoutMngr->DeleteAll();
	pNewGoutMngr->m_nDatasCount = pGinMngr->m_nDatasCount;
	pNewGoutMngr->m_nDatasUse = pGinMngr->m_nDatasUse;
	CIecCfgGoutData *pGoutData = NULL;
	CIecCfgGinData *pGinData = NULL;
	CExBaseObject *pCurObj = NULL;

	POS pos_goose = pGinMngr->GetHeadPosition();

	while(pos_goose)
	{
		pCurObj = pGinMngr->GetNext(pos_goose);

		if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGGINDATA)
		{
			pGinData = (CIecCfgGinData *)pCurObj;
			pGoutData = new CIecCfgGoutData;
			pNewGoutMngr->AddNewChild(pGoutData);
			pGinData->AT02D_CopyToGoutData(pGoutData);
		}
	}
}

void CIecCfgDatasMngr::AT02D_GetAllDatasRef(CIecCfgDatasSMV *pTmpSMVDatas,CIecCfgGinDatas *pTmpGinDatas,CIecCfgGoutDatas *pTmpGoutDatas)
{
	if (m_pSmvMngr != NULL)
	{
		m_pSmvMngr->GetIecCfgDatas(*pTmpSMVDatas);
	}

// 	if (m_pSmvInMngr != NULL)
// 	{
// 		m_pSmvInMngr->GetIecCfgDatas(*pTmpSMVDatas);
// 	}

	if (m_pGinMngr != NULL)
	{
		m_pGinMngr->GetIecCfgDatas(*pTmpGinDatas);
	}

	if (m_pGoutMngr != NULL)
	{
		m_pGoutMngr->GetIecCfgDatas(*pTmpGoutDatas);
	}
}

#endif

BOOL CIecCfgDatasMngr::CanAddCfgData(CIecCfgDatasBase *pDatas, long nMaxCount)
{
	CExBaseList oList;

	pDatas->GetIecCfgDatas(oList);
	BOOL bCan = nMaxCount > oList.GetCount();
	oList.RemoveAll();

	return bCan;
}

BOOL CIecCfgDatasMngr::AddCfgData_Smv(long nCfgDataClassID, const CString &strCfgDataFile)
{
//	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("AddCfgData_Smv"));

	if (!CanAddCfgData(GetSmvMngr(), 4))
	{
		return FALSE;
	}

	CIecCfgDatasSMV *pMngr = GetSmvMngr();
	CIecCfgDataBase *pCfgData = pMngr->CreateIecCfgData();
	UINT nClassID = pCfgData->GetClassID();

	if (pCfgData == NULL)
	{
		return FALSE;
	}

	pMngr->AddNewChild(pCfgData);

	if (nClassID != nCfgDataClassID)
	{
#ifdef NOT_USE_XLANGUAGE
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("添加的SMV配置对象与当前的配置不一致"));
#else
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_DiffSvmConfig/*_T("添加的SMV配置对象与当前的配置不一致")*/);
#endif

		pMngr->DeleteCfgData(pCfgData);
		return FALSE;
	}
	
	BOOL b = pCfgData->OpenCfgDataTempFile();
	pCfgData->InitForSclRead();
//	((CIecCfgSmvDataBase*)pCfgData)->UpdateChsIndex();

	return b;
}

BOOL CIecCfgDatasMngr::AddCfgData_Gin(const CString &strCfgDataFile)
{
//	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("AddCfgData_Gin"));
	
	if (!CanAddCfgData(GetGinMngr(), 8))
	{
		return FALSE;
	}

	CIecCfgGinDatas *pMngr = GetGinMngr();
	CIecCfgDataBase *pCfgData = pMngr->CreateIecCfgData();
	
	if (pCfgData == NULL)
	{
		return FALSE;
	}

	pMngr->AddNewChild(pCfgData);
	pMngr->SetDataUse(1);

	return pCfgData->OpenCfgDataTempFile();
}

BOOL CIecCfgDatasMngr::AddCfgData_Gout(const CString &strCfgDataFile)
{
//	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("AddCfgData_Gout"));
	
	if (!CanAddCfgData(GetGoutMngr(), 8))
	{
		return FALSE;
	}

	CIecCfgGoutDatas *pMngr = GetGoutMngr();
	CIecCfgDataBase *pCfgData = pMngr->CreateIecCfgData();
	
	if (pCfgData == NULL)
	{
		return FALSE;
	}

	pMngr->AddNewChild(pCfgData);
	pMngr->SetDataUse(1);

	return pCfgData->OpenCfgDataTempFile();
}
// BOOL CIecCfgDatasMngr::AddCfgData_SmvInput(long nCfgDataClassID, const CString &strCfgDataFile)
// {
// 	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("AddCfgData_SmvInput"));
// 
// 	if (!CanAddCfgData(GetSmvInputMngr(), 4))
// 	{
// 		return FALSE;
// 	}
// 
// 	CIecCfgDatasSMVInput *pMngr = GetSmvInputMngr();
// 	CIecCfgDataBase *pCfgData = pMngr->CreateIecCfgData();
// 	UINT nClassID = pCfgData->GetClassID();
// 
// 	if (pCfgData == NULL)
// 	{
// 		return FALSE;
// 	}
// 
// 	pMngr->AddNewChild(pCfgData);
// 
// 	if (nClassID != nCfgDataClassID)
// 	{
// 		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_DiffSvmConfig/*_T("添加的SMV配置对象与当前的配置不一致")*/);
// 		pMngr->DeleteCfgData(pCfgData);
// 		return FALSE;
// 	}
// 
// 	BOOL b = pCfgData->OpenCfgDataTempFile();
// 	pCfgData->InitForSclRead();
// 
// 	return b;
// }

BOOL CIecCfgDatasMngr::OverWriteCfgData(long nCfgDataClassID, long nIndex, const CString &strCfgDataFile, CIecCfgDataBase **ppCfgData)
{
	CIecCfgDatasBase *pDatas = NULL;
	CIecCfgDatasSMV *pSmvMngr = NULL;
	pSmvMngr = GetSmvMngr();

// 	CIecCfgDatasSMVInput *pSmvInputMngr = NULL;
// 	pSmvInputMngr = GetSmvInputMngr();

	switch (nCfgDataClassID)
	{
	case CFGCLASSID_CIECCFG92DATA:
		if (pSmvMngr->IsSmvType92())
		{
			pDatas = pSmvMngr;
		}
		break;

// 	case CFGCLASSID_CIECCFG92INPUTDATA:
// 		if (pSmvInputMngr->IsSmvType92())
// 		{
// 			pDatas = pSmvInputMngr;
// 		}
// 		break;

	case CFGCLASSID_CIECCFG91DATA:
		if (pSmvMngr->IsSmvType91())
		{
			pDatas = pSmvMngr;
		}
		break;

	case CFGCLASSID_CIECCFG6044DATA:
		if (pSmvMngr->IsSmvType6044())
		{
			pDatas = pSmvMngr;
		}
		break;

	case CFGCLASSID_CIECCFGGINDATA:
		pDatas = GetGinMngr();
		break;

	case CFGCLASSID_CIECCFGGOUTDATA:
		pDatas = GetGoutMngr();
		break;
	}

	if (pDatas == NULL)
	{
#ifdef NOT_USE_XLANGUAGE
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("数据覆盖失败，配置数据种类不匹配"));
#else
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_NoMatchData/*_T("数据覆盖失败，配置数据种类不匹配")*/);
#endif
		return FALSE;
	}

	if (pDatas->GetDataUse() <= 0)
	{
#ifdef NOT_USE_XLANGUAGE
        CLogPrint::LogString(XLOGLEVEL_TRACE, _T("数据覆盖失败，配置数据种类没有选中"));
#else
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_NoSelData/*_T("数据覆盖失败，配置数据种类没有选中")*/);
#endif
		return FALSE;
	}

	CIecCfgDataBase *pCfgData = (CIecCfgDataBase*)pDatas->GetIecCfgData(nIndex);
	
	if (pCfgData == NULL)
	{
#ifdef NOT_USE_XLANGUAGE
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("数据覆盖失败，配置数据索引%d不存在"), nIndex);
#else
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_NoExisDataIndex.GetString() /*_T("数据覆盖失败，配置数据索引%d不存在")*/, nIndex);
#endif
		return FALSE;
	}

	BOOL b = pCfgData->OpenCfgDataTempFile();
	*ppCfgData = pCfgData;

// 	if (pDatas != NULL && pCfgData != NULL)
// 	{
// 		if (pDatas->GetClassID() == CFGCLASSID_CIECCFGDATASSMV)
// 		{
// 			((CIecCfgSmvDataBase*)pCfgData)->UpdateChsIndex();
// 		}
// 	}

	return b;
}

CIecCfgDataBase* CIecCfgDatasMngr::FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT nAPPID,UINT nCMT,UINT nChCount)
{
	if(nCMT == PROTOCOL_61850_TYPE_91 || nCMT == PROTOCOL_61850_TYPE_92)
	{
		return m_pSmvMngr->FindIecCfgData(pDstMac,pSrcMac,nAPPID,nCMT,nChCount);
	}
	else if(nCMT == PROTOCOL_61850_TYPE_GOOSEIN)
	{
		return m_pGinMngr->FindIecCfgData(pDstMac,pSrcMac,nAPPID,nCMT,nChCount);
	}
	else if (nCMT == PROTOCOL_61850_TYPE_GOOSEOUT)
	{
		return m_pGoutMngr->FindIecCfgData(pDstMac,pSrcMac,nAPPID,nCMT,nChCount);
	}

	return NULL;
}

CIecCfgDatasMngr* iecfg_GetIecCfgDatasMngr(CExBaseObject *pObj)
{
	ASSERT(pObj != NULL);
	CIecCfgDatasMngr *pIecCfgDatasMngr = NULL;

	if (pObj->GetClassID() == CFGCLASSID_CIECCFGDATASMNGR)
	{
		pIecCfgDatasMngr = (CIecCfgDatasMngr *)pObj;
	}
	else
	{
		pIecCfgDatasMngr = (CIecCfgDatasMngr *)pObj->GetAncestor(CFGCLASSID_CIECCFGDATASMNGR);
	}

	ASSERT( pIecCfgDatasMngr != NULL );
	return pIecCfgDatasMngr;
}

CIecCfgSmvRate* iecfg_GetSmvRate(CIecCfgDataSmvChBase* pDataSmvCh,BOOL bDCFT3)
{
	if (pDataSmvCh == NULL)
	{
		return NULL;
	}

// 	CIecCfgDatasMngr *pIecCfgDatasMngr = (CIecCfgDatasMngr*)pDataSmvCh->GetAncestor(CFGCLASSID_CIECCFGDATASMNGR);
// 
// 	if (pIecCfgDatasMngr == NULL)
// 	{
// 		return NULL;
// 	}
//	CIecCfgDatasSMV* pDatasSMV = pIecCfgDatasMngr->GetSmvMngr();

	CIecCfgDatasSMV* pDatasSMV = (CIecCfgDatasSMV*)pDataSmvCh->GetAncestor(CFGCLASSID_CIECCFGDATASSMV);

	if (pDatasSMV == NULL)
	{
		pDatasSMV = (CIecCfgDatasSMV*)pDataSmvCh->GetAncestor(CFGCLASSID_CIECCFGDATASSMVINPUT);
	}

	CIecCfgSmvRates* pSmvRates = pDatasSMV->GetIecCfgSmvRates();

	if (pSmvRates == NULL)
	{
		return NULL;
	}

	CIecCfgSmvRate* pSmvRate = (CIecCfgSmvRate*)pSmvRates->FindByID(st_GetSmvRateID(pDataSmvCh->m_strAppChID,bDCFT3));
	return pSmvRate;
}


#ifndef _PSX_IDE_QT_

CIecCfgDevice* iecfg_GetIecCfgDevice(CExBaseObject *pObj)
{
	ASSERT(pObj != NULL);
	CIecCfgDevice *pIecCfgDevice = NULL;

	if (pObj->GetClassID() == CFGCLASSID_CIECCFGDEVICE)
	{
		pIecCfgDevice = (CIecCfgDevice *)pObj;
	}
	else
	{
		pIecCfgDevice = (CIecCfgDevice *)pObj->GetAncestor(CFGCLASSID_CIECCFGDEVICE);
	}

	return pIecCfgDevice;
}

void iecfg_SetModified(CExBaseObject *pObj, BOOL bModified)
{
	ASSERT(pObj != NULL);

	CIecCfgDevice *pIecfgDevice = iecfg_GetIecCfgDevice(pObj);

	if (pIecfgDevice != NULL)
	{
		pIecfgDevice->m_bModified = bModified;
		return;
	}

	CIecCfgDatasMngr *pIecCfgDatasMngr = iecfg_GetIecCfgDatasMngr(pObj);

	ASSERT( pIecCfgDatasMngr != NULL );
	pIecCfgDatasMngr->m_bModified = bModified;
}

BOOL iecfg_IsModified(CExBaseObject *pObj)
{
	ASSERT(pObj != NULL);

	CIecCfgDevice *pIecfgDevice = iecfg_GetIecCfgDevice(pObj);

	if (pIecfgDevice != NULL)
	{
		return pIecfgDevice->m_bModified;
	}

	CIecCfgDatasMngr *pIecCfgDatasMngr = iecfg_GetIecCfgDatasMngr(pObj);

	ASSERT( pIecCfgDatasMngr != NULL );
	return pIecCfgDatasMngr->m_bModified ;
}

#endif


//
void CIecCfgDatasMngr::UpdateFT3ChsType(long nIecFormat,long nIecFormatMeas)
{
	if (m_pSmvMngr == NULL)
	{
		GetSmvMngr();
	}

	CIecCfg6044CommonData* pIecCfg6044CommonData = NULL;
	CExBaseObject *pCurObj = NULL;
	POS pos = m_pSmvMngr->GetHeadPosition();
	while(pos)
	{
		pCurObj=m_pSmvMngr->GetNext(pos);

		if (pCurObj->GetClassID()==CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			pIecCfg6044CommonData=(CIecCfg6044CommonData*)pCurObj;

			POS pos2= pIecCfg6044CommonData->GetHeadPosition();
			CIecCfg6044Chs *pIecCfg6044Chs=NULL;
			while (pos2)
			{
				pIecCfg6044Chs = (CIecCfg6044Chs*)pIecCfg6044CommonData->GetNext(pos2);
				UpdateFT3ChsTypeChanged(pIecCfg6044Chs,nIecFormat);

			}
		}
	}

	if (m_pSmvInMngr == NULL)
	{
		GetSmvInMngr();
	}

	CIecCfg6044CommonData* pIecCfg6044CommonDatas = NULL;
	CExBaseObject *pData = NULL;
	POS pos4 = m_pSmvInMngr->GetHeadPosition();
	while(pos4)
	{
		pData=m_pSmvInMngr->GetNext(pos4);

		if (pData->GetClassID()==CFGCLASSID_CIECCFG6044COMMONDATA)
		{
			pIecCfg6044CommonDatas=(CIecCfg6044CommonData*)pData;

			POS pos5= pIecCfg6044CommonDatas->GetHeadPosition();
			CIecCfg6044Chs *pIecCfg6044Chs=NULL;
			while (pos5)
			{
				pIecCfg6044Chs = (CIecCfg6044Chs*)pIecCfg6044CommonDatas->GetNext(pos5);
				UpdateFT3ChsTypeChanged(pIecCfg6044Chs,nIecFormatMeas);
			}
		}
	}
}

void CIecCfgDatasMngr::UpdateFT3ChsTypeChanged(CIecCfgChsBase *pIecCfgChsBase,long nType)
{
	CIecCfg6044Chs *pIecCfg6044Chs =(CIecCfg6044Chs *)pIecCfgChsBase;
	if (pIecCfg6044Chs == NULL)
	{
		return;
	}

	if (pIecCfg6044Chs->GetClassID()==CFGCLASSID_CIECCFGCHS6044)
	{
		CIecCfg6044CommonCh *pIecCfgFT3Ch = NULL;
		POS pos = pIecCfg6044Chs->GetHeadPosition();

		while(pos)
		{
			pIecCfgFT3Ch = (CIecCfg6044CommonCh *)pIecCfg6044Chs->GetNext(pos);

			if(nType == IECCFG_FORMAT_60044_8DC)
			{
				if(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Vol)
				{
					pIecCfgFT3Ch->m_strChType = iecfg_SmvChDataType_Val_6Vol;
				}

				if(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Curr)
				{
					pIecCfgFT3Ch->m_strChType = iecfg_SmvChDataType_Val_6CurrProt;
				}

			}
			else
			{
				if(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6Vol)
				{
					pIecCfgFT3Ch->m_strChType = iecfg_SmvChDataType_Val_Vol;
				}

				if(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrMeasure)
				{
					pIecCfgFT3Ch->m_strChType = iecfg_SmvChDataType_Val_CurrMeasure;//2024-5-30 wuxinyi 测量电流
				}

				if(pIecCfgFT3Ch->m_strChType ==iecfg_SmvChDataType_Val_6CurrProt )
				{
					pIecCfgFT3Ch->m_strChType = iecfg_SmvChDataType_Val_Curr;
				}

			}
		}
	}
// 	if (pIecCfg6044Chs->GetClassID()==CFGCLASSID_CIECCFGCHS6044)
// 	{
// 
// 
// 		CIecCfg6044CommonCh *pIecCfgFT3Ch = NULL;
// 		POS pos3 = pIecCfg6044Chs->GetHeadPosition();
// 		while(pos3)
// 		{
// 
// 			pIecCfgFT3Ch = (CIecCfg6044CommonCh *)pIecCfg6044Chs->GetNext(pos3);
// 			if(nType == 2)
// 			{
// 				if(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Vol)
// 				{
// 					pIecCfgFT3Ch->m_strChType = iecfg_SmvChDataType_Val_6Vol;
// 				}
// 
// 				if(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_Curr)
// 				{
// 					pIecCfgFT3Ch->m_strChType = iecfg_SmvChDataType_Val_6CurrProt;
// 				}
// 
// 			}
// 			else
// 			{
// 				if(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6Vol)
// 				{
// 					pIecCfgFT3Ch->m_strChType = iecfg_SmvChDataType_Val_Vol;
// 				}
// 
// 				if(pIecCfgFT3Ch->m_strChType == iecfg_SmvChDataType_Val_6CurrMeasure)
// 				{
// 					pIecCfgFT3Ch->m_strChType = iecfg_SmvChDataType_Val_Curr;
// 				}
// 
// 				if(pIecCfgFT3Ch->m_strChType ==iecfg_SmvChDataType_Val_6CurrProt )
// 				{
// 					pIecCfgFT3Ch->m_strChType = iecfg_SmvChDataType_Val_Curr;
// 				}
// 
// 			}
// 		}
// 
// 
// 	}













}