#ifndef DRV_MANU_GRADIENT_DEF_H
#define DRV_MANU_GRADIENT_DEF_H

#ifdef _PSX_IDE_QT_
#include<QVector>
#endif
#include "tmt_gradient_test.h"
#include "tmt_manu_test.h"
#include "../../SttDevice/RelayTest/drv_define.h"

typedef struct
{
    unsigned int	nmodule;                 //模块编号
    unsigned int	nposCnt;                 //位置总数，最大为6
    unsigned int	npos[GRADIENT_PARAM_MAX];  //位置值
	long 			ndat[GRADIENT_PARAM_MAX];  //每个位置的数据
}drv_gradientdigunit;

typedef struct
{
    unsigned int	nmodule;  //模块编号
    unsigned int	nposCnt;  //位置总数，最大为6
	unsigned int	npos[CHANNEL_MAX*3]; //位置值
	long 			ndat[CHANNEL_MAX*3]; //每个位置的数据
}drv_gradientalgunit;

typedef struct
{
    long ndat[GRADIENT_ALG_PARA_CNT];
}drv_gradientalg;

typedef struct
{
    unsigned int ndat[GRADIENT_SMV_PARA_CNT];
}drv_gradientdig;

//该两个数据所在数组成员变量的位置必须与structDegPara deg[3000];相同，否则会导致输出不正确
typedef struct
{
    drv_gradientalg    alg[MODULE_MAX];
	drv_gradientdig    dig[DIGITAL_MODULE_MAX];
}drv_gradientnormal;

typedef struct
{
    drv_gradientalgunit	 algDgress[MODULE_MAX];          //模拟递变数据，最大4个模块
    drv_gradientdigunit	  digDgress[DIGITAL_MODULE_MAX];  //SMV递变数据，最大4个模块
}drv_gradientpara;

typedef struct
{
    unsigned int nalgCount;             //模拟模块总数
    unsigned int ndigCount;             //数字模块总数
    unsigned int ngradientCount;         //递变总数    递变次数 + 1 ？？
    unsigned int nisReturn;             // 0： 动作值   1： 返回系数？？？
    unsigned int ndiRef;                //开关量参考，0：翻转	1：上升沿	2：下降沿
    unsigned int ndiLogic;              //开关量有效逻辑，0：开入与		1：开入或
    unsigned int ndiValid;              //开关量有效位，bit9~0对应开入9~0
	unsigned int ngsAndValid;           //goose与有效位，未使用
    unsigned int ngsOrValid;            //goose或有效位，未使用    
    unsigned int ntimeDiv;              //递变时间分度，毫秒值。步长时间
    unsigned int ntimeBfChg;            //递变前时间，单位毫秒，变化前时间
	drv_gradientnormal bfChange;          //递变前数据参数？？？
    unsigned int ntimeBfFault;          //故障前时间，单位毫秒
	 drv_gradientnormal bfFault;           //故障前参数？？？
    unsigned int nDIBfFault;            //故障前开入信号
    unsigned int nDIFault;              // 故障开入
    unsigned int nDIFaultFlipSec;       // 故障开入翻转秒值
    unsigned int nDIFaultFlipnSec;      // 故障开入翻转时间纳秒
    drv_gradientpara       gradient[GRADIENT_MAX_COUNT];     //递变参数，最大3000个递变
}drv_gradient_test;



typedef struct
{
    unsigned int nmodule; //模块编号
    unsigned int nharmCnt; //谐波数目
    unsigned int ndat[DIGITAL_CHANNEL_MAX * 3 * HARMONIC_MAX]; // 2325 total 9300 bytes
}drv_sinharmitem;

typedef struct
{
    unsigned int nmoduleCount; // 几个数字模块
    drv_sinharmitem harm[4];
}drv_sinharm;

typedef struct
{
    unsigned int nmodule;
    unsigned int nwaveCount;//波形数
	long ndat[CHANNEL_MAX+CHANNEL_MAX*3*HARMONIC_MAX]; // 此处应该是564
}drv_harm;

typedef struct
{
    unsigned int nmdCount;//表示一共有几个模拟模块 最大不超过4个，没有是0
    unsigned int nuiDO;//开出
    drv_harm      harm[4];
}drv_harmpara;

typedef struct
{
    drv_sinharm     dig; //数字模块
    drv_harmpara  alg; //模拟
}drv_manu_test;

typedef struct
{
    unsigned int 	nisStop;			//接收到开入是否停止
    unsigned int	nmdelay;			//接收到开入量停止延时时间，单位毫秒
    unsigned int 	nisSend0;		//停止时SMV是否发送0，是否保持发送
    unsigned int 	nbiRef;			//开入参考0：翻转	1：true		2：false
    unsigned int 	nbiAndValid;		//开入与有效位
    unsigned int 	nbiOrValid;		//开入或有效位
    unsigned int 	ngsAndValid;		//未使用，使用biAndValid
    unsigned int 	ngsOrValid;		//未使用，使用biOrValid
}drv_manu_bi;

////manu  &&    degress
//typedef struct
//{
//    unsigned int nstep;      //步数
//    unsigned int ntype;		//0:start  1:stop  2:change  3:di change  4:start to return
//    unsigned int ntm_h;      //秒
//    unsigned int ntm_l;      //tm_l/2^32
//    unsigned int ndi;        //硬开入
//    unsigned int ngsdi;      //gs开入
//    unsigned int nsource;    //开入变化状态
//}drv_gradient_result;

typedef struct
{
    drv_manu_test       m_oManuStruct;
    drv_manu_bi           m_oManuBinStruct;
    drv_gradient_test  m_oGradientStruct;
}drv_manu_gradient_test;


void tmt_to_drv_manual_digital(drv_manu_test *pDrv, tmt_channel *pUData, tmt_channel *pIData, bool bDC=false,int harm=1);
void tmt_to_drv_manual_analog(drv_manu_test *pDrv, tmt_channel *pUData, tmt_channel *pIData, tmt_BinaryOut *binOut, bool bDC=false,int harm=1);
void tmt_to_drv_Gradient_alg(drv_gradient_test *pDrvGradient, tmt_GradientProcess *pGradientProcess, int nGradientType,int nHarmIndex=1);
void tmt_to_drv_Gradient_dig(drv_gradient_test *pDrvGradient, tmt_GradientProcess *pGradientProcess, int nGradientType, int bDC=false,int nHarmIndex=1);
#endif

