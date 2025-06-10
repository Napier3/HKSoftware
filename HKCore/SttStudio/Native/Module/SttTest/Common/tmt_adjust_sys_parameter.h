#ifndef TMT_ADJUST_SYS_PARAMETER_H
#define TMT_ADJUST_SYS_PARAMETER_H

//ϵͳӲ������ʱ����û��У׼ϵ���ļ�����ʱϵͳ����ȱʡ��û��У׼ϵ�����ļ�
//ȱʡ��У׼ϵ���ļ���ֻ��ģ���һЩ�ӻ������ԣ�����ģ��Ķ�Ӧ��FPGA�汾��
//У׼���߳������Ӳ����ǣ���ȡУ׼��ϵ���ļ�������ģ������ԣ��ӱ��ؿ��л�ȡ��׼��
//        ģ��У׼ϵ��ģ���ļ���ʼ����ģ��

#define STT_ADJUST_SYS_PARA_VERSION_1_0     0X00010000

//2020-12-27  LIJUNQING  ��������ṹ���������ݣ�������汾��
//g_dwSttAdjSysParaCurrVersion��ʾ��ǰ���µİ汾��
//�������ļ����ϰ汾���ݣ����Ա�������Ӱ汾����
//�ϰ汾��������°汾�ļ��ķ�����
//    �����ӵ����ݣ���Զ����֮ǰ�汾�ĺ���д�룬�������ܹ���֤�ϰ汾�����ȡ�°汾���ļ�������
extern long g_dwSttAdjSysParaCurrVersion;// = STT_ADJUST_SYS_PARA_VERSION_1_0;

//20231030 zhoulei ��дģ��ϵ��ʱ�����ṹ��
#define STT_ADJUST_MODULE_PARA_VERSION_1    1
#define STT_ADJUST_MODULE_PARA_VERSION_2    2//��չ��������4���ֳ�8�飬���Ӳ���Ķ�
#define STT_ADJUST_MODULE_PARA_VERSION_3    3//���ӽ�����ѹ����ģ���������������ֵ
#define STT_ADJUST_MODULE_PARA_VERSION		STT_ADJUST_MODULE_PARA_VERSION_3
#ifdef _PSX_IDE_QT_
extern bool g_bWriteHdInfor;
#else
extern BOOL g_bWriteHdInfor;
#endif

//2020-10-21  lijunqing 
#include "../SttTestGlobaoConfig.h"
//#include "../../SttDevice/Module/PowerCtrl/SttPowerCtrlBase.h"//zhouhj 20210511 ���ļ����а�����ϵͳ������,ϵͳ��������Ҫ�õ����ģ�����궨��,��������ظ�����,�˴�ֻ������
class CSttPowerCtrlBase;

//////////////////////////////////////////////////////////////////////////
//У׼ϵ���ṹ��
#define ADJUST_MAX_MODULE_COUNT      12//Ӳ����֧�����ģ����
#define ADJUST_MAX_CHANNEL_COUNT     12//12·С�ź�
#define ADJUST_MAX_HARM_COUNT        31
#define ADJUST_CHANNEL_INDEX_IDC     65
#define ADJUST_CHANNEL_INDEX_UDC     64

//0=DC 1=BASE 2=HARM 2
#define ADJUST_MAX_CH_WAVE_COUNT            (ADJUST_MAX_HARM_COUNT+1)

#define ADJUST_MAX_TEMPRERATURE_COUNT   3
#define ADJUST_MAX_GEAR_COUNT           10

#define ADJUST_MAX_CH_MAPS_COUNT        12

//2021-5-2  lijunqing  ��Ϊ�ⲿ��Ҫ���ʣ����Խ�ģ�����Զ��岿�ַŵ�  tmt_adjust_sys_para_module_def.h
#include "tmt_adjust_sys_para_module_def.h"

//Ӳ��ͨ��ID�������ĳ���
#define STT_HD_CH_ID_BUF_LEN   8

#define DIGITAL_CHANNEL_MAX      37 //18U+18I+Uz
#define WEEK_MAIN_MODULEPOS    16//����С�źŹ̶�λ��16
#define BINARY_CHANNEL_MAX  64  //

#define STT_MODULE_CHANNEL_MAX  BINARY_CHANNEL_MAX

typedef struct stt_Module_Ch_Def
{//��short �� char����ʡ�ռ�
	char m_pszChId[STT_HD_CH_ID_BUF_LEN];   //Ua~Uc,Ia~Ic,......
	long m_nChIndex;  //ͨ�����(��������ı�ţ���0~5��ʾģ���ͨ����64��ʾ������ֱ��ͨ����6~63�����ֱ���
	long m_nWorkMode;  //// �ɼ��������WorkMode��
	long m_nEeType;  //��ѹ����������EeType
	long m_nChEeIndex;//
	long m_nChRsIndex;  // ��Ӧ�������Դ���
	float m_fChACMaxValue;      //     ���ֵ��ChACMaxValue
	float m_fChDCMaxValue;      //    ���ֵ��ChDCMaxValue
	long m_nChMeasPos;//20220211zhoulei ͨ���ɼ���ӳ��λ��

	//����ADMU��FT3
	char m_pszChIdEx[STT_HD_CH_ID_BUF_LEN];
	long m_nEeTypeEx;
	long m_nChEeIndexEx;
	long m_nChRsIndexEx;

	void init(long nModuleIndex, long nChIndex, char chSubType)
	{//m_nEeType���ȱ���ʼ���ģ����������ļ���ʱ������Ǵ���ģ���ʱ��
		//�μ��ļ���ͷע��
		//chSubType��ģ�������=0   ���������'d'   С�ź�'w'   ����Ϊ'i'   ����Ϊ'o'
		m_nChIndex = nChIndex;

		if (chSubType <= 0)
		{
            sprintf(m_pszChId, "%c%d_%d",m_nEeType , nModuleIndex+1, m_nChEeIndex+1);
		}
		else
		{
            sprintf(m_pszChId, "%c%c%d_%d",m_nEeType , chSubType,  nModuleIndex+1, m_nChEeIndex+1);
		}
	}
}STT_MODULE_CH_DEF, *PSTT_MODULE_CH_DEF;

