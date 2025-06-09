
#pragma once

#include "CharElementInverse.h"


class CCharElementDCOverLoad : public CCharElementInverse
{
public:
	CCharElementDCOverLoad();
	virtual ~CCharElementDCOverLoad();

	CString  m_strIb;
	CString  m_strK;
	CString  m_strConstant;
	
	double  m_fIb;
	double  m_fK;
	double  m_fConstant;
	
//���غ���
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTDCOVERLOAD;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementDCOverLoadKey();     }
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

