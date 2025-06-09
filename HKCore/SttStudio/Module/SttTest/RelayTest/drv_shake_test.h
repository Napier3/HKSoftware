#ifndef DRV_SHAKE_TEST_H
#define DRV_SHAKE_TEST_H

#include "drv_abnormal_test.h"
#include "../../SttDevice/RelayTest/drv_define.h"
#include "../../SttDevice/RelayTest/SttDevice.h"
#include"../../SttTestBase/SttComplexp.h"
#include "../../SttDevice/SttDeviceBase.h"
#include "../../SttTestBase/FaultCalculat.h"
#include "math.h"
#include "tmt_shake_test.h"

#define SHAKE_MAX 5000
#define SHAKE_ALG_PARA_CNT 24
#define SHAKE_DIG_PARA_CNT 75
#define NANOSECOND 1.0e9

typedef struct
{
    long ndat[SHAKE_ALG_PARA_CNT];
}drv_shakealg;

typedef struct
{
    unsigned int ndat[SHAKE_DIG_PARA_CNT];
}drv_shakesv;

typedef struct
{
	drv_shakealg alg[MODULE_MAX];
	drv_shakesv smv[DIGITAL_MODULE_MAX];
}drv_shakepara;

typedef struct
{
    unsigned int nalgCount;                    //模拟模块数量
    unsigned int ndigCount;                    //数字模块数量
    unsigned int nshakeCount;                //振荡步骤数
	unsigned int nBinaryInput;
    unsigned int nisRecip;                    //是否往复振荡
    unsigned int ntimeDiv;                    //变化时间间隔 namiao
    unsigned int ntimeBfShake;                //振荡前时长 haomiao
    unsigned int ntimeShake;                //故障前振荡时长 buchang
    unsigned int ntimeFault;                //故s障态时长  buchang
    unsigned int nalgModule[MODULE_MAX];    //模拟模块选择
    unsigned int ndigModule[DIGITAL_MODULE_MAX];    //数字模块选择
	drv_shakepara bfShake;                //振荡前数据
	drv_shakepara shake[SHAKE_MAX];        //振荡数据
	drv_shakepara falut[SHAKE_MAX];        //故障态
}drv_shake_test;

void tmt_to_drv(tmt_ShakeTest *pTmt, drv_shake_test *pDrv);

#endif // DRV_SHAKE_TEST_H

