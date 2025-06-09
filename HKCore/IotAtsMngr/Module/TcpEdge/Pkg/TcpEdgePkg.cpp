#include "stdafx.h"
#include "TcpEdgePkg.h"
#include "../TcpEdgeGlobalDef.h"

#include "TcpEdgePkgData_TimeSyncReq.h"
#include "TcpEdgePkgData_TimeSyncResp.h"
#include "TcpEdgePkgData_TimeReadReq.h"
#include "TcpEdgePkgData_TimeReadResp.h"
#include "TcpEdgePkgData_DeviceUpdateReq.h"
#include "TcpEdgePkgData_DeviceUpdateResp.h"
#include "TcpEdgePkgData_DeviceUpdateStatusReq.h"
#include "TcpEdgePkgData_DeviceUpdateStatusResp.h"
#include "TcpEdgePkgData_DeviceUpdateResult.h"

#include "TcpEdgePkgData_DeviceCtrlReq.h"
#include "TcpEdgePkgData_DeviceCtrlResp.h"
#include "TcpEdgePkgData_DeviceInfoReq.h"
#include "TcpEdgePkgData_DeviceInfoResp.h"
#include "TcpEdgePkgData_DeviceStatusReq.h"
#include "TcpEdgePkgData_DeviceStatusResp.h"
#include "TcpEdgePkgData_DeviceConfigReq.h"
#include "TcpEdgePkgData_DeviceConfigResp.h"
#include "TcpEdgePkgData_SysAlarm.h"

#include "TcpEdgePkgData_DeviceCtrlReq.h"
#include "TcpEdgePkgData_DeviceConfigReq.h"
#include "TcpEdgePkgData_ConInstallReq.h"
#include "TcpEdgePkgData_ConStatusReq.h"
#include "TcpEdgePkgData_ConStartReq.h"
#include "TcpEdgePkgData_ConStopReq.h"
#include "TcpEdgePkgData_ConRestartReq.h"
#include "TcpEdgePkgData_ConRemoveReq.h"
#include "TcpEdgePkgData_ConGetConfigReq.h"
#include "TcpEdgePkgData_ConSetConfigReq.h"

#include "TcpEdgePkgData_DeviceCtrlResp.h"
#include "TcpEdgePkgData_DeviceConfigResp.h"
#include "TcpEdgePkgData_ConInstallResp.h"
#include "TcpEdgePkgData_ConStatusResp.h"
#include "TcpEdgePkgData_ConStartResp.h"
#include "TcpEdgePkgData_ConStopResp.h"
#include "TcpEdgePkgData_ConRestartResp.h"
#include "TcpEdgePkgData_ConRemoveResp.h"
#include "TcpEdgePkgData_ConGetConfigResp.h"
#include "TcpEdgePkgData_ConSetConfigResp.h"
#include "TcpEdgePkgData_ConAlarm.h"

