#ifndef DRV_DEFINE
#define DRV_DEFINE

#include "tmt_state_test.h"
#include "../../SttDevice/RelayTest/drv_define.h"


typedef struct
{
	unsigned int pos;
	unsigned int value;
	unsigned int group;
}drv_gsetestdata;

typedef struct
{
	unsigned int module;
	unsigned int nCount;
	drv_gsetestdata gs[16];
}drv_gsetestitem;

typedef struct
{
	unsigned int nCount;
	drv_gsetestitem dat[DIGITAL_MODULE_MAX];
}drv_gsetestitems;

typedef struct
{
	unsigned int nBoValue;   //0 open   1 close; ������Чλ
	unsigned int nreverse;   //0 unreverse 1reverse 2 �Ƿ񿪳�״̬��ת
	unsigned int ntrigerMode; //0 time  1 biChanged;
	unsigned int ntimeDelay; //����״̬��ת����ʱ��
	unsigned int nHoldTime;
}drv_analogbosetting;

//�ݱ����
typedef struct
{                                                
	unsigned int nIsChange;					//�Ƿ�ݱ��־, 0:���ݱ�			1���ݱ�
	unsigned int nModule;					//ģ����
	unsigned int  nChangeCount;				//�仯���� ��ѹ�ݱ����
	unsigned int ndfcount;                  //Ƶ�ʵݱ����
    long nChangeValue[CHANNEL_MAX*3*2+CHANNEL_MAX];     	//�仯��  �²�׼���Ի�����ѡ���г����ֱ�������ݵݱ书��
	long nLastChangeValue[CHANNEL_MAX*3*2+CHANNEL_MAX];     	//���һ���仯��  �²�׼���Ի�����ѡ���г����ֱ�������ݵݱ书��
}drv_change;

typedef struct{
    unsigned int nIsChange;
    unsigned int nModule;
    unsigned int nChangeCount;
    unsigned int ndfcount;
    long		 nChangeValue[DIGITAL_CHANNEL_MAX * 3*2];
	long     nLastChangeValue[DIGITAL_CHANNEL_MAX * 3*2];     	//���һ���仯��
}drv_digitalchange;

//ģ����һ��г������������
typedef struct
{
	unsigned int nModule;						//ģ����
	//long nDc[CHANNEL_MAX];                      //ֱ������
	unsigned int nclsPhase;                               //��բ�Ƕ�
	unsigned int nexpconfig;                        //�����ڷ�������
	long nexp[6];                                         //�����ڷ���
    long nData[4*CHANNEL_MAX];//ֱ���ӻ�������
    long nHarmData[3*CHANNEL_MAX];                //г������(2~30��г��������һ��г������ֵ)
}drv_analogitem;

typedef struct
{
	drv_analogitem oModuledata[MODULE_MAX];
}drv_acanalogpara;

//������һ��г������������
typedef struct{
	unsigned int module;// ģ����
	unsigned int nclsPhase;        //��բ�Ƕ�
	unsigned int nexpconfig;                        //�����ڷ�������
	long nexp[12];                 //�����ڷ���
	unsigned int dat[DIGITAL_CHANNEL_MAX * 3];
	unsigned int hrmDat[DIGITAL_CHANNEL_MAX * 3];
}drv_sindataitem;

//DigitalPara
typedef struct
{
	//unsigned int nBO;
	drv_sindataitem oModuledata[DIGITAL_MODULE_MAX];
}drv_digitalpara;

typedef struct 
{
	unsigned int nPos;
	unsigned int nCount;
	unsigned char dat[20];
}drv_chanelchanged;

typedef struct 
{
	unsigned int count;				//���ݸ���
	unsigned int group;				//��������
	drv_chanelchanged dat[CHANELMAXCHANGED];
	unsigned int nUTCChanelCount;     //���Ϊ0,���ô�ʱ��
	unsigned int UTCChanelPos[CHANELMAXCHANGED];  //��Ҫ��ʱ���λ��
}drv_datchanged;

typedef struct
{
	unsigned int module;			//ģ����
	unsigned int group;				//�����ܺ�
	drv_datchanged dat[16];				//������Ϣ�����SV/GOOSE������Ϣ
}drv_gsechangeditem;

typedef struct
{
	unsigned int nModuleCount;    //ģ����
	drv_gsechangeditem datModules[4];//״̬����ÿ��״̬Ԥ���GOOSE��λ����
}drv_gsechangeditems;         

typedef struct
{
	unsigned int group;
	unsigned int nLen;
	unsigned char dat[1024];
}drv_f3send;

typedef struct
{
	unsigned int module;
	unsigned int groupCnt;
	drv_f3send ft3[12];
}drv_ft3dataconfigitem;

typedef struct
{
	unsigned int nModuleCount;
	drv_ft3dataconfigitem datModules[4];
}drv_StateFt3Items;

