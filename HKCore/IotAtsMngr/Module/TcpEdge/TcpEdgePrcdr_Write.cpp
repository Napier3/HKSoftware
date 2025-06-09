#include "stdafx.h"
#include "TcpEdgePrcdr_Write.h"
#include "TcpEdgePrcdr_Read.h"
#include "TcpEdgeProtocol.h"
#include "TcpEdgePrcdrBase.h"
#include "Pkg/TcpEdgePkgData_TimeSyncReq.h"
#include "Pkg/TcpEdgePkgData_DeviceUpdateReq.h"
#include "Pkg/TcpEdgePkgData_DeviceUpdateStatusReq.h"
#include "Pkg/TcpEdgePkgData_DeviceCtrlReq.h"
#include "Pkg/TcpEdgePkgData_DeviceConfigReq.h"
#include "Pkg/TcpEdgePkgData_ConInstallReq.h"
#include "Pkg/TcpEdgePkgData_ConStatusReq.h"
#include "Pkg/TcpEdgePkgData_ConStartReq.h"
#include "Pkg/TcpEdgePkgData_ConStopReq.h"
#include "Pkg/TcpEdgePkgData_ConRestartReq.h"
#include "Pkg/TcpEdgePkgData_ConRemoveReq.h"
#include "Pkg/TcpEdgePkgData_ConGetConfigReq.h"
#include "Pkg/TcpEdgePkgData_ConSetConfigReq.h"
#include "Pkg/TcpEdgePkgData_ModelChange.h"
#include "Pkg/TcpEdgePkgData_DevAdd.h"
#include "Pkg/TcpEdgePkgData_DevUpdate.h"
#include "Pkg/TcpEdgePkgData_ModelDevRead.h"
#include "Pkg/TcpEdgePkgData_DataSubs.h"
#include "Pkg/TcpEdgePkgData_GetDataSubs.h"
#include "Pkg/TcpEdgePkgData_DataSpont.h"
#include "Pkg/TcpEdgePkgData_DataRead.h"
#include "Pkg/TcpEdgePkgData_ParaRead.h"
#include "Pkg/TcpEdgePkgData_ParaCancel.h"
#include "Pkg/TcpEdgePkgData_ParaActivate.h"
#include "Pkg/TcpEdgePkgData_AppSetConfigReq.h"
#include "Pkg/TcpEdgePkgData_AppGetConfigReq.h"
#include "Pkg/TcpEdgePkgData_AppDisableReq.h"
#include "Pkg/TcpEdgePkgData_AppEnableReq.h"
#include "Pkg/TcpEdgePkgData_AppRemoveReq.h"
#include "Pkg/TcpEdgePkgData_AppStopReq.h"
#include "Pkg/TcpEdgePkgData_AppStartReq.h"
#include "Pkg/TcpEdgePkgData_AppStatusReq.h"
#include "Pkg/TcpEdgePkgData_AppInstallReq.h"
#include "Pkg/TcpEdgePkgData_CtrlCmdResp.h"
#include "Pkg/TcpEdgePkgData_ParaSetResp.h"
#include "Pkg/TcpEdgePkgData_CtrlCmd.h"
#include "Pkg/TcpEdgePkgData_ParaSet.h"
#include "Pkg/TcpEdgePkgData_DeviceUpdateResp.h"
#include "Pkg/TcpEdgePkgData_AppInstallResp.h"
#include "Pkg/TcpEdgePkgData_AppInstallStatusReq.h"
#include "Pkg/TcpEdgePkgData_Health.h"
#include "Pkg/TcpEdgePkgData_DeviceCtrlResp.h"
#include "Pkg/TcpEdgePkgData_DeviceConfigResp.h"
#include "Pkg/TcpEdgePkgData_TimeSyncResp.h"
#include "Pkg/TcpEdgePkgData_ConInstallResp.h"
#include "Pkg/TcpEdgePkgData_ConStartResp.h"
#include "Pkg/TcpEdgePkgData_ConStopResp.h"
#include "Pkg/TcpEdgePkgData_ConRestartResp.h"
#include "Pkg/TcpEdgePkgData_ConRemoveResp.h"
#include "Pkg/TcpEdgePkgData_ConSetConfigResp.h"
#include "Pkg/TcpEdgePkgData_AppStartResp.h"
#include "Pkg/TcpEdgePkgData_AppStopResp.h"
#include "Pkg/TcpEdgePkgData_AppRemoveResp.h"
#include "Pkg/TcpEdgePkgData_AppDisableResp.h"
#include "Pkg/TcpEdgePkgData_AppEnableResp.h"
#include "Pkg/TcpEdgePkgData_AppSetConfigResp.h"
#include "Pkg/TcpEdgePkgData_ParaCancelResp.h"
#include "Pkg/TcpEdgePkgData_ParaActivateResp.h"
#include "Pkg/TcpEdgePkgData_GetHisEventResp.h"
#include "../../../SttStudio/Module/SttGlobalDef.h"
#include <map>
#include "Pkg/TcpEdgePkgData_ConGetConfigResp.h"
#include "Pkg/TcpEdgePkgData_GetHisDataResp.h"
#include "Pkg/TcpEdgePkgData_GetMessageResp.h"
#include "Pkg/TcpEdgePkgData_AppStatusResp.h"
#include "Pkg/TcpEdgePkgData_AppGetConfigResp.h"
#include "Pkg/TcpEdgePkgData_ParaReadResp.h"
#include "Pkg/TcpEdgePkgData_DataReadResp.h"
#include "Pkg/TcpEdgePkgData_DataSpontResp.h"
#include "Pkg/TcpEdgePkgData_DataSubsResp.h"
#include "Pkg/TcpEdgePkgData_ModelDevReadResp.h"
#include "Pkg/TcpEdgePkgData_DevUpdateResp.h"
#include "Pkg/TcpEdgePkgData_DevAddResp.h"
#include "Pkg/TcpEdgePkgData_ModelChangeResp.h"
#include "Pkg/TcpEdgePkgData_ConStatusResp.h"
#include "Pkg/TcpEdgePkgData_GetDataSubsResp.h"

