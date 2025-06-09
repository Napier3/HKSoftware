//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIBaseFont.h  CUIBaseFont

#pragma once

#include "UIBaseGlobal.h"



class CUIBaseFont : public CExBaseObject
{
public:
	CUIBaseFont();
	virtual ~CUIBaseFont();

	static CUIBaseFont g_oUIBaseFont;

public:
	long  m_nSize;
	long  m_nItalic;
	long  m_nBold;
	COLORREF  m_crColor;
	long  m_nEscapement;
	COLORREF  m_crBkColor;

//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIBASEFONT;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIBaseFontKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//˽�г�Ա����
private:
	CFont *m_pFont;

//˽�г�Ա�������ʷ���
public:
	CFont* GetFont();
	LOGFONT GetLogFont();

};

