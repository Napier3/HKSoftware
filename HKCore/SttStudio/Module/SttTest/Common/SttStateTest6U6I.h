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

// 	//���̲���
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

	void Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);//zhouhj 20210903 ���߼��������

public:
	virtual void Init();

	virtual long SetParameter(DWORD dwState=0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();
	virtual void Stop(){CSttTestBase::Stop();}
	virtual BOOL EventProcess();
	virtual void Triger();

public://zhouhj 20210613���º������ڹ��ϲ���ת��
	void SetStateBout(tmt_BinaryOut *pStateBinaryOut,tmt_BinaryOut *pBinaryOut,long nBoutCount = 8);

    //���ϲ�ṹ��תΪ�ײ�ṹ��
public:
    virtual void TtmToDrv();
	virtual void ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType);
	virtual void SyncSingleStateTmtResult();

protected:
	CSttFaultCalculatTool m_oFaultCalculatTool;//zhouhj 20210613 ���ڹ��ϼ���
};

void Global_SetStateUIFromCpl(tmt_StatePara *pStatePara,Complex *pVol_Complex,Complex *pCur_Complex);//����ѹ����ʸ��ֵ��ֵ��״̬����
void Global_SetStateBinPreFault(tmt_StatePara *pStatePara);//���ù���ǰ�����������Ŀ����߼�������ѡ��
void Global_SetStateBoutPreFault(tmt_StatePara *pStatePara,long *pnStateBOut,long nOutputSwitchMode,float fBoutTimeTrig,float fBoutHoldTime);
void Global_FaultCalculatUI(tmt_ImpedanceParas *pImpParas,int nFaultIndex,Complex *pVol_Complex,Complex *pCur_Complex);
void Global_SetStateBinFault(tmt_StatePara *pStatePara,tmt_BinaryIn *pBinaryIn,int nBinLogic);//���ù���̬����
void Global_SetStateBinFault(tmt_StatePara *pStatePara,long *pnStateBInput,long nBinSelect);//���ù���̬����
void Global_SetStateBinReclose(tmt_StatePara *pStatePara,long *pnStateBOut,long nBinSelect);//�����غ�̬����
	////����1:����Index(��һ�ι��ϡ��ڶ��ι���)����2:��ѹʸ����ָ�����3:����ʸ����ָ�����4:�Ƿ�Ϊ�����������ϼ���
void Global_SetStateI_AfterTripFromFaultType(tmt_StatePara *pStatePara,long nFaultType,long *pnDInputState,int nBinSelect);
void Global_AddSimulateBreakTimeToResults(tmt_ImpedanceParas *pImpParas,tmt_ImpedanceResults *pResult);//zhouhj 20211105 �ڲ��Խ��������ģ���·������ʱʱ��



