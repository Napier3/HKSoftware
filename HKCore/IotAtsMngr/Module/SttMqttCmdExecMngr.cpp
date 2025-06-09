#include "stdafx.h"
#include "SttMqttCmdExecMngr.h"
#include "SttMqttClientEngineConfig.h"


CSttMqttCmdExecMngr::CSttMqttCmdExecMngr()
{
}

CSttMqttCmdExecMngr::~CSttMqttCmdExecMngr()
{

}

// void CSttMqttCmdExecMngr::DeleteCurTestItem(const CString& strTypeID,const CString &strItemPathID)
// {
// 	CAutoSimpleLock oLock(m_oCurItemsCriticalSection);
// 
// 	POS pos = m_oCurTestItems.GetHeadPosition();
// 	POS prePos = NULL;
// 	CAts_RealTimeItem *p = NULL;
// 
// 	while(pos != NULL)
// 	{
// 		prePos = pos;
// 		p = (CAts_RealTimeItem *)m_oCurTestItems.GetNext(pos);
// 
// 		if (p->m_strTypeID == strTypeID && p->m_strPathID == strItemPathID)
// 		{
// 			m_oCurTestItems.DeleteAt(prePos);
// 			break;
// 		}
// 	}
// }

// void CSttMqttCmdExecMngr::DeleteTypeTestItems(const CString& strTypeID)
// {
// 	CAutoSimpleLock oLock(m_oCurItemsCriticalSection);
// 
// 	POS pos = m_oCurTestItems.GetHeadPosition();
// 	POS prePos = NULL;
// 	CAts_RealTimeItem *p = NULL;
// 
// 	while(pos != NULL)
// 	{
// 		prePos = pos;
// 		p = (CAts_RealTimeItem *)m_oCurTestItems.GetNext(pos);
// 
// 		if (p->m_strTypeID == strTypeID)
// 		{
// 			m_oCurTestItems.DeleteAt(prePos);
// 		}
// 	}
// }

CSttMqttCmdExec *CSttMqttCmdExecMngr::FindDevice(__int64 nSensorID,CPpPrjDevice **ppPrjDevice)
{
	CString strDeviceID;
	strDeviceID.Format(_T("%012X"),nSensorID);

	CPpPrjDevice *pFind = NULL;
	POS pos = GetHeadPosition();
	CSttMqttCmdExec *p = NULL;

	while(pos != NULL)
	{
		p = (CSttMqttCmdExec *)GetNext(pos);

		pFind = (CPpPrjDevice *)p->m_pPrjDevices->FindByID(strDeviceID);

		if (pFind != NULL)
		{
			*ppPrjDevice = pFind;
			return p;
		}
	}

	return NULL;
}