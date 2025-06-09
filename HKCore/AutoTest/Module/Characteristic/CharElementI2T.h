//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementI2T.h  CCharElementI2T

#pragma once

#include "CharElementInverse.h"



class CCharElementI2T : public CCharElementInverse
{
public:
	CCharElementI2T();
	virtual ~CCharElementI2T();

	CString  m_strTp;
	CString  m_strA;

	double  m_fTp;
	double  m_fA;

//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTI2T;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementI2TKey();     }
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

//私有成员变量访问方法
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	virtual double CalInverse(double dVal);
};

