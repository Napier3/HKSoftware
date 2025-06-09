#ifndef DRV_STEP6U6I_DEFINE
#define DRV_STEP6U6I_DEFINE

#include "tmt_harm_test.h"

#define ALG_MODULE_MAX		12
#define BIO_MODULE_MAX		5
#define ALG_PARAM_MAX		3441

//ģ�����ݺ����Ҳ����ṹ
typedef struct{
	unsigned int nDWcnt;			//��Ч���ݸ�������32λΪ��λ
	long dat[ALG_PARAM_MAX];	//ģ������Ҳ�������
}structHarmParam;
//������ģ�����ݽṹ
typedef struct{
	unsigned int dat[2]; //�������ݣ���λȡ�����64��
}structBIOParam;
//�ֶ�ʵ�����ݶ���ṹ
typedef struct{
	structHarmParam	oharm[ALG_MODULE_MAX];
	structBIOParam		obinIO[BIO_MODULE_MAX];
}structManuData;

//harm
void tmt_to_drv(tmt_HarmTest *pTmt , structManuData *pDrv);

#endif // DRV_DEFINE

