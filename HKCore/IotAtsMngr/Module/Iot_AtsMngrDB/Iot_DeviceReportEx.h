//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_DeviceHisTest.h  CIot_DeviceReportEx

#pragma once

#include "Iot_AtsMngrGlobal.h"

class CIot_DeviceReportEx : public CExBaseObject
{
public:
	CIot_DeviceReportEx();
	virtual ~CIot_DeviceReportEx();


	long  m_nIndex_Device_Histest;
	long  m_nIndex_RptEx;
	CString  m_strDoc_File;
	CString  m_strDoc_File_S;
	CString  m_strPdf_File;
	CString  m_strPdf_File_S;
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_DEVICEREPORTEX;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_DeviceReportExKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_RptEx;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_DeviceReportExKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::IndexRptExKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_RptEx);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_RptEx = pRecordset->GetInsertId();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL UpdateDeviceReportEx(CXDbBaseLib *pXDbLib);
// 	void SetTestType(const CString &strTestType);

// 	BOOL UpdateAttrs(const CString &strTestType,CJSON *pArrData);
//	void UpdateAttr(const CString &strID,const CString &strValue);
};

