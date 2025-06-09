//----------------------------------------------------------------------
//Fault�ڲ�ʹ�õĹ����ṹ�嶨��, �����ڲ�ʹ��, �� XML ����������ݴ��� 
//
//��������Ҫ���õ� enum �� FaultDef_Enum.h
//               define �� FaultDef.h
//
//----------------------------------------------------------------------
//1. ��������: 
//   FaultStruct_ ...     -- �ڲ�ʹ�õĹ����ṹ��
//   FaultTest_ ...       -- ������������ṹ��
//   FaultCalc_ ...       -- ������������ṹ��
//   FaultResult_...      -- ����ṹ��(���Խ��)
//   FaultCalcResult_...  -- ����ṹ��(������)
//----------------------------------------------------------------------
//2. �ڲ�ʹ�õĹ����ṹ��
//   FaultStruct_Phase    -- ����(��ֵ,�Ƕ�)
//   FaultStruec_UI       -- UIģ����ͨ��(�Ƿ�ֱ��,��ֵ,�Ƕ�,Ƶ��)
//   FaultStruct_GPS      -- GPS ����

//----------------------------------------------------------------------
#if !defined(_FaultDEF_STRUCT)
#define _FaultDEF_STRUCT

#include "FaultDef.h"
//----------------------------------------------------------------------
#define MAX_VOLT_NUMBER MAX_CHANNEL_COUNT 	// 16 ·��ѹ, 16 ·����
#define MAX_CURR_NUMBER MAX_CHANNEL_COUNT 
#define MAX_BIN_NUMBER  MAX_IO_COUNT 	    // 16 ·����, 16 ·����
#define MAX_BOUT_NUMBER MAX_IO_COUNT 

#define MAX_HARM_NUMBER 50			//г������: ���г������
#define MAX_STATE_NUMBER 50			//״̬����: ���������50��״̬
#define MAX_TRIP_NUMBER 4			//��������: ���������բ����
#define MAX_nStates_NUMBERS 20		//���λط�: ��������¼�Ŀ���ӵ�״̬��ת�Ĵ���


//----------------------------------------------------------------------
struct FaultStruct_LinkInfo	//Fault ������Ϣ
{
	UINT32		PcIP;		//PC��IP
	UINT32		DevIP;		//�豸IP: 0xFFFFFFFF Ϊ�㲥
	UINT16		PcPort;		//PC��Port
	UINT16		DevPort;	//�豸Port
};

struct FaultStruct_Phase	//��ֵ,�Ƕ�
{
	float Mag;	
	float Ang;	
};
struct FaultStruct_UI		//��ֵ,�Ƕ�,Ƶ��,�Ƿ�ֱ��
{
	int bDC;
	float Mag;	
	float Ang;	
	float Fre;
};
struct FaultStruct_GPS		//GPS����
{
	int GpsPos;		//0--����GPS, 1--��� GPS(������), 2--��� GPS(PC��)
	int BaudRate;	//BaudRate=9600;  GPS���� COM �Ĳ�����
	int Parity;		//Parity=0;       0--��У��, 1--��У��, 2--żУ��
	int StopBits;	//StopBits=1;     ֹͣλ, 1, �� 2;
	int DataBits;	//DataBits=8;     ����λ, 7, �� 8;
	int nComNo;		//GPS ���ڵĴ��ں�, 1--COM1, 2--COM2, (��� GPS �� PC ��ʱ��Ч)
};
struct FaultStruct_BinTime	//����������ʱ�䶨��
{
	float Bin[MAX_BIN_NUMBER];
};
typedef struct FaultStruct_BinTime FaultStruct_Bin;

