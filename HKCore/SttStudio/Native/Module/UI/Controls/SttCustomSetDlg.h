#ifndef STTCUSTOMSETDlG_H
#define STTCUSTOMSETDlG_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "ui_SttCustomSetDlg.h"
#include "SttCustomSetTree.h"
#include "../Module/UI/Config/Frame/SttFrameConfig.h"
#include "../Module/UI/Config/Frame/SttFrame_Menus.h"
#include "../Module/UI/Config/Frame/SttFrame_XBar.h"
#include "../../../Module/BaseClass/QT/ExBaseListTreeCtrl.h"
#include "../Module/UI/SttTestCntrFrameBase.h"
#include "../../../Module/OSInterface/QT/XMessageBox.h"


class SttCustomSetDlg : public QDialog
{
	Q_OBJECT
public:
    SttCustomSetDlg(QWidget *parent = 0, Qt::WindowFlags flags = 0);
	~SttCustomSetDlg();

private:
 	Ui::QSttCustomSetDlg ui;

	
public:
	
	void initData();
	void OnSetItemClick();
	void EnableBtns();
	void GetCurrItemData();
	BOOL IsCurrSelMenuItemInBar();
	BOOL IsCurrFloatBarRoot();
	CSttFrame_Button*  NewBtnByCurrSelMenuItem();
	void SetMenuItemState();
	void SetCurrSelMenuItemUpdateState();

	void SetCustomSetFont();

	//窗口关闭
//	virtual void closeEvent ( QCloseEvent * event );

public:
	//定义FrameConfig
	CSttFrameConfig * m_pSttFrameConfig;
    CSttFrame_BarBase * m_pToolBar;
    CSttFrame_Menus * m_pSttMenus; 
	QSttBarDataBtnsMngr m_oDataBtnsMngr;


public:
	CExBaseList *m_pFloatBarList;
	CExBaseList *m_pMenutList;
	CSttFrame_Button *m_pCurrFloatBarData;
	CSttFrame_Item *m_pCurrMenuData;
	QExBaseTreeWidgetItem *m_pCurrMenuItem;
	QExBaseTreeWidgetItem *m_pCurrFloatBarItem;




public slots:
	void slot_OnBtnRemove();
	void slot_OnBtnAddBar();
	void slot_OnClose();
	void slot_OnBtnInsertBefore();
	void slot_OnBtnInsertAfter();
    void slot_MeunTreeItemClicked(QTreeWidgetItem * pSetItem, int nColumn);
	void slot_FolatBarTreeItemClicked(QTreeWidgetItem * pSetItem, int nColumn);
	void slot_FloatBarTreeItemDoubleClicked(QTreeWidgetItem *pTreeItem, int nCol);
	
	
};

#endif // STTCUSTOMSETDlG_H
