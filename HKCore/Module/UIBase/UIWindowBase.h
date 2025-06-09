//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//UIWindowBase.h  CUIWindowBase

#pragma once

#include "UIBaseGlobal.h"
#include "..\Api\GloblaDrawFunctions.h"

#include "UIEvents.h"
#include "UIBaseFont.h"
#include "UIBaseText.h"

#include "UIWindowBaseInterface.h"

static const CString g_pszKeyOnUIMessage_Show = _T("OnShow");
static const CString g_pszKeyOnUIMessage_Hide = _T("OnHide");

class CUIWindowBase : public CExBaseList//, public CUIWindowBaseInterface
{
public:
	CUIWindowBase();
	virtual ~CUIWindowBase();

	long  m_nTabOrder;
	long  m_nTop;
	long  m_nLeft;
	long  m_nWidth;
	long  m_nHeight;
	CString  m_strAccelMsg;
	long  m_nShow;
	long  m_nEnable;
	long  m_nSysTimerID;
	long  m_nSysOptrID;
	COLORREF  m_crBkColor;
	COLORREF  m_crForeColor;
	COLORREF  m_crFrmTopLeftColor;
	COLORREF  m_crFrmRightBottomColor;
	COLORREF  m_crBkActiveColor;      //����״̬����ɫ
	COLORREF  m_crBkDisableColor;     //ʧЧ����ɫ
	long  m_nFrmSize;

	long m_nWndState;
	long  m_nTransparent;
	COLORREF  m_crTransMaskColor;     //ʧЧ����ɫ

	//�����Ĵ���
// 	CWnd *m_pParentWnd;
	CWnd *m_pWindow;

	static CUIWindowBase *g_pUIWndFocus;

//���غ���
public:
	virtual UINT GetClassID() {    return UICLASSID_CUIWINDOWBASE;   }
	virtual BSTR GetXmlElementKey()  {      return CUIBaseXmlRWKeys::CUIWindowBaseKey();     }
	virtual long XmlReadOwn(CXmlRWNodeBase &oNode, CXmlRWKeys *pXmlRWKeys);
	virtual long XmlWriteOwn(CXmlRWDocBase &oXMLDoc, CXmlRWElementBase &oElement, CXmlRWKeys *pXmlRWKeys);
	virtual long SerializeOwn(CBinarySerialBuffer &oBinaryBuffer);
	virtual void InitAfterRead();
	virtual BOOL IsEqualOwn(CBaseObject* pObj);
	virtual BOOL CopyOwn(CBaseObject* pDest);
	virtual CBaseObject* Clone();
	virtual CExBaseObject* CreateNewChild(const CString &strClassID, BOOL &bAddToTail, CXmlRWKeys *pXmlRWKeys);
	virtual CExBaseObject* CreateNewChild(long nClassID/*, BOOL &bAddToTail*/);

	virtual void UI_KillFoucus();
//˽�г�Ա����
protected:
	CUIBaseFont *m_pFont;      //����
	CUIWindowText *m_pText;   //�ı�
	CUIEvents *m_pMsgEvents;    //��Ϣ

//˽�г�Ա�������ʷ���
public:
	CUIEvent* FindEvent(LPCTSTR pstrID);


//////////////////////////////////////////////////////////////////////////
//CUIWindowBaseInterface
public:
	virtual BOOL IsWindowBase();
	virtual BOOL IsWindowList();
	virtual BOOL IsAncestorPageShow();

	//���ڷ���
	virtual void Show();
	virtual BOOL Show(long nShow);
	virtual void ShowChildren(long nShow);
	virtual BOOL IsShow();

	virtual void Enable(long nEnable, BOOL bEnableWindow=TRUE);
	virtual BOOL IsEnable();

	virtual void SetUIWndFocus(long xOff=5, long yOff=5);
	virtual void ReDrawWnd();
	virtual void SetWndText(CString strWndText);	
	virtual CString GetWndText();
	virtual CUIBaseFont* GetUIBaseFont();	


