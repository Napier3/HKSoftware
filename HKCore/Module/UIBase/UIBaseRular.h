//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIBaseRular.h  CUIBaseRular

#pragma once

#include "UIBaseGlobal.h"



class CUIBaseRular : public CExBaseObject
{
public:
	CUIBaseRular();
	virtual ~CUIBaseRular();


	COLORREF  m_crBkColor;
	COLORREF  m_crScaleColor;
	COLORREF  m_crScaleShadowColor;
	COLORREF  m_crTenthScaleColor;
	COLORREF  m_crBorderColor;
	COLORREF  m_crTextColor;
	long  m_nDrawBorder;
	long  m_nDrawHalfScale;
	long  m_nDrawTenthScale;
//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIBASERULAR;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIBaseRularKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
};

