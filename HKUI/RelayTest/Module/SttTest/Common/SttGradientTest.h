#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include "tmt_gradient_test.h"

#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif

class CSttGradientTest : public CSttTestBase,public tmt_GradientTest
{
public:
    CSttGradientTest();
    virtual ~CSttGradientTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttGradientTest();
	}

	float m_fAngleF;
	float m_fAngleS;
	float m_fMaxAngle;
public:


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
	virtual BOOL EventProcess();

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	void Gouts_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);//zhouhj 20210903 ���߼��������

    virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent)
    {
        CSttTestBase::ReturnTestStateEvent_TestStart(dTime,dRealTime,bWithEvent);
    }

	virtual void ReturnTestStateEvent_TestFinish(double dTime, double dRealTime, bool bWithEvent)
	{
		CSttTestBase::ReturnTestStateEvent_TestFinish(dTime,dRealTime,bWithEvent);
	}

	virtual void SyncGradientResult(int nStep,double dTime,int nTripType){}//nTripType: 0-������ 1-���ض�

public://zhouhj 20210703 �߼��������غ���
	virtual void InitParaBeforeGradient(tmt_GradientParas *pTmt_GradientParas,long nGradientChCount = 3)
	{
		CSttTestBase::InitParaBeforeGradient(pTmt_GradientParas,nGradientChCount);
	}

	virtual void CalStepValue_Gradient(tmt_GradientParas *pTmt_GradientParas,int nHarmIndex = 1,long nGradientChCount = 3)
	{
		CSttTestBase::CalStepValue_Gradient(pTmt_GradientParas,nHarmIndex,nGradientChCount);
	}

	virtual void CalStepValue(tmt_GradientParas *pTmt_GradientParas,float fCurValue,int nHarmIndex)
	{
		CSttTestBase::CalStepValue(pTmt_GradientParas,fCurValue,nHarmIndex);
	}

	virtual void SetUIParaToStepUI(tmt_channel *uData, tmt_channel *iData, tmt_StepUI *pUIStepData, int nHarmIndex)
	{
		CSttTestBase::SetUIParaToStepUI(uData,iData,pUIStepData, nHarmIndex);
	}

	void AngleTestTransPara(BOOL bCCW=TRUE);//Ĭ����ʱ��
	float GetStdAngle(float fCurAngle);// zhouhj 20210830  ��ȡ��׼�Ƕ�,����������ȥ�ĽǶ�ת��Ϊ0-360��Χ�ڵĽǶ�
  //���ϲ�ṹ��תΪ�ײ�ṹ��
public:
    virtual void TtmToDrv();
	virtual void ProRtDatasEvent(double dTime1,double dTime2,int nStep,int nState, int nType);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	void ProRtDatasEvent_FixSteps(double dTime1,double dTime2,int nStep,int nType);//zhouhj 20210923 ���ڸ߼�����ģ��ÿ����������仯ֵʱ,����ʵʱ����
	//��̬������ǰ��������,���ݵ�ǰ���õ�������
	void InitBeforeFaultParas_BySequenceSet(tmt_GradientParas *pTmt_GradientParas);
	void CalSequence_ByABC(float fMagA, float fAngA,float fMagB, float fAngB,float fMagC, float fAngC,long nMode,float &fMagDest, float &fAngDest);
};
