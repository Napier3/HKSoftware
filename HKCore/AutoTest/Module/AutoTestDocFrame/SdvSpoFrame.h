#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CMDIChildWnd。"
#endif 

#include "AutoTestBaseFrame.h"

class CSdvSpoFrame : public CAutoTestBaseFrame
{
	DECLARE_DYNCREATE(CSdvSpoFrame)
protected:
	CSdvSpoFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CSdvSpoFrame();

public:
	CTestControlBase* CreateFrame_SdvSpo(CTestControlBase *pTestControl, CTestItemViewGrid *pItemGrid);
	CTestControlBase* CreateFrame_SdvSpo(const CString &strGbBinaryFile, CTestItemViewGrid *pItemGrid, BOOL bFullPath=FALSE);
	CTestControlBase* CreateFrame_SdvSpo(CTestItemViewGrid *pItemGrid, CXFolder *pFolder, const CString &strTemplateFile, const CString &strGuideBookFileType
		, const CString &strTestProjectName, const CString &strPpEngineProgID, const CString &strPpTemplateFile
		, const CString &strDeviceFile);

protected:

	DECLARE_MESSAGE_MAP()
	
public:
	
};