	//���ڵ�λ�ô�С
	virtual void SetWndHeight(long nHeight);
	virtual void SetWndWidth(long nWidth);
	virtual void SetWndWidthHeight(long nWidth, long nHeight);
	virtual void SetWndLeft(long nLeft);
	virtual void SetWndTop(long nTop);
	virtual void SetWndRight(long nRight);
	virtual void SetWndBottom(long nBottom);
	virtual void SetWndPosition(long nLeft, long nTop, long nRight, long nBottom);
	virtual void SetWndPosition(CRect rcPos);
	virtual long GetWndHeight()		{	return m_nHeight;	}
	virtual long GetWndWidth()		{	return m_nWidth;	}
	virtual long GetWndLeft()		{	return m_nLeft;		}
	virtual long GetWndTop()		{	return m_nTop;		}
	virtual long GetWndRight()		{	return m_nLeft + m_nWidth;	}
	virtual long GetWndBottom()		{	return m_nTop + m_nHeight;	}
	virtual CRect GetWndPosition();//	{	return CRect(m_nLeft, m_nTop,GetWndRight(), GetWndBottom());	}
	virtual CPoint GetWndTopLeft()	{	return CPoint(m_nLeft, m_nTop);		}
	virtual CSize GetWndSize()		{	return CSize(m_nWidth, m_nHeight);	}
	virtual void SetWndSize(long nWidth, long nHeight);

	//ϵͳ��Ϣ������
	//virtual long OnSystemMessage(UINT nSysMsgID, long &nImpCount, long &nRunCount);
	//virtual long OnSystemMessage(CSystemMessages *pSysMsgs, long &nImpCount, long &nRunCount);
	//virtual long OnChildrenSystemMessage(UINT nSysMsgID, long &nImpCount, long &nRunCount);

	virtual void SetCheckState(long nState)		   {	}
	virtual long GetCheckState()				   { return 0;}
	virtual void SetWndCurrSel(long nCurrenSel)    {    }
	virtual long GetWndCurrSel()				   { return 0;}

	//����/���ٷ���
	virtual BOOL UICreate(CWnd *pParent); //��ǰ׺��Ŀ����Ϊ��������CWnd�ĺ���Create
	virtual BOOL UICreateChildren(CWnd *pParent = NULL)	{	return TRUE;	};
	virtual BOOL Destroy();
	virtual BOOL DestroyChildren();

	virtual long ExecWndCmd(const char *pszCmd, const char *pszPara);
	virtual long ExecWndCmd(const CString &strCmd, const CString &strPara);
	virtual long GetWndAttr(const CString &strAttrID, CString &strAttrValue);
	virtual long SetWndAttr(const CString &strAttrID, const CString &strAttrValue);

protected:
	static UINT  g_nWindowID;
	static UINT  GenerateWindowID()		{   g_nWindowID++;  return g_nWindowID;   }


protected:
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

	//��ť��״̬
	BOOL m_bOver;	//���λ�ڰ�ť֮��ʱ��ֵΪtrue����֮Ϊflase
	BOOL m_bTracking;	//����갴��û���ͷ�ʱ��ֵΪtrue
	BOOL m_bSelected;	//��ť�������Ǹ�ֵΪtrue
	BOOL m_bFocus;	//��ťΪ��ǰ��������ʱ��ֵΪtrue

	afx_msg void UI_OnClicked();
	afx_msg void UI_OnDoubleclicked();
	afx_msg void UI_OnMouseMove(UINT nFlags, CPoint point);
	afx_msg LRESULT UI_OnMouseLeave(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT UI_OnMouseHover(WPARAM wParam, LPARAM lParam);
	afx_msg void UI_OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void UI_OnLButtonUp(UINT nFlags, CPoint point);

	virtual void DoGradientFill(CDC *pDC, CRect* rect);
	virtual void RedrawParentRect();
};

#define LOG_WriteCSourceFilePos(strMsg)        {          }
#define LOG_WriteString(strMsg, nLevel)        {          }
#define LOG_WriteLawString(strMsg)             {          }
void _P_InitSource_Bitmap_Path();
const char* _P_GetSource_Bitmap_Path();
