#ifndef _DRV_DEFINE_H__
#define _DRV_DEFINE_H__

#define STATECOUNT              250
#define CHANELMAXCHANGED        256
#define STATE_RESULT_MAX        250

//zhoulei 2020-10-04
#define ALG_MODULE_MAX		12
#define BIO_MODULE_MAX		5
#define ALG_PARAM_MAX		3441
#define MODULE_MAX	              8    //ģ����
#define DIGITAL_MODULE_MAX	      4	//�����
#define MAX_DIGITAL_GROUP_NUM     4
#define DATA_MAX               1536
#define CHANNEL_MAX               6    //volt\currentͨ����

#define SYS_INFO_COUNT           11
#define STATERESULTMAX         1000
#define GOOSE_CHANGE_POS_MAX    256
#define CHARPARALeng            256
#define DIGITAL_CHANNEL_MAX      37
#define HARMONIC_MAX             31//��г������

#define SMV_MAX           8
#define GOOSE_MAX        16
#define FT3_MAX          12
#define GOOSESUB_MAX     32

//�ݱ����
#define GRADIENT_MAX_COUNT			3000// ���ݱ����
#define GRADIENT_SMV_PARA_CNT	    111 //(37*3)
#define GRADIENT_ALG_PARA_CNT	    24 //6+6*3
#define GRADIENT_PARAM_MAX		    74 //(37*2)

//ModuleType
#define VOLT             1
#define CURRENT          2
#define DIGITAL          3
#define DCCURRENT        4
#define DCVOLT           5
#define SWITCH           6

union ConverStruct {
		unsigned char b[4];
		unsigned long l;
		float f;
};//4���ֽڣ����ù����壬����ת��

typedef struct{
   unsigned int flag;
   unsigned int version[10];
}Drv_BoardVersion;

typedef struct{
	unsigned int dat[SYS_INFO_COUNT];
}Drv_FeedBack;

typedef struct{
	unsigned int tmFlag;        //bit; 0 GPS   1 BCode
	unsigned int tm_h;          //��
	unsigned int tm_l;          //����
	Drv_FeedBack stBack[8<<1]/*MODULE_MAX]*/;//module 8 1,2,4,8,16,32,64,128
}Drv_SysInfo;

//DAPara Send to Driver
typedef struct{
	unsigned long nmodule[4];
	unsigned long nvolt[4];
}DeviceDAPara;

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

typedef struct{
unsigned int nAlgCnt;			//ģ���SMVģ������
unsigned int nAlgTable[ALG_MODULE_MAX];
unsigned int nBiCnt;			//����ģ������
unsigned int nBiTable[BIO_MODULE_MAX];
unsigned int nBoCnt;				//����ģ������
unsigned int nBoTable[BIO_MODULE_MAX];
}Drv_ModulePara;


//
//
//������ģ�����ݽṹ
typedef struct{
	unsigned int nVal1;
	unsigned int nVal2;		//������ֵ
}structBIStatusItem;

//���������ݶ������ݽṹ
typedef struct{
		structBIStatusItem	item[BIO_MODULE_MAX];		//��������
}Drv_BIStatus;

//����ֵ���ݽṹ
typedef struct{
	unsigned int nVal1;
	unsigned int nVal2;		//����ֵ
}structBoStatusItem;


//�������������ݽṹ
typedef struct{
	structBoStatusItem item[BIO_MODULE_MAX];
}structBoStatus;

typedef struct{
	unsigned int nVal1;
	unsigned int nVal2;		//����ֵ
}structBIChangeItem;

//�����λ���ݽṹ
typedef struct{
structBIChangeItem item[BIO_MODULE_MAX];
}structBIChange;

typedef struct{
	unsigned int 	nStep;			//״̬����״̬��ţ���״̬�������ģ��ʹ��
	unsigned int 	nDegressStep;		//�ݱ䲽���ţ��ݱ�ģ���״̬���еĵݱ䶼ʹ�ø�����ָʾ
	unsigned int 	nType;			//������ͣ������3-1
	unsigned int 	nSource;			//����Դ�������3-2
	unsigned int 	nSec;				//UTCʱ����ֵ
	unsigned int 	nNanoSec;			//UTCʱ������ֵ
	structBIChange 	oBiChg;			//�����λֵ����sourceΪ�����λʱ����ֵ
	Drv_BIStatus	nBi;				//������ֵ
	structBoStatus	nBo;				//������ֵ
}Drv_ResultItem;

typedef struct{
	Drv_ResultItem oItem[100];
}Drv_Results;