CTcpEdgePrcdr_Write::CTcpEdgePrcdr_Write()
{

}

CTcpEdgePrcdr_Write::~CTcpEdgePrcdr_Write()
{

}

BOOL CTcpEdgePrcdr_Write::RunStepNull()
{
	//根据数据集、参数列表，拼报文发送
	CTcpEdgePkg* pPkg = new CTcpEdgePkg;
// 	if(m_strID.Find("Req") != -1)
// 	{
// 		pPkg->m_pPkgHead = ProduceHead(m_strID, PkgData_Value_CotReq);
// 	}
// 	else
// 	{
// 		pPkg->m_pPkgHead = ProduceHead(m_strID, PkgData_Value_CotResp);
// 	}
	pPkg->m_pPkgHead = ProduceHead(m_strID);
	pPkg->m_pPkgData = ProduceData(m_strID);

	if (m_strID == PkgData_ParaSet)
	{
		CTcpEdgePkgData_ParaSet* pParaSetData = (CTcpEdgePkgData_ParaSet*)pPkg->m_pPkgData;
		m_strParaSetID = pParaSetData->m_strSetId;
	}

	if(pPkg->m_pPkgData)
	{
		QByteMap map;
		QByteMap mapASDU = Produce(pPkg, map);
		UpdateDataset(m_strID, mapASDU);
		Send(map, m_strID, m_nPort);
	}
	else
	{
		delete pPkg;
	}

	SetProcedureState(PrcdrState_Step_1);
	//重新设置超时
	ResetTimer();
	m_nOverTimeLong = 60000;
	return FALSE;
}

BOOL CTcpEdgePrcdr_Write::ProcessPackageAck(CPxPkgBase *pPkgDetail)
{
	SetProcedureState(PrcdrState_Step_End);
	return FALSE;
}


