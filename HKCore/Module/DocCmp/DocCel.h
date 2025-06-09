//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//DocCel.h  CDocCel

#pragma once

#include "DocCmpGlobal.h"

#include "DocText.h"


class CDocCel : public CDocText
{
public:
	CDocCel();
	virtual ~CDocCel();


	long  m_nRow;
	long  m_nCol;
	float  m_fWidth;
	float  m_fHeight;

//���غ���
public:
	virtual UINT GetClassID() {    return DOCMPCLASSID_CDOCCEL;   }
	virtual BSTR GetXmlElementKey()  {      return CDocCmpXmlRWKeys::CDocCelKey();     }
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
	
};