typedef struct stt_Module_Ch_Defs
{
	STT_MODULE_CH_DEF m_oChDef[STT_MODULE_CHANNEL_MAX];  //Ӳ����Դ�����ͨ����

	void init(long nModuleIndex, long nChCount)
	{//pszChType:U1��I1��Uw1��
		long nIndex=0;
		for (nIndex=0; nIndex< nChCount; nIndex++)
	{
			if (nIndex >=STT_MODULE_CHANNEL_MAX)
			{
				break;
			}

			m_oChDef[nIndex].init(nModuleIndex, nIndex, 0); //chSubType = 0,  ��ʾ��ѹ���ߵ���
		}
	}

	void init_weak(long nModuleIndex, long nChCount)
	{
		long nIndex=0;
		for (nIndex=0; nIndex< nChCount; nIndex++)
		{
			if (nIndex >=STT_MODULE_CHANNEL_MAX)
			{
				break;
			}

			//20220209 zhoulei ϵ���ļ�δ�����С�źŹ��������ԴĬ��Ϊ��ѹ����
			long nEeType;
			nEeType = m_oChDef[nIndex].m_nEeType;
			m_oChDef[nIndex].m_nEeType = STT_CH_EETYPE_VOLTAGE;//����'Uw'
			m_oChDef[nIndex].m_nChEeIndex = nIndex;
			m_oChDef[nIndex].init(nModuleIndex, nIndex, 'w');//chSubType = 'w',  ��ʾС�ź�
			m_oChDef[nIndex].m_nEeType = nEeType;
		}
	}

	void init_digital(long nModuleIndex)
	{
// 20220309 zhoulei
//		int nCnt=DIGITAL_CHANNEL_MAX/2;
//		for (long nIndex=0; nIndex< nCnt; nIndex++)
//		{
//			sprintf(m_oChDef[nIndex].m_pszChId, "%c%c%d_%d",STT_CH_EETYPE_VOLTAGE , 'd',  nModuleIndex+1, nIndex+1);
//		}
//		//Uz-Ud1_19
//		sprintf(m_oChDef[nCnt].m_pszChId, "%c%c%d_%d",STT_CH_EETYPE_VOLTAGE , 'd',  nModuleIndex+1, nCnt+1);

//		for (long nIndex=0; nIndex< nCnt; nIndex++)
//		{
//			sprintf(m_oChDef[nIndex+nCnt+1].m_pszChId, "%c%c%d_%d",STT_CH_EETYPE_CURRENT , 'd',  nModuleIndex+1, nIndex+1);
//		}

        for (long nIndex=0; nIndex< DIGITAL_CHANNEL_MAX; nIndex++)
		{
            sprintf(m_oChDef[nIndex].m_pszChId, "%c%c%d_%d",m_oChDef[nIndex].m_nEeType ,
                    'd',  nModuleIndex+1, m_oChDef[nIndex].m_nChEeIndex+1);
		}
	}

	void init_binary_sub(long nModuleIndex, long nOffset, long &nBinnaryIndex, char chSubType)
	{
		long nIndex = 0;
		for (nIndex=0; nIndex<16; nIndex++)
		{
			m_oChDef[nIndex+nOffset].init(nModuleIndex, nBinnaryIndex, chSubType);
			nBinnaryIndex++;
		}
	}

	void init_binary(long nModuleIndex, long nCount, long *pSwitchIn)
	{
		long nGrouCount = nCount / 16;
		long nGroupIndex = 0;
		long nBinnaryIndex = 0;

		//������  1 ��ʾ ����
		for (nGroupIndex=0; nGroupIndex<nGrouCount; nGroupIndex++)
		{
			if (pSwitchIn[nGroupIndex] == 1)
			{
				init_binary_sub(nModuleIndex, nGroupIndex * 16, nBinnaryIndex, 'i');
			}
		}

		//������  1 ��ʾ ����
		for (nGroupIndex=0; nGroupIndex<nGrouCount; nGroupIndex++)
		{
			if (pSwitchIn[nGroupIndex] == 0)
			{
				init_binary_sub(nModuleIndex, nGroupIndex * 16, nBinnaryIndex, 'o');
			}
		}

	}
}STT_MODULE_CH_DEFS, *PSTT_MODULE_CH_DEFS;

typedef struct stt_Adjust_Item
{
public:
	float m_fCoef;//��ֵϵ��
	float m_fZero;//��Ư
	float m_fAngle;//��λ����

	void init()
	{
		m_fCoef = 1;
		m_fZero = 0;
		m_fAngle = 0;
	}

	stt_Adjust_Item(){}
	virtual ~stt_Adjust_Item(){}
}STT_ADJUST_ITEM, *PSTT_ADJUST_ITEM;

typedef struct stt_Channel_Gear_Adjust
{
public:
	float m_fGearValue;  //��λֵ
	STT_ADJUST_ITEM m_oAdjItem;

	void init()
	{
		m_fGearValue = 0;
		m_oAdjItem.init();
	}

	stt_Channel_Gear_Adjust(){}
	virtual ~stt_Channel_Gear_Adjust(){}
}STT_CHANNEL_GEAR_ADJUST, *PSTT_CHANNEL_GEAR_ADJUST;

typedef struct stt_Channel_Wave_Adjust
{
public:
	long m_nGearCount;  //��λ��
	STT_CHANNEL_GEAR_ADJUST m_oChGearAdj[ADJUST_MAX_GEAR_COUNT];

	void init()
	{
		m_nGearCount = 1;

		long nIndex = 0;

		for (nIndex=0; nIndex<ADJUST_MAX_GEAR_COUNT; nIndex++)
		{
			m_oChGearAdj[nIndex].init();
		}
	}

	stt_Channel_Wave_Adjust(){}
	virtual ~stt_Channel_Wave_Adjust(){}
}STT_CHANNEL_WAVE_ADJUST, *PSTT_CHANNEL_WAVE_ADJUST;

typedef struct stt_Channel_Adjusts
{
public:
	//2021-5-2  ��������У׼ϵ�����Ƿ�ŵ�  STT_TRANGE_ADJUST��
	//????????????????????????????????????????????????
	float m_fDcZero[3];  //�������ӵ�ֱ��������0V��0Hzʱ����
	float m_fLargeCurrentRatio; //�����������ϵ��


	long nHarmCount;//��ģ������m_nHarmCount����
	//ʵ�ʵ�г��������ģ�������ж���
	PSTT_CHANNEL_WAVE_ADJUST m_pChWaveAdj;

	//2021-4-30  lijunqing
	//���۽����Ϊ���㽫���İ汾���䣬Ϊÿ��ͨ�������Ӷ�������������
	//           �ɼ��������WorkMode��
	//           ��ѹ����������EeType
	//           ���ֵ��ChACMaxValue
	//           ���ֵ��ChDCMaxValue
	//long m_nWorkMode;  //
	//long m_nEeType;
	//float m_fChACMaxValue;
	//float m_fChDCMaxValue;
	PSTT_MODULE_CH_DEF m_pHdChDef; //������Ӳ��ͨ���������

	void init()
	{
        m_fDcZero[0]=m_fDcZero[1]=m_fDcZero[2]=0;
		m_fLargeCurrentRatio=1;//����1ʱ��������
		m_pHdChDef = NULL;
		m_pChWaveAdj = NULL;
		nHarmCount = 0;
	}

	stt_Channel_Adjusts(){}
	virtual ~stt_Channel_Adjusts(){}
}STT_CHANNEL_ADJUSTS, *PSTT_CHANNEL_ADJUSTS;

typedef struct stt_TRange_Adjust
{
public:
	float m_fTemperature;  //�¶�
	long  nChannelNum;//��ģ����Ϥm_nChannelNum����;
	STT_CHANNEL_WAVE_ADJUST m_oChIdcAdj;  //����IdcУ׼ϵ��
	STT_CHANNEL_WAVE_ADJUST m_oChUdcAdj;  //����UdcУ׼ϵ��

	PSTT_CHANNEL_ADJUSTS m_pChsAdjust;
	//	STT_CHANNEL_ADJUSTS m_oChsAdjust[ADJUST_MAX_CHANNEL_COUNT];

	//2021-5-2  lijunqing  ���µĲ��֣��Ƿ��б�Ҫ������Ϊһ������
	//????????????????????????????????????????????????
	STT_CHANNEL_ADJUSTS m_oChsAdjust_PTU_Is;//6��1,���������Isͨ��У׼

	void init()
	{
		m_fTemperature = 0;
		nChannelNum = 0;
		m_oChIdcAdj.init();
		m_oChUdcAdj.init();

		long nIndex=0;
		m_pChsAdjust=NULL;
		//		for (nIndex=0; nIndex<ADJUST_MAX_CHANNEL_COUNT; nIndex++)
		//		{
		//			m_oChsAdjust[nIndex].init();
		//		}
	}

	stt_TRange_Adjust(){}
	virtual ~stt_TRange_Adjust(){}
}STT_TRANGE_ADJUST, *PSTT_TRANGE_ADJUST;

