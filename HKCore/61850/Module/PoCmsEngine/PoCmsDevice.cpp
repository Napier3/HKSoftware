// PoCmsDevice.cpp : 实现文件
//

#include "stdafx.h"
#include "PoCmsDevice.h"
#include "DltEngineAppBase.h"

#include "PoCmsLogicDevice.h"
#include "PoCmsDataSet.h"
#include "../../../Module/API/FileApi.h"
#include "../../../Module/API/GlobalConfigApi.h"
#include "../dlt860/DLT860Engine.h"
#include "../../../Protocol/Module/Engine/DeviceModel/DeviceModelXmlKeys.h"

CPoCmsDevice::CPoCmsDevice()
{
	m_oDsAttr.AddNewData(ATTRID_ENA_WRITE_CTRL_TYPE_,   ATTRID_ENA_WRITE_CTRL_TYPE_, _T("INT"), _T("0"));//
	m_oDsAttr.AddNewData(ATTRID_READ_AIN_USE_REPORT_,   ATTRID_READ_AIN_USE_REPORT_, _T("INT"), _T("0"));//
}

CPoCmsDevice::~CPoCmsDevice()
{
}


long CPoCmsDevice::CommConfig(const CString &strCmmConfig)
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
        oDvmDataset.SetXml(strConfig,CDataMngrXmlRWKeys::g_pXmlKeys);
		CDvmData *pDvmData = (CDvmData*)oDvmDataset.FindByID(_T("ip-addr"));
		CRemoteDev *pRemote = theCmsApp->GetRemoteDev(m_nDeviceIndex);

		if ((pDvmData != NULL)&&(pRemote))
		{
			CString strOldIP,strKey,strPSW;
			strOldIP = pRemote->m_strIP;

			if ((strOldIP != pDvmData->m_strValue)&&(IsValidIP(pDvmData->m_strValue)))
			{
                mms_str_set(&m_pACSI_NODE->IpAddr,pDvmData->m_strValue.GetString());
				pRemote->m_strIP = pDvmData->m_strValue;
				theCmsApp->UpdateDeviceIP_Desc(m_nDeviceIndex);
			}
		}
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

	if (!g_o61850ClientConfig.m_nUseDvmMapFile)
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

	if (m_strLastOpenDeviceFile != m_strDeviceFile && m_strDeviceFile.GetLength() > 0)
	{
		if (bOpenMap)
		{
			m_oDvmDeviceMap.OpenDvmMapFile(m_strDeviceFile);
		}

		if (mms_XmlRead(m_strDeviceFile, m_pACSI_NODE))
		{
			InitGlobalDatasetsDesc_ACSI_NODE(m_pACSI_NODE);
			m_pACSI_NODE->nHasDeviceModel = 1;
			m_strLastOpenDeviceFile = m_strDeviceFile;

			m_oMmsDatasetMapTool.Attach(m_pACSI_NODE, &m_oDvmDeviceMap, m_nDeviceIndex);
			m_oMmsDatasetMapTool.mms_Init_ACSI_NODE_Map(m_pACSI_NODE, &m_oDvmDeviceMap);
		}
		else
		{
			m_pACSI_NODE->nHasDeviceModel = 0;
		}
	}

	if (g_bMmsEngineDebugMode)
	{
		theCmsApp->m_oFuncParamEx[m_nDeviceIndex].set_DevIndex(m_nDeviceIndex);
		theCmsApp->m_oFuncParamEx[m_nDeviceIndex].SetsConnectDevice(TRUE);
	}
	else
	{
//		if (g_bMmsEngineSingleDeviceMode)
		{
			if (m_pACSI_NODE->bConnect)
			{
				mms_PostDeviceSysMessage(m_pACSI_NODE, engineConnectDeviceSuccessful, engineConnectDeviceSuccessful);
				return 0;
			}
		}

		theCmsApp->InitLinkDeviceFuncPara_AutoTest(m_nDeviceIndex, FALSE);
		theCmsApp->CallFirstFunc(m_nDeviceIndex);
	}

	return 0;
}

CPoMmsLogicDevice* CPoCmsDevice::GetItem(LONG nIndex)
{
	if (nIndex >= m_pACSI_NODE->numLD)
	{
		return NULL;
	}

	//返回设备的节点
	CPoCmsLogicDevice *pLogicDevice = CPoCmsLogicDevice::_New_CDeviceNode_LD(m_pACSI_NODE, &(m_pACSI_NODE->LD[nIndex]));

	if (pLogicDevice == NULL)
	{
		return NULL;
	}

	return pLogicDevice;
}

