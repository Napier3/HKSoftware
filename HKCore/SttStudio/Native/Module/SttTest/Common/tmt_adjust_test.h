#ifndef TMT_ADJUST_TEST_H
#define TMT_ADJUST_TEST_H

#include "../../SttTestBase/SttXmlSerialize.h"
#include "tmt_adjust_sys_parameter.h"

//lijunqing 2020-10-20
#define STT_ADJUST_MACRO_ID_AdjustOne		   "AdjustOne"
#define STT_ADJUST_MACRO_ID_AdjustOneCopy      "AdjustOneCopy"
#define STT_ADJUST_MACRO_ID_AdjustThree		   "AdjustThree"
#define STT_ADJUST_MACRO_ID_AdjustSwitch	   "AdjustSwitch"
#define STT_ADJUST_MACRO_ID_ReadModuleFlash    "ReadModuleFlash"
#define STT_ADJUST_MACRO_ID_WriteModuleFlash   "WriteModuleFlash"
#define STT_ADJUST_MACRO_ID_AdjustReboot       "AdjustReboot"
#define STT_ADJUST_MACRO_ID_AdjustOne2Points   "AdjustOne2Points"

#define STT_ADJUST_MODULEFLASH_RESULT_SUCCESS             0
#define STT_ADJUST_MODULEFLASH_RESULT_ModuleNoResponse    1   //��ģ������Ӧ
#define STT_ADJUST_MODULEFLASH_RESULT_ModulePtrIsNull     2  //����ģ��ָ��Ϊ��
#define STT_ADJUST_MODULEFLASH_RESULT_ModuleResponseErr   3  //дģ�鷵�ش���
#define STT_ADJUST_MODULEFLASH_RESULT_DataHeadErr         4  //������������ͷ����
//////////////////////////////////////////////////////////////////////////
//У׼���Թ��ܽṹ��
//��ͨ��У׼�����ṹ��
typedef struct tmt_adjust_one_paras
{
    long m_nModuleType;  //ģ������
	long m_nModule;  //ģ��λ��
	long m_nChannel;  //ͨ����ţ�Ŀǰ���Ϊ6��ͨ��
	long m_nFreqSel; // 0=DC;1=������2=2��г����.......
	long m_nTempretureID;  //<=0��Ч   1=����1......
	long m_nGearID; //��λ <0��Ч  0=ȱʡ��λ������λ1 2=��λ2......
	float m_fMag;   //��Ʋ���ֵ����ֵ����λ��Ƶ��
	float m_fAng;
	float m_fFreq;
	float m_fDeviation;//������

    void init()
    {
		m_nModuleType = 0;
        m_nModule = 0;
        m_nChannel = 0;
		m_nFreqSel = 1;//��g_theModuleOutPut�����,���贮�л�
        m_nTempretureID = 0;
		m_nGearID = 0;//����g_theModuleOutPut��m_nChannel�����,������Ĭ�������λ
        m_fMag = 0;
        m_fAng = 0;
        m_fFreq = 0;
		m_fDeviation=0;
    }
}TMT_ADJUST_ONE_PARAS, *PTMT_ADJUST_ONE_PARAS;

typedef struct tmt_Adjust_One_Results
{
    STT_ADJUST_ITEM m_oResult;

    void init()
    {
        m_oResult.init();
    }
}TMT_ADJUST_ONE_RESULTS, *PTMT_ADJUST_ONE_RESULTS;

//���Թ��ܣ���ͨ��У׼�ṹ��
typedef struct tmt_adust_one
{
    TMT_ADJUST_ONE_PARAS m_oParas;  //����
    TMT_ADJUST_ONE_RESULTS m_oResult;  //У׼����

    void init()
    {
        m_oParas.init();
        m_oResult.init();
    }
}TMT_ADJUST_ONE, *PTMT_ADJUST_ONE;

