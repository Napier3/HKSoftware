//----------------------------------------------------------------------
//Fault ö�ٱ���, ���ڲ��Ͷ��ο���ʹ��
//��������: FaultEnum_... 
//----------------------------------------------------------------------
//   FaultEnum_Error -- ��������еĴ���������
//----------------------------------------------------
//   FaultEnum_DRTSMode -- ���ͬ����ʽ
//   FaultEnum_TestMode -- ��������ģʽ
//   FaultEnum_TestState -- ��ǰ����״̬
//   FaultEnum_Fault     -- ��������
//   FaultEnum_CalcuMode -- ��·����ģ��
//   FaultEnum_KL_Mode   -- ���򲹳�ϵ��������ģʽ
//   FaultEnum_TrigMode -- ������ʽ(���ϴ���, ״̬����)
//   FaultEnum_UxMode -- Ux �����ʽ(��4·��ѹ)
//   FaultEnum_SynMode -- ���������з�ʽ
//   FaultEnum_UabcMode -- Uabc ϵͳ�����ʽ
//   FaultEnum_IabcMode -- Iabc ϵͳ�����ʽ
//----------------------------------------------------
//   FaultEnum_Diff_TestItem -- �����: ������Ŀ
//   FaultEnum_Diff_FaultType -- �����: �������(��������)
//   FaultEnum_Diff_IdEquation -- �����: �����
//   FaultEnum_Diff_IrEquation_0 -- �����: �ƶ�����
//   FaultEnum_Diff_IrEquation_1
//   FaultEnum_Diff_IrEquation_2
//   FaultEnum_Diff_IrEquation_3
//   FaultEnum_Diff_IrEquation_4
//   FaultEnum_Diff_ProtSort -- �����: ��������
//   FaultEnum_Diff_TransWindType -- �����: ��ѹ��������: ˫����, ������
//   FaultEnum_Diff_TransGroupMode_2Windings -- �����: �������(˫����)Y/Y-12, Y/D-11, ...
//   FaultEnum_Diff_TransGroupMode_3Windings --                   (������)Y/Y/Y-12, ... 
//   FaultEnum_Diff_AdoptWind -- �����: �������������
//   FaultEnum_Diff_PhaseCompMode -- �����: ��λ������ʽ
//----------------------------------------------------
//   FaultEnum_Syn_TestItem -- ͬ������: ������Ŀ


//---------------------------------------------------------------------
#if !defined(_FaultDEF_ENUM)
#define _FaultDEF_ENUM

//���ͬ����ʽ: ���ͬ����, ����ʱ��
enum FaultEnum_DRTSMode
{
	DRTSMODE_NO=-1,	DRTSMODE_SYNBOX,	DRTSMODE_GRIDPLL,	//��ͬ������, ���ͬ����, ����ͬ��
};
//�������Է�ʽ
enum FaultEnum_TestMode
{
	TESTMODE_SINGLE=0,  TESTMODE_BATCH,  TESTMODE_FROM,  TESTMODE_FAILED,
};
//��ǰ����״̬
enum FaultEnum_TestState
{
	TESTSTATE_WAIT=-1,  TESTSTATE_FAIL,  TESTSTATE_SUCCESS,  TESTSTATE_TESTING
};