CPoMmsDataSet* CPoCmsDevice::FindDataSet(const CString &strDataSetName)
{
	CString strDsPath = strDataSetName;
	strDsPath.MakeLower();

	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Device::FindDataSet【%s】"), strDsPath);
	if (strDsPath == _T("none"))
	{
		return NULL;
	}

	if (strDsPath.Find(dsID_MmsDvmAttr) >= 0)
	{
		CPoCmsDataSet *pPoDataset = CPoCmsDataSet::_NewPoCmsDataSet(m_pACSI_NODE, &m_oDsAttr);
		return pPoDataset;
	}

	if (strDsPath == dsID_Report || strDsPath.GetLength() == 0)
	{
		CPoCmsDataSet *pPoDataset = CPoCmsDataSet::_NewPoCmsDataSet(m_pACSI_NODE, m_pACSI_NODE->Reports);
		pPoDataset->m_strReadSoeDsPath = m_strReadSoeDsPath;
		pPoDataset->m_pDvmDeviceMap = GetDvmDeviceMap();
		return pPoDataset;
	}
	else if (strDsPath == dsID_Record || strDsPath == dsID_File)
	{
		CPoCmsDataSet *pPoDataset = CPoCmsDataSet::_NewPoFileDir(m_pACSI_NODE, &m_pACSI_NODE->FileDir);
		return pPoDataset;
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
	{//建立映射关系
		LD_NODE *pLdevice = NULL;//zhouhj 20180607 金智采用模型映射方式时，上送的dsRelayAin数据集的数据自动测试未使用，测试结果为空，误差-100%
		LD_DATASET_INFO *pDataset = mms_FindDatasetEx(m_pACSI_NODE, strDsPath, &pLdevice);
		CPoCmsDataSet *pPoDataset = CPoCmsDataSet::_NewPoCmsDataSet(m_oMmsDatasetMapTool.m_pACSI_NODE, pLdevice, pDataset);
		pPoDataset->m_strDatasetPath = strDsPath;
		pPoDataset->m_pMmsDatasetMapTool = &m_oMmsDatasetMapTool;

		m_oMmsDatasetMapTool.SetStandPath(strDsPath);
// 		CPoCmsDataSet *pPoDataset = CPoCmsDataSet::_NewPoCmsDataSet(&m_oMmsDatasetMapTool);
		return pPoDataset;
	}
	else
	{//直接获取数据集
		LD_NODE *pLdevice = NULL;
		LD_DATASET_INFO *pDataset = mms_FindDatasetEx(m_pACSI_NODE, strDsPath, &pLdevice);

		if (pDataset == NULL)
		{
			return NULL;
		}

		CPoCmsDataSet *pPoDataset = CPoCmsDataSet::_NewPoCmsDataSet(m_pACSI_NODE, pLdevice, pDataset);
		pPoDataset->m_strDatasetPath = strDsPath;
		return pPoDataset;
	}
}

long CPoCmsDevice::RunProcedure(const CString &strProcedureID, const CString &strDatasetPath)
{
	m_strCmdIdParaDsPath.Empty();
	m_strReadSoeDsPath.Empty();
	m_pACSI_NODE->nWriteErrorCount = 0;
	CString strID;
	strID = strProcedureID;
	strID.MakeLower();
	long nLdIndex = -1;//zhouhj 20180409 因为之后需要验证此设备是否存在，故此处将其设为-1
	long nDatasetIndex = 0;
	long nDeviceIndex = mms_GetDeviceNodeIndex(m_pACSI_NODE);

	
	CString strDsPathTemp = strDatasetPath;

	if (IsDvmDeviceMapExist())
	{
		m_oMmsDatasetMapTool.SetDataPath(_T(""));
		m_oMmsDatasetMapTool.SetStandPath(strDsPathTemp);
		m_oMmsDatasetMapTool.SetProcedureID(strID);
	}

	CString strMsg;
	BOOL bDsExist = mms_FindDatasetIndex(m_pACSI_NODE, strDsPathTemp, nLdIndex, nDatasetIndex);//zhouhj 20210828  对于单个设备包含多个定值区的情况,需要传递定值区,但也为兼容之前不传递定值区的模板,此处统一先获取
    strMsg.Format(_T("执行外部通讯命令【%s】：ACSIDevice=%d  LdIndex=%d  DatasetIndex=%d")
                  , strID.GetString(),nDeviceIndex, nLdIndex, nDatasetIndex);//_T("执行外部通讯命令【%s】：ACSIDevice=%d  LdIndex=%d  DatasetIndex=%d")

	if (strID == CMDID_ReadMmsAttr || strID == CMDID_WriteMmsAttr)
	{
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

//		BOOL bDsExist = TRUE;

		if (IsDvmDeviceMapExist())//zhouhj 对于使用数据集路径的此处还需要重新给nLdIndex  nDatasetIndex赋值
		{
			bDsExist = (m_oMmsDatasetMapTool.GetCount() > 0);

			if (bDsExist)
			{
				CMmsDvmDs_LdNode_Map *pMap = (CMmsDvmDs_LdNode_Map*)m_oMmsDatasetMapTool.GetHead();
				nLdIndex = pMap->m_nLD_NODE;
				nDatasetIndex = pMap->m_nDATASET_INFO;
			}
		}
// 		else
// 		{
// 			bDsExist = mms_FindDatasetIndex(m_pACSI_NODE, strDsPathTemp, nLdIndex, nDatasetIndex);
// 		}

		if (!bDsExist)
		{//逻辑设备不存在
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("数据集路径【%s】不正确")
                                       , strDsPathTemp.GetString());//_T("数据集路径【%s】不正确")
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommCmdError, engineCommCmdError);
			return 0;
		}
	}

