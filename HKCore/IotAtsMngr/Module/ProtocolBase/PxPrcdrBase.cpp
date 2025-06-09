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

//ѭ��ִ�У��жϳ�ʱ���ͱ��ģ����̽�������TRUE
BOOL CPxPrcdrBase::Run()
{//������̣�WriteMmsAttr

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
	//���ݲ������ó�ʱ
	GetLocalTime(&m_tmBeginTime);
	m_dwBeginTime = GetTickCount();
	//yzj 2021-11-1 ���ֹ��̽��������10����
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

//�������б�,����ǰӦ���ģ�����TRUE,���򷵻�FALSE
BOOL CPxPrcdrBase::ProcessRecvPkgs()
{
	if(m_pPxProtocolRef == NULL)
	{
		return FALSE;
	}

	//��ȡ����δ����ı���
	CExBaseList oRecvList;
	m_pPxProtocolRef->GetNotProcessedPkgs(oRecvList);

	//�ӱ����б��в����Ƿ���Ӧ��
	POS pos = oRecvList.GetHeadPosition();
	CPxPkgBase *pPkg = NULL;
	BOOL bRet = FALSE;

	while(pos != NULL)
	{
		pPkg = (CPxPkgBase *)oRecvList.GetNext(pos);

		//����ʱ��<=m_tmBeginTimeʱ�䣬˵�����Ĺ�ʱ
		if (CompareSysTime(pPkg->m_tmPkg,m_tmBeginTime) <= 0)
		{
			continue;
		}

		//�����ģ��ж�����Ӧ�𣬼�����������TRUE,���򷵻�FALSE
		if(ProcessPackageDetail(pPkg))
		{//���ñ���ΪӦ��,��ӵ���������������

			bRet = TRUE;
			m_listRecvPkg.AddTail(pPkg);
			break;
		}
	}

	oRecvList.RemoveAll();

	return bRet;
}