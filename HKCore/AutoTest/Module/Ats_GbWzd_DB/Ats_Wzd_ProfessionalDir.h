//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Ats_Wzd_ProfessionalDir.h  CAts_Wzd_ProfessionalDir

#pragma once

#include "AtsGbWizrdGlobal.h"



class CAts_Wzd_ProfessionalDir : public CExBaseObject
{
public:
	CAts_Wzd_ProfessionalDir();
	virtual ~CAts_Wzd_ProfessionalDir();

	//m_strName��ProfessionName��רҵ����
	//m_strID��ProfessionID��רҵ��ʶ
	long  m_nHasULevel;
	long  m_nIndex_Profession;
//���غ���
public:
	virtual UINT GetClassID() {    return ATSGBWIZRDCLASSID_CATS_WZD_PROFESSIONALDIR;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_ProfessionalDirKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Profession;     }
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_ProfessionalDirKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::Index_ProfessionKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Profession);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Profession = pRecordset->GetInsertId();     }

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

