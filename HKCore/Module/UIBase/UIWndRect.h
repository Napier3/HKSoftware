//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIWndRect.h  CUIWndRect

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowBase.h"


class CUIWndRect :public CStatic, public CUIWindowBase
{
public:
	CUIWndRect();
	virtual ~CUIWndRect();


	COLORREF  m_crPenColor;
	CString  m_strPenStype;
	long  m_nPenWidth;
	COLORREF  m_crBrushColor;
//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDRECT;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndRectKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual BOOL CanPaste(UINT nClassID);
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

//˽�г�Ա����
private:

//˽�г�Ա�������ʷ���
public:
	virtual BOOL UICreate(CWnd *pParent);
	virtual BOOL Destroy();
};

