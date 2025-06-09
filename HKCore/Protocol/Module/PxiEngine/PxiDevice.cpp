// PoDevice.cpp : 实现文件
//

#include "stdafx.h"
#include "../Engine/PpEngineBaseApp.h"
#include "PxiDevice.h"

#include "PxiDataInterface.h"
#include "../XLanguageResourcePp_PpEngine.h"

#include "PxiEngine.h"

// CPxiDevice


CPxiDevice::CPxiDevice()
{
	m_nDataIndex = 0;
	m_hClientMsgWnd = 0;
	m_nClientMsgID = 0;
	m_hClientSysMsgWnd = 0;
	m_nClientSysMsgID = 0;

	m_bHasCreateDataInterface = FALSE;
    m_pPxiDeviceCommCmdMessage = NULL;

	m_pEngineData = NULL;
}

CPxiDevice::~CPxiDevice()
{
   g_thePxiEngine->UnloadDevice(this);
}

void CPxiDevice::OnFinalRelease()
{

}


void CPxiDevice::Out_ConnectDevice()
{
	//连接设备，如果没有配置信息，则弹出对话框进行配置

	if (m_pEngineThread != NULL)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("ConnectDevice"));
		m_pEngineThread->ConnectDevice();
	}
	else
	{
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("connect device failed"));
		m_pEngineData->OnDeviceConnectFinish(FALSE);
	}
}

long CPxiDevice::CommConfig(const CString &strCmmConfig)
{
	In_ConnectDevice(TRUE);

	return m_pEngineData->IsConnectSuccessful();
}

long CPxiDevice::IsConnectSuccessful(void)
{
	if (g_pTheEngineApp->m_bDebugMode)
	{
		return 1;
	}

	if (m_pACSI_NODE == NULL)
	{
		return 0;
	}

	ASSERT (m_pEngineData != NULL);

	if (m_pEngineData == NULL)
	{
		return 0;
	}

	return m_pEngineData->IsConnectSuccessful();
}

long CPxiDevice::GetCount(void)
{

	//返回设备的节点个数
	return m_pACSI_NODE->GetCount();
}

CPxiLogicDevice* CPxiDevice::GetItem(long nIndex)
{
	if (nIndex >= m_pACSI_NODE->GetCount())
	{
		return NULL;
	}

	CDvmLogicDevice *pDvmLdevice = (CDvmLogicDevice*)m_pACSI_NODE->GetAt(nIndex);
	CPxiLogicDevice *pLogicDevice = CPxiLogicDevice::_New_CDeviceNode_LD(pDvmLdevice);

	if (pLogicDevice == NULL)
	{
		return NULL;
	}

	return pLogicDevice;
}

CDvmDataset* CPxiDevice::GetReportDataset(const CString &strDatasetPath)
{
	CDvmDataset *pDataset = NULL;
	CExBaseList *pDevices = (CExBaseList*)m_pACSI_NODE->GetParent();
	CDvmLogicDevice *pLdevice = NULL;

	if (pDevices->GetClassID() == DVMCLASSID_CDVMDEVICES)
	{
		pLdevice = (CDvmLogicDevice*)((CDvmDevices*)pDevices)->FindByID(g_strReportLogicDeviceID);
	}
	else
	{
		pLdevice = (CDvmLogicDevice*)((CPpDvmDevice*)pDevices)->GetDeviceModel()->FindByID(g_strReportLogicDeviceID);
	}

	if (pLdevice == NULL)
	{
		//如果是多数据模型文件，则m_pDevice作为报告设备
		if (m_pEngineData->m_pDevcieModel != NULL)
		{
			CPpDvmDevice *pPpDvmDevice = m_pEngineData->m_pDevcieModel->GetPpDevice();

			if (pPpDvmDevice->m_pDevice != NULL)
			{
				pLdevice = (CDvmLogicDevice*)pPpDvmDevice->m_pDevice->FindByID(g_strReportLogicDeviceID);
			}
		}

	}

	if (pLdevice == NULL)
	{
		return NULL;
	}

	long nPos = strDatasetPath.Find('$');
	CString strID;

	if (nPos > 0)
	{
		strID = strDatasetPath.Mid(nPos+1);
		strID.MakeLower();
	}

	if (strID == _T("none"))
	{
		strID = _T("soe");
	}

	pDataset = dvm_FindDataset(pLdevice, strID);

	if (pDataset == NULL)
	{
		if (m_strReadSoeDsPath.GetLength() > 0)
		{
			pDataset = dvm_FindDataset(pLdevice, m_strReadSoeDsPath);
		}
	}

	if (pDataset == NULL)
	{
		strID = _T("soe");
		pDataset = dvm_FindDataset(pLdevice, strID);
	}

	CAutoSimpleLock oLock(g_oDeviceBindListCriticSection);

	CDvmDataset *pNew = (CDvmDataset*)pDataset->Clone();

	if (strID == _T("soe"))
	{
		pDataset->DeleteAll();
	}

	return pNew;
}

CPxiDataSet* CPxiDevice::FindDataSet(const CString &strDataSetName)
{
    CDvmDataset *pDataset = FindDvmDataset(strDataSetName);

    if (pDataset == NULL)
    {
        return NULL;
    }

    CPxiDataSet *pPoDataset = CPxiDataSet::_NewPoDataset(pDataset);

    return pPoDataset;
}