//Ӳ����λ����
typedef struct stt_Hd_Gear
{
public:
	long m_nGearID;  //��λID����������ͨ�û������е�λʱ�Ĳ���
	float m_fGearValue;   //��λ��ֵ

	void init()
	{
		m_nGearID = 0;
		m_fGearValue = 0;
	}

	stt_Hd_Gear(){}
	virtual ~stt_Hd_Gear(){}
}STT_HD_GEAR, *PSTT_HD_GEAR;

typedef struct stt_Hd_Gears
{
public:
	long m_nHdGearCount;
	STT_HD_GEAR m_oHdGear[ADJUST_MAX_GEAR_COUNT];

	void init()
	{
		m_nHdGearCount = 0;
		memset(m_oHdGear, 0, sizeof(STT_HD_GEAR) * ADJUST_MAX_GEAR_COUNT);
	}

	stt_Hd_Gears(){}
	virtual ~stt_Hd_Gears(){}
}STT_HD_GEARS, *PSTT_HD_GEARS;

typedef struct stt_Hd_Gears_Ex
{
public:
	STT_HD_GEARS m_oChanHdGears[12];//С�ź����12·

	void init()
	{
		for(int i=0;i<12;i++)
		{
			m_oChanHdGears[i].init();
		}
	}

	stt_Hd_Gears_Ex(){}
	virtual ~stt_Hd_Gears_Ex(){}
}STT_HD_GEARS_EX, *PSTT_HD_GEARS_EX;

typedef struct stt_Module_Adjust
{
public:
	long m_nTemperatureCount;    //������

	//����У׼ϵ��
	STT_TRANGE_ADJUST m_oTempAdjust[ADJUST_MAX_TEMPRERATURE_COUNT];

	void init()
	{
		m_nTemperatureCount = 0;
		long nIndex = 0;

		for (nIndex=0; nIndex<ADJUST_MAX_TEMPRERATURE_COUNT; nIndex++)
		{
			m_oTempAdjust[nIndex].init();
		}
	}

	stt_Module_Adjust(){}
	virtual ~stt_Module_Adjust(){}
}STT_MODULE_ADJUST, *PSTT_MODULE_ADJUST;

//typedef struct stt_Module_Ch_Group
//{
//	//������Ϊ char m_pszCh1ID[3][8]�ķ�ʽ������Ϊ�˲鿴����
//	char m_pszCh1ID[8];
//	char m_pszCh2ID[8];
//	char m_pszCh3ID[8];
//}STT_MODULE_CH_GROUP, *PSTT_MODULE_CH_GROUP;

//typedef struct stt_Module_Ch_Groups
//{
//	long m_nChGroupCount;
//	STT_MODULE_CH_GROUP m_oChGroups[2];//�ݶ�Ϊ���2�����飬����ͨ��
//}STT_MODULE_CH_GROUPS, *PSTT_MODULE_CH_GROUPS;

typedef struct stt_Ch_Drv_Pos
{
	long m_nChDrvPos[STT_MODULE_CHANNEL_MAX];

	void init()
	{
        for (long k=0; k<STT_MODULE_CHANNEL_MAX; k++)
		{
			m_nChDrvPos[k] = k;
		}
	}
}STT_CH_DRV_POS, *PSTT_CH_DRV_POS;

typedef struct stt_Module_Ch_Map_Def
{
public:
	//ͨ��������ģ�鶨�壬�˴����ظ�����
	//long m_nChannelCount��
	//	STT_MODULE_CH_MAPS m_oChMaps;
	//	STT_MODULE_CH_GROUPS m_oChGroups;

	//2021-4-29  lijunqing
	//Ӳ��ͨ�����壺��Ӳ��ͨ����ID������ͨ��ӳ��
	//ϵͳ��ʼ����ʱ���ʼ�������ı�
	STT_MODULE_CH_DEFS m_oChDefs;
	STT_CH_DRV_POS m_oChDrvPos;

	void init()
	{
		memset(&m_oChDefs, 0, sizeof(STT_MODULE_CH_DEFS));
		//		memset(&m_oChGroups, 0, sizeof(STT_MODULE_CH_GROUPS));
		m_oChDrvPos.init();
	}
}STT_MODULE_CH_MAP_DEF, *PSTT_MODULE_CH_MAP_DEF;

