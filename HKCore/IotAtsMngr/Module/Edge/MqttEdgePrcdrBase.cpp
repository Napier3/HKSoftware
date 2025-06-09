#include "stdafx.h"
#include "MqttEdgePrcdrBase.h"
#include "EdgeCmd\EdgeGlobalDef.h"
#include "IotEdgeProtoServerBase.h"
#include "EdgeEngineProtoSvrBaseApp.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

CMqttEdgePrcdrBase::CMqttEdgePrcdrBase()
{

}

CMqttEdgePrcdrBase::~CMqttEdgePrcdrBase()
{

}

//循环执行，判断超时或发送报文，过程结束返回TRUE
BOOL CMqttEdgePrcdrBase::Run()
{
	return FALSE;
}

//若是应答，处理应答，返回TRUE,否则返回FALSE
BOOL CMqttEdgePrcdrBase::ProcessPackageDetail(CPxPkgBase *pPkgDetail)
{
	CMqttEdgePkgBase *pEdgePkg = (CMqttEdgePkgBase *)pPkgDetail;

	//判断该报文是否是期待应答【根据procedureID】


	//收到应答，关闭当前节点的定时器
	KillTimer();
	pPkgDetail->SetPkgState(PX_PKG_STATE_PROCESSED_MATCH);

	//处理应答逻辑
	ProcessPackageAck(pPkgDetail);

	return TRUE;
}

BOOL CMqttEdgePrcdrBase::ProcessPackageFinished(CPxPkgBase *pPkgDetail)
{
	pPkgDetail->SetPkgState(PX_PKG_STATE_CAN_DELETE);
	SetProcedureState(PrcdrState_Step_End);
	SetResultEvent(RUNPROCEDURE_EVENT_CommFinish);
	return TRUE;
}

BOOL CMqttEdgePrcdrBase::CreateRunProcedureObject(const CString& strProcedureID, CEdgeCmd* pEdgeCmd)
{
	//yzj mid需要从xml获取
	CString strTime;
	GetCurrSystemtimeString(strTime);
	pEdgeCmd->SetProcedureID(strProcedureID);
	pEdgeCmd->m_strID = m_strDeviceID;//报文主题的ID
	pEdgeCmd->m_nMid = 10000;
	pEdgeCmd->m_strType = edge_GetCmdInfoType(strProcedureID);
	pEdgeCmd->m_strDeviceId = m_strDeviceID;//报文内部的ID
	pEdgeCmd->m_strTimestamp = strTime;
	pEdgeCmd->m_nExpire = -1;
	return TRUE;
}

CEdgeParas* CMqttEdgePrcdrBase::InitProcedure_Server(BOOL bIsWrite)
{
	POS pos = m_pRefDataset->GetHeadPosition();
	CEdgeParas* pParas = new CEdgeParas;
	while (pos)
	{
		CDvmData* pChild = (CDvmData*)m_pRefDataset->GetNext(pos);
		if(pChild->m_strDataType != _T("STRUCT"))
		{
			//当service命令是读命令或者是有值的写命令时,生成该标签
			if((bIsWrite && pChild->m_strValue.GetLength())
				|| (!bIsWrite))
			{
				pParas->AddNewData(pChild->m_strName, pChild->m_strID,
					pChild->m_strDataType, pChild->m_strValue);
			}
		}
	}
	return pParas;
}

void CMqttEdgePrcdrBase::InitProcedure(CExBaseList* pDatas, CDvmDataset* pDataset, CEdgeProtoDevice* pDevice)
{
	//填充需要发送json的内容,设置发送时需要绑定的接口
	//其中m_pPxCmmOptrInterface是protected的,需要改变为public或增加获取函数
	//正常测试流程中是在RunProcedure中链接,那个时刻是不需要外部获取的,但在这里需要外部获取
	CPxPrcdrBase::InitProcedure(pDevice->m_strID, _T(""), pDatas, pDataset, _T("own"));
	CIotEdgeProtoServerBase* pServerBase = (CIotEdgeProtoServerBase*)pDevice->m_pPxProtocol;
	SetPxProtocol(pServerBase);
	SetPxCmmOptrInterface(pServerBase->GetPxCmmOptrInterface());
}

void CMqttEdgePrcdrBase::AddTail(CEdgeProtoDevice* pDevice)
{
	CAutoSimpleLock oLock(&pDevice->m_pPxProtocol->m_oPrcdrTmpCriticSection);
	pDevice->m_pPxProtocol->m_listTempPrcdr.AddTail(this);
}

