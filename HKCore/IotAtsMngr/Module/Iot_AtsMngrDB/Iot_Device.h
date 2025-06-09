//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_Device.h  CIot_Device

#pragma once

#include "Iot_AtsMngrGlobal.h"

//�豸�����ͣ��Ǳ�����Ʒ���ǻ�������豸
#define DEVICE_TYPE_MONITOR  _T("Monitor")
#define DEVICE_TYPE_TEST     _T("Test")

//�豸��������
#define DEVICE_CLASSIFY_TYPE_WSD   _T("WSD")   //������ʪ�ȴ�����
#define DEVICE_CLASSIFY_TYPE_YG   _T("YG")   //�̸д�����
#define DEVICE_CLASSIFY_TYPE_ZS   _T("ZS")   //����������

class CIot_Device : public CExBaseObject
{
public:
	CIot_Device();
	virtual ~CIot_Device();


	long  m_nIndex_Device;
	long  m_nIndex_Device_Classify;
	long  m_nIndex_Device_Type;
	long  m_nIndex_Factory;
	long  m_nIndex_Dept;
	CString  m_strIp;
	long  m_nPort;
	long  m_nIndex_Engine;
	long  m_nIndex_Model;
	long  m_nIndex_Device_Dir;
	long  m_nTest_State;
	SYSTEMTIME  m_tmCreate_Time;
	long m_nTest_Rslt;  //���Խ���  0-δ���ԣ�1-���Ժϸ�2-���Բ��ϸ� 
	CString m_strDeviceType;  //�豸���ͣ��ǻ�������豸���Ǳ�����Ʒ
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_DEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_DeviceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Device;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_DeviceKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_DeviceKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Device);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Device = pRecordset->GetInsertId();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL QueryByDeviceSN(CXDbBaseLib *pXDbLib,const CString &strDeviceSN);
	BOOL IsMonitorDevice();
};