CPxiData* CPxiDevice::FindData(const CString &strPath)
{

	CDvmData *pDA = NULL;
	CDvmDataset *pDataset = NULL;
	CString strText;
	strText = strPath;

	if (strText.Find(_T("$")) >= 0)
	{
		pDA = (CDvmData*)m_pACSI_NODE->SelectData(strPath);

		if (pDA == NULL)
		{
			return NULL;
		}

		if (pDA->GetClassID() != DVMCLASSID_CDVMDATA)
		{
			return NULL;
		}
	}
	else
	{
		m_oShortData.m_strName = strText;
		m_oShortData.m_strID   = strText;
		pDataset = m_pACSI_NODE->GetDeviceAttrs();
		pDA = (CDvmData*)pDataset->FindByID(strText);

		if (pDA != NULL)
		{
#ifdef _DVM_VALUE_USE_CHAR_
			wcscpy(m_oShortData.m_strValue, pDA->m_strValue);
#else
			m_oShortData.m_strValue = pDA->m_strValue;
#endif
		}
		else
		{
#ifdef _DVM_VALUE_USE_CHAR_
			m_oShortData.m_strValue[0] = 0;
#else
			m_oShortData.m_strValue.Empty();
#endif
		}

		pDA = &m_oShortData;

        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("GetDeviceAttr:%s=%s"), strText.GetString(), m_oShortData.m_strValue.GetString());
	}

	CPxiData *pData = CPxiData::_NewPoData(pDA);

	return pData;
}

long CPxiDevice::GetCurrWriteDataCount()
{
	POS pos = m_pCurrDataset->FindIndex(m_nDataIndex);
	CDvmData *pData = NULL;
	m_nWriteDataCount = 0;

	while (pos != NULL)
	{
		pData = (CDvmData *)m_pCurrDataset->GetNext(pos);

		if (pData->m_dwReserved == 1)
		{
			m_nWriteDataCount++;
		}
	}

	return m_nWriteDataCount;
}

CDvmData* CPxiDevice::GetCurrWriteData()
{
	if (m_nDataIndex >= m_pCurrDataset->GetCount())
	{
		return NULL;
	}

	POS pos = NULL;
	
	if (m_nDataIndex == -1)
	{
		pos = m_pCurrDataset->FindIndex(m_nDataIndex);
	}
	else
	{
		pos = m_pCurrDataset->GetHeadPosition();
	}

	CDvmData *pData = NULL;
	CDvmData *pDataFind = NULL;

	if (pos == NULL)
	{
		pos = m_pCurrDataset->GetHeadPosition();
		m_nDataIndex = 0;
	}

	while (pos != NULL)
	{
		pData = (CDvmData *)m_pCurrDataset->GetNext(pos);

		if (pData->m_dwReserved == 1)
		{
			pDataFind = pData;
			break;
		}

		m_nDataIndex++;
	}
	
	return pDataFind;
}


void CPxiDevice::AddData2(const CString &strID, const CString &strValue)
{
	CBbVariable *pVariable = new CBbVariable();
	pVariable->m_strID = strID;
	pVariable->m_strValue = strValue;
	m_listDataInterface.AddHead(pVariable);
}


void CPxiDevice::AddData2(const CString &strID, const long &nValue)
{
	CBbVariable *pVariable = new CBbVariable();
	pVariable->m_strID = strID;
	pVariable->m_strValue.Format(_T("%d"), nValue);
	m_listDataInterface.AddHead(pVariable);
}

void CPxiDevice::RunProcedure_WriteSingle(const CString &strProcedureID)
{
	ASSERT (m_pCurrDataset != NULL);

	if (m_pCurrDataset == NULL)
	{
		PostDeviceCommCmdMessage(engineCommFinish, engineCommFinish);
		return;
	}

	CDvmData *pData = GetCurrWriteData();

	if (pData == NULL)
	{
		PostDeviceCommCmdMessage(engineCommFinish, engineCommFinish);
		return;
	}

	CDvmLogicDevice *pCpu = (CDvmLogicDevice*)m_pCurrDataset->GetParent();
	AddData2(g_strVariableDataTypeItemIndexID, pData->m_nIndex);
	AddData2(g_strVariableDataTypeGROUPID, m_pCurrDataset->m_strID);
	AddData2(g_strVariableDataTypeCPUID, pCpu->m_strID);

	CPpEngineThreadBase *pEngineThread = GetThread();

	if (!pEngineThread->RunProcedure(strProcedureID, &m_listDataInterface, FALSE))
	{
		PostDeviceCommCmdMessage(engineCommCmdError, engineCommCmdError);
	}

}

long CPxiDevice::RunProcedure_WriteAll(const CString &strProcedureID)
{
	CPpEngineThreadBase *pEngineThread = GetThread();
	CDvmLogicDevice *pCpu = (CDvmLogicDevice*)m_pCurrDataset->GetParent();
	AddData2(g_strVariableDataTypeGROUPID, m_pCurrDataset->m_strID);
	AddData2(g_strVariableDataTypeCPUID, pCpu->m_strID);

	if (!pEngineThread->RunProcedure(strProcedureID, &m_listDataInterface, FALSE))
	{
		return engineCommCmdError;
		//PostDeviceCommCmdMessage(engineCommCmdError, engineCommCmdError);
	}
	else
	{
		return 0;
	}
}


