//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_TestApp.h  CIot_TestApp

#pragma once

#include "Iot_AtsMngrGlobal.h"



class CIot_TestApp : public CExBaseObject
{
public:
	CIot_TestApp();
	virtual ~CIot_TestApp();


	long  m_nIndex_Testapp;
	long  m_nIndex_Dept;
	long  m_nIndex_Device_Classify;
	long  m_nIndex_Device_Type;
	long  m_nIndex_Factory;
	long  m_nIndex_Engine;
	CString  m_strIp;
	long  m_nPort;
	long  m_nIndex_Model;
	long  m_nTest_State;    //����״̬��  0-���У�1-������
	long  m_nConnect_State; //����״̬��  0-δ���ӣ�1-������
	SYSTEMTIME  m_tmCreate_Time;
	long m_nIsUpdate;// ����ĸ��������Ƿ��Ѹ��¡�һ�����ʹ�ö�Σ���ֻ���ۼ�ʹ������+1
	long m_nUseDays;   //�����ʹ��������ÿ��1��1��0������
	long m_nUseDaysAll;  //�ܵ�ʹ������
	long m_nUseCounts;  //��ʹ�ô���
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_TESTAPP;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_TestAppKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Testapp;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TestAppKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_TestappKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Testapp);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Testapp = pRecordset->GetInsertId();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL QueryByDeviceSN(CXDbBaseLib *pXDbLib,const CString &strDeviceSN);
};

