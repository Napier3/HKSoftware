//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIWindowList.h  CUIWindowList

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowBase.h"

class CUIWndListPool;

class CUIWindowList : public CUIWindowBase
{
public:
	CUIWindowList();
	virtual ~CUIWindowList();

	COLORREF  m_crBkColorFrom;
	COLORREF  m_crBkColorTo;
	CString  m_strBkBmpFile;
	CString  m_strType;


//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWINDOWLIST;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWindowListKey();     }
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
	virtual void ShowChildren(long nShow);
	virtual BOOL UICreate(CWnd *pParent);
	virtual BOOL UICreateChildren(CWnd *pParent = NULL);
	virtual BOOL Destroy();
	virtual BOOL DestroyChildren();

protected:
	CUIWndListPool *m_pUIWndListPool;
	CDib *m_pDibBackBitmap;

	void CreateBkBitmap();

};


class CUIWndTabList : public CUIWindowList
{
public:
	CUIWndTabList();
	virtual ~CUIWndTabList();

	void AddUIWindow(CUIWindowBase *pUIWnd);
	CUIWindowBase* OnTabOrder();
	void Release();

private:
	CUIWindowBase *m_pCurrUIWnd;
};