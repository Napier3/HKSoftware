#pragma once

#include "../../tmt_test_paras_head.h"
#include "../../tmt_common_def.h"
#include "../../SearchBase/tmt_search_base.h"

#define BP2_DIFF_U_LOCK_TYPE_UA                              0
#define BP2_DIFF_U_LOCK_TYPE_UAB                             1
#define BP2_DIFF_U_LOCK_TYPE_3U0                             2
#define BP2_DIFF_U_LOCK_TYPE_U2                              3

	
typedef struct tmt_bp2_diff_paras :public tmt_SearchBase
{
	int		m_nTestType;	//�������ͣ���������Ҫ��ÿ����������д����	0-����������1-�����ƶ���2-��������
	int		m_nDiffType;	//����ģʽ 0-������� 1-С������
	float	m_fUmag[3];			//�����ѹ��ֵ
	float	m_fUang[3];			//�����ѹ��λ
	float	m_fIdSetting;	//�������ֵ���������ã�ר��ģ�壩

	//����ֵ
	float	m_fIcdqd;//����������ż�ֵ 0.500In��A	���Լ���IBIAS��������
	float m_fCompoundKh;//��ʽ����ϵ����ֵ
	float m_fCompoundKl;//��ʽ����ϵ����ֵ
	float m_fTA1;
	float m_fTA2;
	float m_fTA3;
	float m_fTAmax;
	
	//ͨ�ò���
	float m_fPreFaultTime;	//����ǰʱ�� 1.000
	float m_fFaultTime;		//����ʱ�� 0.500
	float m_fAfterFaultTime;//���Ϻ����ʱ��

	//�����
	float	m_fIdiff;		//�����
	float	m_fIr_Id;		//��ʽ�����ƶ������꼴��Ir-Id��

	int    m_nULockType;//��ѹ����Ԫ��ѡ��  0-Ua   1-Uab   2-U0   3-U2
	float  m_fULockValue;//������ѹֵ

	//������
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryIn  m_binInEx[MAX_ExBINARY_COUNT];
	tmt_BinaryOut m_binOut[MAX_BINARYOUT_COUNT];	
	tmt_BinaryOut m_binOutEx[MAX_ExBINARY_COUNT];
	int	m_nBinLogic;			//0-�� 1-��
	int m_nAutoSearch;	//�Ƿ��Զ����� (0:�ֶ�����;1:�Զ�����)
	
	//��λ������
	int  m_nKAType;							//0:��ֵ  1:��ֵ
	char m_pszId[PARAS_RSLT_EXPR_LEN];		//Id���ʽ
	char m_pszIrId[PARAS_RSLT_EXPR_LEN];	//Ir-Id���ʽ
public:
	virtual void init()
	{
		tmt_SearchBase::InitSearch();
		m_nTestType = 0;	//Ĭ�ϲ�����������
		m_nDiffType = 0;
		m_fUmag[0]=57.74f;
		m_fUmag[1]=57.74f;
		m_fUmag[2]=57.74f;
		m_fUang[0]=0.0f;
		m_fUang[1]=-120.0f;
		m_fUang[2]=120.0f;
		m_fIdSetting = 1;

		m_fCompoundKh = 0.85f;
		m_fCompoundKl = 0.5f;

		m_fTA1 = 120.0f;
		m_fTA2 = 120.0f;
		m_fTA3 = 120.0f;
		m_fTAmax = 240.0f;

		//ͨ�ò���
		m_fPreFaultTime = 1.000;
		m_fFaultTime = 0.500;

		//�����
		m_fIdiff = 0.600f;
		m_fIr_Id = 0.600f;
		m_fIcdqd=0.5;

		m_nAutoSearch = 1;
		m_nULockType = BP2_DIFF_U_LOCK_TYPE_UA;
		m_fULockValue = 12.0f;


		m_nBinLogic = 0;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			m_binIn[i].init();
			m_binOut[i].init();
		}

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binInEx[i].init();
		}

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binOutEx[i].init();
		}

		//��λ������
		m_nKAType = 0;
		memset(m_pszId,0,PARAS_RSLT_EXPR_LEN);
		memset(m_pszIrId,0,PARAS_RSLT_EXPR_LEN);
	} 

}tmt_BP2DiffParas;

