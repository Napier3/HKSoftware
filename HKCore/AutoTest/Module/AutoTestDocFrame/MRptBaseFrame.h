#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CMDIChildWnd��"
#endif 

#include "AutoTestBaseFrame.h"

class CMRptBaseFrame : public CAutoTestBaseFrame
{
	DECLARE_DYNCREATE(CMRptBaseFrame)
protected:
	CMRptBaseFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
	virtual ~CMRptBaseFrame();

public:
	virtual BOOL OnCloseAtsFrame();;
	virtual BOOL CloseAtsFrameEx();

protected:

	DECLARE_MESSAGE_MAP()
	
public:
	
};


