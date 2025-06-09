#pragma once


#include "../PpEngineThreadBase.h"
// CPpEngineThread

class CPpEngineThread : public CPpEngineThreadBase
{
        DECLARE_DYNCREATE(CPpEngineThread)

protected:
	CPpEngineThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CPpEngineThread();

public:
	static CPpEngineThreadBase* CreateEngineThread(CPpEngineData *pEngineData)
	{
		CPpEngineThreadBase *pThread = (CPpEngineThreadBase*)AfxBeginThread(RUNTIME_CLASS(CPpEngineThread), THREAD_PRIORITY_HIGHEST, 0, CREATE_SUSPENDED);
		pThread->m_pEngineData = pEngineData;
		pThread->Init(pEngineData->m_pDevcieModel, pEngineData->m_pTemplate);
		pEngineData->m_pDeviceCmmChannelRef = pThread->m_pDeviceCmmChannel;
		pThread->ResumeThread();

		pThread->m_pPkgSendMngr->SetParent(pEngineData);
		pThread->m_pDeviceCmmChannel->SetParent(pEngineData);
		return pThread;
	}

protected:
     DECLARE_MESSAGE_MAP()
};


