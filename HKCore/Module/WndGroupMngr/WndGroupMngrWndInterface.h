#pragma once
#include "..\..\module\baseclass\baselist.h"
#include "WndGroup.h"
#include "WndGroupFrame.h"

class CWndGroupMngrWndInterface :	public CBaseList
{
public:
	CWndGroupMngrWndInterface(void);
	~CWndGroupMngrWndInterface(void);

// Attributes
public:
	DWORD   m_nItemData;       //用于保存项目相关的关联数据

protected:
	CWnd   *m_pOwnWnd;

// Operations
public:
	CWndGroup* AddNewGroup(CWndGroupFrame* pFrame, const CString &strTitle, long nGroupID);
	CSize AdjustAllWndGroup(long nGroupID, BOOL bExpand);  //调整参数对话框组的位置
	CSize AdjustAllWndGroup(CWndGroupMngrWndInterface *pSynMacroDlg);  //调整参数对话框组的位置
	void  GetMngrWndRect(CRect &rc);   //获取界面的大小
	CSize Move(long nXOffset, long nYOffset);
	CSize CalSize(long nXOffset, long nYOffset);
	
	CWndGroup* GetAt(long nIndex)   {    return (CWndGroup*)CBaseList::GetAt(nIndex);    };
	CWndGroup* GetAt(POS pos)	      {		return (CWndGroup*)CBaseList::GetAt(pos);         }

public:
	virtual void Show() = 0;        //显示处理，用于实际的管理对象
	virtual void InitMngr() = 0;    //初始化实际管理的对象

};
