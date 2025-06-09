#pragma once

//#include "MacroTestDataEditGrid.h"
#include "afxcmn.h"
#include "afxwin.h"

#include "..\..\Module\Xlanguage\Xlanguagetextwnd.h"
#include "..\..\Module\XLanguage\XLanguageButton.h"

// CItemParaEditDlg 对话框

#define use_MacroTestDataEditPropGridCtrl

#include "..\..\UI\MacroTestDatasPropGridCtrl.h"

class CItemParaEditDlg : public CDynDialogEx, public CExprVariableFind
{
public:
	virtual CExBaseObject* FindVariableByID(const CString &strID);
	virtual CExBaseObject* FindVariableByName(const CString &strName);
	virtual void OnExprScriptChanged(const CString &strExprScript);

public:
	CItemParaEditDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CItemParaEditDlg();

	CMacroTestDatasPropGridCtrl m_oGridFaultPara;
	CMacroTestDatasPropGridCtrl m_oGridCommPara;


	CTmFaultParas m_oFaultParas;
	CTmFaultParasEx m_oFaultParasEx;
	CTmSysParas m_oSysParas;
	CGbItemBase *m_pItem;
	void xlang_InitAndAdjust();
// 对话框数据
	//enum { IDD = IDD_EDIT_ITEM_PARA };

private:
	void ShowItemPara();
	void ShowMacroItemPara();
	void ShowCommCmdPara();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

protected:
	virtual void OnOK();
	virtual void OnCancel();

private:
	void DeleteAll();
	CMFCTabCtrl m_tabMacroItemParaType;

public:
	afx_msg void OnBnClickedCancel();
	CXLanguageButton m_btnItemParaOk;
	CXLanguageButton m_btnItemParaCancel;
};
