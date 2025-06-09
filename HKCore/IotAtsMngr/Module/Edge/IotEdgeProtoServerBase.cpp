#include "stdafx.h"
#include "IotEdgeProtoServerBase.h"
#include "MqttEdgePkgBase.h"
#include "../../../SttStudio/Module/SttGlobalDef.h"

#include "MqttEdgePrcdrRead.h"
#include "MqttEdgePrcdrWrite.h"
#include "EdgeCmd/EdgeGlobalDef.h"
#include "../IotEngineGlobalDef.h"
#include "EdgeCmd/EdgeContPara.h"
#include "EdgeEngineProtoSvrBaseApp.h"
#include "IotEngineToEdgeV5.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CIotEdgeProtoServerBase::CIotEdgeProtoServerBase()
{

}

CIotEdgeProtoServerBase::~CIotEdgeProtoServerBase()
{
	//yzj 2021-10-19 m_pDvmDevice指向的堆栈是其他地方创建的,析构不能在这里
	//yzj 2021-10-22 关闭自动测试页面导致的析构是closedevice但不应该析构pDevice
	//因为没有linkdown
	if(!g_pEdgeEngineProtoSvrBaseApp->m_bViewMode)
	{
	g_pEdgeEngineProtoSvrBaseApp->CloseDevice(m_strDeviceID);
	}
	m_pDvmDevice = NULL;
}

long CIotEdgeProtoServerBase::RunProcedure(const CString &strProcedureID,CExBaseList *pListDatas
										  ,CDvmDataset *pDataset,const CString &strRecordMode)
{
	if(m_pProtoEventInterface == NULL)
	{
		return 0;
	}

// 	if (strProcedureID == PROCEDURE_ID_WriteMmsAttr)
// 	{//更新全局数据集
// 		CDvmDataset* pAttrs = m_pDvmDevice->GetDeviceAttrs();
// 		pAttrs->UpdateDataValue(pDataset);
// 
// 		m_pProtoEventInterface->OnPrcdrFinishedEx(RUNPROCEDURE_EVENT_CommFinish,pDataset);
// 		return 1;
// 	}

	//设置要测试的端设备ID
	if(strProcedureID == EDGE_PROCEDURE_ID_DEV_SET_TOPO_ID)
	{
		SetCurrentTopoID(pListDatas);
		return 1;
	}

	//设置要启用或禁用报文记录功能的Procedure
	if (strProcedureID == EDGE_PROCEDURE_ID_DEV_SET_ENABLE
		|| strProcedureID == EDGE_PROCEDURE_ID_DEV_SET_DISABLE)
	{
		SetEnableReport(pListDatas, strProcedureID);
		return 1;
	}

	//根据过程ID创建不同的过程对象，添加到过程链表中
	CPxPrcdrBase *pProcedure = CreateProcedure(strProcedureID);
	if (pProcedure == NULL)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("CreateProcedure [%s] failed!"), strProcedureID);
		return 0;
	}

	//更新数据集
	CDvmDataset *pDstDataset = CPxProtocolBase::UpdateDataset(pDataset);

	//初始化过程: 2021-8-22 lijunqing  对于边设备来说，过程都是针对设备本身，所以不需要传入DeviceID
	//2021-9-10 yzj 判断报文是否属于某设备时报文PxProtocol中需要一个DeviceID
	pProcedure->InitProcedure(m_strDeviceID, strProcedureID, pListDatas, pDstDataset, strRecordMode);
	pProcedure->SetPxProtocol(this);
	pProcedure->SetPxCmmOptrInterface(m_pPxCmmOptrInterface);

	//添加到协议服务过程链表m_listTempPrcdr中
	CAutoSimpleLock oLock(&m_oPrcdrTmpCriticSection);
	m_listTempPrcdr.AddTail(pProcedure);

	return 1;
}

long CIotEdgeProtoServerBase::PkgPrase(char *pBuf,long nLen,CDvmDataset &oRetDataset)
{
	return 0;
}

long CIotEdgeProtoServerBase::PkgProduce(const CString &strProduceID,CDvmDataset &oDataset,char **ppBuf,long &nLen)
{
	return 0;
}

long CIotEdgeProtoServerBase::GetDataset(const CString &strDatasetPath,CDvmDataset &oRetDataset)
{
	CString strDsID = GetIDFromPath(strDatasetPath,'$');

	oRetDataset.DeleteAll();

	CDvmDataset *pSrcDataset = m_pDvmDevice->FindDataset(strDsID);
	if (pSrcDataset != NULL)
	{
		pSrcDataset->Copy(&oRetDataset);
	}

	oRetDataset.m_strID = strDatasetPath;

	return 1;
}

long CIotEdgeProtoServerBase::ConfigDevice(const CString &strConfig)
{
	return 0;
}

long CIotEdgeProtoServerBase::CloseDevice()
{
	//将转换接口模块指针清0
	m_pProtoEventInterface = NULL;

	//退出线程，也可以不加，在析构中退出线程
	ExitEngineThread();

	return 0;
}

