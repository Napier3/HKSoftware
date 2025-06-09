#include "stdafx.h"
#include "PxProtocolBase.h"
#include "../../../Module/System/TickCount32.h"
#include "../../../Module/GpsPcTime/GpsPcTime.h"
#include "PxProtocolImpInterface.h"
#include "../IotEngineGlobalDef.h"

#include "PxProtoDeviceBase.h"
#include "XProtoSrvrBaseApp.h"

#ifdef _DEBUG  
#define new DEBUG_NEW  
#undef THIS_FILE  
static char THIS_FILE[] = __FILE__; 
#endif  

CPxProtocolBase::CPxProtocolBase()
{
	m_pDvmDevice = NULL;
	m_bDvmDeviceAttach = FALSE;
	m_pCfgGroup = NULL;

	m_pProtoEventInterface = NULL;
	m_pProcedureRunThread = NULL;
	m_bExitEngineThread = FALSE;
}

CPxProtocolBase::~CPxProtocolBase()
{
	ExitEngineThread();

	if (m_pDvmDevice != NULL)
	{
		delete m_pDvmDevice;
		m_pDvmDevice = NULL;
	}

	if (m_pCfgGroup != NULL)
	{
		delete m_pCfgGroup;
		m_pCfgGroup = NULL;
	}
}

void CPxProtocolBase::AttachProtoEventInterface(CPxProtoEventInterface *pProtoEventInterface)
{
	m_pProtoEventInterface = pProtoEventInterface;
}

void CPxProtocolBase::InitProtocol(const CString &strDeviceID,const CString &strDvmFile,const CString &strPpxmlFile
		  ,const CString &strCmmCfgFile,CDataGroup *pCfgGroup)
{
	//m_strID = strDeviceID;
	m_strPpxmlFile = strPpxmlFile;
	m_strCmmCfgFile = m_strCmmCfgFile;

	if (pCfgGroup != NULL)
	{
		m_pCfgGroup = (CDataGroup *)pCfgGroup->Clone();
	}

	m_pDvmDevice->m_strID = strDvmFile;
	//yzj 2021-9-9 不加则RunProcedure时无法找到ID
	m_strDeviceID = strDeviceID;

}

CDvmDataset *CPxProtocolBase::UpdateDataset(CDvmDataset *pSrcDataset)
{
	if (pSrcDataset == NULL)
	{
		return NULL;
	}

	CString strDsID = GetIDFromPath(pSrcDataset->m_strID,'$');

	CDvmDataset *pDstDataset = NULL;
	if (strDsID == MODEL_DEVICE_ID_Attr)
	{
		pDstDataset = m_pDvmDevice->GetDeviceAttrs();
	}
	else
	{
		pDstDataset = m_pDvmDevice->FindDataset(strDsID);
	}

	if (pDstDataset != NULL)
	{
		pDstDataset->UpdateDataValue(pSrcDataset);
	}

	return pDstDataset;
}

//提取所有未处理的报文，用于过程处理
void CPxProtocolBase::GetNotProcessedPkgs(CExBaseList &oList)
{
	POS pos = m_listRecvPkg.GetHeadPosition();
	CPxPkgBase *p = NULL;

	while(pos != NULL)
	{
		p = (CPxPkgBase *)m_listRecvPkg.GetNext(pos);

		if (p->IsPkgState_NotProcessed())
		{
			oList.AddTail(p);
		}
	}
}

void CPxProtocolBase::DeleteUnvalidPkgs()
{
	long nPkgLifeTime = 0;
	long nPkgCnt = m_listRecvPkg.GetCount();
	if (nPkgCnt <= 1)
	{
		return;
	}

	//约定半个小时未处理数据丢弃
	long nValidTimeLong = 1800000;
	SYSTEMTIME tmCur;
	GetLocalTime(&tmCur);

	POS pos = m_listRecvPkg.GetHeadPosition();
	POS posTail = m_listRecvPkg.GetTailPosition();
	POS prePos = NULL;
	CPxPkgBase *p = NULL;

	while(pos != NULL)
	{
		if (pos == posTail)
		{
			break;
		}

		prePos = pos;
		p = (CPxPkgBase *)m_listRecvPkg.GetNext(pos);

		if (p->IsPkgState_CanDelete())
		{
			m_listRecvPkg.DeleteAt(prePos);
			continue;
		}

		nPkgLifeTime = GetSpanMSeconds(p->m_tmPkg,tmCur);
		if (nPkgLifeTime >= nValidTimeLong)
		{
			m_listRecvPkg.DeleteAt(prePos);
			continue;
		}
	}
}

CPxPrcdrBase* CPxProtocolBase::FindProcedure(const CString &strProcedureID)
{
	ASSERT( FALSE );
	return NULL;
}

void CPxProtocolBase::AddProcedureRun(CPxProtoDeviceBase *pProtoDevice, CPxPrcdrBase *pProcedure
				, CExBaseList *pInterface,CDvmDataset *pDataset,const CString &strRecordMode)
{
	ASSERT (FALSE);
}

//////////////////////////////////////////////////////////////////////////
void CPxProtocolBase::StartEngineThread()
{
#ifndef _PSX_IDE_QT_
	ExitEngineThread();

	m_listPrcdr.DeleteAll();
	m_listTempPrcdr.DeleteAll();

	m_bExitEngineThread = FALSE;

	m_pProcedureRunThread = AfxBeginThread(Engine_ProcedureRunThread,this);
	m_pProcedureRunThread->m_bAutoDelete = TRUE;
#endif
}

void CPxProtocolBase::ExitEngineThread() 
{
	m_bExitEngineThread = TRUE;

	CTickCount32 oTick;

	while(m_pProcedureRunThread != NULL)
	{
		oTick.DoEvents(5);
	}
}

void CPxProtocolBase::OnRunProcedure()
{
	while(!m_bExitEngineThread)
	{
		//删除无效报文
		DeleteUnvalidPkgs();

		{
			//一次循环后，将这段时间内过程添加到总的过程链表中
			CAutoSimpleLock oLock(&m_oPrcdrTmpCriticSection);
			m_listPrcdr.AppendEx(m_listTempPrcdr);
			m_listTempPrcdr.RemoveAll();
		}
		
		POS pos = m_listPrcdr.GetHeadPosition();
		POS prePos = NULL;
		CPxPrcdrBase *pProcedure = NULL;

		while(pos != NULL)
		{
			prePos = pos;
			pProcedure = (CPxPrcdrBase *)m_listPrcdr.GetNext(pos);

			if (pProcedure->Run())
			{
				//过程非正常、正常结束
				if(m_pProtoEventInterface != NULL)
				{
					//协议过程事件返回
					m_pProtoEventInterface->OnPrcdrFinished(pProcedure);
				}

				//清空过程接收报文
				pProcedure->DeletePkgList();

				//删除过程节点
				m_listPrcdr.DeleteAt(prePos);
			}
		}
	}

	m_pProcedureRunThread = NULL;
}

UINT CPxProtocolBase::Engine_ProcedureRunThread(LPVOID pParam)
{
	CPxProtocolBase *pProtocol = (CPxProtocolBase *)pParam;

	pProtocol->OnRunProcedure();

	return 0;
}