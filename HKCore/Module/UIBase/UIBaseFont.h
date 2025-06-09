//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

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

//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIBASEFONT;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIBaseFontKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:
	CFont *m_pFont;

//私有成员变量访问方法
public:
	CFont* GetFont();
	LOGFONT GetLogFont();

};

