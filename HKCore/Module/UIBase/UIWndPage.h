//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

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

//���غ���
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

//˽�г�Ա����
private:
	CString m_strPageFile;

//˽�г�Ա�������ʷ���
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

	//����
	CUIWndLayer* FindLayerByID(LPCTSTR pszLayerID);
	CUIWndLayer* FindLayerByID(const CString &strLayerID);
	CUIWindowBase* FindWindowByID(LPCTSTR pszWindowID);
	CUIWindowBase* FindWindowByID(const CString &strWindowID);

	virtual BOOL Destroy();

private:
	CUIWndTabList m_oUIWndTabList;

	//���ݴ��ڶ���Ľ���Tabֵ��Ӵ���,Tabֵ>0�����
	void AddUITabWnd(CUIWindowList *pUIWndList);
	void AddUITabWnd(CUIWindowBase *pUIWnd);

protected:
	//��������
	BOOL    m_bHasCreated;
	BOOL     m_bInClosedState;//Page�Ĺر�״̬

	//���ڵĴ���/���ٷ���
	virtual BOOL UICreate(CWnd *pParent);

public:

};