typedef struct tmt_adjust_one2points_paras
{
	long m_nAdjustType;//0-����ֵ(Point1Mag) 1-��ֵ(Point1Mag,Point2Mag) 2-��λ(m_fAng) 3-Ƶ��
	long m_nModuleType;  //ģ������
	long m_nModule;  //ģ��λ��
	long m_nChannel;  //ͨ����ţ�Ŀǰ���Ϊ6��ͨ��
	long m_nFreqSel; // 0=DC;1=������2=2��г����.......
	long m_nTempretureID;  //<=0��Ч   1=����1......
	long m_nGearID; //��λ <0��Ч  0=ȱʡ��λ������λ1 2=��λ2......
	float m_fPoint1Mag;   //��Ʋ���ֵ����ֵ����λ��Ƶ��
	float m_fPoint2Mag;   //��Ʋ���ֵ����ֵ����λ��Ƶ��
	float m_fAng;
	float m_fFreq;
	float m_fDeviation;//������

	void init()
	{
		m_nAdjustType = 0;
		m_nModuleType = 0;
		m_nModule = 0;
		m_nChannel = 0;//��g_theModuleOutPut�����,���贮�л�
		m_nFreqSel = 1;//��g_theModuleOutPut�����,���贮�л�
		m_nTempretureID = 0;
		m_nGearID = 0;//��m_fPoint1Mag m_fPoint2Mag�����ֵ�������������
		m_fPoint1Mag = 0;
		m_fPoint2Mag = 0;
		m_fAng = 0;
		m_fFreq = 0;
		m_fDeviation=0;
	}
}TMT_ADJUST_ONE2POINTS_PARAS, *PTMT_ADJUST_ONE2POINTS_PARAS;

typedef struct tmt_Adjust_One2Points_Results
{
	STT_ADJUST_ITEM m_oResult;

	void init()
	{
		m_oResult.init();
	}
}TMT_ADJUST_ONE2POINTS_RESULTS, *PTMT_ADJUST_ONE2POINTS_RESULTS;

typedef struct tmt_adust_one2points
{
	TMT_ADJUST_ONE2POINTS_PARAS m_oParas;  //����
	TMT_ADJUST_ONE2POINTS_RESULTS m_oResult;  //У׼����

	void init()
	{
		m_oParas.init();
		m_oResult.init();
	}
}TMT_ADJUST_ONE2POINTS, *PTMT_ADJUST_ONE2POINTS;

//У׼����ͨ��У׼�����ṹ��
typedef struct tmt_adjust_three_paras : public TMT_ADJUST_ONE_PARAS
{
    //������㴦������������
    //ע�⣺���Թ��ܲ������õ�ʱ����Ҫ����������������Ĺ�������
    long m_nChannel2;
	long m_nGearID2;
    float m_fMag2;
    float m_fAng2;
    float m_fFreq2;
    long m_nChannel3;
	long m_nGearID3;
    float m_fMag3;
    float m_fAng3;
    float m_fFreq3;
	long m_nLargeCurrent;//1:�����ϵ��У׼ 0:��ͨϵ��У׼
    void init()
    {
        TMT_ADJUST_ONE_PARAS::init();

        m_nChannel2 = 0;
		m_nGearID2 = 0;
        m_fMag2 = 0;
        m_fAng2 = 0;
        m_fFreq2 = 0;
        m_nChannel3 = 0;
		m_nGearID3 = 0;
        m_fMag3 = 0;
        m_fAng3 = 0;
        m_fFreq3 = 0;
		m_nLargeCurrent=0;
    }
}TMT_ADJUST_THREE_PARAS, *PTMT_ADJUST_THREE_PARAS;

typedef struct tmt_Adjust_Three_Results
{
    STT_ADJUST_ITEM m_oResult[3];

    void init()
    {
        m_oResult[0].init();
        m_oResult[1].init();
        m_oResult[2].init();
    }
}TMT_ADJUST_THREE_RESULTS, *PTMT_ADJUST_THREE_RESULTS;

//���Թ��ܣ���ͨ��У׼�����ṹ��
typedef struct tmt_adjust_three
{
    TMT_ADJUST_THREE_PARAS m_oParas;   //У׼����������
     TMT_ADJUST_THREE_RESULTS m_oResults;  //У׼����

     void init()
     {
         m_oParas.init();
         m_oResults.init();
     }
}TMT_ADJUST_THREE, *PTMT_ADJUST_THREE;

