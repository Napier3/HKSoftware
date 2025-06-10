#ifndef STTASSISTIECRECORDDETECTWIDGET_H
#define STTASSISTIECRECORDDETECTWIDGET_H

#include <QDialog>
#include "ui_SttAssistIecCbSelWidget.h"

#include "../../RecordTest/UI/SttIecCbGrid.h"

class QSttAssistIecCbSelWidget : public QWidget, public CExBaseListGridOptrInterface
{
	Q_OBJECT

public:
	QSttAssistIecCbSelWidget(QWidget *parent = 0);
	~QSttAssistIecCbSelWidget();

	void ShowAllCapDevice();

private:
	Ui::QSttAssistIecCbSelWidget *ui;

public:
	CSttIecCbGrid *m_pGridIecCb;

public:
	void InitUI();
	virtual void OnDataSelChanged(QTableWidget *pGridCtrl, int nRow, int nCol);

private slots:
	void on_m_btnOk_clicked();
	void on_m_btnCancel_clicked();//20230214 zhouhj 根据北京测试反馈,该提示助手支持"取消",取消后可在"报文探测"按钮一直闪烁提示,后续通过该界面选择控制块
};

#endif // STTASSISTIECRECORDDETECTWIDGET_H
