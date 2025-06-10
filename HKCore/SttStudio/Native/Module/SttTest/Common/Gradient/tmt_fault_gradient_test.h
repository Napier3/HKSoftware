#pragma once

#include "../tmt_gradient_test.h"
//////////////////////////////////////////////////////////////////////////

//�����ͽ���������� ����
#define FG_EstimateRow		8
#define FG_EstimateCol		5

//FG  FaultGradient  ���ϵݱ�
//���Է��ػ�����  
enum SttFaultGradientTestMode
{
	FG_TestMode_ActValue = 0,		//����ֵ
	FG_TestMode_ReturnCoef,			//����ϵ��
	FG_TestMode_MaxAngle,			//���������
	FG_TestMode_Null
};

//����ģʽ
enum SttFaultGradientFaultMode
{
	FG_FaultMode_A = 0,				//A���·
	FG_FaultMode_B,					//B���·
	FG_FaultMode_C,					//C���·
	FG_FaultMode_ABC,				//ABC���·
	FG_FaultMode_AB,				//AB���·
	FG_FaultMode_BC,				//BC���·
	FG_FaultMode_CA,				//CA���·
	FG_FaultMode_AB_C,				//AB���·��C�����
	FG_FaultMode_BC_A,				//BC���·��A�����
	FG_FaultMode_CA_B,				//CA���·��B�����
	FG_FaultMode_AB_B,				//AB���·��B�����
	FG_FaultMode_BC_C,				//BC���·��C�����
	FG_FaultMode_CA_A,				//CA���·��A�����
	//FG_FaultMode_CA_A,			//CA���·��A�����  ����
	FG_FaultMode_UF,				//U/f
	FG_FaultMode_I2I1,				//I2/I1
	FG_FaultMode_Null
};

//����ģʽ�ı�( FaultGradientFaultMode  FG_FM )  �仯��ֵ
enum SttFG_FM_Value
{
	FG_FM_Vaule_ShortVM = 0,		//��·��ѹ
	FG_FM_Vaule_ShortVA,			//��·����
	FG_FM_Vaule_ImpedeAngle,		//�迹��
	FG_FM_Vaule_ShortImpede,		//��·�迹
	FG_FM_Vaule_Frequency,			//Ƶ��
	FG_FM_Vaule_PlusVM,				//�����ѹ
	FG_FM_Vaule_MinusVM,			//�����ѹ
	FG_FM_Vaule_ZeroVM,				//�����ѹ��3U0��
	//AB���·��C�����
	FG_FM_Vaule_Uab_c = 0,			//Uab
	FG_FM_Vaule_Ic_ab,				//Ic
	FG_FM_Vaule_Uab_Ic,				//��(Uab-Ic)
	//BC���·��A�����
	FG_FM_Vaule_Ubc_a = 0,			//
	FG_FM_Vaule_Ia_bc,				//
	FG_FM_Vaule_Ubc_Ia,				//
	//CA���·��B�����
	FG_FM_Vaule_Uca_b = 0,			//
	FG_FM_Vaule_Ib_ca,				//
	FG_FM_Vaule_Uca_Ib,				//
	//AB���·��B�����
	FG_FM_Vaule_Uab_b = 0,			//
	FG_FM_Vaule_Ib_ab,				//
	FG_FM_Vaule_Uab_Ib,				//
	//BC���·��C�����
	FG_FM_Vaule_Ubc_c= 0,			//
	FG_FM_Vaule_Ic_bc,				//
	FG_FM_Vaule_Ubc_Ic,				//
	//CA���·��A�����
	FG_FM_Vaule_Uca_a = 0,			//
	FG_FM_Vaule_Ia_ca,				//
	FG_FM_Vaule_Uca_Ia,				//
	//U/f
	FG_FM_Vaule_VM = 0,				//��ѹ
	FG_FM_Vaule_HZ,				    //Ƶ��
	FG_FM_Vaule_I2 = 0,				//I2
	FG_FM_Vaule_Null = 200
};

