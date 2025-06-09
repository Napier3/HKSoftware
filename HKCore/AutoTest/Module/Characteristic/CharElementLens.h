//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//CharElementLens.h  CCharElementLens

#pragma once

#include "CharElementArc.h"



class CCharElementLens : public CCharElement
{
public:
	CCharElementLens();
	virtual ~CCharElementLens();


	CString  m_strForwardReach;
	CString  m_strAngle;
	CString  m_strOffset;
	CString  m_strWidth;

	double  m_fForwardReach;
	double  m_fAngle;
	double  m_fOffset;
	double  m_fWidth;

//重载函数
public:
	virtual UINT GetClassID() {    return CHARCLASSID_CCHARELEMENTLENS;   }
	virtual BSTR GetXmlElementKey()  {      return CCharacteristicXmlRWKeys::CCharElementLensKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);

	virtual CString ReturnXml();
	virtual void SetTestPoint(long nPoints);

//私有成员变量
private:
	CCharElementArc m_oCharElementArc1, m_oCharElementArc2;

//私有成员变量访问方法
public:
	virtual void CalByExpression(BOOL bCalLines, CExBaseList *pDrawList);
	virtual void CalTestLines(UINT nTestLineMode);

	CCharElementArc* GetCharElementArc1()	{	return &m_oCharElementArc1;	}
	CCharElementArc* GetCharElementArc2()	{	return &m_oCharElementArc2;	}
	virtual CXDrawBase* CreateDrawElement()	;
};

