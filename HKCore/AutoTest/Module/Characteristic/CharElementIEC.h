//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//CharElementIEC.h  CCharElementIEC

#pragma once

#include "CharElementInverse.h"



class CCharElementIEC : public CCharElementInverse
{
public:
	CCharElementIEC();
	virtual ~CCharElementIEC();


	CString  m_strTp;
	CString  m_strK;
	CString  m_strAlpha;

	double  m_fTp;
	double  m_fK;
	double  m_fAlpha;

//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTIEC;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementIECKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CString ReturnXml();
	virtual void Draw(CDC *pDC);


//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	virtual void CalTestLines(UINT nTestLineMode);

	virtual double CalInverse(double dVal);
};

