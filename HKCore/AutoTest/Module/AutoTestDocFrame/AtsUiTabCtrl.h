#pragma once


// CMyMFCTabCtrl

#include "AtsUiTestStatusButton.h"
#include "AtsUiOutputLog.h"
#include "..\UITestItem\TestItemViewGrid.h"

class CAtsUiTabCtrl : public CMFCTabCtrl
{
	DECLARE_DYNAMIC(CAtsUiTabCtrl)

public:
	CAtsUiTabCtrl();
	virtual ~CAtsUiTabCtrl();
	void CreateTestTempFile()	{			m_pWndInfo->CreateTestTempFile();	}
	void EmptyGridInlegibleTestItem();
	void AttachMainFrame(CWnd *pWnd)	{	m_pMainFrame = pWnd;	}

public:
	//CAtsUiTestStatusButton m_btnTest;			//��������е�С����״̬��ť
	CAtsUiOutputLog *m_pWndInfo;						//��ʾ��Ϣ����
	CTestItemViewGrid m_gridInlegibleTestItem;

	//2020-12-23  lijunqing
	CAtsUiOutputLog *m_pMacroTestLog;
	CAtsUiOutputLog *m_pPpEngineLog;	

	CFont m_Font;
	CWnd *m_pMainFrame;

	void UpdateTestProjectSpy();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();

};


