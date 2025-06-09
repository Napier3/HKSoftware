#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CMDIChildWnd。"
#endif 

#include "SdvSpoFrame.h"

class CSdvMpoFrame : public CSdvSpoFrame
{
	DECLARE_DYNCREATE(CSdvMpoFrame)
protected:
	CSdvMpoFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CSdvMpoFrame();

public:
	CTestControlSdvMpp* CreateFrame_SdvMpo(CTestTask *pSrcTestTask
		, CTestItemViewGrid *pItemGrid, CXFolder *pFolder
		, const CString &strTemplateFile
		, const CString &strGuideBookFileType
		, const CString &strTestProjectName
		, CXFolder **ppNewFolder);

	CTestControlSdvMpp* CreateFrame_SdvMpo(const CString &strGbBinaryFile, CTestItemViewGrid *pItemGrid, BOOL bFullPath);

protected:

	DECLARE_MESSAGE_MAP()
	
public:
	
};