//----------------------------------------------------------------------
//г������
struct FaultStruct_HarmUI   //��n��г��: ��ֵ,�Ƕ�,�Ƿ�ѡ�����
{
	int bSelect;
	float Mag;
	float Ang;
};
struct FaultStruct_HarmSet	//ÿһ�� ui ͨ����г������
{
	FaultStruct_HarmUI Harm[MAX_HARM_NUMBER+1];		//ֱ��+20��г��
};
struct FaultStruct_InterHarmSet
{
	int bSelect;
	float Mag;
	float Ang;
	float Fre;
};
//----------------------------------------------------------------------
//ʱ�����
struct FaultStruct_TimerSet	//ÿһ��״̬�Ĳ���
{
	//��״̬������ĵ�ѹ����
	FaultStruct_UI Up[MAX_VOLT_NUMBER];		//��ֵ, �Ƕ�, Ƶ��, �Ƿ�ֱ��
	FaultStruct_UI Ip[MAX_CURR_NUMBER];
};
//----------------------------------------------------------------------
//״̬����
struct FaultStruct_StateUI	//ÿһ�� ui ͨ���Ĳ���
{
	float Mag;  float Ang;  float Fre;  int bDC;
	int bDMag;  float dMag_dt;  float EndMag;
	int bDFre;  float dFre_dt;  float EndFre;
};
struct FaultStruct_StateSet	//ÿһ��״̬�Ĳ���
{
	//��״̬������ĵ�ѹ����
	FaultStruct_StateUI Up[MAX_VOLT_NUMBER];
	FaultStruct_StateUI Ip[MAX_CURR_NUMBER];
	//��״̬�µĿ������������
	int OutputState[MAX_BOUT_NUMBER];
	float OutputDelayTime[MAX_BOUT_NUMBER];
	//��״̬��������
	int EndMode;			//��������: 0--��������; 
							//			1--ʱ�䴥��; 
							//			2--GPS�����崥��;  
							//			3--����ӵ㴥��; 
							//			4--��ֵ����; 
							//			5--Ƶ�ʴ���;
							//          6--����ӵ㴥�� + �����ʱ;
	float EndDelayTime;		//�������������, ������һ����ʱ����������
	float MaxLastTime;		//1,6--ʱ�䴥����Ч
	int GPSPos;				//2--GPS����: 0--�Ӳ�����,����GPS; 1--�Ӳ�����,����GPS; 2--�� PC ��, ����GPS(����c,r�ֱ�ΪPPS,PPM);
	int bAndOr;				//3,6--����ӵ㴥����Ч
	int bBinSelect[MAX_BIN_NUMBER];	
	int Mag_nGroup;		//4--��ֵ������Ч: ��ֵ���, 0--���ѹ, 1--�����, ...
	int Mag_nIndex; 	//                 ����������: 012, 345, ...	
	float Mag_Value;	//                 ����ֵ
	int Fre_nGroup;		//5--Ƶ�ʴ�����Ч: Ƶ�����, 0--���ѹ, 1--�����, ...
	int Fre_nIndex; 	//                 ����������: 012, 345, ...	
	float Fre_Value;	//				   ����ֵ
};
//----------------------------------------------------------------------
//���λط�
struct FaultStruct_WPChannel	//ͨ������
{
	int ChIndex;		//Uabcxyz,Iabcxyz�������е�ͨ��������(-1�޹���,0123...)
	float Factor;		//������������(���� PT/CT ���, ԭʼ¼������/���������)
};
struct FaultStruct_WPSection	//�ظ����䶨��
{
	int bSelect;
	float TimeFrom;		//ms, ���
	float TimeLength;	//ms, ���䳤��
	int RepeatNumbers;	//���������
};

//----------------------------------------------------------------------
//��������״̬����--�������г��(ÿͨ��1��г������),
struct FaultStruct_SzNari_UI
{
	float TimeStart;
	float Mag;   float Ang; 
	float Harm_Mag;   float Harm_Ang;   float Harm_Fre;
};
struct FaultStruct_SzNari_Bout
{
	float TimeStart;
	int nState;
};
struct FaultStruct_SzNari_State
{
	FaultStruct_SzNari_UI Up[MAX_VOLT_NUMBER];
	FaultStruct_SzNari_UI Ip[MAX_CURR_NUMBER];
	FaultStruct_SzNari_Bout Bout[MAX_BOUT_NUMBER];
};
//----------------------------------------------------------------------
//���뿪��װ��: SOE ����(����)
struct FaultStruct_IO_SOE_BoutSet
{
	int bSelect;			//ѡ���־
	int Bout_0;				//��ʼ״̬
	float Bout_DelayTime;	//��ת��ʱ(����ת����ʱ��): s
	float Bout_KeepTime;	//��ת�󱣳�ʱ��(��������): s
	int Bout_TripNumbers;	//��ת����
};
//----------------------------------------------------------------------
//���뿪��װ��: ״̬����
struct FaultStruct_StateSet_IO	//ÿһ��״̬�Ĳ���
{
	//��״̬�µĿ������������: 
	int Bout_State[MAX_IO_COUNT_EX];		//0--�Ͽ�, 1--�պ�
	float Bout_DelayTime[MAX_IO_COUNT_EX];	//��ʱ
	//��״̬��������
	int EndMode;			//��������: 0--��������; 
							//			1--ʱ�䴥��; 
							//			2--GPS�����崥��;  
	float EndDelayTime;		//�������������, ������һ����ʱ����������
	float MaxLastTime;		//1,6--ʱ�䴥����Ч
	int GPSPos;				//2--GPS����: 0--�Ӳ�����,����GPS; 1--�Ӳ�����,����GPS; 2--�� PC ��, ����GPS(����c,r�ֱ�ΪPPS,PPM);
};


#endif
