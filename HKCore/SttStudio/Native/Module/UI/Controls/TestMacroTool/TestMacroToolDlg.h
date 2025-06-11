#ifndef TESTMACROTOOLDLG_H
#define TESTMACROTOOLDLG_H

#include "../../../../../Module/BaseClass/ExBaseList.h"
#include "../../Config/TestMacroToolUI/TestMacroToolBar.h"
#include "../../Module/UI/Module/CommonCtrl_QT/QSttProgDlg.h"
#include "../../../../../Module/System/TickCount32.h"

#include <QFont>
#include <QDialog>
#include <QToolButton>
#include <QTreeWidgetItem>

class QTestMacroToolButton : public QToolButton
{
public:
	QTestMacroToolButton();
	virtual ~QTestMacroToolButton();

public:
	QTreeWidgetItem* m_pItem;
	CExBaseList* m_pData;

	bool m_bMutiSelect;//2024.12.18 zhangyq 是否使用多选功能

public:
	void SendClickSig() { emit clicked(false); }

	void InitStyleSheet();
	void setChecked(bool checked);// 2024.12.18 zhangyq 设置复选框状态
	void setIcon(const QPixmap &pixmap);
	void setText(const QString &text);

protected:
	virtual void paintEvent(QPaintEvent *event);//2024.12.18 zhangyq 重写paintEvent以自定义绘制

private:
	QPixmap m_oSelectedPixmap;
	QPixmap m_oUnselectedPixmap;
	QPixmap m_iconPixmap;      // 图标图片
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

	bool m_bUseMutiSelect;//2024.12.18 zhangyq 是否使用多选功能
	QList<QTestMacroToolButton*> m_listToolButton;//2024.12.18 zhangyq 所有选择功能模块创建的button
	QSttProgDlg *m_pSttProgDlg;
public:
    explicit QTestMacroToolDlg(QFont font,QWidget *parent = 0);
    virtual ~QTestMacroToolDlg();

	void InitLanguage();
	void InitData();
	void GetAllSelTestID(QStringList &listTestId, QStringList &listTestName);//2024.12.18 zhangyq 获取所有勾选项的ID和name
	void GetAllSelTestID(QStringList &listCurSelTestID, QStringList &listItemsName, QStringList &listItemsID);//2024.12.25 zhangyq 获取所有勾选项的ID和name
	void StartProgDlg();
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
	QTestMacroToolButton* CreateItem(const CString strName, const CString strPic, QSize sizeBtn, QSize sizeIcon, bool bUseMultiSelect);
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