//ģ�����ݺ����Ҳ����ṹ
typedef struct{
	unsigned int nDWcnt;			//��Ч���ݸ�������32λΪ��λ
	long dat[ALG_PARAM_MAX];	//ģ������Ҳ�������
}Drv_HarmParam;
//������ģ�����ݽṹ
typedef struct{
	unsigned int dat[2]; //�������ݣ���λȡ�����64��
}Drv_BIOParam;
//�ֶ�ʵ�����ݶ���ṹ
typedef struct{
	Drv_HarmParam	oDrv_HarmParam[ALG_MODULE_MAX];
	Drv_BIOParam	oDrv_BIOParam[BIO_MODULE_MAX];
}Drv_ManuData;

//������ת���ݽṹ
typedef struct{
	structBoStatus boStatus;		//��������ʼ״̬
	structBoStatus flipValid;			//��������ת��Чλ
	unsigned int 	nTrip;			//0:ʱ�䴥��		1�����봥��
	unsigned int 	nTripDelay;		//ʱ�䴥��ʱ����ʱ�䣬��λ����
	unsigned int 	nHoldDelay;		//ʱ�䴥��ʱ����ʱ�䣬��λ����
}structBoFlip;

//���ò�������ṹ
typedef struct{
	unsigned int nStateCount;			//״̬����
	unsigned int nIsLoop;				//�Ƿ�ѭ��
	unsigned int nbiRef;				//0���������Ե�һ̬Ϊ�ο�1������һ̬Ϊ�ο�
	Drv_BIStatus oGooseInit;			//goose�����ʼֵ
	structBoFlip 	oBo;					//��������
}Drv_StatePara;



//״̬����״̬����
//GPS��ʱ�������嶨��
typedef struct{
	unsigned int nSec;			//GPS������ֵ
	unsigned int nNsec;			//GPS��������ֵ
}structGPS;
typedef struct{
	unsigned int nMsec;				//ʱ�䴥������ֵ
	unsigned int nDelay;			//���봥����ʱʱ��
}structTime;
typedef union{
	structGPS	oGps;				//GPS����
	structTime	oTime;				//ʱ�䴥��
}unionTm;

//״̬����������ݽṹ
typedef struct{
	unsigned int 	DWCount;			//��Ч���ݳ���
	unsigned int    nPhase;
	long    sss[13];
	long	nVal[2*37*3];		//�������
}structACParamItem;
typedef struct{
	structACParamItem item[ALG_MODULE_MAX];
}structACPara;
//״̬���еݱ����ݽṹ
typedef struct{
	unsigned int 	nIsChange;			//0:���ݱ�			1���ݱ�
	unsigned int    nOffset;            //����ģ��Ϊ0��	ģ��ģ��Ϊ6
	unsigned int 	nAmpCount;				//��ֵ�ݱ����
	unsigned int 	nFreCount;				//Ƶ�ʵݱ����
	unsigned int 	nDWCount;			//��Ч���ݸ���
	long 	changeVal[2*37*2];		//�ݱ�ֵ�����˵��
	long	lastVal[2*37*2];			//��ֵֹ�����˵��
}structChangeNew;
//������Чλ���ݽṹ
typedef struct
{
	unsigned int nModule;
	unsigned int nVal1;
	unsigned int nVal2;		//��Чλ��ֵ
}structBIValidItem;
typedef struct{
	unsigned int nModuleCount;
	structBIValidItem item[BIO_MODULE_MAX];
}structBIValid;
//���봥�����ݽṹ
typedef struct{
	unsigned int nBiRef;			//0:��ת����	 1���½��ش���	2�������ش���
	unsigned int nBiLogic;		//0��������	1�������
	structBIValid oValid;			//��Чͨ��
}structBITrip;

typedef struct googsechanelChanged{
	unsigned int nPos;
	unsigned int nCount;
	unsigned char dat[20];
	googsechanelChanged()
	{
		nPos = 0;
		nCount = 0;
	}
}GOOGSECHANELCHANGED;

typedef struct datConfigChanged{
	unsigned int count;				//���ݸ���
	unsigned int group;				//��������
	googsechanelChanged dat[CHANELMAXCHANGED];

	unsigned int nUTCChanelCount;     //���Ϊ0,���ô�ʱ��
	unsigned int UTCChanelPos[CHANELMAXCHANGED];  //��Ҫ��ʱ���λ��
	datConfigChanged()
	{
		count = 0;
		group = 0;
		nUTCChanelCount = 0;
	}
}DATCONFIGCHANGED;