void CIotEdgeProtoServerBase::InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
				  ,const CString &strCmmCfgFile,CDataGroup *pCfgGroup)
{
	CPxProtoDeviceBase* pDevice = (CPxProtoDeviceBase*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(strDeviceID);
	m_pDvmDevice = &pDevice->m_oDvmDevice;
	CPxProtocolBase::InitProtocol(strDeviceID,strDvmFile,strPpxmlFile,strCmmCfgFile,pCfgGroup);
}

BOOL CIotEdgeProtoServerBase::Init(const char *pszIP,long nPort)
{
	return FALSE;
}

/************************
测试仪主题：
/v1/${edgeId}/service/reply
约定：同一个装置在同一个时间点，相同过程最多只有一个
**************************/
long CIotEdgeProtoServerBase::OnTestMsg(CSttCmmOptrInterface *pCmmOptrInterface, const CString &strFromSN, char *pBuf, long nLen,long nCmdType, char *pszCmdID, char *pszRetType)
{
	//根据CmdType,CmdID创建具体的EdgePkg对象
	//根据命令信息定位数据集，更新数据集(如果需要)【根据命令在程序中默认约定好，什么命令对应什么数据集】
	//将报文添加到规约对象链表中
	CEdgeCmd* pEdgePkg = new CEdgeCmd;
	CString strGbkBuf = Utf8ToGBK(pBuf);
	strGbkBuf = strGbkBuf.Mid(0, strGbkBuf.ReverseFind('}') + 1);
	BufToCmd(pEdgePkg, const_cast<char*>(strGbkBuf.GetString()), nLen, EDGE_DATA_FORMAT_JSON);

	//根据需求存json报文至文件
	

	pEdgePkg->m_nCmdType = nCmdType;
	pEdgePkg->m_strCmdID = pszCmdID;
	
	//确定paras业务报文的参数类型
	CString strCmdParasID;
	CEdgeParam* pParam = (CEdgeParam*)pEdgePkg->GetEdgeParam();
	if(pParam)
	{
		CEdgeParaData* pParasType = (CEdgeParaData*)pParam->FindByID(EDGE_PROCEDURE_VAR_cmd);
		if(pParasType)
		{
			strCmdParasID = pParasType->m_strValue;
		}
	}

	CDvmDataset* pDataset = NULL;
	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);

	CString strProcedureID;
	if(nCmdType == EDGE_CMD_TYPE_IDX_device)
	{
		strProcedureID = edge_GetProcedureID(EDGE_CMD_STR_TYPE_ID_device, pEdgePkg->m_strType);
		if(pEdgePkg->m_strType == EDGE_CMD_INFO_Type_DEV_CMD_STATUS_QUERY
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_DEV_REP_JOB_RESULT
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_DEV_REP_SYS_STATUS
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_DEV_CMD_SYS_STATUS
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_DEV_CMD_INFO_QUERY
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_DEV_CMD_SYS_LOG)
		{	
			//设备状态、信息等报文
			pDataset = UpdateDataset(pEdgePkg->GetEdgeParam(), strProcedureID);
		}
		else if(pEdgePkg->m_strType == EDGE_CMD_INFO_Type_DEV_EVENT_SYS_ALARM)
		{
			//设备自动上报报文
			pDataset = UpdateDataset_Event(pEdgePkg->GetEdgeParam(), strProcedureID);
		}
 		else if(pEdgePkg->m_strType == EDGE_CMD_INFO_Type_DEV_EVENT_HEARTBEAT)
 		{
 			//心跳报文
 			CMqttEdgePrcdrWrite* pWrite = new CMqttEdgePrcdrWrite;
 			pWrite->m_strDeviceID = strFromSN;
 			pWrite->SetPxCmmOptrInterface(m_pPxCmmOptrInterface);
 			pWrite->OnRunProcedure_Device(strProcedureID, (CEdgeCmd*)pEdgePkg);
 			return 0;
 		}
	}
	else if (nCmdType == EDGE_CMD_TYPE_IDX_topo)
	{
		strProcedureID = edge_GetProcedureID(EDGE_CMD_STR_TYPE_ID_topo, pEdgePkg->m_strType);
		//topo端设备是接收到上报后发送报文给边设备
		CMqttEdgePrcdrWrite* pWrite = new CMqttEdgePrcdrWrite;
		pWrite->m_strDeviceID = strFromSN;
		pWrite->SetPxCmmOptrInterface(m_pPxCmmOptrInterface);
		pWrite->OnRunProcedure_Device(strProcedureID, (CEdgeCmd*)pEdgePkg);
		pDataset = UpdateDataset(pEdgePkg->GetEdgeParam(), strProcedureID);
		InitUpdateDatasetCmd(pDevice->m_strIotEngineSN, pDataset);
	}
	else if(nCmdType == EDGE_CMD_TYPE_IDX_container)
	{
		strProcedureID = edge_GetProcedureID(EDGE_CMD_STR_TYPE_ID_container, pEdgePkg->m_strType);
		if(pEdgePkg->m_strType == EDGE_CMD_INFO_Type_CON_CMD_STATUS_QUERY
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_CON_REP_JOB_RESULT
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_CON_CMD_CON_GET_CONFIG
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_CON_CMD_CON_STATUS
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_CON_REP_CON_STATUS
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_CON_CMD_STATUS_QUERY
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_CON_CMD_CON_LOG)
		{	
			//容器状态、信息等报文
			pDataset = UpdateDataset(pEdgePkg->GetEdgeParam(), strProcedureID);
		}
		else if(pEdgePkg->m_strType == EDGE_CMD_INFO_Type_CON_EVENT_CON_ALARM)
		{
			//容器自动上报报文
			pDataset = UpdateDataset_Event(pEdgePkg->GetEdgeParam(), strProcedureID);
		}
	}
	else if(nCmdType == EDGE_CMD_TYPE_IDX_app)
	{
		strProcedureID = edge_GetProcedureID(EDGE_CMD_STR_TYPE_ID_app, pEdgePkg->m_strType);
		if(pEdgePkg->m_strType == EDGE_CMD_INFO_Type_APP_CMD_STATUS_QUERY
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_APP_REP_JOB_RESULT
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_APP_CMD_APP_GET_CONFIG
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_APP_CMD_APP_STATUS
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_APP_REP_APP_STATUS
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_APP_CMD_STATUS_QUERY
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_APP_CMD_APP_LOG)
		{	
			//应用状态、信息等报文		
			pDataset = UpdateDataset(pEdgePkg->GetEdgeParam(), strProcedureID);
		}
		else if(pEdgePkg->m_strType == EDGE_CMD_INFO_Type_APP_EVENT_APP_ALARM)
		{
			//应用自动上报报文
			pDataset = UpdateDataset_Event(pEdgePkg->GetEdgeParam(), strProcedureID);
		}
	}
	else if(nCmdType == EDGE_CMD_TYPE_IDX_service)
	{
		strProcedureID = edge_GetProcedureID(EDGE_CMD_STR_TYPE_ID_service, pEdgePkg->m_strType);
		//业务类全部都是特殊处理
		if(!strcmp(pszCmdID, EDGE_CMD_ID_reply))
		{
			CEdgeParaData* pData = (CEdgeParaData*)pParam->FindByID(EDGE_PROCEDURE_VAR_cmd);

			if(!pData)
			{
				CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_cmd == NULL"));
				return 0;
			}

			if(pData->m_strValue == EDGE_PROCEDURE_ID_parameter_Get
				|| pData->m_strValue == EDGE_PROCEDURE_ID_parameter_Set
				|| pData->m_strValue == EDGE_PROCEDURE_ID_parameter_Activate
				|| pData->m_strValue == EDGE_PROCEDURE_ID_parameter_Cancel
				|| pData->m_strValue == EDGE_PROCEDURE_ID_discrete_Get
				|| pData->m_strValue == EDGE_PROCEDURE_ID_analog_Get
				|| pData->m_strValue == EDGE_PROCEDURE_ID_accumulator_Get
				|| pData->m_strValue == EDGE_PROCEDURE_ID_timeRead
				|| pData->m_strValue == EDGE_PROCEDURE_ID_timeCheck
				|| pData->m_strValue == EDGE_PROCEDURE_ID_commad_HZ
				|| pData->m_strValue == EDGE_PROCEDURE_ID_commad_TZ
				|| pData->m_strValue == EDGE_PROCEDURE_ID_commad_ModelCtrl
				|| pData->m_strValue == EDGE_PROCEDURE_ID_APPDir_Get
				|| pData->m_strValue == EDGE_PROCEDURE_ID_APPHFile_Get
				|| pData->m_strValue == EDGE_PROCEDURE_ID_APP_CONFIG_Dir_Get
				|| pData->m_strValue == EDGE_CMD_INFO_Type_SVR_REP_DATA
				|| pData->m_strValue == EDGE_CMD_INFO_Type_SVR_EVENT_DATA
				|| pData->m_strValue == EDGE_CMD_INFO_Type_SVR_DATA_FILE
				|| pData->m_strValue == EDGE_PROCEDURE_ID_CMD_GET_APP_CONFIG
				|| pData->m_strValue == EDGE_PROCEDURE_ID_CMD_SET_APP_CONFIG)
			{
				strProcedureID = edge_GetProcedureID(EDGE_CMD_STR_TYPE_ID_service, pEdgePkg->m_strType, pData->m_strValue);
				CEdgeParas* pParas = (CEdgeParas*)pParam->GetEdgeParas();
				pDataset = UpdateDataset_Service_Cmd_Service(pParas, strProcedureID);
			}
		}
		else if(pEdgePkg->m_strType == EDGE_CMD_INFO_Type_SVR_EVENT_DATA
			|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_SVR_REP_DATA)
		{
			//业务事件报文
			pDataset = UpdateDataset_Service_Event(pEdgePkg->GetEdgeParam(), strProcedureID, pEdgePkg->m_strDeviceId);
		}
		else if(pEdgePkg->m_strType == EDGE_CMD_INFO_Type_SVR_DATA_FILE)
		{
			
			pDataset = UpdateDataset(pEdgePkg->GetEdgeParam(), strProcedureID);
		}
	}

  	CDvmDataset* pConnectData = NULL;
	if(pDevice)
	{
		//通信结果更新 code:200 等
		CDvmLogicDevice* pLDevice = (CDvmLogicDevice*)pDevice->m_oDvmDevice.FindByID(EDGE_LDEV_ID_ConnectData);
		pConnectData = (CDvmDataset*)pLDevice->FindByID(EDGE_DATASET_ID_ConnectRes);

		if(!pConnectData)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_DATASET_ID_ConnectRes == NULL"));
			return 0;
		}

		CString strCode;
		strCode.Format(_T("%d"), ((CEdgeCmd*)pEdgePkg)->m_nCode);
		((CDvmData*)pConnectData->FindByID(EDGE_PROCEDURE_VAR_code))->m_strValue = strCode;
		((CDvmData*)pConnectData->FindByID(EDGE_PROCEDURE_VAR_msg))->m_strValue = ((CEdgeCmd*)pEdgePkg)->m_strMsg;

		pLDevice = (CDvmLogicDevice*)pDevice->m_oDvmDevice.FindByID(EDGE_LDEV_ID_report);
		CDvmDataset* pReportData = (CDvmDataset*)pLDevice->FindByID(EDGE_DATASET_ID_jsonpackage);
		if(!pReportData)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_DATASET_ID_jsonpackage == NULL"));
			return 0;
		}

		CDvmData* pLibData = (CDvmData*)pDevice->m_listLib.FindByID(strProcedureID);
		if(pLibData)
		{
			//将可能出现的错误信息存入更新的数据集中
			ParseErrorInfo(pEdgePkg);

			//报文内容上报被使能的Procedure进行topic和data的上报
			CString strTopic;
			strTopic.Format(_T("/v1/%s/%s/%s"), m_strDeviceID, 	edge_CmdTypeID_Idx_To_Str(nCmdType), edge_GetEdgeToServerCmdID(strProcedureID));
			CDvmDatasetGroup* pReportRecv = NULL;
			if(strProcedureID == EDGE_PROCEDURE_ID_DEV_CMD_STATUS_QUERY
				|| strProcedureID == EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY
				|| strProcedureID == EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY)
			{
				pReportRecv = (CDvmDatasetGroup*)pReportData->FindByID(EDGE_PROCEDURE_VAR_recvstate);
				if(!pReportRecv)
				{
					CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_recvstate == NULL"));
					return 0;
				}

				//相同过程中的过程查询命令的结果只存一次
				if(((CDvmData*)pReportRecv->FindByID(EDGE_PROCEDURE_VAR_recvstate_topic))->m_strValue != strTopic)
				{
					((CDvmData*)pReportRecv->FindByID(EDGE_PROCEDURE_VAR_recvstate_topic))->m_strValue = strTopic;
					((CDvmData*)pReportRecv->FindByID(EDGE_PROCEDURE_VAR_recvstate_message))->m_strValue = strGbkBuf;
					((CDvmData*)pReportRecv->FindByID(EDGE_PROCEDURE_VAR_recvstate_msg))->m_strValue = pEdgePkg->m_strMsg;
					((CDvmData*)pReportRecv->FindByID(EDGE_PROCEDURE_VAR_recvstate_code))->m_strValue.Format(_T("%d"), pEdgePkg->m_nCode);
					InitUpdateDatasetCmd(pDevice->m_strIotEngineSN, pReportData);
				}		
			}
			else if(nCmdType != EDGE_CMD_TYPE_IDX_service)
			{
				pReportRecv = (CDvmDatasetGroup*)pReportData->FindByID(EDGE_PROCEDURE_VAR_recvmsg);
				if(!pReportRecv)
				{
					CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_recvmsg == NULL"));
					return 0;
				}

				((CDvmData*)pReportRecv->FindByID(EDGE_PROCEDURE_VAR_recvmsg_topic))->m_strValue = strTopic;
				((CDvmData*)pReportRecv->FindByID(EDGE_PROCEDURE_VAR_recvmsg_message))->m_strValue = strGbkBuf;
				((CDvmData*)pReportRecv->FindByID(EDGE_PROCEDURE_VAR_recvmsg_msg))->m_strValue = pEdgePkg->m_strMsg;
				((CDvmData*)pReportRecv->FindByID(EDGE_PROCEDURE_VAR_recvmsg_code))->m_strValue.Format(_T("%d"), pEdgePkg->m_nCode);
				InitUpdateDatasetCmd(pDevice->m_strIotEngineSN, pReportData);
			}

			((CDvmData*)pReportData->FindByID(EDGE_PROCEDURE_VAR_errorinfo))->m_strValue = _T("");
		}
	}

	//yzj 2021-10-5 如果是数据上报的报文,不进入消息循环
	//直接返回iotengine数据集
	if(pEdgePkg->m_strType == EDGE_CMD_INFO_Type_DEV_REP_JOB_RESULT
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_DEV_REP_SYS_STATUS
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_DEV_EVENT_SYS_ALARM
		//|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_DEV_EVENT_HEARTBEAT
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_CON_REP_JOB_RESULT
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_CON_REP_CON_STATUS
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_CON_EVENT_CON_ALARM
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_APP_REP_JOB_RESULT
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_APP_REP_APP_STATUS
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_APP_EVENT_APP_ALARM
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_SVR_REP_DATA
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_SVR_EVENT_DATA
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_ADD
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_DEL
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_UPDATE
		|| pEdgePkg->m_strType == EDGE_CMD_INFO_Type_SVR_CMD_SERVICE)
	{
		//有判断结果的报文,即是自动上报报文
		if(pDevice)
		{
			InitUpdateDatasetCmd(pDevice->m_strIotEngineSN, pDataset);
			CDvmDatasetGroup* pProcedureData = UpdateAutoReport(pDevice, pEdgePkg->m_strType, strProcedureID, strGbkBuf);
			InitUpdateDatasetCmd(pDevice->m_strIotEngineSN, pProcedureData);
		}
	}
	else
	{
		//没有判断结果的报文,所以需要向iotEngine传通信结果作为依据
		if(pDevice)
			InitUpdateDatasetCmd(pDevice->m_strIotEngineSN, pConnectData);
	}



	m_listRecvPkg.AddNewChild(pEdgePkg);