BOOL CPxiDevice::IsWriteProcedure()
{
	CString strProcedure = m_strProcedureID;
	strProcedure.MakeLower();

	return (strProcedure.Find(_T("write")) >= 0);
}

CString CPxiDevice::FindDataInterfaceValue(const CString &strID)
{
	CBbVariable *pFind = (CBbVariable*)m_listDataInterface.FindByID(strID);

	if (pFind == NULL)
	{
		return _T("");
	}
	else
	{
		return pFind->m_strValue;
	}
}

BOOL CPxiDevice::RunProcedure_Static()
{
	CPpEngineThreadBase *pEngineThread = GetThread();
	CPpTemplate *pPpTemplate = pEngineThread->m_pTemplate;

    //2020-5-21 lijunqing
//	if (pPpTemplate == NULL)
//	{
//		PostDeviceCommCmdMessage(engineCommError, engineCommError);
//		return TRUE;
//	}

	BOOL bRet = TRUE;

	if (m_strProcedureID == _T("registerreport"))
	{//开始报告
		if ((pPpTemplate != NULL) && (m_pCurrDataset != NULL))
		{
			pPpTemplate->RegisterReport(m_pCurrDataset);
		}

		bRet = FALSE;
	}
	else if (m_strProcedureID == _T("unregisterreport"))
	{//停止报告
		if ((pPpTemplate != NULL) && (m_pCurrDataset != NULL))
		{
			pPpTemplate->UnRegisterReport(m_pCurrDataset);
		}

		bRet = FALSE;
	}
	else if (m_strProcedureID == _T("recordpackage"))
	{
		m_pEngineData->RecordPackage(FindDataInterfaceValue(_T("PackageID")));
	}
	else if (m_strProcedureID == _T("unrecordpackage"))
	{
		m_pEngineData->UnRecordPackage(FindDataInterfaceValue(_T("PackageID")));
	}
	else if (m_strProcedureID == _T("recordprocedure"))
	{
		m_pEngineData->RecordProcedure(FindDataInterfaceValue(_T("ProcedureID")));
	}
	else if (m_strProcedureID == _T("unrecordprocedure"))
	{
		m_pEngineData->UnRecordProcedure(FindDataInterfaceValue(_T("ProcedureID")));
	}
	else if (m_strProcedureID == _T("readpackage"))
	{
		
	}
	else if (m_strProcedureID == _T("writedsvalue"))
	{

	}
	else
	{
		bRet = FALSE;
	}

	return bRet;
}

BOOL CPxiDevice::RunProcedure_ChnTest()
{
	return TRUE;
}


void CPxiDevice::GetVariableVal(const CString &strID, long &nVal, long nDefaultVal)
{
	CBbVariable *pVariable = NULL;
	pVariable = (CBbVariable*)m_listDataInterface.FindByID(strID);

	if (pVariable != NULL)
	{
		nVal = CString_To_long(pVariable->m_strValue);
	}
	else
	{
		nVal = nDefaultVal;
	}
}

void CPxiDevice::GetVariableVal(const CString &strID, float &fVal, float fDefaultVal)
{
	CBbVariable *pVariable = NULL;
	pVariable = (CBbVariable*)m_listDataInterface.FindByID(strID);

	if (pVariable != NULL)
	{
		fVal = (float)CString_To_double(pVariable->m_strValue);
	}
	else
	{
		fVal = fDefaultVal;
	}
}

void CPxiDevice::GetVariableVal(const CString &strID, CString &strVal, const CString &strDefaultVal)
{
	CBbVariable *pVariable = NULL;
	pVariable = (CBbVariable*)m_listDataInterface.FindByID(strID);

	if (pVariable != NULL)
	{
		strVal = pVariable->m_strValue;
	}
	else
	{
		strVal = strDefaultVal;
	}
}

void CPxiDevice::GetVariableVal(BSTR strID, long &nVal, long nDefaultVal)
{
	CBbVariable *pVariable = NULL;
	pVariable = (CBbVariable*)m_listDataInterface.FindByID(CString(strID));

	if (pVariable != NULL)
	{
		nVal = CString_To_long(pVariable->m_strValue);
	}
	else
	{
		nVal = nDefaultVal;
	}
}

void CPxiDevice::GetVariableVal(BSTR strID, float &fVal, float fDefaultVal)
{
	CBbVariable *pVariable = NULL;
	pVariable = (CBbVariable*)m_listDataInterface.FindByID(CString(strID));

	if (pVariable != NULL)
	{
		fVal = (float)CString_To_double(pVariable->m_strValue);
	}
	else
	{
		fVal = fDefaultVal;
	}
}

void CPxiDevice::GetVariableVal(BSTR strID, CString &strVal, const CString &strDefaultVal)
{
	CBbVariable *pVariable = NULL;
	pVariable = (CBbVariable*)m_listDataInterface.FindByID(CString(strID));

	if (pVariable != NULL)
	{
		strVal = pVariable->m_strValue;
	}
	else
	{
		strVal = strDefaultVal;
	}
}

void CPxiDevice::AddPachageSend()
{

}

