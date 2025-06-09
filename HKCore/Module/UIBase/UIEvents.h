//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIEvents.h  CUIEvents

#pragma once

#include "UIBaseGlobal.h"


#include "UIEvent.h"

class CUIEvents : public CExBaseList
{
public:
	CUIEvents();
	virtual ~CUIEvents();


//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIEVENTS;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIEventsKey();     }
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

//私有成员变量
private:
	CUIEvent *m_pEvent_OnArrowUp;
	CUIEvent *m_pEvent_OnArrowDown;
	CUIEvent *m_pEvent_OnArrowLeft;
	CUIEvent *m_pEvent_OnArrowRight;
	CUIEvent *m_pEvent_OnSetFoucus;
	CUIEvent *m_pEvent_OnKillFoucus;
	CUIEvent *m_pEvent_OnEditChanged;
	CUIEvent *m_pEvent_OnSelChanged;
	CUIEvent *m_pEvent_OnDropDown;
	CUIEvent *m_pEvent_OnClick;
	CUIEvent *m_pEvent_OnDbClick;
	CUIEvent *m_pEvent_OnShow;
	CUIEvent *m_pEvent_OnHide;
	CUIEvent *m_pEvent_OnCheck;
	CUIEvent *m_pEvent_OnPreLoad;
	CUIEvent *m_pEvent_OnLoad;
	CUIEvent *m_pEvent_OnUnload;
	CUIEvent *m_pEvent_OnPreCreate;
	CUIEvent *m_pEvent_OnCreate;

	BOOL SetEvent(CUIEvent *pEvent);

//私有成员变量访问方法
public:
	void Event_OnArrowUp();
	void Event_OnArrowDown();
	void Event_OnArrowLeft();
	void Event_OnArrowRight();
	void Event_OnSetFoucus();
	void Event_OnKillFoucus();
	void Event_OnEditChanged();
	void Event_OnSelChanged();
	void Event_OnDropDown();
	void Event_OnClick();
	void Event_OnDbClick();
	void Event_OnShow();
	void Event_OnHide();
	void Event_OnCheck();
	void Event_OnPreLoad();
	void Event_OnLoad();
	void Event_OnUnload();
	void Event_OnPreCreate();
	void Event_OnCreate();

};