BOOL CTcpEdgePrcdr_Write::ProcessPackageDetail(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;
	if(pPkg->m_nPort == m_nPort)
	{
		//判断回复报文是否属于该过程
		if((pPkg->m_strCmdID == PkgData_TimeSyncResp && m_strID == PkgData_TimeSyncReq)
			|| (pPkg->m_strCmdID == PkgData_DeviceCtrlResp && m_strID == PkgData_DeviceCtrlReq)   		//设备控制
			|| (pPkg->m_strCmdID == PkgData_DeviceConfigResp && m_strID == PkgData_DeviceConfigReq)     //设备配置参数修改
			|| (pPkg->m_strCmdID == PkgData_ConInstallResp && m_strID == PkgData_ConInstallReq)			//容器安装 
			|| (pPkg->m_strCmdID == PkgData_ConStatusResp && m_strID == PkgData_ConStatusReq)			//容器状态查询
			|| (pPkg->m_strCmdID == PkgData_ConStartResp && m_strID == PkgData_ConStartReq)				//容器启动
			|| (pPkg->m_strCmdID == PkgData_ConStopResp && m_strID == PkgData_ConStopReq)				//容器停止			
			|| (pPkg->m_strCmdID == PkgData_ConRestartResp && m_strID == PkgData_ConRestartReq)			//容器重启
			|| (pPkg->m_strCmdID == PkgData_ConRemoveResp && m_strID == PkgData_ConRemoveReq)			//容器删除
			|| (pPkg->m_strCmdID == PkgData_ConGetConfigResp && m_strID == PkgData_ConGetConfigReq)		//容器配置查询
			|| (pPkg->m_strCmdID == PkgData_ConSetConfigResp && m_strID == PkgData_ConSetConfigReq)		//容器配置修改
			|| (pPkg->m_strCmdID == PkgData_ModelChangeResp && m_strID == PkgData_ModelChange)			//模型变化报告
			|| (pPkg->m_strCmdID == PkgData_DevAddResp && m_strID == PkgData_DevAdd)					//添加子设备
			|| (pPkg->m_strCmdID == PkgData_DevUpdateResp && m_strID == PkgData_DevUpdate)				//更新子设备状态
			|| (pPkg->m_strCmdID == PkgData_ModelDevReadResp && m_strID == PkgData_ModelDevRead)		//子设备信息查询
			|| (pPkg->m_strCmdID == PkgData_DataSubsResp && m_strID == PkgData_DataSubs)				//数据订阅
			|| (pPkg->m_strCmdID == PkgData_GetDataSubsResp && m_strID == PkgData_GetDataSubs)			//数据订阅查询
			|| (pPkg->m_strCmdID ==  PkgData_DataSpontResp&& m_strID == PkgData_DataSpont)				//数据主动上报
			|| (pPkg->m_strCmdID == PkgData_DataReadResp && m_strID == PkgData_DataRead)				//数据查询
			|| (pPkg->m_strCmdID == PkgData_ParaReadResp && m_strID == PkgData_ParaRead)	
			|| (pPkg->m_strCmdID == PkgData_CtrlCmdResp && m_strID == PkgData_CtrlCmd)
			|| (pPkg->m_strCmdID == PkgData_ParaSetResp && m_strID == PkgData_ParaSet)					//参数、定值查询
			|| (pPkg->m_strCmdID == PkgData_ParaCancelResp && m_strID == PkgData_ParaCancel)			//撤销参数定值预置
			|| (pPkg->m_strCmdID == PkgData_ParaActivateResp && m_strID == PkgData_ParaActivate)		//参数、定值激活
			|| (pPkg->m_strCmdID == PkgData_AppSetConfigResp && m_strID == PkgData_AppSetConfigReq)		//应用配置修改
			|| (pPkg->m_strCmdID == PkgData_AppGetConfigResp && m_strID == PkgData_AppGetConfigReq)		//应用配置查询
			|| (pPkg->m_strCmdID == PkgData_AppDisableResp && m_strID == PkgData_AppDisableReq)			//应用去使能
			|| (pPkg->m_strCmdID == PkgData_AppEnableResp && m_strID == PkgData_AppEnableReq)			//应用使能
			|| (pPkg->m_strCmdID == PkgData_AppRemoveResp && m_strID == PkgData_AppRemoveReq)			//应用卸载
			|| (pPkg->m_strCmdID == PkgData_AppStopResp && m_strID == PkgData_AppStopReq)				//应用停止
			|| (pPkg->m_strCmdID == PkgData_AppStartResp && m_strID == PkgData_AppStartReq)				//应用启动
			|| (pPkg->m_strCmdID == PkgData_AppStatusResp && m_strID == PkgData_AppStatusReq)			//应用状态查询
			|| (pPkg->m_strCmdID == PkgData_GetHisDataResp && m_strID == PkgData_GetHisData)			//历史数据查询))
			|| (pPkg->m_strCmdID == PkgData_GetMessageResp && m_strID == PkgData_GetMessage))
		{
			UpdateRecord(pPkg);
 			FailErrorInfo(pPkgDetail, m_strID);
			//如果无其他处理,则设置结束标志
			ProcessPackageFinished(pPkg);
			QString strLog = QString("[%1]测试结束...").arg(m_strID);
			emit sig_updateViewPkg(m_strIP, strLog, 0);
			return TRUE;
		}
		else if(pPkg->m_strCmdID == PkgData_GetHisEventResp && m_strID == PkgData_GetHisEvent)
		{
			FailErrorInfo(pPkgDetail, m_strID);
			CTcpEdgePkgData_GetHisEventResp* pData = (CTcpEdgePkgData_GetHisEventResp*)pPkg->m_pPkgData;
			if(pData->m_strContinue == "0")
			{
				ProcessPackageFinished(pPkgDetail);
				QString strLog = QString("[%1]测试结束...").arg(m_strID);
				emit sig_updateViewPkg(m_strIP, strLog, 0);
				return TRUE;
			}
			else
			{
				pPkgDetail->SetPkgState(PX_PKG_STATE_CAN_DELETE);
			}
		}
	}

	SetProcedureState(PrcdrState_Step_1);

	return FALSE;
}