BOOL CPxiDevice::RunProcedure_ChnTest_Serial()
{
	m_oDeviceCmmConfig.DeleteAll();

	CCmmSerialConfig *pSerial = m_oDeviceCmmConfig.AddConfigSerial();
	CDeviceModelXmlKeys *pKey = CDeviceModelXmlKeys::g_pXmlRWKeys;

	GetVariableVal(pKey->m_strPortNumKey,pSerial->m_nPortNum, 1);
	GetVariableVal(pKey->m_strBaudRateKey,pSerial->m_nBaudRate, 9600);
	GetVariableVal(pKey->m_strByteSizeKey,pSerial->m_nDataBit, 8);
	GetVariableVal(pKey->m_strStopBitsKey,pSerial->m_fStopBit, 1);
	GetVariableVal(pKey->m_strParityKey,pSerial->m_nParity, 2);

	return TRUE;
}

BOOL CPxiDevice::RunProcedure_ChnTest_UdpClient()
{
	m_oDeviceCmmConfig.DeleteAll();

	CCmmUdpClientConfig *pUdpClient = m_oDeviceCmmConfig.AddConfigUdpClient();
	CDeviceModelXmlKeys *pKey = CDeviceModelXmlKeys::g_pXmlRWKeys;

	GetVariableVal(pKey->m_strLocalIPKey, pUdpClient->m_strLocalIP, _T("192.168.1.100"));
	GetVariableVal(pKey->m_strLocalPortKey, pUdpClient->m_nLocalPort, 5000);

	GetVariableVal(pKey->m_strRemoteIPKey, pUdpClient->m_strRemoteIP, _T("192.168.1.100"));
	GetVariableVal(pKey->m_strRemotePortKey, pUdpClient->m_nRemotePort, 5000);

	GetVariableVal(pKey->m_strUseBroadcastKey, pUdpClient->m_nUseBroadcast, 0);
	GetVariableVal(pKey->m_strMulticastIPKey, pUdpClient->m_strMulticastIP, _T("0.0.0.0"));
	GetVariableVal(pKey->m_strMulticastPortKey, pUdpClient->m_nMulticastPort, 5000);

	return TRUE;
}

BOOL CPxiDevice::RunProcedure_ChnTest_UdpServer()
{
	m_oDeviceCmmConfig.DeleteAll();

	CCmmUdpServerConfig *pUdpServer = m_oDeviceCmmConfig.AddConfigUdpServer();
	CDeviceModelXmlKeys *pKey = CDeviceModelXmlKeys::g_pXmlRWKeys;

	GetVariableVal(pKey->m_strLocalIPKey, pUdpServer->m_strLocalIP, _T("192.168.1.100"));
	GetVariableVal(pKey->m_strLocalPortKey, pUdpServer->m_nLocalPort, 5000);

	GetVariableVal(pKey->m_strUseBroadcastKey, pUdpServer->m_nUseBroadcast, 0);
	GetVariableVal(pKey->m_strMulticastIPKey, pUdpServer->m_strMulticastIP, _T("0.0.0.0"));
	GetVariableVal(pKey->m_strMulticastPortKey, pUdpServer->m_nMulticastPort, 5000);

	return TRUE;
}

BOOL CPxiDevice::RunProcedure_ChnTest_TcpClient()
{
	m_oDeviceCmmConfig.DeleteAll();

	CCmmTcpClientConfig *pTcpClient = m_oDeviceCmmConfig.AddConfigTcpClient();
	CDeviceModelXmlKeys *pKey = CDeviceModelXmlKeys::g_pXmlRWKeys;

	GetVariableVal(pKey->m_strLocalIPKey, pTcpClient->m_strLocalIP, _T("192.168.1.100"));
	GetVariableVal(pKey->m_strLocalPortKey, pTcpClient->m_nLocalPort, 5000);

	GetVariableVal(pKey->m_strRemoteIPKey, pTcpClient->m_strRemoteIP, _T("192.168.1.100"));
	GetVariableVal(pKey->m_strRemotePortKey, pTcpClient->m_nRemotePort, 5000);

	return TRUE;
}

BOOL CPxiDevice::RunProcedure_ChnTest_TcpServer()
{
	CCmmTcpServerConfig *pTcpServer = m_oDeviceCmmConfig.AddConfigTcpServer();
	CDeviceModelXmlKeys *pKey = CDeviceModelXmlKeys::g_pXmlRWKeys;

	GetVariableVal(CString(pKey->m_strLocalIPKey), pTcpServer->m_strLocalIP, _T("192.168.1.100"));
	GetVariableVal(CString(pKey->m_strLocalPortKey), pTcpServer->m_nLocalPort, 5000);
	pTcpServer->m_bPostConnectFinishMsgAfterAccept = TRUE;

	return TRUE;
}

BOOL CPxiDevice::RunProcedure_ChnTest_Exit()
{
	return TRUE;
}

