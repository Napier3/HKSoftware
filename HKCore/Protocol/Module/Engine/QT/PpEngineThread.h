#pragma once


#include "../PpEngineThreadBase.h"
#include  <QTimer>

// CPpEngineThread

class CPpEngineThread : public CPpEngineThreadBase
{
protected:
	CPpEngineThread();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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
    //���غ���OnWndMsg��ʵ����Ϣ����
    virtual void OnThreadMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);

};


