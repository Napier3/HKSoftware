//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Ats_Wzd_DeviceType.h  CAts_Wzd_DeviceType

#pragma once

#include "AtsGbWizrdGlobal.h"



class CAts_Wzd_DeviceType : public CExBaseObject
{
public:
	CAts_Wzd_DeviceType();
	virtual ~CAts_Wzd_DeviceType();

	//m_strName��DeviceTypeName��װ���������ƣ�
	//m_strID��DeviceTypeID��װ�����ͱ�ʶ��
	long  m_nIndex_Profession;
	long  m_nIndex_DeviceType;
//���غ���
public:
	virtual UINT GetClassID() {    return ATSGBWIZRDCLASSID_CATS_WZD_DEVICETYPE;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_DeviceTypeKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_DeviceType;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_DeviceTypeKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::Index_DeviceTypeKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_DeviceType);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_DeviceType = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

