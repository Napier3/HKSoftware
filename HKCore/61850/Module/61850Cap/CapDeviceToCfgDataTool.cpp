#include "StdAfx.h"
#include "CapDeviceToCfgDataTool.h"

CCapDeviceToCfgDataTool::CCapDeviceToCfgDataTool(void)
{
	m_bUseChs = TRUE;
}

CCapDeviceToCfgDataTool::~CCapDeviceToCfgDataTool(void)
{
}

BOOL CCapDeviceToCfgDataTool::CreateCfgData91(CStCapDevice91 *pCapDevice)
{
	UINT nClassID = pCapDevice->GetClassID();
	ASSERT (CPDCLASSID_DEVICE91 == nClassID);

	if (CPDCLASSID_DEVICE91 != nClassID)
	{
		return FALSE;
	}

	CStCfgData91 *pCfgData = new CStCfgData91();
	pCfgData->OpenCfgDefaultConfigFile();
	CopyDataFromCapDeviceToCfg(pCapDevice, pCfgData);
	pCfgData->SaveCfgDataTempFile();
	m_nCfgDataClassID = pCfgData->GetClassID();
	delete pCfgData;

	return TRUE;
}

BOOL CCapDeviceToCfgDataTool::CreateCfgData92(CStCapDevice92 *pCapDevice)
{
	UINT nClassID = pCapDevice->GetClassID();
	ASSERT (CPDCLASSID_DEVICE92 == nClassID);

	if (CPDCLASSID_DEVICE92 != nClassID)
	{
		return FALSE;
	}

	CStCfgData92 *pCfgData = new CStCfgData92();
	pCfgData->OpenCfgDefaultConfigFile();
	CopyDataFromCapDeviceToCfg(pCapDevice, pCfgData);
	pCfgData->SaveCfgDataTempFile();
	m_nCfgDataClassID = pCfgData->GetClassID();
	delete pCfgData;

	return TRUE;
}

BOOL CCapDeviceToCfgDataTool::CreateCfgDataGin(CStCapDeviceGoose *pCapDevice)
{
	UINT nClassID = pCapDevice->GetClassID();
	ASSERT (CPDCLASSID_DEVICEGOOSE == nClassID);

	if (CPDCLASSID_DEVICEGOOSE != nClassID)
	{
		return FALSE;
	}

	CStCfgDataGin *pCfgData = new CStCfgDataGin();
	pCfgData->OpenCfgDefaultConfigFile();
	CopyDataFromCapDeviceToCfg(pCapDevice, pCfgData);
	pCfgData->SaveCfgDataTempFile();
	m_nCfgDataClassID = pCfgData->GetClassID();
	delete pCfgData;

	return TRUE;
}

BOOL CCapDeviceToCfgDataTool::CreateCfgDataGout(CStCapDeviceGoose *pCapDevice)
{
	UINT nClassID = pCapDevice->GetClassID();
	ASSERT (CPDCLASSID_DEVICEGOOSE == nClassID);

	if (CPDCLASSID_DEVICEGOOSE != nClassID)
	{
		return FALSE;
	}

	CStCfgDataGout *pCfgData = new CStCfgDataGout();
	pCfgData->OpenCfgDefaultConfigFile();
	CopyDataFromCapDeviceToCfg(pCapDevice, pCfgData);
	pCfgData->SaveCfgDataTempFile();
	m_nCfgDataClassID = pCfgData->GetClassID();
	delete pCfgData;

	return TRUE;
}

