//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_RtDataTestApp.h  CIot_RtDataTestApp

#pragma once

#include "Iot_AtsMngrGlobal.h"



class CIot_RtDataTestApp : public CExBaseObject
{
public:
	CIot_RtDataTestApp();
	virtual ~CIot_RtDataTestApp();


	long  m_nIndex_Testapp_Data;
	long  m_nIndex_Testapp;
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
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_RTDATATESTAPP;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_RtDataTestAppKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Testapp_Data;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_RtDataTestAppKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_Testapp_DataKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Testapp_Data);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Testapp_Data = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

