#ifndef QSTTGUIDEBOOKTREEWIDGET_H
#define QSTTGUIDEBOOKTREEWIDGET_H

#include <QWidget>
#include <QToolButton>
#include <QMouseEvent>
#include <QVBoxLayout>
#include <QToolButton>
#include <QFont>

#include "../Config/Frame/SttFrame_GbTree.h"
#include "../../SttCmd/GuideBook/SttGuideBook.h"
#include "SttGuideBookTreeCtrl.h"

class QSttGuideBookTreeWidget : public QWidget, public CExBaseListTreeOptrInterface
{
    Q_OBJECT
public:
    explicit QSttGuideBookTreeWidget(CExBaseObject *pSttGuideBook,CSttFrame_GbTree *pTreeParas,QWidget *parent = 0);

	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);
	virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)	;

	void ShowBaseList(CExBaseList *pGuideBook);
    void InitButton();
	QToolButton* NewButton(const CString &strPicPath);
	void SetCurTestItem(CExBaseObject *pCurTestItem);
	void UpdateButtons();
	void HideAllBtns();

	CExBaseObject* GetCurrSelectGbItem();

    QVBoxLayout *m_pVLayout;
    QSttGuideBookTreeCtrl *m_pTreeCtrl;
	CExBaseObject *m_pCurrSelGbItem;
	CSttItems *m_pCurrSelRootNode;  //当前选中的节点，找到的最近的ROOTNODE

    QToolButton *m_pBtnTestFrom;
    QToolButton *m_pBtnTestThis;

	//LINUX暂时不开放编辑功能
#ifndef _PSX_QT_LINUX_
	QToolButton *m_pBtnNew;
    QToolButton *m_pBtnDeleteCurr;
    QToolButton *m_pBtnEditCurr;
	QToolButton *m_pBtnSaveCurr;
#endif

//windows下，创建右键菜单
#ifndef _PSX_QT_LINUX_
	QMenu *m_MenuGuideBook;
	QMenu *m_subMenuCommCmdNew;  //新建通讯命令的子菜单
	QAction *m_ActItemsNew;      //新建项目分类
	QAction *m_ActItemsNew_BFT;  //新建测试前准备
	QAction *m_ActItemsNew_AFT;  //新建测试后回复
	QAction *m_ActDeleteCurr;    //删除当前选中项目
	QAction *m_ActEditCurr;      //编辑当前选中项目
	QAction *m_ActSaveCurr;      //保存当前选中项目
	QAction *m_ActWzdNew;        //添加功能向导
	QAction *m_ActTestFrom;      //从当前选中项目开始测试
	QAction *m_ActTestThis;      //测试当前选中项目

	void CreateGuideBookMenu();
#endif

protected://Linux暂时没试
	BOOL m_bHasButtonsShow;

#ifndef _PSX_QT_LINUX_
	QRect m_rectClicked;
	void mouseMoveEvent(QMouseEvent *e);
#endif

public:
#ifndef _PSX_QT_LINUX_
	void SwitchMacroViewByCurrSel(CExBaseObject *pSel);
#endif 

signals:

public slots:
	void slot_ItemStateChanged(CExBaseObject *pCurTestItem);
	void slot_ShowItems(CExBaseList *pCurTestItems);
	void slot_OnBtnTestFrom();
	void slot_OnBtnTestThis();
	void slot_OnBtnNew();
	void slot_OnBtnEditCurr();
	void slot_OnBtnDeleteCurr();
	void slot_OnBtnSaveCurr();

	void slot_OnBtnNew_AFT();
	void slot_OnBtnNew_BFT();
	void slot_OnBtnNewCommCmd();
	void slot_OnBtnNewWzd();
#ifndef _PSX_QT_LINUX_
    void slot_SttMouseMoveEventGbTree(QMouseEvent *e);
	void slot_TreeShowMenu(QPoint pos);
#endif
    void slot_SttfocusOutEventGbTree(QFocusEvent *e);

};

#endif // QSTTGUIDEBOOKTREEWIDGET_H