BOOL CCapDeviceToCfgDataTool::OverwriteCfgData(CStCapDeviceBase *pCapDevice, CStCfgDataBase *pCfgData)
{
	UINT nCapDeviceClassID = pCapDevice->GetClassID();
	UINT nCfgDataClassID = pCfgData->GetClassID();

	if ((nCapDeviceClassID == CPDCLASSID_DEVICE91) && (nCfgDataClassID == CFGCLASSID_CSTCFG91DATA))
	{
		return OverwriteCfgData((CStCapDevice91 *)pCapDevice, (CStCfgData91 *)pCfgData);
	}

	if ((nCapDeviceClassID == CPDCLASSID_DEVICE92) && (nCfgDataClassID == CFGCLASSID_CSTCFG92DATA))
	{
		return OverwriteCfgData((CStCapDevice92 *)pCapDevice, (CStCfgData92 *)pCfgData);
	}

	if ((nCapDeviceClassID == CPDCLASSID_DEVICEGOOSE) && (nCfgDataClassID == CFGCLASSID_CSTCFGGINDATA))
	{
		return OverwriteCfgData((CStCapDeviceGoose *)pCapDevice, (CStCfgDataGout *)pCfgData);
	}

	if ((nCapDeviceClassID == CPDCLASSID_DEVICEGOOSE) && (nCfgDataClassID == CFGCLASSID_CSTCFGGOUTDATA))
	{
		return OverwriteCfgData((CStCapDeviceGoose *)pCapDevice, (CStCfgDataGout *)pCfgData);
	}

	return FALSE;
}

BOOL CCapDeviceToCfgDataTool::OverwriteCfgData(CStCapDevice91 *pCapDevice, CStCfgData91 *pCfgData)
{
	CopyDataFromCapDeviceToCfg(pCapDevice, pCfgData);
	pCfgData->SaveCfgDataTempFile();
	m_nCfgDataClassID = pCfgData->GetClassID();
	return TRUE;
}

BOOL CCapDeviceToCfgDataTool::OverwriteCfgData(CStCapDevice92 *pCapDevice, CStCfgData92 *pCfgData)
{
	CopyDataFromCapDeviceToCfg(pCapDevice, pCfgData);
	pCfgData->SaveCfgDataTempFile();
	m_nCfgDataClassID = pCfgData->GetClassID();
	return TRUE;
}

BOOL CCapDeviceToCfgDataTool::OverwriteCfgData(CStCapDeviceGoose *pCapDevice, CStCfgDataGin *pCfgData)
{
	CopyDataFromCapDeviceToCfg(pCapDevice, pCfgData);
	pCfgData->SaveCfgDataTempFile();
	m_nCfgDataClassID = pCfgData->GetClassID();
	return TRUE;
}

BOOL CCapDeviceToCfgDataTool::OverwriteCfgData(CStCapDeviceGoose *pCapDevice, CStCfgDataGout *pCfgData)
{
	CopyDataFromCapDeviceToCfg(pCapDevice, pCfgData);
	pCfgData->SaveCfgDataTempFile();
	m_nCfgDataClassID = pCfgData->GetClassID();
	return TRUE;
}

void CCapDeviceToCfgDataTool::CopyDataFromCapDeviceToCfg(CStCapDevice91 *pCapDevice, CStCfgData91 *pCfgData)
{
	//本身数据
	pCfgData->m_strDestAddress = st_GetMacString(pCapDevice->m_byteDestMac);
	pCfgData->m_strSrcAddress = st_GetMacString(pCapDevice->m_byteSrcMac);
	pCfgData->m_dwAppID = pCapDevice->m_dwAppID;
//	pCfgData->m_nPriority = pCapDevice->m_np
	pCfgData->m_dwVID = pCapDevice->m_dwVID;
	pCfgData->m_dwVersion = pCapDevice->m_dwVersion;
	pCfgData->m_dwDataSet = pCapDevice->m_dwDataSet;
	pCfgData->m_dwLNName = pCapDevice->m_dwLNName;
	//pCfgData->m_dwLDName = pCapDevice->m_dwLDName;

	//通道数据
	CStCfgChsBase *pCfgChs = pCfgData->m_pCfgChs;

	if (pCfgChs == NULL)
	{
		return ;
	}

	if (!m_bUseChs)
	{
		return;
	}

	pCfgChs->SetChannelNum(pCapDevice->GetCount());
	POS pos = pCfgChs->GetHeadPosition();
	CStCfg91Ch *pCh = NULL;
	POS posCapCh = pCapDevice->GetHeadPosition();
	CStCapDeviceSmvCh *pCapCh = NULL;

	while (pos != NULL && posCapCh != NULL)
	{
		pCh = (CStCfg91Ch *)pCfgChs->GetNext(pos);
		pCapCh = (CStCapDeviceSmvCh *)pCapDevice->GetNext(posCapCh);

		//pCh->m_strAppChID 
		pCh->m_strID = pCapCh->GetChType();
	}
}