//��ѹ����
enum SttFaultGradientTypeVM
{
	FG_Type_VM_Plus = 0,			//����(U1)
	FG_Type_VM_Minus,				//����(U2)
	FG_Type_VM_Zero,				//����(3U0)
	FG_Type_VM_Null
};


//////�·����� 
typedef struct tmt_fault_gradient_paras
{

public:
	float m_fStart;								//�仯ʼֵ
	float m_fStop;  							//�仯��ֵ
	float m_fStep;							    //�仯����
	float m_fFaultTime;							//����ʱ��
	int	  m_nTestMode;							//��������
	///////////////
	int	  m_nFaultMode;							//����ģʽ    m_nChannel
	int	  m_nChangeValue;						//�仯��	  m_nType
	float m_fShortVm;							//��·��ѹ
	int   m_nShortVmType;						//��·��ѹ
	float m_fShortVa;							//��·����
	float m_fAngle;								//�迹��
	///////////
	float m_fPrepareTime;						//�仯ǰʱ��
	float m_fPreFaultTime;						//����ǰʱ��
	float m_fPreFaultEDU;						//����ǰ��ѹ
	float m_fPreFaultEDI;						//����ǰ����
	float m_fEDUaIaAngle;						//����ǰ���
	//////////
	int	  m_nBinLogic;							//�߼�����   0-�� 1-��
	tmt_BinaryIn  m_binIn[MAX_BINARYIN_COUNT];
	tmt_BinaryOut m_binOut[2][MAX_BINARYOUT_COUNT];	//0-�ǹ���̬���� 1-����̬����

	//////////////////////////////////////
	//GoosePub
	tmt_GoosePub m_oGoosePub[MAX_MODULES_GOOSEPUB_COUNT];

	//��ֵ
	float m_fUSet;								//��ѹ��������ֵ
	float m_fISet;								//������������ֵ
	float m_fAngleSet;							//��λ��������ֵ
	float m_fHzSet;								//Ƶ����������ֵ
	float m_fRetCoefSet;						//����ϵ������ֵ
	float m_fAngleFSet;							//�߽��1����ֵ
	float m_fAngleSSet;							//�߽��2����ֵ
	float m_fMaxAngleSet;						//�������������ֵ

	//����
	float m_fUActVal_AbsErr; 					//��ѹ����ֵ�������
	float m_fUActVal_RelErr; 					//��ѹ����ֵ������ 		
	long m_nUActVal_ErrorLogic; 				//��ѹ����ֵ����ж��߼� 	
	float m_fIActVal_AbsErr; 					//��������ֵ������� 		
	float m_fIActVal_RelErr; 					//��������ֵ������ 		
	long m_nIActVal_ErrorLogic; 				//��������ֵ����ж��߼� 	
	float m_fAngleActVal_AbsErr; 				//��λ����ֵ������� 		
	float m_fAngleActVal_RelErr; 				//��λ����ֵ������ 		
	long m_nAngleActVal_ErrorLogic; 			//��λ����ֵ����ж��߼� 	
	float m_fHzActVal_AbsErr; 					//Ƶ�ʶ���ֵ������� 		
	float m_fHzActVal_RelErr; 					//Ƶ�ʶ���ֵ������ 		
	long m_nHzActVal_ErrorLogic; 				//Ƶ�ʶ���ֵ����ж��߼� 	
	float m_fRetCoef_AbsErr; 					//����ϵ��������� 		
	float m_fRetCoef_RelErr;					//����ϵ�������� 		
	long m_nRetCoef_ErrorLogic; 				//����ϵ������ж��߼� 	
	float m_fMaxAngle_AbsErr; 					//��������Ǿ������		
	float m_fMaxAngle_RelErr; 					//��������������� 		
	long m_nMaxAngle_ErrorLogic; 				//�������������ж��߼�	
	float m_fAngleF_AbsErr; 					//�߽��1�������			
	float m_fAngleF_RelErr; 					//�߽��1������			
	long m_nAngleF_ErrorLogic; 					//�߽��1����ж��߼� 		
	float m_fAngleS_AbsErr; 					//�߽��2������� 			
	float m_fAngleS_RelErr; 					//�߽��2������ 			
	long m_nAngleS_ErrorLogic; 					//�߽��2����ж��߼�		
	/////////////////////////

	void init()
	{
		m_fStart = 0;
		m_fStop = 0;
		m_fStep = 0;
		m_fFaultTime = 0;
		m_nTestMode = FG_TestMode_ActValue;

		m_nFaultMode = FG_FaultMode_A;
		m_nChangeValue = FG_FM_Vaule_ShortVM;
		m_fShortVm = 0;
		m_nShortVmType = FG_Type_VM_Plus;
		m_fShortVa = 0;
		m_fAngle = 0;

		m_fPrepareTime = 0;
		m_fPreFaultTime = 0;
		m_fPreFaultEDU = 0;
		m_fPreFaultEDI = 0;
		m_fEDUaIaAngle = 0;

		m_nBinLogic = 0;
		for (int i=0;i<MAX_BINARYIN_COUNT;i++)
		{
			m_binIn[i].init();
			for(int j=0;j<2;j++)
			{
				m_binOut[j][i].init();
			}
		}

		m_fUSet = 0;		
		m_fISet = 0;		
		m_fAngleSet = 30;	
		m_fHzSet = 50;
		m_fRetCoefSet = 0;	
		m_fAngleFSet = 0;	
		m_fAngleSSet = 0;	
		m_fMaxAngleSet = 0;	

		m_fUActVal_AbsErr = 0;
		m_fUActVal_RelErr = 0;
		m_nUActVal_ErrorLogic = 0;
		m_fIActVal_AbsErr = 0;
		m_fIActVal_RelErr = 0;
		m_nIActVal_ErrorLogic = 0;
		m_fAngleActVal_AbsErr = 0;
		m_fAngleActVal_RelErr = 0;
		m_nAngleActVal_ErrorLogic = 0;
		m_fHzActVal_AbsErr = 0;		
		m_fHzActVal_RelErr = 0;		
		m_nHzActVal_ErrorLogic = 0;		
		m_fRetCoef_AbsErr = 0; 		
		m_fRetCoef_RelErr = 0;		
		m_nRetCoef_ErrorLogic = 0;	
		m_fMaxAngle_AbsErr = 0;		
		m_fMaxAngle_RelErr = 0;		
		m_nMaxAngle_ErrorLogic = 0; 	
		m_fAngleF_AbsErr = 0;		
		m_fAngleF_RelErr = 0;		
		m_nAngleF_ErrorLogic = 0;	
		m_fAngleS_AbsErr = 0; 		
		m_fAngleS_RelErr = 0; 		
		m_nAngleS_ErrorLogic = 0;
	}

	tmt_fault_gradient_paras()	{}
}tmt_faultGradientParas;



