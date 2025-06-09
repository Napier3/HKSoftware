#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CMDIChildWnd��"
#endif 

#include "MRptBaseFrame.h"

class CSdvSpoMgrpFrame : public CMRptBaseFrame
{
	DECLARE_DYNCREATE(CSdvSpoMgrpFrame)
protected:
	CSdvSpoMgrpFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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


