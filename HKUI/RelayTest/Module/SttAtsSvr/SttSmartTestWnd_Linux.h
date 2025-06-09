#pragma once

#include "SttSmartTestWnd.h"

#include  <QTimer>

class CSttSmartTestWnd_Linux : public CSttSmartTestWnd
{
public:
	CSttSmartTestWnd_Linux();
	virtual ~CSttSmartTestWnd_Linux();

	virtual BOOL CreateSttSmartTestWnd();


    virtual void OnWndMsg(unsigned int nMsgID, unsigned long wParam, unsigned long  lParam);
    virtual void OnWndTimer(unsigned int nIDEvent);

public slots:
};


