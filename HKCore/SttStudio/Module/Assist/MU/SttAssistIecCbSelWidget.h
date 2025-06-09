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
	void on_m_btnCancel_clicked();//20230214 zhouhj ���ݱ������Է���,����ʾ����֧��"ȡ��",ȡ�������"����̽��"��ťһֱ��˸��ʾ,����ͨ���ý���ѡ����ƿ�
};

#endif // STTASSISTIECRECORDDETECTWIDGET_H
