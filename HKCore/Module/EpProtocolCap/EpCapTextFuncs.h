#pragma once

#include "CapCycleMemBuffer.h"
#include "CapSmFileDB\SmFileDBQueryDef.h"
#include "CapSmFileDB\CapSmDb.h"

#include "..\MemBuffer\BinaryTextConvert.h"
#include "..\Protocol\101\EpGlobalDefine_101.h"

#include "Config\MonitorCapConfig.h"

#ifdef _MonitorQueryConfig_H__
#include "Config\MonitorQueryConfig.h"
#endif

#define EPCAP_QUERYFRAME_COL_INDEX   0
#define EPCAP_QUERYFRAME_COL_TIME   1
#define EPCAP_QUERYFRAME_COL_SRCADDR   2
#define EPCAP_QUERYFRAME_COL_DESTADDR   3
#define EPCAP_QUERYFRAME_COL_DIR   4
#define EPCAP_QUERYFRAME_COL_FRAME_DESC   5
#define EPCAP_QUERYFRAME_COL_FRAME_TEXT   6
#define EPCAP_QUERYFRAME_COL_CAPID   7


void EpTxt_GetAddrText(EP_ETHER_CAP_IP cap_ip, CString &strText, BOOL bDest=FALSE);
void EpTxt_GetContentText(PEPCAPDBBUFFERINDEX pIndex, CString &strText);
void EpTxt_GetContentText(DWORD nProtocol, WORD nDeviceDataType, CString &strText);
BOOL EpTxt_GetItemTextBuffer(CCapSmDb *pCapSmDb, CEpCapDbBufferIndex *pDbIndex,CString &strText);
BOOL EpTxt_GetItemTextBuffer(BYTE *pBuffer, long nLen, CString &strText);

#ifdef _MonitorQueryConfig_H__
void EpTxt_GetDir(CMonitorQueryConfig *pCapConfig, EP_ETHER_CAP_IP cap_ip, CString &strText);
#endif

CString EpTxt_GetCapFrameTitle(long nCol);
