#ifndef DRV_ABNORMAL_DEFINE
#define DRV_ABNORMAL_DEFINE

#include"drv_state_test.h"
#include "tmt_abnsimulation_test.h"

//SMV发送配置信息
typedef struct{
    unsigned int nmodule;				//模块编号
    unsigned int nreserved[3];			//占位数据
    unsigned int nsampleCount;			//采样计数和采样间隔
    unsigned int nsmvsamplebegin[4];				//采样计数器初值
}drv_smvconfig;

typedef struct
{
    int ngoosemodule;
    int ngroup ;//goose group
    int ngooselen;
    char szgoosebuf[1520];//goose out buffer
    int nTimePos;
}drv_gooseabnormal;

//abnormal
typedef struct{
    unsigned int	npoint;     //异常点号0～79
    unsigned short nlost;        //丢帧  1为丢帧；0为正常
    unsigned short	njitter; 	//抖动 0 不抖动 1为0.1us，250us写入2500
    int nerrcmpt;                //错序   -1999 到 2000 0为非错序
    unsigned int nflypoint;      //飞点使能
    int		 nflyPointVValue;	//飞点电压值
    int		 nflyPointIValue;	//飞点电流值
}drv_svabnunit;

typedef struct
{
    unsigned int   nmodule ;//数字模块编号，默认
    unsigned int  nptCnt;     //异常点数
    drv_svabnunit	smv_abnormal[80];	//每周波各点的异常设置
    int  ngroup;//SMV组号 8bit有效，0无效 1使能 如 0011 则是第一第二组使能，其他无效。
    unsigned int   nabnormalcircle ;//异常周波数
    unsigned int   nnormalcircle;// 正常周波数
    unsigned int   nroopcount ;//循环个数
}drv_smvabnormal;

typedef struct{
    unsigned int ncount;				//数据长度
    unsigned int ngroup;				//数据光口号
    unsigned char szdat[1536];			//配置数据
}drv_datconfig;

typedef struct{
    unsigned int nmodule;			//模块编号
    unsigned int ncount;				//组数总和
    drv_datconfig dat[8];
}drv_abnormalconfigs;

typedef struct
{
        unsigned long nStateNum;                                    //状态序列序号，0开始
        // 0 manual 1 time 2 gps 3 bin or 4 bin and
        unsigned long nTirpType;                                 //触发条件表，相应位置填写需要跳转到的状态
        unsigned long nReversal;                                    //开入翻转参考设置:
            //0：开入翻转触发wa
            //1：开入上升沿触发
            //2：开入下降沿触发
        unsigned long  nOrValid;               //开入或触发有效位
        unsigned long nAndValid;                                    //开入与触发有效位选择bit9~bit0对应通道9~通道0
        unsigned long nGpsSec;                                      //GPS触发秒值
        unsigned long nGpsnSec;                                     //GPS触发纳秒值
        unsigned long nTimemSec;                                    //时间触发毫秒值
        unsigned long nDelay;                                       //开入触发延时时间，开入条件满足后延时多长时间触发
        drv_analogbosetting oBo;
        drv_acanalogpara acAnalog;                          //模拟参数
        drv_digitalpara  acDigital;			//数字参数
        int nabnormaltype;           //0：正常 1：SMV异常  2：GOOSE 异常 其他： 无定义
        drv_gsechangeditems GooseChangedItem;// abnormaltype=0 valid
        drv_abnormalconfigs oabnormalcomfig;
        drv_smvabnormal osmvabnormal;//abnormaltype=1 valid
        drv_gooseabnormal ogooseabnormal;//abnormaltype=2 valid
        int nsendconfig;
        drv_smvconfig oconfig;
}drv_abnstate;

typedef struct
{
        unsigned long nModuleCount;				//模块总数
        unsigned long nStateModuleCount;        //数字模块
        unsigned long nStateCount;				//状态总数
        unsigned long nloop;
        unsigned long nReverRefence;                                //0 参考第一个状态 1参考上一个状态
        unsigned long noriginal;                //GOOSE init Value;
        drv_analogbosetting oBo;//什么作用？？？
        drv_abnstate stabnState[STATECOUNT];				//状态
}drv_abnstate_test;

void tmt_to_drv(tmt_AbnSimulationTest *pTmt, drv_abnstate_test *pDrv);

#endif