void CMqttEdgePrcdrBase::SetEdgeData(CString& strEdgeData, CDvmData* pDvmData)
{
	if(pDvmData)
	{
		strEdgeData = pDvmData->m_strValue;
	}
}

void CMqttEdgePrcdrBase::SetEdgeData(long& nEdgeData, CDvmData* pDvmData)
{
	if(pDvmData)
	{
		nEdgeData = CString_To_long(pDvmData->m_strValue);
	}
}

void CMqttEdgePrcdrBase::SetEdgeValue(CString& strEdgeValue, CDvmValue* pDvmValue)
{
	if(pDvmValue)
	{
		strEdgeValue = pDvmValue->m_strValue;
	}
}

void CMqttEdgePrcdrBase::SetEdgeValue(long& nEdgeValue, CDvmValue* pDvmValue)
{
	if(pDvmValue)
	{
		nEdgeValue = CString_To_long(pDvmValue->m_strValue);
	}
}

void CMqttEdgePrcdrBase::InitUpdateDataSetCmd(const CString& strIotEngineSN, CDvmDataset* pDataset)
{
	CSttSysState oSysState;
	oSysState.m_strID = STT_CMD_TYPE_IOT_UpdateDataset;
	oSysState.m_strRetSttCmd = STT_CMD_SYSSTATE_IOT;
	oSysState.SetEvent();
	oSysState.SetParasDataAttr(STT_CMD_PARA_DeviceSN, m_strID);
	oSysState.SetParasDataAttr(SYS_STATE_XEVENT_EVENTID, _T("UpdateDataset"));
	oSysState.m_strFromSN = strIotEngineSN;

	CSttParas *pParas = oSysState.GetSttParas();
	CDvmDataset *pResDataset = (CDvmDataset *)pDataset->Clone();
	pParas->AddNewChild(pResDataset);

	m_pPxCmmInterface->Send(&oSysState);
}

void CMqttEdgePrcdrBase::UpdateReport(CExBaseObject *pCmdBase, BOOL bIsState)
{
	CEdgeCmd* pCmd = (CEdgeCmd*)pCmdBase;
	char* strJson = NULL;
	long nLen = pCmd->GetXml(CEdgeCmdMngrXmlRWKeys::g_pXmlKeys, &strJson, 0, _JSON_TYPE_);

	//yzj 2021-12-8 GetXml函数里用的是CJSON_Print_UTF8,自动测试下发的中文会变乱码
	char* strGBK = NULL;
	long nLenGBK = 0;
	charUtf8_to_charGBK(strJson, nLen, &strGBK, nLenGBK);
	CString strData = strGBK;
	strData = strData.Mid(0, strData.ReverseFind('}') + 1);
	delete strJson;
	delete strGBK;

	CString strTopic = _T("");
	strTopic.Format(_T("/v1/%s/%s/%s"), pCmd->m_strID, 
		edge_GetCmdTypeID(pCmd->GetProcedureID()), edge_GetServerToEdgeCmdID(pCmd->GetProcedureID()));

	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);
	CDvmData* pLibData = (CDvmData*)pDevice->m_listLib.FindByID(m_strID);
	if(pLibData)
	{
		//数据集上报报文使能
		CDvmLogicDevice* pLDevice = (CDvmLogicDevice*)pDevice->m_oDvmDevice.FindByID(EDGE_LDEV_ID_report);
		CDvmDatasetGroup* pReportData = (CDvmDatasetGroup*)pLDevice->FindByID(EDGE_DATASET_ID_jsonpackage);
		if(bIsState)
		{
			CDvmDatasetGroup* pReportState = (CDvmDatasetGroup*)pReportData->FindByID(EDGE_PROCEDURE_VAR_sendstate);	
			//相同过程中的过程查询命令只存一次
			if(((CDvmData*)pReportState->FindByID(EDGE_PROCEDURE_VAR_sendstate_topic))->m_strValue != strTopic)
			{
				((CDvmData*)pReportState->FindByID(EDGE_PROCEDURE_VAR_sendstate_topic))->m_strValue = strTopic;
				fwrite(const_cast<char*>(strTopic.GetString()), strTopic.GetLength(), 1, pDevice->m_pReportFile);
				((CDvmData*)pReportState->FindByID(EDGE_PROCEDURE_VAR_sendstate_message))->m_strValue = strData;
				fwrite(const_cast<char*>(strData.GetString()), strData.GetLength(), 1, pDevice->m_pReportFile);
				InitUpdateDataSetCmd(pDevice->m_strIotEngineSN, pReportData);
			}	
		}
		else
		{
			CDvmDatasetGroup* pReportSend = (CDvmDatasetGroup*)pReportData->FindByID(EDGE_PROCEDURE_VAR_sendmsg);	
			((CDvmData*)pReportSend->FindByID(EDGE_PROCEDURE_VAR_sendmsg_topic))->m_strValue = strTopic;
			fwrite(const_cast<char*>(strTopic.GetString()), strTopic.GetLength(), 1, pDevice->m_pReportFile);
			((CDvmData*)pReportSend->FindByID(EDGE_PROCEDURE_VAR_sendmsg_message))->m_strValue = strData;
			fwrite(const_cast<char*>(strData.GetString()), strData.GetLength(), 1, pDevice->m_pReportFile);
			InitUpdateDataSetCmd(pDevice->m_strIotEngineSN, pReportData);
		}
	}
}

