//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementArc.h  CCharElementArc

#pragma once

#include "CharElementArcBase.h"



class CCharElementArc : public CCharElementArcBase
{
public:
	CCharElementArc();
	virtual ~CCharElementArc();


	CString  m_strXCenter;
	CString  m_strYCenter;

// lijq 2020-02-29 数据定义放到 CXDrawData_Arc
// 	double  m_fXCenter;
// 	double  m_fYCenter;
// 	double  m_fXRadius;
// 	double  m_fYRadius;
// 	double  m_fAngleBegin;
// 	double  m_fAngleEnd;

//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTARC;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementArcKey();     }
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
	virtual CXDrawDataBase* GetCXDrawDataBase();
};

