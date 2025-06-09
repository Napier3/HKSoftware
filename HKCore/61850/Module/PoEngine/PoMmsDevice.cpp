// PoDevice.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "PoMmsDevice.h"
#include "../MmsGlobal.h"
// #include "IPSetObj.h"

#include "../../../Module/API/FileApi.h"
#include "../../../Protocol/Module/Engine/DeviceModel/DeviceModelXmlKeys.h"
#include "../../../Module/API/GlobalConfigApi.h"
// CPoMmsDevice

CPoMmsDevice::CPoMmsDevice()
{
	m_pACSI_NODE = NULL;
	m_pJournalDatas = NULL;
	m_bHasCreateDataInterface = FALSE;
	m_nDeviceIndex = -1;
	m_pProgress = NULL;

	m_oDsAttr.AddNewData(g_sLangTxt_CurrentActSet,       ATTRID_ACTSG, _T("INT"), _T("0"));//_T("��ǰ���ֵ��")
	m_oDsAttr.AddNewData(g_sLangTxt_SettingTotalNo,           ATTRID_NUMOFSG, _T("INT"), _T("8"));//_T("��ֵ������")
	m_oDsAttr.AddNewData(g_sLangTxt_CommandTotalTime,           ATTRID_TMTOTAL, _T("INT"), _T("0"));//_T("������ʱ��")
	m_oDsAttr.AddNewData(g_sLangTxt_CommandExecuTime,         ATTRID_TMEXEC, _T("INT"), _T("0"));//_T("����ִ��ʱ��")
	m_oDsAttr.AddNewData(g_sLangTxt_EnaChoseTime, ATTRID_TimeStartExec, _T("UTC_TIME"), _T("2020-1-1 8-0-0-0"));//_T("��ʼѹ��ѡ��ִ�е�ʱ��")	
	m_oDsAttr.AddNewData(g_sLangTxt_CommandChoseTime,         ATTRID_TMSEL, _T("INT"), _T("0"));//_T("����ѡ��ʱ��")
	m_oDsAttr.AddNewData(g_sLangTxt_CommandExecuMess,         ATTRID_InfoEXEC, _T("BIT_STR"), _T("0"));//_T("����ִ����Ϣ")
	m_oDsAttr.AddNewData(g_sLangTxt_CommandChoseMess,         ATTRID_InfoSEL, _T("BIT_STR"), _T("0"));//_T("����ѡ����Ϣ")
	m_oDsAttr.AddNewData(g_sLangTxt_WrongMess,             ATTRID_ERRINFO, _T("INT"), _T("0"));//_T("������Ϣ")
	m_oDsAttr.AddNewData(g_sLangTxt_RecordPath,             ATTRID_RECORD_PATH, _T("INT"), _T("0"));//_T("¼��·��")
	m_oDsAttr.AddNewData(g_sLangTxt_EnaChangeTime,     ATTRID_TimeGapEnaWrite, _T("INT"), _T("0"));//_T("ѹ���޸ļ��ʱ��")
	m_oDsAttr.AddNewData(g_sLangTxt_EnaChoseTime, ATTRID_TimeGapSelExec, _T("INT"), _T("0"));//_T("ѹ��ѡ��ִ�м��ʱ��")

	m_oDsAttr.AddNewData(g_sLangTxt_MonitErrorTime,         ATTRID_LogMmsMsg, _T("INT"), _T("0"));//_T("���Ӵ�����Ϣ")
	m_oDsAttr.AddNewData(g_sLangTxt_BeforEnaRead,         ATTRID_EnaReadBeforeWrite, _T("INT"), _T("0"));//_T("Ͷ��ѹ��ǰ��״̬")
	m_oDsAttr.AddNewData(g_sLangTxt_BeforEnaReadTime,   ATTRID_TEnaReadBeforeWrite, _T("INT"), _T("0"));//_T("Ͷ��ѹ��ǰ��״̬����ʱ")

	m_oDsAttr.AddNewData(g_sLangTxt_WritDataMess,         ATTRID_InfoWriteData, _T("BIT_STR"), _T("0"));//_T("д������Ϣ")
	m_oDsAttr.AddNewData(g_sLangTxt_SetEdtTime,         ATTRID_tmSetSE, _T("INT"), _T("0"));//_T("���ñ༭��ʱ��")
	m_oDsAttr.AddNewData(g_sLangTxt_SetActTime,         ATTRID_tmSetSG, _T("INT"), _T("0"));//_T("���û��ʱ��")
	m_oDsAttr.AddNewData(g_sLangTxt_SetEdtMess,         ATTRID_InfoSetSE, _T("BIT_STR"), _T("0"));//_T("���ñ༭����Ϣ")
	m_oDsAttr.AddNewData(g_sLangTxt_SetActMess,         ATTRID_InfoSetSG, _T("BIT_STR"), _T("0"));//_T("���û����Ϣ")

	m_oDsAttr.AddNewData(g_sLangTxt_TestConnSta,         ATTRID_TestLinkState, _T("INT"), _T("0"));//_T("��������״̬")
	m_oDsAttr.AddNewData(ATTRID_LogCount,         ATTRID_LogCount, _T("BIT_STR"), _T("0"));//_T("��־��Ŀ")
	m_oDsAttr.AddNewData(ATTRID_CurDirFileNum,         ATTRID_CurDirFileNum, _T("BIT_STR"), _T("0"));//_T("��ǰĿ¼���ļ�����Ŀ")

	m_oDsAttr.AddNewData(ATTRID_DVM_NAME_IS_STD,   ATTRID_DVM_NAME_IS_STD, _T("INT"), _T("0"));//_T("ӳ���ļ�ʹ�ñ�׼���Ʒ�ʽ")
	m_oDsAttr.AddNewData(ATTRID_COMM_Error_Code,   ATTRID_COMM_Error_Code, _T("INT"), _T("-1"));//ͨѶ���������ֵ
	m_oDsAttr.AddNewData(ATTRID_COMM_Error_Class,   ATTRID_COMM_Error_Class, _T("INT"), _T("-1"));//ͨѶ���������
	m_oDsAttr.AddNewData(ATTRID_COMM_Error_InforRpt,   ATTRID_COMM_Error_InforRpt, _T("INT"), _T("-1"));//ͨѶ���������Ϣ����

	m_pNewTempPoDataset = NULL;
}

CPoMmsDevice::~CPoMmsDevice()
{
	FreeTempPoDataset();
}

void CPoMmsDevice::AttachProgress(CThreadProgressInterface *pProgress)
{
	m_pProgress = pProgress;
}

void CPoMmsDevice::OnFinalRelease()
{
	
}


// CPoMmsDevice ��Ϣ�������

CString CPoMmsDevice::GetName(void)
{
	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������

	return strResult;
}

void CPoMmsDevice::SetName(const CString &newVal)
{
	// TODO: �ڴ�������Դ���������
}

CString CPoMmsDevice::GetID(void)
{
	// TODO: �ڴ���ӵ��ȴ���������

    return "";
}

void CPoMmsDevice::SetID(CString newVal)
{
	// TODO: �ڴ�������Դ���������
}

CDvmDeviceMap* CPoMmsDevice::GetDvmDeviceMap()
{
	if (m_oDvmDeviceMap.m_bDvmDeviceMapExist)
	{
		return &m_oDvmDeviceMap;
	}
	else
	{
		return NULL;
	}
}

BOOL CPoMmsDevice::IsDvmDeviceMapExist()
{
	return m_oDvmDeviceMap.m_bDvmDeviceMapExist;
}

BOOL CPoMmsDevice::IsValidIP(const CString &strIP)
{
	long nIndex = strIP.Find(_T("."));

	if (nIndex<=0)
	{
		return FALSE;
	}

	CString strTmp;
	strTmp = strIP.Mid(nIndex+1);

	nIndex = strTmp.Find(_T("."));

	if (nIndex<=0)
	{
		return FALSE;
	}

	strTmp = strTmp.Mid(nIndex+1);

	nIndex = strTmp.Find(_T("."));

	if (nIndex<=0)
	{
		return FALSE;
	}

	return TRUE;
}

long CPoMmsDevice::CommConfig(const CString &strCmmConfig)
{
	CDvmData *pData = NULL;
	CString strFile;
	CString strConfig;
	strConfig = strCmmConfig;
	BOOL bOpenMap = TRUE;
	m_nDeviceIndex = mms_GetDeviceNodeIndex(m_pACSI_NODE);

	if (strConfig.GetLength() > 5)
	{
		CDvmDataset oDvmDataset;

/*
		oDvmDataset.SetXml(_bstr_t(strConfig),CDataMngrXmlRWKeys::g_pXmlKeys);
		CDvmData *pDvmData = (CDvmData*)oDvmDataset.FindByID(_T("ip-addr"));

		if (pDvmData != NULL)
		{
			CString strOldIP,strKey,strPSW;
			CIPSetObj oIPSetObj; 
//			oIPSetObj.InitConfigPath(_P_GetBinPath());
			oIPSetObj.m_nDeviceIndex = m_nDeviceIndex;
			oIPSetObj.ReadIpFromConfigFile(strOldIP, strKey, strPSW);

			if ((strOldIP != pDvmData->m_strValue)&&(IsValidIP(pDvmData->m_strValue)))
			{
				mms_str_set(&m_pACSI_NODE->IpAddr,pDvmData->m_strValue);
				device_node_table[m_nDeviceIndex].IP1 = inet_addr(pDvmData->m_strValue);
				sock_info_table[m_nDeviceIndex].ip_addr = device_node_table[m_nDeviceIndex].IP1;
				oIPSetObj.WriteIpToCongfigFile(pDvmData->m_strValue, strKey, strPSW);//���µ�IPд�������ļ� zhouhj20190923
				oIPSetObj.WriteIpToVMDFile(_T(""), pDvmData->m_strValue, m_nDeviceIndex);
				theMmsApi->UpdateDeviceIP_Desc(m_nDeviceIndex);
			}
		}
*/
	}
	
	if (pData != NULL)
	{
		POS pos = pData->GetHeadPosition();
		CDvmValue *pValue = NULL;

		while (pos != NULL)
		{
			pValue = (CDvmValue *)pData->GetNext(pos);
			pValue->m_strID.MakeLower();

			if (pValue->m_strID.Find(strFile) >= 0)
			{
				bOpenMap = FALSE;
				break;
			}
		}
	}

	if (!g_bUseDvmMapFile)
	{
		bOpenMap = FALSE;
	}

	ASSERT (m_pACSI_NODE != NULL);

	if (IsFileExist(m_strDeviceFile))
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Device::CommConfig: %s"), m_strDeviceFile.GetString());
	}
	else
	{
		if ((m_strDeviceFile.GetLength()>2)&&(m_strDeviceFile.GetAt(1) != ':'))
		{
			CString strPath;
			strPath = _P_GetLibraryPath();
			m_strDeviceFile = strPath + m_strDeviceFile;
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Device::CommConfig: %s"), m_strDeviceFile.GetString());
		}
		else
		{
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Device::CommConfig: %s error"), m_strDeviceFile.GetString());
		}
	}

	//theMmsApi->SetAutoTestMode();

	if (m_strLastOpenDeviceFile != m_strDeviceFile && m_strDeviceFile.GetLength() > 0)
	{
		if (bOpenMap)
		{
			m_oDvmDeviceMap.OpenDvmMapFile(m_strDeviceFile);
		}

		if (mms_XmlRead(m_strDeviceFile, m_pACSI_NODE))
		{
			m_pACSI_NODE->nHasDeviceModel = 1;
			m_strLastOpenDeviceFile = m_strDeviceFile;
			//theMmsApi->InitDeviceNodeList(m_nDeviceIndex);

			m_oMmsDatasetMapTool.Attach(m_pACSI_NODE, &m_oDvmDeviceMap, m_nDeviceIndex);
			m_oMmsDatasetMapTool.mms_Init_ACSI_NODE_Map(m_pACSI_NODE, &m_oDvmDeviceMap);
		}
		else
		{
			m_pACSI_NODE->nHasDeviceModel = 0;
		}
	}

	theMmsApi->AttatchProgress(m_nDeviceIndex, m_pProgress);

	if (g_bMmsEngineDebugMode)
	{
		theMmsApi->m_oFuncParamEx[m_nDeviceIndex].set_DevIndex(m_nDeviceIndex);
		theMmsApi->m_oFuncParamEx[m_nDeviceIndex].SetsConnectDevice(TRUE);
	}
	else
	{
		if (g_bMmsEngineSingleDeviceMode)
		{
			if (m_pACSI_NODE->bConnect)
			{
				mms_PostDeviceSysMessage(m_pACSI_NODE, engineConnectDeviceSuccessful, engineConnectDeviceSuccessful);
				return 0;
			}
		}

		theMmsApi->InitLinkDeviceFuncPara_AutoTest(m_nDeviceIndex, FALSE);
		theMmsApi->CallFirstFunc(m_nDeviceIndex);
	}

	return 0;
}

