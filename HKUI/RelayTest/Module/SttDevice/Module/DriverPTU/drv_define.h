#ifndef _DRV_DEFINE_H__
#define _DRV_DEFINE_H__

#define CHANNEL_A     0
#define CHANNEL_B     1
#define CHANNEL_C     2

#define DrvPos_Ang    0
#define DrvPos_Fre    1
#define DrvPos_Amp    2

#define TmtPos_Amp    0
#define TmtPos_Ang    1
#define TmtPos_Fre    2

#define TMT_UA_POS    0
#define TMT_UB_POS    1
#define TMT_UC_POS    2
#define TMT_UA2_POS   3
#define TMT_UB2_POS   4
#define TMT_UC2_POS   5

#define TMT_IA_POS    0
#define TMT_IB_POS    1
#define TMT_IC_POS    2
#define TMT_IA2_POS   3
#define TMT_IB2_POS   4
#define TMT_IC2_POS   5

//��
#define NANOSECOND             1.0e9
#define SHAKE_ALG_PARA_CNT        24//6+6*3
#define SHAKE_DIG_PARA_CNT        75
#define SHAKE_MAX               5000


#define GRADIENT_AMP      0
#define GRADIENT_ANG      1
#define GRADIENT_FRE      2

#define GRADIENT_UA               0
#define GRADIENT_UB               1
#define GRADIENT_UC               2
#define GRADIENT_UABC             3
#define GRADIENT_IA               4
#define GRADIENT_IB               5
#define GRADIENT_IC               6
#define GRADIENT_IABC             7
#define GRADIENT_UA2              8
#define GRADIENT_UB2              9
#define GRADIENT_UC2             10
#define GRADIENT_UABC2           11
#define GRADIENT_IA2             12
#define GRADIENT_IB2             13
#define GRADIENT_IC2             14
#define GRADIENT_IABC2           15
#define GRADIENT_UABC_UABC2      16
#define GRADIENT_IABC_IABC2      17
#define GRADIENT_UABC_IABC_1     18
#define GRADIENT_UABC_IABC_2     19
#define GRADIENT_UAB             20
#define GRADIENT_UBC             21
#define GRADIENT_UCA             22
#define GRADIENT_UAB2            23
#define GRADIENT_UBC2            24
#define GRADIENT_UCA2            25
#define GRADIENT_IAB             26
#define GRADIENT_IBC             27
#define GRADIENT_ICA             28
#define GRADIENT_IAB2            29
#define GRADIENT_IBC2            30
#define GRADIENT_ICA2            31

#define GRADIENT_RESULT_START	         1
#define GRADIENT_RESULT_STOP	         2
#define GRADIENT_RESULT_CHANGE	         3
#define GRADIENT_RESULT_DI_CHANGE	     4
#define GRADIENT_RESULT_RETURN	         5
#define GRADIENT_RESULT_GO_FAULT	     6
#define GRADIENT_RESULT_SHAKE	         7
#define GRADIENT_RESULT_SHAKE_FAULT	     8


//״̬���
#define STATE_RAMP_TYPE_NULL         0
#define STATE_RAMP_TYPE_SLIP_VAL     1
#define STATE_RAMP_TYPE_SLIP_FRE     2
#define STATE_RAMP_TYPE_NORMAL       3

#define STATE_RESULT_START                 1
#define STATE_RESULT_STOP                  2
#define STATE_RESULT_CHANGE                3
#define STATE_RESULT_DI_CHANGE             4
#define STATE_RESULT_GRADIENT              5
#define STATE_RESULT_GOOSE_CHANGED         6
#define STATE_RESULT_GRADIENTVALUE         7
#define STATE_RESULT_BOCHANGED             8
#define STATE_RESULT_GRADIENTEND          10


//״̬���д�������
#define State_Trig_Manual          0x001
#define State_Trig_Bin             0x002
#define State_Trig_TimeDelay       0x100
#define State_Trig_GPS             0x200
#define State_Trig_Bin_TimeDelay   0x102
#define State_Trig_GPS_TimeDelay   0x202

