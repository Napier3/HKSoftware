#ifndef DRV_MANU_DEFINE
#define DRV_MANU_DEFINE

#include "tmt_manu_test.h"
#include "tmt_adjust_sys_parameter.h"

#define ALG_PARAM_MAX 3441
#define BIO_MODULE_MAX 5
#define ALG_MODULE_MAX 12

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

//manu
void SetDrvMoudlePara(BOOL bHasAnalog,BOOL bHasDigital);
void tmt_to_drv(tmt_ManualTest *pTmt , Drv_ManuData *pDrv,int nHarm=1);
void tmt_to_drv_manual_volt(tmt_channel *pTmt_channel,Drv_ManuData *pDrv,int nHarm,int nIndex,BOOL bIsDc=FALSE);
void tmt_to_drv_manual_current(tmt_channel *pTmt_channel,Drv_ManuData *pDrv,int nHarm,int nIndex,BOOL bIsDc=FALSE);


long TranslateACFre(float fFre);

//volt
void TransAnalogDCVolToDrv(float fAmp,int nChannel,int nModuleUIndex,long *pDrvData);
long TranslateACVoltAmp(float fAmp,int nChannel,int nModuleUIndex,int nHarm);
void TransAnalogVolToDrv(float fAmp,float fAng,float fFre,int nChannel,int nModuleUIndex,long *pnDrvData);

//current
void TransAnalogDCCurToDrv(float fAmp,int nChannel,int nModuleIIndex,long *pDrvData);
long  TranslateACCurrentAmp(float fAmp,int nChannel,int nModuleIIndex,int nHarm);
void TransAnalogCurToDrv(float fAmp,float fAng,float fFre,int nChannel,int nModuleIIndex,long *pnDrvData);

//systemdefaultoutput
void tmt_to_drv_systemdefaultoutput(TMT_SYSTEM_DEFAULT_OUTPUT_PARAS *pTmt);
#endif // DRV_DEFINE

