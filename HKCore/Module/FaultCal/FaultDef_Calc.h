//----------------------------------------------------------------------
//Fault������������ṹ�嶨��
//
//���������õ� enum �� ..\TestMacroGlobalDefine.h
//           define �� FaultDef.h, FaultDef_Struct.h
//
//2013-3-20: ���� FaultCalc_Fault_Ex, FaultCalc_Shot_Ex ��չ�ĳ�����ϼ���ģ��
//          ���� Ks_Mode ����
//          Ks_Mode = 0 -- Ks ��������;
//                    1 -- Ks = KL;
//2013-7-18: ���� FaultCalc_GPFault_Ex, FaultCalc_GPDistance_Ex ��Ƶ�仯����·����ģ��
//          ���� CalcuMode ����(����̱�����̲�ͬ)
//          CalcuMode = 0 -- ����̱���ʽ;
//                      1 -- ��̹�ʽ;
//----------------------------------------------------------------------
//1. ��������: 
//   FaultStruct_ ...     -- �ڲ�ʹ�õĹ����ṹ��
//   FaultTest_ ...       -- ������������ṹ��
//   FaultCalc_ ...       -- ������������ṹ��
//   FaultResult_...      -- ����ṹ��(���Խ��)
//   FaultCalcResult_...  -- ����ṹ��(������)
//----------------------------------------------------------------------
//2. �������ʹ�õĲ����ṹ�� 
//   FaultCalc_LoadState    -- �������и���״̬����
//   FaultCalc_Fault        -- �����·�������
//   FaultCalc_Fault_Ex     -- �����·�������: ��չ, ���� Ks_Mode
//   FaultCalc_GPFault      -- ��Ƶ�仯����·�������
//   FaultCalc_GPFault_Ex   -- ��Ƶ�仯����·�������: ��չ, ���� CalcuMode(����̱�����̲�ͬ)
//   FaultCalc_ABCPP        -- ABC ���� <--> �߷���
//   FaultCalc_ABC120       -- ABC ���� <--> �����
//   FaultCalc_PQ           -- ���๦�ʼ���, P,Q, cos;  
//
//   FaultCalc_Shot         -- �����������
//   FaultCalc_Shot_Ex      -- �����������: ��չ, ���� Ks_Mode
//   FaultCalc_Distance     -- ���뱣����ֵУ�����
//   FaultCalc_GPDistance   -- ��Ƶ�仯���迹��ֵУ�����
//   FaultCalc_GPDistance_Ex-- ��Ƶ�仯���迹��ֵУ�����
//   FaultCalc_OverCurr     -- ����������ֵУ�����
//   FaultCalc_ZeroSeqCurr  -- �������������ֵУ�����
//   FaultCalc_NegSeqCurr   -- �������������ֵУ�����
//
//   FaultCalc_Diff         -- �����: ���� Id,Ir �����������ӵ��� Iabc,Ixyz
//   FaultCalc_Diff_Shot    -- �����: �����
//   FaultCalc_Diff_IrId    -- �����: ���� 6 ·����, �������������
//   FaultCalc_Diff_KP      -- �����: ����ϵ�� KPH,M,L ��������
//
//   FaultCalc_Diff5        -- �����: ���� Id,Ir �����������ӵ��� Iabc,Ixy
//
//   FaultCalc_Osc          -- ������: ��ǰ���������, ������װ�� K ��ĵ�ѹ������Чֵ
//   FaultCalc_Osc_Zk       -- ������: ��ǰ���������, ������װ�� K ��Ĳ����迹

#if !defined(_FaultDEF_CALC)
#define _FaultDEF_CALC

