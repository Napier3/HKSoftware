//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_DeviceHisTest.h  CIot_DeviceHisTest

#pragma once

#include "Iot_AtsMngrGlobal.h"

//ҵ����ԣ�Э��һ���Բ��ԣ�MQTT����
#define DEVICE_TEST_TYPE_SERVICE		0		
#define DEVICE_TEST_TYPE_PROTOCOL		1
#define DEVICE_TEST_TYPE_MQTTPROTOCOL	2

#define TEST_TYPE_IOT		_T("IOT")		
#define TEST_TYPE_MQTT		_T("MQTT")	

class CIot_DeviceHisTest : public CExBaseObject
{
public:
	CIot_DeviceHisTest();
	virtual ~CIot_DeviceHisTest();


	long  m_nIndex_Device_Histest;
	long  m_nIndex_Device;
	long  m_nIndex_User;
	long  m_nIndex_Test_Task;
	SYSTEMTIME  m_tmTm_Begin;
	SYSTEMTIME  m_tmTm_End;
	CString  m_strDoc_File;
	CString  m_strDoc_File_S;
	CString  m_strPdf_File;
	CString  m_strPdf_File_S;
	CString  m_strGbrpt_File;
	CString  m_strGbrpt_File_S;
	CString  m_strPcap_File;
	CString  m_strPcap_File_S;
	CString  m_strRpt_Data_File;
	CString  m_strRpt_Data_File_S;
	CString  m_strRpt_Data_File_Format;
	long  m_nReport_Result;
	long  m_nTest_Type;

	CString m_strLoginName;//������Ա��¼�û���
	CString m_strDeviceSN;
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_DEVICEHISTEST;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_DeviceHisTestKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Device_Histest;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_DeviceHisTestKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_Device_HistestKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Device_Histest);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Device_Histest = pRecordset->GetInsertId();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL UpdateDeviceHisTest(CXDbBaseLib *pXDbLib);
	void SetTestType(const CString &strTestType);

	BOOL UpdateAttrs(const CString &strTestType,CJSON *pArrData);
	void UpdateAttr(const CString &strID,const CString &strValue);
};

