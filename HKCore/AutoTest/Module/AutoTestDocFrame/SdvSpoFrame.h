#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CMDIChildWnd��"
#endif 

#include "AutoTestBaseFrame.h"

class CSdvSpoFrame : public CAutoTestBaseFrame
{
	DECLARE_DYNCREATE(CSdvSpoFrame)
protected:
	CSdvSpoFrame();           // ��̬������ʹ�õ��ܱ����Ĺ��캯��
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