BOOL CTcpEdgePrcdr_Write::ProcessCtrlCmd(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;
	CTcpEdgePkgData_CtrlCmdResp* pData = (CTcpEdgePkgData_CtrlCmdResp*)pPkg->m_pPkgData;
	if (pData->m_strCtrlType == "0")
	{
		if(pData->m_strStatus == "0")
		{
			ProduceData_CtrlCmd("1", pData->m_strDeviceId, pData->m_strCtrlVal, pData->m_strDataRefer);
		}
		else if(pData->m_strStatus == "1")
		{
			ProduceData_CtrlCmd("2",pData->m_strDeviceId, pData->m_strCtrlVal, pData->m_strDataRefer);
		}
	}
	else if (pData->m_strCtrlType == "3")
	{
		if (pData->m_strStatus == "0")
		{
			ProduceData_CtrlCmd("4",pData->m_strDeviceId, pData->m_strCtrlVal, pData->m_strDataRefer);
		}
		else if (pData->m_strStatus == "1")
		{
			ProduceData_CtrlCmd("5",pData->m_strDeviceId, pData->m_strCtrlVal, pData->m_strDataRefer);
		}
	}
	else if (pData->m_strCtrlType == "1"
	||pData->m_strCtrlType == "2"
	||pData->m_strCtrlType == "4"
	||pData->m_strCtrlType == "5"
	||pData->m_strCtrlType == "6"
	||pData->m_strCtrlType == "7")
	{
		return FALSE; 
	}
	return TRUE;
}

