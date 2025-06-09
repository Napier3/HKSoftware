//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
//���غ���
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

//˽�г�Ա����
private:
	CAtsSvrDevices *m_pDevices;

	CXSttSmartTestXInterface *m_pSmartTestSvr;

//˽�г�Ա�������ʷ���
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

