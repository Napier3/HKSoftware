#pragma once

#include "../SttStateTest.h"

class CSttPsuStateTest : public CSttStateTest//, public tmt_StateTest
{
public:
    CSttPsuStateTest();
    virtual ~CSttPsuStateTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttPsuStateTest();
	}

public:
    virtual void AfterSetParameter();
    void SetPsuGradientCh(tmt_StatePara *paraState,tmt_channel *uiGradientch);
};

enum PsuGradientChannel{
    PsuGradientUa1 =0,
    PsuGradientUb1 =1,
    PsuGradientUc1 =2,
    PsuGradientUab1 =4,
    PsuGradientUbc1 =5,
    PsuGradientUca1 =6,
    PsuGradientUabc1 =7,
    PsuGradientUa2 =8,
    PsuGradientUb2 =9,
    PsuGradientUc2 =10,
    PsuGradientUab2 =27,
    PsuGradientUbc2 =28,
    PsuGradientUca2 =29,
    PsuGradientUabc2 =11,
    PsuGradientIa1 =12,
    PsuGradientIb1 =13,
    PsuGradientIc1 =14,
    PsuGradientIab1 =15,
    PsuGradientIbc1 =16,
    PsuGradientIca1 =17,
    PsuGradientIabc1 =18,
    PsuGradientIa2 =19,
    PsuGradientIb2  =20,
    PsuGradientIc2  =21,
    PsuGradientIab2  =30,
    PsuGradientIbc2  =31,
    PsuGradientIca2  =32,
    PsuGradientIabc2  =22,
    PsuGradientVoltageAll  =23,
    PsuGradientCurrentAll  =24,
    PsuGradientVdc  =25,
    PsuGradientVz  =26,
    PsuGradientIa1Ib1Ic1  =33,
    PsuGradientIa2Ib2Ic2 =34,
    PsuGradientUa1Ub1Uc1  =35,
    PsuGradientUa2Ub2Uc2  =36,
    PsuGradientAll  =37,
};