#include "TcpEdgePkgData_ModelChange.h"
#include "TcpEdgePkgData_ModelChangeResp.h"
#include "TcpEdgePkgData_DevAdd.h"
#include "TcpEdgePkgData_DevAddResp.h"
#include "TcpEdgePkgData_DevUpdate.h"
#include "TcpEdgePkgData_DevUpdateResp.h"
#include "TcpEdgePkgData_ModelDevRead.h"
#include "TcpEdgePkgData_ModelDevReadResp.h"
#include "TcpEdgePkgData_DataSubs.h"
#include "TcpEdgePkgData_DataSubsResp.h"
#include "TcpEdgePkgData_GetDataSubs.h"
#include "TcpEdgePkgData_GetDataSubsResp.h"
#include "TcpEdgePkgData_DataSpont.h"
#include "TcpEdgePkgData_DataSpontResp.h"
#include "TcpEdgePkgData_DataRead.h"
#include "TcpEdgePkgData_DataReadResp.h"
#include "TcpEdgePkgData_ParaRead.h"
#include "TcpEdgePkgData_ParaReadResp.h"
#include "TcpEdgePkgData_FileGet.h"
#include "TcpEdgePkgData_FileGetResp.h"
#include "TcpEdgePkgData_FileDataTrans.h"
#include "TcpEdgePkgData_FileDataTransResp.h"
#include "TcpEdgePkgData_DeviceGetLogReq.h"
#include "TcpEdgePkgData_DeviceGetLogResp.h"
#include "TcpEdgePkgData_ContGetLogReq.h"
#include "TcpEdgePkgData_ContGetLogResp.h"
#include "TcpEdgePkgData_AppGetLogReq.h"
#include "TcpEdgePkgData_AppGetLogResp.h"
#include "TcpEdgePkgData_ParaSet.h"
#include "TcpEdgePkgData_AppAlarm.h"
#include "TcpEdgePkgData_AppSetConfigResp.h"
#include "TcpEdgePkgData_AppSetConfigReq.h"
#include "TcpEdgePkgData_AppGetConfigResp.h"
#include "TcpEdgePkgData_AppGetConfigReq.h"
#include "TcpEdgePkgData_AppDisableResp.h"
#include "TcpEdgePkgData_AppDisableReq.h"
#include "TcpEdgePkgData_AppEnableResp.h"
#include "TcpEdgePkgData_AppEnableReq.h"
#include "TcpEdgePkgData_AppRemoveResp.h"
#include "TcpEdgePkgData_AppRemoveReq.h"
#include "TcpEdgePkgData_AppStopResp.h"
#include "TcpEdgePkgData_AppStopReq.h"
#include "TcpEdgePkgData_AppStartResp.h"
#include "TcpEdgePkgData_AppStartReq.h"
#include "TcpEdgePkgData_AppStatusResp.h"
#include "TcpEdgePkgData_AppStatusReq.h"
#include "TcpEdgePkgData_AppInstallResult.h"
#include "TcpEdgePkgData_AppInstallStatusResp.h"
#include "TcpEdgePkgData_AppInstallStatusReq.h"
#include "TcpEdgePkgData_AppInstallResp.h"
#include "TcpEdgePkgData_AppInstallReq.h"
#include "TcpEdgePkgData_GetHisData.h"
#include "TcpEdgePkgData_GetHisDataResp.h"
#include "TcpEdgePkgData_ParaCancel.h"
#include "TcpEdgePkgData_ParaCancelResp.h"
#include "TcpEdgePkgData_ParaActivate.h"
#include "TcpEdgePkgData_ParaActivateResp.h"
#include "TcpEdgePkgData_ParaSetResp.h"
#include "TcpEdgePkgData_CtrlCmd.h"
#include "TcpEdgePkgData_CtrlCmdResp.h"
#include "TcpEdgePkgData_GetTopoFile.h"
#include "TcpEdgePkgData_GetTopoFileResp.h"
#include "TcpEdgePkgData_GetHisEventResp.h"
#include "TcpEdgePkgData_GetHisEvent.h"
#include "TcpEdgePkgData_AppSetCfgFileResp.h"
#include "TcpEdgePkgData_AppSetCfgFileReq.h"
#include "TcpEdgePkgData_AppGetCfgFileResp.h"
#include "TcpEdgePkgData_AppGetCfgFileReq.h"
#include "TcpEdgePkgData_GetModel.h"
#include "TcpEdgePkgData_GetMessage.h"
#include "TcpEdgePkgData_GetMessageResp.h"
#include "TcpEdgePkgData_GetModelResp.h"

#ifdef _DEBUG
#undef THIS_FILE
	static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CTcpEdgePkg::CTcpEdgePkg()
{
	m_nPort = 0;
	m_pPkgHead = NULL;
	m_pPkgData = NULL;
}

CTcpEdgePkg::~CTcpEdgePkg()
{
	if(m_pPkgHead)
	{
		delete m_pPkgHead;
		m_pPkgHead = NULL;
	}

	if(m_pPkgData)
	{
		delete m_pPkgData;
		m_pPkgData = NULL;
	}
}

long CTcpEdgePkg::XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgBase::XmlReadOwn(oNode, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	CJSON* pJson = ((CJsonNode*)&oNode)->m_pJsonNode;
	char* pStrJson = CJSON_Print(pJson);
	Parser(pStrJson);

	return 0;
}

long CTcpEdgePkg::XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys)
{
	CTcpEdgePkgBase::XmlWriteOwn(oXMLDoc, oElement, pXmlRWKeys);
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;

	return 0;
}

long CTcpEdgePkg::SerializeOwn(CBinarySerialBuffer &oBinaryBuffer)
{
	CTcpEdgePkgBase::SerializeOwn(oBinaryBuffer);
	if(oBinaryBuffer.IsCalSizeMode())
	{
	}
	else if(oBinaryBuffer.IsReadMode())
	{
	}
	else if(oBinaryBuffer.IsWriteMode())
	{
	}
	return 0;
}

