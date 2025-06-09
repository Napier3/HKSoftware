//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Ats_RTReport.h  CAts_RTReport

#pragma once

#include "ATSMNGRGlobal.h"



class CAts_RTReport : public CExBaseObject
{
public:
	CAts_RTReport();
	virtual ~CAts_RTReport();


	long  m_nIndex_Report;
	long  m_nIndex_TaskBatch;
	long  m_nIndex_Task;
	CString  m_strDeviceTypeID;
	CString  m_strItemPathID;
	CString  m_strDeviceID;
	SYSTEMTIME  m_tmUpdateTime;
	long  m_nDataLen;
	long  m_nDataPosOfFile;
//���غ���
public:
	virtual UINT GetClassID() {    return ATSCLASSID_CATS_RTREPORT;   }
	virtual BSTR GetXmlElementKey()  {      return CATSMNGRXmlRWKeys::CAts_RTReportKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Report;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CATSMNGRXmlRWKeys::CAts_RTReportKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CATSMNGRXmlRWKeys::Index_ReportKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Report);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Report = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL GenerateValueBlobFile(const CString &strRootPath,const CString &strID,CString &strFile);
};

