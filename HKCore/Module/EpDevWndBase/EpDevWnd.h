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

	//����
public:
	//���ڵ�ԭʼ��С�����ڱ���ر�֮ǰ���ڵĴ�С
	long m_nOriginWidth;
	long m_nOriginHeight;	
	DWORD m_color;		//����ɫ

	virtual CPoint GetConnectPoint();

public:
	//����ѡ��״̬
	void DrawSelectedState();		
	
	//��������
	virtual long AdjustOwnPos(long nLeft,long nTop);
	virtual long AdjustChildrenPos(long nLeft,long nTop);
	
	//��������
	virtual long CalSize(CSize &sz);
	
	//����������
	virtual BOOL UICreateChildren(CWnd *pParent);
	virtual BOOL DestroyChildren();
	
	//��ʾ������
	virtual void Show(UINT nShow);
	
	//չ��
	virtual long Expand(long nExpand);
	
	//����������
	virtual void DrawLinkLines(CDC *pDC);
	
	//�ر������Ӷ���
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