BOOL CTcpEdgePrcdr_Write::ProcessParaSet(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;
	CTcpEdgePkgData_ParaSetResp* pData = (CTcpEdgePkgData_ParaSetResp*)pPkg->m_pPkgData;
	if (pData->m_strStatus == "0")
	{
		CTcpEdgePkg* pPkg = new CTcpEdgePkg;
		if(m_strID.Find("Req") != -1)
		{
			pPkg->m_pPkgHead = ProduceHead(PkgData_ParaActivate, PkgData_Value_CotReq);
		}
		else
		{
			pPkg->m_pPkgHead = ProduceHead(PkgData_ParaActivate, PkgData_Value_CotResp);
		}
		CTcpEdgePkgData_ParaActivate* pParaActivateData = new CTcpEdgePkgData_ParaActivate;
		pParaActivateData->m_strDeviceId = pData->m_strDeviceId;
		pParaActivateData->m_strSetId = m_strParaSetID;
		pPkg->m_pPkgData = pParaActivateData;

		CDvmDataset* pTempDataset = m_pDvmDataset;
		m_pDvmDataset = pParaActivateData->ToDataset();
		CDvmData* pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_DeviceID);
		pDvmData->m_strValue = pParaActivateData->m_strDeviceId;
		pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_SetId);
		pDvmData->m_strValue = pParaActivateData->m_strSetId;

		QByteMap map;
		Produce(pPkg, map);
		delete m_pDvmDataset;
		m_pDvmDataset = pTempDataset;
		CDvmDataset* pDataset = (CDvmDataset*)m_pTcpProtocolRef->m_pDvmDevice->FindDataset(PkgData_ParaSet);
		m_pTcpProtocolRef->UpdateDataset(pDataset, PkgData_ParaActivate, m_strASDU);
		Send(map, PkgData_ParaActivate);
		delete pPkg;
	}
	else if (pData->m_strStatus == "1")
	{
		CTcpEdgePkg* pPkg = new CTcpEdgePkg;
		if(m_strID.Find("Req") != -1)
		{
			pPkg->m_pPkgHead = ProduceHead(PkgData_ParaCancel, PkgData_Value_CotReq);
		}
		else
		{
			pPkg->m_pPkgHead = ProduceHead(PkgData_ParaCancel, PkgData_Value_CotResp);
		}
		CTcpEdgePkgData_ParaCancel* pParaCancelData = new CTcpEdgePkgData_ParaCancel;
		pParaCancelData->m_strDeviceId = pData->m_strDeviceId;
		pParaCancelData->m_strSetId = m_strParaSetID;
		pPkg->m_pPkgData = pParaCancelData;

		CDvmDataset* pTempDataset = m_pDvmDataset;
		m_pDvmDataset = pParaCancelData->ToDataset();
		CDvmData* pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_DeviceID);
		pDvmData->m_strValue = pParaCancelData->m_strDeviceId;
		pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_SetId);
		pDvmData->m_strValue = pParaCancelData->m_strSetId;

		QByteMap map;
		Produce(pPkg, map);
		delete m_pDvmDataset;
		m_pDvmDataset = pTempDataset;
		CDvmDataset* pDataset = (CDvmDataset*)m_pTcpProtocolRef->m_pDvmDevice->FindDataset(PkgData_ParaSet);
		m_pTcpProtocolRef->UpdateDataset(pDataset, PkgData_ParaCancel, m_strASDU);
		Send(map, PkgData_ParaCancel);
		delete pPkg;
	}
	return TRUE;
}

