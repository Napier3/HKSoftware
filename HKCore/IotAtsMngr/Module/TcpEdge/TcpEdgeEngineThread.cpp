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
		//��������ͨ���ļ�ʱ��ʱ����
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

		//ɾ����Ч����
		m_pProtocol->DeleteUnvalidPkgs();

		//һ��ѭ���󣬽����ʱ���ڹ�����ӵ��ܵĹ���������
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
 				//��չ��̽��ձ���
 				pProcedure->DeletePkgList();
 
 				//ɾ�����̽ڵ�
 				m_pProtocol->m_listPrcdr.DeleteAt(prePos);
 			}
 		}
	}

	emit sig_exit();
}