//	theCmsApp->m_strCurrCmdID = strProcedureID;
	theCmsApp->m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();


	if (strID == CMDID_readain)
	{//读遥测
		if (g_o61850ClientConfig.m_nReadAinUseReport == 1)
		{
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommFinish, engineCommFinish);
			return 0;
		}
		else
		{
			//theCmsApp->InitReadFuncPara(nDeviceIndex,  nLdIndex, dsID_Ain);
			theCmsApp->InitReadFuncPara(nDeviceIndex,  nLdIndex, nDatasetIndex);
		}
	}
	else if (strID == CMDID_readsetting)
	{//读定值
		Run_CMDID_readsetting(nDeviceIndex, nLdIndex, nDatasetIndex);
	}
	else if (strID == CMDID_readdataset)
	{//读数据集
		long nUseRead = 0;
		GetVariableVal(ParaID_UseRead, nUseRead, 1);

		if (nUseRead == 0)
		{//不读数据，直接返回
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommFinish, engineCommFinish);
			return 0;
		}
		else
		{
			theCmsApp->InitReadFuncPara(nDeviceIndex, nLdIndex, nDatasetIndex);
		}
	}
	else if (strID == CMDID_read_dir)
	{//枚举文件目录
		CTime tmStart = 0, tmEnd = 0;
		__int64 int64Start,int64End;
		CString strPath,strTmp;
		GetVariableVal(ParaID_tmStart, tmStart);
		GetVariableVal(ParaID_tmEnd, tmEnd);
		int64Start = tmStart.GetTime();
		int64End = tmEnd.GetTime();
		long nMode = 0,nNewNum = -1;
		GetVariableVal(ParaID_Mode,nMode ,0);// 0为正常读取模式，读取该路径下全部文件；1为读取该路径下全部指定时间段录波文件；2为读取指定数目的最新录波文件；
		GetVariableVal(ParaID_NewFNum, nNewNum,-1);
		GetVariableVal(ParaID_path, strPath, _T(""));

		if (nMode == 1)//增加按时间查找的命令
		{
			strTmp.Format(_T("%lld^%lld/COMTRADE/"),int64Start,int64End);
			strPath = strTmp;
		}
		else if ((nMode == 2)&&(nNewNum>0))//增加按最新数目查找的命令
		{
			strTmp.Format(_T("/COMTRADE/NEWEST_%d/"),nNewNum);
			strPath = strTmp;
		}
		
		theCmsApp->InitGetFileDir(nDeviceIndex, strPath);//参数2指装置内的目录，为空表示读根目录下的所有文件及文件夹
	}
	else if (strID == CMDID_read_file)
	{//读文件
		CString strFileName,strFolderPath;
		int nIndex = -1;
//		GetVariableVal(ParaID_path, theCmsApp->m_strRecordFilePath, theCmsApp->GetDefaultRecordPath(nDeviceIndex));
		GetVariableVal(ParaID_File, strFileName, _T(""));
		strFileName.Replace("\"","");
		strFolderPath = strFileName;//zhow:m_strRecordPath只是记录了被测报告的路径，此处还要加上装置内的目录文件夹名；
		strFolderPath.Replace("/","\\");
		nIndex = strFolderPath.ReverseFind('\\');

		if (nIndex != -1)
		{
			strFolderPath = strFolderPath.Left(nIndex+1);
		}
		else
			strFolderPath = "";

		strFolderPath = m_strRecordPath + strFolderPath;
		theCmsApp->InitGetFile(nDeviceIndex, strFolderPath,strFileName);
	}
	else if (strID == CMDID_writesetting)
	{//修改定值
		if (! Run_CMDID_writesetting(nDeviceIndex, nLdIndex, nDatasetIndex))
		{
			return 0;
		}
	}
	else if (strID == CMDID_readena)
	{//读软压板
		Run_CMDID_readena(nDeviceIndex,  nLdIndex, nDatasetIndex);
	}
	else if (strID == CMDID_writeena)
	{//修改软压板
		Run_CMDID_writeena(nDeviceIndex,  nLdIndex, nDatasetIndex,_T("压板"), key_dsRelayEna);// _T("压板")
	}
	else if (strID == CMDID_writedout)
	{//修改软压板
		if (strDsPathTemp.Find(key_dsGOOSE) > 0)
		{
			Run_CMDID_writeena(nDeviceIndex,  nLdIndex, nDatasetIndex,_T("遥控") , key_dsGOOSE);//_T("遥控")
		}
		else
		{	
			Run_CMDID_writeena(nDeviceIndex,  nLdIndex, nDatasetIndex,_T("遥控") , key_dsDout);//_T("遥控")
		}
	}
	else if (strID == CMDID_writeenaone)
	{//修改软压板
		if (!WriteEnaOne(nDeviceIndex,  nLdIndex))
		{
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommCmdError, engineCommCmdError);
			return 0;
		}
	}
	else if (strID == CMDID_ReadDataOne)
	{//读单个数据
		if (!ReadOne())
		{
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommCmdError, engineCommCmdError);
			return 0;
		}
	}
	else if (strID == CMDID_readparameter)
	{//读装置参数
		Run_CMDID_readparameter(nDeviceIndex,  nLdIndex, nDatasetIndex);
	}
	else if (strID == CMDID_writeparameter)
	{//修改装置参数
		ACSI_NODE *pDevice = m_pACSI_NODE;

		if (!mms_HasDatasetDataChanged(pDevice/*nDeviceIndex*/, nLdIndex,nDatasetIndex))
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("没有需要修改的数据"));//_T("没有需要修改的数据"));
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommFinish, engineCommFinish);
			return 0;
		}

		theCmsApp->InitWriteFuncParasSingle(nDeviceIndex,  nLdIndex, nDatasetIndex);
	}
	else if (strID == CMDID_readsoe)
	{//读SOE
		theCmsApp->m_pMmsMsgRcvWnd->PostMessage(WM_PROCEDURE_RESET, nDeviceIndex, nDeviceIndex);
	}
	else if (strID == CMDID_readsoeds)
	{//读SOE
		GetVariableVal(_T("DsID"), m_strReadSoeDsPath, _T(""));
		m_strReadSoeDsPath.Replace(_T("\""), _T(""));
	}
	else if (strID == _T("writeyk"))
	{//开出传动

	}
	else if (strID == CMDID_reset)
	{//复位
//		enter_u_mvl_rpt_CriticSection();
		m_pACSI_NODE->nReportBeginIndex = m_pACSI_NODE->nCurrReportIndex;
//		free_u_mvl_rpt_CriticSection();

		if (!g_bResetOnlyClearReport)
		{
			theCmsApp->ResetDevice(nDeviceIndex,  nLdIndex);
		}

		theCmsApp->m_pMmsMsgRcvWnd->PostMessage(WM_PROCEDURE_RESET, nDeviceIndex, nDeviceIndex);
	}
	else if (strID == CMDID_registerreport)
	{//开始报告
		InitRegisterRptPara();

		if (IsDvmDeviceMapExist())
		{
			InitCallReportFuncParas(nDeviceIndex,  nLdIndex, nDatasetIndex, TRUE, _T(""));
		}
		else
		{
			theCmsApp->InitCallReportFuncParas(nDeviceIndex, nLdIndex, nDatasetIndex, TRUE, TRUE);
		}
	}
	else if (strID == CMDID_unregisterreport)
	{//停止报告
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("unregisterreport:数据集：%s")
                                   , strDsPathTemp.GetString());//_T("unregisterreport:数据集：%s")

		if (IsDvmDeviceMapExist())
		{
			InitStopReportFuncParas(nDeviceIndex,  nLdIndex, nDatasetIndex, strDsPathTemp);
		}
		else
		{
			theCmsApp->InitStopReportFuncParas(nDeviceIndex, nLdIndex, nDatasetIndex);
		}
	}
	else if (strID == CMDID_changesetzone)
	{
		long nZone = -1;
		InitChangeSetZone(nZone,nLdIndex);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE,_T("切换定值区：%d") , nZone);//_T("切换定值区：%d")

		if (nZone == -1)
		{
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommCmdError, engineCommCmdError);
			return 0;
		}
	}
	else if (strID == CMDID_readzone)
	{
		m_pACSI_NODE->nSetRunSGIndexState = 1;
		theCmsApp->InitReadLDeviceZoneFuncParas(nDeviceIndex, nLdIndex);
	}
	else if (strID == CMDID_connect)
	{
		theCmsApp->InitLinkDeviceFuncPara_AutoTest(nDeviceIndex, TRUE);
	}
	else if (strID == CMDID_disconnect)
	{
		theCmsApp->InitUnLinkDeviceFuncPara(nDeviceIndex, TRUE, TRUE);
	}
