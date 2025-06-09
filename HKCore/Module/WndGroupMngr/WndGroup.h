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
		CWnd *m_pWnd;      //关联的参数窗口
		CRect m_rcOrigin;  //窗口原始位置
		CRect m_rcCurr;    //窗口的当前位置
		BOOL  m_bShow;     //窗口是否显示

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
	CString      m_strGroupTitle;                //分组标题
	CWndGroupFrame *m_pWndFrame;      //关联的标题分类窗口
	CRect m_rcOrigin;                                //窗口组原始位置
	CRect m_rcCurr;                                  //窗口组的当前位置

	BOOL m_bExpand;                              //展开/关闭控制标记
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

	////尺寸调整
	LONG m_nBtnWidth;//按钮宽度
	LONG m_nBtnHeight;//按钮高度
	LONG m_nBtnHGap;//按钮横向间隔
	LONG m_nBtnVGap;//按钮纵向间隔
	void AddGroupHeight();//增加组控件区域高度，每次默认增加两个按钮高度
	LONG m_nAddlength;//增加的高度

	BOOL m_bResize;
	CRect GetnextWndRefRect();
	CRect m_rcCurWndRef;
private:
	void InitWindowRect();

public:
	//Add by hqy
	LONG Resize(CRect rect);
};
