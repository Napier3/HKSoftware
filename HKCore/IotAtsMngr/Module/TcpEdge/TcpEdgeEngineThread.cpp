#include "stdafx.h"
#include "TcpEdgeEngineThread.h"
#include "TcpEdgeProtocol.h"

CTcpEdgeEngineThread::CTcpEdgeEngineThread()
{
	m_pProtocol = NULL;
}

CTcpEdgeEngineThread::~CTcpEdgeEngineThread()
{

}

void CTcpEdgeEngineThread::run()
{
	if(!m_pProtocol)
	{
		return;
	}

	m_timeMngrLastHealth = QTime::currentTime();
	m_timeDataLastHealth = QTime::currentTime();

	CTickCount32 oEvent;
	while(!m_pProtocol->m_bExitEngineThread)
	{
		//计算两个通道的计时器时间间隔
		QTime time = QTime::currentTime();
		if(m_timeMngrLastHealth.secsTo(time) >= m_pProtocol->m_nMngrHealthTime)
		{
			m_pProtocol->OnMngrTimeOut();
			m_timeMngrLastHealth = time;
		}	

		if(m_timeDataLastHealth.secsTo(time) >= m_pProtocol->m_nDataHealthTime)
		{
			m_pProtocol->OnDataTimeOut();
			m_timeDataLastHealth = time;
		}	

		//删除无效报文
		m_pProtocol->DeleteUnvalidPkgs();

		//一次循环后，将这段时间内过程添加到总的过程链表中
		m_pProtocol->UpdatePrcdrList();

		POS pos = m_pProtocol->m_listPrcdr.GetHeadPosition();
		POS prePos = NULL;
 		CPxPrcdrBase* pProcedure = NULL;
 		while(pos != NULL)
 		{
 			prePos = pos;
 			pProcedure = (CPxPrcdrBase*)m_pProtocol->m_listPrcdr.GetNext(pos);
 
 			if (pProcedure->Run())
 			{
 				//清空过程接收报文
 				pProcedure->DeletePkgList();
 
 				//删除过程节点
 				m_pProtocol->m_listPrcdr.DeleteAt(prePos);
 			}
 		}
	}

	emit sig_exit();
}