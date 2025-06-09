#pragma once
#include "../../../SttTestBase/SttTestBase.h"
#include "../../../SttTestBase/SttFaultCalculatTool.h"
#include "tmt_impedance_test.h"

class CSttImpBaseTest : public CSttTestBase//,  public tmt_ImpBaseParas
{
public:
    CSttImpBaseTest();
    virtual ~CSttImpBaseTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CSttImpBaseTest();
    }
public:
    UINT m_uStartTimeS;
    UINT m_uStartTimeNS;

	tmt_ImpBaseParas *m_pImpBaseParas;
public:
    //	virtual UINT GetClassID()         {    return TMCLASSID_STATE;    }
        virtual void AfterSetParameter();
        virtual double GetTestTimeLong();
        virtual long CalReport(UINT nState=0);
		long CalReport_ImpBase(tmt_ImpedanceParas *pImpParas,tmt_ImpedanceResults *pResult);


        virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
        virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
        virtual void Para_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
        virtual void Report_XmlSerialize_Basic(CSttXmlSerializeBase *pXmlSerialize);
		virtual void SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize){}

		virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
		{
			CSttTestBase::ReturnTestStateEvent_TestFinish(dTime,dRealTime,bWithEvent);
		}
public:
    virtual void Init();

    virtual long SetParameter(DWORD dwState=0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs);
    virtual void StartTest();
	virtual BOOL EventProcess();
    virtual void Triger();
	virtual	void SyncSingleStateTmtResult();

public:
    virtual void TtmToDrv();
	virtual void ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType);
	void TranslateToStateParas_ImpBase(tmt_ImpedanceParas *pImpParas);
	void TranslateToStateParas_ImpBase(tmt_ImpedanceParas *pImpParas,float fUnom);//参数2传递额定电压参数
	void TranslateToStateParas_ImpBase(tmt_ImpedanceParas *pImpParas,float *pfVolAmp,float *pfVolAng);//参数2和参数3分别为常态及故障态各相电压依次Ua/Ub/Uc/Uz数组长度8
	void TranslateToStateParas_FaultIncMode(tmt_ImpedanceParas *pImpParas);

	void SetStateParas_PreFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//状态1(常态)
	void SetStateParas_PreFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//状态1(常态)
	void SetStateParas_FirstFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//状态2(故障态)
	void SetStateParas_FirstFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//状态2(故障态)
	void SetStateParas_AfterFirstTrip(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//状态3(跳闸后状态)
	void SetStateParas_AfterFirstTrip(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//状态3(跳闸后状态)
	void SetStateParas_AfterRecoseTransient(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//状态4(重合后,瞬时故障)
	void SetStateParas_AfterRecoseTransient(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//状态4(重合后,瞬时故障)
	void SetStateParas_AfterRecosePermanent(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//状态5(重合后,永久故障)
	void SetStateParas_AfterRecosePermanent(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//状态5(重合后,永久故障)
	void SetStateParas_TransFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//状态6(转换故障)
	void SetStateParas_TransFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//状态6(转换故障)
	void SetStateParas_AccTrip(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//状态7(加速跳闸后)
	void SetStateParas_AccTrip(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//状态7(加速跳闸后)
	virtual void SetStateParas_StopTest(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//状态8(停止态)
	void Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
	tmt_StateResults m_oImpBaseResults;//
	CSttFaultCalculatTool m_oFaultCalculatTool;//zhouhj 20210613 用于故障计算
};


