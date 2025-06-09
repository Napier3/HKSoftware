//这段源代码由ClassGenerator创建
//版权所有 LiJunqing  lijunqing1224@126.com
//保留所有权利

//UIWndPage.h  CUIWndPage

#pragma once

#include "UIBaseGlobal.h"

#include "UIWindowList.h"
#include "UIWndLayer.h"


class CUIWndPage : public CUIWindowList
{
public:
	CUIWndPage();
	virtual ~CUIWndPage();


	long  m_nShowChildren;
	long  m_nBringToTop;
	long  m_nTabSysMsg;
	long  m_nBorder;

//重载函数
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWNDPAGE;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWndPageKey();     }
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
	CString m_strPageFile;

//私有成员变量访问方法
public:
	void SetPageFile(const CString &strPageFile)	{	m_strPageFile = strPageFile;	}
	CString GetPageFile()							{	return m_strPageFile;			}
	BOOL LoadPage();
	BOOL ReadPageFromFile(const CString &strPageFile);
	void ClosePage();

	long GetPageWidth();
	void SetPageWidth(long nWidth);
	long GetPageHeight();
	void SetPageHeight(long nHeight);
	void SetPagePosition(long nLeft, long nTop, long nRight, long nBottom);
	void SetPageSize(long nWidth, long nHeight);

	//查找
	CUIWndLayer* FindLayerByID(LPCTSTR pszLayerID);
	CUIWndLayer* FindLayerByID(const CString &strLayerID);
	CUIWindowBase* FindWindowByID(LPCTSTR pszWindowID);
	CUIWindowBase* FindWindowByID(const CString &strWindowID);

	virtual BOOL Destroy();

private:
	CUIWndTabList m_oUIWndTabList;

	//根据窗口定义的焦点Tab值添加窗口,Tab值>0则添加
	void AddUITabWnd(CUIWindowList *pUIWndList);
	void AddUITabWnd(CUIWindowBase *pUIWnd);

protected:
	//自身属性
	BOOL    m_bHasCreated;
	BOOL     m_bInClosedState;//Page的关闭状态

	//窗口的创建/销毁方法
	virtual BOOL UICreate(CWnd *pParent);

public:

};