//��������һ���ṹ�壬�Ӵ����Ķ������Լ�xml���л��Ϸ���Щ
typedef struct stt_Module_Attr
{
	//////////////////////////////////////////////////////////////////////////
	//�Ѿ�ȷ��������  lijunqing
	char m_strModelName[32];//ģ���ͺ�
	char m_strModuleSN[32];//ģ�����к�
	long m_nChannelNum;//ͨ����
	long m_nHarmCount;     //г����
	float m_fUdcMax;  //����ֱ����ѹͨ�����ֵ
	float m_fUdcMin;  //����ֱ����ѹͨ����Сֵ
//    float m_fDCCurrMax;  //ֱ������ͨ�����ֵ
	float m_fChMax;  //ģ��ͨ�����������ֵ
	float m_fChDcMax;  //ģ��ͨ����ֱ�����ֵ
	float m_fDefChMax;  //�����ƽ������ֵ��ֻ�н�����ѹ����ģ������
	float m_fDefChDcMax;  //������ֱ�����ֵ��ֻ�н�����ѹ����ģ������

	//ģ������ ���궨��
	long m_nModuleType;     //m_nvoltorcur;
	long m_nModuleIndex; //ģ��λ�� 1~11
	long m_nModuleAddr;//RTDSʹ��ʱPI��ģ�����ڱ��

	//ģ��Ӳ������ ���ʿ���ģʽ
	long m_nModulePower; //�� SttPowerCtrlCom.h �궨��
	CSttPowerCtrlBase *m_pPowerCtrlBase;
	//ģ��ͨ��ӳ�䶨��
	STT_MODULE_CH_MAP_DEF m_oChDefMap;
	long m_nErr;//�������ϵ���ļ��ڵ��쳣ģ�飬��ֹ�˿����
	long m_nUsed;//�������ϵ���ļ��ڵĿ���ģ��

	//Ӳ����λ
//    STT_HD_GEARS m_oHdGears;
//    STT_HD_GEARS_EX m_oHdGearsEx;//С�źŲ��
//    STT_HD_GEARS m_oHdGears_Idc; //����ֱ������ͨ��Ӳ����λ
//    STT_HD_GEARS m_oHdGears_Udc; //����ֱ����ѹͨ��Ӳ����λ

	//////////////////////////////////////////////////////////////////////////
	//��������Բ�ȷ����������ȷ��**********************
	float m_fFreCoef;//Ƶ�ʲ���ϵ��,��ѹʱ��Ч
	float m_fgain; //����
	char m_strFPGAVer[32]; //FPGA�汾��
//	UINT  m_nFiberPortNum;//����ģ������ ������ģ��Ŀǰ�̶�Ϊÿ��ģ��8��ڡ��������ɲο���ѹ����������ÿ��ģ��Ĺ������
	long m_nFiberPortNum_LC;//LC�����
	long m_nFiberPortNum_STSend;//STSend�����
	long m_nFiberPortNum_STRecv;//STRecv�����

	float m_fDigitalDelay;//����ģ����λ��ʱ

	long  m_nSwitchIn[8];//���4��16IOԪ������64IO
	//2021-6-2  lijunqing �����ֺϲ�ģʽͳһ����
	long  m_nChMergeMode;//ͨ���ϲ�ģʽ��0=��֧�֣�1=6��1�� 2=6��3��
	//2023-10-30 zhoulei ����С�źŲ��
	long  m_nChTypeChg;//ͨ���������Ϳɱ䣻1:�ɱ�,0:���ɱ�
	//��������
	char m_strDateProduce[24]; //2020-10-10��������λ�������ַ�������
	char m_strFactory[64]; //2020-10-10��������λ�������ַ�������

	//2021-4-30  lijunqing
	//���۽����Ϊ���㽫���İ汾���䣬Ϊÿ��ͨ�������Ӷ�������������
	//           �ɼ��������WorkMode��
	//           ��ѹ����������EeType
	//           ���ֵ��ChACMaxValue
	//           ���ֵ��ChDCMaxValue
	//Ϊ�˼������ϰ汾��Ϊģ�����Ӱ汾�ţ���ʾУ׼ϵ��ģʽ�İ汾
	long m_dwVersion;

//    bool has_idc()
//    {
//        return (m_fDCCurrMax > 0);
//    }
//    bool has_udc()
//    {
//        return (m_fDCVoltMax > 0);
//    }

	void init()
	{
		m_dwVersion = -1;  //-1����ʼ������ʾû�ж���У׼ϵ���ļ�
		strcpy(m_strModelName, "Stt2020");
		strcpy(m_strModuleSN, "PONV-2020-1001-000");
		strcpy(m_strFactory, "�����������������ɷ����޹�˾");
		strcpy(m_strDateProduce, "2020-01-01");
		strcpy(m_strFPGAVer, "-");
		m_nModuleAddr = 0;
		m_fUdcMax = -1.0f;
		m_fUdcMin = -1.0f;
//        m_fDCCurrMax = 0;
		m_fChMax = 0;
		m_fChDcMax=0;
		m_fDefChMax = 0;
		m_fDefChDcMax = 0;
		m_fFreCoef=1.0;
		m_pPowerCtrlBase=NULL;
		m_nModulePower=0;
		m_nChMergeMode=STT_CURRENT_ChMergeMode_No;
		m_nChannelNum=ADJUST_MAX_CHANNEL_COUNT;
		m_nHarmCount=ADJUST_MAX_CH_WAVE_COUNT;
		m_nFiberPortNum_LC = 0;//LC�����
		m_nFiberPortNum_STSend = 0;//STSend�����
		m_nFiberPortNum_STRecv = 0;//STRecv�����
		m_nSwitchIn[0] = -1; //Ĭ������Ч,0-����,1-����
		m_nSwitchIn[1] = -1; //Ĭ������Ч,0-����,1-����
		m_nSwitchIn[2] = -1; //Ĭ������Ч,0-����,1-����
		m_nSwitchIn[3] = -1; //Ĭ������Ч,0-����,1-����
		m_nSwitchIn[4] = -1; //Ĭ������Ч,0-����,1-����
		m_nSwitchIn[5] = -1; //Ĭ������Ч,0-����,1-����
		m_nSwitchIn[6] = -1; //Ĭ������Ч,0-����,1-����
		m_nSwitchIn[7] = -1; //Ĭ������Ч,0-����,1-����
		m_fDigitalDelay = 0;
		m_nChTypeChg = 1;//Ĭ��С�źŲ��ͨ��������ѡ��ѹ�����
		m_oChDefMap.init();
	}

	void init_hd_ch_def(long nModuleIndex, char chType)
	{
		if (chType == STT_MODULETYPE_ID_ANALOG_CHAR) //ģ�������
		{
			m_oChDefMap.m_oChDefs.init(nModuleIndex, m_nChannelNum);
			return;
		}

		if (chType == STT_MODULETYPE_ID_DIGITAL_CHAR) //���������
		{
			m_oChDefMap.m_oChDefs.init_digital(nModuleIndex);
			return;
		}

		if (chType == STT_MODULETYPE_ID_WEEK_CHAR) //С�źŲ��
		{
			m_oChDefMap.m_oChDefs.init_weak(nModuleIndex, m_nChannelNum);
			return;
		}

		if (chType == STT_MODULETYPE_ID_BINARY_CHAR) //���������
		{
			m_oChDefMap.m_oChDefs.init_binary(nModuleIndex, m_nChannelNum, m_nSwitchIn);
			return;
		}
	}
}ST_MODULE_ATTR, *PST_MODULE_ATTR;

typedef struct stt_Module
{
	ST_MODULE_ATTR m_oModuleAttr;  //ģ������
	STT_MODULE_ADJUST m_oModuleAdjust;  //ģ��У׼ϵ��

	void init()
	{
		memset(&m_oModuleAttr, 0, sizeof(ST_MODULE_ATTR));
		m_oModuleAttr.init();
		m_oModuleAdjust.init();
	}

	//2020-10-05 zhoulei
	long m_nChMeasPos[STT_MODULE_CHANNEL_MAX];
	long m_nChDrvPos[STT_MODULE_CHANNEL_MAX];//����ʹ�ã���ʼ����ȡ��m_oModuleAttr.m_oChDefMap
	long m_nChTmtPos[STT_MODULE_CHANNEL_MAX];//ӳ�䵽�����Դ
	long m_nChTmtPosEx[STT_MODULE_CHANNEL_MAX];//ӳ�䵽�����ԴADMU

	//2021-6-2  lijunqing
	float m_fChTmtCoef[STT_MODULE_CHANNEL_MAX];   //ӳ��ͨ����ϵ�������������ͨ���ϲ������ÿ��ͨ����ϵ������
	//	long m_nArrayBeginIndex;

	void init_ch_drv_pos()
	{
		memcpy(m_nChDrvPos, m_oModuleAttr.m_oChDefMap.m_oChDrvPos.m_nChDrvPos, sizeof(long)*STT_MODULE_CHANNEL_MAX);
        for(int i=0;i<STT_MODULE_CHANNEL_MAX;i++)
		{
			m_nChMeasPos[i] = m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[i].m_nChMeasPos;
		}
	}

	void InitChTmtPos()
	{//����ͨ����ӳ����Դ����Index����ʼ��ChTmtPos
		//
		long nChannelNum = m_oModuleAttr.m_nChannelNum;
		if(m_oModuleAttr.m_nModuleType==STT_MODULE_TYPE_DIGITAL_0G8M
				||m_oModuleAttr.m_nModuleType==STT_MODULE_TYPE_DIGITAL_2G6M
				||m_oModuleAttr.m_nModuleType==STT_MODULE_TYPE_DIGITAL_4G4M
				||m_oModuleAttr.m_nModuleType==STT_MODULE_TYPE_FT3)
		{
			nChannelNum = DIGITAL_CHANNEL_MAX;//���ְ���ϵ���ļ���ͨ��ֵ��0
		}

		PSTT_MODULE_CH_DEFS pChDefs = &m_oModuleAttr.m_oChDefMap.m_oChDefs;
		long nIndex = 0;

		for (nIndex=0; nIndex<nChannelNum;nIndex++)
		{
			m_nChTmtPos[nIndex] = pChDefs->m_oChDef[nIndex].m_nChRsIndex;
		}

		if(m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_ADMU)
		{
			for (nIndex=0; nIndex<DIGITAL_CHANNEL_MAX;nIndex++)
			{
				m_nChTmtPosEx[nIndex] = pChDefs->m_oChDef[nIndex].m_nChRsIndexEx;
			}
		}
	}

	void InitChTmtCoef()
	{//����ͨ����ӳ����Դ����Index����ʼ��ChTmtPos
		//
		long nChannelNum = m_oModuleAttr.m_nChannelNum;
		long nIndex = 0;

		for (nIndex=0; nIndex<nChannelNum;nIndex++)
		{
			m_fChTmtCoef[nIndex] = 1.0f;
		}

	}

	//2021-5-2  lijunqing  ����m_dwVersion����ʼ������
	void init_after_read()
	{

	}
}STT_MODULE, *PSTT_MODULE;

typedef struct stt_Bout_Attrs
{
	UINT m_nBout[16];//����16��������ֵͨ��0-�Ͽ���1-�պ�
	void init()
	{
		for(int i = 0; i < 16; i++)
		{
			m_nBout[i]=1;
		}
	}
}STT_BOUT_ATTRS, *PSTT_BOUT_ATTRS;

