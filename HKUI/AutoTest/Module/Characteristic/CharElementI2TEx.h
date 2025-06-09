
#pragma once

#include "CharElementInverse.h"


class CCharElementI2TEx : public CCharElementInverse
{
public:
	CCharElementI2TEx();
	virtual ~CCharElementI2TEx();

	CString  m_strA;
	CString  m_strP;
	CString  m_strQ;
	CString  m_strTp;


	double  m_fA;
	double  m_fP;
	double  m_fQ;
	double  m_fTp; //D

//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTI2TEx;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementI2TExKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CString ReturnXml();
	virtual void Draw(CDC *pDC);


//私有成员变量
protected:
	virtual BOOL IncreaseX(double &dValX);
	virtual void CalInversePolyline();

//私有成员变量访问方法
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	virtual double CalInverse(double dVal);
};

