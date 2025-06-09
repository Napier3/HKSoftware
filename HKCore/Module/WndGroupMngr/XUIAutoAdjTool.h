#pragma once
#include "..\baseclass\TLinkList.h"

class CXUIAdjItemBase
{
public:
	CXUIAdjItemBase();
	virtual ~CXUIAdjItemBase();

public:
	CRect m_rcItemCurrPos;   //�ؼ�����λ��
	CRect m_rcItem;             //�ؼ���ԭʼλ��
	float	m_fXMoveCoef;		//�ؼ���x���ƶ��İٷֱ�
	float	m_fYMoveCoef;		//�ؼ���y���ƶ��İٷֱ�
	float	m_fXZoomCoef;		//�ؼ���x�����ŵİٷֱ�
	float	m_fYZoomCoef;		//�ؼ���y�����ŵİٷֱ�

	//��������������չ��
	long m_nMinVisibleWidth;	//�ؼ��ɼ�����С��ȣ������ڵĿ��С�ڸ�ֵ�������ش˿ؼ��������ֵΪ-1��Ӳ����أ�
	long m_nMinVisibleHeight;	//�ؼ��ɼ�����С�߶ȣ������ڵĸ߶�С�ڸ�ֵ�������ش˿ؼ��������ֵΪ-1��Ӳ����أ�
	BOOL m_bCanHideShow;		//ָʾ��������ʱ�Ƿ���ݡ���С��Ⱥ���С�߶ȡ���ʾ�����ؿؼ���

	BOOL XUI_Validate(const CRect &rcItem);
	void XUI_Merge(CRect &rcDest, CRect &rcSrc);
public:
	virtual void XUI_Adjust(long xChange, long yChange);
	virtual void XUI_CalSize();
	virtual void XUI_CalSize(CRect &rcItem);
	virtual void XUI_CalOwnSize(CRect &rcItem);
	virtual void XUI_CalChildrenSize(CRect &rcChildren);

};

class CXUIAdjItem_Wnd : public CXUIAdjItemBase
{
public:
	CXUIAdjItem_Wnd();
	CXUIAdjItem_Wnd(CWnd *pParent, CWnd *pWnd, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);
	virtual ~CXUIAdjItem_Wnd();

public:
	CWnd *m_pWnd;   //�����Ĵ���ָ��

public:
	virtual void XUI_Adjust(long xChange, long yChange);
};

class CXUIAdjItem_Area : public CXUIAdjItemBase, public CTLinkList<CXUIAdjItemBase>
{
public:
	CXUIAdjItem_Area(CWnd *pWnd, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);
	CXUIAdjItem_Area(CWnd *pWnd, CRect rcArea, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);
	CXUIAdjItem_Area();
	virtual ~CXUIAdjItem_Area();

	void XUI_SetParentWnd(CWnd *pWnd);

public:
	virtual void XUI_Adjust(long xChange, long yChange);
	virtual void XUI_CalChildrenSize(CRect &rcChildren);

public:
	CXUIAdjItem_Wnd* XUI_AddWnd(CWnd *pWnd, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);
	CXUIAdjItem_Wnd* XUI_AddWnd(UINT nID, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);
	CXUIAdjItem_Area* XUI_AddArea(float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);
	CXUIAdjItem_Area* XUI_AddArea(const CRect &rcArea, float fXMoveCoef, float fYMoveCoef, float fXZoomCoef, float fYZoomCoef);

	void XUI_OnSize(long cx, long cy);
	void XUI_OnSize();
	BOOL XUI_HasIinit()	{	return m_pXUI_ParentWnd != NULL;	}

protected:
	CWnd *m_pXUI_ParentWnd;

	virtual void XUI_InitAdjust()	{	ASSERT (FALSE);	}
};
