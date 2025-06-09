#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CMDIChildWnd。"
#endif 

#include "SdvSpoFrame.h"

class CMdvSpoFrame : public CSdvSpoFrame
{
	DECLARE_DYNCREATE(CMdvSpoFrame)
protected:
	CMdvSpoFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CMdvSpoFrame();


public:
#if 0
	CTestControl* OnCreateFrame_MdvSpoFrame(const CString &strGbBinaryFile, CTestItemViewGrid *pItemGrid, BOOL bFullPath=FALSE);
	CTestControl* OnCreateFrame_MdvSpoFrame(CTestItemViewGrid *pItemGrid, CXFolder *pFolder, const CString &strTemplateFile, const CString &strGuideBookFileType
		, const CString &strTestProjectName, const CString &strPpEngineProgID, const CString &strPpTemplateFile
		, const CString &strDeviceFile);
#endif

	CTestControlManyDevice* CreateFrame_MdvSpo(CTestTask *pSrcTestTask
		, CTestItemViewGrid *pItemGrid, CXFolder *pFolder
		, const CString &strTemplateFile
		, const CString &strGuideBookFileType
		, const CString &strTestProjectName
		, const CString &strPpEngineProgID
		, const CString &strPpTemplateFile
		, const CString &strDeviceFile
		, CXFolder **ppNewFolder);

	CTestControlManyDevice* CreateFrame_MdvSpo(const CString &strGbBinaryFile, CTestItemViewGrid *pItemGrid, BOOL bFullPath);

protected:

	DECLARE_MESSAGE_MAP()
	
public:
	
};


