//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//IecCfgDatasMngr.cpp  CIecCfgDevice


#include "stdafx.h"
#include "IecCfgDevice.h"

#ifdef _use_CIecCfgTool
#include "../OnllyCfgTool/OnllyCfgFileTool.h"
#include "../../../Module/XfileMngrBase/DlgXFileMngr.h"
#include "../IecCfgTool/IecCfgTool.h"
#endif

#ifndef _PSX_IDE_QT_
#include "../../../Module/XfileMngrBase/DlgXFileMngr.h"
#endif

CIecCfgDevice::CIecCfgDevice()
{
	//初始化属性

	//初始化成员变量
	m_bModified = FALSE;
#ifdef IecCfg_With_SCL
	m_pSclIed = NULL;
#endif

	m_pCurrDatasMngr = NULL;
	m_nType = IEC_CFG_DEVICE_USE_TYPE_NORMAL;
}


CIecCfgDevice::~CIecCfgDevice()
{
	
}

long CIecCfgDevice::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;
	CExBaseObject::XmlReadOwn(oNode,pXmlRWKeys);			//yyj

	xml_GetAttibuteValue(pXmlKeys->m_strIcdFileKey, oNode, m_strIcdFile);
	xml_GetAttibuteValue(pXmlKeys->m_strTypeKey, oNode, m_nType);

	return 0;
}

long CIecCfgDevice::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	xml_SetAttributeValue(pXmlKeys->m_strIcdFileKey, oElement, m_strIcdFile);
	xml_SetAttributeValue(pXmlKeys->m_strTypeKey, oElement, m_nType);
// 	xml_SetAttributeValue(pXmlKeys->m_strEnableGOUTKey, oElement, m_nEnableGOUT);
	return 0;
}

BOOL CIecCfgDevice::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	CIecCfgDevice *p = (CIecCfgDevice*)pObj;

	return TRUE;
}

BOOL CIecCfgDevice::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CIecCfgDevice *p = (CIecCfgDevice*)pDest;
	p->m_strIcdFile = m_strIcdFile;
	p->m_nType = m_nType;

	return TRUE;
}

CBaseObject* CIecCfgDevice::Clone()
{
	CIecCfgDevice *p = new CIecCfgDevice();
	Copy(p);
	return p;
}

void CIecCfgDevice::InitAfterRead()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;

#ifdef IecCfg_With_SCL
	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == SCLIECCLASSID_IED)
		{
			m_pSclIed = (CSclIed *)p;
			break;
		}
	}

	if (m_pSclIed == NULL)
	{
		return;
	}

	pos = GetHeadPosition();

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFGDATASMNGR)
		{
			CIecCfgDatasMngr *pIecCfgDatasMngr = (CIecCfgDatasMngr*)p;
			InitSclRef(pIecCfgDatasMngr, m_pSclIed);
		}
	}
#endif
}

#ifdef IecCfg_With_SCL
void CIecCfgDevice::InitSclRef(CIecCfgDatasMngr *pIecCfgDatasMngr)
{
	if (m_pSclIed == NULL)
	{
		InitSclRef(pIecCfgDatasMngr, m_pSclIed);
	}
}


void CIecCfgDevice::InitSclRef(CIecCfgDatasMngr *pIecCfgDatasMngr, CSclIed *pIed)
{
	CIecCfgGinDatas *pGinMngr = pIecCfgDatasMngr->GetGinMngr();
	CIecCfgDatasSMV *pSmvMngr = pIecCfgDatasMngr-> GetSmvMngr();
	CIecCfgGoutDatas *pGoutMngr = pIecCfgDatasMngr-> GetGoutMngr();

	InitSclRef(pGinMngr, pIed);
	InitSclRef(pSmvMngr, pIed);
	InitSclRef(pGoutMngr, pIed);
}

void CIecCfgDevice::InitSclRef(CIecCfgGinDatas *pGinDatas, CSclIed *pIed)
{
	
}