long CPoMmsDevice::IsConnectSuccessful(void)
{
	if (m_pACSI_NODE == NULL)
	{
		return 0;
	}

	if(g_bMmsEngineDebugMode == 1)
	{
		return 1;
	}

	if (m_pACSI_NODE->bTestLinkState)
	{
		return TRUE;
	}
	else
	{
		return m_pACSI_NODE->bConnect;
	}
}

long CPoMmsDevice::GetCount(void)
{
	//�����豸�Ľڵ����
	return m_pACSI_NODE->numLD;
}

CPoMmsLogicDevice* CPoMmsDevice::GetItem(long nIndex)
{
	if (nIndex >= m_pACSI_NODE->numLD)
	{
		return NULL;
	}

	//�����豸�Ľڵ�
	CPoMmsLogicDevice *pLogicDevice = CPoMmsLogicDevice::_New_CDeviceNode_LD(m_pACSI_NODE, &(m_pACSI_NODE->LD[nIndex]));

	if (pLogicDevice == NULL)
	{
		return NULL;
	}

	return pLogicDevice;
}

CString CPoMmsDevice::GetDsPathMap(const CString &strDsPath)
{
	if (!IsDvmDeviceMapExist())
	{
		return strDsPath;
	}

	CDvmDeviceMap *pCDvmDeviceMap = GetDvmDeviceMap();
	CDvmDatasetMap *pDvmDatasetMapFind = NULL;
	CString strTemp;
	strTemp = strDsPath;
	long nPos = strTemp.Find(_T("LLN0$"));

	if (nPos >= 0)
	{
		CString strLdId, strDsId;
		strLdId = strTemp.Left(nPos-1);
		strDsId = strTemp.Mid(nPos);
		pDvmDatasetMapFind = pCDvmDeviceMap->FindDsMap(strLdId, strDsId);

		if (pDvmDatasetMapFind != NULL)
		{
			strTemp = pDvmDatasetMapFind->m_strLdviceMap + _T("$") + pDvmDatasetMapFind->m_strMapID;
		}
	}

	return strTemp;
}

BOOL CPoMmsDevice::GetDataPathMap(const CString &strDsPath, CString &strLdID, CString &strDsID, CString &strDataID)
{
	strDataID = strDsPath;

	if (!IsDvmDeviceMapExist())
	{
		return FALSE;
	}

	CDvmDeviceMap *pCDvmDeviceMap = GetDvmDeviceMap();
	CDvmDatasetMap *pDvmDatasetMapFind = NULL;
	CDvmDataMap *pDvmDataMapFind = NULL;
	CString strTemp;
	strTemp = strDsPath;
	long nPos = -1;//strTemp.Find(_T("LLN0$"));
	nPos = mms_Get_LdID_DsPath(strTemp, strLdID, strDsID);

	if (nPos >= 0)
	{
// 		strLdID = strTemp.Left(nPos-1);
// 		strDsID = strTemp.Mid(nPos);
		pDvmDataMapFind = pCDvmDeviceMap->FindDataMapObj(strLdID, strDsID);

		if (pDvmDataMapFind != NULL)
		{
			pDvmDatasetMapFind = (CDvmDatasetMap*)pDvmDataMapFind->GetParent();
			strLdID   = pDvmDatasetMapFind->m_strLdviceMap;
			strDsID   = pDvmDatasetMapFind->m_strMapID;
			strDataID = pDvmDataMapFind->m_strMapID;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		pDvmDataMapFind = pCDvmDeviceMap->FindDataMapObj(strTemp);

		if (pDvmDataMapFind != NULL)
		{
			pDvmDatasetMapFind = (CDvmDatasetMap*)pDvmDataMapFind->GetParent();
			strLdID   = pDvmDatasetMapFind->m_strLdviceMap;
			strDsID   = pDvmDatasetMapFind->m_strMapID;
			strDataID = pDvmDataMapFind->m_strMapID;
			return TRUE;
		}
		else
		{
			return FALSE;
		}

		return FALSE;
	}
}

BOOL CPoMmsDevice::GetDataPathMap_DsKey(const CString &strDsKey,  const CString &strDsPath, CString &strLdID, CString &strDsID, CString &strDataID)
{
	strDataID = strDsPath;

	if (!IsDvmDeviceMapExist())
	{
		return FALSE;
	}

	CDvmDeviceMap *pCDvmDeviceMap = GetDvmDeviceMap();
	CDvmDatasetMap *pDvmDatasetMapFind = NULL;
	CDvmDataMap *pDvmDataMapFind = NULL;
	CString strTemp;
	strTemp = strDsPath;
	long nPos = -1;//strTemp.Find(_T("LLN0$"));
	nPos = mms_Get_LdID_DsPath(strTemp, strLdID, strDsID);

	if (nPos >= 0)
	{
// 		strLdID = strTemp.Left(nPos-1);
// 		strDsID = strTemp.Mid(nPos);
		pDvmDataMapFind = pCDvmDeviceMap->FindDataMapObj(strLdID, strDsID);

		if (pDvmDataMapFind != NULL)
		{
			pDvmDatasetMapFind = (CDvmDatasetMap*)pDvmDataMapFind->GetParent();
			strLdID   = pDvmDatasetMapFind->m_strLdviceMap;
			strDsID   = pDvmDatasetMapFind->m_strMapID;
			strDataID = pDvmDataMapFind->m_strMapID;
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		pDvmDataMapFind = pCDvmDeviceMap->FindDataMapObj_DsKey(strDsKey, strTemp);

		if (pDvmDataMapFind == NULL)
		{
			pDvmDataMapFind = pCDvmDeviceMap->FindDataMapObj(strTemp);
		}

		if (pDvmDataMapFind != NULL)
		{
			pDvmDatasetMapFind = (CDvmDatasetMap*)pDvmDataMapFind->GetParent();
			strLdID   = pDvmDatasetMapFind->m_strLdviceMap;
			strDsID   = pDvmDatasetMapFind->m_strMapID;
			strDataID = pDvmDataMapFind->m_strMapID;
			return TRUE;
		}
		else
		{
			return FALSE;
		}

		return FALSE;
	}
}

CPoMmsDataSet* CPoMmsDevice::FindDataSet(const CString &strDataSetName)
{
	CString strDsPath = strDataSetName;
	strDsPath.MakeLower();

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Device::FindDataSet��%s��"), strDsPath);
	if (strDsPath == _T("none"))
	{
		return NULL;
	}

	if (strDsPath.Find(dsID_MmsDvmAttr) >= 0)
	{
		FreeTempPoDataset();
		m_pNewTempPoDataset = CPoMmsDataSet::_NewPoDataset(m_pACSI_NODE, &m_oDsAttr);
		return m_pNewTempPoDataset;
	}

	if (strDsPath == dsID_Report || strDsPath.GetLength() == 0)
	{
		FreeTempPoDataset();
		m_pNewTempPoDataset = CPoMmsDataSet::_NewPoDataset(m_pACSI_NODE, m_pACSI_NODE->Reports);
		m_pNewTempPoDataset->m_strReadSoeDsPath = m_strReadSoeDsPath;
		m_pNewTempPoDataset->m_pDvmDeviceMap = GetDvmDeviceMap();
		return m_pNewTempPoDataset;
	}
	else if (strDsPath == dsID_Record || strDsPath == dsID_File)
	{
		m_pNewTempPoDataset = CPoMmsDataSet::_NewPoFileDir(m_pACSI_NODE, &m_pACSI_NODE->FileDir);
		return m_pNewTempPoDataset;
	}


	//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
	//2016-1-24
	CString strProcedureID;
	strProcedureID = m_strProcedureID;
	strProcedureID.MakeLower();

	if (strProcedureID == CMDID_ReadDataOne)
	{
		if (m_strCmdIdParaDsPath.GetLength() > 0)
		{
			strDsPath = m_strCmdIdParaDsPath;
		}
		else
		{
			strDsPath = strDataSetName;
		}
	}
	else
	{
		strDsPath = strDataSetName;
	}

	if (IsDvmDeviceMapExist())
	{//����ӳ���ϵ
		LD_NODE *pLdevice = NULL;//zhouhj 20180607 ���ǲ���ģ��ӳ�䷽ʽʱ�����͵�dsRelayAin���ݼ��������Զ�����δʹ�ã����Խ��Ϊ�գ����-100%
		LD_DATASET_INFO *pDataset = mms_FindDatasetEx(m_pACSI_NODE, strDsPath, &pLdevice);
		FreeTempPoDataset();
		m_pNewTempPoDataset = CPoMmsDataSet::_NewPoDataset(m_oMmsDatasetMapTool.m_pACSI_NODE, pLdevice, pDataset);
		m_pNewTempPoDataset->m_strDatasetPath = strDsPath;
		m_pNewTempPoDataset->m_pMmsDatasetMapTool = &m_oMmsDatasetMapTool;

		m_oMmsDatasetMapTool.SetStandPath(strDsPath);
// 		m_pNewTempPoDataset = CPoMmsDataSet::_NewPoDataset(&m_oMmsDatasetMapTool);
		return m_pNewTempPoDataset;
	}
	else
	{//ֱ�ӻ�ȡ���ݼ�
		LD_NODE *pLdevice = NULL;
		LD_DATASET_INFO *pDataset = mms_FindDatasetEx(m_pACSI_NODE, strDsPath, &pLdevice);

		if (pDataset == NULL)
		{
			return NULL;
		}

		FreeTempPoDataset();
		m_pNewTempPoDataset = CPoMmsDataSet::_NewPoDataset(m_pACSI_NODE, pLdevice, pDataset);
		m_pNewTempPoDataset->m_strDatasetPath = strDsPath;
		return m_pNewTempPoDataset;
	}
}

CPoMmsData* CPoMmsDevice::FindData(const CString &strPath)
{
	CString strResult;
	
	CString strText;
	strText = strPath;
	tagDA *pDA = NULL;
	CPoMmsData *pData = NULL;

	if (strText.Find(_T("$")) >= 0)
	{
		LD_NODE *pLdevice = NULL;
		LD_DATASET_INFO *pDataset = NULL;
		pDA = mms_FindData(m_pACSI_NODE, &pLdevice, &pDataset, strPath);

		if (pDA == NULL)
		{
			return NULL;
		}

		pData = CPoMmsData::_NewPoData(m_pACSI_NODE, pLdevice, pDataset, pDA);
	}
	else
	{
		m_oShortData.m_strName = strText;
		m_oShortData.m_strID   = strText;
		//strText.MakeUpper();

		InitDataAttr(strText);
		
		pData = CPoMmsData::_NewPoData(&m_oShortData);
	}

	return pData;
}

void CPoMmsDevice::InitDataAttr(const CString &strAttrID)
{
	InitDataAttr(strAttrID, m_oShortData.m_strValue);
}

void CPoMmsDevice::InitDataAttr(const CString &strAttrID, CString &strValue)
{
	CDvmData oData;
	oData.m_strID = strAttrID;

	po_GetXmlDataEx_DvmData(&oData, m_pACSI_NODE);

	strValue = oData.m_strValue;
}

BOOL CPoMmsDevice::CmdNeedDsPath(const CString &strCmdID)
{
	if (strCmdID == CMDID_readsoe 
		|| strCmdID == CMDID_reset 
		|| strCmdID == CMDID_changesetzone
		/*|| strCmdID == CMDID_writeenaone */
		|| strCmdID == CMDID_readzone
		|| strCmdID == CMDID_connect || strCmdID == CMDID_disconnect
		|| strCmdID == CMDID_SetDataRef
		|| strCmdID == CMDID_readsoeds
		|| strCmdID == CMDID_read_dir || strCmdID == CMDID_read_file
		|| strCmdID == CMDID_uploadfile
		|| strCmdID == CMDID_dvmenum
		|| strCmdID == CMDID_logmmserr)
	{
		return FALSE;
	}
	else
	{
		return TRUE;
	}
}

long CPoMmsDevice::GetCmdID(const CString &strCmdID, long &nCmdID, long &nCmdState, long &wParam, long &lParam)
{
	nCmdID = 0;

    if (strCmdID == CMDID_writesetting)
	{//�޸Ķ�ֵ
		nCmdID = FuncID_CnfSetSE;
	}
    else if (strCmdID == CMDID_writeena)
	{//�޸���ѹ��
		nCmdID = FuncID_CtrlWrite;
	}
    else if (strCmdID == CMDID_writedout )
	{//�޸���ѹ��
		nCmdID = FuncID_CtrlWrite;
	}
    else if (strCmdID == CMDID_changesetzone )
	{
		nCmdID = FuncID_SetSGNum;
	}

	if (nCmdID == 0)
	{
		return FALSE;
	}

	GetVariableVal(ParaID_CmdState, nCmdState, 0);
	GetVariableVal(ParaID_wParam, wParam, 0);
	GetVariableVal(ParaID_lParam, lParam, 0);

	return TRUE;
}

long CPoMmsDevice::RunProcedure(const CString &strProcedureID, const CString &strDatasetPath)
{
	m_strCmdIdParaDsPath.Empty();
	m_strReadSoeDsPath.Empty();
	m_pACSI_NODE->nWriteErrorCount = 0;
	CString strID;
	strID = strProcedureID;
	strID.MakeLower();
	long nLdIndex = -1;//zhouhj 20180409 ��Ϊ֮����Ҫ��֤���豸�Ƿ���ڣ��ʴ˴�������Ϊ-1
	long nDatasetIndex = 0;
	long nDeviceIndex = mms_GetDeviceNodeIndex(m_pACSI_NODE);

	
	CString strDsPathTemp = strDatasetPath;
	m_strProcedureID = strID;
	m_strCmdIdParaDsPath = strDatasetPath;

	if (IsDvmDeviceMapExist())
	{
		m_oMmsDatasetMapTool.SetDataPath(_T(""));
		m_oMmsDatasetMapTool.SetStandPath(strDsPathTemp);
		m_oMmsDatasetMapTool.SetProcedureID(strID);
	}

	CString strMsg;
    strMsg.Format(g_sLangTxt_ExecConnCommand.GetString()
                  , strID.GetString(),nDeviceIndex, nLdIndex, nDatasetIndex);//_T("ִ���ⲿͨѶ���%s����ACSIDevice=%d  LdIndex=%d  DatasetIndex=%d")

	if (strID == CMDID_ReadMmsAttr || strID == CMDID_WriteMmsAttr)
	{
		//theMmsApi->OutputPrintMsg(strMsg);
		CLogPrint::LogString(XLOGLEVEL_TRACE, strMsg);
		mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommFinish, engineCommFinish);
		return 0;
	}
	else
	{
		m_pACSI_NODE->InfoSel[0] = 0;
		m_pACSI_NODE->InfoExec[0] = 0;
		m_pACSI_NODE->tmSel = 0;
		m_pACSI_NODE->tmExec = 0;
		m_pACSI_NODE->tmSetSE = 0;
		m_pACSI_NODE->tmSetSG = 0;
		m_pACSI_NODE->tmTotal = 0;
		m_pACSI_NODE->InfoSetSE[0] = 0;
		m_pACSI_NODE->InfoSetSG[0] = 0;
		m_pACSI_NODE->InfoWriteData[0] = 0;
	}

	if (!CmdNeedDsPath(strID))
	{
	}
	else
	{

		BOOL bDsExist = TRUE;

		if (IsDvmDeviceMapExist())//zhouhj ����ʹ�����ݼ�·���Ĵ˴�����Ҫ���¸�nLdIndex  nDatasetIndex��ֵ
		{
			bDsExist = (m_oMmsDatasetMapTool.GetCount() > 0);

			if (bDsExist)
			{
				CMmsDvmDs_LdNode_Map *pMap = (CMmsDvmDs_LdNode_Map*)m_oMmsDatasetMapTool.GetHead();
				nLdIndex = pMap->m_nLD_NODE;
				nDatasetIndex = pMap->m_nDATASET_INFO;
			}
		}
		else
		{
			bDsExist = mms_FindDatasetIndex(m_pACSI_NODE, strDsPathTemp, nLdIndex, nDatasetIndex);
		}

		if (!bDsExist)
		{//�߼��豸������
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                                       ,g_sLangTxt_DatasetPathError.GetString() , strDsPathTemp.GetString());//_T("���ݼ�·����%s������ȷ")
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommCmdError, engineCommCmdError);
			return 0;
		}
	}

