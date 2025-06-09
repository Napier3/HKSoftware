#ifndef STTSCLCTRLS_WIDGETBASE_H
#define STTSCLCTRLS_WIDGETBASE_H

#include <QWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QSplitter>

#include "Grid/SclCtrlsGridBase.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"

#include "Grid/SclCtrlChsGridBase.h"

#define STT_SCL_CTRLS_TYPE_SMVIN                        0
#define STT_SCL_CTRLS_TYPE_SMVOUT                       1
#define STT_SCL_CTRLS_TYPE_GOOSEIN                      2
#define STT_SCL_CTRLS_TYPE_GOOSEOUT                     3


class QSttSclCtrlsWidget : public QWidget ,public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QSttSclCtrlsWidget(long nCtrlsType,CExBaseList *pSelectedSclCtrlsRef, QFont oFont ,QWidget *parent=NULL);
	~QSttSclCtrlsWidget();

	void ShowDatas(CSclCtrls* pSclCtrls);
	void UpdateSelectedState();

	CSclCtrlsGridBase *m_pSclCtrlsGrid;
private:
	long m_nCtrlsType;
	CExBaseList *m_pSelectedSclCtrlsRef;

protected:
	virtual void InitUI();
	virtual void InitData(CSclCtrls* pSclCtrls);
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

	QVBoxLayout *m_pMainVLayout;
	QSplitter *m_pSplitter;
	QFont m_oIecFont;
	
	//2023/9/14 wjs
	//通道表格
	QSclCtrlChsGridBase* m_pSclCtrlsChGrid;

signals:
	void sig_UpdateCB_ChDatas(CExBaseList *pCB_Data);

protected slots:
	void slot_UpdateCB_ChDatas(CExBaseList *pCB_Data);
};

extern CFont *g_pSttGlobalFont;

#endif // STTSCLCTRLS_WIDGETBASE_H
