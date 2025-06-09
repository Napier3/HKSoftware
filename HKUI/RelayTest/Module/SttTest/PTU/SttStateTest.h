#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include"tmt_state_test.h"
#include "define.h"


class CSttStateTest : public CSttTestBase, public tmt_StateTest
{
public:
    CSttStateTest();
    virtual ~CSttStateTest(void);

	Drv_Result       m_oDrvResult;
	Drv_StateParas   m_oDrvStateParas;

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttStateTest();
	}
public:

	//过程参数
	Complex *m_CmpUI[2][MAX_VOLTAGE_COUNT];
    int		m_nCurStateIndex;			//当前状态序号

    UINT m_uStartTimeS;
    UINT m_uStartTimeNS;

public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
	virtual void AfterSetParameter();
//	virtual double GetTestTimeLong();
	virtual long CalReport(UINT nState=0);

     virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
    virtual void Init(long nStateNums);
	virtual BOOL IsTestFinished(DWORD dwState) {return !m_Start;}
	virtual long SetParameter(DWORD dwState=0);
//    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();
	virtual void EventProcess();
	virtual void Stop();
	virtual void Triger();


private:
	bool m_Start;
	unsigned int nPreBiVal;

};
