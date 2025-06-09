
#pragma once

#include "CharElementInverse.h"


class CCharElementRXIDG : public CCharElementInverse
{
public:
	CCharElementRXIDG();
	virtual ~CCharElementRXIDG();

	CString  m_strTp;

	double  m_fTp;	
	
//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTRXIDG;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementRXIDGKey();     }
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
protected:
	virtual BOOL IncreaseX(double &dValX);
	virtual void CalInversePolyline();

//˽�г�Ա�������ʷ���
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	virtual double CalInverse(double dVal);
};