/*  2021-7-18 lijunqing  规约通用过程
1、功能划分：报文解析、规约过程执行
2、报文解析：收到报文，解析报文，将报文携带的数据写入数据集（需要写入则写入），同时报文对象存入
	规约对象的接受报文列表
3、规约过程执行：遍历每一个过程，进行处理，包括：
	发送报文处理、超时处理等，遍历规约对象接受报文列表，判断报文是否为本过程的应到，是则处理并对报文进行
	标记
4、总的线程：进行过程执行处理、对规约对象不需要保留的报文进行删除
5、补充：报文解析模式
	如果保证接受的效率，则收到报文后，只缓存报文，报文解析放到独立的线程或者是总的线程。
	报文放到总的线程，可能会增加总线程执行的效率，影响过程执行的时效性。如果单独开放线程进行解析，线程增多
	增加共享操作带来的风险，如果使用互斥操作，则会严重拖慢系统的执行，甚至会导致系统死锁
*/

	return 0;
}

//mqtt连接断链
void CIotEdgeProtoServerBase::OnClose(char *pszErr)
{
	FreePxCmmInterface();
}

//2021-8-19  lijunqing 过程和规约本身相关，没必要使用工厂模式
CPxPrcdrBase* CIotEdgeProtoServerBase::CreateProcedure(const CString &strPrcdrID)
{
	CPxPrcdrBase *pProcedure = NULL;

	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);
	if(pDevice)
	{
		UpdateEdgeAuthDataset(pDevice);
		if(!UpdateLinkupDataset(pDevice))
		{
			return NULL;
		}
	}
	else
	{
		return NULL;
	}

	//根据过程ID创建不同的过程对象
	if (strPrcdrID == PROCEDURE_ID_WriteMmsAttr)
	{//特例处理：执行过程参考CPxPrcdrBase::Run
		pProcedure = new CPxPrcdrBase();
	}
	else if (strPrcdrID == EDGE_PROCEDURE_ID_parameter_Get
		|| strPrcdrID == EDGE_PROCEDURE_ID_discrete_Get
		|| strPrcdrID == EDGE_PROCEDURE_ID_analog_Get
		|| strPrcdrID == EDGE_PROCEDURE_ID_accumulator_Get
		|| strPrcdrID == EDGE_PROCEDURE_ID_timeRead
		|| strPrcdrID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_STATUS
		|| strPrcdrID == EDGE_PROCEDURE_ID_DEV_CMD_INFO_QUERY
		|| strPrcdrID == EDGE_PROCEDURE_ID_CON_CMD_CON_GET_CONFIG
		|| strPrcdrID == EDGE_PROCEDURE_ID_CON_CMD_CON_STATUS
		|| strPrcdrID == EDGE_PROCEDURE_ID_READ_DATASET
		|| strPrcdrID == EDGE_PROCEDURE_ID_READ_CMDRSLT)
	{
		pProcedure = new CMqttEdgePrcdrRead();
	}
	else if (strPrcdrID == EDGE_PROCEDURE_ID_parameter_Set
		|| strPrcdrID == EDGE_PROCEDURE_ID_parameter_Activate
		|| strPrcdrID == EDGE_PROCEDURE_ID_parameter_Cancel
		|| strPrcdrID == EDGE_PROCEDURE_ID_commad_HZ
		|| strPrcdrID == EDGE_PROCEDURE_ID_commad_TZ
		|| strPrcdrID == EDGE_PROCEDURE_ID_commad_ModelCtrl
		|| strPrcdrID == EDGE_PROCEDURE_ID_timeCheck
		|| strPrcdrID == EDGE_PROCEDURE_CMD_ID_APPDir_Get
		|| strPrcdrID == EDGE_PROCEDURE_CMD_ID_APPHFile_Get
		|| strPrcdrID == EDGE_PROCEDURE_CMD_ID_APP_CONFIG_Dir_Get
		|| strPrcdrID == EDGE_PROCEDURE_CMD_ID_CMD_SET_APP_CONFIG
		|| strPrcdrID == EDGE_PROCEDURE_CMD_ID_CMD_GET_APP_CONFIG
		|| strPrcdrID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_UPGRADE
		|| strPrcdrID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_SET_CONFIG
		|| strPrcdrID == EDGE_PROCEDURE_ID_DEV_CMD_DATETIME_SYN
		|| strPrcdrID == EDGE_PROCEDURE_ID_DEV_CMD_SYS_LOG
		|| strPrcdrID == EDGE_PROCEDURE_ID_CON_CMD_CON_INSTALL
		|| strPrcdrID == EDGE_PROCEDURE_ID_CON_CMD_CON_START
		|| strPrcdrID == EDGE_PROCEDURE_ID_CON_CMD_CON_STOP
		|| strPrcdrID == EDGE_PROCEDURE_ID_CON_CMD_CON_REMOVE
		|| strPrcdrID == EDGE_PROCEDURE_ID_CON_CMD_CON_SET_CONFIG
		|| strPrcdrID == EDGE_PROCEDURE_ID_CON_CMD_CON_UPGRADE
		|| strPrcdrID == EDGE_PROCEDURE_ID_CON_CMD_CON_LOG
		|| strPrcdrID == EDGE_PROCEDURE_ID_CON_CMD_STATUS_QUERY
		|| strPrcdrID == EDGE_PROCEDURE_ID_APP_CMD_APP_INSTALL
		|| strPrcdrID == EDGE_PROCEDURE_ID_APP_CMD_STATUS_QUERY
		|| strPrcdrID == EDGE_PROCEDURE_ID_APP_CMD_APP_START
		|| strPrcdrID == EDGE_PROCEDURE_ID_APP_CMD_APP_STOP
		|| strPrcdrID == EDGE_PROCEDURE_ID_APP_CMD_APP_REMOVE
		|| strPrcdrID == EDGE_PROCEDURE_ID_APP_CMD_APP_ENABLE
		|| strPrcdrID == EDGE_PROCEDURE_ID_APP_CMD_APP_UNENABLE
		|| strPrcdrID == EDGE_PROCEDURE_ID_APP_CMD_APP_SET_CONFIG
		|| strPrcdrID == EDGE_PROCEDURE_ID_APP_CMD_APP_UPGRADE
		|| strPrcdrID == EDGE_PROCEDURE_ID_APP_CMD_APP_LOG
		|| strPrcdrID == EDGE_PROCEDURE_ID_APP_CMD_APP_GET_CONFIG
		|| strPrcdrID == EDGE_PROCEDURE_ID_APP_CMD_APP_STATUS)
	{
		pProcedure = new CMqttEdgePrcdrWrite();
	}

	return pProcedure;
}

//根据procedureId查找数据集
CDvmDataset* CIotEdgeProtoServerBase::GetDvmDataset(CString& strProcedureID)
{
	CEdgeProtoDevice* pProtoDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);
	CDvmDevice* pDvmDevice = &pProtoDevice->m_oDvmDevice;
	CString strLDevicetID = GetLDeviceId(strProcedureID);
	CDvmLogicDevice* pDvmLDevice = (CDvmLogicDevice*)pDvmDevice->FindChildByID(strLDevicetID);
	if(!pDvmLDevice)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("ldevice: %s not found!"), strLDevicetID);
		return 0;
	}

	CString strDatasetID = GetDatasetId(strProcedureID);
	CDvmDataset* pDvmDataset =NULL;
	pDvmDataset = (CDvmDataset*)pDvmLDevice->FindByID(strDatasetID);

	return pDvmDataset;
}

//将para值更新至value
void CIotEdgeProtoServerBase::UpdataDvmValue(CDvmValue* pValue, CExBaseList* pPara)
{	
	if(!pValue->GetCount())
	{
		//当pValue数据集中的值都是动态创建的
		//查找pPara来创建数据集
		pValue->m_strID = pValue->m_strName = pPara->m_strID;
		pValue->m_strValue = pPara->m_strName;
		POS pos = pPara->GetHeadPosition();
		while (pos)
		{
			CDvmValue* pEdgeObj = (CDvmValue*)pPara->GetNext(pos);
			CDvmValue* pEdgeChild = new CDvmValue;
			UpdataDvmValue(pEdgeChild, pEdgeObj);
			pValue->AddNewChild(pEdgeChild);
		}

		return;
	}

	//当pValue数据集中存在固定值时,pPara查找并填充数据集
	POS posValue = pValue->GetHeadPosition();
	while(posValue)
	{
		CDvmValue* pChildValue = (CDvmValue*)pValue->GetNext(posValue);
		CExBaseList* pChild = (CExBaseList*)pPara->FindByID(pChildValue->m_strID);
		if(!pChild->GetCount())
		{
			//这里的m_strName是InitAfter中存放的对应成员的值
			pChildValue->m_strValue = pChild->m_strName;
		}
	}
}

void CIotEdgeProtoServerBase::UpdataEdgeParaData(CDvmData* pDvmData, CExBaseList* pParaData)
{
	//当pData数据集中的值都是动态创建的
	//查找pParaData来创建数据集
	CEdgeParaData* pData = (CEdgeParaData*)pParaData;
	POS pos = pData->GetHeadPosition();

	if(!pos)
	{
		//没有子项,只有一个EdgeParaData
		if(pData->GetClassID() == EDGECMDCLASSID_CEDGEPARADATA)
		{
			pDvmData->m_strValue = ((CEdgeParaData*)pData)->m_strValue;
		}
	}

	while (pos)
	{
		CDvmValue* pEdgeObj = (CDvmValue*)pData->GetNext(pos);
		CDvmValue* pEdgeChild = new CDvmValue;
		UpdataDvmValue(pEdgeChild, pEdgeObj);
		pDvmData->AddNewChild(pEdgeChild);
	}
}

