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
	void TranslateToStateParas_ImpBase(tmt_ImpedanceParas *pImpParas,float fUnom);//����2���ݶ��ѹ����
	void TranslateToStateParas_ImpBase(tmt_ImpedanceParas *pImpParas,float *pfVolAmp,float *pfVolAng);//����2�Ͳ���3�ֱ�Ϊ��̬������̬�����ѹ����Ua/Ub/Uc/Uz���鳤��8
	void TranslateToStateParas_FaultIncMode(tmt_ImpedanceParas *pImpParas);

	void SetStateParas_PreFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//״̬1(��̬)
	void SetStateParas_PreFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//״̬1(��̬)
	void SetStateParas_FirstFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//״̬2(����̬)
	void SetStateParas_FirstFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//״̬2(����̬)
	void SetStateParas_AfterFirstTrip(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//״̬3(��բ��״̬)
	void SetStateParas_AfterFirstTrip(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//״̬3(��բ��״̬)
	void SetStateParas_AfterRecoseTransient(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//״̬4(�غϺ�,˲ʱ����)
	void SetStateParas_AfterRecoseTransient(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//״̬4(�غϺ�,˲ʱ����)
	void SetStateParas_AfterRecosePermanent(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//״̬5(�غϺ�,���ù���)
	void SetStateParas_AfterRecosePermanent(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//״̬5(�غϺ�,���ù���)
	void SetStateParas_TransFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//״̬6(ת������)
	void SetStateParas_TransFault(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//״̬6(ת������)
	void SetStateParas_AccTrip(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//״̬7(������բ��)
	void SetStateParas_AccTrip(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float *pfVolAmp,float *pfVolAng);//״̬7(������բ��)
	virtual void SetStateParas_StopTest(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//״̬8(ֹ̬ͣ)
	void Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

protected:
	tmt_StateResults m_oImpBaseResults;//
	CSttFaultCalculatTool m_oFaultCalculatTool;//zhouhj 20210613 ���ڹ��ϼ���
};