typedef struct{
	unsigned int module;			//ģ����
	unsigned int group;				//�����ܺ�
	datConfigChanged dat[16];				//������Ϣ�����SV/GOOSE������Ϣ
}datConfigChangedItems;

typedef struct{
	unsigned int nModuleCount;    //ģ����
	datConfigChangedItems datModules[4];
}stateGooseChangedItem;         //״̬����ÿ��״̬Ԥ���GOOSE��λ����

typedef struct{
	unsigned int group;
	unsigned int nLen;
	unsigned char dat[1024];
}structFt3Send;

typedef struct{
	unsigned int module;
	unsigned int groupCnt;
	structFt3Send ft3[12];
}structFt3DataConfigItems;

typedef struct{
	unsigned int nModuleCount;
	structFt3DataConfigItems datModules[4];
}structStateFt3Item;

typedef struct
{
	unsigned int pos;
	unsigned int value;
	unsigned int gorup;
}structGSTestMdUnit;
typedef struct
{
	unsigned int module;
	unsigned int nCount;
	structGSTestMdUnit gs[16];
}structGSTestData;
typedef struct
{
	unsigned int nCount;
	structGSTestData dat[DIGITAL_MODULE_MAX];
}structGooseTest;

//˵����״̬���еݱ����ͬʱ�仯Ƶ�ʺͷ�ֵ��changVal��lastVal��������˳��Ϊ��
//ģ��ģ�飺6ֱ������+��Ƶ��+��ֵ��*��DWCount-6����
//SMVģ�飺��Ƶ��+��ֵ��*DWCount;
typedef struct{
	unsigned int	nStateNum;			//״̬���
	unsigned int	nTirpType;			//����Դ���ã�����5-1
	structBITrip	obiTrip;				//���봥������
	unionTm         oTm;					//ʱ���GPS�����������
	unsigned int	nChangemSec;		//״̬���еݱ�ʱ��ֶȣ���λ����
	structBoFlip	oStBo;				//��������
	structChangeNew 	oStChange[ALG_MODULE_MAX];		//״̬���еݱ����
	structACPara 	oAcParam;			//ģ���������
	stateGooseChangedItem GooseChangedItem;			//goose��λ��Ϣ
	structStateFt3Item		ft3ChangedItem;
	structGooseTest GooseTest;
}Drv_StateItem;

typedef struct{
	unsigned int startType;       //0:no trip��ֱ�ӿ�ʼ��1:manu���ֶ����� 2:DI�����봥���� 3:GPS ��GPSʱ�䣩�� ���ǿ�ʼ���ŵĴ�������
	unsigned int startSec;        //gps start sec
	unsigned int startnSec;       //gps start nSec
	structBITrip stBIStart;				//���봥����ʼʱ����������
	unsigned int degressType;     //0 loop type 0x80000000 trip type //������ʽ 0�̶�ѭ������λ��������ѭ����������ѭ��  0x80000000 ��������ѭ��
	unsigned int tripType;        //1 manu(�ֶ�)2 bi(����) 3GPS(GPS) 4 time(��ʱ)
	structBITrip stBITrip;				//���봥������
	int tripLoopCount;	 //ѭ������
	int modeAfterTrip;
	unsigned int tripmDelay;		 //��ʱ����
	unsigned int tripgpsSec;      //GPS����
	unsigned int tripgpsnSec;
	unsigned int freq;           //����Ƶ��
	unsigned int moduleCount;	 //ģ������
	unsigned int module;	 //ģ��
}drv_structLtReplayParam;

