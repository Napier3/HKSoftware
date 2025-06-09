#pragma once
 #include"../../SttTestBase/SttXmlSerialize.h"
 #include "../Common/tmt_common_def.h"
 #include "tmt_test_paras_head.h"

 #define SOETYPE_NULL 0
 #define SOETYPE_GPS  1
#define SOE_MAX_STATE_NAME                 64
 
 
 typedef struct tmt_soestate
 {
 public:
 	unsigned int val;            //����ֵ             0���Ͽ�            1���պ�
 	 float time;            //����ʱ�����ֵ
 public:
 	void init()
 	{
 		val=0;
 		time=1;
 	}
 
 	tmt_soestate()	{	init();	}
 }tmt_SoeState;
 
 typedef struct tmt_soebinary_out
 {
 public:
 	unsigned int isValid;            //��ͨ���Ƿ���Ч            1����Ч            0����Ч
 	unsigned int cnt;                  //ѭ������
 	tmt_SoeState otmt_SoeState[3];
 	char m_strTestObject[SOE_MAX_STATE_NAME];//���Զ���
 public:
 	void init()
 	{
 		isValid=0;
 		cnt=1;
 		memset(m_strTestObject, 0, SOE_MAX_STATE_NAME);
 
 		for(int i=0;i<3;i++)
 		{
 			otmt_SoeState[i].init();
 		}
 	}
 
 	tmt_soebinary_out()	{	init();	}
 }tmt_SoeBinaryOut;

typedef struct tmt_soe_paras
{
public:
	unsigned int m_nMode;            //0:����ʵ��      1:GPS����ʵ�鿪ʼ
	unsigned int m_nSelect;//0:���忪������  1:��չ��������  2:Goose
	unsigned int m_nBiAct;//0:���迪���� 1:�����������ͳ�����64�η�ת���
	tmt_time	 m_tGps;            //GPS time
	float m_fHoldTime;   //����ʱ��
	unsigned int m_nTestCount;//���Դ���
	unsigned int m_nInterval; //���
	char m_strDataset_path[MAX_STATE_NAME];//���·��
	unsigned int m_nLoopTest;//�ջ�����
	unsigned int m_nSoeResolution;//�ջ�����
	char m_strSelTestObject[MAX_BINARYOUT_COUNT][MAX_STATE_NAME];//���Զ���
	tmt_SoeBinaryOut m_binOut[MAX_BINARYOUT_COUNT];
	tmt_SoeBinaryOut m_binOutEx[MAX_ExBINARY_COUNT];
//	tmt_SoeBinaryOut m_binOutEx[MAX_ExBINARY_COUNT];
public:
    void init()
    {
		m_nMode=0;
		m_nBiAct=0;
		m_nSelect=1;
		m_fHoldTime=0;
		m_nTestCount = 5;
		m_nInterval = 0;
		m_nLoopTest = 0;
		m_nSoeResolution = 2;
		m_tGps.init();
		memset(m_strSelTestObject, 0, sizeof(m_strSelTestObject));
		memset(m_strDataset_path, 0, MAX_STATE_NAME);

		
 		for(int i=0;i<MAX_BINARYOUT_COUNT;i++)
 		{
 			m_binOut[i].init();
 		}
 
        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_binOutEx[i].init();
		}
    }

	tmt_soe_paras()	{}
}tmt_SoeParas;


typedef struct tmt_soe_result
{
public:
    int		m_nTripFlag;
    float	m_fTripTime;
    float	m_fActValue;

	float	m_frTimeBinAct[MAX_BINARYIN_COUNT][BIBO_ACTCOUNT];		//ÿһ�������¼64�α�λʱ��
	int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT]; //��λ����
	float	m_frTimeBinExAct[MAX_ExBINARY_COUNT][BIBO_ACTCOUNT];		//ÿһ�������¼64�α�λʱ��
	int		m_nrBinExSwitchCount[MAX_ExBINARY_COUNT]; //��λ����

	float m_frTimeBoutAct[MAX_BINARYIN_COUNT][BIBO_ACTCOUNT]; //ÿһ��������¼64�α�λʱ��
	float m_frTimeBoutExAct[MAX_ExBINARY_COUNT][BIBO_ACTCOUNT]; //ÿһ����չ������¼64�α�λʱ��
	int	  m_nrBoutSwitchCount[MAX_BINARYIN_COUNT]; //��λ����
	int	  m_nrBoutExSwitchCount[MAX_ExBINARY_COUNT]; //��λ����
public:
    void init()
    {
        m_nTripFlag = 0;
        m_fTripTime = 0;
        m_fActValue = 0;

		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			for (int j=0;j<BIBO_ACTCOUNT;j++)
			{
				m_frTimeBinAct[i][j] = 0;
				m_frTimeBoutAct[i][j] = 0;
			}
			m_nrBinSwitchCount[i] = 0;
			m_nrBoutSwitchCount[i] = 0;
		}

        for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			for (int j=0;j<BIBO_ACTCOUNT;j++)
			{
				m_frTimeBinExAct[i][j] = 0;
			}
			m_nrBinExSwitchCount[i] = 0;
		}

        for(int i = 0; i < g_nBoutExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			for (int j=0;j<BIBO_ACTCOUNT;j++)
			{
				m_frTimeBoutExAct[i][j] = 0;
			}
			m_nrBoutExSwitchCount[i] = 0;
		}
    }

	tmt_soe_result()	{}
}tmt_SoeResult;

typedef struct tmt_soe_test: public TMT_PARAS_HEAD
{
public:
	tmt_SoeResult   m_oSoeResult;
	tmt_SoeParas    m_oSoeParas;

    void init()
    {
		strcpy(m_pszMacroID, STT_MACRO_ID_SoeTest);
#ifndef NOT_USE_TMT_TEST_PARAS_HEAD
		m_nVersion = 0x00010001;
		m_nTestState = 0;
#endif
		m_oSoeResult.init();
		m_oSoeParas.init();
    }
	tmt_soe_test() {}
}tmt_SoeTest;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas

void stt_xml_serialize_write_SoeTest();
void stt_init_paras(tmt_SoeParas *pParas);
void stt_init_results(tmt_SoeResult *pResults);
void stt_xml_serialize(tmt_SoeParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_SoeResult *pResults, CSttXmlSerializeBase *pXmlSierialize);


