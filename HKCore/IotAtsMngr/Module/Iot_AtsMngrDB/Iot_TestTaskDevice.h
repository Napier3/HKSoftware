//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_TestTaskDevice.h  CIot_TestTaskDevice

#pragma once

#include "Iot_AtsMngrGlobal.h"



class CIot_TestTaskDevice : public CExBaseObject
{
public:
	CIot_TestTaskDevice();
	virtual ~CIot_TestTaskDevice();


	long  m_nIndex_Test_Device;
	long  m_nIndex_Test_Task;
	long  m_nIndex_Bench;
	long  m_nIndex_Device;
	SYSTEMTIME  m_tmCreate_Time;

	//add by shaolei 20210812
	long m_nTotalItems_Protocol;  //协议一致性测试项目总数
	long m_nTotalItems_Function;   //功能性能测试项目总数
	long m_nTotalItems;   //总的项目数
	long m_nCurrItem;   //当前测试的项目编号，从1开始
	long m_nTotalTime;   //预计总的测试时长，单位：s
	long m_nRemainTime;   //预计剩余的测试时长，单位：s
	CString m_strDeviceSN;
	CString m_strDeviceState;   //设备当前已测试项目的总状态： 合格|不合格

//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_TESTTASKDEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_TestTaskDeviceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Test_Device;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TestTaskDeviceKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_Test_DeviceKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Test_Device);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Test_Device = pRecordset->GetInsertId();     }

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL QueryDeviceByDeviceSN(CXDbBaseLib *pXDbLib,const CString &strDeviceSN);
};