typedef struct stt_Bin_Adjust
{
public:
	long m_nGearCount;  //��λ��
	STT_CHANNEL_GEAR_ADJUST m_oBinGearAdj[ADJUST_MAX_GEAR_COUNT];

	void init()
	{
		m_nGearCount = 1;
		long nIndex = 0;

		for (nIndex=0; nIndex < ADJUST_MAX_GEAR_COUNT; nIndex++)
		{
			m_oBinGearAdj[nIndex].init();
		}
	}

	stt_Bin_Adjust(){}
	virtual ~stt_Bin_Adjust(){}
}STT_BIN_ADJUST, *PSTT_BIN_ADJUST;

typedef struct stt_Device_Attrs
{
	float m_fBaseFre;//�Ƶ��
	long m_nStateCount;//״̬��������(��)����Ϊ�����ϱ�
	long m_nBinCount;//���忪������(��)
	long m_nBinVoltMeas;//0-�޿����ѹ�ɼ����ܣ�1-�п����ѹ�ɼ�����
	long m_nBoutCount;//���忪������(��)
	long m_nBoutReplay;//�����ط�(0-��֧�֣�1-֧��)
	float m_fPhaseForMUTest;//�ϲ���Ԫʵ����λ����
//	UINT  m_nInputbinaryMode;//�������ɼ�ģʽ

//	UINT  m_nSMVTotalSize;//SMV�������
//	UINT  m_nGseOutTotalSize;//GOOSE�������
//	UINT  m_nGseInTotalSize;//goosein �������

	char m_strMngrVer[32]; //TestMngr�汾��
	char m_strAppVer[32]; //TestServer�汾��
	char m_strAppName[32]; //TestServer����
	char m_strFPGAVer[32]; //FPGA�汾��
	char m_strDriverVer[32]; //�����汾��
	char m_strDriverName[32]; //��������

	char m_strDeviceName[32];//�����ͺţ�����PN466
	char  m_strSN[32];//װ�����кţ��ַ����� 2020-10-14  lijunqing

	//��������
	char m_strDateProduce[24]; //2020-10-10��������λ�������ַ�������
	char m_strFactory[64]; //2020-10-10��������λ�������ַ�������

	long m_nCheckAuthority;//���ÿ���Ȩ���ж�
	long m_nSTModeSet;//N-����ST��ģʽ���������� 0-��������
	long m_nWindSpeed;//���������Ĭ��ģʽ��//1-�������� 0-��������
	void init()
	{
		m_nCheckAuthority = 0;
		m_nSTModeSet = 0;
		m_nWindSpeed = 1;
		m_fBaseFre=50;
		m_nBinCount = 10;
		m_nBinVoltMeas = 0;
		m_nBoutCount = 8;
		m_nBoutReplay = 0;
		m_fPhaseForMUTest = 0.0f;
		strcpy(m_strDeviceName, "PN");
		strcpy(m_strSN, "PONV-2020-1001-000");
		strcpy(m_strFactory, "�����������������ɷ����޹�˾");
		strcpy(m_strDateProduce, "2020-01-01");

		strcpy(m_strMngrVer, "-");
		strcpy(m_strAppVer, "-");
		strcpy(m_strFPGAVer, "-");
		strcpy(m_strDriverVer, "-");
	}
}STT_DEVICE_ATTRS, *PSTT_DEVICE_ATTRS;

