#ifndef QSTTGUIDEBOOKTREECTRL_H
#define QSTTGUIDEBOOKTREECTRL_H

#include <QTreeWidget>
#include <QStyleFactory>
#include "../../../Module/BaseClass/ExBaseList.h"
#include "../../SttCmd/GuideBook/SttItemBase.h"

#include "../../../../Module/BaseClass/QT/ExBaseListTreeCtrl.h"
#include "../Module/ScrollCtrl/ScrollCtrlInterface.h"

class QSttGuideBookTreeItem : public QExBaseTreeWidgetItem
{
public:
	QSttGuideBookTreeItem(QTreeWidgetItem *parent, CExBaseObject *pData);
	QSttGuideBookTreeItem(QTreeWidget *parent, CExBaseObject *pData);
	virtual ~QSttGuideBookTreeItem();
	
	void UpdateItemColor();
};

#ifdef _PSX_QT_LINUX_
class QSttGuideBookTreeCtrl : public CExBaseListTreeCtrl  ,public CScrollCtrlInterface
#else
class QSttGuideBookTreeCtrl : public CExBaseListTreeCtrl
#endif
{
    Q_OBJECT
    
public:
// 	BOOL m_bInsertIteming;  //是否正在插入项目
public:
    QSttGuideBookTreeCtrl(QFont font,QWidget *parent);
	virtual ~QSttGuideBookTreeCtrl();
    
	virtual QExBaseTreeWidgetItem* NewItem(QTreeWidgetItem *parent, CExBaseObject *pData);
	virtual QExBaseTreeWidgetItem* AddObj(CExBaseObject *pObj, BOOL bExpand=FALSE);
	virtual QExBaseTreeWidgetItem* AddObj(CExBaseObject *pObj, QExBaseTreeWidgetItem* hParent, BOOL bExpand=FALSE);
	void UpdateTestTimesIcon(QExBaseTreeWidgetItem* pItem, CExBaseObject *pObj);
	void PaintIcon_Items(const CString &strIconBack_Path, long nLevel, long nTimes, QIcon &iconDest);

	void UpdateItemColour();
	void OnItemSelChanged(CExBaseObject *pSel);
	void SetQTreeWidgetScrollWidth(long nTreeVertWidth,long nTreeLevelWidth);
	//void SetQTreeWidgetLevelScrollWidth(long nQTreeWidgetLevelScrollWidth);
	virtual QExBaseTreeWidgetItem* InsertItem(QTreeWidgetItem *parent, CExBaseObject *pData);
	QFont m_oFont;

	void InitAllIcons();
	QIcon m_icon_Items[7][11];//存放作为标题、重复测试的CSttItems项目的图标。最多5级标题，测试次数10次。大于5级标题，用M代替，测试次数大于10次，用N代替。
	QIcon m_icon_Normal[6];  //存放图标，顺序为CSttDevice、CSttItems（不作为标题，不重复）、CSttMacroTest、CSttCommCmd、CSttMacroCharItems、CSttSafety

	/*
public:
    virtual void ShowBaseList(CExBaseList *pGuideBook, bool bAddRoot=TRUE);
    virtual void AddObj(CExBaseObject *pObj, QSttGuideBookTreeItem *pTreeItem,bool bShowSelf = true);
    virtual CExBaseList* GetBaseList(){ return m_pGuideBook;    }
    virtual bool CanAdd(CExBaseObject *pObj);
    virtual bool CanAdd(UINT nClassID);
    
	//void SetCurTestItem(CExBaseObject *pCurrTestItem);
	//void ChangeItemColour(QColor color);
public:
	void ClearArrClassID();
	void AddClassID(UINT nClassID);
	void RemoveClassID(UINT nClassID);
	
protected:
    QList<unsigned long> m_arrDwClassID;
	QFont m_font;
    long GetIndexOfClassID(UINT nClassID);
	*/

signals:
	void sig_MouseMoveGbTree(QMouseEvent *);
	void sig_focusOutEventGbTree(QFocusEvent *);

public slots:
// 	virtual void slot_TreeItemChanged(QTreeWidgetItem *pTreeItem, int nCol);

protected:
	void mouseMoveEvent(QMouseEvent *e);
	void mousePressEvent(QMouseEvent *ev);
	void mouseReleaseEvent(QMouseEvent *ev);
	virtual void focusOutEvent(QFocusEvent *e);

private:
	//CString m_strCurrTestID;
    CExBaseList *m_pGuideBook;
};

#endif // QSTTGUIDEBOOKTREECTRL_H
