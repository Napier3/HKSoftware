//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_TypeTaskTest.h  CIot_TypeTaskTest

#pragma once

#include "Iot_AtsMngrGlobal.h"


//������Լ�¼��
class CIot_TypeTaskTest : public CExBaseObject
{
public:
	CIot_TypeTaskTest();
	virtual ~CIot_TypeTaskTest();


	long  m_nIndex_Test;
	long  m_nIndex_Task;
	CString  m_strSn_Sample_Dev;
	CString  m_strSn_Items;
	CString  m_strRpt_File;
	CString  m_strRpt_File_S;
	long  m_nFinal_Report;
	long  m_nIndex_Bench;
	CString  m_strId_User;
	long  m_nState;   //���Լ�¼�Ĳ���״̬: 0-�����ԣ�1-�����쳣��2-�����жϣ�3-�����У�4-�������-���ϸ�5-�������-�ϸ�
	SYSTEMTIME  m_tmTime_Test_Start;
	SYSTEMTIME  m_tmTime_Test_End;
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_TYPETASKTEST;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Test;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_TestKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Test);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Test = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class CIot_TypeTaskTests : public CExBaseList
{
public:
	CIot_TypeTaskTests();
	virtual ~CIot_TypeTaskTests();


	//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_TYPETASKTESTS;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestsKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskTestKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:

	//���Ա������ʷ���
public:
	BOOL QueryAllTaskTests_FinalRpt(CXDbBaseLib *pXDbLib, long nIndex_Task);
};