//	theMmsApi->m_strCurrCmdID = strProcedureID;
	theMmsApi->m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();


	if (strID == CMDID_readain)
	{//��ң��
		if (g_bMmsReadUseReport == 1)
		{
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommFinish, engineCommFinish);
			return 0;
		}
		else
		{
			//theMmsApi->InitReadFuncPara(nDeviceIndex,  nLdIndex, dsID_Ain);
			theMmsApi->InitReadFuncPara(nDeviceIndex,  nLdIndex, nDatasetIndex);
		}
	}
	else if (strID == CMDID_readsetting)
	{//����ֵ
		Run_CMDID_readsetting(nDeviceIndex, nLdIndex, nDatasetIndex);
	}
	else if (strID == CMDID_readdataset)
	{//�����ݼ�
		long nUseRead = 0;
		GetVariableVal(ParaID_UseRead, nUseRead, 1);

		if (nUseRead == 0)
		{//�������ݣ�ֱ�ӷ���
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommFinish, engineCommFinish);
			return 0;
		}
		else
		{
			theMmsApi->InitReadFuncPara(nDeviceIndex, nLdIndex, nDatasetIndex);
		}
	}
	else if (strID == CMDID_read_dir)
	{//ö���ļ�Ŀ¼
		CTime tmStart = 0, tmEnd = 0;
		__int64 int64Start,int64End;
		CString strPath,strTmp;
		GetVariableVal(ParaID_tmStart, tmStart);
		GetVariableVal(ParaID_tmEnd, tmEnd);
		int64Start = tmStart.GetTime();
		int64End = tmEnd.GetTime();
		long nMode = 0,nNewNum = -1;
		GetVariableVal(ParaID_Mode,nMode ,0);// 0Ϊ������ȡģʽ����ȡ��·����ȫ���ļ���1Ϊ��ȡ��·����ȫ��ָ��ʱ���¼���ļ���2Ϊ��ȡָ����Ŀ������¼���ļ���
		GetVariableVal(ParaID_NewFNum, nNewNum,-1);
		GetVariableVal(ParaID_path, strPath, _T(""));

		if (nMode == 1)//���Ӱ�ʱ����ҵ�����
		{
			strTmp.Format(_T("%lld^%lld/COMTRADE/"),int64Start,int64End);
			strPath = strTmp;
		}
		else if ((nMode == 2)&&(nNewNum>0))//���Ӱ�������Ŀ���ҵ�����
		{
			strTmp.Format(_T("/COMTRADE/NEWEST_%d/"),nNewNum);
			strPath = strTmp;
		}
		
		theMmsApi->InitGetFileDir(nDeviceIndex, strPath);//����2ָװ���ڵ�Ŀ¼��Ϊ�ձ�ʾ����Ŀ¼�µ������ļ����ļ���
	}
	else if (strID == CMDID_read_file)
	{//���ļ�
		CString strFileName,strFolderPath;
		int nIndex = -1;
//		GetVariableVal(ParaID_path, theMmsApi->m_strRecordFilePath, theMmsApi->GetDefaultRecordPath(nDeviceIndex));
		GetVariableVal(ParaID_File, strFileName, _T(""));
		strFileName.Replace("\"","");
		strFolderPath = strFileName;//zhow:m_strRecordPathֻ�Ǽ�¼�˱��ⱨ���·�����˴���Ҫ����װ���ڵ�Ŀ¼�ļ�������
		strFolderPath.Replace("/","\\");
		nIndex = strFolderPath.ReverseFind('\\');

		if (nIndex != -1)
		{
			strFolderPath = strFolderPath.Left(nIndex+1);
		}
		else
			strFolderPath = "";

		strFolderPath = m_strRecordPath + strFolderPath;
		theMmsApi->InitGetFile(nDeviceIndex, strFolderPath,strFileName);
	}
	else if (strID == CMDID_writesetting)
	{//�޸Ķ�ֵ
		if (! Run_CMDID_writesetting(nDeviceIndex, nLdIndex, nDatasetIndex))
		{
			return 0;
		}
	}
	else if (strID == CMDID_readena)
	{//����ѹ��
		Run_CMDID_readena(nDeviceIndex,  nLdIndex, nDatasetIndex);
	}
	else if (strID == CMDID_writeena)
	{//�޸���ѹ��
		Run_CMDID_writeena(nDeviceIndex,  nLdIndex, nDatasetIndex,g_sLangTxt_Ena, key_dsRelayEna);// _T("ѹ��")
	}
	else if (strID == CMDID_writedout)
	{//�޸���ѹ��
		if (strDsPathTemp.Find(key_dsGOOSE) > 0)
		{
			Run_CMDID_writeena(nDeviceIndex,  nLdIndex, nDatasetIndex,g_sLangTxt_RemoteCtl , key_dsGOOSE);//_T("ң��")
		}
		else
		{	
			Run_CMDID_writeena(nDeviceIndex,  nLdIndex, nDatasetIndex,g_sLangTxt_RemoteCtl , key_dsDout);//_T("ң��")
		}
	}
	else if (strID == CMDID_writeenaone)
	{//�޸���ѹ��
		if (!WriteEnaOne(nDeviceIndex,  nLdIndex))
		{
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommCmdError, engineCommCmdError);
			return 0;
		}
	}
	else if (strID == CMDID_ReadDataOne)
	{//����������
		if (!ReadOne())
		{
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommCmdError, engineCommCmdError);
			return 0;
		}
	}
	else if (strID == CMDID_readparameter)
	{//��װ�ò���
		Run_CMDID_readparameter(nDeviceIndex,  nLdIndex, nDatasetIndex);
	}
	else if (strID == CMDID_writeparameter)
	{//�޸�װ�ò���
		ACSI_NODE *pDevice = m_pACSI_NODE;

		if (!mms_HasDatasetDataChanged(pDevice/*nDeviceIndex*/, nLdIndex,nDatasetIndex))
		{
			//theMmsApi->OutputPrintMsg(g_sLangTxt_HadNoDataNeedEdit);//_T("û����Ҫ�޸ĵ�����"));
			CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_HadNoDataNeedEdit);
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommFinish, engineCommFinish);
			return 0;
		}

		theMmsApi->InitWriteFuncParasSingle(nDeviceIndex,  nLdIndex, nDatasetIndex);
	}
	else if (strID == CMDID_readsoe)
	{//��SOE
		theMmsApi->m_pMmsMsgRcvWnd->PostMessage(WM_PROCEDURE_RESET, nDeviceIndex, nDeviceIndex);
	}
	else if (strID == CMDID_readsoeds)
	{//��SOE
		GetVariableVal(_T("DsID"), m_strReadSoeDsPath, _T(""));
		m_strReadSoeDsPath.Replace(_T("\""), _T(""));
	}
	else if (strID == _T("writeyk"))
	{//��������

	}
	else if (strID == CMDID_reset)
	{//��λ
		enter_u_mvl_rpt_CriticSection();
		m_pACSI_NODE->nReportBeginIndex = m_pACSI_NODE->nCurrReportIndex;
		free_u_mvl_rpt_CriticSection();

		if (!g_bResetOnlyClearReport)
		{
			theMmsApi->ResetDevice(nDeviceIndex,  nLdIndex);
		}
		else
		{

		}

		theMmsApi->m_pMmsMsgRcvWnd->PostMessage(WM_PROCEDURE_RESET, nDeviceIndex, nDeviceIndex);
	}
	else if (strID == CMDID_registerreport)
	{//��ʼ����
		InitRegisterRptPara();

		if (IsDvmDeviceMapExist())
		{
			InitCallReportFuncParas(nDeviceIndex,  nLdIndex, nDatasetIndex, TRUE, _T(""));
		}
		else
		{
			theMmsApi->InitCallReportFuncParas(nDeviceIndex, nLdIndex, nDatasetIndex, TRUE, TRUE);
		}
	}
	else if (strID == CMDID_unregisterreport)
	{//ֹͣ����
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                                   ,g_sLangTxt_UnRegRepDataSet.GetString() , strDsPathTemp.GetString());//_T("unregisterreport:���ݼ���%s")

		if (IsDvmDeviceMapExist())
		{
			InitStopReportFuncParas(nDeviceIndex,  nLdIndex, nDatasetIndex, strDsPathTemp);
		}
		else
		{
			theMmsApi->InitStopReportFuncParas(nDeviceIndex, nLdIndex, nDatasetIndex);
		}
	}
	else if (strID == CMDID_changesetzone)
	{
		long nZone = -1;
		InitChangeSetZone(nZone);
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_SwitchSet.GetString() , nZone);//_T("�л���ֵ����%d")

		if (nZone == -1)
		{
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommCmdError, engineCommCmdError);
			return 0;
		}
	}
	else if (strID == CMDID_readzone)
	{
		m_pACSI_NODE->nSetRunSGIndexState = 1;
		theMmsApi->InitReadLDeviceZoneFuncParas(nDeviceIndex, -1);
	}
	else if (strID == CMDID_connect)
	{
		theMmsApi->m_bMmsDisConBfConnected = TRUE;
		theMmsApi->m_bMaxMmsConnectedTimes = 3;
		theMmsApi->InitLinkDeviceFuncPara_AutoTest(nDeviceIndex, TRUE);
	}
	else if (strID == CMDID_disconnect)
	{
		theMmsApi->InitUnLinkDeviceFuncPara(nDeviceIndex, TRUE, TRUE);
	}
	else if (strID == CMDID_logmmserr)
	{
		long nValue = 0;
		GetVariableVal(_T("log"), nValue, 0);
		mms_log_error_infor = nValue;
	}
	else if (strID == CMDID_SetDataRef)
	{//����������
		SetDataRef(strDsPathTemp);
	}
	else if (strID == CMDID_StartRecord)
	{//StartRecord���ݴ�ͳ��Լ��StartRecord����Ҫ��Ϊ������¼���ļ���·��

	}
	else if (strID == CMDID_ReadLogCount)
	{
		CString strJournalName;
		strJournalName = GetJournalName(nLdIndex,strDsPathTemp);
//		strLogCtrl = ;//Find LogCtrl by strDsPathTemp
		theMmsApi->InitReadJournalState(nDeviceIndex, nLdIndex, strJournalName, NULL);
	}
	else if (strID == CMDID_ReadLog)
	{
		CString strJournalName;
		strJournalName = GetJournalName(nLdIndex,strDsPathTemp);
		InitReadJournalFuncParas(nDeviceIndex, nLdIndex, nDatasetIndex, strJournalName);
	}
	else if (strID == CMDID_uploadfile)//Զ����������
	{
		CString strFiles;
		GetVariableVal(ParaID_File, strFiles, _T(""));
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CMDID_uploadfile: file=%s"), strFiles.GetString());
		CStringArray arrFilePaths;
		CString strFolderPath;
		strFolderPath = _P_GetSystemPath();
		strFolderPath += _T("UpLoadFiles\\");
		GetFilePaths(strFolderPath,strFiles ,arrFilePaths);
		theMmsApi->InitUploadFiles(nDeviceIndex,arrFilePaths);
	}
	else if (strID == CMDID_dvmenum)
	{
/*
		CString strFileName;
		BOOL bEnumSetting,bEnumRelayEna,bEnumParameter,bEnumRelayAin,bEnumRelayDin,bEnumTripInfor;
		BOOL bEnumAlarm_Warning,bEnumRelayBlk,bEnumRelayState,bEnumRelayFunEn,bEnumLog,bDevStdMsg;
		GetVariableVal(ParaID_FileName,strFileName,_T(""));
		GetVariableVal(ParaID_EnumSetting,bEnumSetting,FALSE);
		GetVariableVal(ParaID_EnumRelayEna,bEnumRelayEna,FALSE);
		GetVariableVal(ParaID_EnumParameter,bEnumParameter,FALSE);
		GetVariableVal(ParaID_EnumRelayAin,bEnumRelayAin,FALSE);
		GetVariableVal(ParaID_EnumRelayDin,bEnumRelayDin,FALSE);
		GetVariableVal(ParaID_EnumTripInfo,bEnumTripInfor,FALSE);
		GetVariableVal(ParaID_EnumAlarm_Warning,bEnumAlarm_Warning,FALSE);
		GetVariableVal(ParaID_EnumRelayBlk,bEnumRelayBlk,FALSE);
		GetVariableVal(ParaID_EnumRelayState,bEnumRelayState,FALSE);
		GetVariableVal(ParaID_EnumRelayFunEn,bEnumRelayFunEn,FALSE);
		GetVariableVal(ParaID_EnumLog,bEnumLog,FALSE);
		GetVariableVal(ParaID_DevStdMsg,bDevStdMsg,FALSE);
		theMmsApi->InitDvmEnum(nDeviceIndex,strFileName,bEnumSetting,bEnumRelayEna,bEnumParameter,bEnumRelayAin,bEnumRelayDin,bEnumTripInfor,bEnumAlarm_Warning,
			bEnumRelayBlk,bEnumRelayState,bEnumRelayFunEn,bEnumLog,bDevStdMsg,TRUE);
*/
		//�������
		mms_Free_ACSI_NODE( &pACSINode[nDeviceIndex]);
		theMmsApi->set_OnlyReadValue(SD_FALSE);
		theMmsApi->InitEnumLDFuncPara(nDeviceIndex, FALSE);  //ö��
		theMmsApi->InitReadDevice(nDeviceIndex,FALSE);
	}

	if (g_bMmsEngineDebugMode)
	{
		//ͨѶ����״̬������ͨѶ������Ϣ
// 		if (!theMmsApi->IsAutoTestMode())
// 		{
// 			return 0;
// 		}

		if (g_bMmsEngineCommError)
		{
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommError, engineCommError);
		}
		else
		{
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommFinish, engineCommFinish);
		}

		return 0;
	}

	if (theMmsApi->CallFirstFunc(nDeviceIndex))
	{
	}
	else
	{
		if (strID == CMDID_readsoe 
			|| strID == CMDID_reset 
			|| strID == CMDID_logmmserr 
			|| strID == CMDID_readsoeds 
			|| strID == CMDID_SetDataRef
			|| strID == CMDID_StartRecord)
		{
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommFinish, engineCommFinish);
		}
		else
		{
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommCmdError, engineCommCmdError);
		}
	}

	return 0;
}

