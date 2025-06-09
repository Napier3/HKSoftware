#pragma once

#include "TestControlWnd.h"

#include  <QTimer>

class CTestControlWnd_Linux : public CTestControlWnd
{
public:
	CTestControlWnd_Linux();
	virtual ~CTestControlWnd_Linux();

	virtual BOOL CreateTestControlWnd();


    virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
    virtual void OnWndTimer(unsigned int nIDEvent);

public slots:
};


