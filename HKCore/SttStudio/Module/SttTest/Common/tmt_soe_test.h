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
 	unsigned int val;            //开出值             0：断开            1：闭合
 	 float time;            //持续时间毫秒值
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
 	unsigned int isValid;            //该通道是否有效            1；有效            0：无效
 	unsigned int cnt;                  //循环次数
 	tmt_SoeState otmt_SoeState[3];
 	char m_strTestObject[SOE_MAX_STATE_NAME];//测试对象
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
	unsigned int m_nMode;            //0:立即实验      1:GPS触发实验开始
	unsigned int m_nSelect;//0:主板开出端子  1:扩展开出端子  2:Goose
	unsigned int m_nBiAct;//0:无需开入结果 1:单个开入端子统计最多64次翻转结果
	tmt_time	 m_tGps;            //GPS time
	float m_fHoldTime;   //持续时间
	unsigned int m_nTestCount;//测试次数
	unsigned int m_nInterval; //间隔
	char m_strDataset_path[MAX_STATE_NAME];//间隔路径
	unsigned int m_nLoopTest;//闭环测试
	unsigned int m_nSoeResolution;//闭环测试
	char m_strSelTestObject[MAX_BINARYOUT_COUNT][MAX_STATE_NAME];//测试对象
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

	float	m_frTimeBinAct[MAX_BINARYIN_COUNT][BIBO_ACTCOUNT];		//每一个开入记录64次变位时间
	int		m_nrBinSwitchCount[MAX_BINARYIN_COUNT]; //变位次数
	float	m_frTimeBinExAct[MAX_ExBINARY_COUNT][BIBO_ACTCOUNT];		//每一个开入记录64次变位时间
	int		m_nrBinExSwitchCount[MAX_ExBINARY_COUNT]; //变位次数

	float m_frTimeBoutAct[MAX_BINARYIN_COUNT][BIBO_ACTCOUNT]; //每一个开出记录64次变位时间
	float m_frTimeBoutExAct[MAX_ExBINARY_COUNT][BIBO_ACTCOUNT]; //每一个扩展开出记录64次变位时间
	int	  m_nrBoutSwitchCount[MAX_BINARYIN_COUNT]; //变位次数
	int	  m_nrBoutExSwitchCount[MAX_ExBINARY_COUNT]; //变位次数
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


