#ifndef CSTTDEVICE_STATUS_H
#define CSTTDEVICE_STATUS_H

#include "../SttTestBase/SttXmlSerialize.h"
#include "../SttTest/Common/tmt_adjust_sys_parameter.h"
#include "../RecordTest/RingMemBuf.h"

#define CHANNEL_MAX 6


typedef struct stt_module_ch_status
{
    char m_pszChId[STT_HD_CH_ID_BUF_LEN];
    float m_fVoltMax;//����ѹ
    float m_fVoltMin;//��С��ѹ
    long m_bIsOverLoad;//����
} STT_MODULE_CH_STATUS, *PSTT_MODULE_CH_STATUS;

typedef struct stt_module_status
{
    STT_MODULE_CH_STATUS m_oChannel[CHANNEL_MAX];//ͨ��0-5
    float m_fVoltDc[4];//��Դ��ѹ
    float m_fBAT[2];//0-��ص�ѹ 1-��ص���
    long m_nWarningVal;
    long m_nTemp[3];//�¶�
    long m_nIsVoltHot;//��ѹ����
    long m_nIsDCHot;//ֱ������
    long m_nIsVoltWarining;//��ѹ�澯
    long m_nIsMissWarining;//ʧ�ظ澯
    long m_nModuleType;
    long m_nModulePos;//1~11
    long m_nChanNum;
    long m_nDisable;//Ϊ1�������
    long m_nNeedMonitor;//Ϊ1���ü���
    float m_fLCPortPower[8];//8��LC��ڹ���

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

    long m_nSync;  //ͬ��
    long m_nUtc_s; //UTCԭʼ����
    long m_nUtc_ns;
    long m_nUser_s; //�û�ϵͳ��Ҫ�ĵ���ʱ��
    long m_nTimeZone;//�û�ϵͳ����ʱ��

    long m_bNeedStop;//����ֹͣʵ��
    long m_b4G;//1-4Gʹ����
    long m_bWifi;//1-WIFIʹ����
    long m_bBle;//1-����ʹ����
    long m_bPowerAC;//1-����У�2-δ���ʱ�����ɼ��쳣
    long m_bUSB;//1-USBʹ����
    long m_nBatCap;//���ʣ������%

    long m_nOverHeat;//ģ�����
    long m_nIBreak;//������·
    long m_nUShort;//��ѹ��·
    long m_nUdc;//������ѹ
    long m_nBatErr;//1-�����ɼ��쳣

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
