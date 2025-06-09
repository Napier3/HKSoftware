#ifndef DRV_DEFINE
#define DRV_DEFINE

#include "tmt_state_test.h"
#include "../../SttDevice/drv_define.h"
#include "drv_manu_test.h"

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

void tmt_to_drv_StatePara(tmt_StateTest *pTmt, Drv_StatePara *pDrv);
void tmt_to_drv_StateItem(tmt_StateTest *pTmt, Drv_StateItem *pDrv_StateItem, char *pBuf,int &nBufLen);
#endif // DRV_DEFINE

