#include "StdAfx.h"
#include "CfgCapCmpTool.h"

CCfgCapCmpTool::CCfgCapCmpTool(void)
{
}

CCfgCapCmpTool::~CCfgCapCmpTool(void)
{
}

BOOL CCfgCapCmpTool::RegisterCmpData2(CStCapDeviceBase *pCapDevice)
{
	BOOL bCanCmp = TRUE;
	UINT nClassID = pCapDevice->GetClassID();

	switch (nClassID)
	{
	case CPDCLASSID_DEVICE91:
		RegisterCapDeviceData((CStCapDevice91*)pCapDevice);
		break;
	case CPDCLASSID_DEVICE92:
		RegisterCapDeviceData((CStCapDevice92*)pCapDevice);
		break;
	case CPDCLASSID_DEVICEGOOSE:
		RegisterCapDeviceData((CStCapDeviceGoose*)pCapDevice);
		break;
	default:
		bCanCmp = FALSE;
		break;
	}

	if (!bCanCmp)
	{
		return bCanCmp;
	}

	return bCanCmp;
}

void CCfgCapCmpTool::RegisterCapDeviceData(CStCapDevice91 *pCapDevice)
{
	//本身数据
	pCapDevice->InitAddress();
	CCfgSclCmpParaObjects *pParas = m_oCmpData2.GetDataParas();
	pParas->RegisterPara(CFGSCL_CMP_ID_MAC, pCapDevice->m_strDestAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_SRCMAC, pCapDevice->m_strSrcAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_APPID, pCapDevice->m_dwAppID, CFGSCL_PARA_TYPE_HEX, 2);
	//pParas->RegisterPara(CFGSCL_CMP_ID_Priority, pCapDevice->m_nPriority);
	pParas->RegisterPara(CFGSCL_CMP_ID_VID, pCapDevice->m_dwVID, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_Version, pCapDevice->m_dwVersion);
	pParas->RegisterPara(CFGSCL_CMP_ID_DataSet, pCapDevice->m_dwDataSet);
	pParas->RegisterPara(CFGSCL_CMP_ID_LNName, pCapDevice->m_dwLNName);
	//pParas->RegisterPara(CFGSCL_CMP_ID_LDName, pCapDevice->m_dwLDName);

	TPOS pos = pCapDevice->GetHeadPosition();
	CStCapDeviceSmvCh *pCh = NULL;

	if (!m_bUseChs)
	{
		return;
	}


	while (pos != NULL)
	{
		pCh = (CStCapDeviceSmvCh *)pCapDevice->GetNext(pos);
		pParas = m_oCmpData2.CreateNewChParaObjects();

		//pParas->RegisterPara(CFGSCL_CMP_ID_AppChID, pCh->m_strAppChID);
		pParas->RegisterPara(CFGSCL_CMP_ID_Name, pCh->m_strID);
	}
}

void CCfgCapCmpTool::RegisterCapDeviceData(CStCapDevice92 *pCapDevice)
{
	//本身数据
	CCfgSclCmpParaObjects *pParas = m_oCmpData2.GetDataParas();
	//	pParas->RegisterPara(_T("AppID"), pCfgData->m_strDestAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_MAC, pCapDevice->m_strDestAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_SRCMAC, pCapDevice->m_strSrcAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_APPID, pCapDevice->m_dwAppID, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_confRef, pCapDevice->m_nConfRev);
	pParas->RegisterPara(CFGSCL_CMP_ID_SVID, pCapDevice->m_strSVID);
	pParas->RegisterPara(CFGSCL_CMP_ID_SmpSynch, pCapDevice->m_nSmpSynch);
	//pParas->RegisterPara(CFGSCL_CMP_ID_Version, pCapDevice->m_dwVersion);
	//pParas->RegisterPara(CFGSCL_CMP_ID_DataSet, pCapDevice->m_strDataSet);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_nSyn);
	// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nCTBit);
	//  pParas->RegisterPara(_T("AppID"), pCfgData->m_nPTBit);
	//pParas->RegisterPara(CFGSCL_CMP_ID_TDelay, pCapDevice->m_nDelay);
	// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseSampRate);
	// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseDataSet);
	// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseSampleTime);
	// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseRefreshTime);
	// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseEncrupt);
	// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nVoltateRate);
	//	pParas->RegisterPara(_T("AppID"), pCfgData->m_nCurrRate);

	if (!m_bUseChs)
	{
		return;
	}

	TPOS pos = pCapDevice->GetHeadPosition();
	CStCapDeviceSmvCh *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CStCapDeviceSmvCh *)pCapDevice->GetNext(pos);
		pParas = m_oCmpData2.CreateNewChParaObjects();

		//pParas->RegisterPara(CFGSCL_CMP_ID_AppChID, pCh->m_strAppChID);
		pParas->RegisterPara(CFGSCL_CMP_ID_Name, pCh->m_strID);
	}
}

void CCfgCapCmpTool::RegisterCapDeviceData(CStCapDeviceGoose *pCapDevice)
{
	CCfgSclCmpParaObjects *pParas = m_oCmpData2.GetDataParas();

	pParas->RegisterPara(CFGSCL_CMP_ID_MAC, pCapDevice->m_strDestAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_SRCMAC, pCapDevice->m_strSrcAddress);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_strSrcAddress);
	pParas->RegisterPara(CFGSCL_CMP_ID_APPID, pCapDevice->m_dwAppID, CFGSCL_PARA_TYPE_HEX, 2);
	//pParas->RegisterPara(CFGSCL_CMP_ID_Priority, pCapDevice->m_nPriority);
	pParas->RegisterPara(CFGSCL_CMP_ID_VID, pCapDevice->m_dwVID, CFGSCL_PARA_TYPE_HEX, 2);
	pParas->RegisterPara(CFGSCL_CMP_ID_Version, pCapDevice->m_dwVersion);
	pParas->RegisterPara(CFGSCL_CMP_ID_goID, pCapDevice->m_strGooseId);
	pParas->RegisterPara(CFGSCL_CMP_ID_DataSet, pCapDevice->m_strDataSet);
	pParas->RegisterPara(CFGSCL_CMP_ID_DataSetDesc, pCapDevice->m_strDataSetDesc);
	pParas->RegisterPara(CFGSCL_CMP_ID_gocbRef, pCapDevice->m_strgocbRef);
	pParas->RegisterPara(CFGSCL_CMP_ID_gocbIED, pCapDevice->m_strgocbIED);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_nTest);
	//pParas->RegisterPara(CFGSCL_CMP_ID_T0, pCapDevice->m_nT0);
	//pParas->RegisterPara(CFGSCL_CMP_ID_T1, pCapDevice->m_nT1);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_nT2);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_nT3);	

	//通道数据
	if (!m_bUseChs)
	{
		return;
	}

	TPOS pos = pCapDevice->GetHeadPosition();
	CStCapDeviceGooseCh *pCh = NULL;

	while (pos != NULL)
	{
		pCh = (CStCapDeviceGooseCh *)pCapDevice->GetNext(pos);
		pCh->InitChTypeName();
		pParas = m_oCmpData2.CreateNewChParaObjects();
		pParas->RegisterPara(CFGSCL_CMP_ID_DataType, pCh->m_strChTypeName);
		//pParas->RegisterPara(CFGSCL_CMP_ID_AppChID, pCh->m_strAppChID);
		//pParas->RegisterPara(CFGSCL_CMP_ID_Name, pCh->m_strID);
	}
}
