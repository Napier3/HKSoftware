#include "stdafx.h"
#include "TcpEdgeProtocol.h"
#include "TcpEdgePrcdr_Read.h"
#include "Pkg/TcpEdgePkgData_TimeReadReq.h"
#include "Pkg/TcpEdgePkgData_DeviceInfoReq.h"
#include "Pkg/TcpEdgePkgData_DeviceStatusReq.h"
#include "../../../SttStudio/Module/SttGlobalDef.h"
#include "Pkg/TcpEdgePkgData_DeviceCtrlResp.h"
#include "Pkg/TcpEdgePkgData_TimeReadResp.h"
#include "Pkg/TcpEdgePkgData_DeviceInfoResp.h"
#include "Pkg/TcpEdgePkgData_DeviceStatusResp.h"
#include "Pkg/TcpEdgePkgData_GetModelResp.h"
#include "Pkg/TcpEdgePkgData_GetTopoFileResp.h"

CTcpEdgePrcdr_Read::CTcpEdgePrcdr_Read()
{

}

CTcpEdgePrcdr_Read::~CTcpEdgePrcdr_Read()
{

}

BOOL CTcpEdgePrcdr_Read::RunStepNull()
{
	//根据数据集、参数列表，拼报文发送
	CTcpEdgePkg* pPkg = new CTcpEdgePkg;
// 	if(m_strID.Find("Req") != -1
// 		|| m_strID == PkgData_GetModel)
// 	{
// 		pPkg->m_pPkgHead = ProduceHead(m_strID, PkgData_Value_CotReq);
// 	}
// 	else
// 	{
// 		pPkg->m_pPkgHead = ProduceHead(m_strID, PkgData_Value_CotResp);
// 	}
	pPkg->m_pPkgHead = ProduceHead(m_strID);
	pPkg->m_pPkgData = ProduceData(m_strID);
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

//处理应答报文逻辑
BOOL CTcpEdgePrcdr_Read::ProcessPackageDetail(CPxPkgBase *pPkgDetail)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;

	//判断回复报文是否属于该通道
	if(pPkg->m_nPort == m_nPort)
	{
		//判断回复报文是否属于该过程
		if((pPkg->m_strCmdID == PkgData_TimeReadResp && m_strID == PkgData_TimeReadReq)				//读装置时间
			|| (pPkg->m_strCmdID == PkgData_DeviceInfoResp && m_strID == PkgData_DeviceInfoReq)		//获取设备基本信息
			|| (pPkg->m_strCmdID == PkgData_DeviceStatusResp && m_strID == PkgData_DeviceStatusReq) //获取设备状态
			|| (pPkg->m_strCmdID == PkgData_GetModelResp && m_strID == PkgData_GetModel) 	
			|| (pPkg->m_strCmdID == PkgData_GetTopoFileResp && m_strID == PkgData_GetTopoFile))
		{
			//如果无其他处理,则设置结束标志
			UpdateFailErrorInfo(pPkgDetail, m_strID);
			UpdateRecord(pPkg);
			ProcessPackageFinished(pPkg);
			QString strLog = QString("[%1]测试结束...").arg(m_strID);
			emit sig_updateViewPkg(m_strIP, strLog, 0);
			return TRUE;
		}
	}

	SetProcedureState(PrcdrState_Step_1);

	return FALSE;
}

void CTcpEdgePrcdr_Read::UpdateFailErrorInfo(CPxPkgBase *pPkgDetail, CString strID)
{
	CTcpEdgePkg* pPkg = (CTcpEdgePkg*)pPkgDetail;

	CTcpEdgePkgData* pData = pPkg->m_pPkgData;

	if(pPkgDetail->m_strCmdID == PkgData_TimeReadResp)          //读时间
	{
		CTcpEdgePkgData_TimeReadResp* pDataResp = (CTcpEdgePkgData_TimeReadResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	if(pPkgDetail->m_strCmdID == PkgData_DeviceInfoResp)          
	{
		CTcpEdgePkgData_DeviceInfoResp* pDataResp = (CTcpEdgePkgData_DeviceInfoResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	if(pPkgDetail->m_strCmdID == PkgData_DeviceStatusResp)          
	{
		CTcpEdgePkgData_DeviceStatusResp* pDataResp = (CTcpEdgePkgData_DeviceStatusResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	if(pPkgDetail->m_strCmdID == PkgData_GetModelResp)          
	{
		CTcpEdgePkgData_GetModelResp* pDataResp = (CTcpEdgePkgData_GetModelResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}
	if(pPkgDetail->m_strCmdID == PkgData_GetTopoFileResp)          
	{
		CTcpEdgePkgData_GetTopoFileResp* pDataResp = (CTcpEdgePkgData_GetTopoFileResp*)pPkg->m_pPkgData;
		UpdateErrInfo(pDataResp->m_strNecessityLack, pDataResp->m_strNecessityErr, pDataResp->m_strRangeOut, pDataResp->m_strReturnFalse);
	}

}

void CTcpEdgePrcdr_Read::UpdateErrInfo(QString strNecessityLack, QString strNecessityErr, QString strRangeOut, QString strReturnFalse)
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

