//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Iot_TypeTaskDevModel.h  CIot_TypeTaskDevModel

#pragma once

#include "Iot_AtsMngrGlobal.h"


//����-��������
class CIot_TypeTaskDevModel : public CExBaseObject
{
public:
	CIot_TypeTaskDevModel();
	virtual ~CIot_TypeTaskDevModel();


	long  m_nIndex_Data;
	long  m_nIndex_Task;
	CString  m_strData_Type;
	CString  m_strValue;
	CString  m_strUnit;
//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_TYPETASKDEVMODEL;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskDevModelKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Data;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskDevModelKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::Index_DataKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Data);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Data = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
	BOOL WriteToDB(CXDbBaseLib *pXDbLib, CDvmData *pData);
};


///////////////////////////////////////////////////////////////////////////////////////////
class CIot_TypeTaskDevModels : public CExBaseList
{
public:
	CIot_TypeTaskDevModels();
	virtual ~CIot_TypeTaskDevModels();


	//���غ���
public:
	virtual UINT GetClassID() {    return IOTCLASSID_CIOT_TYPETASKDEVMODELS;   }
	virtual BSTR GetXmlElementKey()  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskDevModelsKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskDevModelKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CIot_AtsMngrXmlRWKeys::CIot_TypeTaskDevModelKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

	//˽�г�Ա����
private:

	//˽�г�Ա�������ʷ���
public:

	//���Ա������ʷ���
public:
	BOOL QueryTypeTaskDevModels(CXDbBaseLib *pXDbLib, long nIndex_TypeTask);
};