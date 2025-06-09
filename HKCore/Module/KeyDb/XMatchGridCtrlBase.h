#pragma once
#include "..\gridctrl\gridctrl.h"
#include "XMatchToolBase.h"
#include "..\BaseClass\XDialogBase.h"

class CXMatchGridCtrlBase :	public CGridCtrl
{
public:
	CXMatchGridCtrlBase(void);
	~CXMatchGridCtrlBase(void);

	virtual void ShowXMatchTool(CXMatchToolBase *pXMatchTool);

protected:
	CXMatchToolBase *m_pXMatchTool;
};
