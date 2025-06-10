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

	//LINUX暂时不开放编辑功能
//#ifndef _PSX_QT_LINUX_
	QToolButton *m_pBtnNew;
    QToolButton *m_pBtnDeleteCurr;
    QToolButton *m_pBtnEditCurr;
	QToolButton *m_pBtnSaveCurr;
//#endif

//windows下，创建右键菜单
//#ifndef _PSX_QT_LINUX_
	QMenu *m_MenuGuideBook;
	QMenu *m_subMenuCommCmdNew;  //新建通讯命令的子菜单
	QMenu *m_subMenuAddCfgMacro;  //添加配置类电气量项目的子菜单：IEC61850配置、硬件通道映射、系统参数配置
	QAction *m_ActItemsNew;      //新建项目分类
	QAction *m_ActItemsNew_BFT;  //新建测试前准备
	QAction *m_ActItemsNew_AFT;  //新建测试后恢复
	QAction *m_ActDeleteCurr;    //删除当前选中项目
	QAction *m_ActEditCurr;      //编辑当前选中项目
	QAction *m_ActSaveCurr;      //保存当前选中项目
	QAction *m_ActWzdNew;        //添加功能向导
	QAction *m_ActTestFrom;      //从当前选中项目开始测试
	QAction *m_ActTestThis;      //测试当前选中项目
	QAction *m_ActNewIecCfg;     //新建IEC61850Config项目
	QAction *m_ActViewRpts;      //查看报告
	QAction *m_ActRsltExpr;		 //结果判断
	QAction *m_ActMoveUp;        //上移
	QAction *m_ActMoveDown;      //下移
	QAction *m_ActItemCopy;        //拷贝
	QAction *m_ActItemPaste;      //粘贴
	QAction *m_ActAddSafety;      //新建接线提示
	QAction *m_ActEditSafety;      //修改接线提示
	QAction *m_ActDeleteSafety;    //删除接线提示
	QAction *m_ActCmdAddGrp;       //添加测试前后通讯组合：测试前准备 + 测试后恢复

	void CreateGuideBookMenu();
//#endif

protected://Linux暂时没试

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
	BOOL IsContinueTest_FromTree(int nType);  //nType：TestThis = 0; TestFrom = 1;
	long SendSetItemState(CSttItemBase *pItemBase);
	virtual void ExpandRootNode();
	void ExpandRootNode(CSttItems *pItems);
//#endif

};

#endif // QSttGuideBookTreeWidget_Win_H