void CTcpEdgePkg::InitAfterRead()
{
}

BOOL CTcpEdgePkg::IsEqualOwn(CBaseObject* pObj)
{
	if(this == pObj)
	{
		return TRUE;
	}

	if (!CTcpEdgePkgBase::IsEqualOwn(pObj))
	{
		return FALSE;
	}

	CTcpEdgePkg *p = (CTcpEdgePkg*)pObj;

	return TRUE;
}

BOOL CTcpEdgePkg::CopyOwn(CBaseObject* pDest)
{
	if(this == pDest)
	{
		return TRUE;
	}

	CTcpEdgePkgBase::CopyOwn(pDest);

	CTcpEdgePkg *p = (CTcpEdgePkg*)pDest;

	return TRUE;
}

CBaseObject* CTcpEdgePkg::Clone()
{
	CTcpEdgePkg *p = new CTcpEdgePkg();
	Copy(p);
	return p;
}

CBaseObject* CTcpEdgePkg::CloneEx(BOOL bCopyOwn/*=TRUE*/, BOOL bCopyChildren/*=FALSE*/)
{
	CTcpEdgePkg *p = new CTcpEdgePkg();
	CopyEx(p, bCopyOwn, bCopyChildren);
	return p;
}

BOOL CTcpEdgePkg::CanPaste(UINT nClassID)
{
	return FALSE;
}

CExBaseObject* CTcpEdgePkg::CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys)
{
	CExBaseObject *pNew  = NULL;
	CTcpEdgePkgXmlRWKeys *pXmlKeys = (CTcpEdgePkgXmlRWKeys*)pXmlRWKeys;



	return pNew;
}

CExBaseObject* CTcpEdgePkg::CreateNewChild(long nClassID/*, BOOL &bAddToTail*/)
{
	CExBaseObject *pNew  = NULL;



	return pNew;
}

