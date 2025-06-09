#pragma once

#include "EpDevBaseList.h"
#include "EpDevDeleteButton.h"
#include "EpDevMinimizeButton.h"

class CEpDevWnd : public CEpDevBaseList
{
public:
	CEpDevWnd();
	virtual ~CEpDevWnd();

public:
	virtual UINT GetClassID()	{	return EPDCLASSID_DEVWND;	}

	//属性
public:
	//窗口的原始大小，用于保存关闭之前窗口的大小
	long m_nOriginWidth;
	long m_nOriginHeight;	
	DWORD m_color;		//背景色

	virtual CPoint GetConnectPoint();

public:
	//绘制选中状态
	void DrawSelectedState();		
	
	//调整区域
	virtual long AdjustOwnPos(long nLeft,long nTop);
	virtual long AdjustChildrenPos(long nLeft,long nTop);
	
	//计算区域
	virtual long CalSize(CSize &sz);
	
	//创建和销毁
	virtual BOOL UICreateChildren(CWnd *pParent);
	virtual BOOL DestroyChildren();
	
	//显示、隐藏
	virtual void Show(UINT nShow);
	
	//展开
	virtual long Expand(long nExpand);
	
	//绘制连接线
	virtual void DrawLinkLines(CDC *pDC);
	
	//关闭所有子对象
	virtual void UnExpandChildren();
	//

	virtual void AttachDevMinimizeButton(CEpDevMinimizeButton *pButton)
	{
		m_pDevMinimizeButton = pButton;
		m_pDevMinimizeButton->CEpDevBase::SetParent(this);
	}

	virtual void AttachDevDeleteButton(CEpDevDeleteButton *pButton)
	{
		m_pEpDevDeleteButton = pButton;
		m_pEpDevDeleteButton->CEpDevBase::SetParent(this);
	}

protected:
	CEpDevMinimizeButton *m_pDevMinimizeButton;
	CEpDevDeleteButton   *m_pEpDevDeleteButton;
};