CString CIotEdgeProtoServerBase::Utf8ToGBK(char* pBuf)
{
	long nLen = 0;
	wchar_t* pGbkBuf = 0;
	charUtf8_to_wcharGBK(pBuf, strlen(pBuf), &pGbkBuf, nLen);

	//防止出现\\u的转义unicode情况
	CString strGbkBuf, strTemp, strFind;
	strGbkBuf = pGbkBuf;
	while (strGbkBuf.Find("\\u") != -1)
	{
		strFind = strGbkBuf.Mid(strGbkBuf.Find("\\u"), 6);
		long nTemp = 0;
		HexToLong(strFind.Mid(2), nTemp);
		wchar_t wchTemp = nTemp;	
		strTemp = wchTemp;
		strGbkBuf.Replace(strFind, strTemp);
	}

	delete pGbkBuf;
	return strGbkBuf;
}

void CIotEdgeProtoServerBase::ParseErrorInfo(CExBaseList* pCmd)
{
	if(pCmd->GetClassID() == EDGECMDCLASSID_CEDGECMD)
	{
		AddErrorInfo(EDGE_REPORT_JSON, ((CEdgeCmd*)pCmd)->GetCmdErrorInfo());
	}
	else if((pCmd->GetClassID() & EDGECMDCLASSID_CEDGEERRORMNGR) == EDGECMDCLASSID_CEDGEERRORMNGR)
	{
		AddErrorInfo(EDGE_REPORT_JSON, ((CEdgeCmdErrorMngr*)pCmd)->GetCmdErrorInfo());
	}

	POS pos = pCmd->GetHeadPosition();
	while (pos)
	{
		CEdgeCmdErrorMngr* pErr = (CEdgeCmdErrorMngr*)pCmd->GetNext(pos);
		if (pErr)
		{
			ParseErrorInfo(pErr);
		}
	}
}

BOOL CIotEdgeProtoServerBase::AddErrorInfo(long nReportType, const CString& strErrorInfo)
{
	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);
	if(!pDevice)
	{
		return FALSE;
	}

	CDvmLogicDevice* pLDevice = (CDvmLogicDevice*)pDevice->m_oDvmDevice.FindByID(EDGE_LDEV_ID_report);
	CDvmDatasetGroup* pReportData = NULL;
	if(nReportType == EDGE_REPORT_JSON)
	{
		pReportData = (CDvmDatasetGroup*)pLDevice->FindByID(EDGE_DATASET_ID_jsonpackage);
	}
	else if (nReportType == EDGE_REPORT_HTTP)
	{
		pReportData = (CDvmDatasetGroup*)pLDevice->FindByID(EDGE_DATASET_ID_httppackage);
	}
	else if (nReportType == EDGE_REPORT_LINK)
	{
		pReportData = (CDvmDatasetGroup*)pLDevice->FindByID(EDGE_DATASET_ID_Linkpackage);
	}
	else
	{
		return FALSE;
	}

	if(!pReportData)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: AddErrorInfo == NULL"));
		return FALSE;
	}

	CDvmData* pData = (CDvmData*)pReportData->FindByID(EDGE_PROCEDURE_VAR_errorinfo);
	pData->m_strValue += strErrorInfo;

	return TRUE;
}

/*--------------------------------------------------------\
UpdateAutoReport函数用于将自动上报的报文更新至iotEngine
$pDeviceBase: 设备列表中的对应设备对象
$strType: 自动上报的类型,如果是端设备的自动上报需要特殊处理
$strProcedureID: 当前过程ID,用来确定数据集
$pBuf: 当前报文的内容
\---------------------------------------------------------*/
CDvmDatasetGroup* CIotEdgeProtoServerBase::UpdateAutoReport(CPxProtoDeviceBase* pDeviceBase, const CString strType, const CString& strProcedureID, const CString& strGbkBuf)
{
	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)pDeviceBase;
	CDvmLogicDevice* pLDevice = (CDvmLogicDevice*)pDevice->m_oDvmDevice.FindByID(GetLDeviceId(strProcedureID));
	CDvmDatasetGroup* pProcedureData = (CDvmDatasetGroup*)pLDevice->FindByID(GetDatasetId(strProcedureID));

	CString strTopic;
	strTopic.Format(_T("/v1/%s/topo/request"), m_strDeviceID);
	if(strType == EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_ADD)
	{
		CDvmDatasetGroup* pReportData = (CDvmDatasetGroup*)pProcedureData->FindByID(EDGE_PROCEDURE_VAR_TopoAddRequest);
		if(!pReportData)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_TopoAddRequest == NULL"));
			return pProcedureData;
		}

		((CDvmData*)pReportData->FindByID(EDGE_PROCEDURE_VAR_TopoAddRequestTopic))->m_strValue = strTopic;
		((CDvmData*)pReportData->FindByID(EDGE_PROCEDURE_VAR_TopoAddRequestMsg))->m_strValue = strGbkBuf;	
	}
	else if(strType == EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_DEL)
	{
		CDvmDatasetGroup* pReportData = (CDvmDatasetGroup*)pProcedureData->FindByID(EDGE_PROCEDURE_VAR_TopoDelRequest);
		if(!pReportData)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_TopoDelRequest == NULL"));
			return pProcedureData;
		}

		((CDvmData*)pReportData->FindByID(EDGE_PROCEDURE_VAR_TopoDelRequestTopic))->m_strValue = strTopic;
		((CDvmData*)pReportData->FindByID(EDGE_PROCEDURE_VAR_TopoDelRequestMsg))->m_strValue = strGbkBuf;	
	}
	else if(strType == EDGE_CMD_INFO_Type_TOPO_CMD_TOPO_UPDATE)
	{
		CDvmDatasetGroup* pReportData = (CDvmDatasetGroup*)pProcedureData->FindByID(EDGE_PROCEDURE_VAR_TopoUpdateRequest);
		if(!pReportData)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_TopoUpdateRequest == NULL"));
			return pProcedureData;
		}

		((CDvmData*)pReportData->FindByID(EDGE_PROCEDURE_VAR_TopoUpdateRequestTopic))->m_strValue = strTopic;
		((CDvmData*)pReportData->FindByID(EDGE_PROCEDURE_VAR_TopoUpdateRequestMsg))->m_strValue = strGbkBuf;		
	}
	else
	{
		strTopic.Format(_T("/v1/%s/%s/%s"), m_strDeviceID, 	edge_GetCmdTypeID(strProcedureID), edge_GetEdgeToServerCmdID(strProcedureID));
		CDvmDatasetGroup* pReportData = (CDvmDatasetGroup*)pProcedureData->FindByID(EDGE_PROCEDURE_VAR_resultreport);
		if(!pReportData)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_resultreport == NULL"));
			return pProcedureData;
		}
		
		if(pReportData)
		{
			//报文内容上报被使能的Procedure进行topic和data的上报
			((CDvmData*)pReportData->FindByID(EDGE_PROCEDURE_VAR_topic))->m_strValue = strTopic;
			((CDvmData*)pReportData->FindByID(EDGE_PROCEDURE_VAR_message))->m_strValue = strGbkBuf;	
		}
	}

	return pProcedureData;
}

void CIotEdgeProtoServerBase::UpdataDvmData(CDvmData* pDvmData, CExBaseList* pParaData)
{
	if(!pParaData)
	{
		return;
	}

	//当data下面没有value值的时候
	if(!pDvmData->GetCount())
	{
		if(pParaData->GetClassID() == EDGECMDCLASSID_CEDGEPARADATA)
			UpdataEdgeParaData(pDvmData, pParaData);
		else
			pDvmData->m_strValue = pParaData->m_strName;
		return;
	}

	//data下面还存在value
	POS pos = pDvmData->GetHeadPosition();
	while(pos)
	{
		CDvmValue* pValue = (CDvmValue*)pDvmData->GetNext(pos);
		CExBaseList* pChild = (CExBaseList*)pParaData->FindByID(pValue->m_strID);

		if(!pChild)
		{
			continue;
		}

		//自动测试接收GBK格式
		long nLen = 0;
		char* strValue = NULL;
		charUtf8_to_charGBK((char*)pChild->m_strName.GetString(), pChild->m_strName.GetLength(), &strValue, nLen);
		pValue->m_strValue = strValue;
		delete strValue;
	}
}

//将json的数据解析成dvmdata的子项dvmvalue
void CIotEdgeProtoServerBase::JsonToDvmValue(CExBaseList* pNode, CJSON* pJson)
{
	if(!pJson)
		return;

	pJson = pJson->child;
	while (pJson)
	{
		CDvmValue* pChildValue = new CDvmValue;
		pChildValue->m_strName = pChildValue->m_strID = pJson->valuestring;
		pChildValue->m_strValue = pJson->valuestring;
		pNode->AddNewChild(pChildValue);
		pJson = pJson->next;
	}
}

/*--------------------------------------------------------\
InitUpdateDataSetCmd函数用于将数据集更新至iotEngine
$strIotEngineSN: iotEngine的过程ID,用于MQTT的Topic
$pDataset: 需要更新的数据集
\---------------------------------------------------------*/
void CIotEdgeProtoServerBase::InitUpdateDatasetCmd(const CString& strIotEngineSN, CDvmDataset* pDataset)
{
	if(!pDataset)
	{
		return;
	}

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

	m_pPxCmmOptrInterface->Send(&oSysState);
}

void CIotEdgeProtoServerBase::UpdataDvmDataset_LinkState(CDvmDataset* pDvmDataset, CExBaseList* pParaData)
{
	CEdgeParam* pParam = (CEdgeParam*)pParaData;
	CJSON* pChildJson = pParam->GetLinkStateJson();
	if(!pChildJson)
	{
		return;
	}
	pChildJson = pChildJson->child;
	while (pChildJson)
	{	
		//创建data-value对象
		CDvmData* pLinkState = new CDvmData;
		pLinkState->m_strDataType = _T("STRUCT");
		pLinkState->m_strName = _T("其他的设备信息");
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_status), pLinkState, EDGE_PROCEDURE_VAR_status, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_name), pLinkState, EDGE_PROCEDURE_VAR_name, CJSON_String);

		CJSON* pID = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_name);
		if(pID)
		{
			pLinkState->m_strID = CString(pID->valuestring);
		}
		pDvmDataset->AddNewChild(pLinkState);

		pChildJson = pChildJson->next;
	}
}

