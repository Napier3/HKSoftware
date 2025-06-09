//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Ats_RTDevice.h  CAts_RTDevice

#pragma once

#include "ATSMNGRGlobal.h"

#define ATS_DEVICE_TEST_PROGRESS_NOTBEGIN		0
#define ATS_DEVICE_TEST_PROGRESS_WAITING		1
#define ATS_DEVICE_TEST_PROGRESS_HASREPORT		2
#define ATS_DEVICE_TEST_PROGRESS_TIMEOUT		3

class CAts_RTDevice : public CExBaseList
{
public:
	CAts_RTDevice();
	virtual ~CAts_RTDevice();


	long  m_nIndex_Device;
	long  m_nIndex_TaskBatch;
	long  m_nIndex_Task;
	CString  m_strDeviceTypeName;
	CString  m_strDeviceTypeID;
	long  m_nTestBatch;
//重载函数
public:
	virtual UINT GetClassID() {    return ATSCLASSID_CATS_RTDEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CATSMNGRXmlRWKeys::CAts_RTDeviceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Device;     }
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CATSMNGRXmlRWKeys::CAts_RTDeviceKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CATSMNGRXmlRWKeys::Index_DeviceKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Device);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Device = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//私有成员变量
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
};