typedef struct tmt_bp2_diff_results
{
	float	m_fIdiffActValue;	//���������ֵ
	float	m_fIdiffSettingValue;	// ��ǰ�����Ĳ����ֵ
	float	m_fIbiasValue;	//�ƶ�����
	float	m_fIrCoef;		//�ƶ�ϵ��
	BOOL	m_bLastPoint;	//�Ƿ����һ��������
	int		m_nZDRatioIndex;	//�����ƶ����1 1-2 2 2-2 3 3-2 ֵ��1 2 3 4 5 6 7 8
	int		m_rltBin[MAX_BINARYIN_COUNT];	//����״̬

	float	m_fTripTime;		//����ʱ��: ��ֵ��Ч
	int		m_nActFlag;			//������־

	float	m_fI1;
	float	m_fI2;
	float	m_fIRbase[6];
	float	m_fIharm[6];

	//��λ����
	float   m_fRateKid; //�����ƶ�ϵ��

public:
	virtual void init()
	{
		m_fIdiffActValue = 0;	//�����
		m_fIdiffSettingValue = 0;
		m_fIbiasValue = 0;	//�ƶ�����
		m_fIrCoef = 0;		//�ƶ�ϵ��
		m_bLastPoint = 0;	//�Ƿ����һ��������
		m_nZDRatioIndex = 0;	//�����ƶ����1 1-2 2 2-2 3 3-2 ֵ��1 2 3 4 5 6 7 8
		memset(m_rltBin, 0, MAX_BINARYIN_COUNT*sizeof(int));
		m_fTripTime = 0;			//����ʱ��: ��ֵ��Ч
		m_nActFlag = 0;

		m_fI1 = 0;
		m_fI2 = 0;

		m_fRateKid = 0;

		for (int i=0;i<6;i++)
		{
			m_fIRbase[0] = m_fIharm[0] = 0;
		}
	} 

}tmt_BP2DiffResults;


typedef struct tmt_bp2_diff_thr_test : public TMT_PARAS_HEAD // �������������
{
public:
	tmt_BP2DiffParas      m_oDiffCurrParas ;
	tmt_BP2DiffResults   m_oDiffCurrResults;
	int m_nThrType;		//0-����������1-������������

	virtual void init()
	{
		init_head(); //20210918 zhouhj
		strcpy(m_pszMacroID, STT_MACRO_ID_BP2DiffTCurrTest);
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oDiffCurrParas.init();
		m_oDiffCurrResults.init();
		m_nThrType = 0;
	}

	tmt_bp2_diff_thr_test()	{init();}
	virtual void clear_result(){	m_oDiffCurrResults.init();	}
	virtual ~tmt_bp2_diff_thr_test(){}
}tmt_BP2DiffThrTest;

typedef struct tmt_bp2_diff_rate_test : public tmt_BP2DiffThrTest // ������ƶ�
{
public:
	int m_nRateType;		//0-������б�ʣ�1��2-�����ƶ�ϵ��һ��3��4-�����ƶ�ϵ������5��6-�����ƶ�ϵ������7��8-�����ƶ�ϵ���ģ�
	virtual void init()
	{
		tmt_BP2DiffThrTest::init();
		m_nRateType = 0;
		strcpy(m_pszMacroID, STT_MACRO_ID_BP2DiffRateTest);
	}

	tmt_bp2_diff_rate_test()	{init();}
	virtual ~tmt_bp2_diff_rate_test(){}
}tmt_BP2DiffRateTest;


typedef struct tmt_bp2_cboperate_test : public tmt_BP2DiffThrTest // ���������
{
public:
	virtual void init()
	{
		tmt_BP2DiffThrTest::init();
		strcpy(m_pszMacroID, STT_MACRO_ID_BP2CBOperateTest);
	}

	tmt_bp2_cboperate_test()	{init();}
	virtual ~tmt_bp2_cboperate_test(){}
}tmt_BP2CBOperateTest;


void stt_init_paras(tmt_BP2DiffParas *pParas);
void stt_init_results(tmt_BP2DiffResults *pResults);

void stt_xml_serialize_diff_search_results(tmt_BP2DiffParas *pParas, tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr_ex(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_thr(tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_rate(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_rate_ex(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_rate(tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

void stt_xml_serialize_cboperate(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_cboperate_ex(tmt_BP2DiffParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize_cboperate(tmt_BP2DiffResults *pResults, CSttXmlSerializeBase *pXmlSierialize);

CSttXmlSerializeBase* stt_xml_serialize(tmt_BP2DiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize(tmt_BP2DiffThrTest *pTests, CSttXmlSerializeBase *pXmlSerialize,BOOL bResultOnly);
