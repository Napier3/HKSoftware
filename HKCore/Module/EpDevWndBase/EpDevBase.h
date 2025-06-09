#pragma once

#include "EpDevGlobalDefine.h"

class CEpDevBase : public CExBaseObject
{
public:
	CEpDevBase();
	virtual ~CEpDevBase();

// 	static UINT  g_nWindowID;
// 	static UINT  GenerateWindowID()			{   g_nWindowID++;  return g_nWindowID;   }

	//属性
public:
	UINT m_nDataClassID;   //数据m_pData的ClassID，用于扩展用
	CExBaseObject* m_pData;		//关联的数据对象
	CWnd* m_pWindow;

	virtual void SetShow(long nShow=EPDES_SHOW)							{	m_nShow = nShow;	}
	virtual void SetChildrenShow(long nShow=EPDES_SHOW)		{									}
	virtual BOOL IsShow()																{	return (m_nShow==EPDES_SHOW) ? TRUE:FALSE;		}
	virtual void InitPpPos();
	virtual CPoint GetConnectPoint()	{	ASSERT (FALSE);	return CPoint(0, 0);	}

	//连接点 相对于窗口的左上角
	long m_nCnPntX;
	long m_nCnPntY;

	//虚拟大小
	long m_nVirtualWidth;
	long m_nVirtualHeight;

protected: 
	BOOL m_bExpand;
	long m_nShow;
	long m_nTop;
	long m_nLeft;
	long m_nWidth;
	long m_nHeight;

	//方法
public:
	//基本方法
	virtual UINT GetClassID()											{	return EPDCLASSID_DEVBASE;	}

	//编辑
	virtual long IsEqual(CEpDevBase* pObj)						{	return 0;			}
	virtual long Copy(CEpDevBase* pDesObj)					{	return 0;			}
	virtual CEpDevBase* Clone()										{	return NULL;		}
	
	//调整区域
	virtual long AdjustPos(long nLeft,long nTop);
	virtual long AdjustOwnPos(long nLeft,long nTop);
	virtual long AdjustChildrenPos(long nLeft,long nTop)		{	return 0;			}

	//计算区域
	virtual long CalSize(CSize &sz)										{	return 0;			}
	virtual long CalChildrenSize(CSize &sz) 							{	return 0;			}

	//窗口方法
	virtual void SetWndLeftTop(long nLeft, long nTop)		{	m_nLeft = nLeft; m_nTop = nTop;	}
	virtual long GetWndHeight()								{	return m_nHeight;				}
	virtual long GetWndWidth() 								{	return m_nWidth;				}
	virtual long GetWndLeft() 								{	return m_nLeft;					}
	virtual long GetWndTop() 								{	return m_nTop;					}
	virtual long GetWndRight() 								{	return m_nLeft + m_nWidth;		}
	virtual long GetWndBottom()							{	return m_nTop + m_nHeight;		}
	virtual CRect GetWndPosition()							{	return CRect(m_nLeft, m_nTop, GetWndRight(), GetWndBottom());	}
	virtual CPoint GetWndLeftTop() 						{	return CPoint(m_nLeft, m_nTop);			}
	virtual CSize GetWndSize()								{	return CSize(m_nWidth, m_nHeight);		}

	//显示、隐藏方法
	virtual void Show(UINT nShow);		
	virtual void ShowChildren(UINT nShow)					{	}

	//创建、销毁方法
	virtual BOOL UICreate(CWnd *pParent);
	virtual BOOL UICreateOwn(CWnd *pParent);
	virtual BOOL UICreateOwnAttr(CWnd *pParent);
	virtual BOOL UICreateChildren(CWnd *pParent)			{	return FALSE;	}

	virtual BOOL Destroy();
	virtual BOOL DestroyOwn();
	virtual BOOL DestroyChildren()									{	return FALSE;			}

	virtual BOOL IsDevWndCreated();
	virtual BOOL ShowData(CExBaseObject *pData)			{		return FALSE;		}
	virtual BOOL SaveData(CExBaseObject *pData)			{		return FALSE;		}

	//绘制连接线
	virtual void DrawLinkLines(CDC *pDC)							{								}
	virtual void EraseLinkLines(CDC *pDC)							{								}

	//展开
	virtual long Expand(long nExpand);
	virtual BOOL IsExpand()											{	return m_bExpand;	}
};

