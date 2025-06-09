#include "StdAfx.h"
#include "CfgCmpToolBase.h"

CCfgCmpToolBase::CCfgCmpToolBase(void)
{
	m_bUseChs = TRUE;
}

CCfgCmpToolBase::~CCfgCmpToolBase(void)
{
}

BOOL CCfgCmpToolBase::CmpCfg()
{
	m_oCmpData1.Compare(&m_oCmpData2);

	return TRUE;
}

BOOL CCfgCmpToolBase::RegisterCmpData1(CIecCfgDataBase *pCfgData)
{
	UINT nClassID = pCfgData->GetClassID();
	BOOL bCanCmp = TRUE;

	switch(nClassID)
	{
	case CFGCLASSID_CSTCFG91DATA:
		RegisterCfgData((CIecCfgData91*)pCfgData);
		break;
	case CFGCLASSID_CSTCFG92DATA:
		RegisterCfgData((CIecCfgData92*)pCfgData);
		break;
	case CFGCLASSID_CSTCFG6044DATA:
		RegisterCfgData((CIecCfgData6044*)pCfgData);
		break;
	case CFGCLASSID_CSTCFGGINDATA:
		RegisterCfgData((CIecCfgDataGin*)pCfgData);
		break;
	case CFGCLASSID_CSTCFGGOUTDATA:
		RegisterCfgData((CIecCfgDataGout*)pCfgData);
		break;
	default:
		bCanCmp = FALSE;
	}

	return bCanCmp;
}

void CCfgCmpToolBase::RegisterCfgData(CIecCfgGooseDataBase *pCfgData)
{
	CCfgSclCmpParaObjects *pParas = m_oCmpData1.GetDataParas();

	pParas->RegisterPara(CFGSCL_CMP_ID_MAC, pCfgData->m_strDestAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_SRCMAC, pCfgData->m_strSrcAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_APPID, pCfgData->m_dwAppID, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_Version, pCfgData->m_dwVersion);
	//pParas->RegisterPara(CFGSCL_CMP_ID_Priority, pCfgData->m_nPriority);
	pParas->RegisterPara(CFGSCL_CMP_ID_VID, pCfgData->m_dwVID, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_gocbRef, pCfgData->m_strgocbRef);
	pParas->RegisterPara(CFGSCL_CMP_ID_goID, pCfgData->m_strGooseId);
	pParas->RegisterPara(CFGSCL_CMP_ID_DataSet, pCfgData->m_strDataSet);
 	pParas->RegisterPara(CFGSCL_CMP_ID_DataSetDesc, pCfgData->m_strDataSetDesc);
//	pParas->RegisterPara(CFGSCL_CMP_ID_gocbIED, pCfgData->m_strgocbIED);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_nTest);
	pParas->RegisterPara(CFGSCL_CMP_ID_T0, pCfgData->m_nT0);
	pParas->RegisterPara(CFGSCL_CMP_ID_T1, pCfgData->m_nT1);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_nT2);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_nT3);	

	//通道数据
	CIecCfgChsBase *pCfgChs = pCfgData->m_pCfgChs;

	if (pCfgChs == NULL)
	{
		return ;
	}

	if (!m_bUseChs)
	{
		return;
	}

	TPOS pos = pCfgChs->GetHeadPosition();
	CIecCfgDataGooseChBase *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfgGinCh *)pCfgChs->GetNext(pos);
		pParas = m_oCmpData1.CreateNewChParaObjects();
	
		pParas->RegisterPara(CFGSCL_CMP_ID_DataType, pCh->m_strDataTypeName);
		//pParas->RegisterPara(CFGSCL_CMP_ID_Name, pCh->m_strID);
		//pParas->RegisterPara(CFGSCL_CMP_ID_Name, pCh->m_strID);
	}
	
}

void CCfgCmpToolBase::RegisterCfgData(CIecCfgDataGin *pCfgData)
{
	RegisterCfgData((CIecCfgGooseDataBase*)pCfgData);
}

void CCfgCmpToolBase::RegisterCfgData(CIecCfgDataGout *pCfgData)
{
	RegisterCfgData((CIecCfgGooseDataBase*)pCfgData);
}

