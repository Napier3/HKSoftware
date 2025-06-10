#ifndef _SttTestSysGlobalPara_h_
#define _SttTestSysGlobalPara_h_

#include "SttTest/Common/SttSystemConfig.h"
#include "SttTest/Common/tmt_pt_test.h"
#include "SttTest/Common/tmt_common_def.h"
#include "../../Module/DataMngr/DvmValues.h"
#include "SttCmd/SttParas.h"

#define BININ_NUM	10
#define BINOUT_NUM	8

#define Postfix_StateTest		"sttxml"
#define Postfix_ManualTest		"mntxml"
#define Postfix_HarmTest		"hrmxml"
#define Postfix_SoeTest			"soexml"
#define Postfix_SystemParas		"sysxml"
#define Postfix_GradientTest	"grtxml"
#define Postfix_CBOperateTest	"cbtxml"
#define Postfix_DistanceTest	"dttxml"
#define Postfix_ZeroSequenceTest "zstxml"
#define Postfix_Reclose			"rctxml"
#define Postfix_OverCurrentTest  "octxml"
#define Postfix_DifferTest		"dftxml"

#define CHANNAL_TYPE_U(x) (x >= 0 && x < 3) || (x >= 4 && x <= 11) || (x == 23) || (x >= 25 && x <= 29) || (x >= 35 && x <= 36) 
#define CHANNAL_TYPE_I(x) (x >= 12 && x < 23) || (x == 24) || (x >= 30 && x <= 34) || (x >= 38 && x <= 42) 
#define CHANNAL_TYPE_F(x) (x == 37)

//cl�����20230807
#define SEQUENCE_CHANNAL_TYPE_U(x) (x >= 0 && x <= 5)
#define SEQUENCE_CHANNAL_TYPE_I(x) (x >= 6 && x <= 11)
//gyp�ߵ�ѹ20230828
#define LINEVOL_CHANNAL_TYPE_U(x) (x >= 0 && x <= 3)
#define LINEVOL_CHANNAL_TYPE_I(x) (x >= 4 && x <= 11)
enum value_type{
	V_Primary = 0,
	V_Secondary = 1
};

enum HarmGrad_type{
	Amplitude_HarmGradType = 0,
	Percent_HarmGradType = 1
};

//#define  STT_LINEVOLT_Grad_Ch_Uab1              0
//#define  STT_LINEVOLT_Grad_Ch_3U1_0             1
//#define  STT_LINEVOLT_Grad_Ch_Uab2              2
//#define  STT_LINEVOLT_Grad_Ch_3U2_0             3
//#define  STT_LINEVOLT_Grad_Ch_Ia1               4
//#define  STT_LINEVOLT_Grad_Ch_Ib1               5
//#define  STT_LINEVOLT_Grad_Ch_Ic1               6
//#define  STT_LINEVOLT_Grad_Ch_Ia2               7
//#define  STT_LINEVOLT_Grad_Ch_Ib2               8
//#define  STT_LINEVOLT_Grad_Ch_Ic2               9

enum Sequence_type
{
	v11_type = 0, //u1-1
	v12_type = 1, //u1-2
	v10_type = 2,  //u1-0
	v21_type = 3,  //u2-1
	v22_type = 4, //u2-2
	v20_type = 5, //u2-0

	i11_type = 6, 
	i12_type = 7, 
	i10_type = 8,  
	i21_type = 9,
	i22_type = 10,
	i20_type = 11
};
enum LineVolt_type
{
	LineVolt_vab1_type = 0,
	LineVolt_v1_0_type = 1,
	LineVolt_vab2_type = 2,
	LineVolt_v2_0_type = 3,

	LineVolt_ia1_type = 4,
	LineVolt_ib1_type = 5,
	LineVolt_ic1_type = 6,
	LineVolt_ia2_type = 7,
	LineVolt_ib2_type = 8,
	LineVolt_ic2_type = 9,
	LineVolt_iabc1_type = 10,
	LineVolt_iabc2_type = 11
};

enum DCOverLoad_type
{
	I11_type = 0,
	I12_type = 1,
	I13_type = 2,
	I21_type = 3,
	I22_type = 4,
	I23_type = 5,
	I31_type = 6,
	I32_type = 7,
	I33_type = 8,
	I41_type = 9,
	I42_type = 10,
	I43_type = 11
};

enum OverLoad_type
{
	Ia1_type = 0,
	Ib1_type = 1,
	Ic1_type = 2,
};

