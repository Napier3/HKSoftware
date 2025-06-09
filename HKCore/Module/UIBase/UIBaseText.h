//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWindowText.h  CUIWindowText

#pragma once

#include "UIBaseGlobal.h"



class CUIWindowText : public CExBaseObject
{
public:
	CUIWindowText();
	virtual ~CUIWindowText();


	COLORREF  m_crForeColor;
	COLORREF  m_crBackColor;
	COLORREF  m_crDisableColor;
	COLORREF  m_crHighLightColor;
	CString  m_strText;

//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWINDOWTEXT;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWindowTextKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();

//私有成员变量
private:

//私有成员变量访问方法
public:
};