void CIotEdgeProtoServerBase::UpdataDvmDataset_DeviceInfos(CDvmDataset* pDvmDataset, CExBaseList* pParaData)
{
	CEdgeParam* pParam = (CEdgeParam*)pParaData;
	pDvmDataset->RemoveAll();
	CJSON* pChildJson = pParam->GetDeviceInfosJson();
	if(!pChildJson)
	{
		return;
	}
	pChildJson = pChildJson->child;
	while (pChildJson)
	{
		CDvmData* pDeviceInfo = new CDvmData;
		pDeviceInfo->m_strDataType = _T("STRUCT");
		pDeviceInfo->m_strName = _T("端设备信息");

		CString strNodeId = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_nodeId)->valuestring;
		pDeviceInfo->m_strID = strNodeId;

		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_nodeId), pDeviceInfo, EDGE_PROCEDURE_VAR_nodeId, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_name), pDeviceInfo, EDGE_PROCEDURE_VAR_name, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_description), pDeviceInfo, EDGE_PROCEDURE_VAR_description, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_mfgInfo), pDeviceInfo, EDGE_PROCEDURE_VAR_mfgInfo, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_model), pDeviceInfo, EDGE_PROCEDURE_VAR_model, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_modelId), pDeviceInfo, EDGE_PROCEDURE_VAR_modelId, CJSON_String);

		pDvmDataset->AddNewChild(pDeviceInfo);

		pChildJson = pChildJson->next;
	}
}

void CIotEdgeProtoServerBase::UpdataDvmDataset_DeviceData(CDvmDataset* pDvmDataset, const CString& strDeviceID)
{
	pDvmDataset->RemoveAll();
	
	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(strDeviceID);
	POS pos = pDevice->m_listTopoDevice.GetHeadPosition();
	while (pos)
	{
		CExBaseList* pTopo = (CExBaseList*)pDevice->GetNext(pos);

		CDvmData* pDeviceData = new CDvmData;
		pDeviceData->m_strDataType = _T("STRUCT");
		pDeviceData->m_strName = _T("端设备");
		pDeviceData->m_strID = pTopo->m_strID;
		pDeviceData->AddValue(EDGE_PROCEDURE_VAR_nodeId, pTopo->m_strName);
		pDeviceData->AddValue(EDGE_PROCEDURE_VAR_deviceId, pTopo->m_strID);
		pDeviceData->AddValue(EDGE_PROCEDURE_VAR_statusCode, 200);

		pDvmDataset->AddNewChild(pDeviceData);
	}
}

void CIotEdgeProtoServerBase::UpdataDvmDataset_ConPara(CDvmDataset* pDvmDataset, CExBaseList* pParaData)
{
	CEdgeParam* pParam = (CEdgeParam*)pParaData;
	pDvmDataset->RemoveAll();
	CJSON* pChildJson = pParam->GetContParaJson();
	if(!pChildJson)
	{
		return;
	}
	pChildJson = pChildJson->child;
	while (pChildJson)
	{	
		//创建data-value对象
		CString strErrorInfo;
		CDvmDatasetGroup* pConPara = new CDvmDatasetGroup;
		pConPara->m_strDataType = _T("STRUCT");
		pConPara->m_strName = _T("容器参数");
		CJSON* pContainer = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_container);
		CString strContainer = pContainer->valuestring;
		pConPara->AddNewData(EDGE_PROCEDURE_VAR_container, EDGE_PROCEDURE_VAR_container, EDGE_DATATYPE_STRING, strContainer);
		CEdgeCmdErrorMngr::AddErrorInfo(pContainer, CJSON_String, strErrorInfo);
		pConPara->m_strID = strContainer;

		CJSON* pCfgCpuJson = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_cfgCpu);
		CDvmData* pCfgCpu = new CDvmData;
		pCfgCpu->m_strID = EDGE_PROCEDURE_VAR_cfgCpu;

		AddNewValue(CJSON_GetObjectItem(pCfgCpuJson, EDGE_PROCEDURE_VAR_cpus), pCfgCpu, EDGE_PROCEDURE_VAR_cpus, CJSON_Int);
		AddNewValue(CJSON_GetObjectItem(pCfgCpuJson, EDGE_PROCEDURE_VAR_cpuLmt), pCfgCpu, EDGE_PROCEDURE_VAR_cpuLmt, CJSON_Int);

		CJSON* pCfgMemJson = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_cfgMem);
		CDvmData* pCfgMem = new CDvmData;
		pCfgMem->m_strID = EDGE_PROCEDURE_VAR_cfgMem;

		AddNewValue(CJSON_GetObjectItem(pCfgMemJson, EDGE_PROCEDURE_VAR_memory), pCfgMem, EDGE_PROCEDURE_VAR_memory, CJSON_Int);
		AddNewValue(CJSON_GetObjectItem(pCfgMemJson, EDGE_PROCEDURE_VAR_memLmt), pCfgMem, EDGE_PROCEDURE_VAR_memLmt, CJSON_Int);

		CJSON* pCfgDiskJson = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_cfgDisk);
		CDvmData* pCfgDisk = new CDvmData;
		pCfgDisk->m_strID = EDGE_PROCEDURE_VAR_cfgDisk;

		AddNewValue(CJSON_GetObjectItem(pCfgDiskJson, EDGE_PROCEDURE_VAR_disk), pCfgDisk, EDGE_PROCEDURE_VAR_disk, CJSON_Int);
		AddNewValue(CJSON_GetObjectItem(pCfgDiskJson, EDGE_PROCEDURE_VAR_diskLmt), pCfgDisk, EDGE_PROCEDURE_VAR_diskLmt, CJSON_Int);

		AddNewData(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_port), pConPara, EDGE_PROCEDURE_VAR_port);

		pConPara->AddNewChild(pCfgCpu);
		pConPara->AddNewChild(pCfgMem);
		pConPara->AddNewChild(pCfgDisk);

		CJSON* pDevJson = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_dev);
		JsonToDvmValue(pConPara, pDevJson);
		CJSON* pMountJson = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_mount);
		JsonToDvmValue(pConPara, pMountJson);

		pDvmDataset->AddNewChild(pConPara);

		pChildJson = pChildJson->next;
	}
}

void CIotEdgeProtoServerBase::UpdataDvmDataset_ConStatus(CDvmDataset* pDvmDataset, CExBaseList* pParaData)
{
	CEdgeParam* pParam = (CEdgeParam*)pParaData;
	pDvmDataset->RemoveAll();
	CJSON* pChildJson = pParam->GetContStatusJson();
	if(!pChildJson)
	{
		return;
	}
	pChildJson = pChildJson->child;
	while (pChildJson)
	{	
		CDvmData* pConStatus = new CDvmData;
		pConStatus->m_strDataType = _T("STRUCT");
		pConStatus->m_strName = _T("容器状态参数");

		CString strContainer = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_container)->valuestring;
		pConStatus->m_strID = strContainer;

		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_container), pConStatus, EDGE_PROCEDURE_VAR_container, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_version), pConStatus, EDGE_PROCEDURE_VAR_version, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_state), pConStatus, EDGE_PROCEDURE_VAR_state, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_cpuRate), pConStatus, EDGE_PROCEDURE_VAR_cpuRate, CJSON_Double);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_memUsed), pConStatus, EDGE_PROCEDURE_VAR_memUsed, CJSON_Double);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_diskUsed), pConStatus, EDGE_PROCEDURE_VAR_diskUsed, CJSON_Double);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_ip), pConStatus, EDGE_PROCEDURE_VAR_ip, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_created), pConStatus, EDGE_PROCEDURE_VAR_created, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_started), pConStatus, EDGE_PROCEDURE_VAR_started, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_lifeTime), pConStatus, EDGE_PROCEDURE_VAR_lifeTime, CJSON_Int);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_image), pConStatus, EDGE_PROCEDURE_VAR_image, CJSON_String);

		pDvmDataset->AddNewChild(pConStatus);

		pChildJson = pChildJson->next;
	}
}

void CIotEdgeProtoServerBase::UpdataDvmDataset_AppCfgs(CDvmDataset* pDvmDataset, CExBaseList* pParaData)
{
	CEdgeParam* pParam = (CEdgeParam*)pParaData;
	pDvmDataset->RemoveAll();
	CJSON* pChildJson = pParam->GetAppCfgsJson();
	if(!pChildJson)
	{
		return;
	}
	pChildJson = pChildJson->child;
	while (pChildJson)
	{	
		CDvmDatasetGroup* pAppCfgs = new CDvmDatasetGroup;
		pAppCfgs->m_strDataType = _T("STRUCT");
		pAppCfgs->m_strName = _T("应用配置参数");
		CString strApp = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_app)->valuestring;
		pAppCfgs->m_strID = strApp;

		AddNewData(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_app), pAppCfgs, EDGE_PROCEDURE_VAR_app);

		CJSON* pCfgCpuJson = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_cfgCpu);
		CDvmData* pCfgCpu = new CDvmData;
		pCfgCpu->m_strID = EDGE_PROCEDURE_VAR_cfgCpu;
		pCfgCpu->AddValue(EDGE_PROCEDURE_VAR_cpus, CJSON_GetObjectItem(pCfgCpuJson, EDGE_PROCEDURE_VAR_cpus)->valueint);
		pCfgCpu->AddValue(EDGE_PROCEDURE_VAR_cpuLmt, CJSON_GetObjectItem(pCfgCpuJson, EDGE_PROCEDURE_VAR_cpuLmt)->valueint);
		CJSON* pCfgMemJson = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_cfgMem);
		CDvmData* pCfgMem = new CDvmData;
		pCfgMem->m_strID = EDGE_PROCEDURE_VAR_cfgMem;
		pCfgMem->AddValue(EDGE_PROCEDURE_VAR_memory, CJSON_GetObjectItem(pCfgMemJson, EDGE_PROCEDURE_VAR_memory)->valueint);
		pCfgMem->AddValue(EDGE_PROCEDURE_VAR_memLmt, CJSON_GetObjectItem(pCfgMemJson, EDGE_PROCEDURE_VAR_memLmt)->valueint);

		pAppCfgs->AddNewChild(pCfgCpu);
		pAppCfgs->AddNewChild(pCfgMem);

		pDvmDataset->AddNewChild(pAppCfgs);

		pChildJson = pChildJson->next;
	}
}

