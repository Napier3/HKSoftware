#include "stdafx.h"
#include "IotPpProcedureRun.h"
#include "RTDeviceCtrl.h"
#include "../IotSensorSvrEngine.h"
#include "../../../../Module/GpsPcTime/GpsPcTime.h"
#include "../../IotEngineGlobalDef.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


CIotPpProcedureRun::CIotPpProcedureRun(CRTDeviceCtrl *pRTDeviceCtrlRef,CIotPpProcedure *pProcedure
									   , CExBaseList *pInterface,CDvmDataset *pDataset,const CString &strRecordMode)
									   
{
	m_pCurrNode = NULL;
	m_bProcedureExit = FALSE;
	m_bIsValid = TRUE;

	m_pRTDeviceCtrlRef = pRTDeviceCtrlRef;
	m_strID = m_pRTDeviceCtrlRef->m_strID;
	m_pProcedure = pProcedure;
	m_pDatasetRef = pDataset;
	m_strRecordMode = strRecordMode;
}

CIotPpProcedureRun::~CIotPpProcedureRun()
{
	DeletePkgList();

	if (m_pProcedure != NULL)
	{
		delete m_pProcedure;
		m_pProcedure = NULL;
	}
}

//����ɾ����־�������������,�ڹ���ִ���߳���ͳһɾ������
void CIotPpProcedureRun::DeletePkgList()
{
	POS pos = m_listRcvPkg.GetHeadPosition();
	CXSensorPkg *p = NULL;

	while(pos != NULL)
	{
		p = (CXSensorPkg *)m_listRcvPkg.GetNext(pos);

		p->SetPkgState(PX_PKG_STATE_CAN_DELETE);
	}

	m_listRcvPkg.RemoveAll();
	m_listSendPkg.RemoveAll();
}

BOOL CIotPpProcedureRun::Run()
{
	if (!m_bIsValid)
	{
		SetResultEvent(RUNPROCEDURE_EVENT_Exception);
		m_bProcedureExit = TRUE;
		return TRUE;
	}

	if (m_pProcedure == NULL)
	{//˵����WriteMmsAttr����
		SetResultEvent(RUNPROCEDURE_EVENT_CommFinish);
		m_bProcedureExit = TRUE;
		return TRUE;
	}

	if (m_pCurrNode == NULL)
	{//��ǰ�ڵ�Ϊ�գ���ȡ���ڵ㣬ִ�нڵ�

		CIotPpNode *pRootNode = m_pProcedure->GetRootNode();
		ASSERT (pRootNode != NULL);

		if (pRootNode == NULL)
		{//����û��ͷ�ڵ㣬����
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Procedure \"%s\" root node is null"), m_pProcedure->m_strID.GetString());
			m_bIsValid = FALSE;
		}
		else
		{//ִ��ͷ�ڵ�
			SetCurrNode(pRootNode);
			RunNode();
		}
	}
	else
	{
		ProcessNode();
	}

	return m_bProcedureExit;
}

void CIotPpProcedureRun::RunNode()
{
	ASSERT (m_pCurrNode != NULL);

	if ((m_pCurrNode == NULL) || (!m_bIsValid))
	{
		return;
	}

	//ƴ���ķ���
	RunNodePkg(m_pCurrNode->m_strPkg_Id);

	//����RunNode��ʼʱ�䣬���ڼ�ⱨ���Ƿ��ʱ
	m_pCurrNode->SetRunBegin();

	//������ʱ��
	BeginTimer(GetTickCount());
}

void CIotPpProcedureRun::BeginTimer(DWORD dwCurrTick)
{
	ASSERT (m_pCurrNode != NULL);

	m_pCurrNode->BeginTimer(dwCurrTick);
}

void CIotPpProcedureRun::RunNodePkg(const CString &strPackageID)
{//ƴ���ķ���
	if (strPackageID.IsEmpty())
	{//����Ҫƴ���ķ���
		return;
	}

	if(m_pRTDeviceCtrlRef == NULL)
	{
		return;
	}
	if (m_pRTDeviceCtrlRef->m_pIotTemplate == NULL)
	{
		return;
	}

	CIotPpProduce *pProduce = m_pRTDeviceCtrlRef->m_pIotTemplate->FindPpProduce(strPackageID);
	if (pProduce == NULL)
	{
		return;
	}

	//�������ݼ������̶����в����б�ƴ���ķ���
}

void CIotPpProcedureRun::ProcessNode()
{
	if (m_pRTDeviceCtrlRef == NULL)
	{
		m_bIsValid = FALSE;
		return;
	}

	//�ж��Ƿ�ʱ
	DWORD dwCurTick = GetTickCount();
	CIotPpNode *pJumpNode = NULL;
	if (IsTimerOut(dwCurTick,&pJumpNode))
	{
		//�ȹر�ԭ��Node�ڵ㶨ʱ��
		m_pCurrNode->KillTimer();

		if (pJumpNode == NULL)
		{//�����ʱ��ת�ڵ�Ϊ��
			//��ʱ���̽��������ý���¼�
			SetResultEvent(RUNPROCEDURE_EVENT_CommOverTime);
			m_bProcedureExit = TRUE;
		}
		else
		{//�����ʱ��ת�ڵ㲻Ϊ�գ�����Ϊ��ǰ�ڵ㣬ִ�е�ǰ�ڵ�
			SetCurrNode(pJumpNode);
			RunNode();
		}

		return;
	}

	//�ӱ����б��в����Ƿ���Ӧ��
	ProcessRecvPkgs();	
}

