#pragma once

#define USE_SttImpBaseTest

#ifdef USE_SttImpBaseTest
#include "SttImpBaseTest.h"
#else
#include "../SttStateTest.h"
#endif

#include "tmt_distance_test.h"

#ifdef USE_SttImpBaseTest
class CSttDisTanceTest : public CSttImpBaseTest ,virtual public tmt_DistanceParas
#else
class CSttDisTanceTest : public CSttStateTest ,virtual public tmt_DistanceParas
#endif
{
public:
    CSttDisTanceTest();
    virtual ~CSttDisTanceTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttDisTanceTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize){}
    virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
    {
#ifdef USE_SttImpBaseTest
		CSttImpBaseTest::ReturnTestStateEvent_TestStart(dTime,dRealTime,bWithEvent);
#else
        CSttStateTest::ReturnTestStateEvent_TestStart(dTime,dRealTime,bWithEvent);
#endif
    }

	virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
	{
#ifdef USE_SttImpBaseTest
		CSttImpBaseTest::ReturnTestStateEvent_TestFinish(dTime,dRealTime,bWithEvent);
#else
		CSttStateTest::ReturnTestStateEvent_TestFinish(dTime,dRealTime,bWithEvent);
#endif
	}

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);

protected:
	virtual void TranslateToStateParas();//在此函数中实现将重合闸后加速参数转换为状态序列参数

	tmt_DistanceResults m_oDistanceResults;
};
