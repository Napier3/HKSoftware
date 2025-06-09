#pragma once

#include "XSmartTestEventInterface.h"

#define SmartTestSvr_Com		_T("SmartTestCom")
#define SmartTestSvr_Com_Flow   _T("SmartTestCom_Flow")
#define SmartTestSvr_Mqtt		_T("SmartTestMqtt")
#define SmartTestSvr_Mqtt_Flow   _T("SmartTestMqtt_Flow")

class CSttSmartTestSvrFactory : public CTLinkListEx<CXSttSmartTestXInterface> 
{
private:
	CSttSmartTestSvrFactory();
	virtual ~CSttSmartTestSvrFactory(void);

	static CSttSmartTestSvrFactory *g_pSttSmartTestSvrFactory;
	static long g_nSttSmartTestSvrFactory;

public:
	static CSttSmartTestSvrFactory* Create();
	static void Release();
	static CXSttSmartTestXInterface* CreateSttSmartTestSvr(const CString &strSmratTestSvr, const CString &strID);

};
