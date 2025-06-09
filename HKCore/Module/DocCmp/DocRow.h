//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DocRow.h  CDocRow

#pragma once

#include "DocCmpGlobal.h"


#include "DocCel.h"

class CDocRow : public CExBaseList
{
public:
	CDocRow();
	virtual ~CDocRow();


	float  m_fWidth;
	float  m_fHeigh;
//���غ���
public:
	virtual UINT GetClassID() {    return DOCMPCLASSID_CDOCROW;   }
	virtual BSTR GetXmlElementKey()  {      return CDocCmpXmlRWKeys::CDocRowKey();     }
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

//˽�г�Ա�������ʷ���
public:
	void SetCmpError();
	void Cmp(CDocRow *pRef);
	
};