void CIotEdgeProtoServerBase::UpdataDvmDataset_Apps(CDvmDataset* pDvmDataset, CExBaseList* pParaData)
{
	CEdgeParam* pParam = (CEdgeParam*)pParaData;
	pDvmDataset->RemoveAll();
	CJSON* pChildJson = pParam->GetAppsJson();
	if(!pChildJson)
	{
		return;
	}
	pChildJson = pChildJson->child;
	while (pChildJson)
	{	
		CDvmDatasetGroup* pApps = new CDvmDatasetGroup;
		pApps->m_strDataType = _T("STRUCT");
		pApps->m_strName = _T("应用配置参数");
		CString strApp = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_app)->valuestring;
		AddNewData(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_app), pApps, EDGE_PROCEDURE_VAR_app);
		pApps->m_strID = strApp;
		AddNewData(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_version), pApps, EDGE_PROCEDURE_VAR_version);
		AddNewData(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_appHash), pApps, EDGE_PROCEDURE_VAR_appHash);
		AddNewData(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_srvNumber), pApps, EDGE_PROCEDURE_VAR_srvNumber);
		
		//array of process
		CJSON* pProcessJson = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_process);
		if (pProcessJson)
		{
			CJSON* pProcessChildJson = pProcessJson->child;
			while (pProcessChildJson)
			{
				CDvmData* pProcess = new CDvmData;
				pProcess->m_strDataType = _T("STRUCT");
				pProcess->m_strName = _T("进程字段");
				CString strProcess = CJSON_GetObjectItem(pProcessChildJson, EDGE_PROCEDURE_VAR_srvName)->valuestring;
				pProcess->m_strID = strProcess;

				AddNewValue(CJSON_GetObjectItem(pProcessChildJson, EDGE_PROCEDURE_VAR_srvIndex), pProcess, EDGE_PROCEDURE_VAR_srvIndex, CJSON_Int);
				AddNewValue(CJSON_GetObjectItem(pProcessChildJson, EDGE_PROCEDURE_VAR_srvName), pProcess, EDGE_PROCEDURE_VAR_srvName, CJSON_String);
				AddNewValue(CJSON_GetObjectItem(pProcessChildJson, EDGE_PROCEDURE_VAR_srvEnable), pProcess, EDGE_PROCEDURE_VAR_srvEnable, CJSON_String);
				AddNewValue(CJSON_GetObjectItem(pProcessChildJson, EDGE_PROCEDURE_VAR_srvStatus), pProcess, EDGE_PROCEDURE_VAR_srvStatus, CJSON_String);
				AddNewValue(CJSON_GetObjectItem(pProcessChildJson, EDGE_PROCEDURE_VAR_cpuLmt), pProcess, EDGE_PROCEDURE_VAR_cpuLmt, CJSON_Double);
				AddNewValue(CJSON_GetObjectItem(pProcessChildJson, EDGE_PROCEDURE_VAR_cpuRate), pProcess, EDGE_PROCEDURE_VAR_cpuRate, CJSON_Double);
				AddNewValue(CJSON_GetObjectItem(pProcessChildJson, EDGE_PROCEDURE_VAR_memLmt), pProcess, EDGE_PROCEDURE_VAR_memLmt, CJSON_Double);
				AddNewValue(CJSON_GetObjectItem(pProcessChildJson, EDGE_PROCEDURE_VAR_memUsed), pProcess, EDGE_PROCEDURE_VAR_memUsed, CJSON_Double);
				AddNewValue(CJSON_GetObjectItem(pProcessChildJson, EDGE_PROCEDURE_VAR_startTime), pProcess, EDGE_PROCEDURE_VAR_startTime, CJSON_String);
				pApps->AddNewChild(pProcess);
				pProcessChildJson = pProcessChildJson->next;
			}
		}
		
		pDvmDataset->AddNewChild(pApps);
		pChildJson = pChildJson->next;
	}
}

void CIotEdgeProtoServerBase::JsonToDvmData(CDvmDataset* pDvmDataset, CJSON* pJson)
{
	if(!pJson)
	{
		return;
	}
	CJSON* pChildJson = pJson->child;
	while(pChildJson)
	{
		//没有子项,是data
		if(pChildJson->type == CJSON_Number)
		{
			CString strTemp;
			strTemp.Format(_T("%d"), pChildJson->valueint);
			pDvmDataset->AddNewData(pChildJson->string, pChildJson->string, EDGE_DATATYPE_LONG, strTemp);
		}
		else if(pChildJson->type == CJSON_String)
		{
			pDvmDataset->AddNewData(pChildJson->string, pChildJson->string, EDGE_DATATYPE_STRING, pChildJson->valuestring);
		}
		else if (pChildJson->type == CJSON_Array || pChildJson->type == CJSON_Object)
		{
			CDvmDatasetGroup* pDatasetGroup = new CDvmDatasetGroup;
			pDatasetGroup->m_strID = pDatasetGroup->m_strName = CString(pChildJson->string);
			pDvmDataset->AddNewChild(pDatasetGroup);
			JsonToDvmData(pDatasetGroup, pChildJson);
		}

		pChildJson = pChildJson->next;
	}
}

void CIotEdgeProtoServerBase::AddNewData(CJSON* pJson, CDvmDataset* pDvmDataset, const CString& strID)
{
	if(!pJson)
		return;
	
	if(pJson->type == CJSON_String)
		pDvmDataset->AddNewData(strID, strID, EDGE_DATATYPE_STRING, CString(pJson->valuestring));
	else if(pJson->type == CJSON_Number)
	{
		CString strTemp;
		strTemp.Format(_T("%d"), pJson->valueint);
		pDvmDataset->AddNewData(strID, strID, EDGE_DATATYPE_LONG, strTemp);
	}
}

BOOL CIotEdgeProtoServerBase::UpdateLinkupDataset(CPxProtoDeviceBase* pDeviceBase)
{
	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)pDeviceBase;

	if(pDevice->m_bIsOnline)
	{
		return TRUE;
	}

	//yzj 2021-12-4 CreateDevice之后的第一个procedure要将linkup的报文存入dataset
	if(pDevice->m_pLinkupReport->GetCount())
	{
		CDvmDataset* pDataset = m_pDvmDevice->FindDataset(EDGE_DATASET_ID_Linkpackage);
		if(!pDataset)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,"未找到对应的LINK PACKAGE!");
			return FALSE;
		}
		CDvmDatasetGroup* pDatasetGroup = (CDvmDatasetGroup*)pDataset->FindByID(EDGE_PROCEDURE_VAR_recvmsg);
		if(!pDatasetGroup)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_recvmsg == NULL"));
			return FALSE;
		}

		CDvmData* pData = (CDvmData*)pDatasetGroup->FindByID(EDGE_PROCEDURE_VAR_recvmsg_topic);
		if(!pData)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_recvmsg_topic == NULL"));
			return FALSE;
		}

		pData->m_strValue = ((CDvmData*)pDevice->m_pLinkupReport->FindByID(EDGE_PROCEDURE_VAR_recvmsg_topic))->m_strValue;
		fwrite(const_cast<char*>(pData->m_strValue.GetString()), pData->m_strValue.GetLength(), 1, pDevice->m_pReportFile);
		pData = (CDvmData*)pDatasetGroup->FindByID(EDGE_PROCEDURE_VAR_recvmsg_message);
		pData->m_strValue =((CDvmData*)pDevice->m_pLinkupReport->FindByID(EDGE_PROCEDURE_VAR_recvmsg_message))->m_strValue;	
		pData->m_strValue = Utf8ToGBK(const_cast<char*>(pData->m_strValue.GetString()));
		fwrite(const_cast<char*>(pData->m_strValue.GetString()), pData->m_strValue.GetLength(), 1, pDevice->m_pReportFile);

		pDatasetGroup = (CDvmDatasetGroup*)pDataset->FindByID(EDGE_PROCEDURE_VAR_sendmsg);
		pData = (CDvmData*)pDatasetGroup->FindByID(EDGE_PROCEDURE_VAR_sendmsg_topic);
		pData->m_strValue = ((CDvmData*)pDevice->m_pLinkupReport->FindByID(EDGE_PROCEDURE_VAR_sendmsg_topic))->m_strValue;	
		fwrite(const_cast<char*>(pData->m_strValue.GetString()), pData->m_strValue.GetLength(), 1, pDevice->m_pReportFile);
		pData = (CDvmData*)pDatasetGroup->FindByID(EDGE_PROCEDURE_VAR_sendmsg_message);
		pData->m_strValue = ((CDvmData*)pDevice->m_pLinkupReport->FindByID(EDGE_PROCEDURE_VAR_sendmsg_message))->m_strValue;
		fwrite(const_cast<char*>(pData->m_strValue.GetString()), pData->m_strValue.GetLength(), 1, pDevice->m_pReportFile);

		pDevice->m_pLinkupReport->DeleteAll();

		InitUpdateDatasetCmd(pDevice->m_strIotEngineSN, pDataset);

		pDevice->m_bIsOnline = TRUE;
		return TRUE;
	}
	return FALSE;
}

