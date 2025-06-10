#ifndef  QSttCommCfgPkgMonitorDlg_H
#define  QSttCommCfgPkgMonitorDlg_H
 
#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

#include "QSttCommCfgPkgMonitorWidget.h"

class QSttCommCfgPkgMonitorDlg : public QDialog
{
	Q_OBJECT

public:
	QSttCommCfgPkgMonitorDlg(QSttCommCfgPkgMonitorWidget *pSttCommCfgPkgMonitorWidget,QWidget *parent = 0);
	~QSttCommCfgPkgMonitorDlg();

	void InitUI();
	void SetDialogFont();


	QVBoxLayout *m_pMainLayout;  
	QSttCommCfgPkgMonitorWidget *m_pQSttCommCfgPkgMonitorWidget;
	QPushButton *m_pOK_PushButton; 
	QPushButton *m_pCancel_PushButton;   

public slots:
	void slot_OKClicked();
	void slot_CancelClicked();

};

#endif // QSttCommCfgPkgMonitorDlg_H
