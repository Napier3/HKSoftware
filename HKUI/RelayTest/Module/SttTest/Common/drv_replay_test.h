#include "tmt_replay_test.h"
#include "../../SttDevice/drv_define.h"
#include "../Common/drv_state_test.h"

typedef struct{
    unsigned int startType;       //0:no trip（直接开始）1:manu（手动触发 2:DI（开入触发） 3:GPS （GPS时间）， 这是开始播放的触发设置
    unsigned int startSec;        //gps start sec
    unsigned int startnSec;       //gps start nSec
    structBITrip stBIStart;				//开入触发开始时开入量配置
    unsigned int degressType;     //0 loop type 0x80000000 trip type //触发方式 0固定循环（上位机处理），循环触发结束循环  0x80000000 触发跳出循环
    unsigned int tripType;        //1 manu(手动)2 bi(开入) 3GPS(GPS) 4 time(延时)
    structBITrip stBITrip;				//开入触发配置
    int tripLoopCount;	 //循环册书
    int modeAfterTrip;
    unsigned int tripmDelay;		 //延时触发
    unsigned int tripgpsSec;      //GPS触发
    unsigned int tripgpsnSec;
    unsigned int freq;           //播放频率
    unsigned int moduleCount;	 //模块数量
    unsigned int module;	 //模块
}drv_structLtReplayParam;

#define COMTRADE_REPLAY_PKG_POINTS					600
#define LT_REPLAY_FRAME_PKG_CNT						3600
//定义最大 循环 A B 缓存大小
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
    float fCoef;//幅值系数
    float fZero;//交流零漂
    float fMaxValue; // 直流最大值 有效值*1.414
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
    LtReplayCoefItem Item[MAX_MODULE_COUNT][CHANNEL_MAX];
}drv_LtReplayCoef;
void tmt_to_drv(tmt_ReplayTest *pReplayPara, drv_structLtReplayParam *pDrvPara, drv_LtReplayCoef *);
