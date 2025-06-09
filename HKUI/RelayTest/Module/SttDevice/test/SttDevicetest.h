#ifndef CSTTDEVICEPNS330_H
#define CSTTDEVICEPNS330_H

#include "../SttDeviceBase.h"
#include "../Module/Driver466/IEC61850CfgMngr.h"
#include "stdafx.h"

typedef struct
{
    unsigned int T0;
    unsigned int T1;
    unsigned int T2;
    unsigned int T3;
} GooseCfg;

typedef struct
{
    unsigned int valid;
    unsigned int index;
    unsigned int datCnt;
    unsigned char dat[500];
} datConfig;

typedef struct
{
    datConfig gs[50];
} GooseItems;

typedef struct
{
    unsigned int pos;
    unsigned int count;
    unsigned char dat[20];
} GooseChgPoint;

typedef struct
{
    unsigned int valid;
    unsigned int StNumChg;
    unsigned int count;
    GooseChgPoint dat[20];
} GooseChgItem;

typedef struct
{
    GooseChgItem dat[50];
} GooseChgItems;

class CSttDevicetest : public CSttDeviceBase
{
private:
    explicit CSttDevicetest();
    ~CSttDevicetest();
    static long g_nSttDeviceRef;
    long m_nModuleDIndex;//Êý×Ö°åÎ»ÖÃ

public:
    static void Create();
    static void Release();
    static CSttDevicetest *g_pSttDevicePNS330;
    GooseItems m_oGooseItems;
    GooseChgItems m_oGooseChgItems;
    CIEC61850CfgMngr m_oCIEC61850CfgMngr;
    tmt_GoosePub m_oPreGoosePub[50];

    virtual int InitDevice(BOOL bHasAdjFile);
    virtual BOOL OnTimer(BOOL bExec = FALSE);
public:
    virtual void SetSystemConfig()
    {
    }

    virtual void InitDrvResult() {}
    virtual void ProCommDrvResult(BOOL &bTestFinished, STT_TIME &oTestFinishedTime)
    {}

    //IEC61850
public:
    virtual void *GetIecCfgDatasMngr()
    {
        return &m_oCIEC61850CfgMngr.m_oIecCfgDatasMngr;
    }
    virtual void SetIEC61850Para();

private:
    int m_nBatCalcCnt;
    int m_nTestStopTick;
};

#endif // CSTTDEVICEPNS330_H