long CPxiDevice::RunProcedure(const CString &strProcedureID, const CString &strDatasetPath)
{
    m_strDatasetPathOfProcedure = strDatasetPath;  //2020-11-25  lijunqing
	m_strReadSoeDsPath.Empty();
	m_strProcedureID = strProcedureID;
	//g_pTheEngineApp->ShowSpyWnd();

	if (g_bLogEngineDebugInfor)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("+++++++++++++++RunProcedure: %s(%s)"), m_strProcedureID.GetString(),  m_strDatasetPathOfProcedure.GetString());
	}

	//2018-11-6  增加通讯错误测试模式，如果连接不成功，则直接返回通讯错误
	if (!m_pEngineData->IsConnectSuccessful())
	{
		PostDeviceCommCmdMessage(engineCommError, engineCommError);
		return 0;
	}

	CPpEngineThreadBase *pEngineThread = GetThread();
	ASSERT (pEngineThread != NULL);

	if (pEngineThread == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"COM:RunProcedure Failed");
        return -1;  //error  2020-5-21   lijq     0;
	}

	//如果创建了通讯命令参数对象，则参数从外部传入，此处不能清空
	//次变量能够保持新老版本的程序兼容性
	if (!m_bHasCreateDataInterface)
	{
		m_listDataInterface.DeleteAll();
	}

	m_pCurrDataset = (CDvmDataset *)m_pACSI_NODE->SelectData(strDatasetPath);

	m_strProcedureID.MakeLower();

	if (RunProcedure_Static())
	{
        //2020-5-21  lijunqing
		PostDeviceCommCmdMessage(engineCommFinish, engineCommFinish);   //SHAOLEI  20201212
        return engineCommFinish ;//0;
	}

	if (m_strProcedureID == CMDID_readsoeds)
	{//读SOE
		GetVariableVal(_T("DsID"), m_strReadSoeDsPath, _T(""));
		m_strReadSoeDsPath.Replace(_T("\""), _T(""));
	}

	StartProgress();
	m_strProcedureID = strProcedureID;
    long nRet = 0;

	if (m_pCurrDataset != NULL)
	{
		InitProcedureInterface(m_pCurrDataset);

		if (IsWriteProcedure())
		{
			nRet = RunProcedure_WriteAll(m_strProcedureID);
		}
		else
		{
			if (!pEngineThread->RunProcedure(strProcedureID, &m_listDataInterface, FALSE))
			{
                //2020-5-21  lijunqing
                nRet = engineCommCmdError;
                //PostDeviceCommCmdMessage(engineCommCmdError, engineCommCmdError);
			}
		}
	}
	else
	{
		if (!pEngineThread->RunProcedure(strProcedureID, &m_listDataInterface, FALSE))
		{
            //2020-5-21  lijunqing
            nRet = engineCommCmdError;
            //PostDeviceCommCmdMessage(engineCommCmdError, engineCommCmdError);
		}
	}

	m_strProcedureID.MakeLower();

	if (m_strProcedureID == _T("reset"))
	{//复位
		//清空报告节点
		m_pEngineData->RunReset();

#ifndef _PSX_IDE_QT_
        if (::IsWindow(g_hDeviceBindListMsgWnd))
		{
			::PostMessage(g_hDeviceBindListMsgWnd, WM_USER+1053, 0, 0);
		}
#endif
	}

	if (g_pTheEngineApp->m_bDebugMode)
	{
        //2020-5-21  lijunqing
        nRet = engineCommFinish;
	}

	if (nRet != 0)
	{
	  PostDeviceCommCmdMessage(nRet, nRet);   //SHAOLEI  20201212
	}

    return nRet;
}

#define DI_ID_CPUINDEX  _T("nCpuIndex")
#define DI_ID_GROUPINDEX  _T("nGroupIndex")

void CPxiDevice::InitProcedureInterface(CDvmDataset *pDvmDataset)
{
	CDvmLogicDevice *pLd = (CDvmLogicDevice*)pDvmDataset->GetParent();
	CBbVariable *pVariable = (CBbVariable*)m_listDataInterface.FindByID(DI_ID_CPUINDEX);

	if (pVariable == NULL)
	{
		pVariable = new CBbVariable();
		pVariable->m_strID = DI_ID_CPUINDEX;
		pVariable->m_strName = pVariable->m_strID;
		m_listDataInterface.AddNewChild(pVariable);
	}

	pVariable->m_strValue.Format(_T("%d"), pLd->m_nIndex);

	pVariable = (CBbVariable*)m_listDataInterface.FindByID(DI_ID_GROUPINDEX);

	if (pVariable == NULL)
	{
		pVariable = new CBbVariable();
		pVariable->m_strID = DI_ID_GROUPINDEX;
		pVariable->m_strName = pVariable->m_strID;
		m_listDataInterface.AddNewChild(pVariable);
	}

	pVariable->m_strValue.Format(_T("%d"), pDvmDataset->m_nIndex);
}

long CPxiDevice::RunProcedureEx(const CString &strProcedureScript)
{

	// TODO: 在此添加调度处理程序代码

	return 0;
}

long CPxiDevice::AttachSystemWndMsg(ULONG hWnd, ULONG nMsgID)
{

	StartProgress();
	ASSERT (m_pEngineData != NULL);

	m_hClientSysMsgWnd = hWnd;
	m_nClientSysMsgID = nMsgID;

	if (m_pEngineData != NULL)
	{
		m_pEngineData->m_oSystemMsgSendRegister.m_nHWndOrThreadID = (ULONG)g_hDeviceBindListMsgWnd;
		m_pEngineData->m_oSystemMsgSendRegister.m_nMessageID = WM_SYSTEM_MSG;
		m_pEngineData->m_oSystemMsgSendRegister.m_wParam = 0;
		m_pEngineData->m_oSystemMsgSendRegister.m_lParam = 0;
        m_pEngineData->m_pPxiDeviceCommCmdMessage = m_pPxiDeviceCommCmdMessage;
	}

	return 0;
}