void CIecCfgDevice::InitSclRef(CIecCfgDatasSMV *pDatasSMV, CSclIed *pIed)
{
	CIecCfgSmvDataBase *pSvData = NULL;
	POS pos = pDatasSMV->GetHeadPosition();
	UINT nClassID = 0;
	CSclCtrlsSmvIn *pSclSvIns = pIed->GetSmvIns();

	if (pSclSvIns == NULL)
	{
		return;
	}

	while (pos != NULL)
	{
		pSvData = (CIecCfgSmvDataBase *)pDatasSMV->GetNext(pos);
		nClassID = pSvData->GetClassID();

		if (nClassID == CFGCLASSID_CIECCFG92DATA)
		{
			InitSclRef((CIecCfg92Data*)pSvData, pSclSvIns);
		}
	}
	
}

void CIecCfgDevice::InitSclRef(CIecCfg92Data *pData92, CSclCtrlsSmvIn *pSclSvIns)
{
	CSclCtrlSmvIn *pSclCtrlSmvIn = (CSclCtrlSmvIn*)pSclSvIns->FindByID(pData92->m_strSVID);

	if (pSclCtrlSmvIn == NULL)
	{
		return;
	}

	pData92->m_pSclRef = pSclCtrlSmvIn;
	pSclCtrlSmvIn->m_pCfgDataRef = pData92;

	CIecCfgChsBase *pCfgChs = pData92->m_pCfgChs;
	POS pos = pCfgChs->GetHeadPosition();
	CIecCfg92Ch *pCh92 = NULL;
	CSclChSmvIn *pChSmvIn = NULL;
	//CIecCfg92Ch ==>> SVOUT   ID
	//CSclChSmvIn ==>> SVIN     OUT_PATH

	while (pos != NULL)
	{
		pCh92 = (CIecCfg92Ch *)pCfgChs->GetNext(pos);
		pChSmvIn = (CSclChSmvIn *)pSclCtrlSmvIn->FindBy_fcda_name(pCh92->m_strID);

		if (pChSmvIn != NULL)
		{
			pCh92->m_pScdObjRef = pChSmvIn;
			pChSmvIn->m_pCfgDataRef = pCh92;
		}
	}
}

void CIecCfgDevice::InitSclRef(CIecCfgGoutDatas *pGoutDatas, CSclIed *pIed)
{
	CIecCfgGoutData *pCfgoutData = NULL;
	POS pos = pGoutDatas->GetHeadPosition();
	UINT nClassID = 0;
	CSclCtrlsGsIn *pSclGsIns = pIed->GetGsIns();

	if (pSclGsIns == NULL)
	{
		return;
	}

	while (pos != NULL)
	{
		pCfgoutData = (CIecCfgGoutData *)pGoutDatas->GetNext(pos);
		nClassID = pCfgoutData->GetClassID();

		if (nClassID == CFGCLASSID_CIECCFGGOUTDATA)
		{
			InitSclRef((CIecCfgGoutData*)pCfgoutData, pSclGsIns);
		}
	}
}

void CIecCfgDevice::InitSclRef(CIecCfgGoutData *pCfgGout, CSclCtrlsGsIn *pSclGsIns)
{
	CSclCtrlGsIn *pSclCtrlGsIn = (CSclCtrlGsIn*)pSclGsIns->FindByGsID(pCfgGout->m_strGooseId);

	if (pSclCtrlGsIn == NULL)
	{
		return;
	}

	pCfgGout->m_pSclRef = pSclCtrlGsIn;
	pSclCtrlGsIn->m_pCfgDataRef = pCfgGout;

	CIecCfgChsBase *pCfgChs = pCfgGout->m_pCfgChs;
	POS pos = pCfgChs->GetHeadPosition();
	CIecCfgGoutCh *pChGout = NULL;
	CSclChGsIn *pChGsIn = NULL;
	//CIecCfgGoutCh ==>> GSOUT   ID
	//CSclChGsIn ==>> GSIN     OUT_PATH

	while (pos != NULL)
	{
		pChGout = (CIecCfgGoutCh *)pCfgChs->GetNext(pos);
		pChGsIn = (CSclChGsIn *)pSclCtrlGsIn->FindByInPath(pChGout->m_strAddrExternal);

		if (pChGsIn != NULL)
		{
			pChGout->m_pScdObjRef = pChGsIn;
			pChGsIn->m_pCfgDataRef = pChGout;
		}
	}
}
#endif