#include "FaultDef.h"
#include "..\TestMacroGlobalDefine.h"
#include "FaultDef_Struct.h"
//----------------------------------------------------------------------
//���㹦�ܱ��� nCalcID
//----------------------------------------------------------------------
#define CALCID_LOADSTATE	0	//�������и���״̬����
#define	CALCID_FAULT		1	//�����·: �������ģ��
#define CALCID_GPFAULT		2	//�����·: ��Ƶ�仯������ģ��
#define CALCID_ABCTOPP		3	//�߷�������: ABC -> PP
#define CALCID_PPTOABC		4	//            PP -> ABC
#define CALCID_ABCTO120		5	//���������: ABC -> 120
#define CALCID_120TOABC		6	//            120 -> ABC
#define CALCID_ABCTOPQ		7	//�������๦��
//
#define CALCID_SHOT			100		//�����������: ���ݽ����������3��״̬�µĵ�ѹ����(����UI)
#define CALCID_DISTANCE		101		//���뱣����ֵУ�����
#define CALCID_GPDISTANCE	102		//��Ƶ�仯���迹������ֵУ�����
#define CALCID_OVERCURR		103		//����������ֵУ�����
#define CALCID_NEGSEQCURR	104		//�������������ֵУ�����
#define CALCID_ZEROSEQCURR	105		//�������������ֵУ�����
//
#define CALCID_DIFF			120		//�����: ���� Id,Ir �����������ӵ��� Iabc,Ixyz
#define CALCID_DIFF_KP		121		//�����: ����ϵ�� KP123 ��������
#define CALCID_DIFF_SHOT	122		//�����: �����
#define CALCID_DIFF_IRID	123		//�����: ���� I1[3], I2[3] �����������������
//
#define CALCID_DIFF5		130		//�����: ���� Id,Ir �����������ӵ��� Iabc,Ixy
//
#define CALCID_OSC			140		//������: ��ǰ���������, ������װ�� K ��ĵ�ѹ������Чֵ
#define CALCID_OSC_ZK		141		//������: ��ǰ���������, ������װ�� K ��Ĳ����迹
//
#define	CALCID_FAULT_EX			200		//�����·: �������ģ��, ��չ, ���� Ks_Mode
#define CALCID_SHOT_EX			201		//�����������: ��չ, ���� Ks_Mode
#define CALCID_GPFAULT_EX		202		//��Ƶ�仯������: ��չ, ���� CalcuMode
#define CALCID_GPDISTANCE_EX	203		//��Ƶ�仯���迹������ֵУ�����: ��չ, ���� CalcuMode

//----------------------------------------------------------------------
struct FaultCalcResult_UpIp
{
	FaultStruct_Phase Up[3];
	FaultStruct_Phase Ip[3];
};
struct FaultCalcResult_Up
{
	FaultStruct_Phase Up[3]; 
};
struct FaultCalcResult_Ip
{
	FaultStruct_Phase Ip[3]; 
};
struct FaultCalcResult_PQ
{
	float P;
	float Q;
	float COS;
};

struct FaultCalcResult_Shot
{
	FaultStruct_Phase Up_PreFault[3];	//����ǰ��ѹ����: 3U, 3I
	FaultStruct_Phase Ip_PreFault[3];
	//
	FaultStruct_Phase Up_Fault[3];		//���ϵ�ѹ����: 3U, 3I
	FaultStruct_Phase Ip_Fault[3];
	//
	FaultStruct_Phase Up_TransFault[3];	//����ת�����ѹ����: 3U, 3I
	FaultStruct_Phase Ip_TransFault[3];
};

struct FaultCalcResult_Diff
{
	FaultStruct_Phase Ip[6];		//��������: [012]--I1��abc, [345]--I2��abc
	//
	FaultStruct_Phase Ip_Harm[6];	//г���ƶ�: ����г������
	//
	float GapAng[6];				//��Ͻ��ƶ�: ��Ͻ�
};
struct FaultCalcResult_Diff_KP
{
	float KPH;			//��ѹ�ಹ��ϵ��
	float KPM;			//��ѹ�ಹ��ϵ��
	float KPL;			//��ѹ�ಹ��ϵ��
};

struct FaultCalcResult_Diff_IrId
{
	float Id[3];	//�������
	float Ir[3];	//��������
};


//--------------------------------------------------------------------------------
//�������и���״̬����
struct FaultCalc_LoadState
{
	float Us;			//���ѹ
	float ILoad_Mag;	//���ɵ���
	float ILoad_Ang;	//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	FaultCalcResult_UpIp Result;
};

