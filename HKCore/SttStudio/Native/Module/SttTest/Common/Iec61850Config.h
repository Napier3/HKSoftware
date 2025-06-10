#pragma once

#include"../../SttTestBase/SttTestBase.h"
#include"../../../../61850/Module/CfgDataMngr/IecCfgDatasMngr.h"

#ifdef _PSX_QT_LINUX_
#include "../../SttDevice/SttDeviceBase.h"
#endif


class CIec61850Config : public CSttTestBase
{
public:
    CIec61850Config();
    virtual ~CIec61850Config(void);


    static CString m_strMacroName;
    static CString m_strMacroID;
    static CString m_strMacroVer;
    static CString m_strFilePostFix;

    static CSttTestBase* CreateTest()
    {
        return new CIec61850Config();
    }

public:
	CIecCfgDatasMngr* m_pIecCfgDatasMngr;

    virtual void AfterSetParameter();

	virtual long CalReport(UINT nState=0);

    virtual void Para_XmlSerialize(CSttXmlSerializeBase *pXmlSerialize);

public:
    virtual void Init();
    virtual long SetParameter(DWORD dwState = 0);
    virtual void StartTest();

    //将上层结构体转为底层结构体
public:
	virtual void TtmToDrv();
};

extern CString g_strIecCfgVer;
