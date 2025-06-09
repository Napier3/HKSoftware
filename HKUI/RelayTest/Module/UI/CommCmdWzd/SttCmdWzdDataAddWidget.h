#ifndef SttCmdWzdDataAddWidget_H
#define SttCmdWzdDataAddWidget_H

#include <QDialog>
#include <QFont>
#include "SttCmdWzdDsEditGrid.h"

#include "../../../../AutoTest/Module/GbItemsGen/GbSmartGenWzd/GbMacroGenWzd.h"
#include "../../SttCmd/GuideBook/SttItems.h"

namespace Ui {
class QSttCmdWzdDataAddWidget;
}

//通讯命令向导，主窗口
class QSttCmdWzdDataAddWidget : public QDialog, public CExBaseListGridOptrInterface 
{
    Q_OBJECT
public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);
	virtual BOOL OnEditCellLBDblClk(QTableWidget *pGridCtrl, int nRow, int nCol, UINT nChar);

public:
    explicit QSttCmdWzdDataAddWidget(QWidget *parent = 0);
    virtual ~QSttCmdWzdDataAddWidget();

	CSttCmdWzdDsShowGrid *m_pEditGrid;
	void ShowDataset(CDvmDataset *pDataset);
	CSttCommCmd *m_pCommCmdRef;

public:
	void UI_SetFont();
	void EnableInsertBtn(CExBaseObject *pData);

signals:
	void sig_CmdWzd_AddData(CDvmData *pData);


private slots:
    void on_m_btnInsertData_clicked();
    void on_m_btnClose_clicked();

private:
	Ui::QSttCmdWzdDataAddWidget *ui;
};

#endif // SttCmdWzdDataAddWidget_H