//�����·�������(�����������)
struct FaultCalc_Fault
{
	float Us;				//���ѹ
	float ILoad_Mag;		//���ɵ���
	float ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	int FaultType;			//��������: �� FaultEnum_FaultType
	int FaultDirection;		//���Ϸ���: 0--������, 1--������
	float FaultUf;			//��·��ѹ(����ģ��Ϊ����ѹʱ��Ч)
	float FaultIf;			//��·����(����ģ��Ϊ������ʱ��Ч)
	float FaultZf_Mag;		//��·�迹
	float FaultZf_Ang;
	//
	int CalcuMode;			//��·����ģ��: ��� FaultEnum_CalcuMode
	float Zs_Mag;			//��Դ���迹(��Zsģ����Ч)
	float Zs_Ang;
	float Ks_Mag;			//��Դ���迹�����򲹳�ϵ��(��ֵ,�Ƕ�)
	float Ks_Ang;
	int KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	float KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	float KL_Ang;
	float KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	float KL_KX;
	//
	FaultCalcResult_UpIp Result;
};

//�����·�������(�����������): ��չ, ���� Ks_Mode
struct FaultCalc_Fault_Ex
{
	float Us;				//���ѹ
	float ILoad_Mag;		//���ɵ���
	float ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	int FaultType;			//��������: �� FaultEnum_FaultType
	int FaultDirection;		//���Ϸ���: 0--������, 1--������
	float FaultUf;			//��·��ѹ(����ģ��Ϊ����ѹʱ��Ч)
	float FaultIf;			//��·����(����ģ��Ϊ������ʱ��Ч)
	float FaultZf_Mag;		//��·�迹
	float FaultZf_Ang;
	//
	int CalcuMode;			//��·����ģ��: ��� FaultEnum_CalcuMode
	float Zs_Mag;			//��Դ���迹(��Zsģ����Ч)
	float Zs_Ang;
	//
	int Ks_Mode;			//��Դ�迹�����򲹳�ϵ�����÷�ʽ: 0--Ks ����, 1--Ks=KL;
	float Ks_Mag;			//��Դ���迹�����򲹳�ϵ��(��ֵ,�Ƕ�)
	float Ks_Ang;
	//
	int KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	float KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	float KL_Ang;
	float KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	float KL_KX;
	//
	FaultCalcResult_UpIp Result;
};

//��Ƶ�仯����·�������
struct FaultCalc_GPFault
{
	float Zzd_Mag;			//�����迹
	float Zzd_Ang;
	float m;				//У���: m=0.9, 1.1, ...
	float FaultIf;			//��·����(����ģ��Ϊ������ʱ��Ч)
	int FaultType;			//��������: �� FaultEnum_FaultType
	int FaultDirection;		//���Ϸ���: 0--������, 1--������
	//
	float Us;				//���ѹ
	float ILoad_Mag;		//���ɵ���
	float ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	int KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	float KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	float KL_Ang;
	float KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	float KL_KX;
	//
	FaultCalcResult_UpIp Result;
};

//��Ƶ�仯����·�������: ��չ, ���� CalcuMode;
struct FaultCalc_GPFault_Ex
{
	int CalcuMode;			//0--����̱���ʽ,  1--��̹�ʽ
	//
	float Zzd_Mag;			//�����迹
	float Zzd_Ang;
	float m;				//У���: m=0.9, 1.1, ...
	float FaultIf;			//��·����(����ģ��Ϊ������ʱ��Ч)
	int FaultType;			//��������: �� FaultEnum_FaultType
	int FaultDirection;		//���Ϸ���: 0--������, 1--������
	//
	float Us;				//���ѹ
	float ILoad_Mag;		//���ɵ���
	float ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	int KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	float KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	float KL_Ang;
	float KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	float KL_KX;
	//
	FaultCalcResult_UpIp Result;
};

//ABC ���� <-> �߷��� ת������
struct FaultCalc_ABCPP
{
	FaultStruct_Phase Up[3]; 
	FaultCalcResult_Up Result;
};

//ABC ���� <-> ����� ת������
struct FaultCalc_ABC120
{
	FaultStruct_Phase Up[3]; 
	FaultCalcResult_Up Result;
};

