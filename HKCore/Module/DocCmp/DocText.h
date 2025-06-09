//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DocText.h  CDocText

#pragma once

#include "DocCmpGlobal.h"



class CDocText : public CExBaseObject
{
public:
	CDocText();
	virtual ~CDocText();


	CString  m_strCmp_Id;
	CString  m_strTxt;
	long  m_nStart;
	long  m_nEnd;
	long  m_nError;
//���غ���
public:
	virtual UINT GetClassID() {    return DOCMPCLASSID_CDOCTEXT;   }
	virtual BSTR GetXmlElementKey()  {      return CDocCmpXmlRWKeys::CDocTextKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	void Init();
	void SetCmpError();
	BOOL Cmp(CDocText *pRef);
};