void CCapDeviceToCfgDataTool::CopyDataFromCapDeviceToCfg(CStCapDevice92 *pCapDevice, CStCfgData92 *pCfgData)
{
	//本身数据
	pCfgData->m_strDestAddress = st_GetMacString(pCapDevice->m_byteDestMac);
	pCfgData->m_strSrcAddress = st_GetMacString(pCapDevice->m_byteSrcMac);
	pCfgData->m_dwAppID = pCapDevice->m_dwAppID;

// 	pParas->RegisterPara(CFGSCL_CMP_ID_Priority, pCfgData->m_nPriority);
	pCfgData->m_strSVID = pCapDevice->m_strSVID;
	//pParas->RegisterPara(CFGSCL_CMP_ID_VID, pCfgData->m_dwVID, CFGSCL_PARA_TYPE_HEX, 2);
	//pParas->RegisterPara(CFGSCL_CMP_ID_Version, pCfgData->m_dwVersion);
	//pParas->RegisterPara(CFGSCL_CMP_ID_DataSet, pCfgData->m_strDataSet);
	//pParas->RegisterPara(_T("AppID"), pCfgData->m_nSyn);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nCTBit);
//  pParas->RegisterPara(_T("AppID"), pCfgData->m_nPTBit);
	//pParas->RegisterPara(CFGSCL_CMP_ID_TDelay, pCfgData->m_nDelay);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseSampRate);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseDataSet);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseSampleTime);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseRefreshTime);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nUseEncrupt);
// 	pParas->RegisterPara(_T("AppID"), pCfgData->m_nVoltateRate);
//	pParas->RegisterPara(_T("AppID"), pCfgData->m_nCurrRate);

	//通道数据
	CStCfgChsBase *pCfgChs = pCfgData->m_pCfgChs;

	if (pCfgChs == NULL)
	{
		return ;
	}

	if (!m_bUseChs)
	{
		return;
	}

	pCfgChs->SetChannelNum(pCapDevice->GetCount());
	POS pos = pCfgChs->GetHeadPosition();
	CStCfg92Ch *pCh = NULL;
	POS posCapCh = pCapDevice->GetHeadPosition();
	CStCapDeviceSmvCh *pCapCh = NULL;

	while (pos != NULL && posCapCh != NULL)
	{
		pCh = (CStCfg92Ch *)pCfgChs->GetNext(pos);
		pCapCh = (CStCapDeviceSmvCh *)pCapDevice->GetNext(posCapCh);

		//pCh->m_strAppChID 
		pCh->m_strID = pCapCh->GetChType();
	}
}