BOOL CTcpEdgePrcdr_Write::ProduceData_CtrlCmd(CString strCtrlType,CString strDeviceID,CString strCtrlVal,CString strDataRefer)
{
	CTcpEdgePkg* pPkg = new CTcpEdgePkg;
	if(m_strID.Find("Req") != -1)
	{
		pPkg->m_pPkgHead = ProduceHead(PkgData_CtrlCmd, PkgData_Value_CotReq);
	}
	else
	{
		pPkg->m_pPkgHead = ProduceHead(PkgData_CtrlCmd, PkgData_Value_CotResp);
	}

	CTcpEdgePkgData_CtrlCmd* pData = new CTcpEdgePkgData_CtrlCmd;
	pData->m_strCtrlType = strCtrlType;
	pData->m_strDeviceId = strDeviceID;
	pData->m_strCtrlVal = strCtrlVal;
	pData->m_strDataRefer = strDataRefer;
	pPkg->m_pPkgData = pData;

	CDvmDataset* pTempDataset = m_pDvmDataset;
	m_pDvmDataset = pData->ToDataset();
	CDvmData* pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_CtrlType);
	pDvmData->m_strValue = pData->m_strCtrlType;
	pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_DeviceID);
	pDvmData->m_strValue = pData->m_strDeviceId;
	pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_CtrlVal);
	pDvmData->m_strValue = pData->m_strCtrlVal;
	pDvmData = (CDvmData*)m_pDvmDataset->FindByID(PkgData_Node_DataRefer);
	pDvmData->m_strValue = pData->m_strDataRefer;

	QByteMap map;
	Produce(pPkg, map);
	delete m_pDvmDataset;
	m_pDvmDataset = pTempDataset;
	CDvmDataset* pDataset = (CDvmDataset*)m_pTcpProtocolRef->m_pDvmDevice->FindDataset(PkgData_CtrlCmd);
	m_pTcpProtocolRef->UpdateDataset(pDataset, PkgData_CtrlCmd, m_strASDU);
	Send(map, PkgData_CtrlCmd);
	delete pPkg;
	return TRUE;
}