CExBaseObject* CIecCfgDevice::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CCfgDataMngrXmlRWKeys *pXmlKeys = (CCfgDataMngrXmlRWKeys*)pXmlRWKeys;

	if (strClassID == pXmlKeys->m_strCIecCfgDatasMngrKey)
	{
		pNew = new CIecCfgDatasMngr();
	}
#ifdef IecCfg_With_SCL
	else if (strClassID == pXmlKeys->CSclIedKey())
	{
		pNew = new CSclIed();
	}

#endif

	return pNew;
}

void CIecCfgDevice::SetFiber2IndexByFiberIndex(long nOffset)
{
	POS pos = GetHeadPosition();
	CIecCfgDatasMngr *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDatasMngr *)GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFGDATASMNGR)
		{
			p->SetFiber2IndexByFiberIndex(nOffset);
		}
	}
}

BOOL CIecCfgDevice::OpenIecCfgFile(const CString &strFile)
{
	DeleteAll();

	BOOL bTrue = OpenXmlFile(strFile, GetXmlElementKey(), CCfgDataMngrXmlRWKeys::g_pXmlKeys);

	POS pos = GetHeadPosition();
	CIecCfgDatasMngr *p = NULL;

	while (pos != NULL)
	{
		p = (CIecCfgDatasMngr *)GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFGDATASMNGR)
		{
			p->InitCommon();
		}
	}


	if (bTrue)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("加载配置文件【%s】成功"), strFile.GetString());
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("加载配置文件【%s】失败"), strFile.GetString());
	}

	return bTrue;
}


BOOL CIecCfgDevice::SaveAsIecCfgFile(const CString &strFile,BOOL bIsAT02D_CFG)//周宏军 20200616  增加AT02配置
{
	m_bModified = FALSE;

#ifdef _USE_IN_AT02D_MODE_
	if (bIsAT02D_CFG)
	{
		m_nType = IEC_CFG_DEVICE_USE_TYPE_AT02D;
		CExBaseObject *pCurObj = NULL;
		CIecCfgDatasMngr *pIecCfgDatasMngr = NULL;
		POS pos = GetHeadPosition();
//		long nDelayIndex = 1,nCurIndex = 1,nVolIndex = 1,nGinChIndex = 1,nGoutChIndex = 1;
		long nSV_CBIndex = 1,nGinCBIndex = 1,nGoutCBIndex = 1;
		CExBaseList oSVList,oGinList,oGoutList;
		CIecCfgDatasSMV oTmpSMVDatas;
		CIecCfgGinDatas oTmpGinDatas;
		CIecCfgGoutDatas oTmpGoutDatas;

		while(pos)
		{
			pCurObj = GetNext(pos);

			if (pCurObj->GetClassID() == CFGCLASSID_CIECCFGDATASMNGR)
			{
				pIecCfgDatasMngr = (CIecCfgDatasMngr *)pCurObj;
				pIecCfgDatasMngr->SetAT02D_ChannelID(&oSVList,&oGinList,&oGoutList,nSV_CBIndex,nGinCBIndex,nGoutCBIndex);
				pIecCfgDatasMngr->m_strScdFile = GetPathFileNameFromFilePathName(m_strIcdFile);//将SCD文件路径传递给ID用于显示SCD文件名称

				pIecCfgDatasMngr->AT02D_GetAllDatasRef(&oTmpSMVDatas,&oTmpGinDatas,&oTmpGoutDatas);
			}
		}

		oSVList.RemoveAll();
		oGinList.RemoveAll();
		oGoutList.RemoveAll();
		BOOL bInvalid1 = oTmpSMVDatas.IsAT02D_Invalid();
		BOOL bInvalid2 = oTmpGinDatas.IsAT02D_Invalid();
		BOOL bInvalid3 = oTmpGoutDatas.IsAT02D_Invalid();
		oTmpSMVDatas.RemoveAll();
		oTmpGinDatas.RemoveAll();
		oTmpGoutDatas.RemoveAll();

		if (bInvalid1 || bInvalid2 || bInvalid3)
		{
			return FALSE;
		}
	}
#endif

	return SaveXmlFile(strFile, CCfgDataMngrXmlRWKeys::g_pXmlKeys);
}