// 	else if (strID == CMDID_logmmserr)
// 	{
// 		long nValue = 0;
// 		GetVariableVal(_T("log"), nValue, 0);
// 		mms_log_error_infor = nValue;
// 	}
	else if (strID == CMDID_SetDataRef)
	{//读单个数据
		SetDataRef(strDsPathTemp);
	}
	else if (strID == CMDID_StartRecord)
	{//StartRecord兼容传统规约的StartRecord，主要是为了设置录波文件的路径

	}
// 	else if (strID == CMDID_ReadLogCount)
// 	{
// 		CString strLogCtrl;
// 		//strLogCtrl = ;//Find LogCtrl by strDsPathTemp
// 		theCmsApp->InitReadJournalState(nDeviceIndex, nLdIndex, strLogCtrl, NULL);
// 	}
	else if (strID == CMDID_ReadLog)
	{
		InitReadJournalFuncParas(nDeviceIndex, nLdIndex, nDatasetIndex, strDsPathTemp);
	}
// 	else if (strID == CMDID_uploadfile)//远程升级程序
// 	{
// 		CString strFiles;
// 		GetVariableVal(ParaID_File, strFiles, _T(""));
// 		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CMDID_uploadfile: file=%s"), strFiles);
// 		CStringArray arrFilePaths;
// 		CString strFolderPath;
// 		strFolderPath = _P_GetSystemPath();
// 		strFolderPath += _T("UpLoadFiles\\");
// 		GetFilePaths(strFolderPath,strFiles ,arrFilePaths);
// 		theCmsApp->InitUploadFiles(nDeviceIndex,arrFilePaths);
// 	}

	if (g_bMmsEngineDebugMode)
	{
		//通讯命令状态，发送通讯命令消息
// 		if (g_bMmsEngineCommError)
// 		{
// 			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommError, engineCommError);
// 		}
// 		else
		{
			mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommFinish, engineCommFinish);
		}

		return 0;
	}

	if (theCmsApp->CallFirstFunc(nDeviceIndex))
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