///////////////////////////////////////////////���ؽ��
//���ز���-���������
typedef struct tmt_fault_gradient_max_angle_result
{
public:
	float m_fAngleF;					//�߽��1
	float m_fAngleS;					//�߽��2
	float m_fMaxAngle;					//���������
	int  m_nAngleF_StepIndex;			//�׶˱߽�ǵĵݱ䲽��,��0��ʼ����,0Ϊʼֵ
	long m_nAngleS_StepIndex;			//ĩ�˱߽�ǵĵݱ䲽��,��0��ʼ����,0Ϊʼֵ
	int   m_nActF;						//1-���� 0-û����
	int   m_nActS;						//1-���� 0-û����

	void init()
	{
		m_fAngleF = 0;
		m_fAngleS = 0;
		m_fMaxAngle = 0;
		m_nAngleF_StepIndex = 0;
		m_nAngleS_StepIndex = 0;
		m_nActF = 0;
		m_nActS = 0;
	}

	tmt_fault_gradient_max_angle_result(){}
}tmt_FaultGradientMaxAngleResult;


typedef struct tmt_fault_gradient_result
{
public:

	float m_fTripValue;							//����ֵ
	float m_fTripTime;							//����ʱ��
	float m_fTripValueChl[MAX_BINARYIN_COUNT];	//����ֵ��Ĭ����0
	float m_fTripValueExChl[MAX_ExBINARY_COUNT];//0-�ǹ���̬���� 1-����̬����
	float m_fReturnValue;
	float m_fReturnCoef;						//����ֵ/����ֵ
	int   m_nAct;								//1-���� 0-û����
	float m_fPhiAngleValue;
	tmt_FaultGradientMaxAngleResult m_oMaxAngle;

	//����
	float m_fTripUErrVal;						//��ѹ����ֵ���
	float m_fTripIErrVal;						//��������ֵ���
	float m_fTripHzErrVal;						//Ƶ�ʶ���ֵ���
	float m_fTripAngleErrVal;					//��λ����ֵ���
	float m_fRetCoefErrVal;						//����ϵ�����
	float m_fMaxAngleErrVal;					//������������
	float m_fAngleFErrVal;						//�߽��1���
	float m_fAngleSErrVal;						//�߽��2���

	void init()
	{
		m_fTripValue = 0;
		m_fTripTime = 0;
		m_fReturnValue = 0;
		m_fReturnCoef = 0;
		m_nAct = 0;
		m_fPhiAngleValue = 0;
		m_oMaxAngle.init();

		m_fTripUErrVal = 0;
		m_fTripIErrVal = 0;
		m_fTripHzErrVal = 0;
		m_fTripAngleErrVal = 0;
		m_fRetCoefErrVal = 0;
		m_fMaxAngleErrVal = 0;
		m_fAngleFErrVal = 0;
		m_fAngleSErrVal = 0;

		for(int i=0; i<MAX_BINARYIN_COUNT; i++)
		{
			m_fTripValueChl[i] = 0;
		}

		for(int i = 0; i < g_nBinExCount && i < MAX_ExBINARY_COUNT; i++)
		{
			m_fTripValueExChl[i] = 0;
		}
	}

	tmt_fault_gradient_result()	{}
}tmt_faultGradientResult;


