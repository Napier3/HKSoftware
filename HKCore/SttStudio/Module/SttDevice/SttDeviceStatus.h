#ifndef CSTTDEVICE_STATUS_H
#define CSTTDEVICE_STATUS_H

#include "../SttTestBase/SttXmlSerialize.h"
#include "../SttTest/Common/tmt_adjust_sys_parameter.h"
#include "../RecordTest/RingMemBuf.h"

#define CHANNEL_MAX 6


typedef struct stt_module_ch_status
{
    char m_pszChId[STT_HD_CH_ID_BUF_LEN];
    float m_fVoltMax;//最大电压
    float m_fVoltMin;//最小电压
    long m_bIsOverLoad;//过载
} STT_MODULE_CH_STATUS, *PSTT_MODULE_CH_STATUS;

typedef struct stt_module_status
{
    STT_MODULE_CH_STATUS m_oChannel[CHANNEL_MAX];//通道0-5
    float m_fVoltDc[4];//电源电压
    float m_fBAT[2];//0-电池电压 1-电池电流
    long m_nWarningVal;
    long m_nTemp[3];//温度
    long m_nIsVoltHot;//电压过热
    long m_nIsDCHot;//直流过热
    long m_nIsVoltWarining;//电压告警
    long m_nIsMissWarining;//失地告警
    long m_nModuleType;
    long m_nModulePos;//1~11
    long m_nChanNum;
    long m_nDisable;//为1禁用输出
    long m_nNeedMonitor;//为1启用监视
    float m_fLCPortPower[8];//8个LC光口功率

    bool is_exception()
    {
        for(int i = 0; i < CHANNEL_MAX; i++)
        {
            if(m_oChannel[i].m_bIsOverLoad)
            {
                return true;
            }
        }

        return false;
    }
} STT_MODULE_STATUS, *PSTT_MODULE_STATUS;

typedef struct stt_device_status
{
    unsigned int m_nAnalogCount;
    STT_MODULE_STATUS m_oModule[ADJUST_MAX_MODULE_COUNT];

    long m_nSync;  //同步
    long m_nUtc_s; //UTC原始数据
    long m_nUtc_ns;
    long m_nUser_s; //用户系统需要的当地时间
    long m_nTimeZone;//用户系统所在时区

    long m_bNeedStop;//高温停止实验
    long m_b4G;//1-4G使用中
    long m_bWifi;//1-WIFI使用中
    long m_bBle;//1-蓝牙使用中
    long m_bPowerAC;//1-充电中，2-未充电时电量采集异常
    long m_bUSB;//1-USB使用中
    long m_nBatCap;//电池剩余容量%

    long m_nOverHeat;//模块过热
    long m_nIBreak;//电流开路
    long m_nUShort;//电压短路
    long m_nUdc;//辅助电压
    long m_nBatErr;//1-电量采集异常

    long m_nPPSReadPos;
    long m_nPPS64ReadSizeTotal;
    void init()
    {
        m_nAnalogCount = 2;
        m_bNeedStop = FALSE;
        m_nSync = 0;
        m_b4G = 0;
        m_bWifi = 0;
        m_bBle = 0;
        m_bPowerAC = 0;
        m_bUSB = 0;
        m_nBatCap = 0;
        m_nOverHeat = 0;
        m_nIBreak = 0;
        m_nUShort = 0;
        m_nUdc = 0;
        m_nPPSReadPos = 0;
        m_nPPS64ReadSizeTotal = 0;
        m_nTimeZone = 0;
        m_nBatErr = 0;
    }

    bool is_exception()
    {
        if(m_bNeedStop || m_nOverHeat || m_nIBreak || m_nUShort)
        {
            return true;
        }

        for(unsigned int i = 0; i < m_nAnalogCount; i++)
        {
            if(m_oModule[i].is_exception())
            {
                return true;
            }
        }

        return false;
    }
} STT_DEVICE_STATUS, *PSTT_DEVICE_STATUS;

extern PSTT_DEVICE_STATUS g_theSttDeviceStatus;
extern CRingMemBuf *g_pPPSBuf;

void stt_init_stt_device_status();
void stt_free_stt_device_status();

void stt_xml_serialize_register_device_status();
void stt_xml_serialize_device_utc(CSttXmlSerializeBase *pXmlSerialize);
void stt_xml_serialize_device_status(CSttXmlSerializeBase *pXmlSerialize, BOOL IsReport);
void stt_xml_serialize_Digital_LightPower(CSttXmlSerializeBase *pXmlSerialize);

#endif // CSTTDEVICE_STATUS_H
