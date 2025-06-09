//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_Monitor.h  CIot_Monitor

#pragma once

#include "Iot_AtsMngrGlobal.h"

//ʵ���һ���������ݱ�
//���е�ÿһ����¼����Ӧһ�����ָ��

class CIot_Monitor : public CExBaseObject
{
public:
	CIot_Monitor();
	virtual ~CIot_Monitor();


	long  m_nIndex_Monitor_Data;
	long  m_nIndex_Device;
	long  m_nIndex_SubDept;
	CString m_strDataName;
	CString m_strDataID;
	CString m_strUnit;
	//float m_fValue;
	CString m_strValue; //��Ϊ�ַ����������̸еĴ����������� = 2������ = 1��

	//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_MONITOR;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_MonitorKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Monitor_Data;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_MonitorKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_Monitor_Data_Key();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Monitor_Data);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Monitor_Data = pRecordset->GetInsertId();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL QueryByDeviceIndex(CXDbBaseLib *pXDbLib, long nDeviceIndex);

};

