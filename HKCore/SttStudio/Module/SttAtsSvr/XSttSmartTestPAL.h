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

	//�������沿�֣���ͬ�ķ��񳡾�����ʽ��һ�¡���˲����麯������
	virtual long Pre_Ats_ExportReport(CSttAtsCmd *pAtsCmd);   //2023-8-31 lijunqing ִ���Զ����Դ����������߳���Ϣ��������
	virtual long Pre_Ats_ExportReport_single(CSttAtsCmd *pAtsCmd);   
	virtual long Pre_Ats_ExportReport_docs(CSttAtsCmd *pAtsCmd);  
	virtual long Pre_Ats_ExportReport_gbrpts(CSttAtsCmd *pAtsCmd); 
	long Pre_Ats_ExportReport_TestInfo(CTestControlBase *pTestControl, CDataGroup *pTestInfo); //������Ϣ��������Ŀ
	long Pre_Ats_ExportReport_TaskInfo(CTestControlBase *pTestControl, CDataGroup *pTaskInfo);  //����������Ϣ
	long Pre_Ats_ExportReport_SampleInfo(CTestControlBase *pTestControl, CDataGroup *pSampleInfo);  //������Ʒ��Ϣ
	long Pre_Ats_ExportReport_TestAppInfo(CTestControlBase *pTestControl, CDataGroup *pTestAppInfo);  //����������Ϣ
	long Pre_Ats_ExportReport_SingleRpt(CGuideBook *pGuideBook, CDataGroup *pRpt);  
};