void CTcpEdgePrcdr_Write::FailErrorInfo(CPxPkgBase *pPkgDetail, CString strID)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;

	CTcpEdgePkgData* pData = pPkg->m_pPkgData;
	QString strTemp;

	if(pPkgDetail->m_strCmdID == PkgData_DeviceCtrlResp)          //设备控制
	{
		CTcpEdgePkgData_DeviceCtrlResp* pDataResp = (CTcpEdgePkgData_DeviceCtrlResp*)pPkg->m_pPkgData;
		strTemp  += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceCtrlResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceCtrlResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceCtrlResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_DeviceConfigResp)    //
	{
		CTcpEdgePkgData_DeviceConfigResp* pDataResp = (CTcpEdgePkgData_DeviceConfigResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceConfigResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceConfigResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_DeviceConfigResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_TimeSyncResp)    //装置对时
	{
		CTcpEdgePkgData_TimeSyncResp* pDataResp = (CTcpEdgePkgData_TimeSyncResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_TimeSyncResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_TimeSyncResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_TimeSyncResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ConInstallResp)    //容器安装
	{
		CTcpEdgePkgData_ConInstallResp* pDataResp = (CTcpEdgePkgData_ConInstallResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConInstallResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConInstallResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConInstallResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ConStartResp)    //容器启动
	{
		CTcpEdgePkgData_ConStartResp* pDataResp = (CTcpEdgePkgData_ConStartResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConStartResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConStartResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConStartResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ConStopResp)    //容器停止
	{
		CTcpEdgePkgData_ConStopResp* pDataResp = (CTcpEdgePkgData_ConStopResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConStopResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConStopResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConStopResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ConRestartResp)    //容器重启
	{
		CTcpEdgePkgData_ConRestartResp* pDataResp = (CTcpEdgePkgData_ConRestartResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConRestartResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConRestartResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConRestartResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ConRemoveResp)    //容器删除
	{
		CTcpEdgePkgData_ConRemoveResp* pDataResp = (CTcpEdgePkgData_ConRemoveResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConRemoveResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConRemoveResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConRemoveResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ConSetConfigResp)    //容器配置修改
	{
		CTcpEdgePkgData_ConSetConfigResp* pDataResp = (CTcpEdgePkgData_ConSetConfigResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConSetConfigResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConSetConfigResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ConSetConfigResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppStartResp)    //应用启动
	{
		CTcpEdgePkgData_AppStartResp* pDataResp = (CTcpEdgePkgData_AppStartResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppStartResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppStartResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppStartResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppStopResp)    //应用停止
	{
		CTcpEdgePkgData_AppStopResp* pDataResp = (CTcpEdgePkgData_AppStopResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppStopResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppStopResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppStopResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppRemoveResp)    //应用卸载
	{
		CTcpEdgePkgData_AppRemoveResp* pDataResp = (CTcpEdgePkgData_AppRemoveResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppRemoveResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppRemoveResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppRemoveResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppEnableResp)    //应用使能
	{
		CTcpEdgePkgData_AppEnableResp* pDataResp = (CTcpEdgePkgData_AppEnableResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppEnableResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppEnableResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppEnableResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppDisableResp)    //应用去使能
	{
		CTcpEdgePkgData_AppDisableResp* pDataResp = (CTcpEdgePkgData_AppDisableResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppDisableResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppSetConfigResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppSetConfigResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppSetConfigResp)    //应用配置修改
	{
		CTcpEdgePkgData_AppSetConfigResp* pDataResp = (CTcpEdgePkgData_AppSetConfigResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppSetConfigResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppSetConfigResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_AppSetConfigResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ParaCancelResp)
	{
		CTcpEdgePkgData_ParaCancelResp* pDataResp = (CTcpEdgePkgData_ParaCancelResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ParaCancelResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ParaCancelResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ParaCancelResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ParaActivateResp)
	{
		CTcpEdgePkgData_ParaActivateResp* pDataResp = (CTcpEdgePkgData_ParaActivateResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ParaActivateResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ParaActivateResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ParaActivateResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ParaSetResp)
	{
		CTcpEdgePkgData_ParaSetResp* pDataResp = (CTcpEdgePkgData_ParaSetResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ParaSetResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ParaSetResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_ParaSetResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_CtrlCmdResp)
	{
		CTcpEdgePkgData_CtrlCmdResp* pDataResp = (CTcpEdgePkgData_CtrlCmdResp*)pPkg->m_pPkgData;
		strTemp += FailErrorInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_CtrlCmdResp);
		pDataResp->m_strReturnFalse += ReurnFalseInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_CtrlCmdResp);
		pDataResp->m_strRangeOut += RangeOutInfo(pDataResp->m_strStatus, pDataResp->m_strErrorCode, pDataResp->m_strNote, PkgData_CtrlCmdResp);
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
		pDataResp->m_strErrorInfo += strTemp;
		strTemp = pDataResp->m_strErrorInfo;
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ConGetConfigResp)
	{
		CTcpEdgePkgData_ConGetConfigResp* pDataResp = (CTcpEdgePkgData_ConGetConfigResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ConStatusResp)
	{
		CTcpEdgePkgData_ConStatusResp* pDataResp = (CTcpEdgePkgData_ConStatusResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ModelChangeResp)
	{
		CTcpEdgePkgData_ModelChangeResp* pDataResp = (CTcpEdgePkgData_ModelChangeResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_DevAddResp)
	{
		CTcpEdgePkgData_DevAddResp* pDataResp = (CTcpEdgePkgData_DevAddResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_DevUpdateResp)
	{
		CTcpEdgePkgData_DevUpdateResp* pDataResp = (CTcpEdgePkgData_DevUpdateResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ModelDevReadResp)
	{
		CTcpEdgePkgData_ModelDevReadResp* pDataResp = (CTcpEdgePkgData_ModelDevReadResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_DataSubsResp)
	{
		CTcpEdgePkgData_DataSubsResp* pDataResp = (CTcpEdgePkgData_DataSubsResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_GetDataSubsResp)
	{
		CTcpEdgePkgData_GetDataSubsResp* pDataResp = (CTcpEdgePkgData_GetDataSubsResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_DataSpontResp)
	{
		CTcpEdgePkgData_DataSpontResp* pDataResp = (CTcpEdgePkgData_DataSpontResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_DataReadResp)
	{
		CTcpEdgePkgData_DataReadResp* pDataResp = (CTcpEdgePkgData_DataReadResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_ParaReadResp)
	{
		CTcpEdgePkgData_ParaReadResp* pDataResp = (CTcpEdgePkgData_ParaReadResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppGetConfigResp)
	{
		CTcpEdgePkgData_AppGetConfigResp* pDataResp = (CTcpEdgePkgData_AppGetConfigResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_AppStatusResp)
	{
		CTcpEdgePkgData_AppStatusResp* pDataResp = (CTcpEdgePkgData_AppStatusResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_GetHisDataResp)
	{
		CTcpEdgePkgData_GetHisDataResp* pDataResp = (CTcpEdgePkgData_GetHisDataResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else if(pPkgDetail->m_strCmdID == PkgData_GetMessageResp)
	{
		CTcpEdgePkgData_GetMessageResp* pDataResp = (CTcpEdgePkgData_GetMessageResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	else
	{
		return;
	}

	//更新到模型
	CDvmDataset* pDataset = (CDvmDataset*)m_pTcpProtocolRef->m_pDvmDevice->FindDataset(strID);
	CDvmData *pDvmData = (CDvmData *)pDataset->GetTail();
	pDvmData->m_strValue = strTemp;

// 	emit sig_updateViewPkg(m_strIP, strTemp, XERRTYPE_COMMON);
}

QString CTcpEdgePrcdr_Write::FailErrorInfo(CString strStatus, CString strErrorCode, CString strNote, CString strPkgID)
{
	QString strTemp;
	if(strStatus != "0")
	{
		if(strStatus == "1")
		{
			//失败
			strTemp = QString(_T("【执行失败】[%1]报文, 错误代码: [%2]; Note: [%3]; \n")).arg(strPkgID).arg(strErrorCode).arg(strNote);
		}
		else
		{
			strTemp = QString(_T("【错误】【超过范围】[%1]报文字段Status超出范围, 无法判断执行状态;\n")).arg(strPkgID);
		}
	}
	return strTemp;
}

QString CTcpEdgePrcdr_Write::ReurnFalseInfo(CString strStatus, CString strErrorCode, CString strNote, CString strPkgID)
{
	QString strTemp;
	if(strStatus != "0")
	{
		if(strStatus == "1")
		{
			//失败
			strTemp = QString(_T("【执行失败】[%1]报文, 错误代码: [%2]; Note: [%3]; \n")).arg(strPkgID).arg(strErrorCode).arg(strNote);
		}
	}
	return strTemp;
}

QString CTcpEdgePrcdr_Write::RangeOutInfo(CString strStatus, CString strErrorCode, CString strNote, CString strPkgID)
{
	QString strTemp;
	if(strStatus != "0")
	{
		if(strStatus != "1")
		{
			strTemp = QString(_T("【错误】【超过范围】[%1]报文字段Status超出范围, 无法判断执行状态;\n")).arg(strPkgID);
		}
	}
	return strTemp;
}

void CTcpEdgePrcdr_Write::UpdateErrInfo(QString strNecessityLack, QString strNecessityErr, QString strRangeOut, QString strReturnFalse)
{
	if (strNecessityLack != "")
	{
		emit sig_updateViewPkg(m_strIP, strNecessityLack,XERRTYPE_LACKNECESSITY);
	}
	if (strNecessityErr != "")
	{
		emit sig_updateViewPkg(m_strIP, strNecessityErr, XERRTYPE_NECESSITYERR);

	}
	if (strReturnFalse != "")
	{
		emit sig_updateViewPkg(m_strIP, strReturnFalse, XERRTYPE_RETURNFALSE);
	}
	if (strRangeOut != "")
	{	
		emit sig_updateViewPkg(m_strIP,strRangeOut,XERRTYPE_RANGEOUT);
	}
}