void CPoCmsDevice::InitRegisterRptPara()
{
	long nVal = -1;
	GetVariableVal(ParaID_TrgOps_1, nVal, -1);
	CRemoteDevs *pRemoteDevs = g_o61850ClientConfig.GetRemoteDevs();

	if (nVal != -1)
	{
		if ((pRemoteDevs->m_nTrgOps_UI%2) != (nVal>0))
		{
			if (nVal>0)
			{
				pRemoteDevs->m_nTrgOps_UI++;
			} 
			else
			{
				pRemoteDevs->m_nTrgOps_UI--;
			}
		}
	}
	
	GetVariableVal(ParaID_TrgOps_4, nVal, -1);

	if (nVal != -1)
	{
		if (((pRemoteDevs->m_nTrgOps_UI>>2)%2) != (nVal>0))
		{
			if (nVal>0)
			{
				pRemoteDevs->m_nTrgOps_UI += 8;
			} 
			else
			{
				pRemoteDevs->m_nTrgOps_UI -= 8;
			}
		}
	}

	GetVariableVal(ParaID_IntgPd, pRemoteDevs->m_nIntgPd, 3000);
}

void CPoCmsDevice::InitChangeSetZone(long &nZone,long nLdIndex)
{
	long nDeviceIndex = mms_GetDeviceNodeIndex(m_pACSI_NODE);

	if ((nLdIndex<0)||(nLdIndex>=m_pACSI_NODE->numLD))
	{
		nLdIndex = mms_FindLDeviceIndex(nDeviceIndex, "prot");//zhowTest20180111
	}

	if ((nLdIndex<0)||(nLdIndex>=m_pACSI_NODE->numLD))
	{
		nLdIndex = mms_FindLDeviceIndex(nDeviceIndex, "pqld1");//zhowTest20180111
	}

	if ((nLdIndex<0)||(nLdIndex>=m_pACSI_NODE->numLD))
	{
		nLdIndex = mms_FindLDeviceIndex(nDeviceIndex, "rcd");
	}

	if ((nLdIndex<0)||(nLdIndex>=m_pACSI_NODE->numLD))
	{
		nZone = -1;
	}
	else
	{
		GetVariableVal(ParaID_setzone, nZone, nZone);
		theCmsApp->InitWriteLDeviceZoneFuncParas(nDeviceIndex, nLdIndex, nZone);
	}
}

