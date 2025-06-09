#ifndef QSTTSELSCLFILEDLG_H
#define QSTTSELSCLFILEDLG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "QSttSelSclFileWidget.h"

class QSttSelSclFileDlg : public QDialog
{
	Q_OBJECT

public:
	QSttSelSclFileDlg(QWidget *parent);
	virtual ~QSttSelSclFileDlg();
	void InitUI();

private:
	QSttSelSclFileWidget *m_pSttSelSclFileWidget;

	QVBoxLayout *m_pMainVLayout;
	QPushButton *m_pOK_PushButton;
//	QPushButton *m_pCancel_PushButton;
	QHBoxLayout *m_pOK_CancelHLayout;

public slots:
	void slot_OKClicked();
//	void slot_CancelClicked();
};

#endif // QSTTSELSCLFILEDLG_H
