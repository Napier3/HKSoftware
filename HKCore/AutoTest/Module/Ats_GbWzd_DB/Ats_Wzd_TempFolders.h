//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//Ats_Wzd_TempFolders.h  CAts_Wzd_TempFolders

#pragma once

#include "AtsGbWizrdGlobal.h"


#include "Ats_Wzd_TempFolder.h"

class CAts_Wzd_TempFolders : public CExBaseList
{
public:
	CAts_Wzd_TempFolders();
	virtual ~CAts_Wzd_TempFolders();

	long m_nSelect;


//���غ���
public:
	virtual UINT GetClassID() {    return ATSGBWIZRDCLASSID_CATS_WZD_TEMPFOLDERS;   }
	virtual BSTR GetXmlElementKey()  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_TempFoldersKey();     }
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
	virtual BSTR DB_GetOwnTableName(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_TempFolderKey();     }
	virtual BSTR DB_GetChildTableName(CXmlRWKeys *pXmlRWKeys)  {      return CAtsGbWizrdXmlRWKeys::CAts_Wzd_TempFolderKey();     }
	virtual CExBaseObject* DB_CreateNewChild();

public:
	CAts_Wzd_TempFolder* FindFolderByIndex(long nIndex);
	void UpdateFolderByIndex(long nIndex, const CString &strName);
	long GetSelect()	{	return m_nSelect;	}
	void SetSelect(long nSelect)	{	m_nSelect = nSelect;	}
	void RemoveAllTemplateUnits();   //���������Ƴ�����ģ��Ԫ������ֹ��ɾ

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:

//���Ա������ʷ���
public:
};

void AtsWzd_SetTemplateUnitSelectedState(CExBaseList *pList, long nSelect);
void AtsWzd_UpdateTemplateUnitSelectedState(CExBaseList *pList);
void AtsWzd_SetSelect(CExBaseObject *pObj, long nSelect);
long AtsWzd_GetSelect(CExBaseObject *pObj);