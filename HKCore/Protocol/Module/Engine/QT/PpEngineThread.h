#pragma once


#include "../PpEngineThreadBase.h"
#include  <QTimer>

// CPpEngineThread

class CPpEngineThread : public CPpEngineThreadBase
{
protected:
	CPpEngineThread();           // 动态创建所使用的受保护的构造函数
	virtual ~CPpEngineThread();

public:
    static CPpEngineThreadBase* CreateEngineThread(CPpEngineData *pEngineData)
        {
            CPpEngineThreadBase *pThread = new CPpEngineThread();
            pThread->m_pEngineData = pEngineData;
            pThread->Init(pEngineData->m_pDevcieModel, pEngineData->m_pTemplate);
            pEngineData->m_pDeviceCmmChannelRef = pThread->m_pDeviceCmmChannel;
            pThread->ResumeThread();

            pThread->m_pPkgSendMngr->SetParent(pEngineData);
            pThread->m_pDeviceCmmChannel->SetParent(pEngineData);
            pThread->InitInstance();
            return pThread;
        }


public:
    //重载函数OnWndMsg，实现消息处理
    virtual void OnThreadMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);

};


