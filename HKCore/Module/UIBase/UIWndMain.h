//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndMain.h  CUIWndMain

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowList.h"
#include "UIWndPage.h"
#include "UIWndPagesDef.h"

class CUIWndMain : public CUIWindowList
{
public:
	CUIWndMain();
	virtual ~CUIWndMain();

	static CString g_strMainPageFile;
	CString  m_strStartPage;
	long  m_nUseFrame;

//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDMAIN;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndMainKey();     }
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
	CUIWndPagesDef *m_pPagesDef;

	CUIWndPage   *m_pActivePage;//当前的活动页面
	CExBaseList  m_oUIHistoryPage;//显示过的页面对象链表,链表内容为按显示的先后顺序添加的界面Page,类似堆栈,先打开的后关闭

//私有成员变量访问方法
public:
	virtual BOOL Destroy();
	void Load(const CString &strMainPageFile);

	BOOL ClosePage(const CString &strPageID);
	BOOL ClosePage();
	BOOL ClosePage(CUIWndPage *pPage, BOOL bPostExitMsg=TRUE);
	BOOL ShowPage(const CString &strPageID,long nShow);
};