void CPoCmsDevice::InitReadJournalFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, const CString &strDsPath)
{
	CString strJournalName;
	long bStart/* = 1*/, nStartType = 1;
	__int64 nStartEntry;
	long bEnd/* = 1*/, nEndType/* = 1*/, nEntryNum/* = 5*/;
	CTime tmStart, tmEnd;
	m_pJournalDatas = &m_pACSI_NODE->LD[nLDIndex].JournalDatas;//zhouhj 关联日志容器
	GetVariableVal(ParaID_tmStart, tmStart);
	GetVariableVal(ParaID_tmEnd, tmEnd);
	MMS_BTOD btod1,btod2;
	tagEVENTTIME tagTime,tagTime2;
	convert_timet_to_btod(tmStart,btod1);
	convert_btod_to_timet(btod1 ,tagTime);
	convert_timet_to_btod(tmEnd,btod2);
	convert_btod_to_timet(btod2 ,tagTime2);
	CString strStartTime,strStartTime2;
	strStartTime.Format("%d-%d-%d %d:%d:%d.%d",tagTime.year,tagTime.month,tagTime.day,tagTime.hour,tagTime.minute,tagTime.second,tagTime.ms);
	strStartTime2.Format("%d-%d-%d %d:%d:%d.%d",tagTime2.year,tagTime2.month,tagTime2.day,tagTime2.hour,tagTime2.minute,tagTime2.second,tagTime2.ms);
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE,"开始查询时间:%s",strStartTime.GetString());
    CLogPrint::LogFormatString(XLOGLEVEL_TRACE,"结束查询时间:%s",strStartTime2.GetString());

	GetVariableVal(ParaID_Log_bStart, bStart, 0);
	GetVariableVal(ParaID_Log_EntryIDStart, nStartEntry, 0);
	GetVariableVal(ParaID_Log_bEnd, bEnd, 0);
	GetVariableVal(ParaID_Log_EntryNum, nEntryNum, 0);

	if (bStart)// 备注: 使用开始条件，条目号为-1时，使用时间检索；条目号不为-1时，使用条目号检索；
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

	if (bEnd)// 备注: 使用结束条件，条目数为-1时，使用结束时间检索；条目数不为-1时，使用条目数检索；
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
    strTmp.Format("nDeviceIndex=%d;nLDIndex=%d;strJournalName = %s;"
                  ,nDeviceIndex,nLDIndex,strJournalName.GetString());
    CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "%s",strTmp.GetString());

	strTmp.Format("bStart=%d;nStartType=%d;bEnd=%d;nEndType=%d;nEntryNum=%d;",bStart,nStartType,bEnd,nEndType,nEntryNum);
    CLogPrint::LogFormatString (XLOGLEVEL_TRACE, "%s",strTmp.GetString());

 	theCmsApp->InitReadJournal(nDeviceIndex, nLDIndex, strJournalName
 		, bStart, nStartType, tmStart, nStartEntry
 		, bEnd, nEndType, tmEnd, nEntryNum);
}