long CPxiDevice::RegisterProcedureWndMsg(const CString &strProcedureID, ULONG hWnd, ULONG nMsgID)
{

	m_strProcedureID = strProcedureID;
	m_hClientMsgWnd = hWnd;
	m_nClientMsgID = nMsgID;

	ASSERT (m_pEngineData != NULL);

	if (m_pEngineData != NULL)
	{
		MSGSENDREGISTER oMsgRegister;

		oMsgRegister.nMsgType = MSGSENDTYPE_WINDOW;
		oMsgRegister.nHWndOrThreadID = (ULONG)g_hDeviceBindListMsgWnd;
		
		oMsgRegister.nMessageID = WM_PROCEDURE_END_MSG;
		oMsgRegister.nItemData = -1;
		oMsgRegister.strID = strProcedureID;
		oMsgRegister.wParam = 0;
		oMsgRegister.lParam = 0;

		m_pEngineData->Register(&oMsgRegister
			, MSREGMASK_MSGTYPE | MSREGMASK_HWNDORTHREADID | MSREGMASK_MESSAGEID 
			| MSREGMASK_ITEMDATA | MSREGMASK_ID | MSREGMASK_WPARAM | MSREGMASK_LPARAM);
	}

	return 0;
}

long CPxiDevice::UnRegisterProcedureWndMsg(const CString &strProcedureID, ULONG hWnd, ULONG nMsgID)
{

	m_strProcedureID.Empty();
	m_hClientMsgWnd = NULL;
	ASSERT (m_pEngineData != NULL);

	if (m_pEngineData != NULL)
	{
		MSGSENDREGISTER oMsgRegister;

		oMsgRegister.nMsgType = MSGSENDTYPE_WINDOW;
		oMsgRegister.nHWndOrThreadID = (ULONG)g_hDeviceBindListMsgWnd;
		
		oMsgRegister.nMessageID = WM_PROCEDURE_END_MSG;
		oMsgRegister.nItemData = -1;
		oMsgRegister.wParam = 0;
		oMsgRegister.lParam = 0;
		oMsgRegister.strID = strProcedureID;

		m_pEngineData->UnRegister(&oMsgRegister
			, MSREGMASK_MSGTYPE | MSREGMASK_HWNDORTHREADID | MSREGMASK_MESSAGEID 
			| MSREGMASK_ITEMDATA | MSREGMASK_ID | MSREGMASK_WPARAM | MSREGMASK_LPARAM);
	}

	return 0;
}

long CPxiDevice::RegisterDataChangedWndMsg(const CString &strDataPath, ULONG hWnd, ULONG nWMsgID)
{

	ASSERT (m_pEngineData != NULL);
	long nNodeIndex = 0;

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"Register Data Changed Wnd Msg : node index=%d", nNodeIndex);

	if (m_pEngineData != NULL)
	{
		MSGSENDREGISTER oMsgRegister;

		oMsgRegister.nMsgType = MSGSENDTYPE_WINDOW;
		oMsgRegister.nHWndOrThreadID = hWnd;
		oMsgRegister.nMessageID = nWMsgID;
		oMsgRegister.nItemData = nNodeIndex;
		oMsgRegister.strID = L"";
		oMsgRegister.wParam = 0;
		oMsgRegister.lParam = 0;
		m_pEngineData->Register(&oMsgRegister
			, MSREGMASK_MSGTYPE | MSREGMASK_HWNDORTHREADID | MSREGMASK_MESSAGEID 
			| MSREGMASK_ITEMDATA | MSREGMASK_ID | MSREGMASK_WPARAM | MSREGMASK_LPARAM);
	}

	return 0;
}

long CPxiDevice::UnRegisterDataChangedWndMsg(const CString &strDataPath)
{
	return 0;
}

long CPxiDevice::UnLoad(void)
{
	m_pEngineData->ExitEngineThread();
    g_thePxiEngine->UnloadDevice(this);

	return 0;
}

CString CPxiDevice::GetXmlData(void)
{
	CString strResult;
	return strResult;
}

long CPxiDevice::SetXmlData(const CString &bstrXmlData)
{
	return 0;
}

CString CPxiDevice::GetXmlDataEx(const CString &strDatasetPath)
{
	CDvmDataset *pDataset = (CDvmDataset *)m_pACSI_NODE->SelectData(strDatasetPath);
	CString strResult;

	if (pDataset != NULL)
	{
		pDataset->GetXml(CDataMngrXmlRWKeys::g_pXmlKeys, strResult);
	}

	return strResult;
}

long CPxiDevice::SetXmlDataEx(const CString &strDatasetPath, const CString &strXmlData)
{

	CString strResult;

	return 0;
}


//////////////////////////////////////////////////////////////////////////

void CPxiDevice::StartProgress()
{		

}

void CPxiDevice::StopProgress()
{

}

