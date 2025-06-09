#ifndef SttCommCmdWzd_DsReadWidget_H
#define SttCommCmdWzd_DsReadWidget_H

#include <QDialog>
#include <QFont>
#include "SttCmdWzdGrid_Read.h"
#include "..\..\..\..\AutoTest\Module\GbItemsGen\GbSmartGenWzd\SttCmdWzd_CmdDataset.h"

namespace Ui {
class QSttCommCmdWzd_DsReadWidget;
}

//通讯命令向导，主窗口
class QSttCommCmdWzd_DsReadWidget : public QDialog, public CExBaseListGridOptrInterface 
{
    Q_OBJECT
public:
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

public:
    explicit QSttCommCmdWzd_DsReadWidget(QFont font,QWidget *parent = 0);
    virtual ~QSttCommCmdWzd_DsReadWidget();

	CSttCmdWzdGrid_Read *m_pReadGrid;
	CSttCmdWzd_Step *m_pCurrStep;

public:
	void UI_SetFont(QFont font);
	void ShowDatas(CExBaseList *pList);
	void EnableSettingZone();

public slots:

signals:
	void sig_EnableSettingZone();

private slots:
	void on_m_cmbSettingZone_currentIndexChanged(int index);
	void slot_EnableSettingZone();

private:
	Ui::QSttCommCmdWzd_DsReadWidget *ui;

};

#endif // SttCommCmdWzd_DsReadWidget_H