void CCfgCmpToolBase::RegisterCfgData(CIecCfgData91 *pCfgData)
{
	//本身数据
	CCfgSclCmpParaObjects *pParas = m_oCmpData1.GetDataParas();
	pParas->RegisterPara(CFGSCL_CMP_ID_MAC, pCfgData->m_strDestAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_SRCMAC, pCfgData->m_strSrcAddress);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_strSrcAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_APPID, pCfgData->m_dwAppID, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_Priority, pCfgData->m_nPriority);
	pParas->RegisterPara(CFGSCL_CMP_ID_VID, pCfgData->m_dwVID, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_Version, pCfgData->m_dwVersion);
	pParas->RegisterPara(CFGSCL_CMP_ID_DataSet, pCfgData->m_dwDataSet);
	pParas->RegisterPara(CFGSCL_CMP_ID_LNName, pCfgData->m_dwLNName);
	pParas->RegisterPara(CFGSCL_CMP_ID_LDName, pCfgData->m_dwLDName);

	//通道数据
	CIecCfgChsBase *pCfgChs = pCfgData->m_pCfgChs;

	if (pCfgChs == NULL)
	{
		return ;
	}

	if (!m_bUseChs)
	{
		return;
	}

	TPOS pos = pCfgChs->GetHeadPosition();
	CIecCfg91Ch *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfg91Ch *)pCfgChs->GetNext(pos);
		pParas = m_oCmpData1.CreateNewChParaObjects();

		//pParas->RegisterPara(CFGSCL_CMP_ID_AppChID, pCh->m_strAppChID);
		pParas->RegisterPara(CFGSCL_CMP_ID_Name, pCh->m_strID);
	}
}

void CCfgCmpToolBase::RegisterCfgData(CIecCfgData92 *pCfgData)
{
	//本身数据
	CCfgSclCmpParaObjects *pParas = m_oCmpData1.GetDataParas();
//	pParas->RegisterPara(_T("AppID"), pCfgData->m_strDestAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_MAC, pCfgData->m_strDestAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_SRCMAC, pCfgData->m_strSrcAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_APPID, pCfgData->m_dwAppID, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_Version, pCfgData->m_dwVersion);
	pParas->RegisterPara(CFGSCL_CMP_ID_Priority, pCfgData->m_nPriority);
	pParas->RegisterPara(CFGSCL_CMP_ID_VID, pCfgData->m_dwVID, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_SVID, pCfgData->m_strSVID);
	pParas->RegisterPara(CFGSCL_CMP_ID_DataSet, pCfgData->m_strDataSet);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_nSyn);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nCTBit);
//  pParas->RegisterPara(_T("AppID"), pCfgData->m_nPTBit);
//	pParas->RegisterPara(CFGSCL_CMP_ID_TDelay, pCfgData->m_nDelay);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseSampRate);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseDataSet);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseSampleTime);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseRefreshTime);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseEncrupt);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nVoltateRate);
//	pParas->RegisterPara(_T("AppID"), pCfgData->m_nCurrRate);

	//通道数据
	CIecCfgChsBase *pCfgChs = pCfgData->m_pCfgChs;

	if (pCfgChs == NULL)
	{
		return ;
	}

	if (!m_bUseChs)
	{
		return;
	}

	TPOS pos = pCfgChs->GetHeadPosition();
	CIecCfg92Ch *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CIecCfg92Ch *)pCfgChs->GetNext(pos);
		pParas = m_oCmpData1.CreateNewChParaObjects();

		//pParas->RegisterPara(CFGSCL_CMP_ID_AppChID, pCh->m_strAppChID);
		pParas->RegisterPara(CFGSCL_CMP_ID_Name, pCh->m_strID);
	}
}

void CCfgCmpToolBase::RegisterCfgData(CIecCfgData6044 *pCfgData)
{
	//本身数据
	CCfgSclCmpParaObjects *pParas = m_oCmpData1.GetDataParas();

	pParas->RegisterPara(CFGSCL_CMP_ID_LDName, pCfgData->m_dwLDName, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_LNName, pCfgData->m_dwLNName, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_DataSet, pCfgData->m_dwDataSetName, CFGSCL_PARA_TYPE_HEX, 2);
	//pParas->RegisterPara(CFGSCL_CMP_ID_TDelay, pCfgData->m_dwDelayTime, CFGSCL_PARA_TYPE_HEX, 2);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_dwTransSpeed);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_dwStateWord);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_dwINomPh);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_dwUNomPh);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_dwINomNeutral);

	//通道数据
	CIecCfgChsBase *pCfgChs = pCfgData->m_pCfgChs;

	if (pCfgChs == NULL)
	{
		return ;
	}

	if (!m_bUseChs)
	{
		return;
	}

	TPOS pos = pCfgChs->GetHeadPosition();
	CIecCfg6044Ch *pCh = NULL;

	while (pos != NULL)
	{
// 		pCh->m_strName = smvoptchnPtr->strDOIDes;
// 		pCh->m_strID = pCh->m_strName;
		pCh = (CIecCfg6044Ch *)pCfgChs->GetNext(pos);
		pParas = m_oCmpData1.CreateNewChParaObjects();
		//pParas->RegisterPara(CFGSCL_CMP_ID_AppChID, pCh->m_strAppChID);
		pParas->RegisterPara(CFGSCL_CMP_ID_Name, pCh->m_strID);
		pParas->RegisterPara(CFGSCL_CMP_ID_DataType, pCh->m_strChType);
	}
}
