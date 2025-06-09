//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementIEEE.h  CCharElementIEEE

#pragma once

#include "CharElementInverse.h"



class CCharElementIEEE : public CCharElementInverse
{
public:
	CCharElementIEEE();
	virtual ~CCharElementIEEE();


	CString  m_strTp;
	CString  m_strA;
	CString  m_strB;
	CString  m_strP;
	CString  m_strQ;
	CString  m_strK1;
	CString  m_strK2;

	double  m_fTp; //D
	double  m_fA;
	double  m_fB;
	double  m_fP;
	double  m_fQ;
	double  m_fK1;
	double  m_fK2;

//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTIEEE;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementIEEEKey();     }
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

