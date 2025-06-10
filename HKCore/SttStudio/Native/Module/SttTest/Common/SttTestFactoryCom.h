#pragma once
#include "../../SttTestBase/SttTestFactory.h"

class CSttTestFactoryCom : public CSttTestFactory
{
public:
    CSttTestFactoryCom(void);
    virtual ~CSttTestFactoryCom(void);
    CString m_strPxAppID_Relay;
    CString m_strPxAppName_Relay;

public:
    virtual void RegisterInit();
};

