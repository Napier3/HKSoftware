//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIBaseAxis.h  CUIBaseAxis

#pragma once

#include "UIBaseGlobal.h"


#include "UIBaseFont.h"

class CUIBaseAxis : public CExBaseList
{
public:
	CUIBaseAxis();
	virtual ~CUIBaseAxis();


	long  m_nRangeMin;
	long  m_nRangeMax;
	long  m_nScaleType;
	long  m_nScaleMinPixel;
	long  m_nUseHalfScale;
	long  m_nUseTenthScale;
	COLORREF  m_crBkColorFrom;
	COLORREF  m_crBkColorTo;
	COLORREF  m_crScaleColor;
	COLORREF  m_crScaleShadowColor;
//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIBASEAXIS;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIBaseAxisKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:
	CUIBaseFont *m_pTitleFont;
	CUIBaseFont *m_pScaleFont;

//私有成员变量访问方法
public:
};

