//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLinep.h  CCharElementLinep

#pragma once

#include "CharElementLineBase.h"

class CCharElementLinep : public CCharElementLineBase
{
public:
	CCharElementLinep();
	virtual ~CCharElementLinep();


	CString  m_strZ;
	CString  m_strPh;
	CString  m_strAngle;
	
//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTLINEP;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementLinepKey();     }
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
private:

//私有成员变量访问方法
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);

};

