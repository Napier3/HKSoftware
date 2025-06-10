#ifndef QSttGuideBookTreeWidget_Win_H
#define QSttGuideBookTreeWidget_Win_H

#include "SttGuideBookTreeWidget.h"
#include "../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbSmartGenWzd.h"
#include "../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbWzdItemSetState.h"

class QSttGuideBookTreeWidget_Win : public QSttGuideBookTreeWidget
{
    Q_OBJECT
public:
  explicit QSttGuideBookTreeWidget_Win(CExBaseObject *pSttGuideBook,CSttFrame_GbTree *pTreeParas,QWidget *parent = 0);

    virtual void InitButton();
	virtual void OnItemSelChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);
	virtual BOOL OnItemBDblClk(CExBaseListTreeCtrl  *pTreeCtrl, CExBaseObject *pSelObj)	;
	virtual void HideAllBtns();
	virtual void UpdateButtons();

	BOOL m_bTreeUpdateFinish;
	BOOL m_bTreeCheckStateChanging;

	//LINUX��ʱ�����ű༭����
//#ifndef _PSX_QT_LINUX_
	QToolButton *m_pBtnNew;
    QToolButton *m_pBtnDeleteCurr;
    QToolButton *m_pBtnEditCurr;
	QToolButton *m_pBtnSaveCurr;
//#endif

//windows�£������Ҽ��˵�
//#ifndef _PSX_QT_LINUX_
	QMenu *m_MenuGuideBook;
	QMenu *m_subMenuCommCmdNew;  //�½�ͨѶ������Ӳ˵�
	QMenu *m_subMenuAddCfgMacro;  //����������������Ŀ���Ӳ˵���IEC61850���á�Ӳ��ͨ��ӳ�䡢ϵͳ��������
	QAction *m_ActItemsNew;      //�½���Ŀ����
	QAction *m_ActItemsNew_BFT;  //�½�����ǰ׼��
	QAction *m_ActItemsNew_AFT;  //�½����Ժ�ָ�
	QAction *m_ActDeleteCurr;    //ɾ����ǰѡ����Ŀ
	QAction *m_ActEditCurr;      //�༭��ǰѡ����Ŀ
	QAction *m_ActSaveCurr;      //���浱ǰѡ����Ŀ
	QAction *m_ActWzdNew;        //��ӹ�����
	QAction *m_ActTestFrom;      //�ӵ�ǰѡ����Ŀ��ʼ����
	QAction *m_ActTestThis;      //���Ե�ǰѡ����Ŀ
	QAction *m_ActNewIecCfg;     //�½�IEC61850Config��Ŀ
	QAction *m_ActViewRpts;      //�鿴����
	QAction *m_ActRsltExpr;		 //����ж�
	QAction *m_ActMoveUp;        //����
	QAction *m_ActMoveDown;      //����
	QAction *m_ActItemCopy;        //����
	QAction *m_ActItemPaste;      //ճ��
	QAction *m_ActAddSafety;      //�½�������ʾ
	QAction *m_ActEditSafety;      //�޸Ľ�����ʾ
	QAction *m_ActDeleteSafety;    //ɾ��������ʾ
	QAction *m_ActCmdAddGrp;       //��Ӳ���ǰ��ͨѶ��ϣ�����ǰ׼�� + ���Ժ�ָ�

	void CreateGuideBookMenu();
//#endif

protected://Linux��ʱû��

//windows
//#ifndef _PSX_QT_LINUX_
	QRect m_rectClicked;
	void mouseMoveEvent(QMouseEvent *e);
//#endif

public:
	void SwitchMacroViewByCurrSel(CExBaseObject *pSel);
	virtual void UpdateParentCheckState(QSttGuideBookTreeItem* pParent);
	virtual void UpdateChildCheckState(QSttGuideBookTreeItem* pItem);
	virtual void OnItemCheckChanged(CExBaseListTreeCtrl *pTreeCtrl, CExBaseObject *pSelObj);
	virtual void SetCheckBoxEnable(BOOL bEnable);
	virtual void SetChildCheckBoxEnable(QSttGuideBookTreeItem* pItem, BOOL bEnable);

signals:

public slots:
	virtual void slot_ItemStateChanged(CExBaseObject *pCurTestItem);
	virtual void slot_OnBtnTestFrom();
	virtual void slot_OnBtnTestThis();
//windows
//#ifndef _PSX_QT_LINUX_
    void slot_SttMouseMoveEventGbTree(QMouseEvent *e);

	void slot_OnBtnNew();
	void slot_OnBtnEditCurr();
	void slot_OnBtnDeleteCurr();
	void slot_OnBtnSaveCurr();

	void slot_OnBtnMoveUp();
	void slot_OnBtnMoveDown();

	void slot_OnBtnItemCopy();
	void slot_OnBtnItemPaste();

	void slot_OnBtnNew_AFT();
	void slot_OnBtnNew_BFT();
	void slot_OnBtnNewCommCmd();
	void slot_OnBtnCmdAddGrp();
	void slot_OnBtnNewCfgMacro();
	void slot_OnBtnNewWzd();
	void slot_OnBtnViewRpts();
	void slot_OnBtnRsltExpr();

	void slot_TreeShowMenu(QPoint pos);
	virtual void slot_ShowItems(CExBaseList *pCurTestItems);

	void slot_OnBtnAddSafety();
	void slot_OnBtnEditSafety();
	void slot_OnBtnDeleteSafety();

public:
	virtual void After_SaveCurr(const CString &strRootNodePath);
	void After_OnBtnSaveCurr_CommCmdAdd(CGbWzdCommCmdAdd *pCommCmdAdd, const CString &strRootNodePath);
	void After_OnBtnSaveCurr_MacroTestAdd(CGbWzdMacroTestAdd *pMacroTestAdd, const CString &strRootNodePath);
	void After_OnBtnSaveCurr_ItemsAdd(CGbWzdItemsAdd *pItemsAdd, const CString &strRootNodePath);
	void After_OnBtnSaveCurr_ItemEdit(CGbWzdItemEdit *pItemEdit, const CString &strRootNodePath);
	void After_OnBtnSaveCurr_ItemMove(CGbWzdItemMove *pItemMove, const CString &strRootNodePath);
	void After_OnBtnSaveCurr_ItemRsltExprEdit(CGbWzdItemRsltExprEdit *pItemRsltExprEdit, const CString &strRootNodePath);
	void After_OnBtnSaveCurr_ItemSetState(CGbWzdItemSetState *pItemSetState, const CString &strRootNodePath);
	void After_OnBtnSaveCurr_SafetyAdd(CGbWzdSafetyAdd *pSafetyAdd, const CString &strRootNodePath);
	void After_OnBtnSaveCurr_CommCmdUpdate(CGbWzdCommCmdUpdate *pCommCmdUpdate, const CString &strRootNodePath);
	void After_OnBtnSaveCurr_CommCmdAddGrp(CGbWzdCommCmdAddGrp *pCommCmdAddGrp, const CString &strRootNodePath);
	void After_OnBtnSaveCurr_ItemsDelete(CGbWzdItemsDelete *pItemsDelete, const CString &strRootNodePath);
	void WaitForGuideBookTreeUpdate(); 
	BOOL IsContinueTest_FromTree(int nType);  //nType��TestThis = 0; TestFrom = 1;
	long SendSetItemState(CSttItemBase *pItemBase);
	virtual void ExpandRootNode();
	void ExpandRootNode(CSttItems *pItems);
//#endif

};

#endif // QSttGuideBookTreeWidget_Win_H
