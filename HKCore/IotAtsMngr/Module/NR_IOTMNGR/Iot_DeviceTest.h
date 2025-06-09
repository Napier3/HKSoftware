//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceTest.h  CIot_DeviceTest

#pragma once

#include "NR_IOTMNGRGlobal.h"


#include "Iot_DeviceReportEx.h"

class CIot_DeviceTest : public CExBaseObject
{
public:
	CIot_DeviceTest();
	virtual ~CIot_DeviceTest();


	long  m_nIndex_Device_Test;
	long  m_nIndex_User;
	long  m_nIndex_Bench;
	long  m_nIndex_Devicetype;
	long  m_nIndex_Factory;
	long  m_nIndex_Dept;
	long  m_nIndex_Engine;
	long  m_nIndex_Test;
	SYSTEMTIME  m_tmTm_Begin;
	SYSTEMTIME  m_tmTm_End;
	CString  m_strTemplate_File;
	CString  m_strProtocol_File;
	CString  m_strIecfg_File;
	CString  m_strDvm_File;
	CString  m_strDoc_File;
	CString  m_strPdf_File;
	CString  m_strGbrpt_File;
	CString  m_strRpt_Data_File;
	CString  m_strRpt_Data_File_Format;
	CString  m_strTestapp_Used;
	CString  m_strDeviceclassify;
	CString  m_strModel;
	CString  m_strPcap_File;
	long  m_nReport_Result;
	CString  m_strTemplate_File_S;
	CString  m_strProtocol_File_S;
	CString  m_strIecfg_File_S;
	CString  m_strDvm_File_S;
	CString  m_strDoc_File_S;
	CString  m_strPdf_File_S;
	CString  m_strGbrpt_File_S;
	CString  m_strRpt_Data_File_S;
	CString  m_strPcap_File_S;
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_DEVICETEST;   }
	virtual BSTR GetXmlElementKey()  {      return CNR_IOTMNGRXmlRWKeys::CIot_DeviceTestKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Device_Test;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CNR_IOTMNGRXmlRWKeys::CIot_DeviceTestKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CNR_IOTMNGRXmlRWKeys::CIot_DeviceReportExKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CNR_IOTMNGRXmlRWKeys::Index_Device_TestKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Device_Test);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Device_Test = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
};

