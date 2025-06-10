#ifndef DRV_STEP6U6I_DEFINE
#define DRV_STEP6U6I_DEFINE

#include "tmt_harm_test.h"

#define ALG_MODULE_MAX		12
#define BIO_MODULE_MAX		5
#define ALG_PARAM_MAX		3441

//模拟数据和正弦参数结构
typedef struct{
	unsigned int nDWcnt;			//有效数据个数，以32位为单位
	long dat[ALG_PARAM_MAX];	//模拟或正弦参数数据
}structHarmParam;
//开出量模块数据结构
typedef struct{
	unsigned int dat[2]; //开出数据，按位取，最多64个
}structBIOParam;
//手动实验数据顶层结构
typedef struct{
	structHarmParam	oharm[ALG_MODULE_MAX];
	structBIOParam		obinIO[BIO_MODULE_MAX];
}structManuData;

//harm
void tmt_to_drv(tmt_HarmTest *pTmt , structManuData *pDrv);

#endif // DRV_DEFINE

