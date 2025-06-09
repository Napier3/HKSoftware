//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//AtsSvrService.h  CAtsSvrService

#pragma once

#include "AtsServiceGlobal.h"


#include "AtsSvrTestBenchs.h"
#include "AtsSvrTestResources.h"
#include "AtsSvrTestFlows.h"

#include "../SttMqttClientTool.h"
#include "../../../SttStudio/Module/SmartTestInterface/XSmartTestEventInterface.h"

#define ATSSVR_SVERVICE_MODE_BENCH                    _T("Bench")
#define ATSSVR_SVERVICE_MODE_FLOW                     _T("Flow")
#define ATSSVR_SVERVICE_MODE_BENCH_AND_FLOW   _T("Bench_Flow")


class CAtsSvrService : public CSttAtsSvrMqttImpBase
{
public:
	CAtsSvrService();
	virtual ~CAtsSvrService();

	CString  m_strSn;
	CString  m_strSvrMode;
	CString  m_strSmartTestSvr;   //Mqtt��Com
	long m_nIsServiceMngr;   //2021-11-9  lijunqing

//���غ���
public:
	virtual UINT GetClassID() {    return ATSVRCLASSID_CATSSVRSERVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsServiceXmlRWKeys::CAtsSvrServiceKey();     }
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
	CAtsSvrTestBenchs *m_pBenchs;
	CAtsSvrTestResources *m_pTestResources;
	CDvmDataset *m_pAttrs;

	CAtsSvrTestFlows *m_pTestFlows;

protected:
	CExBaseList* m_pIotBenchsRef;   //�����ݿ��в�ѯ��õĲ���̨�б����á�����������Ϊ��CIot_Benchs

//˽�г�Ա�������ʷ���
public:
	void InitAtsSvrService();
	void InitAtsSvrService(const CString &strFile);
	void SaveAtsSvrService();
	void SaveAtsSvrService(const CString &strFile);

	BOOL IsMode_Bench()	{	return m_strSvrMode == ATSSVR_SVERVICE_MODE_BENCH;	}
	BOOL IsMode_Flow()	{	return m_strSvrMode == ATSSVR_SVERVICE_MODE_FLOW;	}
	BOOL IsMode_BenchFlow()	{	return m_strSvrMode == ATSSVR_SVERVICE_MODE_BENCH_AND_FLOW;	}

	CAtsSvrTestBench* FindBench(const CString &strBenchSN);
	CAtsSvrTestBench* FindBenchByDeviceSN(const CString &strDeviceSN);
	CAtsSvrTestBench* AddNewBench(const CString &strBenchSN);

	void SetBenchsRef(CExBaseList *pBenchs)		{	m_pIotBenchsRef = pBenchs;	}
	void SyncBenchsFormDB();  //�����ݿ�ͬ������̨�����������ļ�
	
//Mqtt�¼��ӿ�
//class CSttMqttMsgInterface
public:
	//����ģ�������ص����⣬������ͻ��˶��ģ������ظú���
	BOOL CreateAtsServiceMqttClient_Ex(const CString &strMqttTopic);  
protected:

public:
	virtual long Process_Cmd_Ats(CXObjectRefDriver &oAtsCmdDrv);
	virtual long Process_Cmd_Iot(CXObjectRefDriver &oIotCmdDrv)	{	return 0;	}
	virtual long Process_Cmd_Test(CXObjectRefDriver &oTestCmdDrv)	{	return 0;	}
	virtual long Process_Cmd_SysState(CXObjectRefDriver &oSysStateDrv);

	CXSttSmartTestXInterface* FindSmartTestXInterface(const CString &strDeviceSN);

};

