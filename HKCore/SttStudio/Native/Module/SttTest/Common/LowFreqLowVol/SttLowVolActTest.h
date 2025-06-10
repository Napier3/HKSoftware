#pragma once

#include "../SttStateTest.h"
#include "tmt_low_vol_test.h"


class CSttLowVolActTest : public CSttStateTest ,public tmt_LowVolParas
{
public:
    CSttLowVolActTest();
    virtual ~CSttLowVolActTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttLowVolActTest();
	}
public:

	virtual void Init();
	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent);
	virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent);
	virtual BOOL IsGradientFinished();

protected:
	virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数
    virtual BOOL CalNext();

	long m_nRunSearchCount;//当前运行搜索的次数,初始值为1
	long m_nGradientCount;//递变总次数,初始化为0 ,在参数设置后设定该值
	tmt_LowVolResults m_oResults;
};