void CPxiDevice::OnProcedureEnd(const CString &strProcedure, WPARAM wParam, LPARAM lParam)
{
	CString str1 = m_strProcedureID;
	CString str2 = strProcedure;
	str1.MakeLower();
	str2.MakeLower();

	if (str1  != str2)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                 ,g_sLangTxt_DiffError.GetString() /*_T("当前过程【%s】；结束的过程【%s】，两者不同，发生错误")*/
                 , str1.GetString(), str2.GetString());
		return;
	}

	CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Pxist Procedure End Message %d [%d, %d]"), m_nClientSysMsgID, wParam, lParam);
	PostDeviceCommCmdMessage(wParam, lParam);
	StopProgress();
}

void CPxiDevice::OnSystemMsg(WPARAM wParam, LPARAM lParam)
{
	if (g_bLogEngineDebugInfor)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("Pxist System Message %d [%d, %d]"), m_nClientMsgID, wParam, lParam);
	}

	PostDeviceSysMessage(wParam, lParam);
}

void CPxiDevice::PostDeviceCommCmdMessage(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = (HWND)m_hClientMsgWnd;

	if (m_strProcedureID.GetLength() == 0)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR, _T("===============PostDeviceCommCmdMessage  Error")
                 ,m_strProcedureID.GetString(), m_hClientMsgWnd, m_nClientMsgID);
		return;
	}

	long nDeviceIndex = g_pTheEngineApp->FindDeviceIndex(m_pEngineData);
	wParam = nDeviceIndex;
    CLogPrint::LogFormatString(XLOGLEVEL_INFOR
             , g_sLangTxt_SendTestInf.GetString()/*_T("===============发送测试完成消息[%s] WND=【%08x】 MSG=【%08x】")*/
             , m_strProcedureID.GetString(), m_hClientMsgWnd, m_nClientMsgID);

    if (m_pPxiDeviceCommCmdMessage != NULL)
    {
        m_pPxiDeviceCommCmdMessage->OnCommCmdMessage(wParam, lParam);
    }

    if (hWnd != 0)
    {
        ::PostMessage(hWnd, m_nClientMsgID, wParam, lParam);
    }
}

void CPxiDevice::PostDeviceSysMessage(WPARAM wParam, LPARAM lParam)
{
	HWND hWnd = (HWND)m_hClientSysMsgWnd;

	long nDeviceIndex = g_pTheEngineApp->FindDeviceIndex(m_pEngineData);
	wParam = nDeviceIndex;
	
	if (g_bLogEngineDebugInfor)
	{
        CLogPrint::LogFormatString(XLOGLEVEL_INFOR
                 , g_sLangTxt_SendSystemMsg.GetString()/*_T("发送系统消息 WND=【%08x】 MSG=【%08x】(%d, %d)")*/
                 , m_hClientSysMsgWnd, m_nClientSysMsgID, wParam, lParam);
	}

    if (m_pPxiDeviceCommCmdMessage != NULL)
    {
        m_pPxiDeviceCommCmdMessage->OnSysMessage(wParam, lParam);
    }

    if (hWnd != 0)
    {
        ::PostMessage(hWnd, m_nClientSysMsgID, wParam, lParam);
    }
}

CPxiDataInterface* CPxiDevice::GetDataInterface(void)
{
	m_bHasCreateDataInterface = TRUE;
    CPxiDataInterface *pPoDataInterface = CPxiDataInterface::_New_CPxiDataInterface(&m_listDataInterface);
    return pPoDataInterface;
}

 CPxiDataInterface* CPxiDevice::GetDataInterface(CPxiDataInterface &oDataInterface)
 {
     oDataInterface.SetDataInterface( &m_listDataInterface );
     return &oDataInterface;
 }

long CPxiDevice::ConnectDevice(void)
{
	In_ConnectDevice(TRUE);

	return 0;
}

void CPxiDevice::In_ConnectDevice(BOOL bConnect)
{
    m_pEngineData->m_pPoDeviceProcedureInterface = this;

	if (!bConnect)
	{
		m_pEngineData->OnDeviceConnectFinish(TRUE);
		return;
	}

	if (g_pTheEngineApp->m_bDebugMode)
	{
		m_pEngineData->OnDeviceConnectFinish(TRUE);
		return ;
	}

	if (m_pEngineThread != NULL)
	{
		if (g_bLogEngineDebugInfor)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("CommConfig::PostThreadMessage"));
		}

		if (m_pEngineThread->IsConnectSuccessful())
		{
			m_pEngineData->OnDeviceConnectFinish(TRUE);
		}
		else
		{
			if (m_pEngineThread->IsConnecting())
			{
				if (g_bLogEngineDebugInfor)
				{
					CLogPrint::LogString(XLOGLEVEL_TRACE, _T("IsConnecting, WaitDeviceConnectFinished"));
				}

				m_pEngineThread->WaitDeviceConnectFinished();
				m_pEngineData->OnDeviceConnectFinish(TRUE);
			}
			else
			{
				m_pEngineThread->PostThreadMessage(WM_THREAD_CONNECT, (WPARAM)this, (LPARAM)this);
			}
		}
	}
	else
	{//弹出对话框，配置设备、通讯
		CLogPrint::LogString(XLOGLEVEL_ERROR, _T("connect device failed"));
		m_pEngineData->OnDeviceConnectFinish(FALSE);
	}
}

