#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include"tmt_state_test.h"
#include "Impedance/tmt_impedance_test.h"

#include "../../SttTestBase/SttFaultCalculatTool.h"

#ifdef _PSX_IDE_QT_
#include "../../SttDevice/SttDeviceBase.h"
#endif

class CSttStateTest : public CSttTestBase//, public tmt_StateTest
{
public:
    CSttStateTest();
    virtual ~CSttStateTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttStateTest();
	}
public:

// 	//过程参数
// 	Complex m_CmpUI[2][MAX_VOLTAGE_COUNT];    

    UINT m_uStartTimeS;
    UINT m_uStartTimeNS;

	tmt_StateTest *m_pStateTest;
public:
//	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
	virtual void AfterSetParameter();
	virtual double GetTestTimeLong();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
	{
		CSttTestBase::ReturnTestStateEvent_TestStart(dTime,dRealTime,bWithEvent);
	}

	virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
	{
		CSttTestBase::ReturnTestStateEvent_TestFinish(dTime,dRealTime,bWithEvent);
	}

	virtual void SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize){}

	void Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);//zhouhj 20210903 供高级试验调用

public:
	virtual void Init();

	virtual long SetParameter(DWORD dwState=0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();
	virtual void Stop(){CSttTestBase::Stop();}
	virtual BOOL EventProcess();
	virtual void Triger();

public://zhouhj 20210613以下函数用于故障参数转换
	void SetStateBout(tmt_BinaryOut *pStateBinaryOut,tmt_BinaryOut *pBinaryOut,long nBoutCount = 8);

    //将上层结构体转为底层结构体
public:
    virtual void TtmToDrv();
	virtual void ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType);
	virtual void SyncSingleStateTmtResult();

protected:
	CSttFaultCalculatTool m_oFaultCalculatTool;//zhouhj 20210613 用于故障计算
};

void Global_SetStateUIFromCpl(tmt_StatePara *pStatePara,Complex *pVol_Complex,Complex *pCur_Complex);//将电压电流矢量值赋值给状态序列
void Global_SetStateBinPreFault(tmt_StatePara *pStatePara);//设置故障前开入量触发的开入逻辑及开入选择
void Global_SetStateBoutPreFault(tmt_StatePara *pStatePara,long *pnStateBOut,long nOutputSwitchMode,float fBoutTimeTrig,float fBoutHoldTime);
void Global_FaultCalculatUI(tmt_ImpedanceParas *pImpParas,int nFaultIndex,Complex *pVol_Complex,Complex *pCur_Complex);
void Global_SetStateBinFault(tmt_StatePara *pStatePara,tmt_BinaryIn *pBinaryIn,int nBinLogic);//设置故障态开入
void Global_SetStateBinFault(tmt_StatePara *pStatePara,long *pnStateBInput,long nBinSelect);//设置故障态开入
void Global_SetStateBinReclose(tmt_StatePara *pStatePara,long *pnStateBOut,long nBinSelect);//设置重合态开入
	////参数1:故障Index(第一次故障、第二次故障)参数2:电压矢量首指针参数3:电流矢量首指针参数4:是否为过流保护故障计算
void Global_SetStateI_AfterTripFromFaultType(tmt_StatePara *pStatePara,long nFaultType,long *pnDInputState,int nBinSelect);
void Global_AddSimulateBreakTimeToResults(tmt_ImpedanceParas *pImpParas,tmt_ImpedanceResults *pResult);//zhouhj 20211105 在测试结果中增加模拟断路器的延时时间



