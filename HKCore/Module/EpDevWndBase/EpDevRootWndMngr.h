#pragma once

#include "EpDevBaseList.h"
#include "EpDevWnd.h"

/*
功能描述：管理EpDevRootWnd
*/

class CEpDevRootWndMngr : public CEpDevBaseList
{
public:
	CEpDevRootWndMngr();
	virtual ~CEpDevRootWndMngr();

protected:
	CEpDevBase* m_pCurDevRootWnd;		//??
	BOOL m_bSaveDevWndMode;
	CWnd *m_pParentWnd;

public:
	virtual void SetSaveDevWndMode(BOOL bSaveDevWndMode)	{	m_bSaveDevWndMode = bSaveDevWndMode;	}
	virtual BOOL IsSaveDevWndMode()										{	return m_bSaveDevWndMode;							}
	virtual void SetParentWnd(CWnd *pParentWnd)						{	m_pParentWnd = pParentWnd;						}

	virtual CEpDevWnd* CreateEpDevRootWnd(CExBaseObject *pData);
	virtual BOOL ShowData(CExBaseObject *pData);
	virtual CEpDevBase* FindDevWnd(CExBaseObject *pData);

	void Show();
	void Hide();

	void DrawLinkLines(CEpDevWnd* pDevWnd,CDC* pDC);
	void EraseLinkLines(CEpDevWnd* pDevWnd,CDC* pDC);

	//触发条件 当用户新建、删除、展开或收缩窗口时;当用户拖动已有窗口，调整位置时
	virtual void AdjustAllWnds(long nLeft, long nTop);

	virtual CPoint GetConnectPoint()	{	return CPoint(0, 0);	}

private:
	void DrawLinkLines(CEpDevWnd* pDevWnd,CDC* pDC, COLORREF rcColor);

};

