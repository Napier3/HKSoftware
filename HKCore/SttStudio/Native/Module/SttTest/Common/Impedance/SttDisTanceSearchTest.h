#pragma once


#include "SttDisTanceTest.h"
#include "tmt_distance_search_test.h"

#define USE_COMPLEX_SEARCH_MODE           //zhouhj 20211119 �迹������ʽ��ԭPowerTest�е�ģʽ��Ϊʹ�ù���ģ���tmt_ComplexSearch���еĺ���ģʽ


class CSttDisTanceSearchTest : public CSttDisTanceTest
{
public:
    CSttDisTanceSearchTest();
    virtual ~CSttDisTanceSearchTest(void);

	static CString m_strMacroName;
	static CString m_strMacroID;
	static CString m_strMacroVer;
	static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
	{
        return new CSttDisTanceSearchTest();
	}
public:

	virtual void AfterSetParameter();
	virtual long CalReport(UINT nState=0);

	virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void Report_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void SearchReport_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
	virtual void ReturnTestStateEvent_TestStart(double dTime, double dRealTime, bool bWithEvent);
	virtual void ReturnTestStateEvent_SearchPoint(double dTime, double dRealTime, bool bWithEvent);
	virtual void SetStateParas_StopTest(tmt_StatePara *pStatePara,tmt_ImpedanceParas *pImpParas,Complex *pVol_Complex,Complex *pCur_Complex,float fStdLN_Vol);//״̬8(ֹ̬ͣ)

public:
    virtual void Init();
	virtual long SetParameter(DWORD dwState=0);

public:
#ifndef USE_COMPLEX_SEARCH_MODE
	int		m_nRunSearchCount;//��ǰ���������Ĵ���,��ʼֵΪ1
	BOOL	m_bJudge1;
	BOOL	m_bJudge2;
	BOOL	m_bTempResultJudge;


	Complex m_fZStart;		//�׶��迹
	Complex m_fZEnd;		//ĩ���迹
	Complex m_fZStep;		//�迹����
	Complex m_fZCurrent;	//��ǰ�����迹
#endif

protected:
	virtual void TranslateToStateParas();//�ڴ˺�����ʵ�ֽ��غ�բ����ٲ���ת��Ϊ״̬���в���

#ifndef USE_COMPLEX_SEARCH_MODE
	BOOL ActProcess(float fTime);	//���������Ƿ��ѽ�������Ϣ
	BOOL CalNext();
#endif

private:
	tmt_DistanceSearchParas m_oParas;
	tmt_DistanceSearchResults m_oDistanceSearchResults;
};
