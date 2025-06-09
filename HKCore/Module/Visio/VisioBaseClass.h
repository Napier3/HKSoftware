// WordBaseClass.h
//
//////////////////////////////////////////////////////////////////////

#if !defined(_WORDBASECLASS_H__)
#define _WORDBASECLASS_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MSVisio15.h"

class CVisioDocBase
{
public:
	CVisioDocBase(MSVisio15::CVApplication &oWordApp);
	CVisioDocBase();
	virtual ~CVisioDocBase();
	
public:
	virtual long New(const CString &strTemplateFile, const CString &strWordFile, BOOL bAdjust=FALSE);
	virtual long New(const CString &strWordFile, BOOL bAdjust=FALSE);
	virtual BOOL Open(const CString  &strWordFile, BOOL bAdjust=FALSE);
	virtual long Save();
	virtual long SaveAs(const CString  &strWordFile);
	virtual long Close(long nSave = 0);

	BOOL SelectCurPage(const CString &strPageName);
	BOOL GetAssociateShapes(long nShapeID);
	BOOL SetShapeRowValue(long nShapeID,const CString &strRowValue);

	MSVisio15::CVShapes GetCurShapes();

	//用于调整试验报告界面与主程序界面的布局
// 	virtual void SetParentWnd(CWnd* pParentWnd)		{		m_pParentWnd = pParentWnd;	}
// 	virtual CWnd* GetWordMainWnd()							{		return NULL;								}
	
protected:
	MSVisio15::CVApplication m_oVisioApp;
	MSVisio15::CVDocument m_oDoc;
	MSVisio15::CVPages m_oCurPages;
	MSVisio15::CVPage m_oCurPage;
	MSVisio15::CVShapes m_oCurShapes;
//	HWND m_hWordWnd;

	//WORD的父窗口
// 	CWnd* m_pParentWnd;
// 	HWND m_hParentWnd;

	BOOL AddNewReport(const CString &strRptTmplFile);
	BOOL CloseVisioDocWindow();

private:
	MSVisio15::CVCell m_oCurCell;

public:
	BOOL AddShape(const CString &strTemplate,const CString &strShapeNameU,double dLength,double dWidth);

	void AdjustVisioWindow();
	BOOL SetColorByShapeID(unsigned long uLineID ,const CString &strLineColor);
	BOOL SetTypeByShapeID(unsigned long uLineID ,const CString &strLineType);
	BOOL SetTypeColorByShapeID(unsigned long uLineID ,const CString &strLineType,const CString &strLineColor);
	BOOL SetTypeColorByShapeText(const CString &strLineText ,const CString &strLineType,const CString &strLineColor);

	BOOL SetTypeColorByShapeType(const CString &strShapeType,long nLineType,const CString &strLineColor);

	MSVisio15::CVDocument GetDoc()		{		return m_oDoc;		}

private:
	BOOL SetShapeColor(MSVisio15::CVShape &oCurShape,const CString &strLineColor);
	BOOL SetShapeType(MSVisio15::CVShape &oCurShape,const CString &strLineType);
	BOOL IsEqualShape(const CString &strShapeType ,const CString &strNameU);
	MSVisio15::CVShape GetShapeFromID(long nShapeID);

public:
	MSVisio15::CVShape GetShapeFromName(const CString &strShapeName);

};

class CVisioAppBase
{
public:
	CVisioAppBase(MSVisio15::CVApplication &oWordApp);
	CVisioAppBase();
	virtual ~CVisioAppBase();

public:
	virtual MSVisio15::CVApplication GetVisioApp(BOOL bVisible=FALSE);
	virtual BOOL CloseVisioApplication();

	virtual CVisioDocBase* CreateVisioDocBase();

protected:
	MSVisio15::CVApplication m_oVisioApp;
	BOOL m_bIsAppRef;
};


#endif // !defined(_WORDBASECLASS_H__)