void CIotEdgeProtoServerBase::UpdateEdgeAuthDataset(CPxProtoDeviceBase* pDeviceBase)
{
	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)pDeviceBase;

	if(pDevice->m_bIsOnline)
	{
		return;
	}

	CDataGroup* pDataGroup = (CDataGroup*)g_pEdgeEngineProtoSvrBaseApp->m_oIotEdgeMqttServer.m_oEdgeAuthList.FindByID(m_strDeviceID);
	if(pDataGroup)
	{
		CDvmDataset* pDataset = m_pDvmDevice->FindDataset(EDGE_DATASET_ID_httppackage);
		if(!pDataset)
		{
			CLogPrint::LogString(XLOGLEVEL_INFOR,"未找到对应的HTTP PACKAGE!");
			return;
		}
		pDataset->DeleteByID(EDGE_PROCEDURE_VAR_RequestAddr);
		pDataset->DeleteByID(EDGE_PROCEDURE_VAR_RequestMessage);
		pDataset->DeleteByID(EDGE_PROCEDURE_VAR_ResponseMessage);
		pDataset->DeleteByID(EDGE_PROCEDURE_VAR_msg);
		pDataset->DeleteByID(EDGE_PROCEDURE_VAR_code);
		pDataset->AddNewChild(pDataGroup->FindByID(EDGE_PROCEDURE_VAR_RequestAddr));
		pDataset->AddNewChild(pDataGroup->FindByID(EDGE_PROCEDURE_VAR_RequestMessage));

		CDvmData* pData = (CDvmData*)pDataGroup->FindByID(EDGE_PROCEDURE_VAR_ResponseMessage);
		if(!pData)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_ResponseMessage == NULL"));
			return;
		}

		pDataset->AddNewChild(pData);
		CJSON* pJson = CJSON_Parse(pData->m_strValue);
		CJSON* pMsgJson = CJSON_GetObjectItem(pJson, _T("errMsg"));
		CJSON* pCodeJson =  CJSON_GetObjectItem(pJson, EDGE_PROCEDURE_VAR_code);
		pDataset->AddNewData(EDGE_PROCEDURE_VAR_msg, EDGE_PROCEDURE_VAR_msg, EDGE_DATATYPE_STRING, pMsgJson->valuestring);
		CString strTemp;
		strTemp.Format(_T("%d"), pCodeJson->valueint);
		pDataset->AddNewData(EDGE_PROCEDURE_VAR_code, EDGE_PROCEDURE_VAR_code, EDGE_DATATYPE_LONG, strTemp);
		CJSON_Delete(pJson);

		pDataGroup->RemoveAll();
		g_pEdgeEngineProtoSvrBaseApp->m_oIotEdgeMqttServer.m_oEdgeAuthList.DeleteByID(m_strDeviceID);
		InitUpdateDatasetCmd(pDevice->m_strIotEngineSN, pDataset);
	}
}

//nVarType是目标类型,与json中的type对应
void CIotEdgeProtoServerBase::AddNewValue(CJSON* pJson, CDvmData* pDvmData, const CString& strID, long nVarType)
{
	CString strErrorInfo;

	if(!pJson)
	{
		strErrorInfo.Format(_T("[%s]错误,%s"), strID, EDGE_ERR_TYPE_MISSING);
		AddErrorInfo(EDGE_REPORT_JSON, strErrorInfo);
		return;
	}

	if(pJson->type == CJSON_String)
		pDvmData->AddValue(strID, CString(pJson->valuestring));
	else if(pJson->type == CJSON_Number)
	{
		CString strTemp;
		if(pJson->numType == CJSON_Int)
		{
			strTemp.Format(_T("%d"), pJson->valueint);
		}
		else
		{
			strTemp.Format(_T("%.8f"), pJson->valuedouble);
		}
		pDvmData->AddValue(strID, strTemp);
	}

	CEdgeCmdErrorMngr::AddErrorInfo(pJson, nVarType, strErrorInfo);
	AddErrorInfo(EDGE_REPORT_JSON, strErrorInfo);
}

void CIotEdgeProtoServerBase::SetCurrentTopoID(CExBaseList* pListDatas)
{
	CDvmValue* pTopoID = (CDvmValue*)pListDatas->FindByID(_T("TopoID"));
	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);
	if(pTopoID->m_strValue.Find('.') != -1)
		pDevice->m_strTopoID = pTopoID->m_strValue.Mid(0, pTopoID->m_strValue.Find('.'));
	else
		pDevice->m_strTopoID = pTopoID->m_strValue;

	m_pProtoEventInterface->OnPrcdrFinishedEx(RUNPROCEDURE_EVENT_CommFinish, NULL);
}

void CIotEdgeProtoServerBase::SetEnableReport(CExBaseList* pListDatas, const CString& strProcedureID)
{
	CDvmValue* pLibID = (CDvmValue*)pListDatas->FindByID(_T("LibID"));
	CEdgeProtoDevice* pDevice = (CEdgeProtoDevice*)g_pEdgeEngineProtoSvrBaseApp->m_listDevice.FindByID(m_strDeviceID);
	if(pDevice &&  strProcedureID == EDGE_PROCEDURE_ID_DEV_SET_ENABLE)
	{
		pDevice->m_listLib.AddNew(pLibID->m_strValue, pLibID->m_strValue);
	}
	else if (pDevice &&  strProcedureID == EDGE_PROCEDURE_ID_DEV_SET_DISABLE)
	{
		pDevice->m_listLib.DeleteByID(pLibID->m_strValue);
	}

	m_pProtoEventInterface->OnPrcdrFinishedEx(RUNPROCEDURE_EVENT_CommFinish, NULL);
}

void CIotEdgeProtoServerBase::UpdataDvmDataset_Links(CDvmDataset* pDvmDataset, CExBaseList* pParaData)
{
	CEdgeParam* pParam = (CEdgeParam*)pParaData;
	CJSON* pChildJson = pParam->GetLinksJson();
	if(!pChildJson)
	{
		return;
	}
	pChildJson = pChildJson->child;
	while (pChildJson)
	{	
		//创建data-value对象
		CDvmData* pLinks = new CDvmData;
		pLinks->m_strDataType = _T("STRUCT");
		pLinks->m_strName = _T("其他的边设备信息");

		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_id), pLinks, EDGE_PROCEDURE_VAR_id, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_type), pLinks, EDGE_PROCEDURE_VAR_type, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_mac), pLinks, EDGE_PROCEDURE_VAR_mac, CJSON_String);
		AddNewValue(CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_name), pLinks, EDGE_PROCEDURE_VAR_name, CJSON_String);
	
		CJSON* pID = CJSON_GetObjectItem(pChildJson, EDGE_PROCEDURE_VAR_name);
		if(pID)
		{
			pLinks->m_strID = CString(pID->valuestring);
		}

		pDvmDataset->AddNewChild(pLinks);
		pChildJson = pChildJson->next;
	}
}

void CIotEdgeProtoServerBase::UpdataDvmDataset(CDvmDataset* pDvmDataset, CExBaseList* pParaData)
{
	if(!pParaData)
	{
		return;
	}

	POS pos = pDvmDataset->GetHeadPosition();
	while(pos)
	{
		CExBaseList* pChildNode =  (CExBaseList*)pDvmDataset->GetNext(pos);
		if(pChildNode->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			//子节点是dvmdata
			UpdataDvmData((CDvmData*)pChildNode, (CExBaseList*)pParaData->FindByID(pChildNode->m_strID));
		}
		else
		{
			//子节点是dvmdatasetgroup
			if(pChildNode->m_strID == EDGE_PROCEDURE_VAR_links)
			{
				UpdataDvmDataset_Links((CDvmDatasetGroup*)pChildNode, pParaData);
			}
			else if(pChildNode->m_strID == EDGE_PROCEDURE_VAR_linkState)
			{
				UpdataDvmDataset_LinkState((CDvmDatasetGroup*)pChildNode, pParaData);
			}
			else if(pChildNode->m_strID == EDGE_PROCEDURE_VAR_apps)
			{
				UpdataDvmDataset_Apps((CDvmDatasetGroup*)pChildNode, pParaData);
			}
			else if (pChildNode->m_strID == EDGE_PROCEDURE_VAR_appCfgs)
			{
				UpdataDvmDataset_AppCfgs((CDvmDatasetGroup*)pChildNode, pParaData);
			}
			else if(pChildNode->m_strID == EDGE_PROCEDURE_VAR_contStatus)
			{	
				UpdataDvmDataset_ConStatus((CDvmDatasetGroup*)pChildNode, pParaData);
			}
			else if(pChildNode->m_strID == EDGE_PROCEDURE_VAR_contPara)
			{	
				UpdataDvmDataset_ConPara((CDvmDatasetGroup*)pChildNode, pParaData);
			}
			else if(pChildNode->m_strID == EDGE_PROCEDURE_VAR_deviceInfos)
			{	
				UpdataDvmDataset_DeviceInfos((CDvmDatasetGroup*)pChildNode, pParaData);
			}
			else if(pDvmDataset->m_strID == EDGE_DATASET_ID_TOPO_Admin && pChildNode->m_strID == EDGE_PROCEDURE_VAR_data)
			{	
				UpdataDvmDataset_DeviceData((CDvmDatasetGroup*)pChildNode, m_strDeviceID);
			}
			else
			{
				UpdataDvmDataset((CDvmDatasetGroup*)pChildNode, (CExBaseList*)pParaData->FindByID(pChildNode->m_strID));
			}
		}
	}
}

CDvmDataset* CIotEdgeProtoServerBase::UpdateDataset_Event(CEdgeParaDatas* pParaDatas, CString& strProcedureID)
{
	CDvmDataset* pDvmDataset = GetDvmDataset(strProcedureID);
	CDvmData* pCopy = new CDvmData;
	((CDvmData*)pDvmDataset->GetHead())->CopyEx(pCopy, TRUE, TRUE);
	pDvmDataset->DeleteAll();
	pDvmDataset->AddNewChild(pCopy);
	CDvmData* pDvmData = new CDvmData;
	pDvmData->m_strDataType = _T("STRUCT");
	CString strTime;
	GetCurrSystemtimeString(strTime);

	if(strProcedureID == EDGE_PROCEDURE_ID_DEV_EVENT_SYS_ALARM)
	{
		pDvmData->m_strID = strTime;
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_CON_EVENT_CON_ALARM)
	{
		CDvmValue* pContainerValue = (CDvmValue*)pParaDatas->FindByID(EDGE_PROCEDURE_VAR_container);
		if(!pContainerValue)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_container == NULL"));
			return pDvmDataset;
		}

		pDvmData->m_strID.Format(_T("%s$%s"), strTime, pContainerValue->m_strValue);
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APP_EVENT_APP_ALARM)
	{
		CDvmValue* pContainerValue = (CDvmValue*)pParaDatas->FindByID(EDGE_PROCEDURE_VAR_container);
		CDvmValue* pAppValue = (CDvmValue*)pParaDatas->FindByID(EDGE_PROCEDURE_VAR_app);
		if(!pContainerValue || !pAppValue)
		{
			CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_container | EDGE_PROCEDURE_VAR_app == NULL"));
			return pDvmDataset;
		}

		pDvmData->m_strID.Format(_T("%s$%s$%s"), strTime, pContainerValue->m_strValue, pAppValue->m_strValue);
	}
	pDvmData->m_strName = pDvmData->m_strID;

	POS pos = pParaDatas->GetHeadPosition();
	while (pos)
	{
		CDvmData* pData = (CDvmData*)pParaDatas->GetNext(pos);
		CDvmValue* pValue = new CDvmValue;
		pValue->m_strID = pValue->m_strName = pData->m_strID;
		pValue->m_strValue = pData->m_strValue;
		pDvmData->AddNewChild(pValue);
	}
	pDvmDataset->AddNewChild(pDvmData);
	return pDvmDataset;
}

