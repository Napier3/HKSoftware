#pragma once

#include "SttSmartTest.h"

class CXSmartTestPAL : public CSttSmartTest
{
public:
    CXSmartTestPAL();
    virtual ~CXSmartTestPAL();

	static long g_nXSttSmartTestPALRef;
	static CXSmartTestPAL* g_pXSttSmartTestPAL;
	static CXSmartTestPAL* Create();
	static void Release();

	//导出报告部分，不同的服务场景，方式不一致。因此采用虚函数重载
	virtual long Pre_Ats_ExportReport(CSttAtsCmd *pAtsCmd);   //2023-8-31 lijunqing 执行自动测试创建，被主线程消息函数调用
	virtual long Pre_Ats_ExportReport_single(CSttAtsCmd *pAtsCmd);   
	virtual long Pre_Ats_ExportReport_docs(CSttAtsCmd *pAtsCmd);  
	virtual long Pre_Ats_ExportReport_gbrpts(CSttAtsCmd *pAtsCmd); 
	long Pre_Ats_ExportReport_TestInfo(CTestControlBase *pTestControl, CDataGroup *pTestInfo); //测试信息：测试项目
	long Pre_Ats_ExportReport_TaskInfo(CTestControlBase *pTestControl, CDataGroup *pTaskInfo);  //测试任务信息
	long Pre_Ats_ExportReport_SampleInfo(CTestControlBase *pTestControl, CDataGroup *pSampleInfo);  //测试样品信息
	long Pre_Ats_ExportReport_TestAppInfo(CTestControlBase *pTestControl, CDataGroup *pTestAppInfo);  //测试仪器信息
	long Pre_Ats_ExportReport_SingleRpt(CGuideBook *pGuideBook, CDataGroup *pRpt);  
};