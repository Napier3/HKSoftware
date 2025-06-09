//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Ats_Wzd_TempFolder.h  CAts_Wzd_TempFolder

#pragma once

#include "AtsGbWizrdGlobal.h"


#include "Ats_Wzd_TemplateUnit.h"

class CAts_Wzd_TempFolder : public CExBaseList
{
public:
	CAts_Wzd_TempFolder();
	virtual ~CAts_Wzd_TempFolder();

	//m_strName��Name��Ŀ¼��Ϣ
	long  m_nIndex_Folder;
	long  m_nIndex_ParentFolder;
	long m_nSelect;
//���غ���
public:
	virtual UINT GetClassID() {    return ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDER;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_TempFolderKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CBaseObject* CloneEx(BOOL bCopyOwn=TRUE, BOOL bCopyChildren=FALSE);
	virtual void Db_GetPkeyValue(CXDb_PKeyValue &oPKeyValue)  {      oPKeyValue = &m_nIndex_Folder;     }
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_TempFolderKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_TempFolderKey();     }
	virtual BSTR DB_GetPrimaryKey(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::Index_FolderKey();     }
	virtual CString DB_GetPrimaryKeyValue()  {	CString strVal;	strVal.Format(_T("%d"),m_nIndex_Folder);	return strVal;  }
	virtual long DB_ReadFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual long DB_WriteFields(CXDbRecordsetBase *pRecordset, CXmlRWKeys *pXmlRWKeys);
	virtual void DB_UpdatePrimaryKeyValue(CXDbRecordsetBase *pRecordset)  {      m_nIndex_Folder = pRecordset->GetInsertId();     }
	virtual CExBaseObject* DB_CreateNewChild();

public:
	CAts_Wzd_TempFolder* FindChildFolderByIndex(long nIndex);
	long GetSelect()	{	return m_nSelect;	}
	void SetSelect(long nSelect)	{	m_nSelect = nSelect;	}
	void RemoveAllTemplateUnits();
//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