CString CPoMmsDevice::GetJournalName(long nLdIndex,const CString &strDsPathTemp)
{
	CString strLogCtrl;

	if (nLdIndex<0)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ǰ����־����Ӧ��LD����ȷ."));
	}
	else
	{
		LD_LOG_INFO *pszLogInfo = m_pACSI_NODE->LD[nLdIndex].JournalCtrls.LogInfo;
		int nNum = m_pACSI_NODE->LD[nLdIndex].JournalCtrls.numData;
		CString strDatasetID = strDsPathTemp;
		long nTmpIndex = strDsPathTemp.Find('$');

		if (nTmpIndex>0)
		{
			strDatasetID = strDsPathTemp.Mid(nTmpIndex+1);
		}

		for (int nLen = 0;nLen<nNum;nLen++)
		{
			if (strcmp(mms_string(&pszLogInfo[nLen].Dataset),strDatasetID.GetString()) == 0)
			{
				strLogCtrl = mms_string(&pszLogInfo[nLen].Name);
				break;
			}
		}
	}

	if (strLogCtrl.IsEmpty())
	{
        CLogPrint::LogFormatString(XLOGLEVEL_ERROR,_T("��ʼ������־��Ŀ����,δ���ҵ���ӦLogName(strDsPathTemp=%s);"),strDsPathTemp.GetString());
	}

	return strLogCtrl;
}