void CIotPpProcedureRun::ProcessRecvPkgs()
{
	if (m_pRTDeviceCtrlRef == NULL || m_pCurrNode == NULL)
	{
		return;
	}

	//��ȡ����δ����ı���
	CExBaseList oRecvList;
	m_pRTDeviceCtrlRef->GetNotProcessedPkgs(oRecvList);

	//�ӱ����б��в����Ƿ���Ӧ��
	POS pos = oRecvList.GetHeadPosition();
	CXSensorPkg *pPkg = NULL;

	while(pos != NULL)
	{
		pPkg = (CXSensorPkg *)oRecvList.GetNext(pos);

		//����ʱ��<=RunNodeʱ�䣬˵�����Ĺ�ʱ
		if (CompareSysTime(pPkg->m_tmPkg,m_pCurrNode->m_tmRunBegin) <= 0)
		{
			continue;
		}

		//�����ģ��ж�����Ӧ�𣬼�����������TRUE,���򷵻�FALSE
		if(ProcessPackageDetail(pPkg))
		{//���ñ���ΪӦ����ӵ��ù��̱�������������

			//��������ӵ��ù��̱���������
			m_listRcvPkg.AddTail(pPkg);
			break;
		}
	}

	oRecvList.RemoveAll();
}

BOOL CIotPpProcedureRun::IsTimerOut(DWORD dwCurTime,CIotPpNode **ppCurNode)
{
	return m_pCurrNode->IsTimerOut(dwCurTime,ppCurNode);
}

void CIotPpProcedureRun::SetCurrNode(CIotPpNode *pNode)
{
	m_pCurrNode = pNode;
}

BOOL CIotPpProcedureRun::ProcessPackageDetail(CXSensorPkg *pPkgDetail)
{
	SensorPkgInfo *pSensorPkgInfo = (SensorPkgInfo *)pPkgDetail->m_pSensorPkgInfo;

	//����֡ͷ����ƥ������ڵ�
	CIotPpParse *pParse = m_pRTDeviceCtrlRef->m_pIotTemplate->FindPpParse(pSensorPkgInfo->m_nPkgType
		,pSensorPkgInfo->m_nCtrlType,pSensorPkgInfo->m_nRequestSetFlag);
	ASSERT(pParse != NULL);

	//�жϸñ����Ƿ����ڴ�Ӧ��
	CIotPpAck *pFindAck = m_pCurrNode->FindPpAck(pParse->m_strID);
	if (pFindAck == NULL)
	{//���Ǹù��̵�����Ӧ��
		return FALSE;
	}

	//�յ�Ӧ�𣬹رյ�ǰ�ڵ�Ķ�ʱ��
	m_pCurrNode->KillTimer();
	pPkgDetail->SetPkgState(PX_PKG_STATE_PROCESSED_MATCH);

	//����Ӧ���߼�
	m_bProcedureExit = ProcessPackageAck(pFindAck,pPkgDetail);

	if(m_bProcedureExit)
	{//�յ�Ӧ�𣬹��̽������ý���¼�
		SetResultEvent(RUNPROCEDURE_EVENT_CommFinish);
	}

	return TRUE;
}

BOOL CIotPpProcedureRun::ProcessPackageAck(CIotPpAck *pAck,CXSensorPkg *pPkgDetail)
{//����TRUE:��ʾ����
	CIotPpJumps *pJumps = pAck->GetIotPpJumps();
	if (pJumps == NULL)
	{
		return TRUE;
	}

	POS pos = pJumps->GetHeadPosition();
	CIotPpJump *pJump = NULL;

	while(pos != NULL)
	{
		pJump = (CIotPpJump *)pJumps->GetNext(pos);

		//���ݱ������ݺ���ת�ڵ㣬�ж���ת�����Ƿ�����
		if (!IsMatchJump(pJump,pPkgDetail))
		{
			continue;
		}

		//������ת��������ȡ��ת�ڵ�
		CIotPpNode *pDstNode = GetJumpNode(pJump);

		if (pDstNode != NULL)
		{
			SetCurrNode(pDstNode);
			RunNode();

			return FALSE;
		}

		break;
	}

	return TRUE;
}

CIotPpNode *CIotPpProcedureRun::GetJumpNode(CIotPpJump *pJump)
{
	CIotPpNode *pRetNode = NULL;

	if (PROCEDURE_END_NODE_ID == pJump->m_strJump_To)
	{//����
		return pRetNode;
	}

	if (PROCEDURE_START_NODE_ID == pJump->m_strJump_To)
	{//��ת�����ڵ�
	}
	else if (!pJump->m_strJump_To.IsEmpty())
	{//��ת��ָ���ڵ�
	}
	else
	{//��ת���½��ڵ�
		pRetNode = pJump->GetIotPpNode();
	}

	return pRetNode;
}

BOOL CIotPpProcedureRun::IsMatchJump(CIotPpJump *pJump,CXSensorPkg *pPkgDetail)
{//���ݱ������ݺ���ת�ڵ㣬�ж���ת�����Ƿ�����
	return TRUE;
}