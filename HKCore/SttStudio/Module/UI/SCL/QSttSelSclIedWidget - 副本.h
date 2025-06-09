#ifndef QSTTSELSCLIEDWIDGET_H
#define QSTTSELSCLIEDWIDGET_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include "SttSelSclIedGrid.h"
#include "../../../../61850/Module/SCL/SclIecCfgDatas.h"

class QSttSelSclIedWidget : public QDialog
{
	Q_OBJECT

public:
	QSttSelSclIedWidget(QWidget *parent);
	virtual ~QSttSelSclIedWidget();
	void InitUI();
	void InitDatas(CSclStation *pSclStation);

private:
	CSttSelSclIedGrid *m_pSttSelSclIedGrid;
	QVBoxLayout *m_pMainVLayout;
	QPushButton *m_pOK_PushButton;
	QHBoxLayout *m_pOK_CancelHLayout;

public slots:
	void slot_OKClicked();
	
};

#endif // QSTTSELSCLIEDWIDGET_H
