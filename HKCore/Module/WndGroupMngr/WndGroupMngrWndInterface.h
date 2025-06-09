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
	DWORD   m_nItemData;       //���ڱ�����Ŀ��صĹ�������

protected:
	CWnd   *m_pOwnWnd;

// Operations
public:
	CWndGroup* AddNewGroup(CWndGroupFrame* pFrame, const CString &strTitle, long nGroupID);
	CSize AdjustAllWndGroup(long nGroupID, BOOL bExpand);  //���������Ի������λ��
	CSize AdjustAllWndGroup(CWndGroupMngrWndInterface *pSynMacroDlg);  //���������Ի������λ��
	void  GetMngrWndRect(CRect &rc);   //��ȡ����Ĵ�С
	CSize Move(long nXOffset, long nYOffset);
	CSize CalSize(long nXOffset, long nYOffset);
	
	CWndGroup* GetAt(long nIndex)   {    return (CWndGroup*)CBaseList::GetAt(nIndex);    };
	CWndGroup* GetAt(POS pos)	      {		return (CWndGroup*)CBaseList::GetAt(pos);         }

public:
	virtual void Show() = 0;        //��ʾ��������ʵ�ʵĹ������
	virtual void InitMngr() = 0;    //��ʼ��ʵ�ʹ���Ķ���

};