CDvmDataset* CIotEdgeProtoServerBase::UpdateDataset_Service_Event(CEdgeParaDatas* pParaDatas, CString& strProcedureID, const CString& strTopoID)
{
	CDvmDataset* pDvmDataset = GetDvmDataset(strProcedureID);
	CDvmData* pCopy = new CDvmData;
	((CDvmData*)pDvmDataset->GetHead())->CopyEx(pCopy, TRUE, TRUE);
	pDvmDataset->DeleteAll();
	pDvmDataset->AddNewChild(pCopy);
	CDvmData* pDvmData = new CDvmData;
	pDvmData->m_strDataType = _T("STRUCT");
	CString strTime;
	GetCurrSystemtimeString(strTime);
	pDvmData->m_strID.Format(_T("%s$%s"), strTime, strTopoID);
	pDvmData->m_strName = pDvmData->m_strID;

	CEdgeParaData* pEdgeMethod = (CEdgeParaData*)pParaDatas->FindByID(EDGE_PROCEDURE_VAR_method);
	if(!pEdgeMethod)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_method == NULL"));
		return pDvmDataset;
	}

	CDvmValue* pMethod = new CDvmValue;
	pMethod->m_strID = pEdgeMethod->m_strID;
	pMethod->m_strName = pEdgeMethod->m_strName;
	pMethod->m_strValue = pEdgeMethod->m_strValue;
	pDvmData->AddNewChild(pMethod);
	CEdgeData* pEdgeData = (CEdgeData*)pParaDatas->FindByID(EDGE_PROCEDURE_VAR_data);
	if(!pEdgeData)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_data == NULL"));
		return pDvmDataset;
	}

	POS pos = pEdgeData->GetHeadPosition();
	while (pos)
	{
		CExBaseList* pData = (CExBaseList*)pEdgeData->GetNext(pos);
		if(pData->GetClassID() == EDGECMDCLASSID_CEDGEPARADATA)
		{
			CDvmValue* pValue = new CDvmValue;
			pValue->m_strID = pValue->m_strName = pData->m_strID;
			pValue->m_strValue = ((CEdgeParaData*)pData)->m_strValue;
			pDvmData->AddNewChild(pValue);
		}
	}
	pDvmDataset->AddNewChild(pDvmData);
	return pDvmDataset;
}

/*----------------------------------------------------------------------\
UpdateDataset函数用于将报文类内数据转化为数据集数据
$pParaDatas: EdgeCmd所带的数据
$strProcedureID: 通过过程ID获取对应数据集,并通过UpdataDvmDataset进行更新
\----------------------------------------------------------------------*/
CDvmDataset* CIotEdgeProtoServerBase::UpdateDataset(CEdgeParaDatas* pParaDatas, CString& strProcedureID)
{
	if(!pParaDatas && strProcedureID != EDGE_PROCEDURE_ID_DEV_EVENT_HEARTBEAT)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("para:{} not found!"));
		return 0;
	}

	CDvmDataset* pDvmDataset = GetDvmDataset(strProcedureID);
	UpdataDvmDataset(pDvmDataset, pParaDatas);

	return pDvmDataset;
}

void CIotEdgeProtoServerBase::UpdateDataset(CEdgeParaDatas* pParas, CExBaseList* pDvmDataset)
{
	POS pos = pParas->GetHeadPosition();
	while (pos)
	{
		CEdgeParaData* pData = (CEdgeParaData*)pParas->GetNext(pos);
		CExBaseList* pDvm = (CExBaseList*)pDvmDataset->FindByID(pData->m_strID);
		if(pDvm->GetClassID() == DVMCLASSID_CDVMDATA)
		{
			((CDvmData*)pDvm)->m_strValue = pData->m_strValue;
		}
		else if (pDvm->GetClassID() == DVMCLASSID_CDVMVALUE)
		{
			((CDvmValue*)pDvm)->m_strValue = pData->m_strValue;
		}
	}
}

CDvmDataset* CIotEdgeProtoServerBase::UpdateDataset_Service_Cmd_Service(CEdgeParas* pParas, CString& strProcedureID)
{
	if(!pParas)
	{
		CLogPrint::LogFormatString(XLOGLEVEL_TRACE, _T("para:{} not found!"));
		return 0;
	}

	CDvmDataset* pDvmDataset = GetDvmDataset(strProcedureID);
	if(strProcedureID == EDGE_PROCEDURE_ID_APPDir_Get)
	{	
		UpdateDataset_Service_Cmd_Service_APPDir(pParas, pDvmDataset);
	}
	else if(strProcedureID == EDGE_PROCEDURE_ID_APPHFile_Get)
	{
		UpdateDataset_Service_Cmd_Service_APPHFile(pParas, pDvmDataset);
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_APP_CONFIG_Dir_Get)
	{
		UpdateDataset_Service_Cmd_Service_APPConfigDirGet(pParas, pDvmDataset);
	}
	else if (strProcedureID == EDGE_PROCEDURE_ID_CMD_GET_APP_CONFIG)
	{
		UpdateDataset_Service_Cmd_Service_CmdGetAppConfig(pParas, pDvmDataset);
	}
	else
	{
		UpdateDataset(pParas, pDvmDataset);
	}

	return pDvmDataset;
}

void CIotEdgeProtoServerBase::UpdataDataset_Service(CExBaseList* pList, const CString& strID, const CString& strValue)
{
	POS pos = pList->GetHeadPosition();
	while (pos)
	{
		CExBaseList* pChild = (CExBaseList*)pList->GetNext(pos);
		if(pChild->FindByID(strID))
		{
			CDvmData* pData = (CDvmData*)pChild->FindByID(strID);
			pData->m_strValue = strValue;
		}
	}
}

BOOL CIotEdgeProtoServerBase::UpdateDataset_Service_Cmd_Service_APPDir(CEdgeParas* pParas, CDvmDataset* pDvmDataset)
{
	CEdgeDirResp* pDirResp = pParas->GetEdgeDirResp();
	CDvmData* pDirRespData = (CDvmData*)pDvmDataset->FindByID(pDirResp->m_strID);
	UpdateDataset(pDirResp, pDirRespData);
	return TRUE;
}

BOOL CIotEdgeProtoServerBase::UpdateDataset_Service_Cmd_Service_APPHFile(CEdgeParas* pParas, CDvmDataset* pDvmDataset)
{
	CDvmData* pDvmData = (CDvmData*)pDvmDataset->FindByID(EDGE_PROCEDURE_VAR_DirResp);
	CEdgeParaDatas* pDirResp = (CEdgeParaDatas*)pParas->FindByID(EDGE_PROCEDURE_VAR_DirResp);
	if(!pDvmData || !pDirResp)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_DirResp | EDGE_PROCEDURE_VAR_DirResp == NULL"));
		return FALSE;
	}

	POS pos = pDirResp->GetHeadPosition();
	while (pos)
	{
		CEdgeParaData* pData = (CEdgeParaData*)pDirResp->GetNext(pos);
		CExBaseList* pDvm = (CExBaseList*)pDvmData->FindByID(pData->m_strID);
		if (pDvm->GetClassID() == DVMCLASSID_CDVMVALUE)
		{
			((CDvmValue*)pDvm)->m_strValue = pData->m_strValue;
		}
	}
	return TRUE;
}

BOOL CIotEdgeProtoServerBase::UpdateDataset_Service_Cmd_Service_APPConfigDirGet(CEdgeParas* pParas, CDvmDataset* pDvmDataset)
{
	CDvmData* pDvmData = (CDvmData*)pDvmDataset->FindByID(EDGE_PROCEDURE_VAR_DirResp); 
	if(!pDvmData)
	{
		CLogPrint::LogString(XLOGLEVEL_TRACE, _T("Ptr Error: EDGE_PROCEDURE_VAR_DirResp == NULL"));
		return FALSE;
	}

	pDvmData->DeleteChildren();
	CJSON* pChildJson = pParas->GetDirRespJson();
	if(!pChildJson)
	{
		return FALSE;
	}
	pChildJson = pChildJson->child;
	while(pChildJson != NULL)
	{
		CDvmValue* pDvmValue = (CDvmValue*)pDvmData->CreateNewChild(DVMCLASSID_CDVMVALUE);
		pDvmValue->m_strValue = pDvmValue->m_strID = pDvmValue->m_strName = pChildJson->valuestring;
		pDvmData->AddTail(pDvmValue);
		pChildJson = pChildJson->next;
	}
	return TRUE;
}

BOOL CIotEdgeProtoServerBase::UpdateDataset_Service_Cmd_Service_CmdGetAppConfig(CEdgeParas* pParas, CDvmDataset* pDvmDataset)
{
	UpdateDataset(pParas, pDvmDataset);

	//根据报告以及终端测试结果,body被去除
// 	CEdgeBody* pBody = pParas->GetEdgeBody();
// 	POS pos = pBody->GetHeadPosition();
// 	while (pos)
// 	{
// 		CEdgeParaData* pData = (CEdgeParaData*)pBody->GetNext(pos);
// 		if(CDvmData* pDvmData = (CDvmData*)pDvmDataset->FindByID(pData->m_strID))
// 		{
// 			pDvmData->m_strValue = pData->m_strValue;
// 		}
// 	}
	return TRUE;
}