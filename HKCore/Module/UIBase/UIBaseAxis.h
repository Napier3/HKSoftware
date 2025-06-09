//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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
//���غ���
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

//˽�г�Ա����
private:
	CUIBaseFont *m_pTitleFont;
	CUIBaseFont *m_pScaleFont;

//˽�г�Ա�������ʷ���
public:
};