void CCapDeviceToCfgDataTool::CopyDataFromCapDeviceToCfg(CStCapDeviceGoose *pCapDevice, CStCfgDataGin *pCfgData)
{
	//本身数据
	pCfgData->m_strDestAddress = st_GetMacString(pCapDevice->m_byteDestMac);
	pCfgData->m_strSrcAddress = st_GetMacString(pCapDevice->m_byteSrcMac);
	pCfgData->m_dwAppID = pCapDevice->m_dwAppID;

	pCfgData->m_dwVID = pCapDevice->m_dwVID ;
	pCfgData->m_dwVersion = pCapDevice->m_dwVersion ;
	pCfgData->m_strGooseId = pCapDevice->m_strGooseId ;
	pCfgData->m_strDataSet = pCapDevice->m_strDataSet ;
	pCfgData->m_strDataSetDesc = pCapDevice->m_strDataSetDesc ;
	pCfgData->m_strgocbRef = pCapDevice->m_strgocbRef ;
	pCfgData->m_strgocbIED = pCapDevice->m_strgocbIED ;
	pCfgData->m_nTest = pCapDevice->m_nTest ;
	// 	pCfgData->m_dwTimeAllowToAlive = pCapDevice->m_dwTimeAllowToAlive ;
	// 	pCfgData->m_dwStNum = pCapDevice->m_dwStNum ;
	// 	pCfgData->m_dwSqNum = pCapDevice->m_dwSqNum ;
	// 	pCfgData->m_dwNdsCom = pCapDevice->m_dwNdsCom ;

	//通道数据
	CStCfgChsBase *pCfgChs = pCfgData->m_pCfgChs;

	if (pCfgChs == NULL)
	{
		return ;
	}

	if (!m_bUseChs)
	{
		return;
	}


	pCfgChs->SetChannelNum(pCapDevice->GetCount());
	POS pos = pCfgChs->GetHeadPosition();
	CStCfgGoutCh *pCh = NULL;
	POS posCapCh = pCapDevice->GetHeadPosition();
	CStCapDeviceGooseCh *pCapCh = NULL;

	while (pos != NULL && posCapCh != NULL)
	{
		pCh = (CStCfgGoutCh *)pCfgChs->GetNext(pos);
		pCapCh = (CStCapDeviceGooseCh *)pCapDevice->GetNext(posCapCh);

		pCh->SetDataTypeByName(st_GetGooseChType(pCapCh->m_nChType, pCapCh->m_nLength));
	}
}

void CCapDeviceToCfgDataTool::CopyDataFromCapDeviceToCfg(CStCapDeviceGoose *pCapDevice, CStCfgDataGout *pCfgData)
{
	//本身数据
	pCfgData->m_strDestAddress = st_GetMacString(pCapDevice->m_byteDestMac);
	pCfgData->m_strSrcAddress = st_GetMacString(pCapDevice->m_byteSrcMac);
	pCfgData->m_dwAppID = pCapDevice->m_dwAppID;

	pCfgData->m_dwVID = pCapDevice->m_dwVID ;
	pCfgData->m_dwVersion = pCapDevice->m_dwVersion ;
	pCfgData->m_strGooseId = pCapDevice->m_strGooseId ;
	pCfgData->m_strDataSet = pCapDevice->m_strDataSet ;
	pCfgData->m_strDataSetDesc = pCapDevice->m_strDataSetDesc ;
	pCfgData->m_strgocbRef = pCapDevice->m_strgocbRef ;
	pCfgData->m_strgocbIED = pCapDevice->m_strgocbIED ;
	pCfgData->m_nTest = pCapDevice->m_nTest ;
// 	pCfgData->m_dwTimeAllowToAlive = pCapDevice->m_dwTimeAllowToAlive ;
// 	pCfgData->m_dwStNum = pCapDevice->m_dwStNum ;
// 	pCfgData->m_dwSqNum = pCapDevice->m_dwSqNum ;
// 	pCfgData->m_dwNdsCom = pCapDevice->m_dwNdsCom ;

	//通道数据
	CStCfgChsBase *pCfgChs = pCfgData->m_pCfgChs;

	if (pCfgChs == NULL)
	{
		return ;
	}

	if (!m_bUseChs)
	{
		return;
	}


	pCfgChs->SetChannelNum(pCapDevice->GetCount());
	POS pos = pCfgChs->GetHeadPosition();
	CStCfgGoutCh *pCh = NULL;
	POS posCapCh = pCapDevice->GetHeadPosition();
	CStCapDeviceGooseCh *pCapCh = NULL;

	while (pos != NULL && posCapCh != NULL)
	{
		pCh = (CStCfgGoutCh *)pCfgChs->GetNext(pos);
		pCapCh = (CStCapDeviceGooseCh *)pCapDevice->GetNext(posCapCh);

		pCh->SetDataTypeByName(st_GetGooseChType(pCapCh->m_nChType, pCapCh->m_nLength));
	}
}
