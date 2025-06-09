//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Ats_Wzd_InterVal.h  CAts_Wzd_InterVal

#pragma once

#include "AtsGbWizrdGlobal.h"


//�������
class CAts_Wzd_InterVal : public CExBaseObject
{
public:
	CAts_Wzd_InterVal();
	virtual ~CAts_Wzd_InterVal();

	//m_strID��InterValID�� ���ID
	long  m_nIndex_InterVal;
	long  m_nIndex_Station;

	//m_strID��InterValID ��¼�������
//���غ���
public:
	virtual UINT GetClassID() {    return ATSGBWIZRDCLASSID_CATS_WZD_INTERVAL;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_InterValKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_InterVal;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_InterValKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::Index_InterValKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_InterVal);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_InterVal = pRecordset->GetInsertId();     }
	virtual BOOL DB_SetForeignKeyValue_Own(CXmlRWKeys *pXmlRWKeys, CXDb_PKeyValue &oPKeyValue);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

