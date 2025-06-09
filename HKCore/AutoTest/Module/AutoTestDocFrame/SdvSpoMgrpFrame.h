#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CMDIChildWnd。"
#endif 

#include "MRptBaseFrame.h"

class CSdvSpoMgrpFrame : public CMRptBaseFrame
{
	DECLARE_DYNCREATE(CSdvSpoMgrpFrame)
protected:
	CSdvSpoMgrpFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CSdvSpoMgrpFrame();


public:

	CTestControlManyReport* CreateFrame_SdvSpoMgrp(CTestItemViewGrid *pItemGrid, CXFolder *pFolder
		, const CString &strTemplateFile
		, const CString &strGuideBookFileType
		, const CString &strTestProjectName
		, const CString &strPpEngineProgID
		, const CString &strPpTemplateFile
		, const CString &strDeviceFile
		, const CString &strTestType
		, CDvmDataset *pExpandDatas
		, CXFolder **ppNewFolder);

	CTestControlManyReport* CreateFrame_SdvSpoMgrp(const CString &strGbBinaryFile, CTestItemViewGrid *pItemGrid, BOOL bFullPath);
	CTestControlManyReport* CreateFrame_SdvSpoMgrp(CTestControlManyReport *pTestControlManyReport, CTestItemViewGrid *pItemGrid);

protected:

	DECLARE_MESSAGE_MAP()
	
public:
	
};


