#pragma once

#include "SttXmlSerialize.h"
#include "../MemBuffer/stt_cycle_buffer.h"
#include "../SttTest/Common/tmt_rtdata_def.h"

//��Ӧ���type
#define SttResult_Type_TestStart			  1//��ʼʵ��
#define SttResult_Type_TestFinish			  2//ʵ�����
#define SttResult_Type_StateChange			  3//״̬�л�
#define SttResult_Type_Bin                    4//�����λ
#define Result_Type_StateRamp                 5//�ݱ�
#define Result_Type_StateRampStop             6//�ݱ�ֹͣ
#define SttResult_Type_PPSTime                7//��ʱ��ʱ���
#define SttResult_Type_Bout                   8//������λ
#define SttResult_Type_IEC_DETECT             9//����̽����
#define SttResult_Type_SearchPointReport	 10//�����㱨������  zhouhj 20210925

#define SttResult_Type_TestParaException     30
#define SttResult_Type_BinEx                 34//������չ��λ
#define SttResult_Type_BoutEx                37//������չ��λ

#define SttResult_Type_Ramp_BfFault          35//�ݱ����ǰ״̬
#define SttResult_Type_Ramp_Fault            36//�ݱ����״̬

#define SttResult_Type_Swing_Swing           38//�л�����
#define SttResult_Type_Swing_Fault           39//�л�������

//��Ӧ���source
#define Result_Trig_Null        0
#define Result_Trig_Manual      1
#define Result_Trig_TimeDelay   2
#define Result_Trig_GPS         3
#define Result_Trig_Bin         4

#define IEC_TYPE_SMV_92		1
#define IEC_TYPE_GOOSE		2
#define IEC_TYPE_FT3		3

typedef struct stt_iec_detect
{
	long nCrc;
	long nAppid;
	long nPort;
	long nType;
}STT_IEC_DETECT, *PSTT_IEC_DETECT;

//////////////////////////////////////////////////////////////////////////
//STT_TEST_EVENT_CYCLE_ARRAY
//2020-10-22  lijunqing 
#define STT_DRV_RTDATA_MSG_MAX_COUNT	100//������С�ݱ�ֶ�10�������,����ռ�100��
#define STT_TEST_EVENT_MAX_COUNT		1000

typedef struct stt_test_event_info
{
	long nType;  //bin bout u i
    long nStateIndex;//ʵ��ִ�е�״̬˳���,����
    long nStateNum;//ʵ�ʹ�ѡ��״̬�ţ���һ������
	long nStepIndex;
	long nChannel;
	long nValue;
	STT_IEC_DETECT oIecDetect;
}STT_TEST_EVENT_INFO, *PSTT_TEST_EVENT_INFO;

typedef struct stt_test_event
{
	long nEventInfoCnt;//ͬʱ�̶�����Ϣ�ϲ��洢
	STT_TIME oTime;
	STT_TEST_EVENT_INFO oEventInfo[MAX_ExBINARY_COUNT];
}STT_TEST_EVENT, *PSTT_TEST_EVENT;

typedef struct _stt_test_event_cycle_array_ : public STT_CYCLE_BUFFER_HEAD_DEF
{
	long m_nLockFlag;
	STT_TEST_EVENT bufEvent[STT_TEST_EVENT_MAX_COUNT];
}STT_TEST_EVENT_CYCLE_ARRAY, *PSTT_TEST_EVENT_CYCLE_ARRAY;

typedef struct _stt_rtdatas_cycle_array_ : public STT_CYCLE_BUFFER_HEAD_DEF
{
	long m_nLockFlag;
	STT_RTDATA_EVENT bufRtdata[GRADIENT_MAX_COUNT+10];
}STT_RtDatas_CYCLE_ARRAY, *PSTT_RtDatas_CYCLE_ARRAY;

extern PSTT_TEST_EVENT_CYCLE_ARRAY g_theSttTestEventCycleArray;
extern PSTT_RtDatas_CYCLE_ARRAY g_theSttRtDatasCycleArray;
void stt_create_test_event_cycle_array();
void stt_clear_test_event_cycle_array();
void stt_free_test_event_cycle_array();
void stt_create_rtdatas_cycle_array();
void stt_free_rtdatas_cycle_array();

//void stt_add_test_event(int nType,int StateIndex, int StepIndex, int nChannel, int nValue, double dTime, double dRealTime);
void stt_add_test_event(STT_TEST_EVENT obufEvent);
void stt_add_iec_detect_event(int nType,STT_IEC_DETECT oIecDetect);
long stt_get_test_event_count();
void stt_xml_serialize_test_events(CSttXmlSerializeBase *pXmlSerialize);

void stt_xml_serialize_test_events_time(CSttXmlSerializeBase *pXmlSerialize, PSTT_TIME pSttTime);
//void stt_xml_serialize_test_events_time(CSttXmlSerializeBase *pXmlSerialize, long nUtc_s, long nUtc_ns);

void stt_test_event_set_lock(long nLockFlag);
long stt_test_event_set_is_lock();

void stt_add_rtdatas(STT_RTDATA_EVENT oRtdata);
long stt_get_rtdatas_count();
void stt_xml_serialize_rtdatas(CSttXmlSerializeBase *pXmlSerialize);
