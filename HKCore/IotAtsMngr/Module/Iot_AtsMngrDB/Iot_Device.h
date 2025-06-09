//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_Device.h  CIot_Device

#pragma once

#include "Iot_AtsMngrGlobal.h"

//设备的类型，是被测样品还是环境监测设备
#define DEVICE_TYPE_MONITOR  _T("Monitor")
#define DEVICE_TYPE_TEST     _T("Test")

//设备分类类型
#define DEVICE_CLASSIFY_TYPE_WSD   _T("WSD")   //无线温湿度传感器
#define DEVICE_CLASSIFY_TYPE_YG   _T("YG")   //烟感传感器
#define DEVICE_CLASSIFY_TYPE_ZS   _T("ZS")   //噪声传感器

class CIot_Device : public CExBaseObject
{
public:
	CIot_Device();
	virtual ~CIot_Device();


	long  m_nIndex_Device;
	long  m_nIndex_Device_Classify;
	long  m_nIndex_Device_Type;
	long  m_nIndex_Factory;
	long  m_nIndex_Dept;
	CString  m_strIp;
	long  m_nPort;
	long  m_nIndex_Engine;
	long  m_nIndex_Model;
	long  m_nIndex_Device_Dir;
	long  m_nTest_State;
	SYSTEMTIME  m_tmCreate_Time;
	long m_nTest_Rslt;  //测试结论  0-未测试；1-测试合格；2-测试不合格 
	CString m_strDeviceType;  //设备类型，是环境监测设备还是被测样品
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_DEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_DeviceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Device;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_DeviceKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_DeviceKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Device);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Device = pRecordset->GetInsertId();     }

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL QueryByDeviceSN(CXDbBaseLib *pXDbLib,const CString &strDeviceSN);
	BOOL IsMonitorDevice();
};

