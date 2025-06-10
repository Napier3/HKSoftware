#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include "GradientBase.h"
#include "tmt_gradient_test.h"

#ifdef _PSX_IDE_QT_
#include "drv_gradient_test.h"
#include "drv_manugradient_def.h"
#endif



class CSttGradientTest : public CGradientBase, public tmt_GradientTest
{
public:
    CSttGradientTest();
    virtual ~CSttGradientTest(void);

#ifdef _PSX_IDE_QT_
	drv_manu_gradient_test m_oDrvManuGradient;
#endif
	structRampResult  m_oDrvResults;

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttGradientTest();
	}
public:


public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
	virtual void AfterSetParameter();
	virtual double GetTestTimeLong();
	virtual long CalReport(UINT nState=0);

public:
    virtual void Init();
    virtual void CalStepValue(float fCurValue);
	virtual long SetParameter(DWORD dwState=0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();
	virtual void Stop();

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

    //将上层结构体转为底层结构体
public:
    virtual void TtmToDrv();
};
