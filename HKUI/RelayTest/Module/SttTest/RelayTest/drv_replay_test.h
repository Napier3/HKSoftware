#include "tmt_replay_test.h"
#include "../../SttDevice/RelayTest/drv_define.h"
#include "vector"
#define MAXCOUNT 50000000
#define NORMALPOINT 1000

typedef struct drv_replay_channel
{
    unsigned int nModule;
    unsigned int nCh;
}drv_ReplayChannel;

typedef struct drv_replay_param
{
    unsigned int nStartType;        //0:no trip    1:manu    2:DI        3:GPS
    unsigned int nStartSec;        //gps start sec
    unsigned int nStartnSec;        //gps start nSec
    unsigned int nBiRef;              //开入参考  0：翻转    1：高电平    2：低电平
    unsigned int nBiLogic;           //开入逻辑   0：开入与     1：开入或
    unsigned int nBiValid;             //开入有效通道
    unsigned int nDegressType;       //0 loop type 0x80000000 trip type
    unsigned int nTripType;         //1 manu 2 bi 3GPS 4 time
    unsigned int nSwitchlogic;    //0 and 1 or
    unsigned int nValidchannel;
    unsigned int nmDelay;
    unsigned int nGpsSec;
    unsigned int nGpsnSec;
    drv_ReplayChannel ch[MODULE_MAX + DIGITAL_MODULE_MAX];

    unsigned int nmSec;               //整个回放过程时长，单位毫秒
    unsigned int nFreq;               //播放频率，和之前算法相同
    unsigned int nLoopCount[3];       //1/2/3段循环次数，没有循环填0
    unsigned int nSOL1;               //第一段循环开始位置
    unsigned int nEOL1;               //第一段循环结束位置
    unsigned int nSOL2;               //第二段循环开始位置
    unsigned int nEOL2;               //第二段循环结束位置
    unsigned int nSOL3;               //第三段循环开始位置
    unsigned int nEOL3;               //第三段循环结束位置
}drv_ReplayParam;

typedef struct drv_replay_data
{
    unsigned int modular;		//高16位表示模块，0：电流	1：电压
    unsigned int lenth;			//数据长度，点数
    long  dat[0x2E0000];
}drv_ReplayData;


typedef struct
{
 double x;
 double y;
}LAGRANG_DATA;
void sendDataToDevice(std::vector<float> data,int nType,int channel);
int selectChannel(int nChannel, tmt_ReplyPara *pReplayPara);
void tmt_to_drv(tmt_ReplyPara *pReplayPara, drv_ReplayParam *pDrvPara, drv_ReplayData *pDrvData);
