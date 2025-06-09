//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_RTDeviceData.h  CIot_RTDeviceData

#pragma once

#include "Iot_AtsMngrGlobal.h"


//�����豸��ʵʱ���ݱ�ÿ���豸ֻ����һ����¼�������ݹ���ʱ����ˢ��
class CIot_RTDeviceData : public CExBaseObject
{
public:
	CIot_RTDeviceData();
	virtual ~CIot_RTDeviceData();


	long  m_nIndex_Device_Data;
	long  m_nIndex_Device;
	CString  m_strSn;
	CString  m_strData_Format;
	CString  m_strData;
	SYSTEMTIME  m_tmTm_Update;
	long  m_nIs_Warning;
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_RTDEVICEDATA;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_RTDeviceDataKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Device_Data;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_RTDeviceDataKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_Device_DataKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Device_Data);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Device_Data = pRecordset->GetInsertId();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	long ReadFromBuffer(char *pszBuffer);
	long WriteToDB_ByBuffer(char *pszBuffer);

};

