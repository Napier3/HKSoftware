//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

	SYSTEMTIME m_tmUpdate;//实时数据更新时间
	CDvmDataset *m_pReadAinDs;
//重载函数
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
	DWORD m_dwStartTime;	//超时计时时间
	long m_nTimeOut;		//超时，-1无限超时
	long m_nTestProgress;	//测试状态：0：未启动计时，1：等待报告，2：已有报告，3：超时无报告

public:
	void SetTestProgress_NoStart();
	void SetTestProgress_Start(DWORD dwStartTime,long nTimeOut);
	void SetTestProgress_HasReport();
	void SetTestProgress_TimeOut();
	BOOL IsTestProgress_HasReport();
	BOOL IsTestProgress_Finish(DWORD dwCurTime);

	CString GetTestResult(){return _T("合格");}

//私有成员变量访问方法
public:
	CExBaseObject *m_pRefEngineData;	//关联CSttMqttCmdExec对象
	CDvmDevice m_oDvmDevice;			//数据模型对象
	CMqttPpProcedure *m_pCurProcedure;	//当前执行过程对象

//属性变量访问方法
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

