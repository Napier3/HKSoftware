#pragma once

/*
	功能描述：自动测试的接口App
*/
#include "AtsRpc\AtsRpcServerGlobalApi.h"
#include "AutoTestGlobalDefine.h"

//////////////////////////////////////////////////////////////////////////
//class CXSmartTestClientInterface

class CXSmartTestClientInterface
{
public:
	CXSmartTestClientInterface(){};
	virtual ~CXSmartTestClientInterface(){};

public:
	virtual BOOL InitXSmartTestClient(const CString &strTestAppIP = _T(""))	{	return TRUE;	};
	virtual void ExitXSmartTestClient()	{	};

	virtual long CreateTest(CExBaseList *pSttParas)	{	return 0;	}
	virtual long CreateTest(const CString &strTestDefine)	{	return 0;	}
	virtual long BeginTest(const CString &strDeviceID)	{	return 0;	}
	virtual long StopTest(const CString &strDeviceID)	{	return 0;	}
	virtual long Retest(const CString &strDeviceID, const CString &strCommConfig)	{	return 0;	}
	virtual long ExportRpt(const CString &strDeviceID)	{	return 0;	}
	virtual long CloseTest(const CString &strDeviceID)	{	return 0;	}
	virtual long ViewItemRpt(const CString &strDeviceID, long nItemIndex)	{	return 0;	}
	virtual long TestAllInlegibleItems(const CString &strDeviceID)	{	return 0;	}
	virtual long TestPoint(const CString &strDeviceID, const CString &strItemPath)	{	return 0;	}
	virtual long TestBelow(const CString &strDeviceID, const CString &strItemPath)	{	return 0;	}
	virtual long OpenGbrptFile(const CString &strFilePath, const CString &strSmartTestRunMode, long nDeviceIndex=-1)	{	return 0;	}  //默认参数 -1 表示测两台装置
	virtual CString GetAllTestItems(const CString &strDeviceID)	{	return _T("");	}
	virtual CString GetTestItemReports(const CString &strDeviceID)	{	return _T("");	}
	virtual long SetAppVisible(long nVisible)	{	return 0;	}
	virtual long FinishInputData(const CString& strDeviceID, const CString& strReports)	{	return 0;	}
	virtual long SetItemStateEx(const CString& strItemPath, long nSelect, long nEnable, long nShow, long nState)	{	return 0;	}
	virtual long AddEventSink(const CString &strEventSinkProgID, const CString& strDeviceID)	{	return 0;	}
	virtual long RemoveEventSink(const CString &strEventSinkProgID, const CString& strDeviceID)	{	return 0;	}
	virtual long ClearReport(const CString &strDeviceID)	{	return 0;	}
	virtual long GetReports(const CString &strDeviceID, const CString &strItemPath, char **ppszReports)	{	return 0;	}
	virtual long GetReports(const CString &strDeviceID, const CString &strItemPath, CExBaseList *pRetSttReports)	{	return 0;	}
	virtual long SetReports(const CString &strDeviceID, const CString &strItemPath, const CString &strReports)	{	return 0;	}
	virtual long QueryItems(const CString &strDeviceID, const CString &strItemPath, char **ppszItems)	{	return 0;	}
	virtual long ConfigTest(const CString &strDeviceID, const CString &strConfig)	{	return 0;	}
	virtual long QueryAtsFile(const CString &strDeviceID, const CString &strConfig)	{	return 0;	}
	virtual CString GetDataset(const CString &strDatasetPath)	{	return _T("");	}
	virtual long SetDataset(const CString &strDatasetPath, const CString &strDataset)	{	return 0;	}
	virtual long RunProcedure(const CString &strProcedureID, const CString &strParas)	{	return 0;	}
	virtual long SetItemState(const CString &strParas)	{	return 0;	}
	virtual long SetItemState(CExBaseList *pSttParas)	{	return 0;	}

	virtual long GetGuideBook(const CString &strDeviceID, char **ppszGuideBookUft8)	{	return 0;	}

	virtual long GetReportFiles(const CString &strDeviceID, CString &strFile)	{	return 0;	}

	virtual long GetTotalItemsCount(const CString &strDeviceID, long &nCount)	{	return 0;	}
	virtual long QueryTestParas(const CString &strDeviceID, CString &strTestParas)	{	return 0;	}
	virtual long SetTestParas(const CString &strDeviceID, CString &strTestParas)	{	return 0;	}
	virtual long AdjustMainWnd(LONG hMainParent, LONG hLogParent)	{	return 0;	}
	virtual long AttatchLogWnd(unsigned long hWnd)	{	return 0;	}  //shaolei 20220516
};