/*
<iot-cmd name="" id=" CreateDevice" testor="">
	<paras>
		<data name="" id="DeviceSN" data-type="" value="装置SN"/>
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
BOOL CPoCmsDevice::InitCmmConfig(CDataGroup *pGroup, BOOL bConnect)
{
	m_nDeviceIndex = mms_GetDeviceNodeIndex(m_pACSI_NODE);

	CString strKey;
	strKey = CDeviceModelXmlKeys::g_pXmlRWKeys->m_strCmsKey;
	CDvmData *pMmsCfg = (CDvmData *)pGroup->FindByID(strKey);
	ACSI_NODE *pDevice = &pACSINode[m_nDeviceIndex];

	if (pMmsCfg != NULL)
	{
		CString strLocalIP, strRemoteIP ,nRemotePort;
		pMmsCfg->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strLocalIPKey,  strLocalIP);
		pMmsCfg->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemoteIPKey,  strRemoteIP);
		pMmsCfg->GetValueByID(CDeviceModelXmlKeys::g_pXmlRWKeys->m_strRemotePortKey,  nRemotePort);

//         device_node_table[m_nDeviceIndex].IP1 = inet_addr(strRemoteIP.GetString());
// 		sock_info_table[m_nDeviceIndex].ip_addr = device_node_table[m_nDeviceIndex].IP1;
		CRemoteDev *pRemote = theCmsApp->GetRemoteDev(m_nDeviceIndex);

		if (pRemote != NULL)
		{
			pRemote->m_strIP = strRemoteIP;
		}
        mms_str_set(&pDevice->IpAddr, strRemoteIP.GetString());
	}
	
/*
	if (m_bIsConfig)
	{////2020-12-22  lijunqing  外部调用配置接口，配置IP：如果是配置，仅仅进行联机操作
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

	CDvmDataset oDataSet;
	oDataSet.AppendEx(*pGroup,FALSE);
	CString strXml;
	oDataSet.GetXml(CDataMngrXmlRWKeys::g_pXmlKeys,strXml);
	CommConfig(strXml);
	oDataSet.RemoveAll();
	//theMmsApi->InitLinkDeviceFuncPara(m_nDeviceIndex, TRUE);
	//theMmsApi->CallFirstFunc(m_nDeviceIndex);

	return TRUE;
}

BOOL CPoCmsDevice::WriteEnaOne(long nDeviceIndex, long  nLdIndex)
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

	theCmsApp->InitCtrlWriteOneFuncParasEx(nDeviceIndex, nLdIndex1, nDsIndex1, nDaIndex1, nDaIndex2, nValue1, nValue2, nTdelay);
	return TRUE;
}

BOOL CPoCmsDevice::ReadOne()
{
	long nDeviceIndex = mms_GetDeviceNodeIndex(m_pACSI_NODE);
	long nLdIndex, nDsIndex, nDaIndex;

	CString strRetDataID;

	if (!GetDataIndex_DataID(nLdIndex, nDsIndex, nDaIndex, strRetDataID))
	{
		return FALSE;
	}

	m_oMmsDatasetMapTool.SetDataPath(strRetDataID);
	theCmsApp->InitReadOneFuncParas(nDeviceIndex, nLdIndex, nDsIndex, nDaIndex, TRUE);

	return TRUE;
}

long CPoCmsDevice::UnLoad(void)
{
	m_pACSI_NODE->nReleaseWhenUnlink = 1;
	m_pACSI_NODE->pRefDevice = NULL;
	theCmsApp->InitUnLinkDeviceFuncPara(m_nDeviceIndex, TRUE, TRUE);
	theCmsApp->CallFirstFunc(m_nDeviceIndex);
//	theCmsApp->OnReleaseDevice();
	//theMmsApi->ReleaseObjData(m_pACSI_NODE);

	//2023-2-2  lijunqing
	delete this;

	return 0;
}

void CPoCmsDevice::Run_CMDID_writeena(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex, const CString &strTitle, const char* pszKey)
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
					theCmsApp->InitCtrlWriteFuncParasEx(nDeviceIndex, nLd, nDs, FALSE);
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
			, strTitle.GetString(), m_oMmsDatasetMapTool.m_strStandDsPath.GetString());//_T("没有需要修改的%s【%s】")
	}
}

BOOL CPoCmsDevice::Run_CMDID_writesetting(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex)
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
			theCmsApp->InitWriteCurrSetsFuncParas(nDeviceIndex,  nLdIndex, nDatasetIndex, nZone, TRUE);
		}
	}

	if (!bNeedWrite)
	{
		//theCmsApp->OutputPrintMsg(g_sLangTxt_HadNoDataNeedEdit);//_T("没有需要修改的数据"));
		CLogPrint::LogString(XLOGLEVEL_TRACE, g_sLangTxt_HadNoDataNeedEdit);
		mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommFinish, engineCommFinish);
	}

	return bNeedWrite;
}

void CPoCmsDevice::Run_CMDID_readena(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex)
{
	theCmsApp->set_OnlyReadValue(TRUE);

	if (!IsDvmDeviceMapExist())
	{
		theCmsApp->InitReadFuncPara(nDeviceIndex,  nLdIndex, nDatasetIndex);
		return;
	}

	POS pos = m_oMmsDatasetMapTool.GetHeadPosition();
	CMmsDvmDs_LdNode_Map *p = NULL;
	long nCount = 0;

	theCmsApp->m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	while (pos != NULL)
	{
		p = (CMmsDvmDs_LdNode_Map *)m_oMmsDatasetMapTool.GetNext(pos);

		theCmsApp->InitReadLDeviceValuesFuncParas(p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ReadEna(%s$%s):DV=%d  LD=%d  DS=%d"), 
			p->m_pLD_NODE->LDName, p->m_pDataset->DataSetID,
			p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
		nCount++;
	}
}

void CPoCmsDevice::Run_CMDID_readsetting(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex)
{
	theCmsApp->set_OnlyReadValue(TRUE);

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

			theCmsApp->InitReadFuncPara_Set(p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO, nZone, m_pACSI_NODE->nRunSGIndex, (nCount == 0));
			CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ReadSettings(%s$%s):DV=%d  LD=%d  DS=%d"), 
				p->m_pLD_NODE->LDName, p->m_pDataset->DataSetID,
				p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
			nCount++;
		}
	}
	else
	{
		theCmsApp->InitReadFuncPara_Set(nDeviceIndex, nLdIndex, nDatasetIndex, nZone, m_pACSI_NODE->nRunSGIndex, TRUE);
	}
}

void CPoCmsDevice::Run_CMDID_readparameter(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex)
{
	theCmsApp->set_OnlyReadValue(TRUE);

	if (!IsDvmDeviceMapExist())
	{
		theCmsApp->InitReadLDeviceValuesFuncParas(nDeviceIndex,  nLdIndex, nDatasetIndex);
		return;
	}

	POS pos = m_oMmsDatasetMapTool.GetHeadPosition();
	CMmsDvmDs_LdNode_Map *p = NULL;
	long nCount = 0;

	theCmsApp->m_oFuncParamEx[nDeviceIndex].DeleteAllFuncParas();

	while (pos != NULL)
	{
		p = (CMmsDvmDs_LdNode_Map *)m_oMmsDatasetMapTool.GetNext(pos);

		theCmsApp->InitReadLDeviceValuesFuncParas(p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ReadParameter(%s$%s):DV=%d  LD=%d  DS=%d"), 
			p->m_pLD_NODE->LDName, p->m_pDataset->DataSetID,
			p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
		nCount++;
	}
}

long CPoCmsDevice::IniSetWriteFuncParasEx(long nDeviceIndex, long  nLdIndex, long  nDatasetIndex, long nZone)
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
					theCmsApp->InitWriteCurrSetsFuncParas(nDeviceIndex, nLd, nDs, nZone, (nCount == 0));
					nCount++;
					break;
				}
			}
		}
	}

	return nCount;
}

void CPoCmsDevice::InitCallReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, BOOL bStart, const CString &strDsPath)
{
	//CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("registerreport:数据集：%s"), strDsPathTemp);
	POS pos = m_oMmsDatasetMapTool.GetHeadPosition();
	CMmsDvmDs_LdNode_Map *p = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		p = (CMmsDvmDs_LdNode_Map *)m_oMmsDatasetMapTool.GetNext(pos);

		theCmsApp->InitCallReportFuncParas(p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO, bStart, FALSE);
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
			, m_oMmsDatasetMapTool.m_strStandDsPath.GetString());//_T("registerreport:数据集：%s 不存在")
		mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommError, engineCommError);
	}
}


void CPoCmsDevice::InitStopReportFuncParas(ST_INT nDeviceIndex, ST_INT nLDIndex, ST_INT nDsIndex, const CString &strDsPath)
{
	POS pos = m_oMmsDatasetMapTool.GetHeadPosition();
	CMmsDvmDs_LdNode_Map *p = NULL;
	long nCount = 0;

	while (pos != NULL)
	{
		p = (CMmsDvmDs_LdNode_Map *)m_oMmsDatasetMapTool.GetNext(pos);

		theCmsApp->InitStopReportFuncParas(p->m_nACSI_NODE, p->m_nLD_NODE, p->m_nDATASET_INFO);
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
			, m_oMmsDatasetMapTool.m_strStandDsPath.GetString());//_T("stopreport:数据集：%s 不存在")
		mms_PostDeviceCommCmdMessage(m_pACSI_NODE, engineCommError, engineCommError);
	}
}