enum FaultEnum_FaultType
{
	FAULT_FREESET=-1,		//�Զ������
	FAULT_A,				//����ӵ�
	FAULT_B,
	FAULT_C,
	FAULT_AB,				//�������
	FAULT_BC,
	FAULT_CA,
	FAULT_ABE,				//����ӵ�
	FAULT_BCE,
	FAULT_CAE,
	FAULT_ABC,				//�����·
};
enum FaultEnum_CalcuMode
{
	CALCUMODE_IF=0,			//0--��·���� If �㶨
	CALCUMODE_UF,			//1--��·��ѹ Uf �㶨
	CALCUMODE_ZS,			//2--��Դ�迹 Zs �㶨
};
enum FaultEnum_KL_Mode
{
	KL=0,					//0--Բ�� KL ��ʽ, KL=(Z0-Z1)/3Z1
	KR_KX,					//1--�ı��� KR, KX ��ʽ, KR=(R0-R1)/3R1, KX=(X0-X1)/3X1
};
enum FaultEnum_TrigMode
{
	TRIGMODE_PRESSKEY=0,		//0--��������
	TRIGMODE_TIMER,				//1--ʱ�䴥��
	TRIGMODE_GPS,				//2--GPS����
	TRIGMODE_BIN,				//3--����ӵ㷭ת����
	TRIGMODE_MAG,				//4--��ֵ����
	TRIGMODE_FRE,				//5--Ƶ�ʴ���
	TRIGMODE_BIN_TIMER,			//6--����ӵ㷭ת���� + �����ʱ
};
enum FaultEnum_UabcMode
{
	UABC_MAPTO_ABC=0,	//0--abc
	UABC_MAPTO_XYZ,		//1--xyz
	UABC_MAPTO_UVW,		//2--uvw
	UABC_MAPTO_RST,		//3--rst
};
enum FaultEnum_IabcMode
{
	IABC_MAPTO_ABC=0,	//0--abc
	IABC_MAPTO_XYZ,		//1--xyz
	IABC_MAPTO_UVW,		//2--uvw
	IABC_MAPTO_RST,		//3--rst
	IABC_MAPTO_GROUP12_PARALLEL,	//4--12�鲢��
	IABC_MAPTO_GROUP123_PARALLEL,	//5--123�鲢��
};
enum FaultEnum_UxMode
{
	UX_NONEED=-1,		//����Ҫ�� 4 ·��ѹ Ux;
	UX_3U0=0,			//+3U0
	UX_3U0_NEG,			//-3U0
	UX_3U0_ROOT3,		//+��3 * 3Uo
	UX_3U0_ROOT3_NEG,	//-��3 * 3Uo
	UX_SYN_A,		//��ͬ��A
	UX_SYN_B,		//��ͬ��B
	UX_SYN_C,		//��ͬ��C
	UX_SYN_AB,		//��ͬ��AB
	UX_SYN_BC,		//��ͬ��BC
	UX_SYN_CA,		//��ͬ��CA
};
enum FaultEnum_SynMode		//���������з�ʽ
{
	SYNMODE_NO,			//0--��ͬ��, ��������
	SYNMODE_GPS,		//1--GPS ͬ��
	SYNMODE_GRIDPLL,	//2--����ͬ��
};

//----------------------------------------------------------------------
enum FaultEnum_Diff_TestItem
{
	BIASED_DIFFERENTIAL=0,	    //0--�����ƶ�
	HARMONIC_RESTRAIN,			//1--г���ƶ�
	DEADANG_RESTRAIN,			//2--��Ͻ��ƶ�
};
enum FaultEnum_Diff_FaultType
{
	DIFF_A=0,
	DIFF_B,
	DIFF_C,
	DIFF_AB,
	DIFF_BC,
	DIFF_CA,
	DIFF_ABC,
};
enum FaultEnum_Diff_IdEquation	//�������� Id
{
	ID0 = 0,	//0-- Id= I1
	ID1,		//1-- Id=|I1'+I2'|
	ID2,		//2-- Id=|I1'-I2'|
	ID3,		//3-- Id=|I1'+I2'|^2
	ID4,		//4-- Id=|I1'-I2'|^2
};
enum FaultEnum_Diff_IrEquation_0	//�������� Ir, IdEquation=0
{
	IR0_ID0 = 0,		//0-- Ir= I2
};
enum FaultEnum_Diff_IrEquation_1	//�������� Ir, IdEquation=1
{
	IR0_ID1 = 0,		//0-- Ir = |I1'-I2'|/K
	IR1_ID1,			//1-- Ir = Max(|I1'|,|I2'|)*K
	IR2_ID1,			//2-- Ir = |I2'|
	IR3_ID1,			//3-- Ir = |Id-|I1'|-|I2'||
	IR4_ID1,			//4-- Ir = (|I1'|+|I2'|)/K
	IR5_ID1,			//5-- Ir = |Imax'-��Ii'|/K, Ii'��Imax'
	IR6_ID1,			//6-- Ir = ��(|I1'��I2'| * cos��)
};
enum FaultEnum_Diff_IrEquation_2	//�������� Ir, IdEquation=2
{
	IR0_ID2 = 0,		//0-- Ir = |I1'+I2'|/K
	IR1_ID2,			//1-- Ir = Max(|I1'|,|I2'|)*K
	IR2_ID2,			//2-- Ir = |I2'|
	IR3_ID2,			//3-- Ir = |Id-|I1'|-|I2'||
	IR4_ID2,			//4-- Ir = (|I1'|+|I2'|)/K
	IR5_ID2,			//5-- Ir = |Imax'+��Ii'|/K, Ii'��Imax'
	IR6_ID2,			//6-- Ir = ��(|I1'��I2'| * cos��)
};
enum FaultEnum_Diff_IrEquation_3	//�������� Ir, IdEquation=3
{
	IR0_ID3 = 0,		//Ir = -|I1'��I2'| * cos��
};
enum FaultEnum_Diff_IrEquation_4	//�������� Ir, IdEquation=4
{
	IR0_ID4 = 0,		//Ir = |I1'��I2'| * cos��
};

