#pragma once

#include "XLanguageGlobal.h"
#include "../BaseClass/BaseList.h"
#include "XLanguageWndInterface.h"



class CXLangWndAdjBase : public CBaseObject
{
public:
	CXLangWndAdjBase();
	virtual ~CXLangWndAdjBase();

	//初始化语言调整空间对象
	void InitCXLangWndAdj(CXLanguageWndInterface *pWnd);
	void InitCXLangWndAdj(CWnd *pWnd);

protected:
	CXLanguageWndInterface *m_pXLangWnd;
	CWnd *m_pXLangWndRef;
	CRect m_rcOrigin;
	long  m_nWidthCal;
	long m_nWidthOrigin;

public:
	virtual UINT GetClassID() {        return LGUGCLASSID_WNDBASE;                               }

public:
	//计算调整宽度
	virtual long AdjustCal();
	
	//调整位置
	virtual long Adjust(CWnd *pParent, long nOffset, CSize &szMax);
	
	//获取调整对象的宽度
	virtual long Width()		{	return m_rcOrigin.Width();	}
	
	//获取调整位置的偏移
	virtual long CalWidth()		{	return m_nWidthCal;			}
	virtual void ExpandColWidth(long nAdd)	{	m_nWidthCal += nAdd;	}
};

class CXLangWndAdjBaseList : public CXLangWndAdjBase, public CTLinkList<CXLangWndAdjBase>
{
public:
	CXLangWndAdjBaseList();
	virtual ~CXLangWndAdjBaseList();

public:
	CXLangWndAdjBase* AddNewChild(CXLangWndAdjBase *pNew);

public:
	//调整位置
	virtual long Adjust(CWnd *pParent, long nOffset, CSize &szMax);

	//获取调整对象的宽度
	virtual long Width();

	//获得调整对象的计算宽度
	virtual long CalWidth();

	virtual long AdjustCal();

	//获取调整位置的偏移
	virtual long GetOffset();
};


class CXLangWndAdjFrame;
class CXLangWndAdjCols;

class CXLangWndAdjCol : public CXLangWndAdjBaseList
{
public:
	CXLangWndAdjCol();
	virtual ~CXLangWndAdjCol();
	
public:
	virtual UINT GetClassID() {        return LGUGCLASSID_COL;                               }

public:
	//添加控件对象
	CXLangWndAdjBase* RegisterWnd(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjBase* RegisterWnd(CWnd *pXLandWnd);

	//注册框架窗口对象
	CXLangWndAdjFrame* RegisterFrame(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjFrame* RegisterFrame(CWnd *pXLandWnd);
	
	virtual long Adjust(CWnd *pParent, long nOffset, CSize &szMax);
};

class CXLangWndAdjCols : public CXLangWndAdjBaseList
{
public:
	CXLangWndAdjCols();
	virtual ~CXLangWndAdjCols();
	
public:
	virtual UINT GetClassID() {        return LGUGCLASSID_COLS;                               }


public:
	//为列集合添加一个列对象
	CXLangWndAdjCol* RegisterCol();

	//为当前列对象m_pCurrCol添加控件对象
	//RegisterXWnd与RegisterWnd功能一致，在对话框界面中，如果传入CXLanguageTextWnd对象，编译器无法确定使用哪个函数
	CXLangWndAdjBase* RegisterXWnd(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjBase* RegisterWnd(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjBase* RegisterWnd(CWnd *pXLandWnd);

	//调用当前m_pCurrCol的RegisterFrame
	CXLangWndAdjFrame* RegisterFrame(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjFrame* RegisterFrame(CWnd *pXLandWnd);
	
	virtual long Adjust(CWnd *pParent, CSize &szMax);

protected:
	CXLangWndAdjCol *m_pCurrCol;
	
};

//////////////////////////////////////////////////////////////////////////
//CXLangWndAdjFrame：框架对象，为了概念上的清晰，增加此类
class CXLangWndAdjFrame : public CXLangWndAdjCols
{
public:
	CXLangWndAdjFrame();
	virtual ~CXLangWndAdjFrame();

public:
	virtual UINT GetClassID() {        return LGUGCLASSID_FRAME;                               }

public:
	//调整前，计算Frame的原始大小和调整后的大小
	virtual long AdjustCal();

	//调整框架对象
	virtual long Adjust(CWnd *pParent, long nOffset, CSize &szMax);

	//为框架对象注册控件列
	CXLangWndAdjBase* RegisterXCol(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjBase* RegisterColWnd(CWnd *pXLandWnd);

};

//////////////////////////////////////////////////////////////////////////
//CXLangWndAdjMngr:多语言控件动态调整对象
class CXLangWndAdjMngr : public CBaseList
{
public:
	CXLangWndAdjMngr();
	virtual ~CXLangWndAdjMngr();
	void FreeAdjMngr();
	
public:
	virtual UINT GetClassID() {        return LGUGCLASSID_MNGR;                               }


public:
	CXLangWndAdjCols* RegisterCols();
// 	CXLangWndAdjBase* RegisterXCols(CXLanguageWndInterface *pXLandWnd);
// 	CXLangWndAdjBase* RegisterCols(CWnd *pXLandWnd);

	//注册一列
	CXLangWndAdjCol* RegisterCol();

	//注册一个控件列，一个控件单独一列
	CXLangWndAdjBase* RegisterXCol(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjBase* RegisterCol(CWnd *pXLandWnd);

	//注册控件对象，注册到：m_pCurrCols->m_pCurrCol
	CXLangWndAdjBase* RegisterXWnd(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjBase* RegisterWnd(CWnd *pXLandWnd);

	//调用当前m_pCurrCols的RegisterFrame
	CXLangWndAdjFrame* RegisterXFrame(CXLanguageWndInterface *pXLandWnd);
	CXLangWndAdjFrame* RegisterFrame(CWnd *pXLandWnd);

	//调整位置，如果是对话框，则动态调整对话框的位置
	void Adjust(CWnd *pParent, BOOL bDialog);
	
protected:
	CXLangWndAdjCols *m_pCurrCols;
	//CXLangWndAdjCol  *m_pCurrCol;
	
};
