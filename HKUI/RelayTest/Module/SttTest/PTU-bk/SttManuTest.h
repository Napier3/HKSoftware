#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include"tmt_manu_test.h"
#include "./define.h"
#include "QThread"

class CSttManuTest : public CSttTestBase, public tmt_ManualTest//,public QThread
{
public:
    CSttManuTest();
    virtual ~CSttManuTest(void);

	Drv_ManuPara     m_oDrvManuPara;
	Drv_Result       m_oDrvResult;

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttManuTest();
	}
public:
//	manualdata m_manual;
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];
public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
	virtual void AfterSetParameter();
	virtual double GetTestTimeLong();
	virtual long CalReport(UINT nState=0);

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();
	virtual void EventProcess();
    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Stop();
	virtual void UpdateParameter();
	virtual BOOL IsTestFinished(DWORD dwState) {return !m_Start;}
	virtual void TtmToDrv();

private:
	BOOL m_Start;
	int m_nVtap[4];
	int m_nITap[4];
	int m_vchannel[4];
	int m_ichannel[4];
	int m_nOverload;
//	manualdata m_channelTemp;
	 float m_fMeasValue[8];
	double m_dTestBeginTime;
//	void calcMeasTap();
	void setTap();
	void SetDeviceInnerParaSet(float *fValue);
//	virtual void run();
//	void calcNewData();
//	void setChannelData(manualdata* pdata);

	void TtmToDrv_PTU();
	void TtmToDrv_L336D();
};