typedef struct tmt_fault_gradient_test : public TMT_PARAS_HEAD
{
public:
	tmt_faultGradientParas m_oFaultGradientParas;
	tmt_faultGradientResult m_oFaultResult;

	void init()
	{
		init_head(); 
		strcpy(m_pszMacroID,STT_MACRO_ID_FaultGradientTest);
		m_nSelected = 1;
		m_nVersion = 0x00010001;
		m_nTestState = 0;

		m_oFaultGradientParas.init();
		m_oFaultResult.init();
	}

	tmt_fault_gradient_test(){init();}
}tmt_faultGradientTest;



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void stt_xml_serialize(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
void stt_xml_serialize(tmt_faultGradientResult *pResults, CSttXmlSerializeBase *pXmlSierialize);
//���� ����ֵ ���л�
void stt_xml_serialize_base(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//������ �߼�����
void stt_xml_serialize_binary_AndOr(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//������ 
void stt_xml_serialize_binary_in(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//��̬���� ���Ͽ���
void stt_xml_serialize_binary_out(tmt_faultGradientParas *pParas, CSttXmlSerializeBase *pXmlSierialize);
//����ֵ 
void stt_xml_serialize_FaultGradientSetting(tmt_faultGradientParas *pParas,CSttXmlSerializeBase *pXmlSierialize);
//���� ���ֵ 
void stt_xml_serialize_FaultGradientError(tmt_faultGradientParas *pParas,CSttXmlSerializeBase *pXmlSierialize);

//���ԣ��ļ����� �鿴
void stt_xml_serialize_write_FaultGradientTest();