//У׼����������У׼����
typedef struct tmt_adjust_onecopy_paras : public TMT_ADJUST_ONE_PARAS
{
	//������㴦������������
	//ע�⣺���Թ��ܲ������õ�ʱ����Ҫ����������������Ĺ�������
	long m_nModule2;  //ģ���ţ�ͬ���͵�ģ��˳����
	long m_nChannel2;  //ͨ����ţ�Ŀǰ���Ϊ6��ͨ��
	long m_nTempretureID2;  //<=0��Ч   1=����1......
	long m_nGearID2; //��λ <0��Ч  0=ȱʡ��λ������λ1 2=��λ2......

	void init()
	{
		TMT_ADJUST_ONE_PARAS::init();

		m_nChannel2 = 0;
		m_nModule2 = 0;
		m_nTempretureID2 = 0;
		m_nGearID2 = 0;
	}
}TMT_ADJUST_ONECOPY_PARAS, *PTMT_ADJUST_ONECOPY_PARAS;

typedef struct tmt_Adjust_OneCopy_Results
{
	STT_ADJUST_ITEM m_oResult;

	void init()
	{
		m_oResult.init();
	}
}TMT_ADJUST_ONECOPY_RESULTS, *PTMT_ADJUST_ONECOPY_RESULTS;

//���Թ��ܣ���ͨ��У׼�ṹ��
typedef struct tmt_adust_onecopy
{
	TMT_ADJUST_ONECOPY_PARAS m_oParas;  //����
	TMT_ADJUST_ONECOPY_RESULTS m_oResult;  //У׼����

	void init()
	{
		m_oParas.init();
		m_oResult.init();
	}
}TMT_ADJUST_ONECOPY, *PTMT_ADJUST_ONECOPY;

//ģ�������ͨ��ʸ���ṹ��
typedef struct tmt_adj_channel_vector
{
    float m_fMag;
    float m_fAngle;
}TMT_ADJ_CHANNEL_VECTOR, *PTMT_ADJ_CHANNEL_VECTOR;
typedef struct tmt_adj_channel_vector_ex : public TMT_ADJ_CHANNEL_VECTOR
{
    float m_fFreq;
}TMT_ADJ_CHANNEL_VECTOR_EX, *PTMT_ADJ_CHANNEL_VECTOR_EX;

//ģ�������ͨ�������ṹ��
typedef struct tmt_adj_channel
{
    //0=dc, 1=base wave. 2=second harm,......
	TMT_ADJ_CHANNEL_VECTOR m_oVector;
//    TMT_ADJ_CHANNEL_VECTOR m_harm[ADJUST_MAX_HARM_COUNT] ;
}TMT_ADJ_CHAANEL, *PTMT_ADJ_CHAANEL;

//ģ����������ṹ��
typedef struct tmt_adj_module_output
{	
    long m_nModuleType;
    long m_nModuleIndex;
	long m_nFreqIndex;
	TMT_ADJ_CHAANEL m_oChannels[ADJUST_MAX_CHANNEL_COUNT];

    void init()
    {
		m_nModuleType = 0;
        m_nModuleIndex = 0;
		m_nFreqIndex = 1;
        memset(m_oChannels, 0,  sizeof(TMT_ADJ_CHAANEL) * ADJUST_MAX_CHANNEL_COUNT);
    }
}TMT_ADJ_MODULE_OUTPUT, *PTMT_ADJ_MODULE_OUTPUT;

//ģ�鵥ͨ����������ṹ��
typedef struct tmt_adj_modulech_output
{
	long m_nChIndex;//ͨ��Index
	long m_nModuleType;
	long m_nModuleIndex;
	long m_nFreqIndex;
	TMT_ADJ_CHAANEL m_oChannel;

	void init()
	{
		m_nChIndex = 0;
		m_nModuleType = 0;
		m_nModuleIndex = 0;
		m_nFreqIndex = 1;
		m_oChannel.m_oVector.m_fMag=0;
		m_oChannel.m_oVector.m_fAngle=0;
	}
}TMT_ADJ_MODULECH_OUTPUT, *PTMT_ADJ_MODULECH_OUTPUT;

//�л�װ��
typedef struct tmt_adj_switch_output
{
	long m_nModuleType;
	long m_nModuleIndex;
	long m_nSwitchMode;
	void init()
	{
		m_nModuleType=0;
		m_nModuleIndex=0;
		m_nSwitchMode=0;
	}
}TMT_ADJ_SWITCH_OUTPUT, *PTMT_ADJ_SWITCH_OUTPUT;