enum para_type
{
	va1_type = 0,
	vb1_type = 1,
	vc1_type = 2,
	null_type = 3,
	vab1_type = 4,
	vbc1_type = 5,
	vca1_type = 6,
	vabc1_type = 7,
	va2_type = 8,
	vb2_type = 9,
	vc2_type = 10,
	vabc2_type = 11,
	ia1_type = 12,
	ib1_type = 13,
	ic1_type = 14,
	iab1_type = 15,
	ibc1_type = 16,
	ica1_type = 17,
	iabc1_type = 18,
	ia2_type = 19,
	ib2_type = 20,
	ic2_type = 21,
	iabc2_type = 22,
	vall_type= 23,
	iall_type = 24,
	vdc_type = 25,
	vz_type=26,
	vab2_type = 27,
	vbc2_type = 28,
	vca2_type = 29,
	iab2_type = 30,
	ibc2_type = 31,
	ica2_type = 32,
	iabcAdd_type = 33,
	ia2b2c2Add_type =34,				 //a2+b2+c2
	vabcAdd_type= 35,
	va2b2c2Add_type = 36,				 //va2+vb2+vc2
	freAll_type = 37,
	iaia2Add_type = 38,					 //ia+ia2
	ibib2Add_type = 39,					 //ib+ib2
	icic2Add_type = 40,					 //ic+ic2
	iaia2Add_ibib2Add_icic2Add_type = 41,//ia+ia2,ib+ib2,ic+ic2
	iaia2ibib2icic2Add_type = 42		 //ia+ia2+ib+ib2+ic+ic2
};

struct LocalSysPara
{
	float m_fAuxVDc;				//����ֱ����ѹ
	float m_fAuxIDc;				//����ֱ������ 
	int m_nCHVNum;					//�����Դ��ѹͨ����
	int m_nCHINum;					//�����Դ����ͨ����
// 	int m_nCHBinInNum;				//����������Ĭ��ֵ10����  //zhouhj 20220401 ͳһ����ȫ�ֵ����忪�뿪��
// 	int m_nCHBinOutNum;			//����������Ĭ��ֵ8����������ֵͨ��������
	int m_nMaxHarmCount; //zhouhj 20220401 ���г������
	int m_nCHBinInExNum;			//��չ��������
	int m_nCHBinOutExNum;			//��չ��������
	value_type vType;			//һ�Ρ�����
	float m_fDigVMax;
	float m_fDigIMax;
	bool m_bIsHasDcOut;			//ֱ���������
	int m_nDcVModuleNum;
	int m_nDcIModuleNum;

	float m_fAC_VolMax;//ģ����������ѹ���ֵ
	float m_fAC_VolMin;//ģ����������ѹ��Сֵ(����ͨ�����ֵ�е���Сֵ)
	float m_fAC_CurMax;//ģ���������������ֵ
	float m_fAC_CurMin;//ģ��������������Сֵ(����ͨ�����ֵ�е���Сֵ)
	float m_fDC_VolMax;//ģ����ֱ����ѹ���ֵ
	float m_fDC_VolMin;//ģ����ֱ����ѹ��Сֵ(����ͨ�����ֵ�е���Сֵ)
	float m_fDC_CurMax;//ģ����ֱ���������ֵ
	float m_fDC_CurMin;//ģ����ֱ��������Сֵ(����ͨ�����ֵ�е���Сֵ)
	float m_fWeakCurrMax;//С�źŵ������ֵ
	float m_fWeakVolMax;//С�źŵ�ѹ���ֵ
	long m_nSupportAnalogOutput;//�Ƿ�֧��ģ�����
	long m_nSupportDigitalOutput;//�Ƿ�֧���������
	long m_nSupportWeakOutput;//�Ƿ�֧�����ź����
	long m_nHasSyn;//�Ƿ��Ѷ�ʱ
	long m_nTotalLC_Num;//9-2��GOOSE������������
	long m_nLC_GFiberNum;//9-2��GOOSEǧ�׿�����
	long m_nTotalSTSend_Num;//FT3�⴮�ڷ�������
	long m_nTotalSTRecv_Num;//FT3�⴮�ڽ������� (�ⲿ���)
// 	long m_nSTModeSet; //ST���ʹ��

	//zhouhj 2024.6.12 ���ڲ����ǵײ���¼����������
	long m_nTesterVerIdx;//�����豸״̬���
	long m_nRTData_Num;//dingxy 20240620 ���ʵʱ�����Ƿ���յ�
// 	long m_nTesterHasMouse;//(0-�����,1-�����)
// 	CString m_strTesterKeyBoardString;//���ü��̻�������

