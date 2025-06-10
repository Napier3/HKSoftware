#pragma once

#include "SttSmartTestSvrInterface.h"

class CXSmartTestEventInterface
{
public:
	CXSmartTestEventInterface()	{	m_pGuideBook = NULL;	}
	virtual ~CXSmartTestEventInterface()	{}

	CExBaseList *m_pGuideBook;

public:
	virtual void AttachGuideBook(CExBaseList *pGuideBook)	{	m_pGuideBook = pGuideBook;	}
	virtual long OnItemStateChanged(const CString& strDeviceID, long nDeviceIndex, long nReportIndex, long nItemIndex, const CString& strItemID, const CString& strState, long nSelect) = 0;
	virtual long OnTestFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex) = 0;
	virtual long OnTestStoped(const CString& strDeviceID, long nDeviceIndex, long nReportIndex) = 0;
	//virtual long OnExportRptFinished(const CString& strDeviceID, long nDeviceIndex, long nReportIndex) = 0;
	//2021.0802  shaolei
	//strEventID取值范围：ExportBegin| ExportFinish。当ExportFinish时，再调用GetReportFiles，获取每份报告的绝对路径；
	virtual long OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex) = 0;
	virtual long OnExportRptEvent(const CString& strDeviceID, const CString &strEventID, long nDeviceIndex, long nReportIndex,
		const CString strGbrptFile, const CString strDocFile, const CString strXmlFile) { return 0; }
	virtual long OnTestAppEvent(const CString& strDeviceID, const CString& strEvent) = 0;
	virtual long OnEngineEvent(const CString& strDeviceID, long nDeviceIndex, const CString& strEvent) = 0;
	virtual long OnTestCreated(const CString& strDeviceID) = 0;
	virtual long OnOpenGbrptFileFailed(const CString& strDeviceID) = 0;
	//add by shaolei  2021-08-03
	//TestID = BenchSN  strDeviceState = 合格|不合格
	virtual long OnTestProcess(const CString& strDeviceID, const CString& strTestID, long nTotalItems, long nCurrItem, long nTotalTime, long nRemainTime, const CString& strDeviceState) = 0;
	virtual long OnTestProcess(CExBaseList* pSttParas) = 0;
	virtual long OnReTestFinished(CExBaseList* pSttParas) = 0;
	//add by shaolei 20210805
	virtual long OnTestStarted(const CString& strDeviceID, long nDeviceIndex, long nReportIndex) = 0;
	virtual long OnUploadRptFile(const CString& strDeviceID, const CString &strFiles) = 0;
	//lijunqing 2022-6-26
	virtual long OnInputData(const CString& strDatas, const CString& strMsgs) = 0;
	virtual long OnInputData(CExBaseList *pSttParas, CExBaseList *pSttMsgs) = 0;  //lijunqing 2022-6-27  直接传入数据对象，方便处理对象转换为XML或者JSON等不同的格式
	virtual long On_Ats_CreateTest(const CString &strGbrptFile) = 0;  //shaolei 20220707  CreateTest的REPLY，返回gbrptfile的全路径
	virtual long On_Ats_AdjustMainWnd(LONG nMainWnd) = 0;  //shaolei 20220718  AdjustMainWnd的REPLY，返回SmartTest的MainWnd
};

//2021-8-3  lijunqing 总的接口，方便访问
class CXSttSmartTestXInterface : public CXSmartTestEventInterface, public CSttSmartTestSvrInterface
{
public:
	CString m_strID;
	CXSttSmartTestXInterface()	{}
	virtual ~CXSttSmartTestXInterface()	{}

	CString m_strReportPath;  //报告文件路径  2023-9-12  lijunqing
};
