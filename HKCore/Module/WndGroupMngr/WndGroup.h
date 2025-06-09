#pragma once
#include "..\..\module\baseclass\baselist.h"
#include "WndGroupFrame.h"

class CWndGroup :	public CBaseList
{
protected:
	class CWndRef : public CBaseObject
	{
	public:
		CWndRef(CWnd *pWnd);
		virtual ~CWndRef();

	public:
		CWnd *m_pWnd;      //�����Ĳ�������
		CRect m_rcOrigin;  //����ԭʼλ��
		CRect m_rcCurr;    //���ڵĵ�ǰλ��
		BOOL  m_bShow;     //�����Ƿ���ʾ

	public:
		void Show(BOOL bShow);
		void Move(long nXOffset, long nYOffset);
		CRect Resize(CRect rect);

	private:
		CWndRef(){}
	};

public:
	CWndGroup(CWndGroupFrame *pWnd, const CString &strTitle, long nGroupID);
	~CWndGroup(void);

private:
	CWndGroup(void)    {    }

// Attributes
public:
	long  m_nGroupID;
	CString m_strGroupID;

private:
	CString      m_strGroupTitle;                //�������
	CWndGroupFrame *m_pWndFrame;      //�����ı�����ര��
	CRect m_rcOrigin;                                //������ԭʼλ��
	CRect m_rcCurr;                                  //������ĵ�ǰλ��

	BOOL m_bExpand;                              //չ��/�رտ��Ʊ��
	BOOL m_bExpandChanged;

// Operations
public:
	CSize SetExpandFlag(BOOL bExpand);
	void Move(long nXOffset, long nYOffset);
	void Move(const CRect &rcBorder);
	void CreateParaWnd(CWnd *pWnd);
	void GetParaWndGroupSize(CSize &size);
	void GetParaWndGroupSize(long &nWidth, long nHeight);
	CRect GetWndFrameRect();
	void ExpandY(long nHeightExpand);

	BOOL IsExpand()               {     return m_bExpand;                                 }
	CRect GetWndGroupRect()  {     return m_rcCurr;                                     }
	long GetFrameGap()           {     return m_pWndFrame->GetFrameGap();   }
	CWndGroupFrame* GetWndFrame(){ return m_pWndFrame;}

	////�ߴ����
	LONG m_nBtnWidth;//��ť���
	LONG m_nBtnHeight;//��ť�߶�
	LONG m_nBtnHGap;//��ť������
	LONG m_nBtnVGap;//��ť������
	void AddGroupHeight();//������ؼ�����߶ȣ�ÿ��Ĭ������������ť�߶�
	LONG m_nAddlength;//���ӵĸ߶�

	BOOL m_bResize;
	CRect GetnextWndRefRect();
	CRect m_rcCurWndRef;
private:
	void InitWindowRect();

public:
	//Add by hqy
	LONG Resize(CRect rect);
};
