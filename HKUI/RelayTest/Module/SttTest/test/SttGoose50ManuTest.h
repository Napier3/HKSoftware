#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../SttTestBase/SttComplexp.h"
#include "tmt_goose50_manutest.h"

#ifdef _PSX_QT_LINUX_
    #include "../../SttDevice/test/SttDevicetest.h"
#endif

class CSttGoose50ManuTest : public CSttTestBase
{
public:
    CSttGoose50ManuTest();
    virtual ~CSttGoose50ManuTest(void);

    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strFilePostFix;

    static CSttTestBase *CreateTest()
    {
        return new CSttGoose50ManuTest;
    }
public:
    UINT m_uStartTimeS;
    UINT m_uStartTimeMS;
    UINT m_uChangeTime;
    UINT m_uChangeTimeMS;
    UINT m_uStartTimeNS;
    bool m_bIsReturn;
    UINT m_uReturnTimeMS;
    UINT m_uReturnTime;
    int m_nFd;
    void SetGooseValue(tmt_GoosePub *pCurGoosePub, tmt_goose *ptmt_goose,
                       GooseChgItem *pGooseChgItem, tmt_GoosePub *pPreGoosePub);

public:
    virtual void Init();
    virtual long SetParameter(DWORD dwState = 0);
    virtual long OnTimer(BOOL &bFinish, long nTimerLongMs = 500);
    virtual void StartTest();
    virtual void Stop();
    virtual BOOL EventProcess();

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
    virtual void UpdatePara_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);
public:
    virtual void TtmToDrv();
};

extern tmt_Goose50Paras *g_pGoose50Paras;