extern long OptFlds_BP[9];
extern long OptFlds_RP[9];
extern long TrgOps_UI[5];

void CPoMmsDevice::InitRegisterRptPara()
{
	long nVal = -1;
	GetVariableVal(ParaID_TrgOps_1, nVal, -1);

	if (nVal != -1)
	{
		TrgOps_UI[0] = nVal;
		TrgOps_UI[0] = nVal;
	}
	
	GetVariableVal(ParaID_TrgOps_4, nVal, -1);

	if (nVal != -1)
	{
		TrgOps_UI[3] = nVal;
		TrgOps_UI[3] = nVal;
	}

	GetVariableVal(ParaID_IntgPd, g_nIntgPd, 3000);
}

void CPoMmsDevice::GetFilePaths(const CString &strFolderPath ,CString &strFiles ,CStringArray &arrFilePaths)
{
	CString strCurFilePath,strCurFileName;
	long nIndex = strFiles.Find(';');

	if (nIndex == -1)
	{
		return;
	}

	strCurFileName = strFiles.Left(nIndex);
    strCurFilePath.Format(_T("%s%s") ,strFolderPath.GetString() ,strCurFileName.GetString());
	strFiles = strFiles.Mid(nIndex+1);

	if (IsFileExist(strCurFilePath))
	{
		arrFilePaths.Add(strCurFilePath);
	}
	
	GetFilePaths(strFolderPath ,strFiles ,arrFilePaths);
}

void CPoMmsDevice::InitChangeSetZone(long &nZone)
{
	long nDeviceIndex = mms_GetDeviceNodeIndex(m_pACSI_NODE);
	long nLDeviceIndex = mms_FindLDeviceIndex(nDeviceIndex, "prot");//zhowTest20180111

	if (nLDeviceIndex == -1)
	{
		nLDeviceIndex = mms_FindLDeviceIndex(nDeviceIndex, "pqld1");//zhowTest20180111
	}

	if (nLDeviceIndex == -1)
	{
		nLDeviceIndex = mms_FindLDeviceIndex(nDeviceIndex, "rcd");
	}

	if (nLDeviceIndex == -1)
	{
		nZone = -1;
	}
	else
	{
		GetVariableVal(ParaID_setzone, nZone, nZone);
		theMmsApi->InitWriteLDeviceZoneFuncParas(nDeviceIndex, nLDeviceIndex, nZone);
	}
}

/*
<para type="Value" name="ѡ��ID" id="SelID" value=""/>
<para type="Value" name="ѡ��ֵ" id="SelValue" value=""/>
<para type="Value" name="ѡ�����ʱ" id="TDelayAfterSel" value="0"/>
<para type="Value" name="ִ��ID" id="OperID" value=""/>
<para type="Value" name="ִ��ֵ" id="OperValue" value=""/>
*/
BOOL CPoMmsDevice::WriteEnaOne(long nDeviceIndex, long  nLdIndex)
{
	long nLdIndex1 = -1, nDsIndex1= -1, nDaIndex1= -1;
	long nLdIndex2= -1, nDsIndex2= -1, nDaIndex2= -1;
	long nValue1= -1, nValue2= -1, nTdelay= -1;
	CString strValue;
	CString strPara1, strPara2;
	BOOL bFind = FALSE;

	bFind = GetCmdPara_Of_DataID(_T("SelID"), nLdIndex1, nDsIndex1, nDaIndex1, strPara1);

	if (bFind)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("WriteEnaOne: SelID=%s"), strPara1.GetString());
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("WriteEnaOne: SelID=%s  not exits"), strPara1.GetString());
		return FALSE;
	}

	bFind = GetCmdPara_Of_DataID(_T("OperID"), nLdIndex2, nDsIndex2, nDaIndex2, strPara2);

	if (bFind)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("WriteEnaOne: OperID=%s"), strPara2.GetString());
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("WriteEnaOne: OperID=%s  not exits"), strPara2.GetString());
		return FALSE;
	}

	GetVariableVal(_T("SelValue"), nValue1, 0);
	GetVariableVal(_T("OperValue"), nValue2, 0);
	GetVariableVal(_T("TDelayAfterSel"), nTdelay, 0);

	theMmsApi->InitCtrlWriteOneFuncParasEx(nDeviceIndex, nLdIndex1, nDsIndex1, nDaIndex1, nDaIndex2, nValue1, nValue2, nTdelay);
	return TRUE;
}

/*
BOOL CPoMmsDevice::WriteEnaOne(long nDeviceIndex, long  nLdIndex)
{
long nDeviceIndex = mms_GetDeviceNodeIndex(m_pACSI_NODE);
long nLdIndex1, nDsIndex1, nDaIndex1;
long nLdIndex2, nDsIndex2, nDaIndex2;
long nValue1, nValue2, nTdelay;
CString strValue;

GetVariableVal(_T("SelID"), strValue, _T(""));
strValue.Replace(_T("\""), _T(""));

CString strLdId, strDsId, strDataId;
BOOL bFind = GetDataPathMap(strValue, strLdId, strDsId, strDataId);

if (!bFind)
{
bFind = mms_FindDataByID(m_pACSI_NODE, strDataId, nLdIndex1, nDsIndex1, nDaIndex1);
}
else
{
bFind = mms_FindDataByID(m_pACSI_NODE, strLdId, strDsId, strDataId, nLdIndex1, nDsIndex1, nDaIndex1);
}

if (bFind)
{
CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("WriteEnaOne: SelID=%s"), strValue);
}
else
{
CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("WriteEnaOne: SelID=%s  not exits"), strValue);
return FALSE;
}

GetVariableVal(_T("OperID"), strValue, _T(""));
strValue.Replace(_T("\""), _T(""));
bFind = GetDataPathMap(strValue, strLdId, strDsId, strDataId);

if (!bFind)
{
bFind = mms_FindDataByID(m_pACSI_NODE, strDataId, nLdIndex2, nDsIndex2, nDaIndex2);
}
else
{
bFind = mms_FindDataByID(m_pACSI_NODE, strLdId, strDsId, strDataId, nLdIndex2, nDsIndex2, nDaIndex2);
}

if (!bFind)
{

}

if (bFind)
{
CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("WriteEnaOne: OperID=%s"), strValue);
}
else
{
CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("WriteEnaOne: OperID=%s  not exits"), strValue);
return FALSE;
}

GetVariableVal(_T("SelValue"), nValue1, 0);
GetVariableVal(_T("OperValue"), nValue2, 0);
GetVariableVal(_T("TDelayAfterSel"), nTdelay, 0);

theMmsApi->InitCtrlWriteOneFuncParasEx(nDeviceIndex, nLdIndex1, nDsIndex1, nDaIndex1, nDaIndex2, nValue1, nValue2, nTdelay);
return TRUE;
}

*/

BOOL CPoMmsDevice::GetDataIndex_DataID(const char *strDsKey, long &nLdIndex, long &nDsIndex, long &nDaIndex, CString &strRetDataID)
{
	CString strValue;

	GetVariableVal(_T("DataID"), strValue, _T(""));
	strValue.Replace(_T("\""), _T(""));

	if (strValue.GetLength() == 0)
	{
		strRetDataID = strValue;
	}
	CString strLdId, strDsId, strDataId;
	BOOL bFind = GetDataPathMap_DsKey(strDsKey, strValue, strLdId, strDsId, strDataId);

	if (!bFind)
	{
		bFind = mms_FindDataByID(strDsKey, m_pACSI_NODE, strDataId, nLdIndex, nDsIndex, nDaIndex);
	}
	else
	{
		bFind = mms_FindDataByID(m_pACSI_NODE, strLdId, strDsId, strDataId, nLdIndex, nDsIndex, nDaIndex);
	}

    m_strCmdIdParaDsPath = strLdId + strDsId;

	if (bFind)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DataID=%s[%s]  LD=%d  DS=%d  DA=%d"), strValue.GetString(), strDataId.GetString()
			, nLdIndex, nDsIndex, nDaIndex);
	}
	else
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DataID=%s  not exits"), strValue.GetString());
	}

	strRetDataID = strValue;

	return bFind;
}

BOOL CPoMmsDevice::GetCmdPara_Of_DataID(const CString &strParaKey, long &nLdIndex, long &nDsIndex, long &nDaIndex, CString &strRetDataID)
{
	CString strValue;

	GetVariableVal(strParaKey, strValue, _T(""));
	strValue.Replace(_T("\""), _T(""));

	if (strValue.GetLength() > 0)
	{
		strRetDataID = strValue;
	}

	if (strRetDataID.GetLength() == 0)
	{
		return FALSE;
	}

	//����ӳ���ϵ
	if (m_oMmsDatasetMapTool.FindDataId(strRetDataID, nLdIndex, nDsIndex, nDaIndex))
	{
		return TRUE;
	}

	//·����Ϣ
	CString strDsPath = m_oMmsDatasetMapTool.m_strStandDsPath;
	CString strLdId, strDsId, strDataId;
	BOOL bFind = FALSE;

	if (strDsPath.GetLength() > 0)
	{
		long nPos = strDsPath.Find('$');

		strLdId = strDsPath.Left(nPos);
		strDsId = strDsPath.Mid(nPos+1);
		
		if (strRetDataID.Find(strDsPath) >= 0)
		{
			strRetDataID = strRetDataID.Mid(strDsPath.GetLength() + 1);
		}
	}
	else
	{

	}


	if (strLdId.GetLength() > 0)
	{
		bFind = mms_FindDataByID(m_pACSI_NODE, strLdId, strDsId, strRetDataID, nLdIndex, nDsIndex, nDaIndex);;
	}
	else
	{
		bFind = mms_FindDataByID(m_pACSI_NODE, strRetDataID, nLdIndex, nDsIndex, nDaIndex,TRUE);
	}

	return bFind;
}

