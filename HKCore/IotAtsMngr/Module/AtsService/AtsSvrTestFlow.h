//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//AtsSvrTestFlow.h  CAtsSvrTestFlow

#pragma once

#include "AtsServiceGlobal.h"


#include "AtsSvrDevices.h"
#include "../../../SttStudio/Module/SmartTestInterface/XSmartTestEventInterface.h"

#include "Engine/SttAtsSvrMqttImpBase.h"
#include "AtsSvrTestBench.h"

class CAtsSvrTestFlow : public CSttAtsSvrMqttImpBase
{
public:
	CAtsSvrTestFlow();
	virtual ~CAtsSvrTestFlow();


	CString  m_strSN;
//重载函数
public:
	virtual UINT GetClassID() {    return ATSVRCLASSID_CATSSVRTESTFLOW;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsServiceXmlRWKeys::CAtsSvrTestFlowKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//私有成员变量
private:
	CAtsSvrDevices *m_pDevices;

	CXSttSmartTestXInterface *m_pSmartTestSvr;

//私有成员变量访问方法
public:
	void AttachSmartTestSvrInterface(CXSttSmartTestXInterface *pSmartTestSvr)	{		m_pSmartTestSvr = pSmartTestSvr;	}
	CXSttSmartTestXInterface* GetSmartTestSvrInterface()	{	return m_pSmartTestSvr;	}

public:
	virtual long Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv);
	virtual long Process_Cmd_Iot(CXObjectRefDriver &oIotCmdDrv)	{	return 0;	}
	virtual long Process_Cmd_Test(CXObjectRefDriver &oTestCmdDrv)	{	return 0;	}
	virtual long Process_Cmd_SysState(CXObjectRefDriver &oSysStateDrv)	{	return 0;	}

private:
	long FlowSetBench_InitPara_Apps(CXObjectRefDriver &oAtsCmdDrv);
	CAtsSvrTestBench* FindBench(const CString &strBenchSN);
	CAtsSvrTestBench* AddNewBench(const CString &strBenchSN);
};

