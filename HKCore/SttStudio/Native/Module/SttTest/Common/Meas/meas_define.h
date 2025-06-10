#pragma once
#include "../../../SttTestBase/SttXmlSerialize.h"

typedef struct meas_channel_vector
{
public:
    double	fAmp;//核电采集精度需要到微安级别
	float	fAngle;
	float	fFreq;

public:
	void init()
	{
		fAmp = fAngle = fFreq = 0;
	}

	meas_channel_vector()	{	init();	}
}MEAS_CHANNEL_VECTOR;

typedef struct meas_channel
{
public:
	long nHarmCount;
	MEAS_CHANNEL_VECTOR  oVector[32];

public:
	void init()
	{
		nHarmCount = 0;
		for(int i=0;i<32;i++)
		{
			oVector[i].init();
		}
	}

	meas_channel()	{	init();	}
}MEAS_CHANNEL;

typedef struct meas_module
{
public:
	long nModulePos;
	long nModuleType;
	long nChanCount;
	MEAS_CHANNEL  oChannels[6];

public:
	void init()
	{
		nModulePos = 0;
		nModuleType = 0;
		nChanCount = 0;
		for(int i=0;i<6;i++)
		{
			oChannels[i].init();
		}
	}

	meas_module()	{	init();	}
}MEAS_MODULE;

typedef struct meas_device
{
public:
	long nModuleCnt;
	MEAS_MODULE  oModules[12];

public:
	void init()
	{
		nModuleCnt = 0;
		for(int i=0;i<12;i++)
		{
			oModules[i].init();
		}
	}

	meas_device()	{	init();	}
}MEAS_DEVICE;

extern MEAS_DEVICE *g_MeasDevice;

void stt_xml_serialize_register_meas(CSttXmlSerializeBase *pXmlSerialize);