typedef struct stt_Device_System_Parameter
{
	STT_DEVICE_ATTRS m_oDeviceAttrs;
	STT_BOUT_ATTRS m_oBoutTurnOnValue;//��������ֵͨ
	STT_BIN_ADJUST m_oBinAdj[16];//�������ɼ�У׼

	//ģ�����
	long m_nModuleCount;
	//2021-03-24 zhoulei
	//PI1000�����ƹ��12��.����11��,����1����1588��ʱ
	//FPGAֻ��λ��һ�߱�GOOSE���Ĺ���

	STT_MODULE m_oModules[ADJUST_MAX_MODULE_COUNT+1];//12ģ��+����С�ź�=13

	void init()
	{
		memset(&m_oDeviceAttrs, 0, sizeof (m_oDeviceAttrs));
		m_oDeviceAttrs.init();
		m_oBoutTurnOnValue.init();

		m_nModuleCount_U = 0;
		m_nModuleCount_I = 0;
		m_nModuleCount_D = 0;
		m_nModuleCount_FT3 = 0;
		m_nModuleCount_S = 0;
		m_nModuleCount_WEEK = 0;
		m_nModuleCount_Stable2M = 0;
		m_nModuleCount = 0;

		long nIndex=0;
		for (nIndex=0; nIndex<16; nIndex++)
		{
			m_oBinAdj[nIndex].init();
		}

		for (nIndex=0; nIndex<ADJUST_MAX_MODULE_COUNT; nIndex++)
		{
			m_oModules[nIndex].init();
			m_oModules_U[nIndex] = 0;
			m_oModules_I[nIndex] = 0;
			m_oModules_D[nIndex] = 0;
			m_oModules_FT3[nIndex] = 0;
			m_oModules_UI[nIndex] = 0;
			m_oModules_S[nIndex] = 0;
			m_oModules_WEEK[nIndex] = 0;
		}
		m_oModules_WEEK[ADJUST_MAX_MODULE_COUNT] = 0;
	}

	//2021-04-13 zhoulei
	long m_nModuleCount_U;//��ѹ
	long m_nModuleCount_I;//����
	long m_nModuleCount_D;//����9-2+ft3
	long m_nModuleCount_FT3;//����ft3
	long m_nModuleCount_S;//������
	long m_nModuleCount_WEEK;//С�ź�
	long m_nModuleCount_UI;//UI��ϲ��
	long m_nModuleCount_Stable2M;//�ȿ�2M���
	long m_nModuleCount_ADMU;//ADMU���
	long m_nModuleCount_U_MEAS;//�ɼ�ģ��
	long m_nModuleCount_I_MEAS;//�ɼ�ģ��

	PSTT_MODULE m_oModules_U[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_I[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_D[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_FT3[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_S[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_WEEK[ADJUST_MAX_MODULE_COUNT+1];//��������С�ź�
	PSTT_MODULE m_oModules_UI[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_Stable2M[ADJUST_MAX_MODULE_COUNT];//�ȿ�2M
	PSTT_MODULE m_oModules_ADMU[ADJUST_MAX_MODULE_COUNT];//ADMU
	PSTT_MODULE m_oModules_U_MEAS[ADJUST_MAX_MODULE_COUNT];
	PSTT_MODULE m_oModules_I_MEAS[ADJUST_MAX_MODULE_COUNT];

	void init_module_ref(long &nCount, PSTT_MODULE *ppModuleRef, long nModuleType)
	{
		for(int nModuleIndex = 1; nModuleIndex <= 16; nModuleIndex++)
		{
			for(long k = 0; k < m_nModuleCount; k++)
			{
				if(m_oModules[k].m_oModuleAttr.m_nModuleType == nModuleType)
				{
					if(m_oModules[k].m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_WEEK_EX)
					{
						if(m_oModules[k].m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PN_MAIN
								|| m_oModules[k].m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D)
						{
							m_oModules[k].m_oModuleAttr.m_nModuleIndex = 16;//PN����С�źŹ̶���λ��16
						}
					}

					if(m_oModules[k].m_oModuleAttr.m_nModuleIndex == nModuleIndex)
					{
						ppModuleRef[nCount] = &m_oModules[k];
						ppModuleRef[nCount]->InitChTmtCoef();
						nCount++;
						break;
					}
				}
			}
		}
	}

	void init_array_index(long nModuleType)
	{
		long nIndex = 0;
		for (long k=0; k<m_nModuleCount; k++)
		{
			if (m_oModules[k].m_oModuleAttr.m_nModuleType == nModuleType)
			{
				//				m_oModules[k].m_nArrayBeginIndex = nIndex;
				//				nIndex += ADJUST_MAX_CHANNEL_COUNT;
				nIndex +=m_oModules[k].m_oModuleAttr.m_nChannelNum;
				m_oModules[k].init_ch_drv_pos();
			}
		}
	}

	void set_DigitalTmtPos(PSTT_MODULE pModule)
	{
		PSTT_MODULE_CH_DEF pChDef;
		int nVoltChEeIndex = 0;
		int nCurrChEeIndex = 0;

		for(int nChanIndex = 0; nChanIndex < 18; nChanIndex++)
		{
			pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];
			pChDef->m_nEeType = STT_CH_EETYPE_VOLTAGE;
			pChDef->m_nChRsIndex = nChanIndex;//U0~U17
			pChDef->m_nChEeIndex = nVoltChEeIndex;
			nVoltChEeIndex++;
		}

		for(int nChanIndex = 19; nChanIndex < 37; nChanIndex++)
		{
			pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];
			pChDef->m_nEeType = STT_CH_EETYPE_CURRENT;
			pChDef->m_nChRsIndex = nChanIndex - 19; //I0~I17
			pChDef->m_nChEeIndex = nCurrChEeIndex;
			nCurrChEeIndex++;
		}

		pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[18];
		pChDef->m_nEeType = STT_CH_EETYPE_VOLTAGE;
		pChDef->m_nChRsIndex = 0;//Ĭ��Uz��ȡ����U0
		pChDef->m_nChEeIndex = 18;
		pModule->InitChTmtPos();
	}

	void set_DigitalTmtPosADMU(PSTT_MODULE pModule)
	{
		PSTT_MODULE_CH_DEF pChDef;
		int nVoltChEeIndex = 0;
		int nCurrChEeIndex = 0;

		for(int nChanIndex = 0; nChanIndex < 18; nChanIndex++)
		{
			pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];
			pChDef->m_nEeTypeEx = STT_CH_EETYPE_VOLTAGE;
			pChDef->m_nChRsIndexEx = nChanIndex;//U0~U17
			pChDef->m_nChEeIndexEx = nVoltChEeIndex;
			nVoltChEeIndex++;
		}

		for(int nChanIndex = 19; nChanIndex < 37; nChanIndex++)
		{
			pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];
			pChDef->m_nEeTypeEx = STT_CH_EETYPE_CURRENT;
			pChDef->m_nChRsIndexEx = nChanIndex - 19; //I0~I17
			pChDef->m_nChEeIndexEx = nCurrChEeIndex;
			nCurrChEeIndex++;
		}

		pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[18];
		pChDef->m_nEeTypeEx = STT_CH_EETYPE_VOLTAGE;
		pChDef->m_nChRsIndexEx = 0;//Ĭ��Uz��ȡ����U0
		pChDef->m_nChEeIndexEx = 18;
	}

	void init_module_ByIndexandType()
	{
		m_nModuleCount_U = 0;
		m_nModuleCount_I = 0;
		m_nModuleCount_D = 0;
		m_nModuleCount_FT3 = 0;
		m_nModuleCount_S = 0;
		m_nModuleCount_WEEK = 0;
		m_nModuleCount_UI = 0;
		m_nModuleCount_Stable2M = 0;
		m_nModuleCount_U_MEAS = 0;
		m_nModuleCount_I_MEAS = 0;

		for(long k = 0; k < m_nModuleCount; k++)
		{
			m_oModules[k].m_oModuleAttr.m_nErr = 0; //��ʼ��ʱ����
			m_oModules[k].m_oModuleAttr.m_nUsed = 1;
		}

		init_module_ref(m_nModuleCount_U_MEAS, m_oModules_U_MEAS, STT_MODULE_TYPE_MEAS_VOLT);
		init_module_ref(m_nModuleCount_I_MEAS, m_oModules_I_MEAS, STT_MODULE_TYPE_MEAS_CURRENT);
		init_module_ref(m_nModuleCount_U, m_oModules_U, STT_MODULE_TYPE_VOLT);
		init_module_ref(m_nModuleCount_I, m_oModules_I, STT_MODULE_TYPE_CURRENT);
		init_module_ref(m_nModuleCount_D, m_oModules_D, STT_MODULE_TYPE_DIGITAL_0G8M);
		init_module_ref(m_nModuleCount_D, m_oModules_D, STT_MODULE_TYPE_DIGITAL_2G6M);
		init_module_ref(m_nModuleCount_D, m_oModules_D, STT_MODULE_TYPE_DIGITAL_4G4M);
		init_module_ref(m_nModuleCount_FT3, m_oModules_FT3, STT_MODULE_TYPE_FT3);
		init_module_ref(m_nModuleCount_S, m_oModules_S, STT_MODULE_TYPE_SWITCH);
		init_module_ref(m_nModuleCount_WEEK, m_oModules_WEEK, STT_MODULE_TYPE_WEEK_EX);
		init_module_ref(m_nModuleCount_UI, m_oModules_UI, STT_MODULE_TYPE_VOLT_CURRENT);
		init_module_ref(m_nModuleCount_Stable2M, m_oModules_Stable2M, STT_MODULE_TYPE_Stable2M);
		init_module_ref(m_nModuleCount_ADMU, m_oModules_ADMU, STT_MODULE_TYPE_ADMU);
	}

	void init_module_ChDefMap()
	{
		int nBeginIndex = 0;
		int nVoltIndex = 0;
		int nCurrentIndex = 0;
		int nChannelNum;
		PSTT_MODULE_CH_DEF pChDef;
		PSTT_CHANNEL_WAVE_ADJUST pChWaveAdj;

		for(int nIndex = 0; nIndex < m_nModuleCount_U; nIndex++)
		{
			if(m_oModules_U[nIndex]->m_oModuleAttr.m_nChannelNum > 6)
			{
				m_oModules_U[nIndex]->m_oModuleAttr.m_nChannelNum = 6;
			}

			nChannelNum = m_oModules_U[nIndex]->m_oModuleAttr.m_nChannelNum;
			m_oModules_U[nIndex]->m_oModuleAttr.m_fDefChDcMax =
				m_oModules_U[nIndex]->m_oModuleAttr.m_fDefChMax * 1.414;

			for(int nChanIndex = 0; nChanIndex < nChannelNum; nChanIndex++)
			{
				pChDef = &m_oModules_U[nIndex]->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];
				pChDef->m_nEeType = STT_CH_EETYPE_VOLTAGE;
				pChDef->m_nChRsIndex = nBeginIndex + nChanIndex;
				pChDef->m_nChEeIndex = nChanIndex;
				pChDef->m_fChACMaxValue = m_oModules_U[nIndex]->m_oModuleAttr.m_fDefChMax;
				pChDef->m_fChDCMaxValue = m_oModules_U[nIndex]->m_oModuleAttr.m_fDefChDcMax;

				pChWaveAdj = &m_oModules_U[nIndex]->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChanIndex].m_pChWaveAdj[0];
				long nCount = pChWaveAdj->m_nGearCount;
				if(nCount > 0)
				{
					pChWaveAdj->m_oChGearAdj[nCount - 1].m_fGearValue = pChDef->m_fChDCMaxValue;
				}

				long nHarmCnt = m_oModules_U[nIndex]->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChanIndex].nHarmCount;
				for(int j = 1; j < nHarmCnt; j++)
				{
					pChWaveAdj = &m_oModules_U[nIndex]->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChanIndex].m_pChWaveAdj[j];
					nCount = pChWaveAdj->m_nGearCount;
					if(nCount > 0)
					{
						pChWaveAdj->m_oChGearAdj[nCount - 1].m_fGearValue = pChDef->m_fChACMaxValue;
					}
				}
			}

			nBeginIndex += nChannelNum;
			m_oModules_U[nIndex]->init_ch_drv_pos();
			m_oModules_U[nIndex]->InitChTmtPos();
		}

		nVoltIndex = nBeginIndex;
		nBeginIndex = 0;

		for(int nIndex = 0; nIndex < m_nModuleCount_I; nIndex++)
		{
			if(m_oModules_I[nIndex]->m_oModuleAttr.m_nChannelNum > 6)
			{
				m_oModules_I[nIndex]->m_oModuleAttr.m_nChannelNum = 6;
			}

			nChannelNum = m_oModules_I[nIndex]->m_oModuleAttr.m_nChannelNum;

			float fDefChDcMax1 = m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChMax * 0.5;
			float fDefChDcMax2 = m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChMax;
			if(m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChDcMax < fDefChDcMax1
					|| m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChDcMax > fDefChDcMax2)
			{
				m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChDcMax = fDefChDcMax1;
			}

			for(int nChanIndex = 0; nChanIndex < nChannelNum; nChanIndex++)
			{
				pChDef = &m_oModules_I[nIndex]->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];
				pChDef->m_nEeType = STT_CH_EETYPE_CURRENT;
				pChDef->m_nChRsIndex = nBeginIndex + nChanIndex;
				pChDef->m_nChEeIndex = nChanIndex;
				pChDef->m_fChACMaxValue = m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChMax;
				pChDef->m_fChDCMaxValue = m_oModules_I[nIndex]->m_oModuleAttr.m_fDefChDcMax;

				pChWaveAdj = &m_oModules_I[nIndex]->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChanIndex].m_pChWaveAdj[0];
				long nCount = pChWaveAdj->m_nGearCount;
				if(nCount > 0)
				{
					pChWaveAdj->m_oChGearAdj[nCount - 1].m_fGearValue = pChDef->m_fChDCMaxValue;
				}

				long nHarmCnt = m_oModules_I[nIndex]->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChanIndex].nHarmCount;
				for(int j = 1; j < nHarmCnt; j++)
				{
					pChWaveAdj = &m_oModules_I[nIndex]->m_oModuleAdjust.m_oTempAdjust[0].m_pChsAdjust[nChanIndex].m_pChWaveAdj[j];
					nCount = pChWaveAdj->m_nGearCount;
					if(nCount > 0)
					{
						pChWaveAdj->m_oChGearAdj[nCount - 1].m_fGearValue = pChDef->m_fChACMaxValue;
					}
				}
			}

			nBeginIndex += nChannelNum;
			m_oModules_I[nIndex]->init_ch_drv_pos();
			m_oModules_I[nIndex]->InitChTmtPos();
		}

		nCurrentIndex = nBeginIndex;

		for(int nIndex = 0; nIndex < m_nModuleCount_UI; nIndex++)
		{
			nChannelNum = m_oModules_UI[nIndex]->m_oModuleAttr.m_nChannelNum;
			int nVoltChEeIndex = 0;
			int nCurrChEeIndex = 0;

			for(int nChanIndex = 0; nChanIndex < nChannelNum; nChanIndex++)
			{
				pChDef = &m_oModules_UI[nIndex]->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];

				if(pChDef->m_nEeType == STT_CH_EETYPE_VOLTAGE)
				{
					pChDef->m_nChRsIndex = nVoltIndex++;
					pChDef->m_nChEeIndex = nVoltChEeIndex;
					nVoltChEeIndex++;
				}
				else
				{
					pChDef->m_nEeType = STT_CH_EETYPE_CURRENT;
					pChDef->m_nChRsIndex = nCurrentIndex++;
					pChDef->m_nChEeIndex = nCurrChEeIndex;
					nCurrChEeIndex++;
				}
			}

			m_oModules_UI[nIndex]->init_ch_drv_pos();
			m_oModules_UI[nIndex]->InitChTmtPos();
		}

		for(int nIndex = 0; nIndex < m_nModuleCount_D; nIndex++)
		{
			m_oModules_D[nIndex]->m_oModuleAttr.m_nChannelNum = 0;
			set_DigitalTmtPos(m_oModules_D[nIndex]);			
		}

		//20240111 zhoulei
		//С�źš�ADMU�������Դӳ��ͳһ��ʼ��
		nVoltIndex = 0;
		nCurrentIndex = 0;
		for(int k = 1; k <= 16; k++)
		{
			for(int nIndex = 0; nIndex < m_nModuleCount; nIndex++)
			{
				PSTT_MODULE pModule = &m_oModules[nIndex];
				if(pModule == NULL)
				{
					continue;
				}

				if(pModule->m_oModuleAttr.m_nModuleIndex == k)
				{
					if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_WEEK_EX
							|| pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_ADMU)
					{
						nChannelNum = pModule->m_oModuleAttr.m_nChannelNum;

						for(int nChanIndex = 0; nChanIndex < nChannelNum; nChanIndex++)
						{
							pChDef = &pModule->m_oModuleAttr.m_oChDefMap.m_oChDefs.m_oChDef[nChanIndex];

							if(pChDef->m_nEeType == 0)
							{
								pChDef->m_nEeType = STT_CH_EETYPE_VOLTAGE;
							}

							if(pChDef->m_nEeType == STT_CH_EETYPE_VOLTAGE)
							{
								pChDef->m_nChRsIndex = nVoltIndex++;
							}
							else
							{
								pChDef->m_nChRsIndex = nCurrentIndex++;
							}

							pChDef->m_nChEeIndex = nChanIndex;
						}
						pModule->init_ch_drv_pos();

						if(pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_ADMU)
						{
							set_DigitalTmtPosADMU(pModule);
						}

						pModule->InitChTmtPos();
					}
				}
			}
		}

		for(int nIndex = 0; nIndex < m_nModuleCount_FT3; nIndex++)
		{
			m_oModules_FT3[nIndex]->m_oModuleAttr.m_nChannelNum = 0;
			set_DigitalTmtPos(m_oModules_FT3[nIndex]);			
		}		
	}

	void init_after_read()
	{
		init_module_ByIndexandType();
		init_module_ChDefMap();

		for(int i = 0;i<m_nModuleCount_WEEK;i++)
		{
			PSTT_MODULE pModule = m_oModules_WEEK[i];
			if(pModule == NULL)
			{
				continue;
			}

			if(pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6I20mA
					||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_DC6U10V
					||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_EVTECT
					||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_L336D
					||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PIA12DS
					||pModule->m_oModuleAttr.m_nModulePower == STT_MODULE_WEEK_PNS331
					||pModule->m_oModuleAttr.m_nModuleType == STT_MODULE_TYPE_ADMU)
			{
				//ͨ���������Ͳ��ɱ�ԭ��
				//1��ʵ�������ѹ�źŻ�����ź�
				//2����ѹ�����ĵ�λ����̻�
				pModule->m_oModuleAttr.m_nChTypeChg = 0;
			}
		}
	}

	void init_module_hd_ch_id(PSTT_MODULE *pModules, char chType, long nCount, long &nModuleIndex)
	{
		for (long nIndex=0; nIndex<nCount; nIndex++)
		{
			pModules[nIndex]->m_oModuleAttr.init_hd_ch_def(nModuleIndex, chType);
			nModuleIndex++;
		}
	}

	void init_hd_ch_id()
	{
		long nModuleIndex_U = 0;
		long nModuleIndex_I = 0;
		long nModuleIndex = 0;

		//ģ����
		init_module_hd_ch_id(m_oModules_U, STT_MODULETYPE_ID_ANALOG_CHAR, m_nModuleCount_U, nModuleIndex_U);
		init_module_hd_ch_id(m_oModules_I, STT_MODULETYPE_ID_ANALOG_CHAR, m_nModuleCount_I, nModuleIndex_I);
        nModuleIndex = nModuleIndex_U > nModuleIndex_I ? nModuleIndex_U: nModuleIndex_I;//max(nModuleIndex_U, nModuleIndex_I);
		init_module_hd_ch_id(m_oModules_UI, STT_MODULETYPE_ID_ANALOG_CHAR, m_nModuleCount_UI, nModuleIndex);

		//����
		//20230918 zhoulei FT3��9-2���ְ桢ADMUͳһ����
		//��װλ���Ⱥ�˳��FT3��ADMU��9-2���ְ�
		nModuleIndex = 0;
		for(int k = 1; k <= 16; k++)
		{
			for(long nIndex = 0; nIndex < m_nModuleCount; nIndex++)
			{
				PST_MODULE_ATTR pModuleAttr = &m_oModules[nIndex].m_oModuleAttr;

				if(pModuleAttr->m_nModuleType == STT_MODULE_TYPE_DIGITAL_0G8M
						|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_DIGITAL_2G6M
						|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_DIGITAL_4G4M
						|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_FT3
						|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_ADMU)
				{
					if(pModuleAttr->m_nModuleIndex == k)
					{
						if(pModuleAttr->m_nModuleType == STT_MODULE_TYPE_ADMU)
						{
							PSTT_MODULE_CH_DEFS  pChDefs = &pModuleAttr->m_oChDefMap.m_oChDefs;
							for (long nIndex=0; nIndex< DIGITAL_CHANNEL_MAX; nIndex++)
							{
								sprintf(pChDefs->m_oChDef[nIndex].m_pszChIdEx, "%c%c%d_%d",pChDefs->m_oChDef[nIndex].m_nEeTypeEx ,
										'd',  nModuleIndex+1, pChDefs->m_oChDef[nIndex].m_nChEeIndexEx+1);
							}
						}
						else
						{
							pModuleAttr->init_hd_ch_def(nModuleIndex, STT_MODULETYPE_ID_DIGITAL_CHAR);
						}
						nModuleIndex++;
						break;
					}
				}
			}
		}

		//С�źŲ����ADMU���ͳһ���
		nModuleIndex = 0;
		for(int k = 1; k <= 16; k++)
		{
			for(long nIndex = 0; nIndex < m_nModuleCount; nIndex++)
			{
				PST_MODULE_ATTR pModuleAttr = &m_oModules[nIndex].m_oModuleAttr;

				if(pModuleAttr->m_nModuleType == STT_MODULE_TYPE_WEEK_EX
						|| pModuleAttr->m_nModuleType == STT_MODULE_TYPE_ADMU)
				{
					if(pModuleAttr->m_nModuleIndex == k)
					{
						pModuleAttr->init_hd_ch_def(nModuleIndex++, STT_MODULETYPE_ID_WEEK_CHAR);
						break;
					}
				}
			}
		}

		//������
		nModuleIndex = 0;
		init_module_hd_ch_id(m_oModules_S, STT_MODULETYPE_ID_BINARY_CHAR, m_nModuleCount_S, nModuleIndex);
	}

}STT_DEVICESYSTEMPARAMETER, *PSTT_DEVICESYSTEMPARAMETER;

