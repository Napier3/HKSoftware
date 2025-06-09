//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//PpPrjDevice.h  CPpPrjDevice

#pragma once

#include "PpPrjGlobal.h"
#include "../../../Module/DataMngr/DvmDevice.h"
#include "../MqttPpTemplate/MqttPpTemplate.h"
#include "../SensorProtocol/SttGlobalSensorDef.h"

#define ATS_DEVICE_TEST_PROGRESS_NOTBEGIN		0
#define ATS_DEVICE_TEST_PROGRESS_WAITING		1
#define ATS_DEVICE_TEST_PROGRESS_HASREPORT		2
#define ATS_DEVICE_TEST_PROGRESS_TIMEOUT		3

class CPpPrjDevice : public CExBaseList
{
public:
	CPpPrjDevice();
	virtual ~CPpPrjDevice();


	CString  m_strTemplate_File;
	CString  m_strDdvm_File;

	SYSTEMTIME m_tmUpdate;//ʵʱ���ݸ���ʱ��
	CDvmDataset *m_pReadAinDs;
//���غ���
public:
	virtual UINT GetClassID() {    return MNGRCLASSID_CPPPRJDEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CPpPrjXmlRWKeys::CPpPrjDeviceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

private:
	DWORD m_dwStartTime;	//��ʱ��ʱʱ��
	long m_nTimeOut;		//��ʱ��-1���޳�ʱ
	long m_nTestProgress;	//����״̬��0��δ������ʱ��1���ȴ����棬2�����б��棬3����ʱ�ޱ���

public:
	void SetTestProgress_NoStart();
	void SetTestProgress_Start(DWORD dwStartTime,long nTimeOut);
	void SetTestProgress_HasReport();
	void SetTestProgress_TimeOut();
	BOOL IsTestProgress_HasReport();
	BOOL IsTestProgress_Finish(DWORD dwCurTime);

	CString GetTestResult(){return _T("�ϸ�");}

//˽�г�Ա�������ʷ���
public:
	CExBaseObject *m_pRefEngineData;	//����CSttMqttCmdExec����
	CDvmDevice m_oDvmDevice;			//����ģ�Ͷ���
	CMqttPpProcedure *m_pCurProcedure;	//��ǰִ�й��̶���

//���Ա������ʷ���
public:
	void Init(CExBaseObject *pRefEngineData,const CString &strReadAinDsID);
	long GetTimeout();
	BOOL RunProcedure(CMqttPpProcedure *pCurProcedure,CMqttPpProduce *pProduce);
	BOOL ProcessRecvPacket(CMqttPpTemplate *pMqttPpTemplate,char *pBuf,long nLen);
	void UpdateDataset(CDvmDataset *pSrcDataset);
	void UpdateDataset2(CDvmDataset *pDestDataset);
	void UpdateReportFile(long nRslt,CDvmDataset *pModelDataset);
	CString GetRTDataInfo();
};