void CMqttEdgePrcdrBase::UpdateReport_Topo(CExBaseObject *pCmdBase)
{
	CEdgeCmd* pCmd = (CEdgeCmd*)pCmdBase;
	char* strJson = NULL;
	long nLen = pCmd->GetXml(CEdgeCmdMngrXmlRWKeys::g_pXmlKeys, &strJson, 0, _JSON_TYPE_);
	CString strTopic = _T("");
	strTopic.Format(_T("/v1/%s/%s/%s"), pCmd->m_strID, 
		edge_GetCmdTypeID(pCmd->GetProcedureID()), edge_GetServerToEdgeCmdID(pCmd->GetProcedureID()));

	CJSON* pJson = NULL;
	if(pCmd->GetEdgeParam())
	{
		pJson = CJSON_Parse(strJson);
		CJSON* pParamJson = CJSON_GetObjectItem(pJson, _T("param"));
		//递归复制一份同样的data,否则在delete json时会释放EdgeCmd中的json指针,导致发送报文时出错
		CJSON* pCopyJson = CJSON_Duplicate(pCmd->GetEdgeParam()->GetDeviceDataJson(), TRUE);
		CJSON_AddItemToObject(pParamJson, EDGE_PROCEDURE_VAR_data, pCopyJson);
		strJson = CJSON_Print(pJson);
	}

	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);
	if(pDevice)
	{
		CDvmLogicDevice* pLDevice = (CDvmLogicDevice*)pDevice->m_oDvmDevice.FindByID(EDGE_LDEV_ID_DeviceData);
		CDvmDatasetGroup* pReportData = (CDvmDatasetGroup*)pLDevice->FindByID(EDGE_DATASET_ID_TOPO_Admin);
		if(pCmd->GetProcedureID() == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_ADD)
		{
			CDvmDatasetGroup* pReportState = (CDvmDatasetGroup*)pReportData->FindByID(EDGE_PROCEDURE_VAR_TopoAddResponse);	
			((CDvmData*)pReportState->FindByID(EDGE_PROCEDURE_VAR_TopoAddResponseTopic))->m_strValue = strTopic;
			((CDvmData*)pReportState->FindByID(EDGE_PROCEDURE_VAR_TopoAddResponseMsg))->m_strValue = strJson;
		}
		else if(pCmd->GetProcedureID() == EDGE_PROCEDURE_ID_TOPO_CMD_TOPO_DEL)
		{
			CDvmDatasetGroup* pReportState = (CDvmDatasetGroup*)pReportData->FindByID(EDGE_PROCEDURE_VAR_TopoDelResponse);	
			((CDvmData*)pReportState->FindByID(EDGE_PROCEDURE_VAR_TopoDelResponseTopic))->m_strValue = strTopic;
			((CDvmData*)pReportState->FindByID(EDGE_PROCEDURE_VAR_TopoDelResponseMsg))->m_strValue = strJson;
		}
		else
		{
			CDvmDatasetGroup* pReportState = (CDvmDatasetGroup*)pReportData->FindByID(EDGE_PROCEDURE_VAR_TopoUpdateResponse);	
			((CDvmData*)pReportState->FindByID(EDGE_PROCEDURE_VAR_TopoUpdateResponseTopic))->m_strValue = strTopic;
			((CDvmData*)pReportState->FindByID(EDGE_PROCEDURE_VAR_TopoUpdateResponseMsg))->m_strValue = strJson;
		}
		
		InitUpdateDataSetCmd(pDevice->m_strIotEngineSN, pReportData);
	}

	CJSON_Delete(pJson);
	delete strJson;
}

