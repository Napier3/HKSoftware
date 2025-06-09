//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RtDataDevice.h  CIot_RtDataDevice

#pragma once

#include "Iot_AtsMngrGlobal.h"



class CIot_RtDataDevice : public CExBaseObject
{
public:
	CIot_RtDataDevice();
	virtual ~CIot_RtDataDevice();


	long  m_nIndex_Sample_Data;
	long  m_nIndex_Sample;
	CString  m_strNumber_Sample_Dev;
	CString  m_strSn_Sample_Dev;
	SYSTEMTIME  m_tmTime;
	long  m_nIndex_Data1;
	CString  m_strValue_Data1;
	long  m_nIndex_Data2;
	CString  m_strValue_Data2;
	long  m_nIndex_Data3;
	CString  m_strValue_Data3;
	long  m_nIndex_Data4;
	CString  m_strValue_Data4;
	long  m_nIndex_Data5;
	CString  m_strValue_Data5;
	long  m_nIndex_Data6;
	CString  m_strValue_Data6;
	long  m_nIndex_Data7;
	CString  m_strValue_Data7;
	long  m_nIndex_Data8;
	CString  m_strValue_Data8;
	long  m_nIndex_Data9;
	CString  m_strValue_Data9;
	long  m_nIndex_Data10;
	CString  m_strValue_Data10;
	long  m_nIndex_Data11;
	CString  m_strValue_Data11;
	long  m_nIndex_Data12;
	CString  m_strValue_Data12;
	long  m_nIndex_Data13;
	CString  m_strValue_Data13;
	long  m_nIndex_Data14;
	CString  m_strValue_Data14;
	long  m_nIndex_Data15;
	CString  m_strValue_Data15;
	long  m_nIndex_Data16;
	CString  m_strValue_Data16;
	long  m_nIndex_Data17;
	CString  m_strValue_Data17;
	long  m_nIndex_Data18;
	CString  m_strValue_Data18;
	long  m_nIndex_Data19;
	CString  m_strValue_Data19;
	long  m_nIndex_Data20;
	CString  m_strValue_Data20;
	long  m_nIndex_Data21;
	CString  m_strValue_Data21;
	long  m_nIndex_Data22;
	CString  m_strValue_Data22;
	long  m_nIndex_Data23;
	CString  m_strValue_Data23;
	long  m_nIndex_Data24;
	CString  m_strValue_Data24;
	long  m_nIndex_Data25;
	CString  m_strValue_Data25;
	long  m_nIndex_Data26;
	CString  m_strValue_Data26;
	long  m_nIndex_Data27;
	CString  m_strValue_Data27;
	CString  m_strIndex_Data28;
	CString  m_strValue_Data28;
	long  m_nIndex_Data29;
	CString  m_strValue_Data29;
	long  m_nIndex_Data30;
	CString  m_strValue_Data30;
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_RTDATADEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_RtDataDeviceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Sample_Data;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_RtDataDeviceKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_Sample_DataKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Sample_Data);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Sample_Data = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