//��������ͨ����
typedef struct tmt_adj_binary_output
{
	unsigned int m_nBoutTurnOnValue[8];
	void init()
	{
		for(int i=0;i<8;i++)
		{
			m_nBoutTurnOnValue[i]=1;
		}
	}
}TMT_ADJ_BINARY_OUTPUT, *PTMT_ADJ_BINARY_OUTPUT;

//��дģ��FLASH
typedef struct tmt_adj_moduleflash_paras
{
	long m_nModuleType;//ģ������
	long m_nModuleIndex;//ģ����
	void init()
	{
		m_nModuleType=0;
		m_nModuleIndex=0;
	}
}TMT_ADJ_MODULEFLASH_PARAS, *PTMT_ADJ_MODULEFLASH_PARAS;

typedef struct tmt_adj_moduleflash_results
{
	int m_nResult;
	void init()
	{
		m_nResult=0;
	}
}TMT_ADJ_MODULEFLASH_RESULTS, *PTMT_ADJ_MODULEFLASH_RESULTS;

typedef struct tmt_adj_moduleflash
{
	TMT_ADJ_MODULEFLASH_PARAS m_oParas;
	TMT_ADJ_MODULEFLASH_RESULTS m_oResult;

	void init()
	{
		m_oParas.init();
		m_oResult.init();
	}
}TMT_ADJ_MODULEFLASH, *PTMT_ADJ_MODULEFLASH;

//��ͨ��У׼����ṹ��
typedef struct tmt_adj_cal_vector
{
    TMT_ADJ_CHANNEL_VECTOR_EX m_oOutputVector;  //device output value
    TMT_ADJUST_ONE_PARAS m_oAdjParas;  //adjust paras;
    PSTT_ADJUST_ITEM m_pAdjResults; //adjust coef referance
}TMT_ADJ_CAL_VECTOR, *PTMT_ADJ_CAL_VECTOR;

//��ͨ��У׼����ṹ��
typedef struct tmt_adj_cal_vector_three
{
    TMT_ADJ_CHANNEL_VECTOR_EX m_oOutputVector[3];  //device output value
    TMT_ADJUST_THREE_PARAS m_oAdjParas;  //adjust paras;
    PSTT_ADJUST_ITEM m_pAdjResults[3]; //adjust coef referance
}TMT_ADJ_CAL_VECTOR_THREE, *PTMT_ADJ_CAL_VECTOR_THREE;


void stt_init_paras(TMT_ADJUST_ONE pParas);
void stt_xml_serialize(PTMT_ADJUST_ONE_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(PTMT_ADJUST_ONE_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(TMT_ADJUST_ONE2POINTS pParas);
void stt_xml_serialize(PTMT_ADJUST_ONE2POINTS_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(PTMT_ADJUST_ONE2POINTS_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(PTMT_ADJUST_THREE pParas);
void stt_xml_serialize(PTMT_ADJUST_THREE_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(PTMT_ADJUST_THREE_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(TMT_ADJUST_ONECOPY pParas);
void stt_xml_serialize(PTMT_ADJUST_ONECOPY_PARAS pPara, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(PTMT_ADJUST_ONECOPY_RESULTS pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(PTMT_ADJ_MODULE_OUTPUT pParas);
void stt_xml_serialize(PTMT_ADJ_MODULE_OUTPUT pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(PTMT_ADJ_MODULECH_OUTPUT pParas);
void stt_xml_serialize(PTMT_ADJ_MODULECH_OUTPUT pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(PTMT_ADJ_SWITCH_OUTPUT pParas);
void stt_xml_serialize(PTMT_ADJ_SWITCH_OUTPUT pPara, CSttXmlSerializeBase *pXmlSierialize);

void stt_init_paras(PTMT_ADJ_BINARY_OUTPUT pParas);
void stt_xml_serialize(PTMT_ADJ_BINARY_OUTPUT pPara, CSttXmlSerializeBase *pXmlSerialize);

void stt_init_paras(PTMT_ADJ_MODULEFLASH pParas);
void stt_xml_serialize(PTMT_ADJ_MODULEFLASH_PARAS pPara, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize(PTMT_ADJ_MODULEFLASH_RESULTS pPara, CSttXmlSerializeBase *pXmlSerialize);

void stt_xml_serialize_write_ModuleOutPut();
#endif // TMT_ADJUST_TEST_H