CEdgeParaData* CMqttEdgePrcdrBase::AddEdgeData(CEdgeParaDatas* pPara ,CDvmDataset* pDataset, CString strVarName, CString strVarType)
{
	if(!pDataset)
	{
		return NULL;
	}

	CEdgeParaData* pEdgePara = NULL;
	CDvmData* pData = (CDvmData*)pDataset->FindByID(strVarName);
	if(pData && pData->m_strValue.GetLength())
	{
		//针对自动测试传number全部为浮点数的问题加以限制
		if(pData->m_strDataType == _T("number") && pData->m_strValue.Find('.') != -1)
		{
			double dTemp = CString_To_double(pData->m_strValue);
			dTemp = dTemp - int(dTemp);
			if (dTemp - 0 <= 0.00001 || 0 - dTemp <= 0.00001)
			{
				pData->m_strValue = pData->m_strValue.Mid(0, pData->m_strValue.Find('.'));
			}
		}
		pEdgePara = pPara->AddNewData(pData->m_strName, pData->m_strID, strVarType, pData->m_strValue);
	}
	return pEdgePara;
}

void CMqttEdgePrcdrBase::GetEdgeJson(CExBaseList* pData, CJSON* pJson)
{
	POS pos = pData->GetHeadPosition();
	while (pos)
	{
		CDvmValue* pValue = (CDvmValue*)pData->GetNext(pos);
		if(pValue && pValue->m_strValue.GetLength())
			CJSON_AddItemToArray(pJson, CJSON_CreateString(pValue->m_strValue));
	}
}

CEdgeFile* CMqttEdgePrcdrBase::AddEdgeFile(CDvmData* pData)
{
	if(!pData ||   pData->IsEmpty())
	{
		return NULL;
	}

	CEdgeFile* pFile = new CEdgeFile;
	CDvmData* pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_name);
	SetEdgeData(pFile->m_strName, pDvmData);
	pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_url);
	SetEdgeData(pFile->m_strUrl, pDvmData);
	pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_md5);
	SetEdgeData(pFile->m_strMd5, pDvmData);
	pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_size);
	SetEdgeData(pFile->m_nSize, pDvmData);
	pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_fileType);
	SetEdgeData(pFile->m_strFileType, pDvmData);

	pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_sign);
	pFile->SetEdgeSign(AddEdgeSign(pDvmData));

	return pFile;
}

CEdgeSign* CMqttEdgePrcdrBase::AddEdgeSign(CDvmData* pData)
{
	if(!pData ||   pData->IsEmpty())
	{
		return NULL;
	}

	CEdgeSign* pSign = new CEdgeSign;
	CDvmValue* pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_name); 
	SetEdgeValue(pSign->m_strName, pValue);
	pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_url);
	SetEdgeValue(pSign->m_strUrl, pValue);
	pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_md5);
	SetEdgeValue(pSign->m_strMd5, pValue);
	pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_size);
	SetEdgeValue(pSign->m_nSize, pValue);
	return pSign;
}

CEdgeImage* CMqttEdgePrcdrBase::AddEdgeImage(CDvmData* pData)
{
	if(!pData ||   pData->IsEmpty())
	{
		return NULL;
	}

	CEdgeImage* pImage = new CEdgeImage;
	CDvmData* pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_name);
	SetEdgeData(pImage->m_strName, pDvmData);
	pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_url);
	SetEdgeData(pImage->m_strUrl, pDvmData);
	pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_md5);
	SetEdgeData(pImage->m_strMd5, pDvmData);
	pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_size);
	SetEdgeData(pImage->m_nSize, pDvmData);

	pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_sign);
	pImage->SetEdgeSign(AddEdgeSign(pDvmData));

	return pImage;
}

CEdgeTemperature* CMqttEdgePrcdrBase::AddEdgeTemperature(CDvmData* pData)
{
	if(!pData ||   pData->IsEmpty())
	{
		return NULL;
	}

	CEdgeTemperature* pTemperature = new CEdgeTemperature;
	CString strTemLow, strTemHigh;
	CDvmValue* pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_temLow);
	SetEdgeValue(strTemLow, pValue);
	pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_temHigh);
	SetEdgeValue(strTemHigh, pValue);
	pTemperature->InitTemperature(CString_To_long(strTemLow), CString_To_long(strTemHigh));
	return pTemperature;
}

CEdgeRepPeriod* CMqttEdgePrcdrBase::AddEdgeRepPeriod(CDvmData* pData)
{
	if(!pData ||  pData->IsEmpty())
	{
		return NULL;
	}

	CEdgeRepPeriod* pRepPeriod = new CEdgeRepPeriod;
	CDvmValue* pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_devPeriod);
	pRepPeriod->m_nDevPeriod = CString_To_long(pValue->m_strValue);
	pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_conPeriod);
	pRepPeriod->m_nConPeriod = CString_To_long(pValue->m_strValue);
	pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_appPeriod);
	pRepPeriod->m_nAppPeriod = CString_To_long(pValue->m_strValue);
	pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_heartPeriod);
	pRepPeriod->m_nHeartPeriod = CString_To_long(pValue->m_strValue);
	return pRepPeriod;
}