CString CPxiDevice::GetAttrByID(const CString &strAttrID)
{
	CString strResult("");
	CString strTemp;
	strTemp = strAttrID;
	strTemp.MakeLower();

	if (strTemp == _T("rcd-file-path"))
	{
		strResult = m_pEngineData->m_strRcdFilePath;
	}
	else
	{
		CPpDvmDevice *pPpDvmDevice = m_pEngineData->m_pDevcieModel->GetPpDevice();

		if (pPpDvmDevice != NULL)
		{
			strTemp = strAttrID;
			CDvmDataset *pDevceAttrs = pPpDvmDevice->m_pDevice->GetDeviceAttrs();
			CDvmData *pData = (CDvmData*)pDevceAttrs->FindByID(strTemp);

			if (pData != NULL)
			{
				strResult = pData->m_strValue ;
			}
		}
	}

	return strResult;
}

long CPxiDevice::SetAttrByID(const CString &strAttrID, const CString &strValue)
{
	CString strTemp;
	strTemp = strAttrID;
	strTemp.MakeLower();

	if (strTemp == _T("rcd-file-path"))
	{
		m_pEngineData->m_strRcdFilePath = strValue;
	}
	else
	{
		CPpDvmDevice *pPpDvmDevice = m_pEngineData->m_pDevcieModel->GetPpDevice();

		if (pPpDvmDevice != NULL)
		{
			strTemp = strAttrID;
			CDvmDataset *pDevceAttrs = pPpDvmDevice->m_pDevice->GetDeviceAttrs();
			CDvmData *pData = (CDvmData*)pDevceAttrs->FindByID(strTemp);

			if (pData != NULL)
			{
				strTemp = strValue;

#ifdef _DVM_VALUE_USE_CHAR_
#ifdef UNICODE
				wcscpy(pData->m_strValue, strTemp);
#else
				CString bstr = strTemp.AllocSysString();
				wcscpy(pData->m_strValue, bstr);
				::SysFreeString(bstr);
#endif
#else
				pData->m_strValue = strTemp;
#endif
			}
		}
	}

	return 0;
}


long CPxiDevice::SaveDvmFile(const CString &strDvmFile)
{
	return 0;
}

long CPxiDevice::SetCommConfig(const CString &strCommConfig)
{
	CLogPrint::LogString(XLOGLEVEL_TRACE, _T("..................Device::CommConfig..............."));

#ifdef UNICODE
	if (wcslen(strCommConfig) > 10)
#else
    if (strCommConfig.GetLength() > 10)
#endif
	{
        BSTR bstrCmmConfig;
        bstrCmmConfig = strCommConfig.AllocSysString();
		m_pEngineData->m_pDeviceCmmConfigRef->InitByOnlyConfig(bstrCmmConfig);
        ::SysFreeString(bstrCmmConfig);
	}

	return 0;
}

CString CPxiDevice::GetCommConfig(void)
{
	CString strResult;
	return strResult;
}

//2020-9-8  lijunqing
BOOL CPxiDevice::InitCmmConfig(CDataGroup *pGroup, BOOL bConnect)
{
    if (m_pEngineData != NULL)
    {
        m_pEngineData->InitCmmConfig(pGroup);

        if (bConnect)
        {
            In_ConnectDevice(TRUE);
            return m_pEngineData->IsConnectSuccessful();
        }
        else
        {
            return TRUE;
        }
    }

    return FALSE;
}

//shaolei 2023-9-11 通过定时器，读实时值。不发通讯消息，不弹进度条。仅在后台执行
long CPxiDevice::RunProcedure_Timer_ReadAin()
{
	CPpEngineThreadBase *pEngineThread = GetThread();
	ASSERT (pEngineThread != NULL);

	if (pEngineThread == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, L"RunProcedure_Timer_ReadAin Failed");
		return -1;  //error  2020-5-21   lijq     0;
	}

	CString strProcedureID;
	strProcedureID = CMDID_readain;
	long nRet = 0;

	nRet = (long)pEngineThread->RunProcedure(strProcedureID, NULL, TRUE);
	return nRet;
}

CDvmDataset* CPxiDevice::FindDvmDataset(const CString &strDataSetName)
{
    CString strTemp = strDataSetName;

    if (g_bLogEngineDebugInfor)
    {
        CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CPxiDevice::FindDataSet(%s)"), strTemp.GetString());
    }

    strTemp.MakeLower();
    CDvmDataset *pDataset = NULL;

    if (strTemp == _T("none"))
    {
        return NULL;
    }

    if (strTemp == dsID_MmsDvmAttr)
    {
        pDataset = m_pACSI_NODE->GetDeviceAttrs();
        return pDataset;
    }

    if (strTemp.Find(g_strReportLogicDeviceID) >= 0)
    {
        pDataset = GetReportDataset(strTemp);

        if (pDataset == NULL)
        {
            CLogPrint::LogFormatString(XLOGLEVEL_TRACE
                     , g_sLangTxt_RptPathUnExist.GetString()/*_T("报告路径“%s”不存在")*/
                     , strTemp.GetString());
            return NULL;
        }

        return pDataset;
    }

    strTemp = strDataSetName;
    pDataset = (CDvmDataset*)m_pACSI_NODE->SelectData(strTemp);

    if (pDataset == NULL)
    {
		pDataset = m_pACSI_NODE->FindDataset(strTemp);

		if (pDataset == NULL)
		{
			return NULL;
		}
    }

    if (pDataset->GetClassID() != DVMCLASSID_CDVMDATASET)
    {
        return NULL;
    }

    return pDataset;
}