#define COMTRADE_REPLAY_PKG_POINTS					600
#define LT_REPLAY_FRAME_PKG_CNT						3600
//������� ѭ�� A B �����С
#define LT_REPLAY_MAX_LOOP_PKG_CNT                  30
#define LT_REPLAY_MAX_A_PKG_CNT                     120
#define LT_REPLAY_MAX_B_PKG_CNT                     120
typedef struct{
	unsigned int	num;
	unsigned int 	module;
	unsigned int	title;
	unsigned int	length;
	unsigned int	cmd;
	long			data[LT_REPLAY_FRAME_PKG_CNT];
}Drv_BlockPkg;
typedef struct{
	unsigned int offset_loop;
	unsigned int offset_bufferA;
	unsigned int offset_bufferB;
	unsigned int loop_max_block; //30
	unsigned int loop_cur_block;
	unsigned int buffer_A_max_block; //120
	unsigned int buffer_A_curr_block;
	unsigned int buffer_A_flag;
	unsigned int buffer_B_max_block; // 120
	unsigned int buffer_B_curr_block;
	unsigned int buffer_B_flag;
	Drv_BlockPkg bufferLoop[LT_REPLAY_MAX_LOOP_PKG_CNT];
	Drv_BlockPkg bufferA[LT_REPLAY_MAX_A_PKG_CNT];
	Drv_BlockPkg bufferB[LT_REPLAY_MAX_B_PKG_CNT];

}drv_structLtBuffer;
#define LT_REPLAY_LOOP_BUFFER_FLAG 0x01
#define LT_REPLAY_BUFFERA_FLAG 0x02
#define LT_REPLAY_BUFFERB_FLAG 0x04
typedef struct LtReplayCoefItem{
	float fCoef;//��ֵϵ��
	float fZero;//������Ư
	float fMaxValue; // ֱ�����ֵ ��Чֵ*1.414
	int   nCh;
	float fReverse;// +1 -1
	LtReplayCoefItem()
	{
		fCoef = 1.0;
		fZero = 0;
		fMaxValue = 100;
		nCh = 0;
		fReverse = 1.0;
	}
}drv_LtReplayCoefItem;
typedef struct LtReplayCoef{
	LtReplayCoefItem Item[ALG_MODULE_MAX][CHANNEL_MAX];
}drv_LtReplayCoef;

typedef struct{
	unsigned int pos;
	unsigned int group;
	unsigned int module;
	unsigned char trueValue;
	unsigned char falseValue;
	unsigned int hasUTC;
	unsigned int utcPos;
}structBOMap;

typedef struct{
	unsigned int cnt;
	structBOMap stMap[16];
}structGSOutInfo;

typedef struct{
	structGSOutInfo info[2][32];
}structGSOutModule;

typedef struct{
	structGSOutModule boMd[BIO_MODULE_MAX];
}structGSOutMap;

typedef struct{
	unsigned int pos;
	unsigned int mdPos;
	unsigned int index;
	unsigned int trueValue;
	unsigned int falseValue;
}structGooseSubValue;

#define GOOSE_MAP_MAX					64
#define GOCB_LEN_MAX					256
#define GOID_LEN_MAX					GOCB_LEN_MAX
#define DATASET_LEN_MAX					GOCB_LEN_MAX

typedef struct
{
	int CRC;
	int paramAdvance;
	int gocbLen;
	char GOCB[GOCB_LEN_MAX];
	int goidLen;
	char GOID[GOID_LEN_MAX];
	int dataSetLen;
	char dataSet[DATASET_LEN_MAX];
	int testMode;
	int count;
	structGooseSubValue val[GOOSE_MAP_MAX];
}GooseSubItem;

typedef struct
{
	unsigned int nPort;//bit0-bit7 1 enabled 2 unenabled
	unsigned int ncount;
	GooseSubItem gooseSub[16];
}GooseSubData;

typedef struct{
	unsigned int init_time[8]; //��ʼʱ��
	unsigned int firstfliptime[8]; // ��һ�η�תʱ��
	unsigned int secondfliptime[8]; // �ڶ��η�תʱ��
	unsigned int flipcnt[8]; //��ת����
	unsigned int init_val[8]; //��ʼֵ
}Drv_SoeState;

typedef struct{
	unsigned int triptype; //0: �������� 1: GPS ����
	unsigned int sec;           //GPS s
	unsigned int nsec;          //GPS ns
	unsigned int holdtime;      //����ʱ�����ֵ
	Drv_SoeState soe;
}Drv_SOETest;

/******structDegUnit
		 xw   pl   fz
Ua1      0    1    2
Ub1      1*3  4    5
Uc1      2*3  7    8

Uz       3*3  10   11

Ua2      4*3  13   14
Ub2      5*3  16   17
Uc2      6*3  19   20
Ua3      7*3
Ub3      8*3
Uc3      9*3
Ua4      10*3
Ub4      11*3
Uc4      12*3

Ia1      13*3 40   41
Ib1      14*3 43   44
Ic1      15*3 46   47
Ia2      16*3 49   50
Ib2      17*3 52   53
Ic2      18*3 55   56
Ia3      19*3
Ib3      20*3
Ic3      21*3
Ia4      22*3
Ib4      23*3
Ic4      24*3 73   74

Ua5      25*3 76   77
Ub5      26*3 79   80
Uc5      27*3 82   83
Ua6      28*3 85   86
Ub6      29*3 88   89
Uc6      30*3 91   92

Ia5      31*3
Ib5      32*3
Ic5      33*3
Ia6      34*3
Ib6      35*3
Ic6      36*3
*****/
#endif // _DRV_DEFINE_H__