	void InitMaxMinVolCurValue()//��ʼ����ѹ���������Сֵ,�����ڸ���ģ�����������Сֵ�����,��������Ϊ��С��ֵ
	{
		m_fAC_VolMax = 0;	//130
		m_fAC_VolMin = 0;
		m_fAC_CurMax = 0;	//20
		m_fAC_CurMin = 0;

		m_fDC_VolMax = 0;	//100
		m_fDC_VolMin = 0;
		m_fDC_CurMax = 0;	//20
		m_fDC_CurMin = 0;
		m_fWeakCurrMax = 20;
		m_fWeakVolMax = 100;
	}

	LocalSysPara()
	{
		m_fAuxVDc = 130;
		m_fAuxIDc = 10;
		m_nCHVNum = 4;
		m_nCHINum = 3;
// 		m_nCHBinInNum = BININ_NUM;
// 		m_nCHBinOutNum = BINOUT_NUM;
		m_nMaxHarmCount = 31;//ȱʡΪ31��
		m_fDigVMax = 2000;
		m_fDigIMax = 2000;
		m_bIsHasDcOut = false;
		m_nDcVModuleNum = 1;
		m_nDcIModuleNum = 1;

		InitMaxMinVolCurValue();

		m_nSupportAnalogOutput = 1;
		m_nSupportDigitalOutput = 0;
		m_nSupportWeakOutput = 0;
		m_nHasSyn = 0;
		m_nTotalLC_Num = 8;
		m_nTotalSTSend_Num = 6;
		m_nLC_GFiberNum = 1;
		m_nTotalSTRecv_Num = 2;

		m_nTesterVerIdx = -1;
		m_nRTData_Num = 0;
// 		m_nTesterHasMouse = -1;
// 		m_strTesterKeyBoardString = "";
// 		m_nSTModeSet = 0;

	}

	LocalSysPara &operator = (const LocalSysPara &right)
	{
		m_fAuxVDc = right.m_fAuxVDc;
		m_fAuxIDc = right.m_fAuxIDc;
		m_nCHVNum = right.m_nCHVNum;
		m_nCHINum = right.m_nCHINum;
// 		m_nCHBinInNum = right.m_nCHBinInNum;
// 		m_nCHBinOutNum = right.m_nCHBinOutNum;
		m_nMaxHarmCount = right.m_nMaxHarmCount;
		m_fDigVMax = right.m_fDigVMax;
		m_fDigIMax = right.m_fDigIMax;
		m_bIsHasDcOut = right.m_bIsHasDcOut;
		m_nDcVModuleNum = right.m_nDcVModuleNum;
		m_nDcIModuleNum = right.m_nDcIModuleNum;
		return *this;
	}

	bool operator==(const LocalSysPara right) const
	{
		return (m_fAuxVDc==right.m_fAuxVDc && m_fAuxIDc==right.m_fAuxIDc\
			&& m_fDigVMax==right.m_fDigVMax && m_fDigIMax==right.m_fDigIMax\
			&& m_bIsHasDcOut==right.m_bIsHasDcOut &&m_nDcVModuleNum==right.m_nDcVModuleNum && m_nDcIModuleNum==right.m_nDcIModuleNum);
	};
};

// extern STT_SystemParas g_oSystemParas; //2023-11-17 suyang �ظ�ɾ��

extern TMT_SYSTEM_DEFAULT_OUTPUT_PARAS g_oDefaultOutputPara;
extern STT_SystemParas g_oSystemParas;
extern tmt_PtPara g_oPTTestPara;

extern LocalSysPara g_oLocalSysPara;

//2022-9-19  lijunqing  ͬ���Ĵ��룬�����˺ü����ط�
void stt_SystemParas_GetString(CString &strSysParas);
void stt_SystemParas_SetString(const CString &strSysParas);
void stt_SystemParas_SetString(char *strSysParas, long nLen);
long Global_GetMaxFreq();
BOOL GetResultStringGradientTest(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults);
BOOL GetResultStringLineVolGradientTest(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults);
BOOL GetResultStringSequenceGradientTest(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults);
BOOL GetResultStringULockOverCurrent(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults);
BOOL GetResultStringPowerDirection(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults);
BOOL GetResultStringVoltageActValue(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults);
BOOL GetResultStringCurrentActValue(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults);
BOOL GetResultStringDistanceSearchTest(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults);
BOOL GetResultStringStateTest(CDvmValues *pValues,BOOL &bHasActValue,CString &strResultsString,CSttResults &pTestMacroResults);
//��__DATE__��ȡ����������ת��Ϊ�����յ�����
CString Global_GetSoftwareGeneVersion(const CString &strVersionString);


#endif
