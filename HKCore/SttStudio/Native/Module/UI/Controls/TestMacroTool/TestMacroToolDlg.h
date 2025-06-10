#ifndef TESTMACROTOOLDLG_H
#define TESTMACROTOOLDLG_H

#include "../../../../../Module/BaseClass/ExBaseList.h"
#include "../../Config/TestMacroToolUI/TestMacroToolBar.h"

#include <QFont>
#include <QDialog>
#include <QToolButton>
#include <QTreeWidgetItem>

class QTestMacroToolButton : public QToolButton
{
public:
	QTestMacroToolButton() { m_pData = NULL; m_pItem = NULL;}
	virtual ~QTestMacroToolButton() {}

public:
	QTreeWidgetItem* m_pItem;
	CExBaseList* m_pData;

public:
	void SendClickSig() { emit clicked(false); }
};

namespace Ui {
class QTestMacroToolDlg;
}

class QTestMacroToolDlg : public QDialog
{
    Q_OBJECT

public:
	QFont m_font;

	long m_nRepeatTimes;
	//shaolei 2023-6-21 
	long m_nRptTitle;
	long m_nTitleLevel;
	CString m_strItemsName;
	CString m_strItemsID;
	CExBaseList* m_pCurrentSelGbItem;  //选择功能时，当前选中的父项目节点
	CExBaseList* m_pCurrentSelTest;

	CTestMacroToolBar* m_pTestMacroToolBar;

	QTestMacroToolButton* m_pLastTreeBtnClicked;
	QTestMacroToolButton* m_pLastTableBtnClicked;

public:
    explicit QTestMacroToolDlg(QFont font,QWidget *parent = 0);
    virtual ~QTestMacroToolDlg();
	void InitLanguage();
private:
    Ui::QTestMacroToolDlg *ui;

private:
	void InitConnect();
	void InitTreeBtn();
	void EnableAddBtns(bool bEnable);
	void ClearLayout(QLayout* pLayout);
	void UpdateBtnTable(CExBaseList* pList);
	long CalAutoIndex(const CString& strID);
	void UpdateBtnTree(CExBaseList* pList, QTreeWidgetItem* pParentItem = NULL);
	QTestMacroToolButton* CreateItem(const CString strName, const CString strPic, QSize sizeBtn, QSize sizeIcon);
	void InitCmbTitleLevel();

public:
	CString GetCurSelTestName();
	CString GetCurSelTestID();

private slots:
	void OnTreeBtnClick(bool bChecked);
	void OnTreeBtnExpand(bool bChecked);
	void OnTableBtnClick(bool bChecked);
	void OnBtnCloseClick(bool bChecked);
	void OnBtnAddAfterClick(bool bChecked);
	void OnBtnAddBeforeClick(bool bChecked);
	void OnBtnAddChildClick(bool bChecked);

	void on_m_chkRptTitle_clicked();

};

#endif // TESTMACROTOOLDLG_H
