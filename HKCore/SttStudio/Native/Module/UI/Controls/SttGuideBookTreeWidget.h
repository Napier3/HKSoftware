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

    virtual void InitButton();
	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);
	virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)	;
	virtual void HideAllBtns();
	virtual void UpdateButtons();

	void ShowBaseList(CExBaseList *pGuideBook);
	QToolButton* NewButton(const CString &strPicPath);
	void SetCurTestItem(CExBaseObject *pCurTestItem);
	CExBaseObject* GetCurTestItem();//chenling202402267 获得当前测试ID
	CExBaseObject* GetCurrSelectGbItem();

    QVBoxLayout *m_pVLayout;
    QSttGuideBookTreeCtrl *m_pTreeCtrl;
	CExBaseObject *m_pCurrSelGbItem;
	CExBaseObject *m_pCurrTestGbItem;
	CSttItems *m_pCurrSelRootNode;  //当前选中的节点，找到的最近的ROOTNODE
	CString m_strCurrSelRootNodePath;

    QToolButton *m_pBtnTestFrom;
    QToolButton *m_pBtnTestThis;

protected://Linux暂时没试
	BOOL m_bHasButtonsShow;
	BOOL m_bTreeCheckStateChanging;

public:
	virtual void After_SaveCurr(const CString &strRootNodePath);
	virtual void ExpandRootNode();
	void ExpandRootNode(CSttItems *pItems);
	void SwitchMacroViewByCurrSel(CExBaseObject *pSel);//切换对应模块界面
	virtual void OnItemCheckChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);//更新树节点的勾选状态
	virtual void UpdateParentCheckState(QSttGuideBookTreeItem* pParent);
	virtual void UpdateChildCheckState(QSttGuideBookTreeItem* pItem);
	long SendSetItemState(CSttItemBase *pItemBase);
	virtual void SetCheckBoxEnable(BOOL bEnable);
	virtual void SetChildCheckBoxEnable(QSttGuideBookTreeItem* pItem, BOOL bEnable);
signals:

public slots:
	virtual void slot_ItemStateChanged(CExBaseObject *pCurTestItem);
	virtual void slot_ShowItems(CExBaseList *pCurTestItems);
	virtual void slot_OnBtnTestFrom();
	virtual void slot_OnBtnTestThis();
    void slot_SttfocusOutEventGbTree(QFocusEvent *e);

};

#endif // QSTTGUIDEBOOKTREEWIDGET_H
