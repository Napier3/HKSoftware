#ifndef QITEMTABLEBASE_H
#define QITEMTABLEBASE_H

#include <QTableWidget>
#include <QMap>
#include <QAction>
#include <QMenu>
#include "..\..\Module\SttTest\Common\tmt_test_mngr.h"
class QItemTableBase : public QTableWidget
{
	Q_OBJECT

public:
	QItemTableBase(QWidget *parent);
	virtual ~QItemTableBase();

	virtual void InitData();
	virtual void SetData(TMT_PARAS_MNGR* pTestMngr);
	virtual void UpdateItem(int nIndex);
	virtual void UpdateItemResult(int nIndex);
	virtual void UpdateCurrItemResult();
	virtual void ClearItemResult(int nIndex);
	virtual void ClearCurrItemResult();

	PTMT_PARAS_HEAD GetCurrentItem();

	void SetCurrentRow(int nRow);
	int GetCurrentRow(){	return m_nCurRow;	}

	virtual void InitUI();

	virtual CString GetTestItemResultText(PTMT_PARAS_HEAD pParas){ return ""; };
	virtual bool GetTestItemResultJudge(PTMT_PARAS_HEAD pParas);
	
	int m_nPsuDiffRateTest;//2023-12-25 suyang 差动：标志启动段斜率动作与未动作


protected:
	void keyPressEvent(QKeyEvent *event);
	void mousePressEvent(QMouseEvent *event);

signals:
	void sig_AddItemBF();
	void sig_AddItemAF();
	void sig_DeleteCurr();
	void sig_Delete_N_1();//删除n-1
	void sig_ClearCurrResult();
	void sig_ClearAllResult();
	void sig_Table_cellClicked(int row);
	void sig_SelectAll();
	void sig_UnselectAll();

	void sig_TableChooseChanged(PTMT_PARAS_HEAD pTest);
public slots:
	virtual void slot_Table_cellClicked ( int row, int column);//2024-4-2 wuxinyi 满足现需求故改为虚函数

	void slot_customContextMenuRequested(QPoint &pos);

	void slot_ActionTestAddBeforeClicked();
	void slot_ActionTestAddAfterClicked();
	void slot_ActionTestDeleteCurrClicked();
	void slot_ActionTestDelete_N_1_Clicked();
	void slot_ActionTestClearResultClicked();
	void slot_ActionTestClearAllResultClicked();
	void slot_ActionTestSelectAllClicked();
	void slot_ActionTestUnselectAllClicked();

public:
	TMT_PARAS_MNGR *m_pTestMngr;

public:
	int m_nCurRow;
	QMenu *m_TestMenu;
	QAction *m_TestAddAction;
	QAction *m_TestDelAction;
	QAction *m_TestClearAction;
	QAction *m_TestClearResultAction;
	QAction *m_TestClearAllResultAction;
	QAction *m_TestSelectAllAction;
	QAction *m_TestUnSelectAllAction;
};

#endif // QITEMTABLEBASE_H
