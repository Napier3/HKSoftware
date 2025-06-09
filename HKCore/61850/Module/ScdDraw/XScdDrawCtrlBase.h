//���Դ������ClassGenerator����
//��Ȩ���� LiJunqing  lijunqing1224@126.com
//��������Ȩ��

//XScdDrawCtrlBase.h  CXScdDrawCtrlBase

#pragma once

#include "XScdDrawGlobal.h"
#include "XScdDrawCtrl_GridBase.h"
#include "XScdDrawLine_Ctrl.h"

#include "..\..\..\Module\GridBase\ExBaseListXGridCtrlBase.h"
#include "XScdDrawCtrl_GridBase.h"


/*
#���ԭ�����߶���ֻ������SclIn������/
*/

class CXScdDrawCtrlBase : public CXDrawElements
{
public:
	CXScdDrawCtrlBase();
	virtual ~CXScdDrawCtrlBase();

//���غ���
public:
	virtual void AttachViewWindow(CXDrawBaseInterface_ViewWindow *pViewWindow);

//˽�г�Ա����
protected:
	CXScdDrawCtrl_CfgGridTitleBase *m_pGridCtrlTitle;
	CXScdDrawCtrl_CfgGridChsBase   *m_pGridCtrlChs;
	BOOL m_bShowChs;
	CXScdDrawLine_Ctrl *m_pXScdDrawLine_Ctrl;

	CExBaseListXGridCtrlBase *m_pActiveGrid;

//˽�г�Ա�������ʷ���
public:
	void SetShowChs(BOOL b)	{	m_bShowChs = b;	}
	BOOL IsShowChs()		{	return m_bShowChs;	}

	//��ͼ��غ�������
public:
	virtual void Draw(CDC *pDC, double fZoomRatio,const CPoint &ptOffset, DWORD dwDrawFlag=0xFFFFFFFF);
	virtual void Pick(const CPoint &point, CExBaseList &oList);

public:
	virtual DWORD XCreateElement(CExBaseObject *pData, CWnd *pParentWnd);
	virtual CSize CalLayout(CSize &szDraw);
	virtual CSize Layout(CPoint &ptTopLeft);
	virtual void InitLineBeginElement(CXDrawElement *pElement);
	virtual void InitLineEndElement(CXDrawElement *pElement);
	virtual CXScdDrawLine_Ctrl* AddXScdDrawLineCtrl(CXDrawElement *pBeginElement, CXDrawElement *pEndElement, CExBaseObject *pBeginObj, CExBaseObject *pEndObj);

	virtual void CreateCtrlLines();
	virtual void GetAllLines(CXDrawElements &oScdLines);
	CXDrawElement* QueryByXDrawDataRef(CExBaseObject *pDrawDataRef);
	virtual void OnOnlyShowUsedChsChanged(CXScdDrawLines *pLines);
	virtual void RemoveErrorLines();

protected:
	virtual DWORD XCreateElement_Title(CExBaseObject *pData, CWnd *pParentWnd);
	virtual DWORD XCreateElement_Chs(CExBaseObject *pData, CWnd *pParentWnd);
	void ReSetTiTleChsWidth();

	virtual void LayoutLines();
	virtual void LayoutCtrlLine();
	virtual void LayoutLine(CXScdDrawCtrl_CfgGridBase *pBeginGridChs, CXScdDrawCtrl_CfgGridBase *pEndGridChs, long nBeginIndex, long nEndIndex,long nEndColIndex, CXScdDrawLineBase *pLine);
	long GetLineBeginIndex(CExBaseList *pChs, CExBaseObject *pCh);
	long GetLineBeginIndex(CXScdDrawCtrl_CfgGridChsBase *pGridChs, CExBaseObject *pCh);


//Message
public:
	virtual LRESULT UI_OnSetFont(WPARAM hFont, LPARAM lParam);
	virtual LRESULT UI_OnGetFont(WPARAM hFont, LPARAM lParam);

	virtual void UI_OnLButtonUp(UINT nFlags, CPoint point);
	virtual BOOL UI_OnLButtonDown(UINT nFlags, CPoint point);
	virtual void UI_OnMouseMove(UINT nFlags, CPoint point);
	virtual void UI_OnTimer(UINT nIDEvent);

	virtual BOOL UI_OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual BOOL UI_OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	virtual void UI_OnLButtonDblClk(UINT nFlags, CPoint point);
	virtual void UI_OnRButtonDblClk(UINT nFlags, CPoint point);

	virtual void UI_OnCaptureChanged(CWnd *pWnd);

	virtual void UI_OnRButtonUp(UINT nFlags, CPoint point);
	virtual void UI_OnKillFocus(CWnd* pNewWnd);	
	virtual void UI_OnRButtonDown(UINT nFlags, CPoint point);

	virtual void UI_KillFocus();

};

