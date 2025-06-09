//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_TestTaskDevice.h  CIot_TestTaskDevice

#pragma once

#include "Iot_AtsMngrGlobal.h"



class CIot_TestTaskDevice : public CExBaseObject
{
public:
	CIot_TestTaskDevice();
	virtual ~CIot_TestTaskDevice();


	long  m_nIndex_Test_Device;
	long  m_nIndex_Test_Task;
	long  m_nIndex_Bench;
	long  m_nIndex_Device;
	SYSTEMTIME  m_tmCreate_Time;

	//add by shaolei 20210812
	long m_nTotalItems_Protocol;  //Э��һ���Բ�����Ŀ����
	long m_nTotalItems_Function;   //�������ܲ�����Ŀ����
	long m_nTotalItems;   //�ܵ���Ŀ��
	long m_nCurrItem;   //��ǰ���Ե���Ŀ��ţ���1��ʼ
	long m_nTotalTime;   //Ԥ���ܵĲ���ʱ������λ��s
	long m_nRemainTime;   //Ԥ��ʣ��Ĳ���ʱ������λ��s
	CString m_strDeviceSN;
	CString m_strDeviceState;   //�豸��ǰ�Ѳ�����Ŀ����״̬�� �ϸ�|���ϸ�

//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_TESTTASKDEVICE;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_TestTaskDeviceKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Test_Device;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TestTaskDeviceKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_Test_DeviceKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Test_Device);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Test_Device = pRecordset->GetInsertId();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL QueryDeviceByDeviceSN(CXDbBaseLib *pXDbLib,const CString &strDeviceSN);
};