extern PSTT_DEVICESYSTEMPARAMETER g_theDeviceSystemParameter;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// \brief stt_init_paras
/// \param pParas
///
///
///
///
void stt_create_adjust_ex();
void stt_init_adj_para_config();
void stt_xml_serialize_adj_para_config(CSttXmlSerializeBase *pXmlSerialize);

bool stt_open_adjust_file(const char *pszFileName);
bool stt_open_adjust_file_path(const CString &strFilePath);//zhouhj 20210506 ���Ӹ����ļ�·��ȥ��ȡDevice���ܣ�
void stt_xml_serialize_write_adjust();
void stt_xml_serialize_register_adjust(const CString &strXMLPath);

//2021-5-2  lijunqing save-adjust-file
bool stt_save_adjust_file(const char *pszFileName);


void stt_xml_serialize_register_adjust(CSttXmlSerializeTool &oSttXmlSerializeTool);
void stt_xml_serialize_register_adjust();
void stt_xml_serialize_register_adjust(CSttXmlSerializeBase *pXmlSerialize);
void stt_init_paras(STT_DEVICESYSTEMPARAMETER *pParas);

void stt_xml_serialize_AdjItem(PSTT_ADJUST_ITEM pPara,  CSttXmlSerializeBase *pXmlSerialize);

