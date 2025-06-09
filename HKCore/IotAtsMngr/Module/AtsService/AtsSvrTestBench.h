//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestBench.h  CAtsSvrTestBench

#pragma once

#include "AtsServiceGlobal.h"


#include "AtsSvrTestApps.h"
#include "AtsSvrDevices.h"
#include "../../../SttStudio/Module/SmartTestInterface/XSmartTestEventInterface.h"

#include "Engine/SttAtsSvrMqttImpBase.h"

class CAtsSvrTestBench : public CSttAtsSvrMqttImpBase
{
public:
	CAtsSvrTestBench();
	virtual ~CAtsSvrTestBench();


	long  m_nSelfStart;
//重载函数
public:
	virtual UINT GetClassID() {    return ATSVRCLASSID_CATSSVRTESTBENCH;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsServiceXmlRWKeys::CAtsSvrTestBenchKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CAtsSvrTestApps *m_pTestApps;
	CDvmDataset *m_pAttrs;
	CAtsSvrDevices *m_pDevices;
	CDataGroup m_oDvmDevices;
	CDataGroup m_oBinForStart;  //2021-11-4  lijunqing  开关量输入：出发开始测试的条件

	CXSttSmartTestXInterface *m_pSmartTestSvr;

public:
	CAtsSvrTestApps* GetTestApps()	{	return m_pTestApps;	}
	void GetTestApps(CDataGroup &oTestApps);
	CDvmDataset* GetAttrs()				{	return m_pAttrs;			}
	CAtsSvrDevices* GetDevices()			{	return m_pDevices;		}
	CXSttSmartTestXInterface* GetSmartTestSvrInterface()	{	return m_pSmartTestSvr;	}
	CDataGroup* GetDvmDevices()			{	return &m_oDvmDevices;		}
	CDataGroup* FindDvmDevice(const CString &strDeviceSN);
	
	CDataGroup* GetBinForStart()			{	return &m_oBinForStart;		}
	void InitBinForStart(CDataGroup *pBinForStart);
	BOOL IsSmartTestSvr_Com();
	BOOL IsSmartTestSvr_Mqtt();

public:
	//2021-7-21  lijunqing  后续考虑将命令函数封装到Ats执行对象中，CSttAtsSvrMqttImpBase只作为命令中转对象，即：
	//通信对象（STT、MQTT）  <<==>>  SttCmd     
	virtual long Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv);
	virtual long Process_Cmd_Iot(CXObjectRefDriver &oIotCmdDrv)	{	return 0;	}
	virtual long Process_Cmd_Test(CXObjectRefDriver &oTestCmdDrv)	{	return 0;	}
	virtual long Process_Cmd_SysState(CXObjectRefDriver &oSysStateDrv);

	//shaolei 20210927
	virtual long Process_Cmd_Ats_Event_UploadFinish(CSttCmdBase* pSttCmdBase);

};