enum FaultEnum_Diff_ProtSort
{
	PROT_TRANS=0,	//0--��ѹ��
	PROT_GENTRANS,	//1--������
	PROT_GEN,		//2--�����
	PROT_BUS,		//3--ĸ��
};
enum FaultEnum_Diff_TransWindType
{
	TWO_WINDINGS=0,		//0--˫����
	THREE_WINDINGS,		//1--������
};
enum FaultEnum_Diff_TransGroupMode_2Windings	//˫�Ʊ�������
{
	YY_12=0,
	YD_11,
	YD_1,
	YD_3,
	YD_5,   
	YD_7,
	YD_9,
	YY_2,
	YY_4,
	YY_6,
	YY_8, 
	YY_10,
};
enum FaultEnum_Diff_TransGroupMode_3Windings	//���Ʊ�������
{
	YYY_12=0, 
	YYD_11,
	YYD_1,
	YDD_11,
	YDD_1,
};
enum FaultEnum_Diff_AdoptWind	//��������ı�ѹ������
{
	H_L=0,		//0--��-��
	H_M,		//1--��-��
	M_L,		//2--��-��
};
enum FaultEnum_Diff_PhaseCompMode	//�����ڲ���λУ����ʽ
{
	PHASECOMP_NO=0,			//0--��У��
	PHASECOMP_Y,			//1--Y��У��
	PHASECOMP_D,			//2--d��У��
};
enum FaultEnum_Diff5_TransGroupMode	//������ѹ�����(���)
{
	DIFF5_BALANCE_Z=0,		//0-- ƽ���ѹ�� -- �迹ƥ��
	DIFF5_YD11,				//1-- Y/��-11 ��ѹ��
	DIFF5_VV,				//2-- V/V ��ѹ��
	DIFF5_BALANCE_SCOTT,	//3-- ƽ���ѹ�� -- SCOTT
	DIFF5_YDD,				//4-- Y/��/��-11��ѹ��
	DIFF5_VX,				//5-- V/X ��ѹ��
	DIFF5_SINGLEPHASE,		//6-- �����ѹ��
};

enum FaultEnum_Syn_TestType		//ͬ������: ������Ŀ���
{
	SYN_CHECK=0,			//0--��բ�����: ���, �Ƿ��բ(��¼��ǰ��, ���㵼ǰʱ��)
	SYN_ADJUSTV,			//1--��ѹ����
	SYN_ADJUSTFRE,			//2--��Ƶ����
	SYN_ADJUSTAUTO,			//3--�Զ���������
};

#endif