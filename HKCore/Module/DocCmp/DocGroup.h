//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DocGroup.h  CDocGroup

#pragma once

#include "DocCmpGlobal.h"


#include "DocText.h"
#include "DocTable.h"
#include "../../Module/DataMngr/DataGroup.h"

class CDocGroup : public CExBaseList
{
public:
	CDocGroup();
	virtual ~CDocGroup();


	CString  m_strCmp_Id;
//���غ���
public:
	virtual UINT GetClassID() {    return DOCMPCLASSID_CDOCGROUP;   }
	virtual BSTR GetXmlElementKey()  {      return CDocCmpXmlRWKeys::CDocGroupKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:
	CDataGroup *m_pConfig;
	CExBaseList m_listDocElement;

//˽�г�Ա�������ʷ���
public:
	void SetConfig(CDataGroup *pConfig);
	void AddDocElement(CExBaseObject *pDocElement);
	void Group();

	CDocText* GetTitle();

	void Cmp(CDocGroup *pSrc);
	void SetCmpError();

private:
	CDocGroup* FindChildGroup(CDocGroup *pRef);
	BOOL CmpOwn(CDocGroup *pRef);
	BOOL CmpChildren(CDocGroup *pRef);

	void CmpText(CDocText* pText, long nIndexText, CDocGroup *pSrc);
	void CmpTable(CDocTable* pTable, long nIndexTable, CDocGroup *pSrc);
	void CmpGroup(CDocGroup* pGroup, long nIndexGroup, CDocGroup *pSrc);
};



void doccmp_GroupLevel1(CExBaseList *pDocElementList, CDataGroup *pGroupLevel, CDocGroup *pDocGroupRoot);
void doccmp_GroupLevel1Child(CExBaseList *pDocElementList, CDataGroup *pGroupLevel, CDocGroup *pDocGroupRoot);
void doccmp_AddElementToGroupLevel1(CExBaseList *pDocElementList);
void doccmp_Group(CExBaseList *pDocElementList, CDataGroup *pConfig, CDocGroup *pDocGroupRoot);
