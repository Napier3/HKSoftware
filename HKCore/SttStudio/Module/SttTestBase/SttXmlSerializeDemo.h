#pragma once

#include "SttXmlSerialize.h"

#define STT_XMLSERIALIZE_CHANNEL_MAX   24
#define STT_XMLSERIALIZE_STATE_MAX     8

typedef struct SttXmlSerialize_Channel
{
	float fMag;
	float fAng;
	float fFreq;
}STT_XMLSERIALIZE_CHANNEL, *PSTT_XMLSERIALIZE_CHANNEL;

typedef struct SttXmlSerialize_State
{
	float fMaxTime;
	STT_XMLSERIALIZE_CHANNEL UI[STT_XMLSERIALIZE_CHANNEL_MAX];
}STT_XMLSERIALIZE_STATE, *PSTT_XMLSERIALIZE_STATE;


typedef struct SttXmlSerialize_StateTest
{
	int nStateCount;
	STT_XMLSERIALIZE_STATE state[STT_XMLSERIALIZE_STATE_MAX];
}STT_XMLSERIALIZE_STATETEST, *PSTT_XMLSERIALIZE_STATETEST;

void stt_init_paras(STT_XMLSERIALIZE_STATETEST &oStateTest);
void xml_serialize(STT_XMLSERIALIZE_STATETEST &oStateTest, CSttXmlSerializeBase *pXmlSierialize);


//Demo
extern STT_XMLSERIALIZE_STATETEST g_oStateTestDemo;

void xml_serialize_read_demo();
void xml_serialize_write_demo();
void xml_serialize_register_demo();
