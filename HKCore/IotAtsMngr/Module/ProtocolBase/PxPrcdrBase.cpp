#include "stdafx.h"
#include "PxPrcdrBase.h"
#include "../Edge/EdgeCmd/EdgeGlobalDef.h"
#include "PxProtocolBase.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"
#include "../IotEngineGlobalDef.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif 

CPxPrcdrBase::CPxPrcdrBase()
{
	m_nProcedureState = 0;
	m_strRecordMode = Prcdr_RecordMode_None;

	m_dwBeginTime = 0;
	m_nOverTimeLong = -1;
	GetLocalTime(&m_tmBeginTime);

	m_pRefDataset = NULL;
	m_pPxCmmInterface = NULL;
	m_pPxProtocolRef = NULL;
}

CPxPrcdrBase::~CPxPrcdrBase()
{
	DeletePkgList();
}

void CPxPrcdrBase::DeletePkgList()
{
	POS pos = m_listRecvPkg.GetHeadPosition();
	CPxPkgBase *p = NULL;

	while(pos != NULL)
	{
		p = (CPxPkgBase *)m_listRecvPkg.GetNext(pos);

		p->SetPkgState(PX_PKG_STATE_CAN_DELETE);
	}

	m_listRecvPkg.RemoveAll();
	m_listSendPkg.RemoveAll();
}

//循环执行，判断超时或发送报文，过程结束返回TRUE
BOOL CPxPrcdrBase::Run()
{//特殊过程：WriteMmsAttr

	if(m_strID == PROCEDURE_ID_WriteMmsAttr)
	{
		SetResultEvent(RUNPROCEDURE_EVENT_CommFinish);
		SetProcedureState(PrcdrState_Step_End);
		return TRUE;
	}
	
	return FALSE;
}

void CPxPrcdrBase::InitProcedure(const CString &strDeviceID,const CString &strProcedureID,CExBaseList *pListDatas
				   ,CDvmDataset *pDataset,const CString &strRecordMode)
{
	m_oDataInterface.DeleteAll();
	if (pListDatas != NULL)
	{
		m_oDataInterface.AppendClone(pListDatas);
	}

	m_strID = strProcedureID;
	m_strDeviceID = strDeviceID;
	m_strRecordMode = strRecordMode;
	m_pRefDataset = pDataset;

	m_nProcedureState = PrcdrState_Step_NULL;
}

void CPxPrcdrBase::ResetTimer()
{
	//根据参数设置超时
	GetLocalTime(&m_tmBeginTime);
	m_dwBeginTime = GetTickCount();
	//yzj 2021-11-1 部分过程将会持续近10分钟
	m_nOverTimeLong = 600000;
}

void CPxPrcdrBase::KillTimer()
{
	m_dwBeginTime = 0;
	m_nOverTimeLong = -1;
}

BOOL CPxPrcdrBase::IsTimerOut(DWORD dwCurTime)
{
	if (m_nOverTimeLong <= 0)
	{
		return FALSE;
	}
	return ((dwCurTime - m_dwBeginTime) >= m_nOverTimeLong) ;
}

//处理报文列表,若提前应答报文，返回TRUE,否则返回FALSE
BOOL CPxPrcdrBase::ProcessRecvPkgs()
{
	if(m_pPxProtocolRef == NULL)
	{
		return FALSE;
	}

	//提取所有未处理的报文
	CExBaseList oRecvList;
	m_pPxProtocolRef->GetNotProcessedPkgs(oRecvList);

	//从报文列表中查找是否有应答
	POS pos = oRecvList.GetHeadPosition();
	CPxPkgBase *pPkg = NULL;
	BOOL bRet = FALSE;

	while(pos != NULL)
	{
		pPkg = (CPxPkgBase *)oRecvList.GetNext(pos);

		//报文时间<=m_tmBeginTime时间，说明报文过时
		if (CompareSysTime(pPkg->m_tmPkg,m_tmBeginTime) <= 0)
		{
			continue;
		}

		//处理报文：判断若是应答，继续处理，返回TRUE,否则返回FALSE
		if(ProcessPackageDetail(pPkg))
		{//若该报文为应答,添加到过程链表引用中

			bRet = TRUE;
			m_listRecvPkg.AddTail(pPkg);
			break;
		}
	}

	oRecvList.RemoveAll();

	return bRet;
}