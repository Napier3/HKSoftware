#ifndef SttCommCmdWzd_ErrorValueWidget_H
#define SttCommCmdWzd_ErrorValueWidget_H

#include <QDialog>
#include <QFont>
#include "../../../../Module/DataMngr/DataGroup.h"
#include "../Module/QExBaseListGridBase/QExBaseListGridBase.h"
#include "../Module/QExBaseListGridBase/QExBaseListComBoxDelegBase.h"

namespace Ui {
class QSttCommCmdWzd_ErrorValueWidget;
}

//////////////////////////////////////////////////////////////////////////
//
class QSttCommCmdWzd_ErrorValueGrid_StateTest : public QExBaseListGridBase
{
public:
	QSttCommCmdWzd_ErrorValueGrid_StateTest(QWidget* pparent);
	virtual ~QSttCommCmdWzd_ErrorValueGrid_StateTest();

public:
	void InitLanguage();
	virtual void InitGrid();
	virtual void InitGridTitle();

	QExBaseListCheckBoxDelegate *m_pSelect;

	virtual void ShowDatas(CExBaseList *pDatas, BOOL bResetScrollBars=TRUE);
	virtual void ShowData(CExBaseObject *pData, int& nRow, BOOL bInsertRow=TRUE);

	static void EndEditCell_Select(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
	static void EndEditCell_RelError(int nRow, int nCol,QGV_ITEM *pCell, QExBaseListGridBase *pGrid);
};

//通讯命令向导，主窗口
class QSttCommCmdWzd_ErrorValueWidget : public QDialog
{
	Q_OBJECT
public:
    explicit QSttCommCmdWzd_ErrorValueWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttCommCmdWzd_ErrorValueWidget();

public:
	CString m_strTestMacroID;
	void InitUI();
	void UI_SetFont(QFont font);
	void ShowDatas(CDataGroup* pDataGroup);
	void FinishEditDatas(CDataGroup* pDataGroup);
	virtual void resizeEvent(QResizeEvent *);
	void InitLanguage();

	QSttCommCmdWzd_ErrorValueGrid_StateTest* m_pGridStateTest;

private:
	Ui::QSttCommCmdWzd_ErrorValueWidget *ui;

};

#endif // SttCommCmdWzd_DsReadWidget_H
