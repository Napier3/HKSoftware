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
	CExBaseObject* GetCurTestItem();//chenling202402267 ��õ�ǰ����ID
	CExBaseObject* GetCurrSelectGbItem();

    QVBoxLayout *m_pVLayout;
    QSttGuideBookTreeCtrl *m_pTreeCtrl;
	CExBaseObject *m_pCurrSelGbItem;
	CExBaseObject *m_pCurrTestGbItem;
	CSttItems *m_pCurrSelRootNode;  //��ǰѡ�еĽڵ㣬�ҵ��������ROOTNODE
	CString m_strCurrSelRootNodePath;

    QToolButton *m_pBtnTestFrom;
    QToolButton *m_pBtnTestThis;

protected://Linux��ʱû��
	BOOL m_bHasButtonsShow;

public:
	virtual void After_SaveCurr(const CString &strRootNodePath);
	virtual void ExpandRootNode();

signals:

public slots:
	virtual void slot_ItemStateChanged(CExBaseObject *pCurTestItem);
	virtual void slot_ShowItems(CExBaseList *pCurTestItems);
	virtual void slot_OnBtnTestFrom();
	virtual void slot_OnBtnTestThis();
    void slot_SttfocusOutEventGbTree(QFocusEvent *e);

};

#endif // QSTTGUIDEBOOKTREEWIDGET_H