CTcpEdgePkgData* CTcpEdgePkg::CreatePkgDataByID(const CString& strPrcdrID, char* pDataJson)
{
	CTcpEdgePkgData* pData = NULL;
	if(strPrcdrID == PkgData_TimeSyncReq)
	{
		pData = new CTcpEdgePkgData_TimeSyncReq();
	}
	else if(strPrcdrID == PkgData_TimeSyncResp)
	{
		pData = new CTcpEdgePkgData_TimeSyncResp();
	}
	else if(strPrcdrID == PkgData_TimeReadReq)
	{
		pData = new CTcpEdgePkgData_TimeReadReq();
	}
	else if(strPrcdrID == PkgData_TimeReadResp)
	{
		pData = new CTcpEdgePkgData_TimeReadResp();
	}
	else if(strPrcdrID == PkgData_DeviceUpdateReq)
	{
		pData = new CTcpEdgePkgData_DeviceUpdateReq();
	}
	else if(strPrcdrID == PkgData_DeviceUpdateResp)
	{
		pData = new CTcpEdgePkgData_DeviceUpdateResp();
	}
	else if(strPrcdrID == PkgData_DeviceUpdateStatusReq)
	{
		pData = new CTcpEdgePkgData_DeviceUpdateStatusReq();
	}
	else if(strPrcdrID == PkgData_DeviceUpdateStatusResp)
	{
		pData = new CTcpEdgePkgData_DeviceUpdateStatusResp();
	}
	else if(strPrcdrID == PkgData_DeviceUpdateResult)
	{
		pData = new CTcpEdgePkgData_DeviceUpdateResult();
	}
	else if(strPrcdrID == PkgData_DeviceCtrlReq)
	{
		pData = new CTcpEdgePkgData_DeviceCtrlReq();
	}
	else if(strPrcdrID == PkgData_DeviceCtrlResp)
	{
		pData = new CTcpEdgePkgData_DeviceCtrlResp();
	}
	else if(strPrcdrID == PkgData_DeviceInfoReq)
	{
		pData = new CTcpEdgePkgData_DeviceInfoReq();
	}
	else if(strPrcdrID == PkgData_DeviceInfoResp)
	{
		pData = new CTcpEdgePkgData_DeviceInfoResp();
	}
	else if(strPrcdrID == PkgData_DeviceStatusReq)
	{
		pData = new CTcpEdgePkgData_DeviceStatusReq();
	}
	else if(strPrcdrID == PkgData_DeviceStatusResp)
	{
		pData = new CTcpEdgePkgData_DeviceStatusResp();
	}
	else if(strPrcdrID == PkgData_DeviceConfigReq)
	{
		pData = new CTcpEdgePkgData_DeviceConfigReq();
	}
	else if(strPrcdrID == PkgData_DeviceConfigResp)
	{
		pData = new CTcpEdgePkgData_DeviceConfigResp();
	}
	else if(strPrcdrID == PkgData_SysAlarm)
	{
		pData = new CTcpEdgePkgData_SysAlarm();
	}
	else if(strPrcdrID == PkgData_ConInstallReq)
	{
		pData = new CTcpEdgePkgData_ConInstallReq();
	}
	else if(strPrcdrID == PkgData_ConInstallResp)
	{
		pData = new CTcpEdgePkgData_ConInstallResp();
	}
	else if(strPrcdrID == PkgData_ConStartReq)
	{
		pData = new CTcpEdgePkgData_ConStartReq();
	}
	else if(strPrcdrID == PkgData_ConStartResp)
	{
		pData = new CTcpEdgePkgData_ConStartResp();
	}
	else if(strPrcdrID == PkgData_ConStopReq)
	{
		pData = new CTcpEdgePkgData_ConStopReq();
	}
	else if(strPrcdrID == PkgData_ConStopResp)
	{
		pData = new CTcpEdgePkgData_ConStopResp();
	}
	else if(strPrcdrID == PkgData_ConRestartReq)
	{
		pData = new CTcpEdgePkgData_ConRestartReq();
	}
	else if(strPrcdrID == PkgData_ConRestartResp)
	{
		pData = new CTcpEdgePkgData_ConRestartResp();
	}
	else if(strPrcdrID == PkgData_ConRemoveReq)
	{
		pData = new CTcpEdgePkgData_ConRemoveReq();
	}
	else if(strPrcdrID == PkgData_ConRemoveResp)
	{
		pData = new CTcpEdgePkgData_ConRemoveResp();
	}
	else if(strPrcdrID == PkgData_ConGetConfigReq)
	{
		pData = new CTcpEdgePkgData_ConGetConfigReq();
	}
	else if(strPrcdrID == PkgData_ConGetConfigResp)
	{
		pData = new CTcpEdgePkgData_ConGetConfigResp();
	}
	else if(strPrcdrID == PkgData_ConSetConfigReq)
	{
		pData = new CTcpEdgePkgData_ConSetConfigReq();
	}
	else if(strPrcdrID == PkgData_ConSetConfigResp)
	{
		pData = new CTcpEdgePkgData_ConSetConfigResp();
	}
	else if(strPrcdrID == PkgData_ConAlarm)
	{
		pData = new CTcpEdgePkgData_ConAlarm();
	}
	else if(strPrcdrID == PkgData_ConStatusReq)
	{
		pData = new CTcpEdgePkgData_ConStatusReq();
	}
	else if(strPrcdrID == PkgData_ConStatusResp)
	{
		pData = new CTcpEdgePkgData_ConStatusResp();
	}
	else if(strPrcdrID == PkgData_ModelChange)
	{
		pData = new CTcpEdgePkgData_ModelChange();
	}
	else if(strPrcdrID == PkgData_ModelChangeResp)
	{
		pData = new CTcpEdgePkgData_ModelChangeResp();
	}
	else if(strPrcdrID == PkgData_DevAdd)
	{
		pData = new CTcpEdgePkgData_DevAdd();
	}
	else if(strPrcdrID == PkgData_DevAddResp)
	{
		pData = new CTcpEdgePkgData_DevAddResp();
	}
	else if(strPrcdrID == PkgData_DevUpdate)
	{
		pData = new CTcpEdgePkgData_DevUpdate();
	}
	else if(strPrcdrID == PkgData_DevUpdateResp)
	{
		pData = new CTcpEdgePkgData_DevUpdateResp();
	}
	else if(strPrcdrID == PkgData_ModelDevRead)
	{
		pData = new CTcpEdgePkgData_ModelDevRead();
	}
	else if(strPrcdrID == PkgData_GetModel)
	{
		pData = new CTcpEdgePkgData_GetModel();
	}
	else if(strPrcdrID == PkgData_ModelDevReadResp )
	{
		pData = new CTcpEdgePkgData_ModelDevReadResp();
	}
	else if(strPrcdrID == PkgData_DataSubs)
	{
		pData = new CTcpEdgePkgData_DataSubs();
	}
	else if(strPrcdrID == PkgData_DataSubsResp)
	{
		pData = new CTcpEdgePkgData_DataSubsResp();
	}
	else if(strPrcdrID == PkgData_GetDataSubs)
	{
		pData = new CTcpEdgePkgData_GetDataSubs();
	}
	else if(strPrcdrID == PkgData_GetDataSubsResp)
	{
		pData = new CTcpEdgePkgData_GetDataSubsResp();
	}
	else if(strPrcdrID == PkgData_DataSpont)
	{
		pData = new CTcpEdgePkgData_DataSpont();
	}
	else if(strPrcdrID == PkgData_DataSpontResp)
	{
		pData = new CTcpEdgePkgData_DataSpontResp();
	}
	else if(strPrcdrID == PkgData_DataRead)
	{
		pData = new CTcpEdgePkgData_DataRead();
	}
	else if(strPrcdrID == PkgData_DataReadResp)
	{
		pData = new CTcpEdgePkgData_DataReadResp();
	}
	else if(strPrcdrID == PkgData_ParaRead)
	{
		pData = new CTcpEdgePkgData_ParaRead();
	}
	else if(strPrcdrID == PkgData_ParaReadResp)
	{
		pData = new CTcpEdgePkgData_ParaReadResp();
	}
	else if(strPrcdrID == PkgData_FileGet)
	{
		pData = new CTcpEdgePkgData_FileGet();
	}
	else if(strPrcdrID == PkgData_FileGetResp)
	{
		pData = new CTcpEdgePkgData_FileGetResp();
	}
	else if(strPrcdrID == PkgData_FileDataTrans)
	{
		pData = new CTcpEdgePkgData_FileDataTrans();
	}
	else if(strPrcdrID == PkgData_FileDataTransResp)
	{
		pData = new CTcpEdgePkgData_FileDataTransResp();
	}
	else if(strPrcdrID == PkgData_DeviceGetLogReq)
	{
		pData = new CTcpEdgePkgData_DeviceGetLogReq();
	}
	else if(strPrcdrID == PkgData_DeviceGetLogResp)
	{
		pData = new CTcpEdgePkgData_DeviceGetLogResp();
	}
	else if(strPrcdrID == PkgData_ContGetLogReq)
	{
		pData = new CTcpEdgePkgData_ContGetLogReq();
	}
	else if(strPrcdrID == PkgData_ContGetLogResp)
	{
		pData = new CTcpEdgePkgData_ContGetLogResp();
	}
	else if(strPrcdrID == PkgData_AppGetLogReq)
	{
		pData = new CTcpEdgePkgData_AppGetLogReq();
	}
	else if(strPrcdrID == PkgData_AppGetLogResp)
	{
		pData = new CTcpEdgePkgData_AppGetLogResp();
	}
	else if(strPrcdrID == PkgData_ParaSet)
	{
		pData = new CTcpEdgePkgData_ParaSet();
	}
	else if(strPrcdrID == PkgData_AppInstallReq)
	{
		pData = new CTcpEdgePkgData_AppInstallReq();
	}
	else if(strPrcdrID == PkgData_AppInstallResp)
	{
		pData = new CTcpEdgePkgData_AppInstallResp();
	}
	else if(strPrcdrID == PkgData_AppInstallStatusReq)
	{
		pData = new CTcpEdgePkgData_AppInstallStatusReq();
	}
	else if(strPrcdrID == PkgData_AppInstallStatusResp)
	{
		pData = new CTcpEdgePkgData_AppInstallStatusResp();
	}
	else if(strPrcdrID == PkgData_AppInstallResult)
	{
		pData = new CTcpEdgePkgData_AppInstallResult();
	}
	else if(strPrcdrID == PkgData_AppStatusReq)
	{
		pData = new CTcpEdgePkgData_AppStatusReq();
	}
	else if(strPrcdrID == PkgData_AppStatusResp)
	{
		pData = new CTcpEdgePkgData_AppStatusResp();
	}
	else if(strPrcdrID == PkgData_AppStartReq)
	{
		pData = new CTcpEdgePkgData_AppStartReq();
	}
	else if(strPrcdrID == PkgData_AppStartResp)
	{
		pData = new CTcpEdgePkgData_AppStartResp();
	}
	else if(strPrcdrID == PkgData_AppStopReq)
	{
		pData = new CTcpEdgePkgData_AppStopReq();
	}
	else if(strPrcdrID == PkgData_AppStopResp)
	{
		pData = new CTcpEdgePkgData_AppStopResp();
	}
	else if(strPrcdrID == PkgData_AppRemoveReq)
	{
		pData = new CTcpEdgePkgData_AppRemoveReq();
	}
	else if(strPrcdrID == PkgData_AppRemoveResp)
	{
		pData = new CTcpEdgePkgData_AppRemoveResp();
	}
	else if(strPrcdrID == PkgData_AppEnableReq)
	{
		pData = new CTcpEdgePkgData_AppEnableReq();
	}
	else if(strPrcdrID == PkgData_AppEnableResp)
	{
		pData = new CTcpEdgePkgData_AppEnableResp();
	}
	else if(strPrcdrID == PkgData_AppDisableReq)
	{
		pData = new CTcpEdgePkgData_AppDisableReq();
	}
	else if(strPrcdrID == PkgData_AppDisableResp)
	{
		pData = new CTcpEdgePkgData_AppDisableResp();
	}
	else if(strPrcdrID == PkgData_AppGetConfigReq)
	{
		pData = new CTcpEdgePkgData_AppGetConfigReq();
	}
	else if(strPrcdrID == PkgData_AppGetConfigResp)
	{
		pData = new CTcpEdgePkgData_AppGetConfigResp();
	}
	else if(strPrcdrID == PkgData_AppSetConfigReq)
	{
		pData = new CTcpEdgePkgData_AppSetConfigReq();
	}
	else if(strPrcdrID == PkgData_AppSetConfigResp)
	{
		pData = new CTcpEdgePkgData_AppSetConfigResp();
	}
	else if(strPrcdrID == PkgData_AppAlarm)
	{
		pData = new CTcpEdgePkgData_AppAlarm();
	}
	else if(strPrcdrID == PkgData_GetHisData)
	{
		pData = new CTcpEdgePkgData_GetHisData();
	}
	else if(strPrcdrID == PkgData_GetHisDataResp)
	{
		pData = new CTcpEdgePkgData_GetHisDataResp();
	}
	else if(strPrcdrID == PkgData_ParaCancel)
	{
		pData = new CTcpEdgePkgData_ParaCancel();
	}
	else if(strPrcdrID == PkgData_ParaCancelResp)
	{
		pData = new CTcpEdgePkgData_ParaCancelResp();
	}
	else if(strPrcdrID == PkgData_ParaActivate)
	{
		pData = new CTcpEdgePkgData_ParaActivate();
	}
	else if(strPrcdrID == PkgData_ParaActivateResp)
	{
		pData = new CTcpEdgePkgData_ParaActivateResp();
	}
	else if(strPrcdrID == PkgData_ParaSetResp)
	{
		pData = new CTcpEdgePkgData_ParaSetResp();
	}
	else if(strPrcdrID == PkgData_CtrlCmd)
	{
		pData = new CTcpEdgePkgData_CtrlCmd();
	}
	else if(strPrcdrID == PkgData_CtrlCmdResp)
	{
		pData = new CTcpEdgePkgData_CtrlCmdResp();
	}
	else if(strPrcdrID == PkgData_GetTopoFile)
	{
		pData = new CTcpEdgePkgData_GetTopoFile();
	}
	else if(strPrcdrID == PkgData_GetTopoFileResp)
	{
		pData = new CTcpEdgePkgData_GetTopoFileResp();
	}
	else if(strPrcdrID == PkgData_AppGetCfgFileReq)
	{
		pData = new CTcpEdgePkgData_AppGetCfgFileReq();
	}
	else if(strPrcdrID == PkgData_AppGetCfgFileResp)
	{
		pData = new CTcpEdgePkgData_AppGetCfgFileResp();
	}
	else if(strPrcdrID == PkgData_AppSetCfgFileReq)
	{
		pData = new CTcpEdgePkgData_AppSetCfgFileReq();
	}
	else if(strPrcdrID == PkgData_AppSetCfgFileResp)
	{
		pData = new CTcpEdgePkgData_AppSetCfgFileResp();
	}
	else if(strPrcdrID == PkgData_GetHisEvent)
	{
		pData = new CTcpEdgePkgData_GetHisEvent();
	}
	else if(strPrcdrID == PkgData_GetHisEventResp)
	{
		pData = new CTcpEdgePkgData_GetHisEventResp();
	}
	else if(strPrcdrID == PkgData_GetMessage)
	{
		pData = new CTcpEdgePkgData_GetMessage();
	}
	else if(strPrcdrID == PkgData_GetMessageResp)
	{
		pData = new CTcpEdgePkgData_GetMessageResp();
	}
	else if(strPrcdrID == PkgData_GetModelResp)
	{
		pData = new CTcpEdgePkgData_GetModelResp();
	}

	if(!pData)
	{
		return NULL;
	}

	QByteArray bytes;
	bytes.append(pDataJson);
	pData->SetXml_ASCII(pDataJson, bytes.size(), CTcpEdgePkgXmlRWKeys::g_pXmlKeys, _JSON_TYPE_);
	return pData;
}