CEdgeCfgCpu* CMqttEdgePrcdrBase::AddEdgeCfgCpu(CDvmData* pData)
{
	if(!pData ||   pData->IsEmpty())
	{
		return NULL;
	}

 	CEdgeCfgCpu* pCfgCpu = new CEdgeCfgCpu;
 	CDvmValue* pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_cpus);
 	pCfgCpu->m_nCpus = CString_To_long(pValue->m_strValue);
 	pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_cpuLmt);
 	pCfgCpu->m_nCpuLmt = CString_To_long(pValue->m_strValue);
	return pCfgCpu;
}

CEdgeCfgMem* CMqttEdgePrcdrBase::AddEdgeCfgMem(CDvmData* pData)
{
	if(!pData ||   pData->IsEmpty())
	{
		return NULL;
	}

 	CEdgeCfgMem* pCfgMem = new CEdgeCfgMem;
 	CDvmValue* pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_memory);
 	pCfgMem->m_nMemory = CString_To_long(pValue->m_strValue);
 	pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_memLmt);
 	pCfgMem->m_nMemLmt = CString_To_long(pValue->m_strValue);
	return pCfgMem;
}

CEdgeCfgDisk* CMqttEdgePrcdrBase::AddEdgeCfgDisk(CDvmData* pData)
{
	if(!pData ||   pData->IsEmpty())
	{
		return NULL;
	}

 	CEdgeCfgDisk* pCfgDisk = new CEdgeCfgDisk;
 	CDvmValue* pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_disk);
 	pCfgDisk->m_nDisk = CString_To_long(pValue->m_strValue);
 	pValue = (CDvmValue*)pData->FindByID(EDGE_PROCEDURE_VAR_diskLmt);
 	pCfgDisk->m_nDiskLmt = CString_To_long(pValue->m_strValue);
	return pCfgDisk;
}

CEdgeWithApp* CMqttEdgePrcdrBase::AddEdgeWithApp(CDvmData* pData)
{
	if(!pData ||   pData->IsEmpty())
	{
		return NULL;
	}

	CEdgeWithApp* pWithApp = new CEdgeWithApp;
	CDvmData* pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_version);

	if(!pDvmData->m_strValue.GetLength())
	{
		delete pWithApp;
		return 0;
	}

	SetEdgeData(pWithApp->m_strVersion, pDvmData);
	pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_enable);
	SetEdgeData(pWithApp->m_strEnable, pDvmData);
	
	pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_file);
	pWithApp->SetEdgeFile(AddEdgeFile(pDvmData));
	pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_cfgCpu);
	pWithApp->SetEdgeCfgCpu(AddEdgeCfgCpu(pDvmData));
	pDvmData = (CDvmData*)pData->FindByID(EDGE_PROCEDURE_VAR_cfgMem);
	pWithApp->SetEdgeCfgMem(AddEdgeCfgMem(pDvmData));
	
	return pWithApp;
}




// void CMqttEdgePrcdrBase::RunProcedure(CString strProcedure)
//{
// 	CDvmValue* pValue = (CDvmValue*)::SendMessage(AfxGetApp()->GetMainWnd()->m_hWnd, WM_ON_EDGE_DATASET_VALUE_GET, 0 ,0);
// 	pProcedure->m_strID = strProcedure;
// 	pProcedure->OnRunProcedure_Service(strProcedure, pValue);
//}

//void  CMqttEdgePrcdrBase::RunProcedure(CString strProcedure, CExBaseList* pData /*= NULL*/, CDvmValue* pValue /*= NULL*/)
//{
// 	m_strID = strProcedure;
// 	if(edge_GetCmdTypeID(strProcedure) == EDGE_CMD_STR_TYPE_ID_service)
// 	{	
// 		OnRunProcedure_Service(strProcedure, pData, pValue);
// 	}
// 	else if (edge_GetCmdTypeID(strProcedure) == EDGE_CMD_STR_TYPE_ID_device)
// 	{
// 		OnRunProcedure_Device(strProcedure);
// 	}
// 	else if (edge_GetCmdTypeID(strProcedure) == EDGE_CMD_STR_TYPE_ID_container)
// 	{
// 		OnRunProcedure_Container(strProcedure);
// 	}
// 	else if (edge_GetCmdTypeID(strProcedure) == EDGE_CMD_STR_TYPE_ID_app)
// 	{
// 		OnRunProcedure_App(strProcedure);
// 	}
//}