//״̬���в���
typedef struct
{
	unsigned long nStateNum;                                    //״̬������ţ�0��ʼ
	// 0 manual 1 time 2 gps 3 bin or 4 bin and
	unsigned long nTirpType[7];                                 //������������Ӧλ����д��Ҫ��ת����״̬
	unsigned long nReversal;                                    //���뷭ת�ο�����:
	//0�����뷭ת����wa
	//1�����������ش���
	//2�������½��ش���
	unsigned long nAndValid;                                    //�����봥����Чλѡ��bit9~bit0��Ӧͨ��9~ͨ��0
	unsigned long nOrValid;                                     //����򴥷���Чλѡ��bit9~bit0��Ӧͨ��9~ͨ��0

	unsigned long nParaTripLogic;                               //���������߼�
	unsigned long nTripPara;                              //GOOSE����򴥷���Чλѡ��bit31~bit0��Ӧͨ��31~ͨ��0

	unsigned long nGpsSec;                                      //GPS������ֵ
	unsigned long nGpsnSec;                                     //GPS��������ֵ
	unsigned long nTimemSec;                                    //ʱ�䴥������ֵ
	unsigned long nDelay;                                       //���봥����ʱʱ�䣬���������������ʱ�೤ʱ�䴥��
	unsigned long nChangemSec;                                  //��ʱ��ݱ�ʱ���ݱ�ʱ��ֶ�, ��λ����
	drv_analogbosetting oBo;
	drv_change stChange[MODULE_MAX];                          //�ݱ����
	drv_digitalchange stDigitalChange[DIGITAL_MODULE_MAX];
	drv_acanalogpara acAnalog;                          //ģ�����
	drv_digitalpara  Digital;			//���ֲ���
	drv_gsechangeditems GooseChangedItems;
	drv_StateFt3Items ft3ChangedItems;
	drv_gsetestitems GooseTestItems;
}drv_state;

//״̬���������ܲ���
typedef struct
{
	unsigned long nModuleCount;				//ģ��ģ��
	unsigned long nStateModuleCount;        //����ģ��
	unsigned int  nDcmodule;              //ֱ��ģ��
	unsigned long nStateCount;				//״̬����
	unsigned long nSequence;				//�Ƿ�Ϊ˳��״̬���У�1����		0������
	unsigned long nloop;
	unsigned long nReverRefence;                                //1 �ο���һ��״̬ 0�ο���һ��״̬
	unsigned long noriginal;                //GOOSE init Value;
	drv_analogbosetting oBo;
	drv_state stState[STATECOUNT];				//״̬
}drv_state_test;




#define ALG_MODULE_MAX		12
#define BIO_MODULE_MAX		5
#define ALG_PARAM_MAX		3441
#define BIO_MODULE_MAX		5

//������ģ�����ݽṹ
typedef struct{
	unsigned int nVal1;
	unsigned int nVal2;		//������ֵ
}structBIStatusItem;

//���������ݶ������ݽṹ
typedef struct{
		structBIStatusItem	item[BIO_MODULE_MAX];		//��������
}structBIStatus;

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
	structBIStatus oGooseInit;			//goose�����ʼֵ
	structBoFlip 	oBo;					//��������
}structStateParamNew;



typedef struct{
unsigned int nAlgCnt;			//ģ���SMVģ������
unsigned int nAlgTable[ALG_MODULE_MAX];
unsigned int nbIntCnt;			//����ģ������
unsigned int nbITable[BIO_MODULE_MAX];
unsigned int nBoCnt;				//����ģ������
unsigned int nBoTable[BIO_MODULE_MAX];
}structModuleParam;

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
	unsigned int    sss[13];
	unsigned int	nVal[2*37*3];		//�������
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
	unsigned int 	changeVal[2*37*2];		//�ݱ�ֵ�����˵��
	unsigned int	lastVal[2*37*2];			//��ֵֹ�����˵��
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
}structStateItem;

typedef struct{
	unsigned int 	nStep;			//״̬����״̬��ţ���״̬�������ģ��ʹ��
	unsigned int 	nDegressStep;		//�ݱ䲽���ţ��ݱ�ģ���״̬���еĵݱ䶼ʹ								//�ø�����ָʾ
	unsigned int 	nType;			//������ͣ������3-1
	unsigned int 	nSource;			//����Դ�������3-2
	unsigned int 	nSec;				//UTCʱ����ֵ
	unsigned int 	nNanoSec;			//UTCʱ������ֵ
	structBIChange 	oBiChg;			//�����λֵ����sourceΪ�����λʱ����ֵ
	structBIStatus	nBi;				//������ֵ
	structBoStatus	nBo;				//������ֵ
}structResultItemNew;

typedef struct{
	structResultItemNew result[100];
}structResultNew;

void tmt_to_drv(tmt_StateTest *pTmt, drv_state_test *pDrv);
#endif // DRV_DEFINE

