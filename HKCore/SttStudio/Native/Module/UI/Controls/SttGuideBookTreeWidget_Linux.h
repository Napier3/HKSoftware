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
	CSttItems *m_pCurrSelRootNode;  //��ǰѡ�еĽڵ㣬�ҵ��������ROOTNODE

    QToolButton *m_pBtnTestFrom;
    QToolButton *m_pBtnTestThis;

	//LINUX��ʱ�����ű༭����
#ifndef _PSX_QT_LINUX_
	QToolButton *m_pBtnNew;
    QToolButton *m_pBtnDeleteCurr;
    QToolButton *m_pBtnEditCurr;
	QToolButton *m_pBtnSaveCurr;
#endif

//windows�£������Ҽ��˵�
#ifndef _PSX_QT_LINUX_
	QMenu *m_MenuGuideBook;
	QMenu *m_subMenuCommCmdNew;  //�½�ͨѶ������Ӳ˵�
	QAction *m_ActItemsNew;      //�½���Ŀ����
	QAction *m_ActItemsNew_BFT;  //�½�����ǰ׼��
	QAction *m_ActItemsNew_AFT;  //�½����Ժ�ظ�
	QAction *m_ActDeleteCurr;    //ɾ����ǰѡ����Ŀ
	QAction *m_ActEditCurr;      //�༭��ǰѡ����Ŀ
	QAction *m_ActSaveCurr;      //���浱ǰѡ����Ŀ
	QAction *m_ActWzdNew;        //��ӹ�����
	QAction *m_ActTestFrom;      //�ӵ�ǰѡ����Ŀ��ʼ����
	QAction *m_ActTestThis;      //���Ե�ǰѡ����Ŀ

	void CreateGuideBookMenu();
#endif

protected://Linux��ʱû��
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