CString CTcpEdgePkg::GetPrcdrIDByPkgData(CTcpEdgePkgData* pPkgData)
{
	//理论上全部的prcdr都应该是回复到平台的报文,即是resp
	//但由于几乎所有的过程加上req也不影响判断,所以if中存在req部分
	if(pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_TIMESYNCREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_TIMESYNCRESP)
	{
		return PkgData_TimeSyncReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_TIMEREADREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_TIMEREADRESP)
	{
		return PkgData_TimeReadReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEUPDATEREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEUPDATERESP
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEUPDATESTATUSREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEUPDATESTATUSRESP
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEUPDATERESULT)
	{
		return PkgData_DeviceUpdateReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICECTRLREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICECTRLRESP)
	{
		return PkgData_DeviceCtrlReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEINFOREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEINFORESP)
	{
		return PkgData_DeviceInfoReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICESTATUSREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICESTATUSRESP)
	{
		return PkgData_DeviceStatusReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICECONFIGREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICECONFIGRESP)
	{
		return PkgData_DeviceConfigReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_SYSALARM)
	{
		return PkgData_SysAlarm;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONINSTALLREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONINSTALLRESP)
	{
		return PkgData_ConInstallReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONSTATUSREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONSTATUSRESP)
	{
		return PkgData_ConStatusReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONSTARTREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONSTARTRESP)
	{
		return PkgData_ConStartReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONSTOPREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONSTOPRESP)
	{
		return PkgData_ConStopReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONRESTARTREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONRESTARTRESP)
	{
		return PkgData_ConRestartReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONREMOVEREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONREMOVERESP)
	{
		return PkgData_ConRemoveReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONGETCONFIGREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONGETCONFIGRESP)
	{
		return PkgData_ConGetConfigReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONSETCONFIGREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONSETCONFIGRESP)
	{
		return PkgData_ConSetConfigReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONALARM)
	{
		return PkgData_ConAlarm;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPINSTALLREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPINSTALLRESP
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPINSTALLSTATUSREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPINSTALLSTATUSRESP
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPINSTALLRESULT)
	{
		return PkgData_AppInstallReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPSTATUSREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPSTATUSRESP)
	{
		return PkgData_AppStatusReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPSTARTREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPSTARTRESP)
	{
		return PkgData_AppStartReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPSTOPREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPSTOPRESP)
	{
		return PkgData_AppStopReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPREMOVEREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPREMOVERESP)
	{
		return PkgData_AppRemoveReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPENABLEREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPENABLERESP)
	{
		return PkgData_AppEnableReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPDISABLEREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPDISABLERESP)
	{
		return PkgData_AppDisableReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPGETCONFIGREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPGETCONFIGRESP)
	{
		return PkgData_AppGetConfigReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPSETCONFIGREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPSETCONFIGRESP)
	{
		return PkgData_AppSetConfigReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPALARM)
	{
		return PkgData_AppAlarm;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEGETLOGREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVICEGETLOGRESP)
	{
		return PkgData_DeviceGetLogReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONTGETLOGREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CONTGETLOGRESP)
	{
		return PkgData_ContGetLogReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPGETLOGREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPGETLOGRESP)
	{
		return PkgData_AppGetLogReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_GETMODEL
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_GETMODELRESP)
	{
		return PkgData_GetModel;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_MODELCHANGE
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_MODELCHANGERESP)
	{
		return PkgData_ModelChange;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVADD
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVADDRESP)
	{
		return PkgData_DevAdd;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVUPDATE
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DEVUPDATERESP)
	{
		return PkgData_DevUpdate;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_MODELDEVREAD
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_MODELDEVREADRESP)
	{
		return PkgData_ModelDevRead;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DATASUBS
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DATASUBSRESP)
	{
		return PkgData_DataSubs;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_GETDATASUBS
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_GETDATASUBSRESP)
	{
		return PkgData_GetDataSubs;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DATASPONT
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DATASPONTRESP)
	{
		return PkgData_DataSpont;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DATAREAD
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_DATAREADRESP)
	{
		return PkgData_DataRead;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_PARAREAD
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_PARAREADRESP)
	{
		return PkgData_ParaRead;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_GETTOPOFILE
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_GETTOPOFILERESP)
	{
		return PkgData_GetTopoFile;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_GETMESSAGE
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_GETMESSAGERESP)
	{
		return PkgData_GetMessage;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CTRLCMD
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_CTRLCMDRESP)
	{
		return PkgData_CtrlCmd;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_PARASET
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_PARASETRESP)
	{
		return PkgData_ParaSet;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_PARAACTIVATE
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_PARAACTIVATERESP)
	{
		return PkgData_ParaActivate;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_PARACANCEL
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_PARACANCELRESP)
	{
		return PkgData_ParaCancel;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_HEALTH)
	{
		return PkgData_HealthReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_FILEGET
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_FILEGETRESP
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_FILEDATATRANS
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_FILEDATATRANSRESP)
	{
		//协议中接收到的报文,上报是FileDataTrans
		return PkgData_FileGet;
	}
// 	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_FILESEND
// 		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_FILESENDRESP)
// 	{
// 		return PkgData_FileSend;
// 	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPGETCFGFILEREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPGETCFGFILERESP)
	{
		//协议中接收到的报文,上报是FileDataTransResp
		return PkgData_AppGetCfgFileReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPSETCFGFILEREQ
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_APPSETCFGFILERESP)
	{
		//协议中接收到的报文,上报是FileDataTransResp
		return PkgData_AppSetCfgFileReq;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_GETHISEVENT
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_GETHISEVENTRESP)
	{
		//协议中接收到的报文,上报是FileDataTransResp
		return PkgData_GetHisEvent;
	}
	else if (pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_GETHISDATA
		|| pPkgData->GetClassID() == MNGRCLASSID_CTCPEDGEPKGDATA_GETHISDATARESP)
	{
		//协议中接收到的报文,上报是FileDataTransResp
		return PkgData_GetHisData;
	}

	return "";
}

