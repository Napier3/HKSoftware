#pragma once

#include "EpDevWnd.h"


class CEpDevPoint : public CEpDevBaseList
{
public:
	CEpDevPoint();
	virtual ~CEpDevPoint();

public:
	UINT GetClassID()		{	return EPDCLASSID_DEVPOINT;	}
	LONG m_nChildTop;			//���е��Ӵ��ڸ߶�
	LONG m_nChildBottom;	//�Ӵ��ڵײ���
	
	virtual void SetChildrenShow(long nShow);
	virtual void SetChildrenShowEx(CEpDevBase* pDevBase);
	
public:
	//��������
	virtual long AdjustChildrenPos(long nLeft,long nTop);
	
	//��������
	virtual long CalSize(CSize &sz);
	
	//����������
	virtual BOOL UICreateChildren(CWnd *pParent);
	virtual BOOL DestroyChildren();
	virtual BOOL DestroyOwn();
	
	//����������
	virtual void DrawLinkLines(CDC *pDC);
	
	//��ʾ������
	virtual void Show(UINT nShow);
	
	//չ��
	virtual long Expand(long nExpand);
	void GetChildSize();
	void ReArrangeChildren();

protected:
	BOOL m_bDrawLine;;
};