//���๦�ʼ���
struct FaultCalc_PQ
{
	int CalcuMode;					//0--����Ʒ�, 1--����Ʒ�
	FaultStruct_Phase Up[3];		//�����ѹ: ��ֵ, �Ƕ�
	FaultStruct_Phase Ip[3];		//�������: ��ֵ, �Ƕ�
	FaultCalcResult_PQ Result;
};

//�����������: ���ݽ����������3��״̬�µĵ�ѹ����(����UI)
struct FaultCalc_Shot
{
	//����ǰ
	float Us;				//���ѹ
	float ILoad_Mag;		//���ɵ���
	float ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//����
	int FaultType;			//��������: �� FaultEnum_FaultType
	int FaultDirection;		//���Ϸ���: 0--������, 1--������
	float FaultUf;			//��·��ѹ(����ģ��Ϊ����ѹʱ��Ч)
	float FaultIf;			//��·����(����ģ��Ϊ������ʱ��Ч)
	float FaultZf_Mag;		//��·�迹
	float FaultZf_Ang;
	//����ת��
	int bFaultTrans;			//�Ƿ�������ת��: 0--��, 1--��;
	int TransFaultType;			//��������: �� FaultEnum_FaultType
	int TransFaultDirection;	//���Ϸ���: 0--������, 1--������
	float TransFaultUf;			//��·��ѹ(����ģ��Ϊ����ѹʱ��Ч)
	float TransFaultIf;			//��·����(����ģ��Ϊ������ʱ��Ч)
	float TransFaultZf_Mag;		//��·�迹
	float TransFaultZf_Ang;
	//
	int CalcuMode;			//��·����ģ��: ��� FaultEnum_CalcuMode
	float Zs_Mag;			//��Դ���迹(��Zsģ����Ч)
	float Zs_Ang;
	float Ks_Mag;			//��Դ���迹�����򲹳�ϵ��(��ֵ,�Ƕ�)
	float Ks_Ang;
	int KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	float KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	float KL_Ang;
	float KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//�����������: ���ݽ����������3��״̬�µĵ�ѹ����(����UI): ��չ, ���� Ks_Mode
struct FaultCalc_Shot_Ex
{
	//����ǰ
	float Us;				//���ѹ
	float ILoad_Mag;		//���ɵ���
	float ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//����
	int FaultType;			//��������: �� FaultEnum_FaultType
	int FaultDirection;		//���Ϸ���: 0--������, 1--������
	float FaultUf;			//��·��ѹ(����ģ��Ϊ����ѹʱ��Ч)
	float FaultIf;			//��·����(����ģ��Ϊ������ʱ��Ч)
	float FaultZf_Mag;		//��·�迹
	float FaultZf_Ang;
	//����ת��
	int bFaultTrans;			//�Ƿ�������ת��: 0--��, 1--��;
	int TransFaultType;			//��������: �� FaultEnum_FaultType
	int TransFaultDirection;	//���Ϸ���: 0--������, 1--������
	float TransFaultUf;			//��·��ѹ(����ģ��Ϊ����ѹʱ��Ч)
	float TransFaultIf;			//��·����(����ģ��Ϊ������ʱ��Ч)
	float TransFaultZf_Mag;		//��·�迹
	float TransFaultZf_Ang;
	//
	int CalcuMode;			//��·����ģ��: ��� FaultEnum_CalcuMode
	float Zs_Mag;			//��Դ���迹(��Zsģ����Ч)
	float Zs_Ang;
	//
	int Ks_Mode;			//��Դ�迹�����򲹳�ϵ�����÷�ʽ: 0--Ks ����, 1--Ks=KL;
	float Ks_Mag;			//��Դ���迹�����򲹳�ϵ��(��ֵ,�Ƕ�)
	float Ks_Ang;
	//
	int KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	float KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	float KL_Ang;
	float KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//���뱣����ֵУ�����(�����ǹ���ת��): ���ݽ���������� 2 ��״̬�µĵ�ѹ����(����UI)
//����ģ��: �̶�Ϊ������
struct FaultCalc_Distance
{
	float Zzd_Mag;			//�迹��ֵ
	float Zzd_Ang;
	float Zf_Ratio;			//��·�迹: ����
	float FaultIf;			//��·����(����ģ��: ������)
	int FaultType;			//��������: �� FaultEnum_FaultType
	int FaultDirection;		//���Ϸ���: 0--������, 1--������
	//
	float Us;				//���ѹ
	float ILoad_Mag;		//���ɵ���
	float ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	int KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	float KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	float KL_Ang;
	float KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//��Ƶ�仯���迹������ֵУ�����(�����ǹ���ת��): ���ݽ���������� 2 ��״̬�µĵ�ѹ����(����UI)
struct FaultCalc_GPDistance
{
	float Zzd_Mag;			//�����迹
	float Zzd_Ang;
	float m;				//У���: m=0.9, 1.1, ...
	float FaultIf;			//��·����(����ģ��: ������)
	int FaultType;			//��������: �� FaultEnum_FaultType
	int FaultDirection;		//���Ϸ���: 0--������, 1--������
	//
	float Us;				//���ѹ
	float ILoad_Mag;		//���ɵ���
	float ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	int KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	float KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	float KL_Ang;
	float KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//��Ƶ�仯���迹������ֵУ�����(�����ǹ���ת��): ���ݽ���������� 2 ��״̬�µĵ�ѹ����(����UI)
struct FaultCalc_GPDistance_Ex
{
	int CalcuMode;			//0--����̱���ʽ,  1--��̹�ʽ
	//
	float Zzd_Mag;			//�����迹
	float Zzd_Ang;
	float m;				//У���: m=0.9, 1.1, ...
	float FaultIf;			//��·����(����ģ��: ������)
	int FaultType;			//��������: �� FaultEnum_FaultType
	int FaultDirection;		//���Ϸ���: 0--������, 1--������
	//
	float Us;				//���ѹ
	float ILoad_Mag;		//���ɵ���
	float ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	int KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	float KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	float KL_Ang;
	float KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//����������ֵУ�����(�����ǹ���ת��): ���ݽ���������� 2 ��״̬�µĵ�ѹ����(����UI)
//����ģ��: �̶�Ϊ������
struct FaultCalc_OverCurr
{
	float Izd;				//������ֵ
	float If_Ratio;			//��·����: ����
	float Zf_Mag;			//��·�迹: ��ֵ, ������ (����ģ��: ������)
	float Zf_Ang;
	int FaultType;			//��������: �� FaultEnum_FaultType
	int FaultDirection;		//���Ϸ���: 0--������, 1--������
	//
	float Us;				//���ѹ
	float ILoad_Mag;		//���ɵ���
	float ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	int KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	float KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	float KL_Ang;
	float KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//�������������ֵУ�����(�����ǹ���ת��): ���ݽ���������� 2 ��״̬�µĵ�ѹ����(����UI)
//����ģ��: �̶�Ϊ������
struct FaultCalc_NegSeqCurr
{
	float Izd;				//������� I2 ��ֵ
	float If_Ratio;			//��·����: ����
	float Zf_Mag;			//��·�迹: ��ֵ, ������ (����ģ��: ������)
	float Zf_Ang;
	int FaultType;			//��������: �� FaultEnum_FaultType
	int FaultDirection;		//���Ϸ���: 0--������, 1--������
	//
	float Us;				//���ѹ
	float ILoad_Mag;		//���ɵ���
	float ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	int KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	float KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	float KL_Ang;
	float KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//�������������ֵУ�����(�����ǹ���ת��): ���ݽ���������� 2 ��״̬�µĵ�ѹ����(����UI)
//����ģ��: �̶�Ϊ������
struct FaultCalc_ZeroSeqCurr
{
	float Izd;				//������� 3I0 ��ֵ
	float If_Ratio;			//��·����: ����
	float Zf_Mag;			//��·�迹: ��ֵ, ������ (����ģ��: ������)
	float Zf_Ang;
	int FaultType;			//��������: �� FaultEnum_FaultType
	int FaultDirection;		//���Ϸ���: 0--������, 1--������
	//
	float Us;				//���ѹ
	float ILoad_Mag;		//���ɵ���
	float ILoad_Ang;		//���ɵ����Ƕ�(����ڶ�Ӧ��ĵ�ѹ, +Ϊ��ǰ)
	//
	int KL_Mode;			//��·�迹�����򲹳�ϵ�����÷�ʽ: 0--Kl, 1--KR,KX
	float KL_Mag;			//��·�迹�����򲹳�ϵ��(KL ��ʽ��Ч)
	float KL_Ang;
	float KL_KR;			//��·�迹�����򲹳�ϵ��(KR,KX ��ʽ��Ч)
	float KL_KX;
	//
	FaultCalcResult_Shot Result;
};

//�����: ���� Id,Ir �����������ӵ��� Iabc,Ixyz
struct FaultCalc_Diff
{
	int TestItem;			//������Ŀ���� FaultEnum_Diff_TestItem
	int FaultType;			//�������: �� FaultEnum_Diff_FaultType, 012--ABC,  345--AB,BC,CA;  6--ABC
	float Ir;				//�����õ� (Ir, Id), (Id, Harm), (Id, GapAng)
	float Id;
	float Harm;				//г������: �ٷֱ�, �� 0.2(�� 20%)
	int Harm_Num;			//г������
	int Harm_Pos;			//г��ʩ�Ӳ�: 0--I1��, 1--I2��;
	float GapAng;			//��Ͻ�: ��
	int GapAng_Pos;			//��Ͻ�ʩ�Ӳ�: 0--I1��, 1--I2��;
	//
	int IdEquation;		//Id ��������������: 0,12,34; �� FaultEnum_Diff_IdEquation
	int IrEquation;		//Ir �ƶ�����������: ..., �� FaultEnum_Diff_IrEquation
	float K;
	float KP1;			//I1, I2���CT��Ȳ���ϵ��(������Գ�״̬����)	
	float KP2;
	float I1_Ang;
	float I2_Ang;		//�����ǵ�12�������׼��λ;
	//
	//�������²���, ��� FaultType ����ʵ��ʹ�õ� K1, K2 ����ϵ��, �� I1,I2 �Ƕ�
	//
	int ProtSort;			//��������: �� FaultEnum_ProtSort
	int TransWindType;		//��ѹ��������: �� FaultEnum_TransWindType
	int TransGroupMode;		//��ѹ���������: �� FaultEnum_TransGroupMode_TwoWindings, ThreeWindings
	int AdoptWind;			//�������������: �� FaultEnum_AdoptWind 
	int PhaseCompMode;		//�����ڲ���λУ����ʽ: �� FaultEnum_PhaseCompMode
	int Y0CompMode;			//�����ڲ�����������ʽ: 0--��У��; 1-- Y ���� I0 У��
	//
	FaultCalcResult_Diff Result;
};

//�����: �����
struct FaultCalc_Diff_Shot
{
	//��ѹ������(��������), ����ȷ����ѹ���ӵ� m_nClock
	int ProtSort;			//��������: �� FaultEnum_ProtSort
	int TransWindType;		//��ѹ��������: �� FaultEnum_TransWindType
	int TransGroupMode;		//��ѹ���������: �� FaultEnum_TransGroupMode_TwoWindings, ThreeWindings
	int AdoptWind;			//�������������: �� FaultEnum_AdoptWind 
	//
	int I1_bY0;			//1--Y0; 0--Y,d
	int I2_bY0;	
	int PowerPos;		//��Դλ��: 0--I1��, 1--I2��;
	int FaultPos;		//���ϵ�λ��: 0--I1��,     1--I2��
	int FaultArea;		//            0--���ڹ���; 1--�������
	int FaultType;		//��������: �� FaultEnum_Diff_FaultType, 012--ABC,  345--AB,BC,CA;  6--ABC
	float FaultIp;		//���ϵ���: CT ���β�ֵ
	int DirectionMode;	//��������������: 0--Ԫ���ڲ�����Ϊ��;  1--Ԫ���ⲿ����Ϊ��
	//
	FaultCalcResult_Diff Result;	//ֻ��Ҫ���е� 6 ·��������
};

//�����: ���� 6 ·����, �������������
struct FaultCalc_Diff_IrId
{
	FaultStruct_Phase I1[3];	//I1: ABC
	FaultStruct_Phase I2[3];	//I2: abc
	//
	int IdEquation;		//Id ��������������: 0,12,34; �� FaultEnum_Diff_IdEquation
	int IrEquation;		//Ir �ƶ�����������: ..., �� FaultEnum_Diff_IrEquation
	float K;
	float KP1;				//I1, I2���CT��Ȳ���ϵ��(������Գ�״̬����)	
	float KP2;
	//
	//��ѹ������(��������), ����ȷ����ѹ���ӵ� m_nClock
	int ProtSort;			//��������: �� FaultEnum_ProtSort
	int TransWindType;		//��ѹ��������: �� FaultEnum_TransWindType
	int TransGroupMode;		//��ѹ���������: �� FaultEnum_TransGroupMode_TwoWindings, ThreeWindings
	int AdoptWind;			//�������������: �� FaultEnum_AdoptWind 
	//
	int PhaseCompMode;		//�����ڲ���λУ����ʽ: �� FaultEnum_PhaseCompMode
	int Y0CompMode;			//�����ڲ�����������ʽ: 0--��У��; 1-- Y ���� I0 У��
	//
	FaultCalcResult_Diff_IrId Result;	
};

//�����: ����ϵ�� KPH,M,L ��������(����Գ�)
struct FaultCalc_Diff_KP
{
	//��������
	int ProtSort;			//��������: �� FaultEnum_ProtSort
	//����ģʽ
	int CalcuMode;			//��������ϵ�����㷽ʽ: 0--���ݶ��ѹ��CT��ȹ�������ѹ��
	//                      1--���ݶ����In'��������ѹ��
	//                      2--��ôֵ����(RCS-978, �����In'�ĵ���)
	float Sn;			//��ѹ�������(��׼)
	float Un[3];		//��ѹ��������ѹ(012--���е�)
	float CT[3];		//��ѹ������ CT ���;
	float In[3];		//��ѹ����������(�������� CT �Ķ��β�)
	//������
	FaultCalcResult_Diff_KP Result;
};

//�����: ���� Id,Ir �����������ӵ��� Iabc,Ixy
struct FaultCalc_Diff5
{
	int TestItem;			//������Ŀ���� FaultEnum_Diff_TestItem
	int FaultType;			//�������: �� FaultEnum_Diff_FaultType, 012--ABC,  345--AB,BC,CA;  6--ABC
	float Ir;				//�����õ� (Ir, Id), (Id, Harm), (Id, GapAng)
	float Id;
	float Harm;				//г������: �ٷֱ�, �� 0.2(�� 20%)
	int Harm_Num;			//г������
	int Harm_Pos;			//г��ʩ�Ӳ�: 0--I1��, 1--I2��;
	float GapAng;			//��Ͻ�: ��
	int GapAng_Pos;			//��Ͻ�ʩ�Ӳ�: 0--I1��, 1--I2��;
	//
	int IdEquation;		//Id ��������������: 0,12,34; �� FaultEnum_Diff5_IdEquation
	int IrEquation;		//Ir �ƶ�����������: ..., �� FaultEnum_Diff5_IrEquation
	float K;
	float KP1;			//I1, I2���CT��Ȳ���ϵ��(������Գ�״̬����)	
	float KP2;
	float I1_Ang;
	float I2_Ang;		//�����ǵ�12�������׼��λ;
	//
	//�������²���, ��� FaultType ����ʵ��ʹ�õ� K1, K2 ����ϵ��, �� I1,I2 �Ƕ�
	//
	int ProtSort;			//��������: �� FaultEnum_ProtSort
	int TransWindType;		//��ѹ��������: �� FaultEnum_TransWindType
	int TransGroupMode;		//��ѹ���������: �� FaultEnum_TransGroupMode_TwoWindings, ThreeWindings
	int AdoptWind;			//�������������: �� FaultEnum_AdoptWind 
	int PhaseCompMode;		//�����ڲ���λУ����ʽ: �� FaultEnum_PhaseCompMode
	int Y0CompMode;			//�����ڲ�����������ʽ: 0--��У��; 1-- Y ���� I0 У��
	//
	FaultCalcResult_Diff Result;
};

//������: ��ǰ���������, ������װ�� K ��ĵ�ѹ������Чֵ
struct FaultCalc_Osc
{
};
//������: ��ǰ���������, ������װ�� K ��Ĳ����迹
struct FaultCalc_Osc_Zk
{
};

#endif
