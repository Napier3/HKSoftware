#pragma once

#include "EpDevWnd.h"


class CEpDevPoint : public CEpDevBaseList
{
public:
	CEpDevPoint();
	virtual ~CEpDevPoint();

public:
	UINT GetClassID()		{	return EPDCLASSID_DEVPOINT;	}
	LONG m_nChildTop;			//所有的子窗口高度
	LONG m_nChildBottom;	//子窗口底部；
	
	virtual void SetChildrenShow(long nShow);
	virtual void SetChildrenShowEx(CEpDevBase* pDevBase);
	
public:
	//调整区域
	virtual long AdjustChildrenPos(long nLeft,long nTop);
	
	//计算区域
	virtual long CalSize(CSize &sz);
	
	//创建、销毁
	virtual BOOL UICreateChildren(CWnd *pParent);
	virtual BOOL DestroyChildren();
	virtual BOOL DestroyOwn();
	
	//绘制连接线
	virtual void DrawLinkLines(CDC *pDC);
	
	//显示、隐藏
	virtual void Show(UINT nShow);
	
	//展开
	virtual long Expand(long nExpand);
	void GetChildSize();
	void ReArrangeChildren();

protected:
	BOOL m_bDrawLine;;
};