/***PTUͨ��ӳ��ο�
int g_nVChannel[6] = {4,5,0,1,3,2};
int g_nIChannel[6] = {3,5,0,2,1,4};
***/

//��Ӧ���type
#define PTU_Result_Type_TestStart       1//��ʼʵ��
#define PTU_Result_Type_TestFinish      2//ʵ�����
#define PTU_Result_Type_ANALG_CHANGE    3
#define PTU_Result_Type_DIG_CHANGE      4
#define PTU_Result_Type_DO_CHANGE       5
#define PTU_Result_Type_DI_CHANGE       6
#define PTU_Result_Type_StateChange     7//״̬�л�

//typedef struct{
//	unsigned int rms[8][2];		//�ɼ���Чֵ8·��ÿ·2��32λֵ
//	unsigned int inst[8];			//˲ʱֵ8·��ÿ·1��32λֵ
//	long dc[3];					//ֱ����ѹ���������Ʋ�
//	unsigned int sec;
//	unsigned int nsec;
//}Drv_SysInfo;

typedef struct{
	unsigned int module;							//ģ���ţ�0����ѹ	1������
	long dat[1500];			//���ݣ����ݸ�ʽ��PN466A��ͬ
}structAnalogPara;

typedef struct{
	unsigned int moduleCount;				//ģ������
	unsigned int sample;						//�������ʣ�sample = 40000/F, FΪ����Ƶ��
	unsigned int waveCount[8]; 				//ÿ��ģ��ÿ��ͨ������θ�����ͬPN466A
	structAnalogPara stAlg[8];				//ģ�����ݽṹ
}structACPara;

typedef struct{
	unsigned int type;					//���ͣ���PN466A
	unsigned int step;					//ָʾ״̬���еĵڼ���״̬���ֶ�ʵ����0
	unsigned int source;					//״̬���д���ֵ��0���ֶ�������1��ʱ�䴥�� 2��GPS����3������������
	unsigned int sec;						//UTC sec
	unsigned int nSec;					//UTC nSec
	unsigned int biValue;					//��������ֵ
	unsigned int boValue;
}structResultItem;

typedef struct{
	unsigned int cnt;
	structResultItem result[1000];
}structResult;						//���ؽ��

//~~~~~~~~~~~~~~~~~~~~~~~~~~~` state
typedef struct{
	unsigned int ref;			//0:��ת	1:�ߵ�ƽ	2:�͵�ƽ
	unsigned int logic;		//0:�봥��	1:�򴥷�
	unsigned int valid;		//bit9~bit0��Ӧ����10������1
}structBITrip;

typedef struct{
	unsigned int sec;						//GPS��ֵ
	unsigned int nSec;					//GPS����ֵ
	unsigned int reserve;					//����
}structGPSTrip;

typedef struct{
	unsigned int mSec;					//ʱ�䴥������ֵ
	unsigned int reserve[2];				//����
}structTmTrip;

typedef struct{
	unsigned int module;			//ģ����
	unsigned int cnt;
	long dat[12+12*3];				//ģ������6��ͨ��ֱ��ֵ������ͨ����λ����ֵ��Ƶ��
}structStateAnalog;
typedef struct{
	unsigned int state;			//״̬��
	unsigned int trip;				//��������	0���ֶ�1��ʱ��2��GPS	3:	������
	union {						//���������������������ṹ��
		structBITrip	bi;
		structGPSTrip 	gps;
		structTmTrip	tm;
	}tripData;
	unsigned int mdelay;			//���봥������ʱʱ����ʱʱ�����ֵ
	unsigned int BO;				//������ֵ
	structStateAnalog dat[8];		//ģ������
}structState;
typedef struct{
	unsigned int stateCount;			//״̬��
	unsigned int moduleCount;		//ģ����
	unsigned int isLoop;				//�Ƿ�ѭ��
	structState state[500];
}structStateParam;
#endif // _DRV_DEFINE_H__

