#pragma once

#include "../SttStateTest.h"
#include "tmt_dc_increment_test.h"


class CSttDcIncrementTest : public CSttStateTest ,public tmt_DcIncrementParas
{
public:
    CSttDcIncrementTest();
    virtual ~CSttDcIncrementTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttDcIncrementTest();
	}
public:

	virtual void Init();
	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent);
	virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent);
	virtual void SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void SyncSingleStateTmtResult();
//	virtual BOOL IsGradientFinished();

protected:
//	BOOL CalNext();
	virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数
	long GetDcIncActTime(float &fAcgtTime);

// 	long m_nRunSearchCount;//当前运行搜索的次数,初始值为1
// 	long m_nGradientCount;//递变总次数,初始化为0 ,在参数设置后设定该值
	tmt_DcIncrementResults m_oResults;
};
