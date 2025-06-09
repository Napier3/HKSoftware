#ifndef WEAKSETGRID_H
#define WEAKSETGRID_H

#include "../QExBaseListGridBase/QExBaseListGridBase.h"
#include "../QExBaseListGridBase/QExBaseListFloatEditDelegBase.h"
#include "../../../SttCmd/SttChMaps.h"
#include "../../../SttCmd/SttChMap.h"
#include <QObject>
#include "../CommonMethod/commonMethod.h"
#define WEAKSET_GRID_COLS		4

class CWeakSetGrid : public QExBaseListGridBase
{
	Q_OBJECT//zhouhj 20210715 要使用信号、槽必须要加此
public:
	CWeakSetGrid(QWidget* pparent);
	virtual ~CWeakSetGrid();

public:
	virtual void InitGrid();
	virtual void InitGridTitle();

	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);
	virtual void CreateGridMenu();//创建表格选中后显示菜单


public:
	//编辑处理函数
	static void EndEditCell_WeakRateSetString (int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);

private:
	BOOL GetCurSelChMapObj(CSttChMaps **ppChMaps,CSttChMap **ppChMap,CSttHdCh **ppHdCh,float &fValue,BOOL &bPrimaryValue);

	QMenu *m_pWeakSetMenu;
	QAction *m_pThreePhaseEqualAction;
	QAction *m_pAllEqualAction;

	QExBaseListFloatEditDelegBase *m_pPrimaryValue_DelegBase;
	QExBaseListFloatEditDelegBase *m_pSecondaryValue_DelegBase;

	BOOL m_bRunning;
	bool eventFilter(QObject *obj, QEvent *event);
	virtual void mousePressEvent(QMouseEvent *);

protected slots:
	//2023/7/24 wjs
	void slot_OnItemClicked(int nRow,int nCol);

	void slot_ThreePhaseEqualActlicked();
	void slot_AllEqualActlicked();
	virtual void slot_GridShowMenu(QPoint pos);//用于显示菜单

};

#endif // WEAKSETGRID_H