CJSON* CTcpEdgePkg::Parser(char* pBuf)
{
	//解析接收到的报文前要从utf8转ascii
	QString strAscii = QString::fromUtf8(pBuf);
	CJSON* pJson = CJSON_Parse(strAscii.toStdString().c_str());
	CJSON* pHeadJson = CJSON_GetObjectItem(pJson, PkgData_Node_Head);
	CJSON* pDataJson = CJSON_GetObjectItem(pJson, PkgData_Node_Data);

	m_pPkgHead = new CTcpEdgePkgHead();
	m_pPkgHead->SetXml(CJSON_Print(pHeadJson), CTcpEdgePkgXmlRWKeys::g_pXmlKeys, _JSON_TYPE_);
	m_pPkgData = CreatePkgDataByID(m_pPkgHead->m_strFunName, CJSON_Print(pDataJson));
	
	return pJson;
}

CString CTcpEdgePkg::Produce()
{
	CString strHead, strData;
	if(m_pPkgHead && m_pPkgData)
	{
		if(!CTcpEdgePkgXmlRWKeys::g_pXmlKeys)
		{
			//关闭的一刹那仍然在准备发报文,会析构错误
			return "";
		}
		char* tempData = NULL;
		m_pPkgHead->GetXml_ASCII(CTcpEdgePkgXmlRWKeys::g_pXmlKeys, &tempData, 0, _JSON_TYPE_);
		strHead = tempData;
		delete tempData;

		m_pPkgData->GetXml_ASCII(CTcpEdgePkgXmlRWKeys::g_pXmlKeys, &tempData, 0, _JSON_TYPE_);
		strData = tempData;
		delete tempData;

		QString strPkg = QString("{\"Head\":%1,\"Data\":%2}").arg(strHead).arg(strData);
		return strPkg;
	}
	return "";
}