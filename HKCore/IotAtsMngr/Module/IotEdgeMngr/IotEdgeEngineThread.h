#pragma once

class CIotEdgeEngineData;

class CIotEdgeEngineThread:public CWinThread
{
	 DECLARE_DYNCREATE(CIotEdgeEngineThread)

private:
	CIotEdgeEngineThread();
	virtual ~CIotEdgeEngineThread();

public:
	static CIotEdgeEngineThread* CreateEngineThread(CIotEdgeEngineData *pEngineData)
	{
		CIotEdgeEngineThread *pThread = (CIotEdgeEngineThread*)AfxBeginThread(RUNTIME_CLASS(CIotEdgeEngineThread), THREAD_PRIORITY_HIGHEST, 0, CREATE_SUSPENDED);
		pThread->m_pEngineData = pEngineData;
		pThread->ResumeThread();

		return pThread;
	}

protected:
	DECLARE_MESSAGE_MAP()

public:
	CIotEdgeEngineData *m_pEngineData;

};