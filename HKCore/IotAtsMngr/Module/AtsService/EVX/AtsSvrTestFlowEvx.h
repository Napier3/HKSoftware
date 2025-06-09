//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestFlowEvx.h  CAtsSvrTestFlowEvx

#pragma once

#include "../AtsSvrTestFlow.h"

#define STT_CMD_PARA_GunCount      "GunCount" //枪的数量1或者2
#define STT_CMD_PARA_GunARptFile   "GunARptFile"   //A枪测试报告
#define STT_CMD_PARA_GunBRptFile   "GunBRptFile"  //B枪测试报告  	
#define STT_CMD_PARA_GunA            "GunA"  
#define STT_CMD_PARA_GunB            "GunB"
#define STT_CMD_PARA_Gun              "Gun"

#define EVDX_GUN_SN_A    _T("/A")
#define EVDX_GUN_SN_B     _T("/B")
#define EVDX_GUN_SN_AB   _T("/AB")

class CAtsSvrTestFlowEvx : public CAtsSvrTestFlow
{
public:
	CAtsSvrTestFlowEvx();
	virtual ~CAtsSvrTestFlowEvx();

//CMqttMsgProcessInterface
public:
	virtual BOOL MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser);
	virtual BOOL MqttMatch(CSttMqttTopicParser &oSttMqttTopicParser, const CString &strDeviceSN);

public:
	long m_nGunCount;
	CString m_strGunARptFile;
	CString m_strGunBRptFile;

	//测试模板
	CString m_strGbxmlFile;
	CString m_strGbxmlFile_s;
	CString m_strDocFile_s;

	long m_nTestStateGunA;
	long m_nTestStateGunB;
	long m_nCmbnDocs;

protected:
	//CAtsSvrTestFlow::m_pSmartTestSvr; == GunA
	CXSttSmartTestXInterface *m_pSmartTestSvr_GunB;

	void InitGunXParas(CSttAtsCmd *pAtsCmd);
	void InitGunXParas(CDataGroup *pDevices);
	long CreateSmartTestSvr(CSttAtsCmd *pAtsCmd);
	void InitGunRptFile();

//重载函数
public:
	virtual CBaseObject* Clone();

protected:
	virtual long Process_Cmd_Ats_CreateTest(CXObjectRefDriver &oAtsCmdDrv);
	virtual long Process_Cmd_Ats_StartTest(CXObjectRefDriver &oAtsCmdDrv);
	virtual long Process_Cmd_Ats_StopTest(CXObjectRefDriver &oAtsCmdDrv);
	virtual long Process_Cmd_Ats_FlowSetBench(CXObjectRefDriver &oAtsCmdDrv);
	virtual long Process_Cmd_Ats_CloseTest(CXObjectRefDriver &oAtsCmdDrv);
	virtual long Process_Cmd_Ats_SetItemsReport(CXObjectRefDriver &oAtsCmdDrv);
	virtual long Process_Cmd_Ats_ExportReport(CXObjectRefDriver &oAtsCmdDrv);

	virtual long Process_Cmd_SysState_EVENT_ExportReport(CXObjectRefDriver &oAtsCmdDrv);
	virtual long Process_Cmd_SysState_EVENT_TestStarted(CXObjectRefDriver &oAtsCmdDrv);
	virtual long Process_Cmd_SysState_EVENT_TestStoped(CXObjectRefDriver &oAtsCmdDrv);
	virtual long Process_Cmd_SysState_EVENT_TestFinished(CXObjectRefDriver &oAtsCmdDrv);

protected:
	void Ats_ExportReport(const CString &strGbRptFile, const CString &strGunID);
	void Ats_CmbnReport();
	CString GetCmbnReportFile();
	void Return_EVENT_ExportFinish_A();
	void Return_EVENT_ExportFinish_AB();
	void Return_ExportFinish_AddFile(CDataGroup *pParent, const CString &strGbrptFile);
	void SendAtsCmdToAB(CSttAtsCmd *pAtsCmd, char *pszAtsCmd);
};

