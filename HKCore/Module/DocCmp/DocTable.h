//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DocTable.h  CDocTable

#pragma once

#include "DocCmpGlobal.h"


#include "DocRow.h"

class CDocTable : public CExBaseList
{
public:
	CDocTable();
	virtual ~CDocTable();


	CString  m_strCmp_Id;
	CString  m_strTxt_Cmp_Id;
//���غ���
public:
	virtual UINT GetClassID() {    return DOCMPCLASSID_CDOCTABLE;   }
	virtual BSTR GetXmlElementKey()  {      return CDocCmpXmlRWKeys::CDocTableKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void SetCmpError();
	void Cmp(CDocTable *pRef);

};

