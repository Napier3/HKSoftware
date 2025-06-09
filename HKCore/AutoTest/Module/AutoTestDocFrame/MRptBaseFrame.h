#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CMDIChildWnd。"
#endif 

#include "AutoTestBaseFrame.h"

class CMRptBaseFrame : public CAutoTestBaseFrame
{
	DECLARE_DYNCREATE(CMRptBaseFrame)
protected:
	CMRptBaseFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CMRptBaseFrame();

public:
	virtual BOOL OnCloseAtsFrame();;
	virtual BOOL CloseAtsFrameEx();

protected:

	DECLARE_MESSAGE_MAP()
	
public:
	
};


