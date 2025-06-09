//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//Iot_DeviceHisTest.h  CIot_DeviceOutReport

#pragma once

#include "Iot_AtsMngrGlobal.h"


class CIot_DeviceOutReport : public CExBaseObject
{
public:
	CIot_DeviceOutReport();
	virtual ~CIot_DeviceOutReport();

	long  m_nIndex_Device;
	long  m_nIndex_Rpt;
	CString  m_strDoc_File;
	CString  m_strDoc_File_s;
	CString  m_strPdf_File;
	CString  m_strPdf_File_s;
	CString  m_strPcap_File;
	CString  m_strPcap_File_s;
	CString  m_strRpt_Data_File;
	CString  m_strRpt_Data_File_s;
	CString  m_strRpt_Data_File_Format;
//重载函数
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_DEVICEOUTREPORT;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_DeviceOutReportKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Rpt;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_DeviceOutReportKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::IndexRptKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Rpt);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Rpt = pRecordset->GetInsertId();     }

//私有成员变量
private:

//私有成员变量访问方法
public:

//属性变量访问方法
public:
	BOOL UpdateDeviceOutReport(CXDbBaseLib *pXDbLib);
// 	void SetTestType(const CString &strTestType);
// 
// 	BOOL UpdateAttrs(const CString &strTestType,CJSON *pArrData);
// 	void UpdateAttr(const CString &strID,const CString &strValue);
};