BOOL CIecCfgDevice::SaveAsIecCfgFile()
{
#ifdef _PSX_IDE_QT_
	return FALSE;
#else	
	CWnd *pMainFrame = AfxGetMainWnd();
	return pMainFrame->SendMessage(WM_SAVEAS_IecCfgFILE, 0, 0);
#endif
}

CIecCfgDatasMngr* CIecCfgDevice::CreateIecCfgDatasMngr(long nCfgDataCount)
{
	CIecCfgDatasMngr *pNew = new CIecCfgDatasMngr();
	pNew->CreateDefaultCfgDataMngr(nCfgDataCount);
	AddNewChild(pNew);

	return pNew;
}

#ifdef IecCfg_With_SCL
void CIecCfgDevice::SetSclIed(CSclIed *pIed)
{
	if (m_pSclIed != NULL)
	{
		Delete(m_pSclIed);
		m_pSclIed = NULL;
	}

	if (pIed == NULL)
	{
		return;
	}

	m_pSclIed = (CSclIed*)pIed->Clone();
	AddNewChild(m_pSclIed);
	m_strIcdFile = pIed->GetSCDFilePath();
}
#endif


void CIecCfgDevice::InitIecfgDataType(CDataType *pDataType)
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	long nIndex = 0;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFGDATASMNGR)
		{
			pDataType->AddNewValue(p->m_strName, p->m_strID, nIndex);
			nIndex++;
		}
	}
}

void CIecCfgDevice::UpdateGinChMaps()
{
	POS pos = GetHeadPosition();
	CExBaseObject *p = NULL;
	CIecCfgDatasMngr* pCurrDatasMngr = NULL;
	CIecCfgGinDatas *pGinMngr = NULL;

	while (pos != NULL)
	{
		p = (CExBaseObject *)GetNext(pos);

		if (p->GetClassID() == CFGCLASSID_CIECCFGDATASMNGR)
		{
			pCurrDatasMngr = (CIecCfgDatasMngr*)p;
			pGinMngr = pCurrDatasMngr->GetGinMngr();
			pGinMngr->InitAfterRead();
		}
	}
}

#ifdef _use_CIecCfgTool
CString CIecCfgDevice::GetIecfgDeviceFile(CWnd *pParent)
{
	CXFileMngr *pFileMngr = CIecCfgTool::GetIecCfgDeviceFileMngr();//zhouhj20180626 在打开选择配置文件时，重新搜索下文件夹
	pFileMngr->Research();
	
	return GetIecfgDeviceFile(pParent,pFileMngr );
}
#endif

CString CIecCfgDevice::GetIecfgDeviceFile(CWnd *pParent, CXFileMngr *pFileMngr)
{
	CString strFileName;

#ifndef _PSX_IDE_QT_
#ifdef NOT_USE_XLANGUAGE
	CDlgXFileMngr dlg(0,g_strDeviceIecCfgFilePostfix,_T("测试仪配置文件"),pFileMngr,OPEN_FILE_MODE,pParent);
#else
	CDlgXFileMngr dlg(0,g_strDeviceIecCfgFilePostfix,g_sLangTxt_TesterConfigFile/*_T("测试仪配置文件")*/,pFileMngr,OPEN_FILE_MODE,pParent);
#endif
	if(dlg.DoModal() == IDOK)
	{
		strFileName = dlg.GetFileName();
	}
#endif

	return strFileName;
}

//yyj
CIecCfgDataBase* CIecCfgDevice::FindIecCfgData(BYTE *pDstMac,BYTE *pSrcMac,UINT nAPPID,UINT nCMT,UINT nChCount)
{
	if (m_pCurrDatasMngr == NULL)
	{
		return NULL;
	}

	return m_pCurrDatasMngr->FindIecCfgData(pDstMac, pSrcMac, nAPPID, nCMT, nChCount);
}
