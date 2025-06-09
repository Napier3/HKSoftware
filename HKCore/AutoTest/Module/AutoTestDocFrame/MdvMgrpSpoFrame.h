#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CMDIChildWnd。"
#endif 

#include "MRptBaseFrame.h"

class CMdvMgrpSpoFrame : public CMRptBaseFrame
{
	DECLARE_DYNCREATE(CMdvMgrpSpoFrame)
protected:
	CMdvMgrpSpoFrame();           // 动态创建所使用的受保护的构造函数
	virtual ~CMdvMgrpSpoFrame();


public:

	CMdvMgrpSpoDeviceMngrTestControl* CreateFrame_MdvMgrpSpo(CTestItemViewGrid *pItemGrid, CXFolder *pFolder
		, const CString &strTasksFile, CXFolder **ppNewFolder);

	CMdvMgrpSpoDeviceMngrTestControl* CreateFrame_MdvMgrpSpo(CXFileMngr *pXFileMngr, const CString &strGbBinaryFile, CTestItemViewGrid *pItemGrid, BOOL bFullPath);

protected:
// 	CMdvMgrpSpoDeviceTestControl* CreateFrame_MdvMgrpSpo_Task(CTestItemViewGrid *pItemGrid, CXFolder *pParentFolder
// 		, CGuideBook *pGuideBook, CTestTask *pTestTask, CXFolder **ppNewTaskFolder);
	CXFolder* CreateMdvMgrpFolders(CTestTasks *pTestTasks, CXFolder *pFolder);
	void CreateMdvMgrpTaskFolders(CTestTasks *pTestTasks, CXFolder *pMdvMgrpFolder);

protected:

	DECLARE_MESSAGE_MAP()
	
public:
	
};