BOOL CPoMmsDevice::GetDataIndex_DataID(long &nLdIndex, long &nDsIndex, long &nDaIndex, CString &strRetDataID)
{
	CString strValue;

	GetVariableVal(_T("DataID"), strValue, _T(""));
	strValue.Replace(_T("\""), _T(""));

	if (strValue.GetLength() > 0)
	{
		strRetDataID = strValue;
	}

	if (strRetDataID.GetLength() == 0)
	{
		return FALSE;
	}

	//����ӳ���ϵ
	if (m_oMmsDatasetMapTool.FindDataId(strRetDataID, nLdIndex, nDsIndex, nDaIndex))
	{
		return TRUE;
	}

	//·����Ϣ
	CString strDsPath = m_oMmsDatasetMapTool.m_strStandDsPath;
	CString strLdId, strDsId, strDataId;
	BOOL bFind = FALSE;

	if (strDsPath.GetLength() > 0)
	{
		long nPos = strDsPath.Find('$');

		strLdId = strDsPath.Left(nPos);
		strDsId = strDsPath.Mid(nPos+1);
	}

	if ((strRetDataID.Find(strDsPath) >= 0)&&(!strDsPath.IsEmpty()))
	{
		strRetDataID = strRetDataID.Mid(strDsPath.GetLength() + 1);
	}

	if (strDataId.IsEmpty())
	{
		strDataId = strRetDataID;
	}
	
	if (strLdId.GetLength() > 0)
	{
		bFind = mms_FindDataByID(m_pACSI_NODE, strLdId, strDsId, strDataId, nLdIndex, nDsIndex, nDaIndex);;
	}
	else
	{
		bFind = mms_FindDataByID(m_pACSI_NODE, strDataId, nLdIndex, nDsIndex, nDaIndex,TRUE);
	}

	return bFind;

#if 0
	CString strLdId, strDsId, strDataId;
	BOOL bFind = GetDataPathMap_DsKey(strDsKey, strValue, strLdId, strDsId, strDataId);

	if (!bFind)
	{
		bFind = mms_FindDataByID(strDsKey, m_pACSI_NODE, strDataId, nLdIndex, nDsIndex, nDaIndex);
	}
	else
	{
		bFind = mms_FindDataByID(m_pACSI_NODE, strLdId, strDsId, strDataId, nLdIndex, nDsIndex, nDaIndex);
	}

	m_strCmdIdParaDsPath.Format(_T("%s$%s"), strLdId, strDsId);

	if (bFind)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DataID=%s[%s]  LD=%d  DS=%d  DA=%d"), strValue, strDataId
			, nLdIndex, nDsIndex, nDaIndex);
	}
	else
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("DataID=%s  not exits"), strValue);
	}

	strRetDataID = strValue;

	return bFind;
#endif
}

BOOL CPoMmsDevice::ReadOne()
{
	long nDeviceIndex = mms_GetDeviceNodeIndex(m_pACSI_NODE);
	long nLdIndex, nDsIndex, nDaIndex;

	CString strRetDataID;

	if (!GetDataIndex_DataID(nLdIndex, nDsIndex, nDaIndex, strRetDataID))
	{
		return FALSE;
	}

	m_oMmsDatasetMapTool.SetDataPath(strRetDataID);
	theMmsApi->InitReadOneFuncParas(nDeviceIndex, nLdIndex, nDsIndex, nDaIndex, TRUE);

	return TRUE;
}

BOOL CPoMmsDevice::SetDataRef(const CString &strDsPath)
{
	long nDeviceIndex = mms_GetDeviceNodeIndex(m_pACSI_NODE);
	long nLdIndex, nDsIndex, nDaIndex;
	CString strRetDataID;
	char *pszKey = mms_GetDatasetKey(strDsPath);

	if (GetDataIndex_DataID(pszKey,nLdIndex, nDsIndex, nDaIndex, strRetDataID))
	{
        strcpy(m_pACSI_NODE->RefDaPath, strRetDataID.GetString());
	}
	else
	{
		if (strRetDataID.GetLength() == 0)
		{
			m_pACSI_NODE->RefDaPath[0] = 0;
		}
	}


	return TRUE;
}

void CPoMmsDevice::GetVariableVal(const CString &strID, long &nVal, long nDefaultVal)
{
	CValue *pVariable = NULL;
	pVariable = (CValue*)m_listDataInterface.FindByID(strID);

	if (pVariable != NULL)
	{
		nVal = CString_To_long(pVariable->m_strValue);
	}
	else
	{
		nVal = nDefaultVal;
	}
}

void CPoMmsDevice::GetVariableVal(const CString &strID, __int64 &nVal, __int64 nDefaultVal)
{
	CValue *pVariable = NULL;
	pVariable = (CValue*)m_listDataInterface.FindByID(strID);

	if (pVariable != NULL)
	{
		if (pVariable->m_strValue.GetLength() > 2)
		{
			TCHAR ch1, ch2;
			ch1 = pVariable->m_strValue.GetAt(0);
			ch2 = pVariable->m_strValue.GetAt(1);

			if (ch1 == '0' && (ch2=='x' || ch2=='X'))
			{
                __uint64 u64Val;
				HexTo_i64(pVariable->m_strValue, u64Val);
				nVal = u64Val;
			}
			else
			{
				nVal = CString_To_i64(pVariable->m_strValue);
			}
		}
		else
		{
			nVal = CString_To_i64(pVariable->m_strValue);
		}
	}
	else
	{
		nVal = nDefaultVal;
	}
}

void CPoMmsDevice::GetVariableVal(const CString &strID, float &fVal, float fDefaultVal)
{
	CValue *pVariable = NULL;
	pVariable = (CValue*)m_listDataInterface.FindByID(strID);

	if (pVariable != NULL)
	{
		fVal = (float)CString_To_double(pVariable->m_strValue);
	}
	else
	{
		fVal = fDefaultVal;
	}
}

void CPoMmsDevice::GetVariableVal(const CString &strID, CString &strVal, const CString &strDefaultVal)
{
	CValue *pVariable = NULL;
	pVariable = (CValue*)m_listDataInterface.FindByID(strID);

	if (pVariable != NULL)
	{
		strVal = pVariable->m_strValue;
	}
	else
	{
		strVal = strDefaultVal;
	}
}

void CPoMmsDevice::GetVariableVal(const CString &strID, CTime &tmVal)
{
	CValue *pVariable = NULL;
	pVariable = (CValue*)m_listDataInterface.FindByID(strID);
	CString strVal;

	if (pVariable != NULL)
	{
		strVal = pVariable->m_strValue;
		int nIndex = strVal.ReverseFind('.');//zhouhj ��Ϊʱ���͹�����ʱ��Ϊ"2018-4-2 16:12:43 352"  �����������ĸ�ʽΪ"2018-4-2 16:12:43" 
		                                       //��Ϊ�˼���"2018-4-2 16:12:43.352"���ַ�ʽ��  �����˴�����
		if (nIndex == -1)
		{
			nIndex = strVal.ReverseFind(' ');
		}

		if (nIndex>0)
		{
			CString strTmp;
			strTmp = strVal.Mid(nIndex);

			if (strTmp.Find(':') == -1)
			{
				strVal = strVal.Left(nIndex);
			}
		}
	}

	CString_to_CTime(strVal, tmVal);
}

void CPoMmsDevice::GetVariableVal(const CString &strID, BOOL &bVal,BOOL bDefaultVal)
{
	CValue *pVariable = NULL;
	pVariable = (CValue*)m_listDataInterface.FindByID(strID);

	if (pVariable != NULL)
	{
		pVariable->m_strValue.MakeUpper();

		if (pVariable->m_strValue == _T("TRUE"))
		{
			bVal = 1;
		}
		else if (pVariable->m_strValue == _T("FALSE"))
		{
			bVal = 0;
		}
		else
		{
			bVal = CString_To_long(pVariable->m_strValue);
		}
	}
	else
	{
		bVal = bDefaultVal;
	}
}

long CPoMmsDevice::RunProcedureEx(const CString &strProcedureScript)
{
	// TODO: �ڴ���ӵ��ȴ���������

	return 0;
}

long CPoMmsDevice::AttachSystemWndMsg(ULONG hWnd, ULONG nMsgID)
{
	m_pACSI_NODE->hSysMsgWnd = hWnd;
	m_pACSI_NODE->nSysMsg = nMsgID;

	return 0;
}

long CPoMmsDevice::RegisterProcedureWndMsg(const CString &strProcedureID, ULONG hWnd, ULONG nMsgID)
{
	m_strProcedureID = strProcedureID;

	m_pACSI_NODE->hMsgWnd = hWnd;
	m_pACSI_NODE->nMsg = nMsgID;

	return 0;
}

long CPoMmsDevice::UnRegisterProcedureWndMsg(const CString &strProcedureID, ULONG hWnd, ULONG nMsgID)
{
	m_pACSI_NODE->hMsgWnd = NULL;
	m_pACSI_NODE->nMsg = 0;

	return 0;
}

long CPoMmsDevice::RegisterDataChangedWndMsg(const CString &strDataPath, ULONG hWnd, ULONG nWMsgID)
{
	CString strPath;
	strPath = strDataPath;

	if (strPath.Find(_T("$")) >= 0)
	{
		if (IsDvmDeviceMapExist())
		{
			m_oDvmDeviceMap.FindDataMap(strPath, strPath);
		}

		mms_RegisterDataChangedMsg(m_pACSI_NODE, strPath, hWnd, nWMsgID);
	}
	else
	{
		long nCmdID=0, nCmdState=0, wParam=0, lParam=0;
		
		//2019-1-5  �����¼������ӱ��������ж�
		if (GetCmdID(strPath, nCmdID, nCmdState, wParam, lParam))
		{//�����ͨѶ�����ע��ͨѶ����
			mms_RegisterCmdMsg(m_pACSI_NODE, strPath, hWnd, nWMsgID,nCmdID, nCmdState, wParam, lParam);
		}
		else
		{//��Ϊ���ģ����ݶ������ƴ���
			mms_RegisterDataChangedMsg(m_pACSI_NODE, strPath, hWnd, nWMsgID);
		}
	}

	return 0;
}

long CPoMmsDevice::UnRegisterDataChangedWndMsg(const CString &strDataPath)
{
	CString strPath;
	strPath = strDataPath;

	if (strPath.Find(_T("$")) >= 0)
	{
		if (IsDvmDeviceMapExist())
		{
			m_oDvmDeviceMap.FindDataMap(strPath, strPath);
		}
	}

	mms_UnRegisterDataChangedMsg(m_pACSI_NODE, strPath);

	return 0;
}

long CPoMmsDevice::UnLoad(void)
{
	m_pACSI_NODE->nReleaseWhenUnlink = 1;
	m_pACSI_NODE->pRefDevice = NULL;
	theMmsApi->InitUnLinkDeviceFuncPara(m_nDeviceIndex, TRUE, TRUE);
	theMmsApi->CallFirstFunc(m_nDeviceIndex);
	theMmsApi->OnReleaseDevice();
	//theMmsApi->ReleaseObjData(m_pACSI_NODE);

	//2023-2-2  lijunqing
	delete this;

	return 0;
}

CString CPoMmsDevice::GetXmlData(void)
{
	CString strResult;

	mms_GetXml(m_pACSI_NODE, strResult);

	return strResult;
}

long CPoMmsDevice::SetXmlData(const CString &bstrXmlData)
{
	mms_SetXml(m_pACSI_NODE, bstrXmlData);

	return 0;
}

CString CPoMmsDevice::GetXmlDataEx(const CString &strDatasetPath)
{
	CString strDsPath;
	strDsPath = GetDsPathMap(strDatasetPath);

	LD_DATASET_INFO *pDataset = mms_FindDataset(m_pACSI_NODE, strDsPath);
	CString strResult;

	if (pDataset != NULL)
	{
		mms_GetXml(pDataset, strResult);
	}

	return strResult;
}

