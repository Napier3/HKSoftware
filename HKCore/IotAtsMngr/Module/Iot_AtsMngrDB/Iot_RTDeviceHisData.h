//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RTDeviceHisData.h  CIot_RTDeviceHisData

#pragma once

#include "Iot_AtsMngrGlobal.h"

//被测设备+测试仪的历史实时数据表
//需要刻画测试曲线图时，需要的数据放到该表中
//每一次更新时，都往库里面添加记录

class CIot_RTDeviceHisData : public CExBaseObject
{
public:
	CIot_RTDeviceHisData();
	virtual ~CIot_RTDeviceHisData();


	long  m_nIndex_His_Data;
	CString  m_strSn;
	SYSTEMTIME  m_tmTm_Update;
	//需要画曲线图的数据，才需要放到该历史实时表中，此处先预留10个
	float m_fValue1;
	float m_fValue2;
	float m_fValue3;
	float m_fValue4;
	float m_fValue5;
	float m_fValue6;
	float m_fValue7;
	float m_fValue8;
	float m_fValue9;
	float m_fValue10;

	//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_RTDEVICEHISDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_RTDeviceHisDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_His_Data;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_RTDeviceHisDataKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_His_DataKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_His_Data);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_His_Data = pRecordset->GetInsertId();     }

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	void UpdateValue(const CString &strData, const CString &strValue);
};

