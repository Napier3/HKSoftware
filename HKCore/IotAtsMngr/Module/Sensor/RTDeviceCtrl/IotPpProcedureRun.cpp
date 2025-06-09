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

//设置删除标志，清空链表引用,在过程执行线程中统一删除报文
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
	{//说明是WriteMmsAttr过程
		SetResultEvent(RUNPROCEDURE_EVENT_CommFinish);
		m_bProcedureExit = TRUE;
		return TRUE;
	}

	if (m_pCurrNode == NULL)
	{//当前节点为空，获取根节点，执行节点

		CIotPpNode *pRootNode = m_pProcedure->GetRootNode();
		ASSERT (pRootNode != NULL);

		if (pRootNode == NULL)
		{//过程没有头节点，结束
			CLogPrint::LogFormatString(XLOGLEVEL_ERROR, _T("Procedure \"%s\" root node is null"), m_pProcedure->m_strID.GetString());
			m_bIsValid = FALSE;
		}
		else
		{//执行头节点
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

	//拼报文发送
	RunNodePkg(m_pCurrNode->m_strPkg_Id);

	//设置RunNode起始时间，用于检测报文是否过时
	m_pCurrNode->SetRunBegin();

	//启动定时器
	BeginTimer(GetTickCount());
}

void CIotPpProcedureRun::BeginTimer(DWORD dwCurrTick)
{
	ASSERT (m_pCurrNode != NULL);

	m_pCurrNode->BeginTimer(dwCurrTick);
}

void CIotPpProcedureRun::RunNodePkg(const CString &strPackageID)
{//拼报文发送
	if (strPackageID.IsEmpty())
	{//不需要拼报文发送
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

	//根据数据集、过程对象中参数列表拼报文发送
}

void CIotPpProcedureRun::ProcessNode()
{
	if (m_pRTDeviceCtrlRef == NULL)
	{
		m_bIsValid = FALSE;
		return;
	}

	//判断是否超时
	DWORD dwCurTick = GetTickCount();
	CIotPpNode *pJumpNode = NULL;
	if (IsTimerOut(dwCurTick,&pJumpNode))
	{
		//先关闭原先Node节点定时器
		m_pCurrNode->KillTimer();

		if (pJumpNode == NULL)
		{//如果超时跳转节点为空
			//超时过程结束，设置结果事件
			SetResultEvent(RUNPROCEDURE_EVENT_CommOverTime);
			m_bProcedureExit = TRUE;
		}
		else
		{//如果超时跳转节点不为空，设置为当前节点，执行当前节点
			SetCurrNode(pJumpNode);
			RunNode();
		}

		return;
	}

	//从报文列表中查找是否有应答
	ProcessRecvPkgs();	
}

void CIotPpProcedureRun::ProcessRecvPkgs()
{
	if (m_pRTDeviceCtrlRef == NULL || m_pCurrNode == NULL)
	{
		return;
	}

	//提取所有未处理的报文
	CExBaseList oRecvList;
	m_pRTDeviceCtrlRef->GetNotProcessedPkgs(oRecvList);

	//从报文列表中查找是否有应答
	POS pos = oRecvList.GetHeadPosition();
	CXSensorPkg *pPkg = NULL;

	while(pos != NULL)
	{
		pPkg = (CXSensorPkg *)oRecvList.GetNext(pos);

		//报文时间<=RunNode时间，说明报文过时
		if (CompareSysTime(pPkg->m_tmPkg,m_pCurrNode->m_tmRunBegin) <= 0)
		{
			continue;
		}

		//处理报文：判断若是应答，继续处理，返回TRUE,否则返回FALSE
		if(ProcessPackageDetail(pPkg))
		{//若该报文为应答，添加到该过程报文引用链表中

			//将报文添加到该过程报文链表中
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

	//根据帧头查找匹配解析节点
	CIotPpParse *pParse = m_pRTDeviceCtrlRef->m_pIotTemplate->FindPpParse(pSensorPkgInfo->m_nPkgType
		,pSensorPkgInfo->m_nCtrlType,pSensorPkgInfo->m_nRequestSetFlag);
	ASSERT(pParse != NULL);

	//判断该报文是否是期待应答
	CIotPpAck *pFindAck = m_pCurrNode->FindPpAck(pParse->m_strID);
	if (pFindAck == NULL)
	{//不是该过程的启动应答
		return FALSE;
	}

	//收到应答，关闭当前节点的定时器
	m_pCurrNode->KillTimer();
	pPkgDetail->SetPkgState(PX_PKG_STATE_PROCESSED_MATCH);

	//处理应答逻辑
	m_bProcedureExit = ProcessPackageAck(pFindAck,pPkgDetail);

	if(m_bProcedureExit)
	{//收到应答，过程结束设置结果事件
		SetResultEvent(RUNPROCEDURE_EVENT_CommFinish);
	}

	return TRUE;
}

BOOL CIotPpProcedureRun::ProcessPackageAck(CIotPpAck *pAck,CXSensorPkg *pPkgDetail)
{//返回TRUE:表示结束
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

		//根据报文数据和跳转节点，判断跳转条件是否满足
		if (!IsMatchJump(pJump,pPkgDetail))
		{
			continue;
		}

		//满足跳转条件，获取跳转节点
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
	{//结束
		return pRetNode;
	}

	if (PROCEDURE_START_NODE_ID == pJump->m_strJump_To)
	{//跳转到根节点
	}
	else if (!pJump->m_strJump_To.IsEmpty())
	{//跳转到指定节点
	}
	else
	{//跳转到新建节点
		pRetNode = pJump->GetIotPpNode();
	}

	return pRetNode;
}

BOOL CIotPpProcedureRun::IsMatchJump(CIotPpJump *pJump,CXSensorPkg *pPkgDetail)
{//根据报文数据和跳转节点，判断跳转条件是否满足
	return TRUE;
}