void stt_xml_serialize(STT_MODULE &oPara, long nIndex, CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize(STT_DEVICESYSTEMPARAMETER *pPara, CSttXmlSerializeBase *pXmlSerialize);


//����У׼�����ļ�
void stt_create_adjust();
PSTT_DEVICESYSTEMPARAMETER stt_create_adjust(long nTemperatureCount, long nModuleCount, long nHarmCount, long nGearCount, long nHdGearCount);
bool stt_init_adjust(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, long nTemperatureCount, long nModuleCount, long nHarmCount, long nGearCount, long nHdGearCount);
void stt_free_adjust();

//2021-11-15 zhoulei �޸�ԭ��ͬ���Ͷ�ģ������,PSTT_MODULE pModule
PSTT_MODULE stt_adj_find_module_byModulePos(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, long nModulePos, long nModuleType);
PSTT_CHANNEL_WAVE_ADJUST stt_adj_find_ch_wave(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PSTT_MODULE pModule, float fTemperature, long nChannel, long nFreqSel);
PSTT_CHANNEL_WAVE_ADJUST stt_adj_find_ch_wave(PSTT_TRANGE_ADJUST  pTemperatureAdj, long nChannel, long nFreqSel);
PSTT_CHANNEL_ADJUSTS stt_adj_find_channel(PSTT_MODULE pModule, long nChannel, float fTemperature);

PSTT_ADJUST_ITEM stt_adj_find_adjust_item(PSTT_DEVICESYSTEMPARAMETER pDvSysParas, PSTT_MODULE pModule, float fTemperature, long nChannel, long nFreqSel, float fAmp);
PSTT_ADJUST_ITEM stt_adj_get_ac(float fAmp,PSTT_MODULE pModule,int nChannel,float fTemperature,int nHarm=1);

//���Ӳ����λ���ֵ
//float stt_adj_get_ac_max(float fAmp, PSTT_MODULE pModule);
//int stt_adj_get_ac_HGearID(float fAmp, PSTT_MODULE pModule);
float stt_adj_get_ac_max_GearVal(float nChannel, PSTT_MODULE pModule, int nHarm = 1);

//��òɼ�ϵ��
PSTT_ADJUST_ITEM stt_adj_find_meas_u_item(float fGearVal,int nModulePos,int nChannel,float fTemperature,int nHarm=1);
PSTT_ADJUST_ITEM stt_adj_find_meas_i_item(float fGearVal,int nModulePos,int nChannel,float fTemperature,int nHarm=1);
//////////////////////////////////////////////////////////////////////////
//
//���л��������ͣ��ַ��� ==>>  �ı�  2021-5-4  lijunqing
void stt_xml_serialize_data_type(CSttXmlSerializeBase *pXmlSerialize, const char *pszName, const char *pszID, const char *pszUnit, const char *pszDataType, long &nValue);

#endif // TMT_ADJUST_SYS_PARAMETER_H