long CPoMmsDevice::SetXmlDataEx(const CString &strDatasetPath, const CString &strXmlData)
{
	CString strDsPath;
	strDsPath = GetDsPathMap(strDatasetPath);

	CString strResult;

	LD_DATASET_INFO *pDataset = mms_FindDataset(m_pACSI_NODE, strDatasetPath);

	if (pDataset != NULL)
	{
		mms_SetXml(pDataset, strXmlData);
	}

	return 0;
}

CPoMmsDataInterface* CPoMmsDevice::GetDataInterface(void)
{
	m_bHasCreateDataInterface = TRUE;
	CPoMmsDataInterface *pPoDataInterface = CPoMmsDataInterface::_New_CPoMmsDataInterface(&m_listDataInterface);
	return pPoDataInterface;
}


long CPoMmsDevice::ConnectDevice(void)
{
	return 0;
}

CString CPoMmsDevice::GetAttrByID(const CString &strAttrID)
{
	CString strResult;
	CString strText;
	strText = strAttrID;
	strText.MakeUpper();

	InitDataAttr(strText, strResult);

	return strResult;
}

long CPoMmsDevice::SetAttrByID(const CString &strAttrID, const CString &strValue)
{
	CString strText;
	strText = strAttrID;

	if (strText == ATTRID_RECORD_PATH)
	{
		m_strRecordPath = strValue;
//		mms_str_init(&m_pACSI_NODE->RcdFilePath);
		log_WriteRcdPath(strValue);
        mms_str_set(&m_pACSI_NODE->RcdFilePath ,strValue.GetString()); //m_pACSI_NODE->RcdFilePath//�Զ���������£��Ὣm_pACSI_NODE->RcdFilePath¼��·����Ϊ���ⱨ��·��
	}
	else if (strText.GetLength() > 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,g_sLangTxt_OnlyReadProp.GetString() , strText.GetString());//_T("���ԡ�%s��Ϊֻ������")
	}

	return 0;
}

long CPoMmsDevice::SaveDvmFile(const CString &strDvmFile)
{
	CString strFile;
	strFile = strDvmFile;
	mms_XmlWrite(strFile, m_pACSI_NODE);

	return 0;
}


long CPoMmsDevice::SetCommConfig(const CString &strCommConfig)
{
	// TODO: �ڴ���ӵ��ȴ���������

	return 0;
}

CString CPoMmsDevice::GetCommConfig(void)
{
	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������

	return strResult;
}

void CPoMmsDevice::Run_CMDID_writeena(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex, const CString &strTitle, const char* pszKey)
{
	long nLd = 0;
	long nDs = 0;
	long nDaIndex = 0;
	LD_NODE *pLdevice = NULL;
	LD_DATASET_INFO *pDs = NULL;
	long nCount = 0;

	for (nLd=0; nLd<m_pACSI_NODE->numLD; nLd++)
	{
		pLdevice = &m_pACSI_NODE->LD[nLd];

		for (nDs=0; nDs<pLdevice->numDaSet; nDs++)
		{
			pDs = &pLdevice->DataInfo[nDs];

// 			if (strstr(pDs->DataSetID, pszKey) == NULL)
// 			{
// 				continue;
// 			}

			for (nDaIndex=0; nDaIndex<pDs->numData; nDaIndex++)
			{
				if (pDs->DataSet[nDaIndex].bModify == 1)
				{
					theMmsApi->InitCtrlWriteFuncParasEx(nDeviceIndex, nLd, nDs, FALSE);
					nCount++;
					break;
				}
			}
		}
	}

	if (nCount == 0)
	{
		//theMmsApi->InitCtrlWriteFuncParasEx(nDeviceIndex, nLdIndex, nDatasetIndex);
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, g_sLangTxt_NoNeedCorect.GetString()
                                   , strTitle.GetString(), m_oMmsDatasetMapTool.m_strStandDsPath.GetString());//_T("û����Ҫ�޸ĵ�%s��%s��")
	}
}

BOOL CPoMmsDevice::Run_CMDID_writesetting(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex)
{
	long nZone = 0;
	GetVariableVal(ParaID_setzone, nZone, nZone);
	BOOL bNeedWrite = TRUE;

	if (IsDvmDeviceMapExist())
	{
		bNeedWrite = IniSetWriteFuncParasEx(nDeviceIndex, nLdIndex, nDatasetIndex, nZone);
	}
	else
	{
		ACSI_NODE *pDevice = m_pACSI_NODE;
		bNeedWrite = mms_HasDatasetDataChanged(pDevice/*nDeviceIndex*/, nLdIndex,nDatasetIndex);

		if (bNeedWrite)
		{
			theMmsApi->InitWriteCurrSetsFuncParas(nDeviceIndex,  nLdIndex, nDatasetIndex, nZone, TRUE);
		}
	}

	if (!bNeedWrite)
	{
		//theMmsApi->OutputPrintMsg(g_sLangTxt_HadNoDataNeedEdit);//_T("û����Ҫ�޸ĵ�����"));
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_HadNoDataNeedEdit);
		mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommFinish, engineCommFinish);
	}

	return bNeedWrite;
}

void CPoMmsDevice::Run_CMDID_readena(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex)
{
	theMmsApi->set_OnlyReadValue(TRUE);

	if (!IsDvmDeviceMapExist())
	{
		theMmsApi->InitReadFuncPara(nDeviceIndex,  nLdIndex, nDatasetIndex);
		return;
	}

	POS pos = m_oMmsDatasetMapTool.GetHeadPosition();
	CMmsDvmDs_LdNode_Map *p = NULL;
	long nCount = 0;

	theMmsApi->m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	while (pos != NULL)
	{
		p = (CMmsDvmDs_LdNode_Map *)m_oMmsDatasetMapTool.GetNext(pos);

		theMmsApi->InitReadLDeviceValuesFuncParas(p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ReadEna(%s$%s):DV=%d  LD=%d  DS=%d"), 
            p->m_pLD_NODE->LDName, p->m_pDataset->DataSetID,
			p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
		nCount++;
	}
}

void CPoMmsDevice::Run_CMDID_readsetting(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex)
{
	theMmsApi->set_OnlyReadValue(TRUE);

	long nZone = 0;
	GetVariableVal(ParaID_setzone, nZone, nZone);

	if (IsDvmDeviceMapExist())
	{
		POS pos = m_oMmsDatasetMapTool.GetHeadPosition();
		CMmsDvmDs_LdNode_Map *p = NULL;
		long nCount = 0;

		while (pos != NULL)
		{
			p = (CMmsDvmDs_LdNode_Map *)m_oMmsDatasetMapTool.GetNext(pos);

			theMmsApi->InitReadFuncPara_Set(p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO, nZone, m_pACSI_NODE->nRunSGIndex, (nCount == 0));
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ReadSettings(%s$%s):DV=%d  LD=%d  DS=%d"), 
                p->m_pLD_NODE->LDName, p->m_pDataset->DataSetID,
				p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
			nCount++;
		}
	}
	else
	{
		theMmsApi->InitReadFuncPara_Set(nDeviceIndex, nLdIndex, nDatasetIndex, nZone, m_pACSI_NODE->nRunSGIndex, TRUE);
	}
}

void CPoMmsDevice::Run_CMDID_readparameter(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex)
{
	theMmsApi->set_OnlyReadValue(TRUE);

	if (!IsDvmDeviceMapExist())
	{
		theMmsApi->InitReadLDeviceValuesFuncParas(nDeviceIndex,  nLdIndex, nDatasetIndex);
		return;
	}

	POS pos = m_oMmsDatasetMapTool.GetHeadPosition();
	CMmsDvmDs_LdNode_Map *p = NULL;
	long nCount = 0;

	theMmsApi->m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	while (pos != NULL)
	{
		p = (CMmsDvmDs_LdNode_Map *)m_oMmsDatasetMapTool.GetNext(pos);

		theMmsApi->InitReadLDeviceValuesFuncParas(p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ReadParameter(%s$%s):DV=%d  LD=%d  DS=%d"), 
            p->m_pLD_NODE->LDName, p->m_pDataset->DataSetID,
			p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
		nCount++;
	}
}

long CPoMmsDevice::IniSetWriteFuncParasEx(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex, long nZone)
{
	long nLd = 0;
	long nDs = 0;
	long nDaIndex = 0;
	LD_NODE *pLdevice = NULL;
	LD_DATASET_INFO *pDs = NULL;
	long nCount = 0;

	for (nLd=0; nLd<m_pACSI_NODE->numLD; nLd++)
	{
		pLdevice = &m_pACSI_NODE->LD[nLd];

		for (nDs=0; nDs<pLdevice->numDaSet; nDs++)
		{
			pDs = &pLdevice->DataInfo[nDs];

			if (strstr(pDs->DataSetID, key_dsSetting) == NULL)
			{
				continue;
			}

			for (nDaIndex=0; nDaIndex<pDs->numData; nDaIndex++)
			{
				if (pDs->DataSet[nDaIndex].bModify == 1)
				{
					theMmsApi->InitWriteCurrSetsFuncParas(nDeviceIndex, nLd, nDs, nZone, (nCount == 0));
					nCount++;
					break;
				}
			}
		}
	}

	return nCount;
}

void CPoMmsDevice::InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart, const CString &strDsPath)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("registerreport:���ݼ���%s"), strDsPathTemp);
	POS pos = m_oMmsDatasetMapTool.GetHeadPosition();
	CMmsDvmDs_LdNode_Map *p = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		p = (CMmsDvmDs_LdNode_Map *)m_oMmsDatasetMapTool.GetNext(pos);

		theMmsApi->InitCallReportFuncParas(p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO, bStart, FALSE);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CallReport(%s$%s):DV=%d  LD=%d  DS=%d"), 
            p->m_pLD_NODE->LDName, p->m_pDataset->DataSetID,
			p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
		nCount++;
	}

// 	char *pszKey = mms_GetDatasetKey(strDsPath);
// 	long nDs = 0;
// 	long nDaIndex = 0;
// 	LD_NODE *pLdevice = NULL;
// 	LD_DATASET_INFO *pDs = NULL;
// 	long nCount = 0;
// 
// 	//for (nLd=0; nLd<m_pACSI_NODE->numLD; nLd++)
// 	if (pszKey != NULL)
// 	{
// 		pLdevice = &m_pACSI_NODE->LD[nLDIndex];
// 
// 		for (nDs=0; nDs<pLdevice->numDaSet; nDs++)
// 		{
// 			pDs = &pLdevice->DataInfo[nDs];
// 
// 			if (strstr(pDs->DataSetID, pszKey) == NULL)
// 			{
// 				continue;
// 			}
// 
// 			theMmsApi->InitCallReportFuncParas(nDeviceIndex, nLDIndex, nDs, bStart, FALSE);
// 			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CallReport:DV=%d  LD=%d  DS=%d"), nDeviceIndex, nLDIndex, nDs);
// 			nCount++;
// 		}
// 	}

	if (nCount == 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                                   , g_sLangTxt_RegRepDataSetMiss.GetString()
                                   , m_oMmsDatasetMapTool.m_strStandDsPath.GetString());//_T("registerreport:���ݼ���%s ������")
		mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommError, engineCommError);
	}
}


