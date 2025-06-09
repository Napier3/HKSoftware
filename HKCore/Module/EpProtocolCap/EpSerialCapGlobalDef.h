#pragma once

#include "EpCapGlobalDef.h"

#define  MAX_BUFFER_LEN 3028
#define  MAX_SERIAL_BUFFER_LEN 65536

typedef struct ep_serial_cap_config
{
	int iPort;
	int iBaudRate;
	int iByteSize;
	int iParity;
	int iStopBits;
}EP_SERIAL_CAP_CONFIG;

