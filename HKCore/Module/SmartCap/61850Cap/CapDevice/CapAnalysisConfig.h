#pragma once
#include "../../../BaseClass/ExBaseObject.h"

class CCapAnalysisConfig : public CExBaseObject
{
public:
	CCapAnalysisConfig();	
	virtual ~CCapAnalysisConfig();

public:
	bool m_bSmvSyncDelt;   // SVͬ����
	bool m_bAnalysisData_DelayTime;  //SV��ʱ
	bool m_bAnalysisData_Complex;  //�������
	bool m_bAnalysisData_PhaseDelt;  //�ǲ�
	bool m_bMaxTimeDiscrete; //SV��ɢ��
	bool m_bPkgConsistence; //��鱨��һ����
	bool m_bGsAnalysis;   // GSͬ����
	bool m_bMU_Test;//20220618 zhouhj����MU���Ե���ز�����
	bool m_bChQualitySpy;//ͨ��Ʒ�ʼ���
	bool m_bStateValueChangedAnalysis;  //2024.5.29 chenling ״̬���仯

	bool m_bSvAnalysis;  //�Ƿ�ִ�б��ķ������쳣������һ���Է�������ʱ�ȵ�

	bool m_bSmv_AD;       //�Ƿ����˫AD���ݼ�
	bool m_bSmv_Power;   //�Ƿ���¹������ݼ�
	bool m_bSmv_Vector;  //�Ƿ����ʸ��ͼ���ݼ�

	bool m_bUseCapRecord;  //2022-6-19  lijunqing �Ƿ�ʹ��¼�����ݣ���CapRecord�Ƿ�������

// 	double m_dCT_PrimaryValue;//A//20220612 ������������δ����IEC����ӳ��ı��
// 	double m_dCT_SecondValue;//A
// 	double m_dPT_PrimaryValue;//kV
// 	double m_dPT_SecondValue;//V
	long m_nShowPrimaryValue;

	double m_fCT_Rate[6];//zhouhj 20220812 CT���ֵ ��IEC������SV���ձ�ȱ���һ��
	double m_fPT_Rate[6];//zhouhj 20220812 PT���ֵ ��IEC������SV���ձ�ȱ���һ��

public:
	void DisableAll();
	void EnableRcdCal(long nEnable=1);
	void EnableRcdHarmCal(long nEnable=1);

	void Smv_EffecValue();	//��Чֵ
	void Smv_Wave();	//���η���
	void Smv_Vector();	  //����
	void Smv_Sequence();	//�����
	void Smv_Power();	   //����
	void Smv_Harm();	//г��
	void Smv_Polar();	   //����
	void Smv_PkgError();	  //����ͳ��  2022-6-19  ��ΪError����ǿ�ɶ���
	void Smv_AD();	  //˫AD����
	void Smv_PkgAnalyze();	  //���ķ���
	void Smv_MUAccuracy();  //MU��ȷ��
	void Smv_MUErrorStatistics();  //MU���ͳ��
	void Smv_ChQualitySpy();//ͨ��Ʒ�ʼ���

	void Goose_RT();	//ʵʱֵ
	void Goose_TurnList();	  //��λ�б�
	void Goose_PkgStc();	//����ͳ��
	void Goose_PkgAnalyze();	//���ķ���
	void Goose_TurnSpy();	   //��λ����

	void FT3_RT();	//ʵʱֵ
	void FT3_OriginalMsg();	//ԭʼ����

public:
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual BSTR GetXmlElementKey()	{      return m_strCapAnalysisCfgKey;	}

	BOOL Open();
	BOOL Save();

private:
	static BSTR m_strCapAnalysisCfgKey;
	static BSTR m_strCT_PrimaryValueKey;
	static BSTR m_strCT_SecondValueKey;
	static BSTR m_strPT_PrimaryValueKey;
	static BSTR m_strPT_SecondValueKey;
	static BSTR m_strShowPrimaryValueKey;


};


extern CCapAnalysisConfig g_oCapAnalysisConfig;
extern BOOL g_bSmartCap_RecordNow; 
extern BOOL g_bIsParsingPkg;

//2022-5-3  lijunqing enable harm cal  functions
extern long g_nEnableCal_Root;//  = 1 ;

extern long g_nEnableCal_Harm02Value;//  = 1 ;
extern long g_nEnableCal_Harm03Value;//  = 1 ;
extern long g_nEnableCal_Harm04Value;//  = 1 ;
extern long g_nEnableCal_Harm05Value;//  = 1 ;
extern long g_nEnableCal_Harm06Value;//  = 1 ;
extern long g_nEnableCal_Harm07Value;//  = 1 ;
extern long g_nEnableCal_Harm08Value;//  = 1 ;
extern long g_nEnableCal_Harm09Value;//  = 1 ;
extern long g_nEnableCal_Harm10Value;//  = 1 ;
extern long g_nEnableCal_Harm11Value;//  = 1 ;
extern long g_nEnableCal_Harm12Value;//  = 1 ;
extern long g_nEnableCal_Harm13Value;//  = 1 ;
extern long g_nEnableCal_Harm14Value;//  = 1 ;
extern long g_nEnableCal_Harm15Value;//  = 1 ;
extern long g_nEnableCal_Harm16Value;//  = 1 ;
extern long g_nEnableCal_Harm17Value;//  = 1 ;
extern long g_nEnableCal_Harm18Value;//  = 1 ;
extern long g_nEnableCal_Harm19Value;//  = 1 ;
extern long g_nEnableCal_Harm20Value;//  = 1 ;
extern long g_nEnableCal_Harm21Value;//  = 1 ;
extern long g_nEnableCal_Harm22Value;//  = 1 ;
extern long g_nEnableCal_Harm23Value;//  = 1 ;
extern long g_nEnableCal_Harm24Value;//  = 1 ;
extern long g_nEnableCal_Harm25Value;//  = 1 ;