void CPoMmsDevice::InitStopReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, const CString &strDsPath)
{
	POS pos = m_oMmsDatasetMapTool.GetHeadPosition();
	CMmsDvmDs_LdNode_Map *p = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		p = (CMmsDvmDs_LdNode_Map *)m_oMmsDatasetMapTool.GetNext(pos);

		theMmsApi->InitStopReportFuncParas(p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("stopreport(%s$%s):DV=%d  LD=%d  DS=%d"), 
            p->m_pLD_NODE->LDName, p->m_pDataset->DataSetID,
			p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
		nCount++;
	}

// 
// 	char *pszKey = mms_GetDatasetKey(strDsPath);
// 	long nDs = 0;
// 	long nDaIndex = 0;
// 	LD_NODE *pLdevice = NULL;
// 	LD_DATASET_INFO *pDs = NULL;
// 	long nCount = 0;
// 
// 	//for (nLd=0; nLd<m_pACSI_NODE->numLD; nLd++)
// 	{
// 		pLdevice = &m_pACSI_NODE->LD[nLDIndex];
// 
// 		for (nDs=0; nDs<pLdevice->numDaSet; nDs++)
// 		{
// 			pDs = &pLdevice->DataInfo[nDs];
// 
// 			if (strstr(pDs->DataSetID, pszKey) == NULL)
// 			{
// 				continue;
// 			}
// 
// 			theMmsApi->InitStopReportFuncParas(nDeviceIndex, nLDIndex, nDs);
// 			nCount++;
// 		}
// 	}

	if (nCount == 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                                   , g_sLangTxt_StopRepDataSetMiss.GetString()
                                   , m_oMmsDatasetMapTool.m_strStandDsPath.GetString());//_T("stopreport:���ݼ���%s ������")
		mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommError, engineCommError);
	}
}

void CPoMmsDevice::InitReadJournalFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, const CString &strJournalName)
{
	long bStart/* = 1*/, nStartType = 1;
	__int64 nStartEntry;
	long bEnd/* = 1*/, nEndType/* = 1*/, nEntryNum/* = 5*/;
	CTime tmStart, tmEnd;
	m_pJournalDatas = &m_pACSI_NODE->LD[nLDIndex].JournalDatas;//zhouhj ������־����
	GetVariableVal(ParaID_tmStart, tmStart);
	GetVariableVal(ParaID_tmEnd, tmEnd);

// 	tmStart -= 600;
	MMS_BTOD btod1,btod2;
	tagEVENTTIME tagTime,tagTime2;
	convert_timet_to_btod(tmStart,btod1);
	convert_btod_to_timet(btod1 ,tagTime);
	convert_timet_to_btod(tmEnd,btod2);
	convert_btod_to_timet(btod2 ,tagTime2);
	CString strStartTime,strStartTime2;
	strStartTime.Format("%d-%d-%d %d:%d:%d.%d",tagTime.year,tagTime.month,tagTime.day,tagTime.hour,tagTime.minute,tagTime.second,tagTime.ms);
	strStartTime2.Format("%d-%d-%d %d:%d:%d.%d",tagTime2.year,tagTime2.month,tagTime2.day,tagTime2.hour,tagTime2.minute,tagTime2.second,tagTime2.ms);
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE,"��ʼ��ѯʱ��:%s",strStartTime.GetString());
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE,"������ѯʱ��:%s",strStartTime2.GetString());

	GetVariableVal(ParaID_Log_bStart, bStart, 0);
	GetVariableVal(ParaID_Log_EntryIDStart, nStartEntry, 0);
	GetVariableVal(ParaID_Log_bEnd, bEnd, 0);
	GetVariableVal(ParaID_Log_EntryNum, nEntryNum, 0);

	if (bStart)// ��ע: ʹ�ÿ�ʼ��������Ŀ��Ϊ-1ʱ��ʹ��ʱ���������Ŀ�Ų�Ϊ-1ʱ��ʹ����Ŀ�ż�����
	{
		if (nStartEntry == -1)
		{
			nStartType = 0; //start time
		}
		else
		{
			nStartType = 1;
		}
	}

	if (bEnd)// ��ע: ʹ�ý�����������Ŀ��Ϊ-1ʱ��ʹ�ý���ʱ���������Ŀ����Ϊ-1ʱ��ʹ����Ŀ��������
	{
		if (nEntryNum == -1)
		{
			nEndType = 0; //start time
		}
		else
		{
			nEndType = 1;
		}
	}

	CString strTmp;
    strTmp.Format("nDeviceIndex=%d;nLDIndex=%d;strJournalName = %s;",nDeviceIndex,nLDIndex,strJournalName.GetString());
    CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "%s",strTmp.GetString());

	strTmp.Format("bStart=%d;nStartType=%d;bEnd=%d;nEndType=%d;nEntryNum=%d;",bStart,nStartType,bEnd,nEndType,nEntryNum);
    CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "%s",strTmp.GetString());

	theMmsApi->InitReadJournal(nDeviceIndex, nLDIndex, strJournalName
		, bStart, nStartType, tmStart, nStartEntry
		, bEnd, nEndType, tmEnd, nEntryNum);
}

CString CPoMmsDevice::GetXmlDataLD(void)
{
	CString strResult;

	mms_GetXml(m_pACSI_NODE, strResult, TRUE);

	return strResult;
}

CString CPoMmsDevice::GetLogsXml(void)
{
	CString strResult;

	// TODO: �ڴ���ӵ��ȴ���������
	CString strFile;
	if (m_pJournalDatas != NULL)
	{
		CDvmLogs oDvmLogs;
		mms_GetDvmLogs(m_pJournalDatas, &oDvmLogs);
		strFile = _P_GetBinPath();
		strFile += _T("ReadLogXmlData.dat");
		CBinarySerialBuffer oBuffer;
		dvm_InitDvmVersion(oBuffer);
		oBuffer.SetCharSet(CHAR_SET_ASCII);
		oBuffer.SetVersionFind(g_dwDataMngrCurrVersion);

		oBuffer.SetCalSizeMode();
		oBuffer.WriteVersion();
		oDvmLogs.Serialize(oBuffer);
		oBuffer.AllocBuffer(0);

		oBuffer.SetWriteMode();
		oBuffer.WriteVersion();
		oDvmLogs.Serialize(oBuffer);

		oBuffer.SaveToFile(strFile);
		oDvmLogs.DeleteAll();
	}

    CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "strFile = %s", strFile.GetString());

	return strFile;

//	return strResult;
}

void CPoMmsDevice::log_WriteRcdPath(const CString &strPath)
{
#ifndef _PSX_QT_LINUX_
	CFile oFile;
	CString strFile;
	strFile = _P_GetCommonPath();
	strFile += _T("CurTestFolder.dat");

	if (IsFileExist(strFile))
	{
		X_DeleteFile(strFile);
	}

	if (oFile.Open(strFile, CFile::modeWrite | CFile::modeCreate))
	{
		oFile.Write(strPath, strPath.GetLength());
		oFile.Close();
	}
#endif
}


/*
<iot-cmd name="" id=" CreateDevice" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="װ��SN"/>
		<data name="" id="ppxml-file" data-type="" value="SZNR-TTU.ppxml"/>
		<data name="" id="dvm-file" data-type="" value="SZNR-TTU.xml"/>
		<data name="" id="cmm-cfg-file" data-type="" value="SZNR-TTU202012131700"/>
		<group name="" id="comm-config" data-type="" value="">
			<data name="" id="tcp-client" data-type="" value="">
				<value name="" id="local-ip" data-type="" value="192.168.10.10"/>
				<value name="" id="local-port" data-type="" value="20183"/>
				<value name="" id="remote-ip" data-type="" value="192.168.10.101"/>
				<value name="" id="remote-port" data-type="" value="2404"/>
			</data>
		</group>
	</paras>
</iot-cmd>
*/
BOOL CPoMmsDevice::InitCmmConfig(CDataGroup *pGroup, BOOL bConnect)
{
	m_nDeviceIndex = mms_GetDeviceNodeIndex(m_pACSI_NODE);

	CString strKey;
	strKey = CDeviceModelXmlKeys::g_pXmlRWKeys->m_strMmsKey;
	CDvmData *pMmsCfg = (CDvmData *)pGroup->FindByID(strKey);
	ACSI_NODE *pDevice = &pACSINode[m_nDeviceIndex];

	if (pMmsCfg != NULL)
	{
		CString strLocalIP, strRemoteIP ,nRemotePort;
		pMmsCfg->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey,  strLocalIP);
		pMmsCfg->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey,  strRemoteIP);
		pMmsCfg->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey,  nRemotePort);

        device_node_table[m_nDeviceIndex].IP1 = inet_addr(strRemoteIP.GetString());
		sock_info_table[m_nDeviceIndex].ip_addr = device_node_table[m_nDeviceIndex].IP1;
        mms_str_set(&pDevice->IpAddr, strRemoteIP.GetString());
	}
	
/*
	if (m_bIsConfig)
	{////2020-12-22  lijunqing  �ⲿ�������ýӿڣ�����IP����������ã�����������������
		theApp.InitLinkDeviceFuncPara(m_nDeviceIndex, TRUE);
	}
	else
	{
		if (pDevice->numLD > 0)
		{
			theApp.InitLinkDeviceFuncPara(m_nDeviceIndex, TRUE);
		}
		else
		{
			theApp.InitLinkDeviceFuncPara(m_nDeviceIndex, FALSE);
		}
	}
*/

	CommConfig(_T(""));
	//theMmsApi->InitLinkDeviceFuncPara(m_nDeviceIndex, TRUE);
	//theMmsApi->CallFirstFunc(m_nDeviceIndex);

	return TRUE;
}

void CPoMmsDevice::mms_PostDeviceSysMessage(ACSI_NODE *pDevice, WPARAM wParam, LPARAM lParam)
{
	if (pDevice->bTestLinkState)
	{
		wParam = engineConnectDeviceSuccessful;//engineConnectDeviceSuccessful;    zhouhj  20200703 ԭ��Ϊ1  ��Ϊ�궨��
		lParam = engineConnectDeviceSuccessful;//engineConnectDeviceSuccessful;zhouhj  20200703 ԭ��Ϊ1  ��Ϊ�궨��
	}

	wParam = m_nDeviceIndex;//mms_GetDeviceNodeIndex(pDevice);
	m_pPxiDeviceCommCmdMessage->OnSysMessage(wParam, lParam);
}

void CPoMmsDevice::mms_PostDeviceEventMessage(ACSI_NODE *pDevice, WPARAM wParam, LPARAM lParam)
{
	m_pPxiDeviceCommCmdMessage->OnEventMessage(m_nDeviceIndex, lParam);
}

void CPoMmsDevice::mms_PostDeviceCommCmdMessage(ACSI_NODE *pDevice, WPARAM wParam, LPARAM lParam)
{
	m_pPxiDeviceCommCmdMessage->OnCommCmdMessage(wParam, lParam);
}

void CPoMmsDevice::mms_PostMmsReportMessage(ACSI_NODE *pDevice, WPARAM wParam, LPARAM lParam)
{
    m_pPxiDeviceCommCmdMessage->OnReportMessage(wParam, lParam);
}

